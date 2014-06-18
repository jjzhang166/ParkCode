////////////////////////////////////////////////////////////////////////////////
//
//	Title:		Crypto Shell Extension Object
//	File:		CryptoShellExt.cpp
//	Author:		Chad Slater
//	Date:		March 2001
//
//	Abstract:	This shell extension object provides a context menu item
//				for encrypting and decrypting files in windows explorer
//				using the Win32 Crypto API.
//
//
//
//
//	Revision History:
//	---------------------------------------------------------------------
//	cslater		03/15/2001	Initial revision
//	cslater		03/16/2001	Fixed context menu item defect 
//	cslater		03/17/2001	Added two additional menu items for selecting
//							the destination folder for encrypting/decrypting
//	cslater		03/18/2001	Added a hook procedure to enable/disable the OK
//							button in the browse for folder dialog based on
//							whether the destination is writable
//
//
//
////////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Common.h"
#include "CryptoAPI.h"

#include <io.h>


#define	CSP_KEYCONTAINER_NAME	L"CRYPTO_CONTEXTMENU_SHELLEXT_1_0_0"
#define	MENU_ITEMS_ADDED		5
#define	DOUBLE_ENCRYPT_FILENAME	_T("~TMP_ICRYPTO.CRP")


static BOOL 
BrowseFolder( LPTSTR	lptstrSelectedFolder );
	//	Displays the browse for folder dialog for the user to select the 
	//	destination folder for the encrypted/decrypted files


static int CALLBACK
BrowseFolderProc( HWND		hWnd,
				  UINT		nMsg,
				  LPARAM	lParam,
				  LPARAM	dwData		);
	//	Hook procedure for the browse for folder dialog
	//
	//	Used for enabling/disabling the OK button based on whether the 
	//	destination is writable


static BOOL
BuildDestinationPathFromSrc( IN		const CComBSTR	bstrSource, 
							 INOUT		  CComBSTR& bstrDestination );
	//	Constructs a destination path by combining the source filename
	//	with the destination path
	//
	//	Returns whether the operation was successful


static _variant_t
GetDblCryptTempFilename();
	//	Returns the temporary filename for decrypting to guard against double encryption


HRESULT CCryptoShellExt::
Initialize ( LPCITEMIDLIST	pidlFolder,
		     LPDATAOBJECT	pDataObj,
			 HKEY			hProgID			)
	{
	FORMATETC fmt		= { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg		= { TYMED_HGLOBAL };
	HDROP     hDrop		=	NULL;
	HRESULT	  hr		=	S_OK;
	UINT	  uNumFiles	=	0;
	HMODULE	  hLib		=	NULL;

	try
		{
			// Look for CF_HDROP data in the data object
		CHECK_HR( pDataObj->GetData( &fmt, &stg ) );
		hDrop = (HDROP) GlobalLock ( stg.hGlobal );
		if( NULL == hDrop )
			THROW_HRESULT( E_INVALIDARG );

			// How many files are selected?
		CleanUp();
		m_nFiles = DragQueryFile ( hDrop, 0xFFFFFFFF, NULL, 0 );
		if( m_nFiles <= 0 )
			THROW_HRESULT( E_INVALIDARG );

			//	Allocate the buffer to hold the paths to the selected files
		m_pbstrFiles = new CComBSTR[ m_nFiles ];
		if( m_pbstrFiles == NULL )
			THROW_HRESULT( E_OUTOFMEMORY );

			//	For each file selected in Explorer, save them in case the user
			//	selects our context menu item
		for( UINT nIndex = 0;
				nIndex < m_nFiles;
					nIndex++ )
			{
			TCHAR	lptstrFile[ MAX_PATH ] = {0};
			if( DragQueryFile ( hDrop, nIndex, lptstrFile, MAX_PATH ) == 0 )
				THROW_HRESULT( E_INVALIDARG );
			m_pbstrFiles[ nIndex ] = lptstrFile;
			}
		}

	catch( HRESULT _hr )
		{
		hr = _hr;
		}

	GlobalUnlock ( stg.hGlobal );
	ReleaseStgMedium ( &stg );	
	return hr;
	}


HRESULT CCryptoShellExt::
QueryContextMenu (	HMENU hMenu,
					UINT  uMenuIndex, 
					UINT  uidFirstCmd,
					UINT  uidLastCmd,
					UINT  uFlags )
	{
	HRESULT hr = S_OK;

	try
		{
			// If the flag is CMF_DEFAULTONLY then don't do anything
		if( uFlags & CMF_DEFAULTONLY )
			throw MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 0 );

			//	Get the menu item out of the string table and insert it
		CHECK_HR( InsertContextMenuItem( hMenu, uMenuIndex, uidFirstCmd, IDC_ENCRYPT_FILE_TO, IDS_ENCRYPT_FILE_TO_MENU_ITEM ) );
		CHECK_HR( InsertContextMenuItem( hMenu, uMenuIndex, uidFirstCmd, IDC_ENCRYPT_FILE,	  IDS_ENCRYPT_MENU_ITEM			) );
		CHECK_HR( InsertContextMenuItem( hMenu, uMenuIndex, uidFirstCmd, IDC_DECRYPT_FILE_TO, IDS_DECRYPT_FILE_TO_MENU_ITEM ) );		
		CHECK_HR( InsertContextMenuItem( hMenu, uMenuIndex, uidFirstCmd, IDC_DECRYPT_FILE,	  IDS_DECRYPT_MENU_ITEM			) );
		
			//	Insert a separator 
		InsertMenu( hMenu, uMenuIndex, MF_BYPOSITION | MF_SEPARATOR, 0, 0 );
		hr = MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, MENU_ITEMS_ADDED );
		}
	catch( HRESULT _hr )
		{
		hr = _hr;
		}

	return hr;
	}


