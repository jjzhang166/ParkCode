////////////////////////////////////////////////////////////////////////////////
//
//	Title:		Cryptography Object
//	File:		TSDocCrypto.cpp
//	Author:		Chad Slater
//	Date:		January 2001
//
//	Current Encrypted File Binary Format:
//---------------------------------------
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
//	Revision History:
//	---------------------------------------------------------------------
//
//	cslater		01/26/2001	Initial revision
//	cslater		01/29/2001	Implemented EncryptDoc and DecryptDoc
//	cslater		01/30/2001	Initial attempt at in-memory encryption with 
//							128-bit encryption + Base64 encoding (failed...)
//	cslater		01/31/2001	Fixed the in-memory encryption algorithms so they
//							actually work (royal pain in the neck)
//	cslater		02/01/2001	Fixed memory leaks
//	cslater		02/02/2001  Added Base64EncodeFile and Base64DecodeFile
//	cslater		02/06/2001	Added Base64EncodeFileToString and
//								  Base64DecodeFileToString
//
//
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Base64Helper.h"
#include "Common.h"
#include "Crypto.h"
#include "windows.h"


	//	Types
typedef		BYTE*							LPBYTE;


	//	Algorithm to use for encryption
#define		FILE_ENCRYPT_ALGORITHM			CALG_RC2 
#define		INMEMORY_ENCRYPT_ALGORITHM		CALG_RC4
#define		HASHING_ALGORITHM				CALG_MD5

	//	Key container name - Unique per application
#define		CRYPTO_KEY_CONTAINER_NAME		_T("ICRYPTO_VERSION_1_0")

	//	Binary file format version (encrypted files)
#define		INVALID_FORMAT_VERSION			0xFFFFFFFF
#define		BINARY_FORMAT_MAJOR_VERSION		((WORD)0x0001)
#define		BINARY_FORMAT_MINOR_VERSION		((WORD)0x0000)
#define		FILE_BINARY_FORMAT_VERSION		MAKELONG(BINARY_FORMAT_MINOR_VERSION,\
													 BINARY_FORMAT_MAJOR_VERSION)
#define		INMEMORY_FORMAT_VERSION			MAKELONG(BINARY_FORMAT_MINOR_VERSION,\
													 BINARY_FORMAT_MAJOR_VERSION)

	//	General defines
#define		FILE_INTERMEDIATE_FILENAME		"INTERMEDIATE.CRP"
#define		FILE_READBYTES					0x00000200
#define		SIZE_VERSION					sizeof(DWORD)
#define		SIZE_PRIVATEKEY_SIZE			sizeof(DWORD)
#define		SIZE_ENCRYPTED_DATA				sizeof(DWORD)

	//	General macros
#define		VERIFY_MALLOC(lpData)			{\
											if(!lpData)\
												nStringID=IDS_ERROR_OUTOFMEMORY,\
												THROW_HRESULT( E_OUTOFMEMORY );\
											}

#define		CRYPTO_OUTPUT_DEBUGSTRING(nStringID) {\
													{\
													TCHAR	szMessage[ MAX_MSG ] = { 0 }; \
													if(::LoadString( _Module.GetResourceInstance(),\
																	 nStringID,\
																	 szMessage,\
																	 MAX_MSG ) ) \
														::OutputDebugString( szMessage ); \
													}\
												}

CCrypto::
CCrypto()
	:
	m_hContext( NULL ),
	m_lpDigitalSignature( NULL ),
	m_dwDigitalSignatureLen( 0 ),
	m_bstrContainerName( CRYPTO_KEY_CONTAINER_NAME )
	{}


CCrypto::
~CCrypto()
	{
	if( m_hContext )
		{
		CryptReleaseContext( m_hContext, 0 );
		m_hContext = NULL;
		}
	ClearDigitalSignature();	
	}


STDMETHODIMP CCrypto::
InterfaceSupportsErrorInfo( REFIID riid )
	{
	static const IID* arr[] =  { &IID_ICrypto };
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
		{
		if( InlineIsEqualGUID( *arr[i], riid ) )
			return S_OK;
		}
	return S_FALSE;
	}


STDMETHODIMP CCrypto::
get_DigitalSignature( BSTR* pVal )
	{
	HRESULT hr				= E_FAIL;
	HGLOBAL hDigSig			= NULL;
	LPBYTE	lpEncodedBytes	= NULL; 
	
	ATLASSERT( pVal );
	if( pVal )
		{
		if( m_lpDigitalSignature	&&
			m_dwDigitalSignatureLen > 0 )
			{
			PBYTE			lpEncodedDigSig	=	NULL;
			DWORD			dwEncodedDigSig =   0;
			CBase64Helper	Base64;

				//	Encode the digital signature
			dwEncodedDigSig = Base64.Base64Encoder(	m_lpDigitalSignature, 
													m_dwDigitalSignatureLen, 
													&hDigSig );
			
			lpEncodedDigSig = (LPBYTE)GlobalLock( hDigSig );
			ATLASSERT( lpEncodedDigSig );
			if( lpEncodedDigSig )
				{
					//	Convert to a zero-terminated string
				lpEncodedBytes = (LPBYTE)malloc( sizeof(BYTE) * dwEncodedDigSig + 1 );
				if( lpEncodedBytes )
					{
					USES_CONVERSION;

						//	Copy out to the caller
					memcpy( lpEncodedBytes, lpEncodedDigSig, dwEncodedDigSig );
					lpEncodedBytes[ dwEncodedDigSig ] = '\0';
					*pVal = ::SysAllocString( A2W((char*)lpEncodedBytes) );
					if( (*pVal) && 
						::SysStringLen( *pVal ) > 0 )
						hr = S_OK;
					else
						hr = Error( IDS_ERROR_OUTOFMEMORY, IID_ICrypto, E_OUTOFMEMORY );
					}
				else
					hr = Error( IDS_ERROR_OUTOFMEMORY, IID_ICrypto, E_OUTOFMEMORY );
				}

			else
				hr = Error( IDS_ERROR_OUTOFMEMORY, IID_ICrypto, E_OUTOFMEMORY );
			}
		else
			hr = Error( IDS_ERROR_DIGITALSIGNATURE_NOTAVAILABLE, 
						IID_ICrypto, E_FAIL );
		}
	else
		hr = Error( IDS_ERROR_INVALID_ARG, IID_ICrypto, E_INVALIDARG );

	if( hDigSig )
		GlobalFree( hDigSig );

	SAFE_MALLOC_FREE(lpEncodedBytes);
	return hr;
	}


