#include "qnetworklibrary.h"
#include "../IniConfigFile/qiniconfigfile.h"


QNetworkLibrary::QNetworkLibrary( QObject *parent ) : QObject ( parent )
{
    Set2Null( );
}

void QNetworkLibrary::Set2Null( )
{
    pTcpServer = NULL;
    pConnectedSocketHash = NULL;
    pDisconnectedSocketHash = NULL;
    pAttachedSocketQueue = NULL;
    pDetachedSocketQueue = NULL;
}

QNetworkLibrary::~QNetworkLibrary( )
{
    if ( NULL != pTcpServer ) {
        delete pTcpServer;
    }

    DestroyHash( pConnectedSocketHash );
    DestroyHash( pDisconnectedSocketHash );

    DestroyQueue( pAttachedSocketQueue );
    DestroyQueue( pDetachedSocketQueue );

    Set2Null( );
}

void QNetworkLibrary::CreateHash( )
{
    if ( 0 == pConnectedSocketHash ) {
        pConnectedSocketHash = new QHostSocketHash( );
    }

    if ( 0 == pDisconnectedSocketHash ) {
        pDisconnectedSocketHash = new QHostSocketHash( );
    }
}

void QNetworkLibrary::DestroyHash( QNetworkLibrary::QHostSocketHash *pHash )
{
    if ( 0 == pHash ) {
        return;
    }

    foreach ( QTcpSocket* pSocket, pHash->values( ) ) {
        pSocket->disconnect( );
        pSocket->close( );
        delete pSocket;
    }

    pHash->clear( );
    delete pHash;
}

void QNetworkLibrary::DestroyQueue( QNetworkLibrary::QSocketQueue *pQueue )
{
    if ( 0 == pQueue ) {
        return;
    }

    QTcpSocket* pSocket = NULL;

    while ( !pQueue->isEmpty( ) ) {
        pSocket = pQueue->dequeue( );
        delete pSocket;
    }

    delete pQueue;
}

void QNetworkLibrary::CreateQueue( )
{
    if ( 0 == pAttachedSocketQueue ) {
        pAttachedSocketQueue = new QSocketQueue( );
    }

    if ( 0 == pDetachedSocketQueue ) {
        pDetachedSocketQueue = new QSocketQueue( );
    }
}

void QNetworkLibrary::HandleAccept( qintptr socketDescriptor )
{
    emit Accept( socketDescriptor );
}

void QNetworkLibrary::HandleDataIncoming( void *pSocket, void *pByteArray )
{
    emit DataIncoming( pSocket, pByteArray );
}

bool QNetworkLibrary::StartServerListen( QString& strInfo )
{
    bool bRet = false;

    if ( 0 == pTcpServer ) {
        pTcpServer = new QMyTcpServer( );
        connect( pTcpServer, SIGNAL( Accept( qintptr ) ), this, SLOT( HandleAccept( qintptr ) ) );
    }

    if ( pTcpServer->isListening( ) ) {
        strInfo = "Listen started.";
        return bRet;
    }

    quint16 nPort = QIniConfigFile::GetServerListenPort( );
    qint32 nMaxConnection = QIniConfigFile::GetMaxPendingConnections( );

    pTcpServer->setMaxPendingConnections( nMaxConnection );
    bRet = pTcpServer->listen( QHostAddress::Any, nPort );

    if ( bRet ) {
        strInfo = QString( "Server Listening Port %1." ).arg( nPort );
    } else {
        strInfo = pTcpServer->errorString( );
    }

    return bRet;
}

void QNetworkLibrary::StoptServerListen( QString& strInfo )
{
    if ( 0 == pTcpServer || !pTcpServer->isListening( ) ) {
        strInfo = "Listen not started.";
        return;
    }

    pTcpServer->close( );
    strInfo = pTcpServer->errorString( );
}

void QNetworkLibrary::GetKey(quint32 nIP, quint16 nPort, QString& strKey )
{
    QString strSeperator = QCommonLibrary::GetKeySeperator( );
    strKey = QString( "%1%2%3" ).arg( QString::number( nIP ),
                                      strSeperator,
                                      QString::number( nPort ) );
}

