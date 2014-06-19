#include "netclient.h"
#include <QtGui/QApplication>

CNetClient* CNetClient::clientInst[ CLIENT_INSTANCE ] = { 0 };

CNetClient::CNetClient(QObject *parent) :
    QObject(parent)
{
    pTextCodec = NULL;
    udpClient = NULL;
    tcpClient = NULL;
    httpClient = NULL;
    httpServer = NULL;

    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    client  = ClientUDPClient;
}

CNetClient::~CNetClient( )
{
    if  ( NULL != httpServer  ) {
        if ( httpServer->isRunning( ) ) {
            httpServer->terminate( );
        }

        delete httpServer;
        httpServer = NULL;
    }

    if ( NULL != udpClient ) {
        delete udpClient;
        udpClient = NULL;
    }

    if ( NULL != tcpClient ) {
        delete tcpClient;
        tcpClient = NULL;
    }

    if ( NULL != httpClient ) {
        delete httpClient;
        httpClient = NULL;
    }
}

CNetClient& CNetClient::GetInstance( bool bTcp, bool bToCenterServer, QTextCodec* pCodec, QObject* parent )
{
    CNetClient** pInst = &clientInst[ bTcp ];

    if ( NULL == *pInst ) {
        *pInst = new CNetClient( parent );
        ( *pInst )->CreateClient( bTcp ? ClientTCPClient : ClientUDPClient, pCodec, bToCenterServer );
    }

    return **pInst;
}

quint16 CNetClient::GetPort( ClientType client, bool bCenterServer )
{
    quint16 nPort = 0;
    QString strKey = ( bCenterServer ? "CenterServer/%1" : "Database/%1" );

    switch ( client ) {
    case ClientUDPClient :
        nPort = pSettings->value( strKey.arg( "UdpPort" ), UDP_DISPATCHER_PORT ).toUInt( );
        break;

    case ClientTCPClient :
        nPort = pSettings->value( strKey.arg( "TcpPort" ), TCP_DISPATCHER_PORT ).toUInt( );
        break;

    case ClientHTTPServer :
        nPort = pSettings->value( "CenterServer/HttpPort", HTTP_DISPATCHER_PORT ).toUInt( );
        break;

    case ClientHTTPClient :
        break;
    }

    return nPort;
}

QString CNetClient::GetIP( ClientType client, bool bCenterServer )
{
    QString strIP = "";
    QString strDefault = "127.0.0.1";
    QString strKey = ( bCenterServer ? "CenterServer/%1" : "Database/Agent" );

    switch ( client ) {
    case ClientUDPClient :
        if ( bCenterServer ) {
            strKey  = strKey.arg( "UdpIP" );
        }
        strIP = pSettings->value( strKey, strDefault ).toString( );
        break;

    case ClientTCPClient :
        if ( bCenterServer ) {
            strKey  = strKey.arg( "TcpIP" );
        }
        strIP = pSettings->value( strKey, strDefault ).toString( );
        break;

    case ClientHTTPServer :
        strIP = pSettings->value( "CenterServer/HttpIP", strDefault ).toString( );
        break;

    case ClientHTTPClient :
        break;
    }

    qDebug( ) << strIP << endl;

    return strIP;
}

