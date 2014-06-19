#ifndef CRYPTOAPI_H
#define CRYPTOAPI_H

#include "CryptoAPI_global.h"
#include <windows.h>
#include <WinCrypt.h>
#include <QFile>

class CRYPTOAPISHARED_EXPORT CCryptoAPI {
public:
    CCryptoAPI( );
    ~CCryptoAPI( );

public:
    BOOL CryptDoc( QString& strFile, BOOL bEncrypt );

private:
    BOOL ConnectCSP( );
    BOOL OperateSignature( QFile& file, DWORD& dwSignature, BOOL bWrite );
    BOOL OperateKey( QFile& file, HCRYPTKEY& hKey, BOOL bWrite );
    BOOL DataEncrypt( QFile& srcFile, QFile& dstFile );
    BOOL DataDecrypt( QFile& srcFile, QFile& dstFile );
    BOOL WriteKey( QFile& file, HCRYPTKEY& hKey );
    BOOL ReadKey( QFile& file, HCRYPTKEY& hKey );
    BOOL CryptData( QFile& srcFile, QFile& dstFile, HCRYPTKEY& hKey, BOOL bEncrypt );

    BOOL WriteKeyValue( QFile& file, HCRYPTKEY& hKey, HCRYPTKEY& hExpKey  );
    BOOL ReadKeyValue( QFile& file, HCRYPTKEY& hKey, HCRYPTKEY& hPublicKey );

    inline DWORD SignatureValue( );


    inline BOOL FileOpen( QFile& file, BOOL bWrite, BOOL bTemp );
    inline VOID FileClose( QFile& file );

    inline BOOL FileOpen( QFile& srcFile, QFile& dstFile );
    inline VOID FileClose( QFile& srcFile, QFile& dstFile );

    inline BOOL FileCopy( QFile& srcFile, QFile& dstFile );

private:
    HCRYPTPROV hCryptProvider;
};

#endif // CRYPTOAPI_H
