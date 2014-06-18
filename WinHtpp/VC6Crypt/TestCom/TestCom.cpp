// TestCom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestCom.h"

#include <comutil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#import "../CryptoAPI.tlb"

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

typedef enum __CryptoType {
	FileEncrypt,
	//EncryptString,
	FileDecrypt,
	//DecryptString,
} CryptoType;

BOOL WINAPI DoCrypto( CryptoType type, LPCWSTR lpszSrcFile, LPCWSTR lpszDesFile )
{
	BOOL bRet = FALSE;
	HRESULT hr = S_FALSE;

	if ( NULL == lpszSrcFile ) {
		return bRet;
	}

	CRYPTOAPILib::ICryptoPtr crypt;
	crypt.CreateInstance( __uuidof ( CRYPTOAPILib::Crypto ) );
	_bstr_t bstrSrc( lpszSrcFile );
	_variant_t varDest( lpszDesFile );

	if ( NULL == lpszDesFile ) {
		varDest = vtMissing;
	}

	switch ( type ) {
	case FileEncrypt :
		hr = crypt->EncryptDoc( bstrSrc, varDest );
		break;

	case FileDecrypt :
		hr = crypt->DecryptDoc( bstrSrc, varDest );
		break;
	}

	bRet = SUCCEEDED( hr );

	return bRet;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;
	}

	HRESULT hr = ::CoInitialize( NULL );
	//FileEncrypt     FileDecrypt
	DoCrypto( FileDecrypt, L"d:\\a.txt", NULL );
	CoUninitialize( );

	return nRetCode;
}


