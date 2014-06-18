#if !defined(AFX_TSDOCCRYPTO_H__5410499B_F0ED_4A91_8AA4_FB38E19B8AAB__INCLUDED_)
#define AFX_TSDOCCRYPTO_H__5410499B_F0ED_4A91_8AA4_FB38E19B8AAB__INCLUDED_

////////////////////////////////////////////////////////////////////////////////
//
//	Title:		Cryptography Object
//	File:		TSDocCrypto.h
//	Author:		Chad Slater
//	Date:		January 2001
//
//	Abstract:	This object exposes a simple interface for encrypting and
//				decrypting files and in-memory data using the CryptoAPI.
//				The encrypted data is then digitally signed and the signature
//				is stored as a property of the object.
//
//
//	Encrypted File Binary Format:
//-------------------------------
//
//	+-----------+
//	|  4 BYTES	| <-- Binary format version (reserved)
//	|-----------|
//	|  4 BYTES	| <-- Size of the private key
//	|-----------|
//	|			|
//	| VARIABLE	| <-- Private key (typically ~76 bytes)
//	|   SIZE	|
//	|___________|
//	|			|
//	| VARIABLE	|
//	|	SIZE	| <-- Encrypted data
//	|			|
//	|-----------|
//	|	 EOF	|
//	|___________|
//
//
//	Current String Binary Format (In-memory Encryption):
//-----------------------------------------------------
//		
// +---------------+
// | BASE64 ENCODED|<---- Base64 Encoded BSTR
// |    WRAPPER	   |
// | +-----------+ |
// | |  4 BYTES	 |<---- Binary format version (reserved)
// | |-----------| |
// | |  4 BYTES	 |<---- Size of the private key
// | |-----------| |
// | |			 | |
// | | VARIABLE	 |<---- Private key (typically ~76 bytes)
// | |   SIZE	 | |
// | |-----------| |
// | |  4 BYTES	 |<---- Size of the encrypted data
// | |-----------| |
// | |			 | |
// | | VARIABLE	 | |
// | |	SIZE	 |<---- Encrypted data
// | |___________| |
// |_______________|
//
//
//
//	Revision History:
//	---------------------------------------------------------------------
//
//	cslater		01/26/2001	Initial revision
//	cslater		01/29/2001	Implemented EncryptDoc and DecryptDoc
//	cslater		02/02/2001	Added Base64EncodeFile and Base64DecodeFile
//	cslater		02/06/2001	Added Base64EncodeFileToString and
//								  Base64DecodeStringToFile
//
////////////////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif 
	// _MSC_VER > 1000

#include "resource.h"
#include "CryptoAPI.h"