void CNetClient::CreateClient( ClientType client, QTextCodec* pCodec, bool bToCenterServer  )
{
    this->client = client;
    pTextCodec = pCodec;

    switch ( client ) {
    case ClientUDPClient:
        udpClient = new CUdpClient( this );
        udpClient->SetTextCodec( pCodec );

        connect( udpClient, SIGNAL( NotifyMessage( QString ) ), this, SLOT( NotifyMessage( QString ) ) );
        udpClient->Connect2Server( QHostAddress( GetIP( client, bToCenterServer ) ), GetPort( client, bToCenterServer ) );
        break;

    case ClientTCPClient:
        tcpClient = new CTcpClient( this );
        tcpClient->SetTextCodec( pCodec );

        connect( tcpClient, SIGNAL( NotifyMessage( QString ) ), this, SLOT( NotifyMessage( QString ) ) );
        tcpAddr = QHostAddress( GetIP( client, bToCenterServer ) );
        tcpPort = GetPort( client, bToCenterServer ) ;
        tcpClient->Connect2Server( tcpAddr, tcpPort );
        break;

    case ClientHTTPClient:
        httpClient = new CHttp( this );
        httpClient->SetTextCodec( pCodec );

        connect( httpClient, SIGNAL( NotifyMessage( QString ) ), this, SLOT( NotifyMessage( QString ) ) );
        break;

    case ClientHTTPServer:
        httpServer = new CHttpServer( this );
        httpServer->SetTextCodec( pCodec );

        connect( httpServer, SIGNAL( error( QString  ) ), this, SLOT( HttpError( QString ) ) );
        connect( httpServer, SIGNAL( HttpVerbs( CHttpServer::HTTP_VERB  ) ),
                                                        this, SLOT( HttpVerbs( CHttpServer::HTTP_VERB ) ) );
        connect( httpServer, SIGNAL( FreeEntityMemory( CHttpEvent::HttpGetResponse ) ),
                                                        this, SLOT( HttpFreeEntityMemory( CHttpEvent::HttpGetResponse ) ) );
        break;
    }
}

void CNetClient::NotifyMessage( QString strMsg )
{
    emit Notify( strMsg );
}

void CNetClient::HttpError( QString strMsg )
{
    emit Notify( strMsg );
}

void CNetClient::HttpVerbs( CHttpServer::HTTP_VERB verb )
{

    QFile file( "d:/testhttp.html" );
    bool bRet = file.open( QIODevice::ReadWrite );
    if ( !bRet ) {
        return;
    }

    HANDLE hHeap = ::GetProcessHeap( );
    quint64 lSize = file.size();
    PCHAR pData = ( PCHAR ) ::HeapAlloc( hHeap, HEAP_ZERO_MEMORY, ( DWORD ) lSize );
    lSize = file.read( pData, lSize);
    file.close( );

    CHttpEvent::HttpGetResponse response;
    memset( &response, 0, sizeof ( response ) );
    response.StatusCode = 200;
    strcpy( response.cReason, "OK!" );
    response.sEntityCount = 1;
    response.lEntityLen[ 0 ] = ( ULONG ) lSize;
    response.pEntity[ 0 ] = pData;

    if ( CHttpServer::HttpVerbGET == verb ) {
        PostHttpServerEvent( CHttpEvent::HttpSendGetResponse, &response );
    }
}

void CNetClient::HttpFreeEntityMemory( CHttpEvent::HttpGetResponse response )
{
    HANDLE hHeap = ::GetProcessHeap( );
    BOOL bRet =  FALSE;

    for ( int nIndex = 0; nIndex < response.sEntityCount; nIndex++ ) {
        LPVOID pData = response.pEntity[ nIndex ];
        bRet = ::HeapFree( hHeap, 0, pData );
    }

    PostHttpServerEvent( CHttpEvent::HttpReleaseRequest );
}

bool CNetClient::WaitForReply( QAbstractSocket *pSockect )
{
    bool bRet = false;
    if ( NULL == pSockect ) {
        return bRet;
    }

    QByteArray byReply;

    bRet = pSockect->waitForReadyRead( );
    if ( bRet ) {
        byReply = pSockect->readAll( );
        bRet = ( 0 == strcmp( byReply.data( ), HANDSHAKE ) );
    }

    NotifyMessage( QString( bRet ? "Send successfully." : "Send unsuccessfully." ) );

    return bRet;
}

