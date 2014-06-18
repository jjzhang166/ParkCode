// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CRYPTDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CRYPTDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CRYPTDLL_EXPORTS
#define CRYPTDLL_API __declspec(dllexport)
#else
#define CRYPTDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
#define CAPI_STYLE extern "C"
#elif
#define CAPI_STYLE
#endif

#include <windows.h>
#include <Wincrypt.h>

CAPI_STYLE CRYPTDLL_API BOOL WINAPI EncryptData( );
CAPI_STYLE CRYPTDLL_API BOOL WINAPI DecryptData( );
CAPI_STYLE CRYPTDLL_API BOOL WINAPI ExportKey( );
CAPI_STYLE CRYPTDLL_API BOOL WINAPI ImportKey( );
CAPI_STYLE CRYPTDLL_API BOOL WINAPI CryptStartup( );
CAPI_STYLE CRYPTDLL_API BOOL WINAPI CryptCleanup( );