HRESULT CCryptoShellExt::
GetCommandString (	UINT   idCmd,
					UINT   uFlags,
					LPUINT pwReserved,
					LPSTR  pszName,
					UINT   cchMax	)
	{
	USES_CONVERSION;
	int		nStringID	=	0;
	HRESULT	hr			=	S_OK;

		// If Explorer is asking for a help string, copy our string into the
		// supplied buffer
    if( uFlags & GCS_HELPTEXT )
        {
        TCHAR	lptstrBuffer[ MAX_STRINGTBL + 1 ] = {0};

			//	Which menu item is selected?
		switch( idCmd )
			{
			case IDC_ENCRYPT_FILE:
				nStringID = IDS_ENCRYPT_OBJECT_FLYBY_HELP;
				break;

			case IDC_DECRYPT_FILE:
				nStringID = IDS_DECRYPT_OBJECT_FLYBY_HELP;
				break;

			case IDC_ENCRYPT_FILE_TO:
				nStringID = IDS_ENCRYPT_FILE_TO_FLYBY;
				break;

			case IDC_DECRYPT_FILE_TO:
				nStringID = IDS_DECRYPT_FILE_TO_FLYBY;
				break;

			default:
				ATLASSERT( 0 );
				hr =  E_INVALIDARG;
				break;
			}

			//	Load the help string that will appear in the status bar
			//	as a fly-by help string
		if( SUCCEEDED( hr ) &&
			::LoadString( _Module.m_hInst,
						  nStringID,
						  lptstrBuffer,
						  MAX_STRINGTBL ) != 0 )
			{
			if ( uFlags & GCS_UNICODE )
				lstrcpynW ( (LPWSTR) pszName, T2CW(lptstrBuffer), cchMax );
			else
				lstrcpynA ( pszName, T2CA(lptstrBuffer), cchMax );
			}
		}

    return hr;
	}	


HRESULT CCryptoShellExt::
InvokeCommand ( LPCMINVOKECOMMANDINFO pCmdInfo )
	{
	HRESULT	hr = S_OK;

		// If lpVerb points to a string, then ignore this call
    if( HIWORD( pCmdInfo->lpVerb ) != 0 )
        hr = E_INVALIDARG;

	else
		{
		TCHAR	lptstrDestination[ MAX_PATH ] = {0};

			// Carry out the menu selection
		switch( LOWORD( pCmdInfo->lpVerb ) )
			{
			case IDC_ENCRYPT_FILE:
				DoCrypto();			
				break;
			
			case IDC_DECRYPT_FILE:
				DoCrypto( CCryptoShellExt::cryptDecrypt );
				break;

			case IDC_ENCRYPT_FILE_TO:
				if( BrowseFolder( lptstrDestination ) )
					DoCrypto( CCryptoShellExt::cryptEncrypt, lptstrDestination );
				break;

			case IDC_DECRYPT_FILE_TO:
				if( BrowseFolder( lptstrDestination ) )
					DoCrypto( CCryptoShellExt::cryptDecrypt, lptstrDestination );
					break;
			
			default:
				ATLASSERT( 0 );
				hr = E_INVALIDARG;
				break;
			}

			//	The context menu is gone at this point
		CleanUp();
		}
	return hr;
	}


