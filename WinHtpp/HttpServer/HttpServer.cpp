// HttpServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

#include "../HttpServerDll/HttpServerDll.h"
#ifdef _DEBUG
#pragma comment( lib, "../Debug/HttpServerDll.lib" )
#else
#pragma comment( lib, "../Release/HttpServerDll.lib" )
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bRet = StartupHttp( );
	if ( bRet ) {
		printf( "%s\r\n", "StartupHttp  success." );
	}
	//WCHAR* pUrl = L"http://127.0.0.1:80/Test" ;
	WCHAR* pUrl = L"http://192.168.1.25:80/" ;
	bRet = AddListenUrl( pUrl );
	if ( bRet ) {
		printf( "%s\r\n", "AddListenUrl  success." );
	}

	HANDLE hHeap = GetProcessHeap( );
	ULONG lSize = 170140;
	
	LPVOID pEntity[ 1  ];
	pEntity[ 0 ] = HeapAlloc( hHeap, HEAP_ZERO_MEMORY, lSize );
	ULONG lEntityLen[  1 ];
	lEntityLen[ 0 ] = lSize;
	USHORT sEntityCount = 1;

	HANDLE hFile = CreateFile( L"d:\\testhttp.html", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( INVALID_HANDLE_VALUE != hFile ) {
		printf( "%s\r\n", "CreateFile  success." );
	}

	DWORD dwRead = 0;
	bRet = ReadFile( hFile, pEntity[ 0 ], lSize, &dwRead, NULL );
	if ( bRet ) {
		printf( "%s\r\n", "ReadFile  success." );
	}

	bRet = CloseHandle( hFile );
	if ( bRet ) {
		printf( "%s\r\n", "CloseHandle  success." );
	}

	DWORD dwError = 0;
	HANDLE hRequest = NULL;
	HTTP_VERB httpVerb = HttpVerbMaximum;
	
	while ( true ) {
		hRequest = RetrieveRequest( httpVerb );
		if  ( NULL != hRequest ) {
			printf( "%s\r\n", "RetrieveRequest  success." );
		}

		bRet = SendHttpResponse( hRequest, 200, "OK",  pEntity, lEntityLen, sEntityCount );
		if ( bRet ) {
			printf( "%s\r\n", "SendHttpResponse  success." );
		}  

		bRet = ReleaseRequestHandle( hRequest );
		if ( bRet ) {
			printf( "%s\r\n", "ReleaseRequestHandle  success." );
		}
	}

	bRet = HeapFree( hHeap, 0, pEntity[ 0 ] );
	if ( bRet ) {
		printf( "%s\r\n", "HeapFree  success." );
	}

	bRet = AddDelistenUrl( pUrl );
	if ( bRet ) {
		printf( "%s\r\n", "AddDelistenUrl  success." );
	}

	bRet = CleanupHttp( );
	if ( bRet ) {
		printf( "%s\r\n", "CleanupHttp  success." );
	}

	getchar( );
	return 0;
}