STDMETHODIMP CCrypto::
get_ContainerName( BSTR *pVal )
	{
	return m_bstrContainerName.CopyTo( pVal );
	}


STDMETHODIMP CCrypto::
put_ContainerName( BSTR newVal )
	{
	m_bstrContainerName = newVal;	
	return S_OK;
	}



STDMETHODIMP CCrypto::
VerifyDigitalSignature( BSTR bstrDigitalSig, BOOL* pbMatches )
	{
	HRESULT		hr = S_OK;
	CComBSTR	bstrSrcDigSig( bstrDigitalSig );
	CComBSTR	bstrDigSig;

	ATLASSERT( pbMatches != NULL );

	if( pbMatches != NULL )
		{
		if( m_lpDigitalSignature &&
			m_dwDigitalSignatureLen > 0  )
			{
				//	Get the encoded string version of the digital signature
			hr = get_DigitalSignature( &bstrDigSig );
			if( SUCCEEDED( hr ) )
				*pbMatches = ( bstrDigSig == bstrDigitalSig );
			}
		else
			hr = Error( IDS_ERROR_DIGITALSIGNATURE_NOTAVAILABLE, 
						IID_ICrypto, E_FAIL );
		}
	else
		hr = Error( IDS_ERROR_INVALID_ARG, IID_ICrypto, E_INVALIDARG );

	return hr;
	}




STDMETHODIMP CCrypto::
EncryptDoc( BSTR		bstrSrc, 
			VARIANT		varDestination	)
	{
	USES_CONVERSION;
	USES_CHECKHR_MSG( IID_ICrypto );
	HRESULT		hr					= S_OK;
	HCRYPTKEY	hPrivateKey			= NULL;
	HCRYPTHASH	hDigSigHash			= NULL;
	LPBYTE		lpPrivateKey		= NULL;
	LPBYTE		lpData				= NULL; 
	FILE*		pSrcFile			= NULL;
	FILE*		pDestinationFile	= NULL;
	BOOL		bSrcIsDestination	= PARAM_IS_MISSING( varDestination );
	
	try
		{
		char* pFile = W2A(bstrSrc);
		pSrcFile = fopen( pFile, "rb" );
		//HANDLE hFile = ::CreateFile( pFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL );   
		DWORD dwError = GetLastError( );

			//	Open destination with intentions of destroying existing contents
		if( pSrcFile )
			pDestinationFile	= bSrcIsDestination ? 
										fopen( FILE_INTERMEDIATE_FILENAME,  "w+b" ) :
										fopen( W2A(varDestination.bstrVal), "w+b" );

		ATLASSERT( pSrcFile			!= NULL );
		ATLASSERT( pDestinationFile != NULL );

			//	Make sure the files opened
		if( pSrcFile			== NULL ||
			pDestinationFile	== NULL		)
			nStringID = IDS_ERROR_ENCRYPTFILE_FILEOPENFAILED,
			THROW_HRESULT( E_FAIL );

		if( !WriteFileFormatVersion( pDestinationFile ) )
			nStringID = IDS_ERROR_ENCRYPT_WRITEFILEFORMATVERSION,
			THROW_HRESULT( E_FAIL );

			//	Write the private key to the destination file
		ClearDigitalSignature();
		if(	Initialize()	&&
			WritePrivateKey( pDestinationFile, 
							 hPrivateKey		) )
			{
			lpData = (LPBYTE)malloc( FILE_READBYTES * sizeof( BYTE ) );
			VERIFY_MALLOC( lpData );
			
				//	Create the hash for digital signature 
			if( !CryptCreateHash( m_hContext, 
								  HASHING_ALGORITHM, 0, 0, 
								  &hDigSigHash ) )
				nStringID = IDS_ERROR_HASHCREATE_FAILED,
				THROW_HRESULT( E_FAIL );


				//	Read in the data from the source file, encrypt it and write to the destination
			do 
				{ 
				DWORD dwCount = fread(	lpData, 
										sizeof(BYTE), 
										FILE_READBYTES, 
										pSrcFile ); 							
				if( ferror( pSrcFile ) )
					nStringID = IDS_ERROR_ENCRYPT_READING_SOURCE,
					THROW_HRESULT( E_FAIL );

					// If encryption fails, give some useful information back to caller
				if( !CryptEncrypt(	hPrivateKey, 
									hDigSigHash, 
									feof(pSrcFile), 
									0, lpData, 
									&dwCount, FILE_READBYTES ) )
					nStringID = IDS_ERROR_ENCRYPT_ENCRYPTION_FAILED,
					THROW_HRESULT( E_FAIL );
				
					// Write encrypted data to the destination file
				fwrite( lpData, 
						sizeof(BYTE), 
						dwCount, 
						pDestinationFile ); 
				if( ferror( pDestinationFile ) )
					nStringID = IDS_ERROR_ENCRYPT_WRITETODESTINATION_FAILED,
					THROW_HRESULT( E_FAIL );
				} 
			while( !feof( pSrcFile ) ); 
			fflush( pDestinationFile );

			if( !DigitallySignHash( hDigSigHash ) )
				nStringID = IDS_ERROR_ENCRYPT_SIGNHASH_FAILED,
				THROW_HRESULT( E_FAIL );
		 	}

		else
			nStringID = IDS_ERROR_INITIALIZATION_FAILED,
			THROW_HRESULT( E_FAIL );
		}
	catch( HRESULT _hr )
		{
		CATCH_FAILED_HR(_hr);
		}
      
		////////////////////
		//	Cleanup

	if( hPrivateKey )
		CryptDestroyKey( hPrivateKey );

	SAFE_MALLOC_FREE( lpPrivateKey );
	
	if( pSrcFile )
		fclose( pSrcFile );

	if( pDestinationFile )
		fclose( pDestinationFile );

	SAFE_MALLOC_FREE( lpData );

	if( hDigSigHash )
		CryptDestroyHash( hDigSigHash );

		//	Caller wants to overwrite src - Copy Destination to Source
	if( bSrcIsDestination )
		{
			//	CopyFile fails if file is readonly
		SetFileAttributes( W2T(bstrSrc), FILE_ATTRIBUTE_NORMAL );
		if( !CopyFile( A2T(FILE_INTERMEDIATE_FILENAME), W2T(bstrSrc), FALSE ) )
			hr = Error( IDS_ERROR_DECRYPT_COPYDESTINATIONTOSOURCE_FAILED,
						IID_ICrypto, E_FAIL );
		}

		//	Delete the intermediate file - if it exists
	_unlink( FILE_INTERMEDIATE_FILENAME );

	return hr;
	}