void CCryptoShellExt::
CleanUp()
	{
	if( m_pbstrFiles != NULL )
		{
		delete [] m_pbstrFiles;
		m_pbstrFiles = NULL;
		}
	m_nFiles = 0;
	}


void CCryptoShellExt::
DoCrypto(	CCryptoShellExt::CryptAction Action,
			LPCTSTR						 lpctstrDestination	) const
	{
	_variant_t	vtDestination;

	try
		{
		ATLASSERT( m_nFiles > 0 );
		if( m_nFiles > 0 )
			{
			CComPtr< ICrypto >	pCrypto;

			if( SUCCEEDED( pCrypto.CoCreateInstance( CLSID_Crypto ) ) )
				{
				ATLASSERT( pCrypto != NULL );
				if( !pCrypto )
					THROW_HRESULT( E_FAIL );

					//	Set the key container name
				CHECK_HR( pCrypto->put_ContainerName( CSP_KEYCONTAINER_NAME ) );

					//	For each file selected in Explorer, encrypt/decrypt
				for( UINT nIndex = 0;
						nIndex < m_nFiles;
							nIndex++ )
					{
					CComBSTR	bstrDestination;

						//	If the user specified a destination, set that now
					if( lpctstrDestination )
						{
						bstrDestination = lpctstrDestination;
						BuildDestinationPathFromSrc( m_pbstrFiles[ nIndex ].m_str, bstrDestination );
						}

					ATLASSERT( m_pbstrFiles != NULL );
					ATLASSERT( !::IsBadReadPtr( m_pbstrFiles, sizeof( CComBSTR* ) ) );
					ATLASSERT( !::IsBadReadPtr( m_pbstrFiles[ nIndex ], sizeof( CComBSTR ) ) );
					if( m_pbstrFiles != NULL &&
						!::IsBadReadPtr( m_pbstrFiles,			 sizeof( CComBSTR* ) ) &&
						!::IsBadReadPtr( m_pbstrFiles[ nIndex ], sizeof( CComBSTR  ) ) )
						{
							//	Change to hour glass icon
						HCURSOR	hCursor = SetCursor( LoadCursor( NULL, IDC_WAIT ) );
						switch( Action )
							{
							case CCryptoShellExt::cryptEncrypt:
								{
								USES_CONVERSION;
								_variant_t	varDblEncryptFilename = GetDblCryptTempFilename();

									//	Try to decrypt first to guard against multiple encryptions
								if( FAILED( pCrypto->DecryptDoc( m_pbstrFiles[ nIndex ].m_str, varDblEncryptFilename ) ) )
									{
									( lpctstrDestination != NULL ) ?
										CHECK_HR( pCrypto->EncryptDoc( m_pbstrFiles[ nIndex ].m_str, _variant_t(bstrDestination) ) ) :
										CHECK_HR( pCrypto->EncryptDoc( m_pbstrFiles[ nIndex ].m_str, vtMissing ) );
									}

									//	Cleanup the intermediate file
								_unlink( W2A(varDblEncryptFilename.bstrVal) );								
								break;
								}

							case CCryptoShellExt::cryptDecrypt:
								( lpctstrDestination != NULL ) ?
									CHECK_HR( pCrypto->DecryptDoc( m_pbstrFiles[ nIndex ].m_str, _variant_t(vtDestination)  ) ) :
									CHECK_HR( pCrypto->DecryptDoc( m_pbstrFiles[ nIndex ].m_str, vtMissing  ) );
								break;

							default:
								ATLASSERT( 0 );
								break;
							}
						SetCursor( hCursor );
						}
					}
				}
			}
		}
	catch( HRESULT _hr )
		{
		UNREFERENCED_PARAMETER( _hr );
		IErrorInfo* pErrorInfo = NULL;
		if( ::GetErrorInfo( 0, &pErrorInfo ) == S_OK &&
			pErrorInfo                       != NULL    )
			{
			CComBSTR	bstrErrorMsg;
			
			pErrorInfo->GetDescription( &bstrErrorMsg );
			::MessageBox( NULL, _bstr_t(bstrErrorMsg.m_str), NULL, MB_OK | MB_ICONEXCLAMATION );
			pErrorInfo->Release();
			}	   
		}
	}