bool CNetClient::SocketSendData(ClientType client, QByteArray& byData )
{
    QByteArray byToken = QString( "FutureInternet" ).toAscii( );
    qint32 nDataLen = sizeof ( quint32 );
    quint32 nTotal = byToken.length( ) + nDataLen + byData.length( );
    nTotal = htonl( nTotal );

    const char* pTotal = ( const char* ) &nTotal;

    byData.insert( 0, pTotal, nDataLen );
    byData.insert( 0, byToken );

    bool bRet = false;
    quint64 nRetSize = 0;
try {
    switch ( client ) {
    case ClientUDPClient:
        if ( NULL != udpClient ) {
            nRetSize = udpClient->SendData( byData );
            udpClient->flush( );
            udpClient->waitForBytesWritten( );
            //bRet = WaitForReply( udpClient );
            bRet = true;
        }
        break;

    case ClientTCPClient:
        if ( NULL != tcpClient ) {
            QAbstractSocket::SocketState state = tcpClient->state( );

            if ( QAbstractSocket::ConnectedState != state ) {
                break;//tcpClient->Connect2Server( tcpAddr, tcpPort );
            }

            //state = tcpClient->state( );
            nRetSize = tcpClient->SendData( byData );
            tcpClient->flush( );
            tcpClient->waitForBytesWritten( );
            bRet = WaitForReply( tcpClient );
        }
        break;

    case ClientHTTPClient:
        bRet = true;
        break;

    case ClientHTTPServer:
        bRet = true;
        break;
    }
    } catch ( ... ) {
        int n = 0;
        n++;
    }

    return bRet;
}

void CNetClient::HttpClientMethod( QString &strUrl, CHttpServer::HTTP_VERB httpMethod,
                                                     QIODevice *pDevData, QByteArray *pByData )
{
    if ( CHttpServer::HttpVerbGET == httpMethod ) {
        httpClient->HttpGet( strUrl );
    } else if ( CHttpServer::HttpVerbPUT == httpMethod ) {
        if ( NULL != pDevData ) {
            httpClient->HttpPut( strUrl, pDevData );
        } else if ( NULL != pByData ) {
            httpClient->HttpPut( strUrl, *pByData );
        }
    } else if ( CHttpServer::HttpVerbPOST == httpMethod ) {
        if ( NULL != pDevData ) {
            httpClient->HttpPost( strUrl, pDevData );
        } else if ( NULL != pByData ) {
            httpClient->HttpPost( strUrl, *pByData );
        }
    } else if ( CHttpServer::HttpVerbDELETE == httpMethod ) {
        httpClient->HttpDelete( strUrl );
    } else if ( CHttpServer::HttpVerbHEAD == httpMethod ) {
        httpClient->HttpHead( strUrl );
    }
}

bool CNetClient::SendHeartbeatData( QString &strBody, NetTransport::eHeartbeat hbType )
{
    NetTransport::DispatcherData data;
    memset( &data, 0, sizeof ( data ) );

    data.CommHeader.dgType.PacketHeartbeat = 1;
    quint16* pType = ( quint16* ) &data.auxHeader.hbHeader.hbType;
    *pType = ( quint16 ) ( 1 << ( quint16 ) hbType );

    QByteArray byData;
    byData.append( pTextCodec->fromUnicode( strBody ) );

    int nCommHeader = sizeof ( data.CommHeader );
    int nAuxHeader = sizeof ( data.auxHeader.hbHeader );
    data.CommHeader.nDataLen = byData.count( ) + nCommHeader + nAuxHeader;

    byData.insert( 0, ( char* ) &data.auxHeader.hbHeader, nAuxHeader );
    byData.insert( 0, ( char* ) &data.CommHeader, nCommHeader );

    return SocketSendData( client, byData );
}

bool CNetClient::SendTableData( QString &strBody, int nRows, int nCols, NetTransport::eTableType tabType )
{
    NetTransport::DispatcherData data;
    memset( &data, 0, sizeof ( data ) );

    data.CommHeader.dgType.PacketTable = 1;
    data.auxHeader.tabHeader.nRows = nRows;
    data.auxHeader.tabHeader.nCols = nCols;
    quint16* pType = ( quint16* ) &data.auxHeader.tabHeader.tabType;
    *pType = ( quint16 ) ( 1 << ( quint16 ) tabType );

    QByteArray byData;
    byData.append( pTextCodec->fromUnicode( strBody ) );

    int nCommHeader = sizeof ( data.CommHeader );
    int nAuxHeader = sizeof ( data.auxHeader.tabHeader );
    data.CommHeader.nDataLen = byData.count( ) + nCommHeader + nAuxHeader;

    byData.insert( 0, ( char* ) &data.auxHeader.tabHeader, nAuxHeader );
    byData.insert( 0, ( char* ) &data.CommHeader, nCommHeader );

    return SocketSendData( client, byData );
}