STDMETHODIMP CCrypto::
DecryptDoc( BSTR		bstrSrc, 
		    VARIANT		varDestination	)
	{
	USES_CONVERSION;
	USES_CHECKHR_MSG( IID_ICrypto );
	HRESULT		hr					= S_OK;
	HCRYPTKEY	hPrivateKey			= NULL;
	HCRYPTHASH	hDigSigHash			= NULL;
	LPBYTE		lpData				= NULL; 
	FILE*		pSrcFile			= NULL;
	FILE*		pDestinationFile	= NULL;
	BOOL		bSrcIsDestination	= PARAM_IS_MISSING( varDestination );
	
	try
		{
		pSrcFile = fopen( W2A(bstrSrc), "rb" );

			//	Open destination with intentions of destroying existing contents
		if( pSrcFile )
			pDestinationFile	= bSrcIsDestination ? 
										fopen( FILE_INTERMEDIATE_FILENAME,  "w+b" ) :
										fopen( W2A(varDestination.bstrVal), "w+b" );

		ATLASSERT( pSrcFile			!= NULL );
		ATLASSERT( pDestinationFile != NULL );

			//	Make sure the files opened
		if( pSrcFile			== NULL ||
			pDestinationFile	== NULL		)
			nStringID = IDS_ERROR_DECRYPTFILE_FILEOPENFAILED,
			THROW_HRESULT( E_FAIL );

			//	Read the version stamp and make sure its a version that we can read
		if( !ReadFileFormatVersion( pSrcFile ) )
			nStringID = IDS_ERROR_DECRYPTFILE_READINGFILEVERSION,
			THROW_HRESULT( E_FAIL );

			//	Read the private key and import into CSP
		ClearDigitalSignature();
		if(	Initialize() &&
			ReadPrivateKey( pSrcFile, hPrivateKey ) )
			{	
			lpData	   = (LPBYTE)malloc( FILE_READBYTES * sizeof( BYTE ) );
			VERIFY_MALLOC( lpData );
				
				//	Create the hash for digital signature 
			if( !CryptCreateHash( m_hContext, 
								  HASHING_ALGORITHM, 0, 0, 
								  &hDigSigHash ) )
				nStringID = IDS_ERROR_HASHCREATE_FAILED,
				THROW_HRESULT( E_FAIL );

				//	Read in the data from the source file, encrypt it and write to the destination
			do 
				{ 
				DWORD dwCount = fread(	lpData, 
										sizeof(BYTE), 
										FILE_READBYTES, 
										pSrcFile ); 							
				if( ferror( pSrcFile ) )
					nStringID = IDS_ERROR_DECRYPT_READING_SOURCE,
					THROW_HRESULT( E_FAIL );

					// If encryption fails, give some useful information back to caller
				if( !CryptDecrypt(	hPrivateKey, 
									hDigSigHash, 
									feof(pSrcFile), 
									0, lpData, 
									&dwCount	 ) )
					nStringID = IDS_ERROR_DECRYPT_DECRYPTION_FAILED,
					THROW_HRESULT( E_FAIL );
				
					// Write decrypted data to the destination file
				fwrite( lpData, sizeof(BYTE), dwCount, pDestinationFile ); 
				if( ferror( pDestinationFile ) )
					nStringID = IDS_ERROR_DECRYPT_WRITETODESTINATION_FAILED,
					THROW_HRESULT( E_FAIL );
				} 
			while( !feof( pSrcFile ) ); 
			fflush( pDestinationFile );

				//	Determine the length of the digital signature
			if( !DigitallySignHash( hDigSigHash ) )
				nStringID = IDS_ERROR_DECRYPT_SIGNHASH_FAILED,
				THROW_HRESULT( E_FAIL );
		 	}
		}
	catch( HRESULT _hr )
		{
		CATCH_FAILED_HR( _hr );
		}
      
		///////////////////////////////////////////////////////////////////////
		//	Cleanup
	if( hPrivateKey )
		CryptDestroyKey( hPrivateKey );

	if( pSrcFile )
		fclose( pSrcFile );

	if( pDestinationFile )
		fclose( pDestinationFile );

	SAFE_MALLOC_FREE( lpData );

	if( hDigSigHash )
		CryptDestroyHash( hDigSigHash );

		//	Caller wants to overwrite src - Copy Destination to Source
	if( SUCCEEDED(hr) && 
		bSrcIsDestination )
		{
			//	CopyFile fails if file is readonly
		SetFileAttributes( W2T(bstrSrc), FILE_ATTRIBUTE_NORMAL );
		if( !CopyFile( A2T(FILE_INTERMEDIATE_FILENAME), W2T(bstrSrc), FALSE ) )
			hr = Error( IDS_ERROR_DECRYPT_COPYDESTINATIONTOSOURCE_FAILED,
						IID_ICrypto, E_FAIL );
		}

		//	Delete the intermediate file - if it exists
	_unlink( FILE_INTERMEDIATE_FILENAME );

	return hr;
	}


