////////////////////////////////////////////////////////////////////////////////
//
//	Title:		CryptoAPI Implementation
//	File:		CryptoAPI.cpp
//	Author:		Chad Slater
//	Date:		March 2001
//
//	Abstract:	DLL Main for the in-proc server
//
//
//
//
//	Revision History:
//	---------------------------------------------------------------------
//	cslater		3/15/2001 8:26:44 AM	Initial revision
//
//
//
////////////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "CryptoAPI.h"

#include "CryptoAPI_i.c"
#include "Crypto.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY( CLSID_Crypto, CCrypto )
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI 
DllMain( HINSTANCE	hInstance, 
		 DWORD		dwReason, 
		 LPVOID		lpReserved	)
	{
    if( dwReason == DLL_PROCESS_ATTACH )
		{
        _Module.Init( ObjectMap, hInstance, &LIBID_CRYPTOAPILib );
        DisableThreadLibraryCalls( hInstance );
		}

    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    
	return TRUE;    
	}


STDAPI 
DllCanUnloadNow()
	{
    return ( _Module.GetLockCount() == 0 ) ? S_OK : S_FALSE;
	}


STDAPI 
DllGetClassObject(	REFCLSID	rclsid, 
					REFIID		riid, 
					LPVOID*		ppv		)
	{
    return _Module.GetClassObject(	rclsid, riid, ppv	);
	}


STDAPI 
DllRegisterServer()
	{
    return _Module.RegisterServer( TRUE );
	}


STDAPI 
DllUnregisterServer()
	{
    return _Module.UnregisterServer( TRUE );
	}