bool CNetClient::SendImageData( const char *pImg, quint32 nImgLen, NetTransport::eImageType imgType,
                                quint32 nParkID, QString& strPlate, QDateTime& datetime )
{
    NetTransport::DispatcherData data;
    memset( &data, 0, sizeof ( data ) );

    data.CommHeader.dgType.PacketImage = 1;
    data.auxHeader.imgHeader.nParkID = nParkID;
    data.auxHeader.imgHeader.nImgSize = nImgLen;
    QByteArray byPlate = pTextCodec->fromUnicode( strPlate );
    strcpy( data.auxHeader.imgHeader.cPlate, byPlate.data( ) );
    data.auxHeader.imgHeader.nMSecsSinceEpoch = datetime.toMSecsSinceEpoch( );
    quint16* pType = ( quint16* ) &data.auxHeader.imgHeader.imgType;
    *pType = ( quint16 ) ( 1 << ( quint16 ) imgType );

    QByteArray byData;
    byData.append( pImg, nImgLen );

    int nCommHeader = sizeof ( data.CommHeader );
    int nAuxHeader = sizeof ( data.auxHeader.imgHeader );
    data.CommHeader.nDataLen = nImgLen + nCommHeader + nAuxHeader;

    byData.insert( 0, ( char* ) &data.auxHeader.imgHeader, nAuxHeader );
    byData.insert( 0, ( char* ) &data.CommHeader, nCommHeader );

    return SocketSendData( client, byData );
}

bool CNetClient::SendCltMsgData( NetTransport::eCltMsg cltType, QStringList &lstParams, QByteArray &byBody )
{
    NetTransport::DispatcherData data;
    memset( &data, 0, sizeof ( data ) );

    quint16* pType = NULL;
    data.CommHeader.dgType.PacketCltMsg = 1;
    int nCommHeader = sizeof ( data.CommHeader );
    int nAuxThirdHeader = 0;
    int nAuxCltHeader = sizeof ( data.auxHeader.cltHeader );
    int nBodySize = byBody.count( );

    switch ( cltType ) {
    case NetTransport::CltImg :
        {
#if false
            lstParams << QString::number( bEnter ? NetTransport::ImgIn : NetTransport::ImgOut )
                           << strParkID
                           << strCardNo
                           << strPlate
                           << QString::number( dtCurrent.toMSecsSinceEpoch( ) );
#endif
            nAuxThirdHeader = sizeof ( data.auxHeader.imgHeader );

            NetTransport::eImageType imgType =  ( NetTransport::eImageType  ) lstParams[ 0 ].toInt( );
            quint64 nParkID = lstParams[ 1 ].toULongLong( );
            quint32 nCardID = lstParams[ 2 ].toUInt( );
            QString& strPlate = lstParams[ 3 ];
            quint64 nMSecsSinceEpoch = lstParams[ 4 ].toULongLong( );

            data.auxHeader.imgHeader.nParkID = nParkID;
            data.auxHeader.imgHeader.nCardID = nCardID;
            data.auxHeader.imgHeader.nImgSize = nBodySize;
            QByteArray byPlate = pTextCodec->fromUnicode( strPlate );
            strcpy( data.auxHeader.imgHeader.cPlate, byPlate.data( ) );
            data.auxHeader.imgHeader.nMSecsSinceEpoch = nMSecsSinceEpoch;
            pType = ( quint16* ) &data.auxHeader.imgHeader.imgType;
            *pType = ( quint16 ) ( 1 << ( quint16 ) imgType );
            byBody.insert( 0, ( char* ) &data.auxHeader.imgHeader, nAuxThirdHeader );
        }
        break;

    case NetTransport::CltTable :
        nAuxThirdHeader = sizeof ( data.auxHeader.tabHeader );
        break;

    case NetTransport::CltHeartbeat :
        nAuxThirdHeader = sizeof ( data.auxHeader.hbHeader );

        NetTransport::eHeartbeat hbType =  ( NetTransport::eHeartbeat  ) lstParams[ 0 ].toInt( );
        pType = ( quint16* ) &data.auxHeader.hbHeader.hbType;
        *pType = ( quint16 ) ( 1 << ( quint16 ) hbType );
        byBody.insert( 0, ( char* ) &data.auxHeader.hbHeader, nAuxThirdHeader );
        break;
    }

    data.CommHeader.nDataLen = nBodySize + nCommHeader + nAuxThirdHeader + nAuxCltHeader;
    pType = ( quint16* ) &data.auxHeader.cltHeader.cltMsgType;
    *pType = ( quint16 ) ( 1 << ( quint16 ) cltType );
    byBody.insert( 0, ( char* ) &data.auxHeader.cltHeader, nAuxCltHeader );
    byBody.insert( 0, ( char* ) &data.CommHeader, nCommHeader );

    return SocketSendData( client, byBody );
}