STDMETHODIMP CCrypto::
EncryptString(	BSTR bstrSrc, BSTR *pbstrResult	)
	{
	USES_CONVERSION;
	USES_CHECKHR_MSG( IID_ICrypto );
	HRESULT			hr				= S_OK;	
	HCRYPTKEY		hPrivateKey		= NULL;
	HCRYPTHASH		hDigSigHash		= NULL;
	LPBYTE			lpPrivateKey	= NULL;
	LPBYTE			lpFinalBuffer	= NULL;
	LPBYTE			lpSrcBytes		= NULL;
	LPBYTE			lpEncodedBytes	= NULL;

	ATLASSERT( pbstrResult	!= NULL	);
	try
		{
		CComBSTR	strSrc(bstrSrc);

		ClearDigitalSignature();
		if( !Initialize() )
			nStringID = IDS_ERROR_INITIALIZATION_FAILED,
			THROW_HRESULT( E_FAIL );

			//	Nothing to encrypt?
		ATLASSERT( strSrc.Length() > 0 );
		if( strSrc.Length() > 0 )
			{
			DWORD	dwEncryptSize	= 0; 
			DWORD	dwEncodedBytes	= 0;
			DWORD	dwPrivateKeySize= 0;
			DWORD	dwFinalBuffer	= 0;
			DWORD	dwVersion		= INMEMORY_FORMAT_VERSION;
			DWORD	dwEncryptedLen	= strSrc.Length();
		
			hPrivateKey = GeneratePrivateKey( &lpPrivateKey, 
											  &dwPrivateKeySize, 
											  INMEMORY_ENCRYPT_ALGORITHM );
			if(  hPrivateKey  &&
				lpPrivateKey	)
				{
				CBase64Helper	Base64Helper;
				
					//	Create the hash for digital signature 
				if( !CryptCreateHash( m_hContext, 
									  HASHING_ALGORITHM, 0, 0, 
									  &hDigSigHash ) )
					nStringID = IDS_ERROR_HASHCREATE_FAILED,
					THROW_HRESULT( E_FAIL );

					
					//	Copy the src string into a byte array
				lpSrcBytes = (LPBYTE)malloc( sizeof(BYTE) * strSrc.Length() + 1 );
				VERIFY_MALLOC( lpSrcBytes );
				strcpy( (char*)lpSrcBytes, W2A(strSrc) );
				
					//	Calculate the size of the encrypted buffer
				dwEncryptSize = strlen( (char*)lpSrcBytes );

					// Encrypt the src string and initialize the digital signature hash
				if( !CryptEncrypt(	hPrivateKey, 
									hDigSigHash, 
									TRUE, 
									0, 
									lpSrcBytes, 
									&dwEncryptSize, 
									dwEncryptSize		) )
					nStringID = IDS_ERROR_ENCRYPT_ENCRYPTION_FAILED,
					THROW_HRESULT( E_FAIL );		
			
					//	Calculate the total size of the resulting string (in bytes)
				dwFinalBuffer = SIZE_VERSION		 + 
								SIZE_PRIVATEKEY_SIZE +
								dwPrivateKeySize	 +
								SIZE_ENCRYPTED_DATA  + 
								dwEncryptSize;

					//	Create the final buffer
				lpFinalBuffer = (LPBYTE)malloc( ( sizeof(BYTE) * dwFinalBuffer ) + 1 );
				VERIFY_MALLOC( lpFinalBuffer );
					
					//	Build the encrypted blob in-memory
				memcpy( lpFinalBuffer, &dwVersion, sizeof(dwVersion) );
				memcpy( &lpFinalBuffer[ SIZE_VERSION ], &dwPrivateKeySize, sizeof(dwPrivateKeySize) );
				memcpy( &lpFinalBuffer[ SIZE_VERSION + SIZE_PRIVATEKEY_SIZE ], lpPrivateKey, dwPrivateKeySize );
				memcpy( &lpFinalBuffer[ SIZE_VERSION + SIZE_PRIVATEKEY_SIZE + dwPrivateKeySize ], &dwEncryptedLen, sizeof(dwEncryptedLen) );
				memcpy( &lpFinalBuffer[ SIZE_VERSION + SIZE_PRIVATEKEY_SIZE + dwPrivateKeySize + SIZE_ENCRYPTED_DATA ], lpSrcBytes, dwEncryptSize );

					//	Prepare the encrypted blob for the caller
				dwEncodedBytes = Base64Helper.Base64Encoder( lpFinalBuffer, dwFinalBuffer, (void**)&lpEncodedBytes );
				
					//	Convert encoded/encrypted bytes to zero-terminated string
				lpSrcBytes = (LPBYTE)realloc( lpSrcBytes, dwEncodedBytes + 1 );
				memcpy( lpSrcBytes, (PBYTE)GlobalLock( lpEncodedBytes ), dwEncodedBytes );
				lpSrcBytes[ dwEncodedBytes ] = '\0';
					
					//	Grab the digital signature
				if( !DigitallySignHash( hDigSigHash ) )
					nStringID = IDS_ERROR_DIGITALSIGNATURE_ENCRYPT_STRING,
					THROW_HRESULT( E_FAIL );

					//	Copy out to the caller
				*pbstrResult = ::SysAllocString( A2W((char*)lpSrcBytes) );				
				}
			}
		}
	catch( HRESULT _hr )
		{
		CATCH_FAILED_HR( _hr );
		}

		//	Cleanup
	if( hPrivateKey	)
		CryptDestroyKey( hPrivateKey );

	SAFE_MALLOC_FREE( lpSrcBytes	);
	SAFE_MALLOC_FREE( lpFinalBuffer );
	SAFE_MALLOC_FREE( lpPrivateKey	);

	if( hDigSigHash )
		CryptDestroyHash( hDigSigHash );	

	if( lpEncodedBytes )
		GlobalFree( lpEncodedBytes );

	return hr;
	}


