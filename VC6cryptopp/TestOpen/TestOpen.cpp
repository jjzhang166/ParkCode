// TestOpen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include "../OpenSoucreCrypt/OpenSoucreCrypt.h"

int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	BYTE bData[ ] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', '\0' };
	char cErrorMsg[ 512 ] = { 0 };
	BOOL bRet = OpenSourceCrypt( bData, 24, TRUE, cErrorMsg );
	printf( "Enc:%s\n", ( char* ) bData ); 
	bRet = OpenSourceCrypt( bData, 24, FALSE, cErrorMsg );
	printf( "Dec:%s\n", ( char* ) bData ); 
	getchar( );
	return 0;
}

