// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CRYPTCOMDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CRYPTCOMDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CRYPTCOMDLL_EXPORTS
#define CRYPTCOMDLL_API __declspec(dllexport)
#else
#define CRYPTCOMDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
#define CAPI_STYLE extern "C"
#else
#define CAPI_STYLE
#endif

#include <windows.h>

typedef enum __CryptoType {
	FileEncrypt,
	//EncryptString,
	FileDecrypt,
	//DecryptString,
} CryptoType;

CAPI_STYLE CRYPTCOMDLL_API BOOL WINAPI DoCrypto( CryptoType type, LPCWSTR lpszSrcFile, LPCWSTR lpszDesFile );