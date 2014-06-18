// CryptComDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CryptComDLL.h"
//#include "CryptoAPI_i.c"
//#include "CryptoAPI.h"
//#include <comutil.h>

#import "CryptoAPI.tlb"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define	THROW_HRESULT(hr)				throw hr
#define	CHECK_HR( hr )					( ( SUCCEEDED( hr ) ) ? 0 : THROW_HRESULT( hr ) )
#define CSP_KEYCONTAINER_NAME           L"PMS_KEY_CONTAINER"


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

BOOL WINAPI DoCrypto( CryptoType type, LPCWSTR lpszSrcFile, LPCWSTR lpszDesFile )
{
	BOOL bRet = FALSE;
	HRESULT hr = S_FALSE;

	if ( NULL == lpszSrcFile ) {
		return bRet;
	}

	CRYPTOAPILib::ICryptoPtr crypt;
	crypt.CreateInstance( __uuidof ( CRYPTOAPILib::Crypto ) );
	CComBSTR bstrSrc( lpszSrcFile );
	_variant_t varDest( lpszDesFile );

	if ( NULL == lpszDesFile ) {
		varDest = vtMissing;
	}

	switch ( type ) {
	case FileEncrypt :
		hr = crypt->EncryptDoc( bstrSrc.m_str, varDest );
		break;

	case FileDecrypt :
		hr = crypt->DecryptDoc( bstrSrc.m_str, varDest );
		break;
	}

	bRet = SUCCEEDED( hr );

	return bRet;
}