QTcpSocket* QNetworkLibrary::Connect2Host( quint32 nIP, quint16 nPort )
{
    QTcpSocket* pSocket = NULL;
    QString strKey = "";
    GetKey( nIP, nPort, strKey );

    CreateHash( );

    QList< QTcpSocket* > lstSocket = pDisconnectedSocketHash->values( strKey );
    if ( 0 == lstSocket.length( ) ) {
        pSocket = new QTcpClientSocket( parent( ) );
        ConnectSocketEvent( pSocket );
    } else {
        pSocket = lstSocket.at( 0 );
        pDisconnectedSocketHash->remove( strKey, pSocket );
    }

    pConnectedSocketHash->insertMulti( strKey, pSocket );
    strKey = pConnectedSocketHash->key( pSocket );
    Connect2Server( pSocket, true );

    return pSocket;
}

void QNetworkLibrary::Disconnect2Hots( QTcpSocket *pSocket )
{
    if ( 0 == pSocket || QAbstractSocket::ConnectedState != pSocket->state( ) ) {
        return;
    }

    CreateHash( );

    DisconnectHashChange( pSocket );
    pSocket->disconnectFromHost( );
}

quint64 QNetworkLibrary::SocketSendData( QTcpSocket *pSocket, QByteArray& byData )
{
    QMyTcpSocket* pSender = ( QMyTcpSocket* ) pSocket;
    return pSender->SendData( byData );
}

void QNetworkLibrary::Connect2Server( QTcpSocket *pSocket, bool bManual )
{
    if ( 0 == pSocket || QAbstractSocket::ConnectedState == pSocket->state( ) ) {
        return;
    }

    QString strKey = ( bManual ? pConnectedSocketHash: pDisconnectedSocketHash )->key( pSocket );
    if ( strKey.isEmpty( ) ) {
        return;
    }

    // IP+Port
    QStringList lstHost = strKey.split( "+" );

    if ( 2 != lstHost.length( ) ) {
        return;
    }

    quint32 nIP = lstHost.at( 0 ).toUInt( );
    quint16 nPort = lstHost.at( 1 ).toUShort( );
    QHostAddress addr( nIP );

    pSocket->connectToHost( addr, nPort );

    if ( !bManual ) {
        emit ClientReconnect( pSocket );
    }
}

void QNetworkLibrary::DisconnectHashChange( QTcpSocket *pSocket )
{
    QString strKey = pConnectedSocketHash->key( pSocket );
    if ( strKey.isEmpty( ) ) {
        return;
    }

    pConnectedSocketHash->remove( strKey, pSocket );

    if ( !pDisconnectedSocketHash->contains( strKey, pSocket ) ) {
        pDisconnectedSocketHash->insertMulti( strKey, pSocket );
    }
}

void QNetworkLibrary::HandleConnectFinished( QTcpSocket *pSocket, bool bPeer )
{
    ConnectLog( pSocket, true, bPeer );

    if ( bPeer ) {

    } else{
        QString strKey = pDisconnectedSocketHash->key( pSocket );
        if ( !strKey.isEmpty( ) ) {
            pDisconnectedSocketHash->remove( strKey, pSocket );
        } else {
            GetKey( pSocket->localAddress( ).toIPv4Address( ), pSocket->peerPort( ), strKey );
        }

        if ( !pConnectedSocketHash->contains( strKey, pSocket ) ) {
            pConnectedSocketHash->insertMulti( strKey, pSocket );
        }
    }
}

void QNetworkLibrary::HandleErrorInfo( qint32 logType, QString strText )
{
    emit ErrorInfo( logType, strText );
}

void QNetworkLibrary::HandleErrorCode( QTcpSocket* pSocket )
{
    QAbstractSocket::SocketError nCode = pSocket->error( );

    if ( QAbstractSocket::ConnectionRefusedError == nCode ) {
        DisconnectHashChange( pSocket );
        emit ErrorCode( pSocket );
    }
}

