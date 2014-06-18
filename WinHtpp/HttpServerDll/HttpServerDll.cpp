// HttpServerDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HttpServerDll.h"
#include <stdio.h>

#define ERROR_INFO_LEN  ( int ) ( 512 )
#define GET_ERROR_MSG( EXCEPTION_CODE, RET_CODE, ERROR_MSG ) ( EXCEPTION_CODE == RET_CODE ) ? \
			ERROR_MSG : \
			L" Call GetLasterror( ) to get error code."

static WCHAR g_szErrorInfo[ ERROR_INFO_LEN ] = { 0 };
static HANDLE g_hHttpReqQueue = NULL;

WCHAR* WINAPI GetErrorMessage( )
{
	return g_szErrorInfo;
}

BOOL WINAPI StartupHttp( )
{
	BOOL bRet = FALSE;
	HTTPAPI_VERSION httpVer = HTTPAPI_VERSION_1; // xp

    ULONG lRet = HttpInitialize( httpVer, HTTP_INITIALIZE_SERVER, NULL );
	if ( NO_ERROR != lRet ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_INVALID_PARAMETER, lRet, L"The parameter contains an unsupported value." ) );
		SetLastError( lRet );
		return bRet;
	}

    lRet = HttpCreateHttpHandle( &g_hHttpReqQueue, 0 );
	if ( NO_ERROR != lRet ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_DLL_INIT_FAILED, lRet, L"The calling application did not call HttpInitialize before calling this function." ) );
		SetLastError( lRet );
		return bRet;
	}

	bRet = TRUE;

	return bRet;
}

BOOL WINAPI CleanupHttp( )
{
	BOOL bRet = FALSE;
	ULONG lRet = 0;

	if ( NULL == g_hHttpReqQueue ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"Please StartupHttp( )." ) );
		return bRet;
	}

    if ( 0 == CloseHandle( g_hHttpReqQueue ) ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"Close http request queue to fail." ) );
	}

    lRet = HttpTerminate( HTTP_INITIALIZE_SERVER, NULL);
	if ( NO_ERROR != lRet ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_INVALID_PARAMETER, lRet, L"One or more of the supplied parameters is in an unusable form." ) );
		SetLastError( lRet );
		return bRet;
	}

	bRet = TRUE;

    return bRet;

}

BOOL WINAPI AddDelistenUrl( LPCWSTR pszUrl )
{
	BOOL bRet = FALSE;

	if ( NULL == pszUrl ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"The invalided parameter value." ) );
		return bRet;
	}

	if ( NULL == g_hHttpReqQueue ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"Please StartupHttp( )." ) );
		return bRet;
	}

	ULONG lRet = HttpRemoveUrl( g_hHttpReqQueue, pszUrl );
	if ( NO_ERROR != lRet ) {

		switch ( lRet ) {
		case ERROR_ACCESS_DENIED :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_ACCESS_DENIED, lRet, L"The calling application does not have permission to remove the URL." ) );
			break;

		case ERROR_INVALID_PARAMETER :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_INVALID_PARAMETER, lRet, L"One or more of the supplied parameters is in an unusable form." ) );
			break;

		case ERROR_NOT_ENOUGH_MEMORY :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_NOT_ENOUGH_MEMORY, lRet, L"Insufficient resources to complete the operation." ) );
			break;

		case ERROR_FILE_NOT_FOUND :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_FILE_NOT_FOUND, lRet, L"The specified UrlPrefix could not be found in the registration database." ) );
			break;

		default :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( NO_ERROR, lRet, L"" ) );
			break;
		}

		SetLastError( lRet );
		return bRet;
	}

	bRet = TRUE;

	return bRet;
}

BOOL WINAPI AddListenUrl( LPCWSTR pszUrl )
{
	//
	// "http://www.adatum.com:80/vroot/" 
	// "https://adatum.com:443/secure/database/" 
	//

	BOOL bRet = FALSE;

	if ( NULL == pszUrl ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"The invalided parameter value." ) );
		return bRet;
	}

	if ( NULL == g_hHttpReqQueue ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"Please StartupHttp( )." ) );
		return bRet;
	}

	ULONG lRet = HttpAddUrl( g_hHttpReqQueue, pszUrl, NULL );
	if ( NO_ERROR != lRet ) {
		SetLastError( lRet );
		switch ( lRet ) {
		case ERROR_ACCESS_DENIED :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_ACCESS_DENIED, lRet, L"The calling application does not have permission to register the URL." ) );
			break;

		case ERROR_DLL_INIT_FAILED :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_INVALID_PARAMETER, lRet, L"The calling application did not call HttpInitialize before calling this function." ) );
			break;

		case ERROR_INVALID_PARAMETER :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_NOT_ENOUGH_MEMORY, lRet, L"One of the parameters are invalid." ) );
			break;

		case ERROR_ALREADY_EXISTS :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_FILE_NOT_FOUND, lRet, L"The specified UrlPrefix conflicts with an existing registration." ) );
			break;

		case ERROR_NOT_ENOUGH_MEMORY :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_FILE_NOT_FOUND, lRet, L"Insufficient resources to complete the operation." ) );
			break;

		default :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( NO_ERROR, lRet, L"" ) );
			break;
		}

		SetLastError( lRet );
		return bRet;
	}

	bRet = TRUE;

	return bRet;
}

