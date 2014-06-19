#include "httpserver.h"
#include <QDebug>
#include <QMetaType>

#define FunctionExist( strMsg, MyFunction )    if ( NULL == MyFunction ) { \
                                                        emit error(  QString( strMsg ) + "( ) not exist." );\
                                                        return;\
                                                    }
#define EmitMessage( )    if ( !bRet ) {\
                                            strMsg = QString::fromWCharArray( MyGetErrorMessage( ) );\
                                            emit error( strMsg );\
                                        }

CHttpServer::CHttpServer(QObject *parent) :
    QThread(parent)
{
    qRegisterMetaType< CHttpServer::HTTP_VERB >( "CHttpServer::HTTP_VERB" );
    qRegisterMetaType< CHttpEvent::HttpGetResponse >( "CHttpEvent::HttpGetResponse" );
    GetFunctionPointer( );
}

CHttpServer::~CHttpServer( )
{
}

void CHttpServer::SetTextCodec( QTextCodec *pCodec )
{
    pTextCodec = pCodec;
}

void CHttpServer::GetFunctionPointer( )
{
    MyGetErrorMessage = NULL;
    MyStartupHttp = NULL;
    MyCleanupHttp = NULL;
    MyAddListenUrl = NULL;
    MyAddDelistenUrl = NULL;
    MyRetrieveRequest = NULL;
    MyReleaseRequestHandle = NULL;
    MySendHttpResponse = NULL;

    hRequest = NULL;

    QString strFile = "HttpServerDll.dll";
    libLoader.setFileName( strFile );
    if ( !libLoader.load( ) ) {
        strFile = libLoader.errorString( );
        qDebug( ) << strFile << endl;
        return;
    }

    MyGetErrorMessage = ( GetErrorMessage ) libLoader.resolve( "GetErrorMessage" );
    MyStartupHttp = ( StartupHttp ) libLoader.resolve( "StartupHttp" );
    MyCleanupHttp = ( CleanupHttp ) libLoader.resolve( "CleanupHttp" );
    MyAddListenUrl = ( AddListenUrl ) libLoader.resolve( "AddListenUrl" );
    MyAddDelistenUrl = ( AddDelistenUrl ) libLoader.resolve( "AddDelistenUrl" );
    MyRetrieveRequest = ( RetrieveRequest ) libLoader.resolve( "RetrieveRequest" );
    MyReleaseRequestHandle = ( ReleaseRequestHandle ) libLoader.resolve( "ReleaseRequestHandle" );
    MySendHttpResponse = ( SendHttpResponse ) libLoader.resolve( "SendHttpResponse" );
}

void CHttpServer::run( )
{
    FunctionExist( "GetErrorMessage", MyGetErrorMessage );
    exec( ); // Enter event loop
}

void CHttpServer::customEvent( QEvent *e )
{
    BOOL bRet = FALSE;
    HTTP_VERB httpMethod;
    LPCWSTR pUrl = NULL;
    QString strMsg = "";

    CHttpEvent& httpEvent = *( CHttpEvent* ) e;
    CHttpEvent::HttpGetResponse& httpResponse = httpEvent.GetHttpGetResponse( );
    pUrl = ( LPCWSTR ) httpEvent.GetUrl( ).utf16( );
    CHttpEvent::UserEvent nEvent =  ( CHttpEvent::UserEvent ) httpEvent.type( );
    //QString strUrl = QString::fromWCharArray( pUrl );

    if ( CHttpEvent::HttpStartup == nEvent ) {
        FunctionExist( "StartupHttp", MyStartupHttp );
        bRet = MyStartupHttp( );
        EmitMessage( );
    } else if ( CHttpEvent::HttpCleanup == nEvent ) {
        FunctionExist( "CleanupHttp", MyCleanupHttp );
        bRet = MyCleanupHttp( );
        EmitMessage( );
    } else if ( CHttpEvent::HttpAddListenUrl == nEvent ) {
        FunctionExist( "AddListenUrl", MyAddListenUrl );
        bRet = MyAddListenUrl( pUrl );
        EmitMessage( );
     } else if ( CHttpEvent::HttpAddDelistenUrl == nEvent ) {
        FunctionExist( "AddDelistenUrl", MyAddDelistenUrl );
        bRet = MyAddDelistenUrl(  pUrl );
        EmitMessage( );
    } else if ( CHttpEvent::HttpRetrieveRequest == nEvent ) {
        FunctionExist( "RetrieveRequest", MyRetrieveRequest );
        hRequest = MyRetrieveRequest( httpMethod );
        bRet = ( NULL != hRequest );
        EmitMessage( );
        emit HttpVerbs( httpMethod );
    } else if ( CHttpEvent::HttpReleaseRequest == nEvent ) {
        FunctionExist( "ReleaseRequestHandle", MyReleaseRequestHandle );
        bRet = MyReleaseRequestHandle( hRequest );
        EmitMessage( );
    } else if ( CHttpEvent::HttpSendGetResponse == nEvent ) {
        FunctionExist( "SendHttpResponse", MySendHttpResponse );
        bRet = MySendHttpResponse( hRequest, httpResponse.StatusCode,
                                                      httpResponse.cReason, httpResponse.pEntity,
                                                      httpResponse.lEntityLen, httpResponse.sEntityCount );
        emit FreeEntityMemory( httpResponse );
        EmitMessage( );
    } else if ( CHttpEvent::HttpSendPostResponse == nEvent ) {
        //FunctionExist( "GetErrorMessage" );
    }
}
