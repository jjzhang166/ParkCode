#ifndef __COMMON_H_
#define __COMMON_H_

////////////////////////////////////////////////////////////////////////////////
//
//	Title:		Common Definitions
//	File:		Common.h
//	Author:		Chad Slater
//	Date:		February 2001
//
//	Abstract:	Header file that contains common macros and definitions
//				for helper functions.
//
//
//
//
//	Revision History:
//	---------------------------------------------------------------------
//	cslater		02/13/2001	Initial revision
//
//
///////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////
	//	Function parameter qualifiers
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef INOUT
#define INOUT
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif



	///////////////////////////////////////////////////////////////////////////
	//	Constant defines
#define	MAX_STRINGTBL					256
#define	MAX_MSG							256
#define	MAX_FILEEXT						3

	
#ifdef _DEBUG
#define	THROW_HRESULT(hr)				(DumpException(__FILE__, __LINE__, hr))
#else
#define	THROW_HRESULT(hr)				throw hr
#endif

#define	CHECK_HR(hr)					((SUCCEEDED(hr))?0:THROW_HRESULT(hr))
#define	USES_CHECKHR_MSG(I_ID)			int nStringID=IDS_UNKNOWN_ERROR; const IID iID = I_ID
#define	CHECKHR_MSG(hr,msgID)			((SUCCEEDED(hr))?0:(nStringID=msgID, THROW_HRESULT(hr)))

#define	CATCH_FAILED_HR(_hr)			{\
											{\
											TCHAR	szMessage[ MAX_MSG ] = { 0 }; \
											if(::LoadString( _Module.GetResourceInstance(),\
															 nStringID,\
															 szMessage,\
															 MAX_MSG ) ) \
												{\
												hr = Error( szMessage, iID, _hr ); \
												lstrcat( szMessage, _T("\n") ); \
												::OutputDebugString( szMessage ); \
												}\
											 else\
												hr = _hr;\
											}\
										}


#define	SAFE_MALLOC_FREE(lpData)		{\
										if(lpData)\
											{\
											free(lpData);\
											lpData = NULL;\
											}\
										}


#define	PARAM_IS_MISSING(variant)		(((variant.vt==VT_ERROR)&&(variant.ulVal==DISP_E_PARAMNOTFOUND)))


	/////////////////////////////////////////////////////////////////////////////////////
	//	GENERAL METHODS	
#ifdef _DEBUG
inline void
DumpException( LPCSTR		strFileName, 
			   const int	nLineNumber,
			   HRESULT		hr				)
	{
	TCHAR szMsg[ MAX_MSG ] = {0};
	TCHAR szSystemMsg[ MAX_MSG ] = {0};

	if( FormatMessage(	FORMAT_MESSAGE_FROM_SYSTEM, 
						NULL, 
						hr, 
						0, 
						szSystemMsg, 
						MAX_MSG, NULL ) )
		wsprintf( szMsg, _T("Fatal Exception - File: %s Line: %d System Message: %s"), strFileName, nLineNumber, szSystemMsg );
	else
		wsprintf( szMsg, _T("Fatal Exception - File: %s Line: %d"), strFileName, nLineNumber );
		
	::OutputDebugString( szMsg );
	throw hr;
	}
#endif
	

#endif 
	//__COMMON_H_
