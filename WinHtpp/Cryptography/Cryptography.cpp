// Cryptography.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../CryptDll/CryptDll.h"

#ifdef _DEBUG
#pragma comment( lib, "../Debug/CryptDll.lib" )
#else
#pragma comment( lib, "../Release/CryptDll.lib" )
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bRet = CryptStartup( );
	bRet = ExportKey( );
	bRet = CryptCleanup( );
	return 0;
}

