#include "cryptoapi.h"
#include <QDebug>
#include <QTemporaryFile>

#define KEY_CONTAINER_NAME             ( LPCTSTR ) "PMS_CRYPT"
#define CIPHERTEXT_SIGNATURE           "PMSZ"
#define KEY_LENGTH                     0x00800000
#define ENCRYPT_ALGORITHM              CALG_RC4
#define HASH_ALGORITHM                 CALG_MD5
#define ENCRYPT_BLOCK_SIZE             8


// Signature( 4B ) PublicKeyLen( 4B ) KeyData  PrivateKeyLen( 4B ) KeyData Data EOF

CCryptoAPI::CCryptoAPI( )
{
    hCryptProvider = NULL;
    BOOL bRet = ConnectCSP( );
    if ( !bRet ) {
        qDebug( ) << "ConnectCSP failed." << endl;
    }
}

CCryptoAPI::~CCryptoAPI( )
{
    if ( 0 != hCryptProvider ) {
        BOOL bRet = CryptReleaseContext( hCryptProvider, 0 );
        if ( !bRet ) {
            qDebug( ) << "CryptReleaseContext failed." << endl;
        }
    }
}

BOOL CCryptoAPI::ConnectCSP( )
{
    BOOL bRet = FALSE;

    bRet = CryptAcquireContext( &hCryptProvider, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0 );
    if ( !bRet && NTE_BAD_KEYSET == ( LONG ) GetLastError( ) ) {
        bRet = CryptAcquireContext( &hCryptProvider, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET );
    }

    return bRet;
}

BOOL CCryptoAPI::FileOpen( QFile& file, BOOL bWrite, BOOL bTemp )
{
    BOOL bRet = file.exists( );

    if ( !bRet && !bTemp ) {
        return bRet;
    }

    QIODevice::OpenMode mode = QIODevice::ReadWrite;
    if ( bWrite ) {
        mode |= QIODevice::Truncate;
    }

    bRet = file.isOpen( );
    if (  !bRet ) {
        bRet = file.open( mode );
    }

    return bRet;
}

BOOL CCryptoAPI::FileOpen( QFile &srcFile, QFile &dstFile )
{
    BOOL bRet = FALSE;

    if ( !srcFile.exists( ) ) {
        return bRet;
    }

    if ( !FileOpen( srcFile, FALSE, FALSE ) ) {
        return bRet;
    }

    if ( !FileOpen( dstFile, TRUE, TRUE ) ) {
        srcFile.close( );
        return bRet;
    }

    bRet = TRUE;

    return bRet;
}

VOID CCryptoAPI::FileClose( QFile &file )
{
    if ( file.isOpen( ) ) {
        file.close();
    }
}

VOID CCryptoAPI::FileClose( QFile &srcFile, QFile &dstFile )
{
    FileClose( srcFile );
    FileClose( dstFile );
}

BOOL CCryptoAPI::FileCopy( QFile &srcFile, QFile &dstFile )
{
    BOOL bRet = FALSE;

    if ( dstFile.exists( ) ) {
        dstFile.remove( );
    }

    bRet = srcFile.copy( dstFile.fileName( ) );
    //qDebug( ) << srcFile.errorString( ) << endl;

    return bRet;
}

BOOL CCryptoAPI::OperateSignature( QFile &file, DWORD &dwSignature, BOOL bWrite )
{
    BOOL bRet = FALSE;

    if ( !file.isOpen( ) && !FileOpen( file, bWrite, FALSE ) ) {
        return bRet;
    }

    char* pSignature = ( char* ) &dwSignature;
    quint64 nMaxLen = sizeof( dwSignature );

    qint64 nRet = bWrite ? file.write( pSignature, nMaxLen ) : file.read( pSignature, nMaxLen );
    bRet = ( -1 != nRet );

    return bRet;
}