STDMETHODIMP CCrypto::
DecryptString( BSTR bstrSrc, BSTR *pbstrResult )
	{
	USES_CONVERSION;
	USES_CHECKHR_MSG( IID_ICrypto );
	HRESULT		hr				= S_OK;	
	HCRYPTHASH	hDigSigHash		= NULL;
	HCRYPTKEY	hPrivateKey		= NULL;
	LPBYTE		lpSrcBytes		= NULL;
	HGLOBAL		hDecodedBytes	= NULL;
	PBYTE		lpDecodedBytes	= NULL;
	LPBYTE		lpEncryptedData = NULL;
	LPBYTE		lpPrivateKey	= NULL;	

	ATLASSERT( pbstrResult	!= NULL	);
	try
		{
		CBase64Helper	Base64;
		CComBSTR		bstrDecoded(bstrSrc);

        ClearDigitalSignature();
		if( !Initialize() )
			nStringID = IDS_ERROR_INITIALIZATION_FAILED,
			THROW_HRESULT( E_FAIL );
		
			//	Must be long enough
		ATLASSERT( ::SysStringLen( bstrSrc ) > ( SIZE_VERSION + SIZE_PRIVATEKEY_SIZE ) );
		if( ::SysStringLen( bstrSrc ) > ( SIZE_VERSION + SIZE_PRIVATEKEY_SIZE ) )
			{
			DWORD	dwVersion			= INVALID_FORMAT_VERSION;
			DWORD	dwPrivateKeySize	= 0;
			DWORD	dwEncryptedData		= 0;
			DWORD	dwDecodedBytes		= 0;

				//	Create the hash for digital signature 
			if( !CryptCreateHash( m_hContext, 
								  HASHING_ALGORITHM, 0, 0, 
								  &hDigSigHash ) )
				nStringID = IDS_ERROR_HASHCREATE_FAILED,
				THROW_HRESULT( E_FAIL );
			
				//	Covert the src encoded, encrypted string into a byte array
			lpSrcBytes = (LPBYTE)malloc( sizeof(BYTE) * bstrDecoded.Length() + 1 );
			VERIFY_MALLOC( lpSrcBytes );
			strcpy( (char*)lpSrcBytes, W2A(bstrDecoded) );

				//	Decode the bytes
			dwDecodedBytes = Base64.Base64Decoder(	lpSrcBytes, 
													strlen( (char*)lpSrcBytes ), 
													&hDecodedBytes );
			lpDecodedBytes = (PBYTE)GlobalLock( hDecodedBytes );

				//	Grab the version and private key size
			dwVersion		= (*((DWORD*)lpDecodedBytes));
			dwPrivateKeySize= (*((DWORD*)&lpDecodedBytes[ SIZE_VERSION ]));

				//	Validate the in-memory string format
			if( dwVersion != INMEMORY_FORMAT_VERSION ||
				dwDecodedBytes <= ( SIZE_VERSION + SIZE_PRIVATEKEY_SIZE + dwPrivateKeySize ) )
				nStringID = IDS_ERROR_UNSUPORTED_INMEMORY_ENCRYPTION_VERSION,
				THROW_HRESULT( E_FAIL );

				//	Grab the private key
			lpPrivateKey	= (LPBYTE)malloc( sizeof(BYTE) * dwPrivateKeySize );
			VERIFY_MALLOC( lpPrivateKey );
			memcpy( lpPrivateKey, &lpDecodedBytes[ SIZE_VERSION + SIZE_PRIVATEKEY_SIZE ], sizeof(BYTE) * dwPrivateKeySize );

			//	Import the private key into the CSP
			if( !CryptImportKey( m_hContext, 
								 lpPrivateKey, 
								 dwPrivateKeySize, 0, 0, 
								 &hPrivateKey		) )
				nStringID = IDS_ERROR_IMPORTPRIVATEKEY_FAILED,
				THROW_HRESULT( E_FAIL );


				//	Grab the encrypted data size
			dwEncryptedData = (*((DWORD*)&lpDecodedBytes[ SIZE_VERSION + SIZE_PRIVATEKEY_SIZE + dwPrivateKeySize ]));
				
				//	Grab the encrypted data
			lpEncryptedData = (LPBYTE)malloc( dwEncryptedData + 1 );
			VERIFY_MALLOC( lpEncryptedData );
			memcpy( lpEncryptedData, &lpDecodedBytes[	SIZE_VERSION + SIZE_PRIVATEKEY_SIZE + SIZE_ENCRYPTED_DATA + dwPrivateKeySize ], dwEncryptedData	);
				
				//	Perform the decryption
			if( !CryptDecrypt(	hPrivateKey, 
								hDigSigHash, 
								TRUE, 0, 
								lpEncryptedData, 
								&dwEncryptedData ) )
				nStringID = IDS_ERROR_DECRYPTSTRING_FAILED,
				THROW_HRESULT( E_FAIL );
			
				//	Copy the result to the caller
			lpEncryptedData[ dwEncryptedData ] = '\0';
			*pbstrResult = ::SysAllocString( A2W((char*)lpEncryptedData) );
			
				//	Digital signature
			if( !DigitallySignHash( hDigSigHash ) )
				nStringID = IDS_ERROR_DIGITALSIGNATURE_DECRYPT_STRING,
				THROW_HRESULT( E_FAIL );
			}

			//	Bad format
		else
			nStringID = IDS_ERROR_UNSUPORTED_INMEMORY_ENCRYPTION_VERSION,
			THROW_HRESULT( E_FAIL );

		}
	catch( HRESULT _hr )
		{
		CATCH_FAILED_HR( _hr );
		}

	SAFE_MALLOC_FREE( lpSrcBytes		);
	SAFE_MALLOC_FREE( lpPrivateKey		);
	SAFE_MALLOC_FREE( lpEncryptedData	);

	if( hPrivateKey	)
		CryptDestroyKey( hPrivateKey );

	if( hDecodedBytes )
		GlobalFree( hDecodedBytes );

	if( hDigSigHash	)
		CryptDestroyHash( hDigSigHash );
	
	return hr;
	}


STDMETHODIMP CCrypto::
Base64EncodeString(	BSTR bstrSrc, BSTR *pbstrResult	)
	{
	CBase64Helper	Base64;
	CComBSTR		bstrEncoded = Base64.Base64EncodeString( bstrSrc );
	return bstrEncoded.CopyTo( pbstrResult );
	}


STDMETHODIMP CCrypto::
Base64DecodeString( BSTR bstrSrc, BSTR *pbstrResult	)
	{
	CBase64Helper	Base64;
	CComBSTR		bstrDecoded = Base64.Base64DecodeString( bstrSrc );
	return bstrDecoded.CopyTo( pbstrResult );
	}


STDMETHODIMP CCrypto::
Base64EncodeFile( BSTR bstrSrc, VARIANT varDestination )
	{
	return Base64FileHelper( bstrSrc, varDestination );
	}


STDMETHODIMP CCrypto::
Base64DecodeFile( BSTR bstrSrc, VARIANT varDestination )
	{
	return Base64FileHelper( bstrSrc, varDestination, FALSE );
	}