#if FALSE
Request = Request-Line ; Section 5.1
*(( general-header ; Section 4.5
| request-header ; Section 5.3
| entity-header ) CRLF) ; Section 7.1
CRLF
[ message-body ] ; Section 4.3

Response = Status-Line ; Section 6.1
*(( general-header ; Section 4.5
| response-header ; Section 6.2
| entity-header ) CRLF) ; Section 7.1
CRLF
[ message-body ] ; Section 7.2
#endif

BOOL WINAPI SendHttpResponse( HANDLE hRequest, USHORT StatusCode, PCSTR pReason, LPVOID pEntity[ ], ULONG lEntityLen[ ], USHORT sEntityCount )
{
	BOOL bRet = FALSE;
	ULONG lRet = 0;
	ULONG lSent = 0;
	HTTP_RESPONSE response;
	PHTTP_REQUEST pRequest = ( PHTTP_REQUEST ) hRequest;

	if ( NULL == g_hHttpReqQueue ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"Please StartupHttp( )." ) );
		return bRet;
	}

	if ( NULL == pRequest || NULL == pReason || NULL ==pEntity || NULL == lEntityLen ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"Invalided parameter." ) );
		return bRet;
	}

   
    PHTTP_DATA_CHUNK pChunk = new HTTP_DATA_CHUNK[ sEntityCount ];
   

    INITIALIZE_HTTP_RESPONSE( &response, StatusCode, pReason );
    ADD_KNOWN_HEADER( response, HttpHeaderContentType, "text/html" );
   
	for ( USHORT sIndex = 0; sIndex < sEntityCount; sIndex++ ) { 
		pChunk[ sIndex ].DataChunkType           = HttpDataChunkFromMemory;
		pChunk[ sIndex ].FromMemory.pBuffer      = pEntity[ sIndex ];
		pChunk[ sIndex ].FromMemory.BufferLength = lEntityLen[ sIndex ];
	}

    response.EntityChunkCount = sEntityCount;
    response.pEntityChunks = pChunk;

	//
	// HttpSendResponseEntityBody( ) to send body
	//
    lRet = HttpSendHttpResponse( g_hHttpReqQueue, pRequest->RequestId, 0, &response, NULL, &lSent, NULL, 0, NULL, NULL ); 

	if ( NULL != pChunk ) {
		delete [ ] pChunk;
		pChunk = NULL;
	}

	if ( NO_ERROR != lRet ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_INVALID_PARAMETER, lRet, L"One or more of the supplied parameters is in an unusable form." ) );
		SetLastError( lRet );
		return bRet;
	}

	bRet = TRUE;

    return bRet;
}

#define MAX_ULONG_STR ((ULONG) sizeof("4294967295"))

