// CryptDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CryptDll.h"

#define KEY_CONTAINER_NAME		TEXT( "PMSKeyContainer" )
#define KEY_LENGTH 0x40000000
#define KEY_FILE_NAME TEXT( "pms.key" )

#define PROV_NAME		MS_DEF_PROV
#define PROV_TYPE		PROV_RSA_FULL

#define ALG_BLOCK		CALG_RC2
#define ALG_STREAM	CALG_RC4
#define ALG_HASH		CALG_MD5

#if FALSE
1.Get CSP Handle ( CryptAcquireContext )
	A. Generate Key ( CryptGenKey )--->Export Key ( CryptExportKey )--->Save / Transfer
	B.Import Key ( CryptImportKey )---->Encrypt ( CryptEncrypt ) / Decrypt ( CryptDecrypt )
#endif

static HCRYPTPROV g_hCryptProv = NULL;
static HCRYPTKEY g_hCryptKey = NULL;

BOOL InitializeKey(  DWORD dwAlgID )
{
	BOOL bRet = FALSE;
	HCRYPTKEY hKey = NULL;

	if ( NULL == g_hCryptProv ) {
		return bRet;
	}

	bRet = CryptGetUserKey ( g_hCryptProv, dwAlgID, &hKey );

	if ( !bRet && NTE_NO_KEY == GetLastError( ) ) {
		bRet = CryptGenKey( g_hCryptProv, dwAlgID, 0, &hKey );
	}

	if ( bRet && NULL != hKey ) {
		bRet = CryptDestroyKey( hKey );
	} else {
		bRet = CryptReleaseContext( g_hCryptProv, 0 );
		g_hCryptProv = NULL;
	}

	return bRet;
}

BOOL WINAPI CryptStartup( )
{
	BOOL bRet = FALSE;
	bRet = CryptAcquireContext( &g_hCryptProv, KEY_CONTAINER_NAME, PROV_NAME, PROV_TYPE, 0 );

	if ( !bRet && NTE_BAD_KEYSET == GetLastError( ) ) {
		bRet = CryptAcquireContext( &g_hCryptProv, KEY_CONTAINER_NAME, PROV_NAME, PROV_TYPE, CRYPT_NEWKEYSET );
	}

	if ( !bRet ) {
		return bRet;
	}

	bRet = InitializeKey( AT_SIGNATURE );
	bRet = InitializeKey( AT_KEYEXCHANGE );

	return bRet;
}

BOOL WINAPI CryptCleanup( )
{
	BOOL bRet = FALSE;

	if ( NULL != g_hCryptKey ) {
		bRet =  CryptDestroyKey ( g_hCryptKey );
		g_hCryptKey = NULL;
	}

	if ( NULL != g_hCryptProv ) {
		bRet = CryptReleaseContext( g_hCryptProv, 0 );
		g_hCryptProv = NULL;
	}

	return bRet;
}

BOOL WINAPI EncryptData( PBYTE pData, IN OUT DWORD& dwDataLen )
{
	BOOL bRet = FALSE;
	HCRYPTKEY hKey = NULL;
	DWORD dwCiphertextLen = 0;
	HCRYPTHASH hHash = NULL;

	if ( NULL == g_hCryptKey || NULL == g_hCryptKey ) {
		return bRet; 
	}

	bRet = CryptCreateHash( g_hCryptKey, CALG_AES_256, NULL, 0, &hHash );
	if ( !bRet ) {
		return bRet; 
	}

	bRet = CryptEncrypt( g_hCryptKey, hHash, TRUE, 0, pData, &dwCiphertextLen, dwDataLen );
	dwDataLen = dwCiphertextLen;
	CryptDestroyHash( hHash );

	return bRet;
}