STDMETHODIMP CCrypto::
Base64EncodeFileToString( BSTR  bstrSrc, 
						  BSTR* pbstrResult )
	{
	USES_CONVERSION;
	USES_CHECKHR_MSG( IID_ICrypto );
	FILE*		pSrcFile				= NULL;
	HRESULT		hr						= S_OK;
	LPBYTE		lpData[ FILE_READBYTES ]= {0}; 
    LPBYTE      lpResultBlob            = NULL;
	HGLOBAL		hEncodedBytes			= NULL;
	LPBYTE		pEncodedBytes			= NULL;
    DWORD       dwTotalRead             = 0;   
	CComBSTR	bstrResult;
	
	ATLASSERT( pbstrResult != NULL );
	try
		{
		pSrcFile = fopen( W2A(bstrSrc), "rb" );
		ATLASSERT( pSrcFile			!= NULL );
		
			//	Make sure the files opened
		if( pSrcFile == NULL )
			nStringID = IDS_ERROR_ENCODEDFILE_FILEOPENFAILED,
			THROW_HRESULT( E_FAIL );

            //  Read the file into memory - We need to anyway since the client wants a string back
		do
			{
            LPBYTE  lpTemp = NULL;

				// Read up to FILE_READBYTES bytes from the source file
			DWORD  dwCount = fread( lpData, sizeof(BYTE), FILE_READBYTES, pSrcFile );
			if( ferror( pSrcFile ) )
				nStringID = IDS_ERROR_ENCODEDFILE_FILEIO,
				THROW_HRESULT( E_FAIL );

                //  Append the bytes to what has already been read
            dwTotalRead += dwCount;
            lpTemp = (LPBYTE)realloc( lpResultBlob, dwTotalRead + 1 );
            VERIFY_MALLOC( lpTemp );
            lpResultBlob = lpTemp;
            memcpy( &lpResultBlob[ dwTotalRead - dwCount ], lpData, dwCount );
			}
		while( !feof(pSrcFile) );
		}
	catch( HRESULT _hr )
		{
		CATCH_FAILED_HR( _hr );
		}

        //  Clean up
	if( pSrcFile )
		fclose( pSrcFile );

	if( SUCCEEDED( hr ) )
        {
        CBase64Helper	Base64;
        
            //  Encode the bits
        DWORD dwEncoded = Base64.Base64Encoder( (LPBYTE)lpResultBlob, dwTotalRead, &hEncodedBytes );				
		pEncodedBytes = (LPBYTE)GlobalLock( hEncodedBytes );

            //  Convert encoded bits to a BSTR
        bstrResult.Append( (LPCSTR)pEncodedBytes );
        hr = bstrResult.CopyTo( pbstrResult );
        GlobalFree( hEncodedBytes );
        }

    SAFE_MALLOC_FREE( lpResultBlob );
	return hr;
	}


STDMETHODIMP CCrypto::
Base64DecodeStringToFile( BSTR  bstrSrc, 
						  BSTR  bstrDestination )
	{
	USES_CONVERSION;
	USES_CHECKHR_MSG( IID_ICrypto );
	HRESULT		hr				= S_OK;
	LPBYTE		lpSrcBytes		= NULL;
	HGLOBAL		hDecodedBytes	= NULL;
	FILE*		pDestination	= NULL;
	CComBSTR	cbstrSrc( bstrSrc );

	try
		{
		CBase64Helper	Base64;
		DWORD			dwDecoded		= 0;

			//	Copy the source string to byte array
		lpSrcBytes = (LPBYTE)malloc( sizeof(BYTE) * cbstrSrc.Length() + 1 );
		VERIFY_MALLOC( lpSrcBytes );
		strcpy( (char*)lpSrcBytes, W2A(cbstrSrc) );

		dwDecoded = Base64.Base64Decoder( lpSrcBytes, strlen( (LPCSTR)lpSrcBytes ), &hDecodedBytes );

		pDestination = fopen( W2A(bstrDestination), "w+b" );
		if( pDestination )
			{
			LPBYTE	lpDecodedBytes = (LPBYTE)GlobalLock( hDecodedBytes );
			
				//	Write the result to the destination file
			fwrite( lpDecodedBytes, sizeof(BYTE), dwDecoded, pDestination );
			fflush( pDestination );

			if( ferror( pDestination ) )
				nStringID = IDS_ERROR_DECODED_FILEIO,
				THROW_HRESULT( E_FAIL );
			}
		}
	catch( HRESULT _hr )
		{
		CATCH_FAILED_HR( _hr );
		}

		//	Cleanup
	SAFE_MALLOC_FREE( lpSrcBytes );
	if( hDecodedBytes )
		GlobalFree( hDecodedBytes    );

	if( pDestination )
		fclose( pDestination );
	
	return hr;
	}


BOOL CCrypto::
Initialize() const
	{
	BOOL	bSuccess	= TRUE;

	if( !m_hContext )		
		{
		bSuccess =  InitializeContainer();
		if( bSuccess )
			{
			bSuccess  = InitializeDigitalSignatureEngine();

			if( bSuccess )
				bSuccess = 	InitializeEncryptionEngine();

				//	If we failed to initialize digital signatures or encryption, then reset
			if( !bSuccess )
				{
				CryptReleaseContext( m_hContext, 0 );
				m_hContext = NULL;
				}
			}
		}
	return bSuccess;
	}


BOOL CCrypto::
InitializeContainer() const
	{
	USES_CONVERSION;
	BOOL	bSuccess = FALSE;
	int		nStringID= IDS_UNKNOWN_ERROR;

	ATLASSERT( !m_hContext );
	bSuccess = CryptAcquireContext( &m_hContext, 
									W2T(m_bstrContainerName.m_str), 
									MS_DEF_PROV, 
									PROV_RSA_FULL, 0 );
		
		//	Container doesn't exist - Possibly try to create a new container
	if( !bSuccess )
		{
		int nLastError = GetLastError();
		if( nLastError == NTE_BAD_KEYSET )
			{
				//	Creating the key container for the first time
			bSuccess = CryptAcquireContext( &m_hContext, 
											W2T(m_bstrContainerName.m_str), 
											MS_DEF_PROV, 
											PROV_RSA_FULL, CRYPT_NEWKEYSET );

			if( !bSuccess )
				nStringID = IDS_ERROR_INITIALIZATION_CREATE_NEW_CONTAINER_FAILED;
			}
		else
			nStringID = LookupCryptErrorStringID( nLastError );
		}

	if( !bSuccess )
		CRYPTO_OUTPUT_DEBUGSTRING( nStringID );

	return bSuccess;
	}


BOOL CCrypto::
InitializeDigitalSignatureEngine() const
	{
	BOOL		bSuccess = FALSE;
	HCRYPTKEY	hKey	 = NULL;
	int			nStringID= IDS_UNKNOWN_ERROR;

		//	Check the key pair for digital signatures
	if( !CryptGetUserKey( m_hContext, AT_SIGNATURE, &hKey ) )
		{
		if( GetLastError() == NTE_NO_KEY ) 
			{		
				// There is a container but no key - Create signature key pair
			if( !CryptGenKey( m_hContext, AT_SIGNATURE, 0, &hKey ) )
				nStringID = IDS_ERROR_INITIALIZATION_CREATE_DIGSIGKEYS;

			else
				bSuccess = TRUE;
			}
		else
			nStringID = IDS_ERROR_INITIALIZATION_CREATE_DIGSIGKEYS;
		}

		//	Key pair already available
	else
		bSuccess = TRUE;
	
	if( hKey )
		CryptDestroyKey( hKey );

	if( !bSuccess )
		CRYPTO_OUTPUT_DEBUGSTRING( nStringID );

	return bSuccess;
	}