BOOL CCryptoAPI::WriteKeyValue( QFile &file, HCRYPTKEY& hKey, HCRYPTKEY& hExpKey )
{
    BOOL bRet = FALSE;
    DWORD dwKeyBlobLen = 0;
    PBYTE pKeyBlob = NULL;
    DWORD dwBlobType = 0;
    qint64 nRet = 0;
    BOOL bPrivate =  ( 0 != hExpKey ) ;

    dwBlobType = bPrivate ? SIMPLEBLOB : PUBLICKEYBLOB;

    bRet = CryptExportKey( hKey, hExpKey, dwBlobType, 0, NULL, &dwKeyBlobLen );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    pKeyBlob = new BYTE[ dwKeyBlobLen ];
    bRet = CryptExportKey( hKey, hExpKey, dwBlobType, 0, pKeyBlob, &dwKeyBlobLen );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    bRet = OperateSignature( file, dwKeyBlobLen, TRUE );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    nRet = file.write( ( const char* ) pKeyBlob, dwKeyBlobLen );
    bRet = ( -1 != nRet );
    if (!bRet ) {
        goto DESTROY_KEY;
    }

    DESTROY_KEY:
    if ( NULL != pKeyBlob ) {
        delete [ ] pKeyBlob;
        pKeyBlob = NULL;
    }

    return bRet;
}

BOOL CCryptoAPI::WriteKey( QFile &file, HCRYPTKEY &hKey )
{
    BOOL bRet = FALSE;
    HCRYPTKEY hPublicKey = NULL;
    HCRYPTKEY hExpKey = NULL;

    // CryptGetUserKey Get public key
    bRet = CryptGenKey( hCryptProvider, ENCRYPT_ALGORITHM,
                                           KEY_LENGTH | CRYPT_EXPORTABLE, &hKey );
    if ( !bRet ) {
        return bRet;
    }

    bRet = CryptGetUserKey( hCryptProvider, AT_KEYEXCHANGE, &hPublicKey );
    if ( !bRet && NTE_NO_KEY == ( HRESULT ) GetLastError( ) ) {
        bRet = CryptGenKey( hCryptProvider, AT_KEYEXCHANGE, CRYPT_EXPORTABLE, &hPublicKey );
    }

    if ( !bRet ) {
        return bRet;
    }

    bRet = WriteKeyValue( file, hPublicKey, hExpKey );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    hExpKey = hPublicKey;
    bRet = WriteKeyValue( file, hKey, hExpKey );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    DESTROY_KEY:
    if ( 0 != hPublicKey ) {
        CryptDestroyKey( hPublicKey );
        hPublicKey = NULL;
    }

    return bRet;
}

BOOL CCryptoAPI::ReadKeyValue( QFile &file, HCRYPTKEY &hKey, HCRYPTKEY& hPublicKey )
{
    BOOL bRet = FALSE;
    DWORD dwKeyBlobLen = 0;
    PBYTE pKeyBlob = NULL;
    DWORD dwError = 0;
    qint64 nRet = 0;

    bRet = OperateSignature( file, dwKeyBlobLen, FALSE );
    if ( !bRet ) {
        return bRet;
    }

    pKeyBlob = new BYTE[ dwKeyBlobLen ];

    nRet = file.read( ( char* ) pKeyBlob, dwKeyBlobLen );
    bRet = ( -1 != nRet );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    bRet = CryptImportKey( hCryptProvider, pKeyBlob, dwKeyBlobLen, hPublicKey, 0,
                                               0 != hPublicKey ? &hKey : &hPublicKey );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    dwError = GetLastError( );

    DESTROY_KEY:
    if ( NULL != pKeyBlob ) {
        delete [ ] pKeyBlob;
        pKeyBlob = NULL;
    }

    return bRet;
}

BOOL CCryptoAPI::ReadKey( QFile &file, HCRYPTKEY &hKey )
{
    BOOL bRet = FALSE;
    HCRYPTKEY hPublicKey = NULL;

    bRet = ReadKeyValue( file, hKey, hPublicKey );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    bRet = ReadKeyValue( file, hKey, hPublicKey );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    DESTROY_KEY:
    if ( 0 != hPublicKey ) {
        CryptDestroyKey( hPublicKey );
        hPublicKey = NULL;
    }

    return bRet;
}

