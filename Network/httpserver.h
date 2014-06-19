#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QThread>
#include <QLibrary>
#include <QTextCodec>
#include "windows.h"
#include "httpevent.h"

class CHttpServer : public QThread
{
    Q_OBJECT
public:
    explicit CHttpServer(QObject *parent = 0);
    ~CHttpServer( );

    typedef enum _HTTP_VERB
    {
        HttpVerbUnparsed,
        HttpVerbUnknown,
        HttpVerbInvalid,
        HttpVerbOPTIONS,
        HttpVerbGET,
        HttpVerbHEAD,
        HttpVerbPOST,
        HttpVerbPUT,
        HttpVerbDELETE,
        HttpVerbTRACE,
        HttpVerbCONNECT,
        HttpVerbTRACK,  // used by Microsoft Cluster Server for a non-logged trace
        HttpVerbMOVE,
        HttpVerbCOPY,
        HttpVerbPROPFIND,
        HttpVerbPROPPATCH,
        HttpVerbMKCOL,
        HttpVerbLOCK,
        HttpVerbUNLOCK,
        HttpVerbSEARCH,

        HttpVerbMaximum

    } HTTP_VERB, *PHTTP_VERB;

    void SetTextCodec( QTextCodec *pCodec );

private:
    typedef WCHAR*  ( WINAPI *GetErrorMessage ) ( );

    typedef  BOOL ( WINAPI *StartupHttp ) ( );
    typedef  BOOL ( WINAPI *CleanupHttp ) ( );

    typedef  BOOL ( WINAPI *AddListenUrl ) ( LPCWSTR pszUrl );
    typedef  BOOL ( WINAPI *AddDelistenUrl ) ( LPCWSTR pszUrl );

    typedef  HANDLE ( WINAPI *RetrieveRequest ) ( HTTP_VERB& httpMethod ); // Get request handle, NULL failed
    typedef  BOOL ( WINAPI *ReleaseRequestHandle ) ( HANDLE hRequest );

    typedef  BOOL ( WINAPI *SendHttpResponse ) ( HANDLE hRequest, USHORT StatusCode, PCSTR pReason, LPVOID pEntity[ ], ULONG lEntityLen[ ], USHORT sEntityCount );

protected:
    void run( );
    void customEvent( QEvent * e );

private:
    void GetFunctionPointer( );

private:
    QLibrary libLoader;

    GetErrorMessage MyGetErrorMessage;
    StartupHttp MyStartupHttp;
    CleanupHttp MyCleanupHttp;
    AddListenUrl MyAddListenUrl;
    AddDelistenUrl MyAddDelistenUrl;
    RetrieveRequest MyRetrieveRequest;
    ReleaseRequestHandle MyReleaseRequestHandle;
    SendHttpResponse MySendHttpResponse;

    HANDLE hRequest;
    QTextCodec* pTextCodec;

signals:
    void error( QString strMsg );
    void HttpVerbs( CHttpServer::HTTP_VERB verb );
    void FreeEntityMemory( CHttpEvent::HttpGetResponse );

public slots:

};

#endif // HTTPSERVER_H