BOOL SendHttpPostResponse( HANDLE hRequest )
{
	BOOL bRet = FALSE;
	ULONG lRet = 0;
    HTTP_RESPONSE   response;
    DWORD           result;
    DWORD           bytesSent;
    PUCHAR          pEntityBuffer;
    ULONG           EntityBufferLength;
    ULONG           BytesRead;
    ULONG           TempFileBytesWritten;
    HANDLE          hTempFile;
    TCHAR           szTempName[MAX_PATH + 1];
    CHAR            szContentLength[MAX_ULONG_STR];
    HTTP_DATA_CHUNK dataChunk;
    ULONG           TotalBytesRead = 0;
	PHTTP_REQUEST pRequest = ( PHTTP_REQUEST ) hRequest;

    BytesRead  = 0;
    hTempFile  = INVALID_HANDLE_VALUE;

	if ( NULL == g_hHttpReqQueue ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"Please StartupHttp( )." ) );
		return bRet;
	}

    //
    // Allocate space for an entity buffer. Buffer can be increased 
    // on demand.
    //
    EntityBufferLength = 2048;
    pEntityBuffer      = (PUCHAR) ALLOC_MEM( EntityBufferLength );

    if (pEntityBuffer == NULL)
    {
        result = ERROR_NOT_ENOUGH_MEMORY;
        wprintf(L"Insufficient resources \n");
        goto Done;
    }

    //
    // Initialize the HTTP response structure.
    //
    INITIALIZE_HTTP_RESPONSE(&response, 200, "OK");

    //
    // For POST, echo back the entity from the
    // client
    //
    // NOTE: If the HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY flag had been
    //       passed with HttpReceiveHttpRequest(), the entity would 
    //       have been a part of HTTP_REQUEST (using the pEntityChunks
    //       field). Because that flag was not passed, there are no
    //       o entity bodies in HTTP_REQUEST.
    //
   
    if(pRequest->Flags & HTTP_REQUEST_FLAG_MORE_ENTITY_BODY_EXISTS)
    {
        // The entity body is sent over multiple calls. Collect 
        // these in a file and send back. Create a temporary 
        // file.
        //

        if(GetTempFileName(
                L".", 
                L"New", 
                0, 
                szTempName
                ) == 0)
        {
            result = GetLastError();
            wprintf(L"GetTempFileName failed with %lu \n", result);
            goto Done;
        }

        hTempFile = CreateFile(
                        szTempName,
                        GENERIC_READ | GENERIC_WRITE, 
                        0,                  // Do not share.
                        NULL,               // No security descriptor.
                        CREATE_ALWAYS,      // Overrwrite existing.
                        FILE_ATTRIBUTE_NORMAL,    // Normal file.
                        NULL
                        );

        if(hTempFile == INVALID_HANDLE_VALUE)
        {
            result = GetLastError();
            wprintf(L"Cannot create temporary file. Error %lu \n",
                     result);
            goto Done;
        }

        do
        {
            //
            // Read the entity chunk from the request.
            //
            BytesRead = 0; 
            result = HttpReceiveRequestEntityBody(
                        g_hHttpReqQueue,
                        pRequest->RequestId,
                        0,
                        pEntityBuffer,
                        EntityBufferLength,
                        &BytesRead,
                        NULL 
                        );

            switch(result)
            {
                case NO_ERROR:

                    if(BytesRead != 0)
                    {
                        TotalBytesRead += BytesRead;
                        WriteFile(
                                hTempFile, 
                                pEntityBuffer, 
                                BytesRead,
                                &TempFileBytesWritten,
                                NULL
                                );
                    }
                    break;

                case ERROR_HANDLE_EOF:

                    //
                    // The last request entity body has been read.
                    // Send back a response. 
                    //
                    // To illustrate entity sends via 
                    // HttpSendResponseEntityBody, the response will 
                    // be sent over multiple calls. To do this,
                    // pass the HTTP_SEND_RESPONSE_FLAG_MORE_DATA
                    // flag.
                    
                    if(BytesRead != 0)
                    {
                        TotalBytesRead += BytesRead;
                        WriteFile(
                                hTempFile, 
                                pEntityBuffer, 
                                BytesRead,
                                &TempFileBytesWritten,
                                NULL
                                );
                    }

                    //
                    // Because the response is sent over multiple
                    // API calls, add a content-length.
                    //
                    // Alternatively, the response could have been
                    // sent using chunked transfer encoding, by  
                    // passimg "Transfer-Encoding: Chunked".
                    //

                    // NOTE: Because the TotalBytesread in a ULONG
                    //       are accumulated, this will not work
                    //       for entity bodies larger than 4 GB. 
                    //       For support of large entity bodies,
                    //       use a ULONGLONG.
                    // 

                  
                    sprintf_s(szContentLength, MAX_ULONG_STR, "%lu", TotalBytesRead);

                    ADD_KNOWN_HEADER(
                            response, 
                            HttpHeaderContentLength, 
                            szContentLength
                            );

                    result = 
                        HttpSendHttpResponse(
                               g_hHttpReqQueue,           // ReqQueueHandle
                               pRequest->RequestId, // Request ID
                               HTTP_SEND_RESPONSE_FLAG_MORE_DATA,
                               &response,       // HTTP response
                               NULL,            // pReserved1
                               &bytesSent,      // bytes sent-optional
                               NULL,            // pReserved2
                               0,               // Reserved3
                               NULL,            // LPOVERLAPPED
                               NULL             // pReserved4
                               );

                    if(result != NO_ERROR)
                    {
                        wprintf(
                           L"HttpSendHttpResponse failed with %lu \n", 
                           result
                           );
                        goto Done;
                    }

                    //
                    // Send entity body from a file handle.
                    //
                    dataChunk.DataChunkType = HttpDataChunkFromFileHandle;
                    dataChunk.FromFileHandle.ByteRange.StartingOffset.QuadPart = 0;
                    dataChunk.FromFileHandle.ByteRange.Length.QuadPart = HTTP_BYTE_RANGE_TO_EOF;
                    dataChunk.FromFileHandle.FileHandle = hTempFile;

                    result = HttpSendResponseEntityBody( g_hHttpReqQueue, pRequest->RequestId,
                                0,           // This is the last send.
                                1,           // Entity Chunk Count.
                                &dataChunk,
                                NULL,
                                NULL,
                                0,
                                NULL,
                                NULL
                                );

                    if(result != NO_ERROR)
                    {
                       wprintf(
                          L"HttpSendResponseEntityBody failed %lu\n", 
                          result
                          );
                    }

                    goto Done;

                    break;
                       

                default:
                  wprintf( 
                   L"HttpReceiveRequestEntityBody failed with %lu \n", 
                   result);
                  goto Done;
            }

        } while(TRUE);
    }
    else
    {
        // This request does not have an entity body.
        //
        
        result = HttpSendHttpResponse( g_hHttpReqQueue, pRequest->RequestId,
                   0,
                   &response,           // HTTP response
                   NULL,                // pReserved1
                   &bytesSent,          // bytes sent (optional)
                   NULL,                // pReserved2
                   0,                   // Reserved3
                   NULL,                // LPOVERLAPPED
                   NULL                 // pReserved4
                   );
        if(result != NO_ERROR)
        {
            wprintf(L"HttpSendHttpResponse failed with %lu \n",
                    result);
        }
    }

