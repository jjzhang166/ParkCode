// LPKernelEx.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MyLPKernelEx.h"

extern HMODULE g_hPlateRaw;

//
//	Get a function pointer from [LPKernelExRaw.dll]
//
static PVOID GetFunctionPointer( LPCSTR pszFName )
{
	PVOID pFN = NULL;

	if ( NULL != g_hPlateRaw && NULL != pszFName ) {
		pFN = ::GetProcAddress( g_hPlateRaw, pszFName );
	}

	return pFN;
}

//
// Comfirm validation for a channel number
//
static BOOL ValidateChannel( const int nChannel )
{
	BOOL bRet = ( 1 <= nChannel && PLATE_WAY_COUNT >= nChannel );

	return bRet;
}

LPKERNELEX_API BOOL WINAPI LPR_SetParameters( BOOL bMovingImage,
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
																				int nChannel )
{
	#pragma EXPORT

	BOOL bRet = ValidateChannel( nChannel );

	if ( !bRet ) {
		return FALSE;
	}

	static PLPR_SetParameters pFN = ( PLPR_SetParameters ) GetFunctionPointer( "LPR_SetParameters" );

	if ( NULL == pFN ) {
		return FALSE;
	}

	nChannel = 1;
	bRet = pFN( bMovingImage,
						nPlatesNum,
						bFlipVertical, 
						nColorOrder,
						bVertCompress,
						nImageplateThr, nImageRecogThr, 
						nMinPlateWidth, nMaxPlateWidth, 
						LocalProvince,
						bDwordAligned,
						bInputHalfHeightImage,    												   
						bOutputSingleFrame,
						bYellow2, bIndivi, bArmPol, bArmy2, bTractor, 
						bNight, 	
						nChannel );

	return bRet;
}

LPKERNELEX_API BOOL WINAPI LPR_SetImageFormat(BOOL bMovingImage,		
		BOOL bFlipVertical, 
		int nColorOrder,
		BOOL bVertCompress, 
		int nMinPlateWidth, 
		int nMaxPlateWidth, 
		BOOL bDwordAligned,
		BOOL bInputHalfHeightImage,    												   
		BOOL bOutputSingleFrame,	
		int nChannel )
{
	#pragma EXPORT

	BOOL bRet = ValidateChannel( nChannel );

	if ( !bRet ) {
		return FALSE;
	}

	static PLPR_SetImageFormat pFN = ( PLPR_SetImageFormat ) GetFunctionPointer( "LPR_SetImageFormat" );

	if ( NULL == pFN ) {
		return FALSE;
	}

	nChannel = 1;
	bRet = pFN( bMovingImage,		
						bFlipVertical, 
						nColorOrder,
						bVertCompress, 
						nMinPlateWidth, 
						nMaxPlateWidth, 
						bDwordAligned,
						bInputHalfHeightImage,    												   
						bOutputSingleFrame,	
						nChannel );

	return bRet;
}

LPKERNELEX_API BOOL WINAPI LPR_SetPlateType(BOOL bYellow2, 
		BOOL bIndivi,
		BOOL bArmPol, 
		BOOL bArmy2,
		BOOL bTractor,
		BOOL bOnlyDyellow,
		BOOL bEmbassy,
		BOOL bDarmpolice,
		BOOL bOnlyLocation,
		int  nChannel )
{
	#pragma EXPORT

	BOOL bRet = ValidateChannel( nChannel );

	if ( !bRet ) {
		return FALSE;
	}

	static PLPR_SetPlateType pFN = ( PLPR_SetPlateType ) GetFunctionPointer( "LPR_SetPlateType" );

	if ( NULL == pFN ) {
		return FALSE;
	}

	nChannel = 1;
	bRet = pFN( bYellow2, 
						bIndivi,
						bArmPol, 
						bArmy2,
						bTractor,
						bOnlyDyellow,
						bEmbassy,
						bDarmpolice,
						bOnlyLocation,
						nChannel );

	return bRet;
}