BOOL CCrypto::
InitializeEncryptionEngine() const
	{
	BOOL		bSuccess = FALSE;
	HCRYPTKEY	hKey	 = NULL;
	int			nStringID= IDS_UNKNOWN_ERROR;

		//	Check the key pair for encryption
	if( !CryptGetUserKey( m_hContext, AT_KEYEXCHANGE, &hKey ) )
		{
		if( GetLastError() == NTE_NO_KEY ) 
			{		
				// There is a container but no key - Create an encryption key pair
			if( !CryptGenKey( m_hContext, AT_KEYEXCHANGE, 0, &hKey ) )
				nStringID = IDS_ERROR_INITIALIZATION_CREATE_ENCRYPTIONKEYS;

			else
				bSuccess = TRUE;
			}
		else
			nStringID = IDS_ERROR_INITIALIZATION_CREATE_ENCRYPTIONKEYS;
		}

		//	Key pair already available
	else
		bSuccess = TRUE;
	
	if( hKey )
		CryptDestroyKey( hKey );

	if( !bSuccess )
		CRYPTO_OUTPUT_DEBUGSTRING( nStringID );

	return bSuccess;
	}


void CCrypto::
ClearDigitalSignature()
	{
	SAFE_MALLOC_FREE( m_lpDigitalSignature );
	m_dwDigitalSignatureLen = 0;
	}


BOOL CCrypto::
WritePrivateKey(	FILE*		pDestination, 
					HCRYPTKEY&	hPrivateKey	)
	{
	BOOL		bSuccess	= FALSE;
	DWORD		dwBlobLen	= 0;
	LPBYTE		lpPrivateKey= NULL;

	ATLASSERT( pDestination	!= NULL );
	
		//	Get a private key
	hPrivateKey = GeneratePrivateKey( &lpPrivateKey, &dwBlobLen, FILE_ENCRYPT_ALGORITHM );

		//	If we succeeded in getting a private key...
	if(  lpPrivateKey )
		{
			//	Write the size of the private key to the destination file
		if( fwrite(  &dwBlobLen, sizeof(dwBlobLen), 1, pDestination ) )
			{
				//	Write the private key (encrypted) to the destination file
			if( fwrite( lpPrivateKey, sizeof(BYTE), dwBlobLen, pDestination ) == dwBlobLen )
				bSuccess = TRUE;
			}
		}

	SAFE_MALLOC_FREE( lpPrivateKey );
	return bSuccess;
	}


BOOL CCrypto::
ReadPrivateKey( FILE* pSrcFile, HCRYPTKEY& hPrivateKey ) const
	{
	BOOL		bSuccess		= FALSE;
	DWORD		dwKeySize		= 0;
	LPBYTE		lpPrivateKey	= NULL;

	ATLASSERT( pSrcFile		!= NULL );

		//	Read in the key size
	if( fread( &dwKeySize, sizeof(DWORD), 1, pSrcFile ) )
		{
			//	Allocate room to hold the private key
		lpPrivateKey = (LPBYTE)malloc( sizeof(BYTE)*dwKeySize );
		ATLASSERT( lpPrivateKey != NULL );
		if( lpPrivateKey )
			{
				//	Read in the private key
			if( fread(	lpPrivateKey, 
						sizeof(BYTE), 
						dwKeySize, 
						pSrcFile ) == dwKeySize )
				{
					//	Import the private key into the CSP
				bSuccess = CryptImportKey(  m_hContext, 
											lpPrivateKey, 
											dwKeySize, 0, 0, 
											&hPrivateKey		);
				}
			}				
		}
	SAFE_MALLOC_FREE( lpPrivateKey );
	return bSuccess;
	}


BOOL CCrypto::
WriteFileFormatVersion( FILE* pDestination ) const
	{
	DWORD	dwFileFormat = FILE_BINARY_FORMAT_VERSION;
	
	ATLASSERT( pDestination != NULL );

		//	Stamp the file with the version header
	return( fwrite( &dwFileFormat, sizeof(DWORD), 1, pDestination ) );
	}


BOOL CCrypto::
ReadFileFormatVersion( FILE* pSrc ) const
	{
	BOOL	bSuccess	 = FALSE;
	DWORD	dwFileFormat = INVALID_FORMAT_VERSION;
	
	ATLASSERT( pSrc != NULL );
	if( fread( &dwFileFormat, sizeof(DWORD), 1, pSrc ) )
		{
		ATLASSERT( dwFileFormat == FILE_BINARY_FORMAT_VERSION );
		if( dwFileFormat == FILE_BINARY_FORMAT_VERSION )
			bSuccess = TRUE;
		}	
	return bSuccess;
	}


HCRYPTKEY CCrypto::
GeneratePrivateKey( LPBYTE*	lpPrivateKeyBlob, 
					LPDWORD lpdwBlobSize,
					int		enumAlgorithm		) 
	{
	HCRYPTKEY	hPrivateKey = NULL;
	HCRYPTKEY	hPublicKey  = NULL;

		//	Generate the private key
	ClearDigitalSignature();
	if( Initialize() &&
		CryptGenKey( m_hContext, 
					 enumAlgorithm, 
					 CRYPT_EXPORTABLE, &hPrivateKey ) )
		{
			// Get handle to the encrypter's exchange public key 
		if( CryptGetUserKey( m_hContext, AT_KEYEXCHANGE, &hPublicKey ) )
			{
				// Determine size of the key blob
			if( CryptExportKey( hPrivateKey, 
								hPublicKey, 
								SIMPLEBLOB, 
								0, NULL, 
								lpdwBlobSize ) )
				{
				(*lpPrivateKeyBlob) = (LPBYTE)malloc( sizeof(BYTE) * (*lpdwBlobSize) );
				ATLASSERT( lpPrivateKeyBlob != NULL );

				if( lpPrivateKeyBlob )
						// Encrypt and export private key 
					CryptExportKey( hPrivateKey, 
						 			hPublicKey, 
									SIMPLEBLOB, 
									0, 
									(*lpPrivateKeyBlob), 
									lpdwBlobSize		);
				}
			}
		}

	if( hPublicKey )
		CryptDestroyKey( hPublicKey );

	return hPrivateKey;
	}


