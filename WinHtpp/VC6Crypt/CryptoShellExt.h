#ifndef __CRYPTOSHELLEXT_H_
#define __CRYPTOSHELLEXT_H_


////////////////////////////////////////////////////////////////////////////////
//
//	Title:		Crypto Shell Extension Object
//	File:		CryptoShellExt.h
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
//	cslater		3/15/2001 7:49:06 PM	Initial revision
//
//
//
////////////////////////////////////////////////////////////////////////////////




#include <shlobj.h>
#include <comdef.h>
#include "resource.h"       



class ATL_NO_VTABLE CCryptoShellExt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCryptoShellExt, &CLSID_CryptoShellExt>,
	public IDispatchImpl<ICryptoShellExt, &IID_ICryptoShellExt, &LIBID_CRYPTOAPILib>,
	public IShellExtInit, 
	public IContextMenu
	{
	public:


		CCryptoShellExt()
			:
			m_pbstrFiles( NULL ),
			m_nFiles( 0 )
			{}

		virtual
		~CCryptoShellExt()
			{
			CleanUp();
			}
		
		DECLARE_REGISTRY_RESOURCEID( IDR_CRYPTOSHELLEXT )
			
		DECLARE_PROTECT_FINAL_CONSTRUCT()
			
		BEGIN_COM_MAP(CCryptoShellExt)
			COM_INTERFACE_ENTRY( ICryptoShellExt )
			COM_INTERFACE_ENTRY( IDispatch		 )
			COM_INTERFACE_ENTRY( IShellExtInit	 )
			COM_INTERFACE_ENTRY( IContextMenu	 )
		END_COM_MAP()


	public:

			//	IShellExtInit
		STDMETHOD(Initialize)( LPCITEMIDLIST, LPDATAOBJECT, HKEY );
			
				// IContextMenu
		STDMETHOD(GetCommandString)(UINT, UINT, UINT*, LPSTR, UINT);
		STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO);
		STDMETHOD(QueryContextMenu)(HMENU, UINT, UINT, UINT, UINT);


	private:

		enum CryptAction
			{
			cryptEncrypt = 0,
			cryptDecrypt
			};

		void
		CleanUp();

		
		HRESULT 
		InsertContextMenuItem(	HMENU	hMenu,
								int		nMenuIndex,
								int		uidFirstCmd,
								int		uidCmdItem,
								int		nStringID	) const;


		void 
		DoCrypto( CryptAction cryptAction		 = cryptEncrypt,
				  LPCTSTR	  lpctstrDestination = NULL				) const;



		CComBSTR*	m_pbstrFiles;
		UINT		m_nFiles;

	};

#endif 
	//__CRYPTOSHELLEXT_H_
