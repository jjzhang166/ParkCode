#include "qsocketthread.h"

QSocketThread* QSocketThread::pThreadInstance = NULL;

QSocketThread::QSocketThread( bool bServerSide,
                              QDataParserThread* pDataParser,
                              QObject *parent ) :
    QMyThread(parent), bServerSideThread( bServerSide ),
    pDataParserThread( pDataParser )
{
    pDataParserThread->SetServerSide( bServerSide );
    nThreadStartSleepTime = 0;
    pDispatcherThread = NULL;
    pHostSocketHash = NULL;
    pNetwork = NULL;

    setObjectName( QString( "[Socket %1 Thread]" ).arg( bServerSide ? "Server" : "Client" ) );
}

void QSocketThread::HandleClientReconnect( QTcpSocket *pSocket )
{
    emit ClientReconnect( pSocket );
}

void QSocketThread::HandleClientDisconnect( QTcpSocket *pSocket )
{
    emit ClientDisconnect( pSocket );
}

void QSocketThread::HandleErrorCode( QTcpSocket *pSocket )
{
    emit ErrorCode( pSocket );
}

void QSocketThread::InitializeSubThread( )
{
    pNetwork = new QNetworkLibrary( );

    connect( pNetwork, SIGNAL( DataIncoming( void*, void* ) ),
             this, SLOT( HandleDataIncoming( void*, void* ) ) );
    connect( pNetwork, SIGNAL( ErrorInfo( qint32, QString ) ),
             this, SLOT( HandleErrorInfo( qint32, QString ) ) );

    if ( bServerSideThread ) {
        connect( pNetwork, SIGNAL( PeerDisconenct( QTcpSocket* ) ),
                 this, SLOT( HandlePeerDisconenct( QTcpSocket* ) ) );
    } else {
        pHostSocketHash = new QHostSocketHash( );
        connect( pNetwork, SIGNAL( ClientReconnect( QTcpSocket* ) ),
                 this, SLOT( HandleClientReconnect( QTcpSocket* ) ) );
        connect( pNetwork, SIGNAL( ClientDisconnect( QTcpSocket* ) ),
                 this, SLOT( HandleClientDisconnect( QTcpSocket* ) ) );
        connect( pNetwork, SIGNAL( ErrorCode( QTcpSocket* ) ),
                 this, SLOT( HandleErrorCode( QTcpSocket* ) ) );
    }
}

QSocketThread::~QSocketThread( )
{
    if ( 0 != pHostSocketHash ) {
        delete pHostSocketHash;
        pHostSocketHash = NULL;
    }

    FreeNetwork( );
}

QSocketThread* QSocketThread::CreateThread( bool bServerSide, QDataParserThread* pDataParser, QObject* pUIReceiver, QObject *pParent )
{
    QSocketThread* pThread = new QSocketThread( bServerSide, pDataParser, pParent );
    pThread->StartThread( pThread );

    if ( NULL != pUIReceiver && !bServerSide && NULL != pDataParser ) {
        connect( pDataParser, SIGNAL( DataIncoming( QTcpSocket*, QByteArray* ) ),
                 pUIReceiver, SLOT( HandleDataIncoming( QTcpSocket*, QByteArray* ) ) );
    }

    return pThread;
}

QSocketThread* QSocketThread::GetSingletonInstance( bool bServerSide, QObject* pUIReceiver, QObject *pParent )
{
    if ( 0 == pThreadInstance ) {
        QDataParserThread* pDataParser = QDataParserThread::GetSingletonInstance( );
        pThreadInstance = CreateThread( bServerSide, pDataParser, pUIReceiver, pParent );
    }

    return pThreadInstance;
}

QSocketThread* QSocketThread::GetInstance( bool bServerSide, QDataParserThread *pDataParser, QObject* pUIReceiver, QObject *pParent )
{
    return CreateThread( bServerSide, pDataParser, pUIReceiver, pParent );
}

void QSocketThread::SetDispatcherThread( QThread *pThread )
{
    pDispatcherThread = pThread;
}

void QSocketThread::SetThreadStartSleepTime( )
{
    nThreadStartSleepTime = QDateTime::currentMSecsSinceEpoch( );
    nThreadStartSleepTime /= 60 * 1000;// Minute
}

bool QSocketThread::TimerRecycle( qint32 nInterval )
{
    qint64 nTmpTime = QDateTime::currentMSecsSinceEpoch( )- nThreadStartSleepTime;
    nTmpTime /= 60 * 1000;

    return ( nTmpTime >= nInterval );
}

void QSocketThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QSocketThread::FreeNetwork( )
{
    if ( 0 != pNetwork ) {
        delete pNetwork;
        pNetwork = NULL;
    }
}

void QSocketThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QCommonLibrary::ThreadEventType type = ( QCommonLibrary::ThreadEventType ) pEvent->type( );
    QCommonLibrary::EventParam& uParam = pEvent->GetEventParam( );

    if ( QCommonLibrary::EventExit == type ) {
        if ( !bServerSideThread ) {
            PostThreadExit( pDataParserThread );
        }

        FreeNetwork( );
        LaunchThreadExit( );
        pThreadInstance = NULL;
    } else if ( QCommonLibrary::EventAttachSocketDescriptor == type ) {
        ProcessServerAttachSocketEvent( uParam );
    } else if ( QCommonLibrary::EventDetachSocketDescriptor == type ) {
        ProcessServerDetachSocketEvent( uParam );
    } else if ( QCommonLibrary::EventClientConnection == type ) {
        ProcessClientConnectionEvent( uParam );
    } else if ( QCommonLibrary::EventClientDisconnection == type ) {
        ProcessClientDisconnectionEvent( uParam );
    } else if ( QCommonLibrary::EventClientSendData == type ) {
        ProcessClientSendDataEvent( uParam );
    } else if ( QCommonLibrary::EventServerSendData == type ) {
        ProcessServerSendDataEvent( uParam );
    }
}