BOOL CCrypto::
DigitallySignHash( HCRYPTHASH hHash )
	{
	BOOL	bSuccess	= FALSE;

	ATLASSERT( hHash );
	
		//	Clear existing signature
	ClearDigitalSignature();
	
		//	Determine the length of the digital signature
	if( CryptSignHash( hHash, 
					   AT_SIGNATURE, NULL, 
					   0, NULL, &m_dwDigitalSignatureLen ) )
		{
		ATLASSERT( m_lpDigitalSignature == NULL );
		m_lpDigitalSignature = (LPBYTE)malloc( m_dwDigitalSignatureLen + 1 );
		if( m_lpDigitalSignature )
				//	Sign the original (decrypted) data 
			bSuccess = CryptSignHash(	hHash, 
										AT_SIGNATURE, NULL, 0, 
										m_lpDigitalSignature, 
										&m_dwDigitalSignatureLen );
		}
	return bSuccess;
	}


HRESULT CCrypto::
Base64FileHelper( BSTR		bstrSrc, 
				  VARIANT	varDestination, 
				  BOOL		bEncode				) const
	{
	USES_CONVERSION;
	USES_CHECKHR_MSG( IID_ICrypto );
	HRESULT		hr						= S_OK;
	LPBYTE		lpData[ FILE_READBYTES ]= {0}; 
	FILE*		pSrcFile				= NULL;
	FILE*		pDestinationFile		= NULL;
	HGLOBAL		hEncodedBytes			= NULL;
	BOOL		bSrcIsDestination		= PARAM_IS_MISSING( varDestination );
	try
		{
		CBase64Helper	Base64;

		pSrcFile = fopen( W2A(bstrSrc), "rb" );

			//	Open destination with intentions of destroying existing contents
		if( pSrcFile )
			pDestinationFile	= bSrcIsDestination ? 
										fopen( FILE_INTERMEDIATE_FILENAME,  "w+b" ) :
										fopen( W2A(varDestination.bstrVal), "w+b" );

		ATLASSERT( pSrcFile			!= NULL );
		ATLASSERT( pDestinationFile != NULL );

			//	Make sure the files opened
		if( pSrcFile			== NULL ||
			pDestinationFile	== NULL		)
			nStringID = IDS_ERROR_ENCODEDFILE_FILEOPENFAILED,
			THROW_HRESULT( E_FAIL );

		do
			{
				// Read up to FILE_READBYTES_BLOCKSIZE bytes from the source file
			DWORD dwEncoded = 0;
			DWORD dwCount	= fread(	lpData, 
										sizeof(BYTE), 
										FILE_READBYTES, 
										pSrcFile );
			
			if( ferror( pSrcFile ) )
				nStringID = IDS_ERROR_ENCODEDFILE_FILEIO,
				THROW_HRESULT( E_FAIL );

				//	Encode or decode the bits
			dwEncoded = bEncode ? Base64.Base64Encoder( (LPBYTE)lpData, dwCount, &hEncodedBytes ) :
								  Base64.Base64Decoder( (LPBYTE)lpData, dwCount, &hEncodedBytes );
			
				// Write encoded/decoded data to the destination file
			fwrite( GlobalLock(hEncodedBytes), 
					sizeof(BYTE), 
					dwEncoded, 
					pDestinationFile ); 
			GlobalFree( hEncodedBytes );

			if( ferror( pDestinationFile ) )
				nStringID = IDS_ERROR_ENCODEDFILE_FILEIO,
				THROW_HRESULT( E_FAIL );
			}
		while( !feof(pSrcFile) );
		fflush( pDestinationFile );
		}
	catch( HRESULT _hr )
		{
		CATCH_FAILED_HR( _hr );
		}

	if( pSrcFile )
		fclose( pSrcFile );

	if( pDestinationFile )
		fclose( pDestinationFile );

		//	Caller wants to overwrite src - Copy Destination to Source
	if( SUCCEEDED(hr) && 
		bSrcIsDestination )
		{
			//	CopyFile fails if file is readonly
		SetFileAttributes( W2T(bstrSrc), FILE_ATTRIBUTE_NORMAL );
		if( !CopyFile( A2T(FILE_INTERMEDIATE_FILENAME), W2T(bstrSrc), FALSE ) )
			hr = Error( IDS_ERROR_DECRYPT_COPYDESTINATIONTOSOURCE_FAILED,
						IID_ICrypto, E_FAIL );
		}

		//	Delete the intermediate file
	_unlink( FILE_INTERMEDIATE_FILENAME );

	return hr;
	}


int CCrypto::
LookupCryptErrorStringID( int nLastError ) const
	{
	int nStringID;

	switch( nLastError )
		{
		case ERROR_NOT_ENOUGH_MEMORY:
		case NTE_NO_MEMORY:
			nStringID = IDS_ERROR_OUTOFMEMORY;
			break;
		case NTE_BAD_FLAGS:
			nStringID = IDS_ERROR_INITIALIZE_NTE_BAD_FLAGS;
			break;\
		case NTE_BAD_KEYSET_PARAM:
			nStringID = IDS_ERROR_INITIALIZE_NTE_BAD_KEYSET_PARAM;
			break;
		case NTE_BAD_PROV_TYPE:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_BAD_PROV_TYPE;
			break;
		case NTE_BAD_SIGNATURE:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_BAD_SIGNATURE;
			break;
		case NTE_EXISTS:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_EXISTS;
			break;
		case NTE_KEYSET_ENTRY_BAD:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_KEYSET_ENTRY_BAD;
			break;
		case NTE_KEYSET_NOT_DEF:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_KEYSET_NOT_DEF;
			break;
		case NTE_PROV_DLL_NOT_FOUND:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_PROV_DLL_NOT_FOUND;
			break;
		case NTE_PROV_TYPE_ENTRY_BAD:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_PROV_TYPE_ENTRY_BAD;
			break;
		case NTE_PROV_TYPE_NO_MATCH:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_PROV_TYPE_NO_MATCH;
			break;
		case NTE_PROV_TYPE_NOT_DEF:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_PROV_TYPE_NOT_DEF;
			break;
		case NTE_PROVIDER_DLL_FAIL: 
			nStringID = IDS_ERROR_INITIALIZATION_NTE_PROVIDER_DLL_FAIL;					
			break;
		case NTE_SIGNATURE_FILE_BAD:
			nStringID = IDS_ERROR_INITIALIZATION_NTE_SIGNATURE_FILE_BAD;
			break;
		default:
			nStringID = IDS_UNKNOWN_ERROR;
			break;
		}

	return nStringID;
	}