void QNetworkLibrary::HandleDisconnectFinished( QTcpSocket *pSocket, bool bPeer )
{
    ConnectLog( pSocket, false, bPeer );

    if ( bPeer ) { // Server Side
        emit PeerDisconenct( pSocket );
    } else { // Client Side
        emit ClientDisconnect( pSocket );
        DisconnectHashChange( pSocket );
        Connect2Server( pSocket, false );
    }
}

void QNetworkLibrary::ConnectLog( QTcpSocket *pSocket, bool bConnected, bool bPeer )
{
    QString strError = pSocket->errorString( );
    QString strKey = QString( "Client[%1:%2] %3 to Server[%4:%5]" ).arg(
                               bPeer ? pSocket->peerAddress( ).toString( ) : pSocket->localAddress( ).toString( ),
                               bPeer ? QString::number( pSocket->peerPort( ) ) : QString::number( pSocket->localPort( ) ),
                               bConnected ? "Connected" : "Disconnected",
                               bPeer ? pSocket->localAddress( ).toString( ) : pSocket->peerAddress( ).toString( ),
                               bPeer ? QString::number( pSocket->localPort( ) ) : QString::number( pSocket->peerPort( ) ) );

    QString strDateTime = "";
    QCommonLibrary::GetCurrentDateTime( strDateTime );
    QString strMsg = QString ( "%1 %2\r\n" ).arg( strDateTime, strKey );

    if ( pSocket->error( ) != QAbstractSocket::UnknownSocketError ) {
        emit ErrorInfo( QCommonLibrary::LogError, strError );
    }

    emit ErrorInfo( QCommonLibrary::LogInformation, strMsg );
}

QTcpSocket* QNetworkLibrary::ProcessServerAttachSocketEvent( QCommonLibrary::EventParam& uParam )
{
    CreateQueue( );

    QTcpSocket* pSocket = NULL;
    bool bRet = false;

    if ( pDetachedSocketQueue->isEmpty( ) ) {
        pSocket = new QTcpPeerSocket( );
        ConnectSocketEvent( pSocket );
    } else {
        pSocket = pDetachedSocketQueue->dequeue( );
    }

    pAttachedSocketQueue->enqueue( pSocket );

    qintptr nDescriptor = uParam.ParamValue.ServerSocketThread.Param.SocketDescriptor.nSocketDescriptor;
    bRet = pSocket->setSocketDescriptor( nDescriptor );
    Q_UNUSED( bRet )

    ConnectLog( pSocket, true, true );

    return pSocket;
}

void QNetworkLibrary::ConnectSocketEvent( QTcpSocket *pSocket )
{
    bool bRet = connect( pSocket, SIGNAL( ConnectFinished( QTcpSocket*, bool ) ),
                         this, SLOT( HandleConnectFinished( QTcpSocket*, bool ) ) );

    bRet = connect( pSocket, SIGNAL( DisconnectFinished( QTcpSocket*, bool ) ),
                    this, SLOT( HandleDisconnectFinished( QTcpSocket*, bool ) ) );

    bRet = connect( pSocket, SIGNAL( ErrorInfo( qint32, QString ) ),
                    this, SLOT( HandleErrorInfo( qint32, QString ) ) );

    bRet = connect( pSocket, SIGNAL( DataIncoming( void*, void* ) ),
                    this, SLOT( HandleDataIncoming( void*, void* ) ) );

    bRet = connect( pSocket, SIGNAL( ErrorCode( QTcpSocket* ) ),
                    this, SLOT( HandleErrorCode( QTcpSocket* ) ) );
}

void QNetworkLibrary::RemoveSocketFromQueue( QNetworkLibrary::QSocketQueue* pQueue, QTcpSocket* pSocket )
{
    QSocketQueue::Iterator ite = pQueue->begin( );

    while ( pQueue->end( ) != ite ) {
        if ( *ite == pSocket ) {
            pQueue->erase( ite );
            break;
        }

        ite++;
    }
}

void QNetworkLibrary::PeerSocketDisconnectQueueChange( QTcpSocket *pSocket )
{
    CreateQueue( );
    RemoveSocketFromQueue( pAttachedSocketQueue, pSocket );
    pDetachedSocketQueue->enqueue( pSocket );
}
