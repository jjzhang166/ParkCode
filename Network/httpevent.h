#ifndef HTTPEVENT_H
#define HTTPEVENT_H

#include <QEvent>
#include <QString>
#include <windows.h>
#define ENTITY_COUNT ( int ) ( 32 )
#define REASON_SIZE ( int ) ( 512 )

class CHttpEvent : public QEvent
{
public:
    typedef enum __UserEvent {
        HttpStartup = User,
        HttpCleanup,
        HttpAddListenUrl,
        HttpAddDelistenUrl,
        HttpRetrieveRequest ,
        HttpReleaseRequest,
        HttpSendGetResponse,
        HttpSendPostResponse
    } UserEvent ;

    CHttpEvent( UserEvent event );
    ~CHttpEvent( );

    typedef struct __HttpGetResponse {
        USHORT StatusCode;
        char cReason[ REASON_SIZE ];
        LPVOID pEntity[ ENTITY_COUNT ];
        ULONG lEntityLen[ ENTITY_COUNT ];
        USHORT sEntityCount;
    } HttpGetResponse, PHttpGetResponse;

    void SetUrl( QString& strUrl );
    QString& GetUrl( );

    void SetHttpGetResponse( CHttpEvent::HttpGetResponse& response );
    CHttpEvent::HttpGetResponse& GetHttpGetResponse( );

private:
    QString strUrl;
    HttpGetResponse sResponse;
};

#endif // HTTPEVENT_H
