#include "httpevent.h"
#include <QDebug>

CHttpEvent::CHttpEvent( UserEvent event  ) : QEvent( ( Type ) event )
{
    memset( &sResponse, 0, sizeof ( sResponse ) );
}

void CHttpEvent::SetUrl( QString& strUrl )
{
    this->strUrl = strUrl;
}

QString& CHttpEvent::GetUrl( )
{
    return strUrl;
}

CHttpEvent::~CHttpEvent( )
{
    UserEvent nEvent = ( UserEvent ) type( );
    QString strMsg;

    if ( CHttpEvent::HttpStartup == nEvent ) {
        strMsg = "HttpStartup";
    } else if ( CHttpEvent::HttpCleanup == nEvent ) {
        strMsg = "HttpCleanup";
    } else if ( CHttpEvent::HttpAddListenUrl == nEvent ) {
        strMsg = "HttpAddListenUrl";
     } else if ( CHttpEvent::HttpAddDelistenUrl == nEvent ) {
        strMsg = "HttpAddDelistenUrl";
    } else if ( CHttpEvent::HttpRetrieveRequest == nEvent ) {
        strMsg = "HttpRetrieveRequest";
    } else if ( CHttpEvent::HttpReleaseRequest == nEvent ) {
        strMsg = "HttpReleaseRequest";
    } else if ( CHttpEvent::HttpSendGetResponse == nEvent ) {
        strMsg = "HttpSendGetResponse";
    } else if ( CHttpEvent::HttpSendPostResponse == nEvent ) {
        strMsg = "HttpSendPostResponse";
    }

    qDebug( ) << "~CHttpEvent( ) " << strMsg << endl;
}

void CHttpEvent::SetHttpGetResponse( CHttpEvent::HttpGetResponse& response )
{
    sResponse = response;
}

CHttpEvent::HttpGetResponse& CHttpEvent::GetHttpGetResponse( )
{
    return sResponse;
}
