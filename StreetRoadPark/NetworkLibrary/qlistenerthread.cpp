#include "qlistenerthread.h"

QListenerThread::QListenerThread(QObject *parent) :
    QThread(parent)
{
    setObjectName( QString( "[Listner Thread ID = %1]" ).arg( qrand( ) ) );
}

void QListenerThread::InitializeSubThread( )
{
    pTcpServer = new QMyTcpServer( );
    pSocketDispatcher = QSocketDispatcherThread::CreateThread( );

    connect( pTcpServer, SIGNAL( acceptError( QAbstractSocket::SocketError ) ),
             this, SLOT( HandleAcceptError( QAbstractSocket::SocketError ) ) );
    connect( pSocketDispatcher, SIGNAL( Log( QString, bool ) ),
             this, SLOT( HandleLog( QString, bool ) ) );
}

void QListenerThread::HandleAcceptError( QAbstractSocket::SocketError socketError )
{
    QTcpServer* pServer =( QTcpServer* ) sender( );
    Q_UNUSED( socketError )
    QString strLog = pServer->errorString( );
    SendLog( strLog, true );
}

void QListenerThread::HandleLog( QString strLog, bool bStatic )
{
    //SendLog( strLog, bStatic );
    emit Log( strLog, bStatic );
}

QListenerThread* QListenerThread::CreateThread( QObject *pParent )
{
    qDebug( ) << Q_FUNC_INFO << endl;

    QListenerThread* pThread = new QListenerThread( pParent );
    pThread->start( );
    pThread->moveToThread( pThread );

    return pThread;
}

void QListenerThread::run( )
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QListenerThread::StopServer( )
{
    if ( !pTcpServer->isListening( ) ) {
        return;
    }

    quint16 nPort = pTcpServer->serverPort( );

    pTcpServer->close( );

    QString strLog = QString( "Stop server port %1." ).arg( nPort );

    SendLog( strLog, true );
    ConnectAccept( false );
}

void QListenerThread::SendLog( QString& strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void QListenerThread::ConnectAccept( bool bConnect )
{
    if ( bConnect ) {
        connect( pTcpServer, SIGNAL( Accept( qintptr ) ), this, SLOT( HandleAccept( qintptr ) ) );
    } else {
        disconnect( pTcpServer, SIGNAL( Accept( qintptr ) ), this, SLOT( HandleAccept( qintptr ) ) );
    }
}

void QListenerThread::StartServer( QThreadEvent *pEvent )
{
    quint16 nPort = pEvent->GetListenPort( );
    qint32 nMaxConn = pEvent->GetMaxPendingConnection( );

    pTcpServer->setMaxPendingConnections( nMaxConn );
    bool bRet = pTcpServer->listen( QHostAddress::Any, nPort );

    QString strLog = QString( "Start server port %1 %2" ).arg( QString::number( nPort ),
                                                               bRet ? "Successfully." :
                                                                      QString( "Unsuccessfully. %1" ).arg( pTcpServer->errorString( ) ) );

    SendLog( strLog, true );
    ConnectAccept( true );
}

void QListenerThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QThreadEvent::EventType evtType = ( QThreadEvent::EventType ) pEvent->type( );

    if ( QThreadEvent::EventStartListen == evtType ) {
        StopServer( );
        StartServer( pEvent );
    } else if ( QThreadEvent::EventStopListen == evtType ) {
        StopServer( );
    }
}

void QListenerThread::HandleAccept( qintptr socketDescriptor )
{
    pSocketDispatcher->PostDispatchSocketEvent( socketDescriptor, pTcpServer->serverPort( ) );
}

void QListenerThread::PostStartListenEvent( quint16 nPort, qint32 nMaxConn )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadListener,
                                                            QThreadEvent::EventStartListen );
    pEvent->SetListenPort( nPort );
    pEvent->SetMaxPendingConnection( nMaxConn );
    PostEvent( pEvent );
}

void QListenerThread::PostStopListenEvent( )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadListener,
                                                            QThreadEvent::EventStopListen );
    PostEvent( pEvent );
}

void QListenerThread::PostEvent( QThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}
