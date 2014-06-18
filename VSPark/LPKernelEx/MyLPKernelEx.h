// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LPKERNELEX_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LPKERNELEX_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LPKERNELEX_EXPORTS
#define LPKERNELEX_API __declspec(dllexport)
#else
#define LPKERNELEX_API __declspec(dllimport)
#endif

#if _MSC_VER > 1200 // Later than Visual Studio 6.0
#define EXPORT comment(linker, "/EXPORT:"__FUNCTION__"="__FUNCDNAME__)
#else // Cannot use this way of exporting functions.
#define EXPORT
#endif // else need to use DEF file or __declspec(dllexport)

#include "..\include\LPKernelEx.h"

#define PLATE_WAY_COUNT		( int ) 2

typedef BOOL ( WINAPI *PLPR_SetParameters  )  (BOOL bMovingImage,
		int nPlatesNum,
		BOOL bFlipVertical, 
		int nColorOrder,
		BOOL bVertCompress,
		int nImageplateThr, int nImageRecogThr, 
		int nMinPlateWidth, int nMaxPlateWidth, 
		char *LocalProvince,
		BOOL bDwordAligned,
		BOOL bInputHalfHeightImage,    												   
		BOOL bOutputSingleFrame,
		BOOL bYellow2, BOOL bIndivi, BOOL bArmPol, BOOL bArmy2, BOOL bTractor, 
		BOOL bNight, 	
		int nChannel );

typedef BOOL ( WINAPI * PLPR_SetImageFormat ) (BOOL bMovingImage,		
		BOOL bFlipVertical, 
		int nColorOrder,
		BOOL bVertCompress, 
		int nMinPlateWidth, 
		int nMaxPlateWidth, 
		BOOL bDwordAligned,
		BOOL bInputHalfHeightImage,    												   
		BOOL bOutputSingleFrame,	
		int nChannel );

typedef BOOL ( WINAPI * PLPR_SetPlateType ) (BOOL bYellow2, 
		BOOL bIndivi,
		BOOL bArmPol, 
		BOOL bArmy2,
		BOOL bTractor,
		BOOL bOnlyDyellow,
		BOOL bEmbassy,
		BOOL bDarmpolice,
		BOOL bOnlyLocation,
		int  nChannel );

typedef BOOL ( WINAPI * PLPR_SetSpecialParameters ) (BOOL bNight,		
		int nImageplateThr, 
		int nImageRecogThr,
		int nPlatesNum,
		char *LocalProvince,
		int nChannel);

typedef BOOL ( WINAPI * PLPR_InitEx ) (int  nChannel);

typedef void ( WINAPI * PLPR_UninitEx ) (int  nChannel);

typedef BOOL ( WINAPI * PLPR_RGB888Ex ) (unsigned char *pImg, int nWidth, int  nHeight, TH_PlateResult* pResult, int &nRecogNum, TH_RECT *prcRange, int  nChannel);

typedef BOOL ( WINAPI * PLPR_GetImageBuf ) (unsigned char *&pImageBuf, int &nWidth, int &nHeight, int &nSize, int  nChannel);

typedef BOOL ( WINAPI * PLPR_FileEx ) (char* lpszFileName, char *lpszPlateFile, TH_PlateResult* pResult, int &nRecogNum, TH_RECT *prcRange,int nChannel);
