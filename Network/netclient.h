#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include "udpclient.h"
#include "tcpclient.h"
#include "http.h"
#include "httpserver.h"
#include "CommonData.h"
#include "../Common/commonfunction.h"

class CNetClient : public QObject
{
    Q_OBJECT
public:
    explicit CNetClient(QObject *parent = 0);
    ~CNetClient( );

    typedef enum __ClientType {
        ClientUDPClient,
        ClientTCPClient,
        ClientHTTPClient,
        ClientHTTPServer
    } ClientType;

public:
    static CNetClient& GetInstance( bool bTcp, bool bToCenterServer, QTextCodec* pCodec = 0, QObject* parent = 0 );
    void PostHttpServerEvent( CHttpEvent::UserEvent nEvent, CHttpEvent::HttpGetResponse* pResponse = NULL );
    void CreateClient( ClientType client, QTextCodec* pCodec, bool bToCenterServer );
    bool SendTableData( QString& strBody, int nRows, int nCols,  NetTransport::eTableType tabType );
    bool SendImageData( const char* pImg, quint32 nImgLen, NetTransport::eImageType imgType,
                        quint32 nParkID, QString& strPlate, QDateTime& datetime );
    bool SendSvrMsgData( NetTransport::eSvrMsg svrType, QString& strBody );
    bool SendCltMsgData( NetTransport::eCltMsg cltType, QStringList& lstParams, QByteArray& byBody );
    bool SendHeartbeatData( QString& strBody, NetTransport::eHeartbeat hbType);
    void HttpClientMethod( QString& strUrl, CHttpServer::HTTP_VERB httpMethod,
                                       QIODevice* pDevData = NULL, QByteArray* pByData = NULL );
    bool SocketSendData( ClientType client, QByteArray& byData );

private:
    bool WaitForReply( QAbstractSocket* pSockect );
    quint16 GetPort( ClientType client, bool bCenterServer = true );
    QString GetIP( ClientType client, bool bCenterServer = true );

private:
    QTextCodec* pTextCodec;
    CUdpClient* udpClient;
    CTcpClient* tcpClient;
    CHttp* httpClient;
    CHttpServer* httpServer;
    ClientType client;
    QSettings* pSettings;
    static CNetClient* clientInst[ CLIENT_INSTANCE ];
    QHostAddress tcpAddr;
    quint16 tcpPort;

signals:
    void Notify( QString strMsg );

public slots:

private slots:
    void HttpError( QString strMsg );
    void HttpVerbs( CHttpServer::HTTP_VERB verb );
    void HttpFreeEntityMemory( CHttpEvent::HttpGetResponse );
    void NotifyMessage( QString strMsg );
};

#endif // NETCLIENT_H
