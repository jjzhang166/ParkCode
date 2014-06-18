// OpenSoucreCrypt.cpp : Defines the entry point for the DLL application.
//
#ifndef CRYPTOPP_DLL_ONLY
#define CRYPTOPP_DEFAULT_NO_DLL
#endif

#include "stdafx.h"
#include "../dll.h"

#include "OpenSoucreCrypt.h"

USING_NAMESPACE(CryptoPP)
USING_NAMESPACE(std)

#ifdef CRYPTOPP_IMPORTS

static PNew s_pNew = NULL;
static PDelete s_pDelete = NULL;

extern "C" __declspec(dllexport) void __cdecl SetNewAndDeleteFromCryptoPP(PNew pNew, PDelete pDelete, PSetNewHandler pSetNewHandler)
{
	s_pNew = pNew;
	s_pDelete = pDelete;
}

void * __cdecl operator new (size_t size)
{
	return s_pNew(size);
}

void __cdecl operator delete (void * p)
{
	s_pDelete(p);
}

#endif

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

BOOL OpenSourceCrypt( LPBYTE pData, const int nDataLen, BOOL bEncrypt, char* pErrorMsg )
{
	BOOL bRet = FALSE;

	if ( NULL == pErrorMsg ) {
		return bRet;
	}

	if ( NULL == pData || 0 >= nDataLen ) {
		strcpy( pErrorMsg, "NULL == pData || 0 >= nDataLen" );
		return bRet;
	}

	if ( !FIPS_140_2_ComplianceEnabled( ) ) {
		strcpy( pErrorMsg, "!FIPS_140_2_ComplianceEnabled( )" );
		return bRet;
	}

	if ( GetPowerUpSelfTestStatus( ) != POWER_UP_SELF_TEST_PASSED ) {
		strcpy( pErrorMsg, "GetPowerUpSelfTestStatus( ) != POWER_UP_SELF_TEST_PASSED" );
		return bRet;
	}

	SimulatePowerUpSelfTestFailure( );

	try {
		AES::Encryption aes;
		strcpy( pErrorMsg, "AES::Encryption aes;" );
		return bRet;
	}
	catch ( SelfTestFailure &e ) {
		OutputDebugString( e.what( ) );
	}

	DoDllPowerUpSelfTest();

	if ( GetPowerUpSelfTestStatus( ) != POWER_UP_SELF_TEST_PASSED ) {
		strcpy( pErrorMsg, "GetPowerUpSelfTestStatus( ) != POWER_UP_SELF_TEST_PASSED" );
		return bRet;
	}

	// encrypt and decrypt
	const BYTE bKey[ ] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
		                   0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 
					       0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

	const BYTE iv[] = { 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef };

	LPBYTE decrypted = new BYTE[ nDataLen ];

	if ( bEncrypt ) {
		CFB_FIPS_Mode< DES_EDE3 >::Encryption encryption_DES_EDE3_CFB;
		encryption_DES_EDE3_CFB.SetKeyWithIV( bKey, sizeof( bKey ), iv );
		encryption_DES_EDE3_CFB.ProcessString( decrypted, pData, nDataLen );
	} else {
		CFB_FIPS_Mode<DES_EDE3>::Decryption decryption_DES_EDE3_CFB;
		decryption_DES_EDE3_CFB.SetKeyWithIV( bKey, sizeof( bKey ), iv );
		decryption_DES_EDE3_CFB.ProcessString( decrypted, pData, nDataLen );
	}

	bRet = ( memcmp( pData, decrypted, nDataLen ) != 0 );
	if ( bRet ) {
		memcpy( pData, decrypted, nDataLen );
	}

	if ( NULL != decrypted ) {
		delete [ ] decrypted;
		decrypted = NULL;
	}

	return bRet;
}
