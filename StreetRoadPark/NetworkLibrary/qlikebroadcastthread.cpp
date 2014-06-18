#include "qlikebroadcastthread.h"

QLikeBroadcastThread* QLikeBroadcastThread::pThreadInstance = NULL;

QLikeBroadcastThread::QLikeBroadcastThread( QObject *parent ) :
    QThread( parent )
{
    nListenerPort = CNetConfigurator::GetConfigurator( )->GetMulticastPort( );
    setObjectName( QString( "[Like Broadcast Thread ID = %1]" ).arg( qrand( ) ) );
}

QLikeBroadcastThread* QLikeBroadcastThread::CreateThread( QObject *pParent )
{
    if ( NULL == pThreadInstance ) {
        qDebug( ) << Q_FUNC_INFO << endl;

        pThreadInstance = new QLikeBroadcastThread( pParent );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QLikeBroadcastThread::PostStartListenEvent( )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadMulticast,
                                                            QThreadEvent::EventStartListen );
    int nMaxConn = 100;
    pEvent->SetListenPort( nListenerPort );
    pEvent->SetMaxPendingConnection( nMaxConn );
    PostEvent( pEvent );
}

void QLikeBroadcastThread::PostStopListenEvent( )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadMulticast,
                                                            QThreadEvent::EventStopListen );
    PostEvent( pEvent );
}

void QLikeBroadcastThread::PostEvent( QThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void QLikeBroadcastThread::PostMulticastSocketEvent(QByteArray &byData)
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadMulticast, QThreadEvent::EventMulticastData );
    pEvent->SetByteArray( byData );

    PostEvent( pEvent );
}

void QLikeBroadcastThread::InitializeSubThread( )
{
    pTcpServer = new QMyTcpServer( );
    connect( pTcpServer, SIGNAL( acceptError( QAbstractSocket::SocketError ) ),
             this, SLOT( HandleAcceptError( QAbstractSocket::SocketError ) ) );
}

void QLikeBroadcastThread::ConnectAccept( bool bConnect )
{
    if ( bConnect ) {
        connect( pTcpServer, SIGNAL( Accept( qintptr ) ), this, SLOT( HandleAccept( qintptr ) ) );
    } else {
        disconnect( pTcpServer, SIGNAL( Accept( qintptr ) ), this, SLOT( HandleAccept( qintptr ) ) );
    }
}

void QLikeBroadcastThread::StartServer( QThreadEvent *pEvent )
{
    quint16 nPort = pEvent->GetListenPort( );
    qint32 nMaxConn = pEvent->GetMaxPendingConnection( );

    pTcpServer->setMaxPendingConnections( nMaxConn );
    bool bRet = pTcpServer->listen( QHostAddress::Any, nPort );
    QString strLog = QString( "Start server port %1 %2" ).arg( QString::number( nPort ),
                                                               bRet ? "Successfully." :
                                                                      QString( "Unsuccessfully. %1" ).arg( pTcpServer->errorString( ) ) );
    ConnectAccept( true );
    SendLog( strLog, true );
}

void QLikeBroadcastThread::StopServer( )
{
    if ( !pTcpServer->isListening( ) ) {
        return;
    }

    quint16 nPort = pTcpServer->serverPort( );
    pTcpServer->close( );
    ConnectAccept( false );

    QString strLog = QString( "Stop server port %1." ).arg( nPort );

    SendLog( strLog, true );
}

void QLikeBroadcastThread::SendLog( QString &strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void QLikeBroadcastThread::HandleAcceptError( QAbstractSocket::SocketError socketError )
{
    QTcpServer* pServer =( QTcpServer* ) sender( );
    Q_UNUSED( socketError )
    QString strLog = pServer->errorString( );
    SendLog( strLog, true );
}

void QLikeBroadcastThread::ConnectSocketEvent( QTcpSocket *pSocket )
{
    bool bRet = connect( pSocket, SIGNAL( connected( ) ),
                         this, SLOT( HandleConnectFinished( ) ) );

    bRet = connect( pSocket, SIGNAL( disconnected( ) ),
                    this, SLOT( HandleDisconnectFinished( ) ) );

    bRet = connect( pSocket, SIGNAL( readyRead( ) ),
                    this, SLOT( HandleDataIncoming( ) ) );

    bRet = connect( pSocket, SIGNAL( error( QAbstractSocket::SocketError ) ),
                    this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );

    Q_UNUSED( bRet )
}

void QLikeBroadcastThread::HandleDataIncoming( )
{
}

void QLikeBroadcastThread::HandleConnectFinished( )
{
    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );
    Q_UNUSED( pSocket )
}

void QLikeBroadcastThread::HandleDisconnectFinished( )
{
    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );
    QString strLog = QString( "Client【%1:%2】 disconnect to server." ).arg(
                pSocket->peerAddress( ).toString( ),
                QString::number( pSocket->peerPort( ) ));

    SendLog( strLog, false );

    lstPeers.removeOne( pSocket );
    pSocket->deleteLater( );
}

void QLikeBroadcastThread::HandleError( QAbstractSocket::SocketError socketError )
{
    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );
    Q_UNUSED( socketError )

    QString strLog = QString( "Client【%1】.%2" ).arg( pSocket->peerAddress( ).toString( ),
                                                     pSocket->errorString( ) );

    SendLog( strLog, false );
}

void QLikeBroadcastThread::run()
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );

    InitializeSubThread( );
    exec( );
}

void QLikeBroadcastThread::HandleAccept( qintptr socketDescriptor )
{
    QTcpSocket* pPeer = new QTcpSocket( );

    ConnectSocketEvent( pPeer );
    pPeer->setSocketDescriptor( socketDescriptor );

    QString strLog = QString( "Client【%1:%2】 connect to Server【%3】." ).arg(
                pPeer->peerAddress( ).toString( ),
                QString::number( pPeer->peerPort( ) ),
                QString::number( pTcpServer->serverPort( ) ) );

    SendLog( strLog, false );
    lstPeers.append( pPeer );
}

void QLikeBroadcastThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QByteArray& byData = pEvent->GetByteArray( );
    QThreadEvent::EventType evtType = ( QThreadEvent::EventType ) pEvent->type( );

    if ( QThreadEvent::EventMulticastData == evtType ) {
        foreach ( QTcpSocket* pPeer, lstPeers ) {
            pPeer->write( byData );
            pPeer->flush( );
            pPeer->waitForBytesWritten( );
        }
    } else if ( QThreadEvent::EventStartListen == evtType ) {
        StopServer( );
        StartServer( pEvent );
    } else if ( QThreadEvent::EventStopListen == evtType ) {
        StopServer( );
    }
}