bool CNetClient::SendSvrMsgData( NetTransport::eSvrMsg svrType, QString& strBody )
{
    NetTransport::DispatcherData data;
    memset( &data, 0, sizeof ( data ) );

    data.CommHeader.dgType.PacketSvrMsg = 1;
    quint16* pType = ( quint16* ) &data.auxHeader.svrHeader.svrMsgType;
    *pType = ( quint16 ) ( 1 << ( quint16 ) svrType );

    QByteArray byData = pTextCodec->fromUnicode( strBody );

    int nCommHeader = sizeof ( data.CommHeader );
    int nAuxHeader = sizeof ( data.auxHeader.svrHeader );
    data.CommHeader.nDataLen = byData.count( ) + nCommHeader + nAuxHeader;

    byData.insert( 0, ( char* ) &data.auxHeader.imgHeader, nAuxHeader );
    byData.insert( 0, ( char* ) &data.CommHeader, nCommHeader );

    return SocketSendData( client, byData );
}

void CNetClient::PostHttpServerEvent( CHttpEvent::UserEvent nEvent, CHttpEvent::HttpGetResponse* pResponse )
{
    if ( NULL == httpServer ) {
        return;
    }

    CHttpEvent* pEvent = new CHttpEvent( nEvent );
#ifndef QT_NO_DEBUG
    QString strMsg;
#endif
    QString strUrl = "http://127.0.0.1:80/";

    switch ( nEvent ) {
    case CHttpEvent::HttpStartup :
        httpServer->start( );
        httpServer->moveToThread( httpServer );
#ifndef QT_NO_DEBUG
        strMsg = "Event HttpStartup";
#endif
        break;
    case CHttpEvent::HttpCleanup :
        httpServer->exit( );
#ifndef QT_NO_DEBUG
        strMsg = "Event HttpCleanup";
#endif
        break;
    case CHttpEvent::HttpAddListenUrl :
        pEvent->SetUrl( strUrl );
#ifndef QT_NO_DEBUG
        strMsg = "Event HttpAddListenUrl";
#endif
        break;
    case CHttpEvent::HttpAddDelistenUrl :
        pEvent->SetUrl( strUrl );
#ifndef QT_NO_DEBUG
        strMsg = "Event HttpAddDelistenUrl";
#endif
        break;
    case CHttpEvent::HttpRetrieveRequest :
#ifndef QT_NO_DEBUG
        strMsg = "Event HttpRetrieveRequest";
#endif
        break;
    case CHttpEvent::HttpReleaseRequest :
#ifndef QT_NO_DEBUG
        strMsg = "Event HttpReleaseRequest";
#endif
        break;
    case CHttpEvent::HttpSendGetResponse :
        pEvent->SetHttpGetResponse( *pResponse );
#ifndef QT_NO_DEBUG
        strMsg = "Event HttpSendGetResponse";
#endif
        break;
    case CHttpEvent::HttpSendPostResponse :
#ifndef QT_NO_DEBUG
        strMsg = "Event HttpSendPostResponse";
#endif
        break;
    }

#ifndef QT_NO_DEBUG
    qDebug( ) << strMsg << endl;
#endif
    QApplication::postEvent( httpServer, pEvent );
}