HRESULT CCryptoShellExt::
InsertContextMenuItem(	HMENU	hMenu,
						int		nMenuIndex,
						int		uidFirstCmd,
						int		uidCmdItem,
						int		nStringID	) const
	{
	HRESULT	hr								  = E_FAIL;
	TCHAR	lptstrBuffer[ MAX_STRINGTBL + 1 ] = {0};

		//	Insert the decrypt menu item
	if( ( ::LoadString( _Module.m_hInst,  nStringID,  lptstrBuffer,  MAX_STRINGTBL ) != 0    ) &&
		InsertMenu( hMenu, nMenuIndex, MF_BYPOSITION, uidFirstCmd + uidCmdItem, lptstrBuffer ) )
			hr = S_OK;

	return hr;
	}


BOOL 
BrowseFolder( LPTSTR	lptstrSelectedFolder )
	{
	BOOL			bResult	=	FALSE;

	ATLASSERT( !::IsBadWritePtr( lptstrSelectedFolder, sizeof( TCHAR ) * MAX_PATH ) );
	if( !::IsBadWritePtr( lptstrSelectedFolder, sizeof( TCHAR ) * MAX_PATH ) )
		{
		LPITEMIDLIST	pItemList	=	NULL;
		BROWSEINFO		BrowseInfo	=	{0};

		BrowseInfo.ulFlags	=	BIF_RETURNONLYFSDIRS | BIF_DONTGOBELOWDOMAIN ;
		BrowseInfo.lpfn     =	BrowseFolderProc;

			//	Show the browse dialog
		pItemList	=	SHBrowseForFolder( &BrowseInfo );
		if( pItemList )
			bResult = SHGetPathFromIDList( pItemList, lptstrSelectedFolder );
		}
	return bResult;	
	}



int CALLBACK
BrowseFolderProc( HWND		hWnd,
				  UINT		nMsg,
				  LPARAM	lParam,
				  LPARAM	dwData		)
	{
	switch( nMsg )
		{
		case	BFFM_SELCHANGED:
			{
			USES_CONVERSION;
			TCHAR	lptstrPath[ MAX_PATH ] = {0};
			
				//	Enable/disable the OK button based on whether the 
				//	selection is writable
			ATLASSERT( lParam );
			if( SHGetPathFromIDList( (LPITEMIDLIST)lParam, lptstrPath ) )
				::SendMessage( hWnd, BFFM_ENABLEOK, 0, _access( T2A(lptstrPath), 02 ) == 0 );			
			break;
			}
		}

	return 0;
	}


BOOL
BuildDestinationPathFromSrc( IN		const CComBSTR	bstrSource, 
							 INOUT		  CComBSTR& bstrDestination )
	{
	USES_CONVERSION;
	BOOL	bSuccess = FALSE;
	CHAR	lpstrSource[ MAX_PATH ]			= {0};
	CHAR*	lpstrSourceFilename				= NULL;
	CHAR	lpstrDestination[ MAX_PATH ]	= {0};

	if( bstrSource.Length()		 > 0 &&
		bstrDestination.Length() > 0 )
		{
			//	Perform string manipulations on CHAR first, then convert back
		strcpy( lpstrSource,	  W2A(bstrSource.m_str) );
		strcpy( lpstrDestination, W2A(bstrDestination)  );

			//	Point to the source filename
		lpstrSourceFilename = strrchr( lpstrSource, '\\' );
		if( lpstrSourceFilename )
			{
			lpstrSourceFilename++;
			ATLASSERT( lpstrSourceFilename != NULL );
			if( lpstrSourceFilename )
				{
					//	Tack on the trailing backslash if one doesn't already exist
				if( lpstrDestination[ strlen( lpstrDestination ) - 1 ] != '\\' )
					strcat( lpstrDestination, "\\" );

					//	Tack on the source filename
				strcat( lpstrDestination, lpstrSourceFilename );
				bstrDestination = lpstrDestination;
				bSuccess = TRUE;
				}
			}
		}

	return bSuccess;
	}


_variant_t
GetDblCryptTempFilename()
	{
	_variant_t  varFilename;
	TCHAR		lptstrTempDir[ MAX_PATH ] = {0};

	GetTempPath( MAX_PATH, lptstrTempDir );
	lstrcat( lptstrTempDir, DOUBLE_ENCRYPT_FILENAME );

	varFilename = lptstrTempDir;

	return varFilename;
	}