BOOL WINAPI DecryptData( PBYTE pData, IN OUT DWORD& dwDataLen )
{
	BOOL bRet = FALSE;
	HCRYPTKEY hKey = NULL;
	HCRYPTHASH hHash = NULL;

	if ( NULL == g_hCryptKey || NULL == g_hCryptKey ) {
		return bRet; 
	}

	bRet = CryptCreateHash( g_hCryptKey, CALG_AES_256, NULL, 0, &hHash );
	if ( !bRet ) {
		return bRet; 
	}

	bRet = CryptDecrypt( g_hCryptKey, hHash, TRUE, 0, pData, &dwDataLen );
	CryptDestroyHash( hHash );

	return bRet;
}

BOOL SaveKey( PBYTE pData, DWORD dwDataLen ) 
{
	BOOL bRet = FALSE;
	if ( NULL == pData ) {
		return bRet;
	}

	HANDLE hFile = CreateFile( KEY_FILE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 
	if ( INVALID_HANDLE_VALUE == hFile ) {
		return bRet;
	}

	bRet = WriteFile( hFile, pData, dwDataLen, NULL, NULL );
	bRet = CloseHandle( hFile );

	return bRet;
}

BOOL RetrieveKey( PBYTE pData, IN OUT DWORD& dwDataLen ) 
{
	BOOL bRet = FALSE;

	HANDLE hFile = CreateFile( KEY_FILE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 
	if ( INVALID_HANDLE_VALUE == hFile ) {
		return bRet;
	}

	if ( NULL == pData ) {
		dwDataLen = GetFileSize( hFile, NULL );
		bRet = CloseHandle( hFile );
		bRet = TRUE;
		return bRet;
	}

	bRet = ReadFile( hFile, pData, dwDataLen, NULL, NULL );
	bRet = CloseHandle( hFile );

	return bRet;
}

BOOL WINAPI ExportKey( )
{
	BOOL bRet = FALSE;
	DWORD dwBlobLen = 0;
	HCRYPTKEY hExpKey = NULL;
	PBYTE pData = NULL;

	if ( NULL == g_hCryptProv ) {
		return bRet;
	}

	if ( NULL != g_hCryptKey ) {
		bRet =  CryptDestroyKey ( g_hCryptKey );
		if ( bRet ) {
			g_hCryptKey = NULL;
		} else {
			return bRet;
		}
	}

	bRet = CryptGenKey( g_hCryptProv, CALG_RC4, CRYPT_EXPORTABLE, &g_hCryptKey );  

	if ( !bRet ) {
		return bRet;
	}

	bRet = CryptDuplicateKey( g_hCryptKey, NULL, 0, &hExpKey );
	if ( !bRet ) {
		return bRet; 
	}

	bRet = CryptExportKey( g_hCryptKey, NULL, SIMPLEBLOB, 0, NULL, &dwBlobLen );
	DWORD dwError = GetLastError( );
	if ( 0 == dwBlobLen && NTE_BAD_KEY == dwError ) {
		bRet = CryptDestroyKey( hExpKey );
		return bRet;
	}

	pData = new BYTE[ dwBlobLen ];
	bRet = CryptExportKey( g_hCryptKey, hExpKey, PRIVATEKEYBLOB, 0, pData, &dwBlobLen);
	if ( bRet ) {
		bRet = SaveKey( pData, dwBlobLen );
	}

	delete [] pData;
	pData = NULL;

	bRet = CryptDestroyKey( hExpKey );

	return bRet;
}

BOOL WINAPI ImportKey( )
{
	BOOL bRet = FALSE;

	if ( NULL == g_hCryptProv ) {
		return bRet;
	}

	DWORD dwDataLen = 0;
	bRet = RetrieveKey( NULL, dwDataLen );
	if ( !bRet ) {
		return bRet;
	}

	if ( NULL != g_hCryptKey ) {
		bRet =  CryptDestroyKey ( g_hCryptKey );
		if ( bRet ) {
			g_hCryptKey = NULL;
		} else {
			return bRet;
		}
	}

	PBYTE pData = new BYTE[ dwDataLen ];
	bRet = CryptImportKey( g_hCryptProv, pData, dwDataLen, 0, 0, &g_hCryptKey );
	delete [ ] pData;
	pData = NULL;

	return bRet;
}