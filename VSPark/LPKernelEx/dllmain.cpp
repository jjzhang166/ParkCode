// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

HMODULE g_hPlateRaw = NULL;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hPlateRaw = LoadLibrary( TEXT( "LPKernelExRaw.dll" ) );
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		if ( NULL != g_hPlateRaw ) {
			FreeLibrary( g_hPlateRaw );
		}
		break;
	}
	return TRUE;
}