class ATL_NO_VTABLE CCrypto : 
public CComObjectRootEx<CComSingleThreadModel>,
public CComCoClass<CCrypto, &CLSID_Crypto>,
public ISupportErrorInfo,
public IDispatchImpl<ICrypto, &IID_ICrypto, &LIBID_CRYPTOAPILib>
	{
	public:

		CCrypto();

		virtual
		~CCrypto();

		
		DECLARE_REGISTRY_RESOURCEID( IDR_CRYPTO )
			
			DECLARE_PROTECT_FINAL_CONSTRUCT()
			
			BEGIN_COM_MAP( CCrypto )
				COM_INTERFACE_ENTRY( ICrypto           )
				COM_INTERFACE_ENTRY( IDispatch         )
				COM_INTERFACE_ENTRY( ISupportErrorInfo )
			END_COM_MAP()
			
				// ISupportsErrorInfo
			STDMETHOD(InterfaceSupportsErrorInfo)( REFIID riid );
		
		// ITSDocCrypto
	public:
		
		
		virtual HRESULT STDMETHODCALLTYPE
		get_ContainerName( OUT	BSTR	*pVal );


		virtual HRESULT STDMETHODCALLTYPE
		put_ContainerName( IN	BSTR	newVal );

		
		virtual HRESULT STDMETHODCALLTYPE
		VerifyDigitalSignature( IN	BSTR	bstrDigitalSig, 
								OUT BOOL*	pbMatches		);


		virtual HRESULT STDMETHODCALLTYPE
		EncryptDoc(	 IN				BSTR	bstrSrc, 
					 IN OPTIONAL	VARIANT	varDestination	);


		virtual HRESULT STDMETHODCALLTYPE
		DecryptDoc(	 IN				BSTR	bstrSrc, 
					 IN OPTIONAL	VARIANT	varDestination	);


		virtual HRESULT STDMETHODCALLTYPE
		EncryptString( IN			BSTR	bstrSrc, 
					   OUT			BSTR*	pbstrResult		);


		virtual HRESULT STDMETHODCALLTYPE
		DecryptString( IN			BSTR	bstrSrc, 
					   OUT			BSTR*	pbstrResult	);


		virtual HRESULT STDMETHODCALLTYPE
		Base64DecodeString( IN		BSTR	bstrSrc, 
							OUT		BSTR*	pbstrResult	);


		virtual HRESULT STDMETHODCALLTYPE
		Base64EncodeString( IN		BSTR	bstrSrc, 
						    OUT		BSTR*	pbstrResult	);


		virtual HRESULT STDMETHODCALLTYPE
		Base64DecodeFile(	IN			BSTR	bstrSrc, 
							IN OPTIONAL VARIANT varDestination );
		
		virtual HRESULT STDMETHODCALLTYPE
		Base64EncodeFile( IN			BSTR	bstrSrc, 
						  IN OPTIONAL	VARIANT varDestination );


		virtual HRESULT STDMETHODCALLTYPE
		Base64EncodeFileToString( IN	BSTR	bstrSrc, 
								  OUT	BSTR*	pbstrResult );


		virtual HRESULT STDMETHODCALLTYPE
		Base64DecodeStringToFile( IN	BSTR  bstrSrc, 
								  IN	BSTR  bstrDestination );


		virtual HRESULT STDMETHODCALLTYPE
		get_DigitalSignature(	OUT	BSTR*	pVal );


	private:

		BOOL
		Initialize() const;
			//	Initializes the receiver object to use the cryptographic engine


		BOOL
		InitializeContainer() const;
			//	Initializes the cryptographic container and returns whether the
			//	operation was successful


		BOOL
		InitializeDigitalSignatureEngine() const;
			//	Prepares the container with a key pair for digital signatures 
			//	and returns whether the operation was successful


		BOOL
		InitializeEncryptionEngine() const;
			//	Prepares the container with a key pair for digital signatures 
			//	and returns whether the operation was successful


		void
		ClearDigitalSignature();
			//	Cleans up the digital signature


		BOOL
		WritePrivateKey( FILE* pDestination, HCRYPTKEY& lpPrivateKey );
			//	Writes the private key length and private key to the argument file


		BOOL
		ReadPrivateKey( FILE* pDestination, HCRYPTKEY& lpPrivateKey ) const;
			//	Reads the private key from the argument file and imports it
			//	into the CSP


		HCRYPTKEY
		GeneratePrivateKey( LPBYTE*	lpPrivateKeyBlob, 
							LPDWORD lpdwBlobSize,
							int		enumAlgorithm );
			//	Generates a private key and returns it from the CSP


		BOOL
		WriteFileFormatVersion( FILE* pDestination ) const;
			//	Writes the binary file format version to the destination file


		BOOL
		ReadFileFormatVersion( FILE* pSrc ) const;
			//	Reads the binary file format version and initializes the
			//	receiver object


		BOOL
		DigitallySignHash( HCRYPTHASH hHash );
			//	Signs the argument hash and returns whether the operation
			//	was successful


		inline int
		LookupCryptErrorStringID( int nLastError ) const;
			//	Returns the stringID associated with the argument error
			//	returned from GetLastError after a call to a Crypt function


		HRESULT
		Base64FileHelper( BSTR		bstrSrc, 
						  VARIANT	varDestination, 
						  BOOL		bEncode			= TRUE	) const;
			//	Helper function for encoding/decoding files


	
		mutable HCRYPTPROV	m_hContext;
				LPBYTE		m_lpDigitalSignature;
				DWORD		m_dwDigitalSignatureLen;
				CComBSTR	m_bstrContainerName;
					
	};

#endif 
	// !defined(AFX_TSDOCCRYPTO_H__5410499B_F0ED_4A91_8AA4_FB38E19B8AAB__INCLUDED_)