LPKERNELEX_API BOOL WINAPI LPR_SetSpecialParameters(BOOL bNight,		
		int nImageplateThr, 
		int nImageRecogThr,
		int nPlatesNum,
		char *LocalProvince,
		int nChannel)
{
	#pragma EXPORT

	BOOL bRet = ValidateChannel( nChannel );

	if ( !bRet ) {
		return FALSE;
	}

	static PLPR_SetSpecialParameters pFN = ( PLPR_SetSpecialParameters ) GetFunctionPointer( "LPR_SetSpecialParameters" );

	if ( NULL == pFN ) {
		return FALSE;
	}

	nChannel = 1;
	bRet = pFN( bNight,		
						nImageplateThr, 
						nImageRecogThr,
						nPlatesNum,
						LocalProvince,
						nChannel );

	return bRet;
}
	
LPKERNELEX_API BOOL WINAPI LPR_InitEx( int  nChannel )
{
	#pragma EXPORT

	BOOL bRet = ValidateChannel( nChannel );

	if ( !bRet ) {
		return FALSE;
	}

	static PLPR_InitEx pFN = ( PLPR_InitEx ) GetFunctionPointer( "LPR_InitEx" );

	if ( NULL == pFN ) {
		return FALSE;
	}

	static BOOL bInitialize = FALSE;

	if ( !bInitialize ) {
		bInitialize = TRUE;
		nChannel = 1;
		bRet = pFN( nChannel );
	} else {
		bRet = TRUE;
	}

	return bRet;
}
	
LPKERNELEX_API void WINAPI LPR_UninitEx( int  nChannel )
{
	#pragma EXPORT

	BOOL bRet = ValidateChannel( nChannel );

	if ( !bRet ) {
		return;
	}

	static PLPR_UninitEx pFN = ( PLPR_UninitEx ) GetFunctionPointer( "LPR_UninitEx" );

	if ( NULL == pFN ) {
		return;
	}

	static BOOL bUninitialize = FALSE;

	if ( !bUninitialize ) {
		bUninitialize = TRUE;
		nChannel = 1;
		pFN( nChannel );
	}
}

LPKERNELEX_API BOOL WINAPI LPR_RGB888Ex(unsigned char *pImg, int nWidth, int  nHeight, TH_PlateResult* pResult, int &nRecogNum, TH_RECT *prcRange, int  nChannel)
{
	#pragma EXPORT

	//return FALSE; // Not supprot video stream

	BOOL bRet = ValidateChannel( nChannel );

	if ( !bRet ) {
		return FALSE;
	}

	static PLPR_RGB888Ex pFN = ( PLPR_RGB888Ex ) GetFunctionPointer( "LPR_RGB888Ex" );

	if ( NULL == pFN ) {
		return FALSE;
	}

	bRet = pFN( pImg, nWidth, nHeight, pResult, nRecogNum, prcRange, nChannel );

	return bRet;
}

LPKERNELEX_API BOOL WINAPI LPR_GetImageBuf(unsigned char *&pImageBuf, int &nWidth, int &nHeight, int &nSize, int  nChannel)
{
	#pragma EXPORT

	BOOL bRet = ValidateChannel( nChannel );

	if ( !bRet ) {
		return FALSE;
	}

	static PLPR_GetImageBuf pFN = ( PLPR_GetImageBuf ) GetFunctionPointer( "LPR_GetImageBuf" );

	if ( NULL == pFN ) {
		return FALSE;
	}

	nChannel = 1;
	bRet = pFN( pImageBuf, nWidth, nHeight, nSize, nChannel );

	return bRet;
}

LPKERNELEX_API BOOL WINAPI LPR_FileEx( char* lpszFileName, char *lpszPlateFile, TH_PlateResult* pResult, int &nRecogNum, TH_RECT *prcRange, int nChannel )
{
	#pragma EXPORT

	BOOL bRet = ValidateChannel( nChannel );

	if ( !bRet ) {
		return FALSE;
	}

	static PLPR_FileEx pFN = ( PLPR_FileEx ) GetFunctionPointer( "LPR_FileEx" );

	if ( NULL == pFN ) {
		return FALSE;
	}

	nChannel = 1;
	bRet = pFN( lpszFileName, lpszPlateFile, pResult, nRecogNum, prcRange, nChannel );

	return bRet;
}