BOOL CCryptoAPI::OperateKey( QFile &file, HCRYPTKEY &hKey, BOOL bWrite )
{
    BOOL bRet = FALSE;

    bRet = bWrite ? WriteKey( file, hKey ) : ReadKey( file, hKey );

    return bRet;
}

BOOL CCryptoAPI::CryptDoc( QString &strFile, BOOL bEncrypt )
{
    BOOL bRet = FALSE;
    QFile srcFile( strFile );
    QTemporaryFile dstFile;

    if ( !FileOpen( srcFile, dstFile ) ) {
        return bRet;
    }

    bRet = bEncrypt ? DataEncrypt( srcFile, dstFile ) : DataDecrypt( srcFile, dstFile );

    //qDebug( ) << dstFile.fileName( ) << endl;
    FileClose( srcFile, dstFile );

    bRet = FileCopy( dstFile, srcFile );

    return bRet;
}

DWORD CCryptoAPI::SignatureValue( )
{
    QString strSignature = CIPHERTEXT_SIGNATURE;
    DWORD dwSignature = *( LPDWORD ) strSignature.toAscii( ).data( );
    //char cData[ ] = { 'P', 'M', 'S', 'Z' }; // 50 4d 53 5a

    return dwSignature;
}

BOOL CCryptoAPI::DataEncrypt( QFile &srcFile, QFile &dstFile )
{
    BOOL bRet = FALSE;
    HCRYPTKEY hKey = NULL;

    DWORD dwSignature = SignatureValue( );

    bRet = OperateSignature( dstFile, dwSignature, TRUE );
    if ( !bRet ) {
        return bRet;
    }

    bRet = OperateKey( dstFile, hKey, TRUE );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    bRet = CryptData( srcFile, dstFile, hKey, TRUE );

    DESTROY_KEY:
    if ( 0 != hKey ) {
        CryptDestroyKey( hKey );
    }

    return bRet;
}

BOOL CCryptoAPI::DataDecrypt( QFile &srcFile, QFile &dstFile )
{
    BOOL bRet = FALSE;
    DWORD dwSignature;
    HCRYPTKEY hKey = NULL;

    bRet = OperateSignature( srcFile, dwSignature, FALSE );
    if ( !bRet || SignatureValue( ) != dwSignature ) {
        return bRet;
    }

    bRet = OperateKey( srcFile, hKey, FALSE );
    if ( !bRet ) {
        goto DESTROY_KEY;
    }

    bRet = CryptData( srcFile, dstFile, hKey, FALSE );

    DESTROY_KEY:
    if ( 0 != hKey ) {
        CryptDestroyKey( hKey );
    }

    return bRet;
}


BOOL CCryptoAPI::CryptData( QFile &srcFile, QFile &dstFile, HCRYPTKEY &hKey, BOOL bEncrypt )
{
    BOOL bRet = TRUE;
    BOOL bEof = FALSE;
    DWORD dwBlockLen = 0;
    DWORD dwBufferLen = 0;
    PBYTE pData = NULL;
    qint64 nReadLen = -1;

    dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;
    dwBufferLen = dwBlockLen;

    if ( 1 < ENCRYPT_BLOCK_SIZE ) {
        dwBufferLen += ENCRYPT_BLOCK_SIZE;
    }

    pData = new BYTE[ dwBufferLen ];

    do {
        nReadLen = srcFile.read( ( char* ) pData, dwBlockLen );
        bRet = ( -1 != nReadLen );
        if ( !bRet ) {
            break;
        }

        bEof = ( ( DWORD ) nReadLen < dwBlockLen );
        bRet = bEncrypt ? CryptEncrypt( hKey, NULL, bEof, 0, pData,( LPDWORD ) &nReadLen, dwBufferLen ) :
                          CryptDecrypt( hKey, NULL, bEof, 0, pData, ( LPDWORD ) &nReadLen );
        if ( !bRet ) {
            break;
        }

        nReadLen = dstFile.write( ( const char* ) pData, nReadLen );
        bRet = ( -1 != nReadLen );
        if ( !bRet ) {
            break;
        }
    } while ( !bEof );

    if ( 0 != pData ) {
        delete [ ] pData;
        pData = NULL;
    }

    return bRet;
}