void QSocketThread::ProcessServerAttachSocketEvent( QCommonLibrary::EventParam& uParam )
{
    QTcpSocket* pSocket = pNetwork->ProcessServerAttachSocketEvent( uParam );

    Q_UNUSED( pSocket )
}

void QSocketThread::ProcessServerDetachSocketEvent( QCommonLibrary::EventParam& uParam )
{
    Q_UNUSED( uParam )
}

void QSocketThread::ProcessServerSendDataEvent( QCommonLibrary::EventParam& uParam )
{
    QTcpSocket* pSocket = uParam.ParamValue.ServerSocketThread.Param.Data.pSocket;
    QByteArray* pByteArray = uParam.ParamValue.ServerSocketThread.Param.Data.pByteArray;

    pNetwork->SocketSendData( pSocket, *pByteArray );
    Q_UNUSED( uParam )
}

void QSocketThread::GetKey( QCommonLibrary::EventParam &uParam, QString &strKey )
{
    QString strSeperator = QCommonLibrary::GetKeySeperator( );
    strKey = QString( "%1%2%3%4%5" ).arg( QString::number( uParam.ParamValue.ClientSocketThread.Host.nIP ),
                                          strSeperator,
                                          QString::number( uParam.ParamValue.ClientSocketThread.Host.nPort ),
                                          strSeperator,
                                          QString::number( uParam.ParamValue.ClientSocketThread.Host.nSequence ) );
}

QTcpSocket* QSocketThread::GetTargetSocket( QCommonLibrary::EventParam &uParam )
{
    QString strKey = "";
    GetKey( uParam, strKey );
    QTcpSocket* pSocket = pHostSocketHash->value( strKey );

    return pSocket;
}

void QSocketThread::ProcessClientSendDataEvent( QCommonLibrary::EventParam& uParam )
{
    QTcpSocket* pSocket = GetTargetSocket( uParam );
    QByteArray* pByteArray = uParam.ParamValue.ClientSocketThread.Data.pByteArray;
    quint64 nRet = pNetwork->SocketSendData( pSocket, *pByteArray );
    Q_UNUSED( nRet )
}

void QSocketThread::ProcessClientConnectionEvent( QCommonLibrary::EventParam& uParam )
{
    quint32 nIP = uParam.ParamValue.ClientSocketThread.Host.nIP;
    quint16 nPort = uParam.ParamValue.ClientSocketThread.Host.nPort;

    QString strKey = "";
    GetKey( uParam, strKey );

    QTcpSocket* pSocket = pNetwork->Connect2Host( nIP, nPort );
    pHostSocketHash->insert( strKey, pSocket );
}

void QSocketThread::ProcessClientDisconnectionEvent( QCommonLibrary::EventParam& uParam )
{
    QTcpSocket* pSocket = GetTargetSocket( uParam );
    pNetwork->Disconnect2Hots( pSocket );
}

void QSocketThread::PostClientConnectEvent( QCommonLibrary::EventParam &uParam )
{
    PostThreadEvent( this,
                     QCommonLibrary::ThreadSocketClient,
                     QCommonLibrary::EventClientConnection,
                     uParam );
}

void QSocketThread::PostClientDisconnectEvent( QCommonLibrary::EventParam &uParam )
{
    PostThreadEvent( this,
                     QCommonLibrary::ThreadSocketClient,
                     QCommonLibrary::EventClientDisconnection,
                     uParam );
}

void QSocketThread::PostClientSendDataEvent( QCommonLibrary::EventParam &uParam )
{
    PostThreadEvent( this,
                     QCommonLibrary::ThreadSocketClient,
                     QCommonLibrary::EventClientSendData,
                     uParam );
}
void QSocketThread::HandleDataIncoming( void* pSocket, void* pByteArray )
{
    // pByteArray in QMyTcpSocket::ReceiveData( ) new
    QCommonLibrary::EventParam uParam;
    uParam.ParamValue.ParserThread.DataParam.pSocket = ( QTcpSocket* ) pSocket;
    uParam.ParamValue.ParserThread.DataParam.pByteArray = ( QByteArray* ) pByteArray;
    PostThreadEvent( pDataParserThread, QCommonLibrary::ThreadDataParser, QCommonLibrary::EventTCPData, uParam );
}

void QSocketThread::HandlePeerDisconenct( QTcpSocket* pSocket )
{
    QCommonLibrary::EventParam uParam;

    uParam.ParamValue.DistpatcherThread.Param.pSocket = pSocket;
    PostThreadEvent( pDispatcherThread,
                     QCommonLibrary::ThreadSocketDispatcher,
                     QCommonLibrary::EventSocketDisconnection,
                     uParam );

    pNetwork->PeerSocketDisconnectQueueChange( pSocket );
}

void QSocketThread::HandleErrorInfo( qint32 logType, QString strText )
{
    WriteLog( ( QCommonLibrary::LogType ) logType, strText, false );
}