Done:

    if(pEntityBuffer)
    {
        FREE_MEM(pEntityBuffer);
    }

    if(INVALID_HANDLE_VALUE != hTempFile)
    {
        CloseHandle(hTempFile);
        DeleteFile(szTempName);
    }

    return result;
}

BOOL WINAPI ReleaseRequestHandle( HANDLE hRequest )
{
	BOOL bRet = FALSE;

	if ( NULL == hRequest ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"The parameter contains an unsupported value." ) );
		return bRet;
	}

	FREE_MEM( hRequest );

	bRet = TRUE;

	return bRet;
}

// Qt startup a thread to monitor. request
HANDLE WINAPI RetrieveRequest( HTTP_VERB& httpMethod )
{
	HANDLE hRequest = NULL;
	ULONG lReqBufLen = 0;
	PCHAR pRequestBuffer = NULL;
	PHTTP_REQUEST pRequest = NULL;
	HTTP_REQUEST_ID reqId;
	ULONG lRet = 0;
	DWORD dwRead = 0;

	if ( NULL == g_hHttpReqQueue ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"Please StartupHttp( )." ) );
		return hRequest;
	}

	lReqBufLen = sizeof( HTTP_REQUEST ) + 2048;
    pRequestBuffer  = ( PCHAR ) ALLOC_MEM( lReqBufLen );

    if ( NULL == pRequestBuffer ) {
		wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( 0, 0, L"ALLOC_MEM( ) to fail." ) );
        return hRequest;
    }

    pRequest = ( PHTTP_REQUEST ) pRequestBuffer;
	HTTP_SET_NULL_ID( &reqId );

PROCESSFAILURE:

	RtlZeroMemory( pRequest, lReqBufLen );
	//
	// Flags is HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY HTTP_RECEIVE_REQUEST_FLAG_FLUSH_BODY to get request body
	//  HttpReceiveRequestEntityBody( ) to get body
	//
	lRet = HttpReceiveHttpRequest( g_hHttpReqQueue, reqId, 0, pRequest, lReqBufLen, &dwRead, NULL ); // Block
	
	if ( NO_ERROR != lRet ) {
		switch ( lRet ) {
		case ERROR_INVALID_PARAMETER :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_ACCESS_DENIED, lRet, L"One or more of the supplied parameters is in an unusable form." ) );
			break;

		case ERROR_NOACCESS :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_INVALID_PARAMETER, lRet, L"One or more of the supplied parameters points to an invalid or unaligned memory buffer." ) );
			break;

		case ERROR_HANDLE_EOF :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( ERROR_FILE_NOT_FOUND, lRet, L"The specified request has already been completely retrieved." ) );
			break;

		case ERROR_MORE_DATA :
			FREE_MEM( pRequest );
			lReqBufLen = dwRead;
			pRequestBuffer  = ( PCHAR ) ALLOC_MEM( lReqBufLen );
			pRequest = ( PHTTP_REQUEST ) pRequestBuffer;
			goto PROCESSFAILURE;
			break;

		default :
			wcscpy_s( g_szErrorInfo, GET_ERROR_MSG( NO_ERROR, lRet, L"" ) );
			break;
		}

		FREE_MEM( pRequest );

		SetLastError( lRet );
		return hRequest;
	}

	hRequest = ( HANDLE ) pRequest;
	httpMethod = pRequest->Verb;

	return hRequest;
}