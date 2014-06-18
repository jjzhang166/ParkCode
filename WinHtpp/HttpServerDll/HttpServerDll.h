// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HTTPSERVERDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HTTPSERVERDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef __cplusplus
#define CAPI_STYLE extern "C"
#elif
#define CAPI_STYLE
#endif

#ifdef HTTPSERVERDLL_EXPORTS
#define HTTPSERVERDLL_API  __declspec(dllexport)
#else
#define HTTPSERVERDLL_API __declspec(dllimport)
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma comment(lib, "httpapi.lib")

#include "windows.h"
#include "http.h"

//
// Macros.
//
#define INITIALIZE_HTTP_RESPONSE( resp, status, reason )    \
    do                                                      \
    {                                                       \
        RtlZeroMemory( (resp), sizeof(*(resp)) );           \
        (resp)->StatusCode = (status);                      \
        (resp)->pReason = (reason);                         \
        (resp)->ReasonLength = (USHORT) strlen(reason);     \
    } while (FALSE)

#define ADD_KNOWN_HEADER(Response, HeaderId, RawValue)               \
    do                                                               \
    {                                                                \
        (Response).Headers.KnownHeaders[(HeaderId)].pRawValue =      \
                                                          (RawValue);\
        (Response).Headers.KnownHeaders[(HeaderId)].RawValueLength = \
            (USHORT) strlen(RawValue);                               \
    } while(FALSE)

#define ALLOC_MEM( cb ) HeapAlloc( GetProcessHeap( ), 0, ( cb ) )

#define FREE_MEM( ptr ) HeapFree( GetProcessHeap( ), 0, ( ptr ) )

//
// Export Function
//

CAPI_STYLE HTTPSERVERDLL_API WCHAR* WINAPI GetErrorMessage( );

CAPI_STYLE HTTPSERVERDLL_API BOOL WINAPI StartupHttp( );
CAPI_STYLE HTTPSERVERDLL_API BOOL WINAPI CleanupHttp( );

CAPI_STYLE HTTPSERVERDLL_API BOOL WINAPI AddListenUrl( LPCWSTR pszUrl );
CAPI_STYLE HTTPSERVERDLL_API BOOL WINAPI AddDelistenUrl( LPCWSTR pszUrl );

CAPI_STYLE HTTPSERVERDLL_API HANDLE WINAPI RetrieveRequest( HTTP_VERB& httpMethod ); // Get request handle, NULL failed
CAPI_STYLE HTTPSERVERDLL_API BOOL WINAPI ReleaseRequestHandle( HANDLE hRequest );

CAPI_STYLE HTTPSERVERDLL_API BOOL WINAPI SendHttpResponse( HANDLE hRequest, USHORT StatusCode, PCSTR pReason, LPVOID pEntity[ ], ULONG lEntityLen[ ], USHORT sEntityCount );