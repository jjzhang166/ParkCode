
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the OPENSOUCRECRYPT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// OPENSOUCRECRYPT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef OPENSOUCRECRYPT_EXPORTS
#define OPENSOUCRECRYPT_API __declspec(dllexport)
#else
#define OPENSOUCRECRYPT_API __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
#endif
OPENSOUCRECRYPT_API BOOL OpenSourceCrypt( LPBYTE pData, const int nDataLen, BOOL bEncrypt, char* pErrorMsg  );

