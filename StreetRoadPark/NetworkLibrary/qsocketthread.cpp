#include "qsocketthread.h"
#include "qsocketdispatcherthread.h"

QSocketThread::QSocketThread( QObject *parent ) :
    QThread(parent)
{
    nThreadStartSleepTime = 10;
    pDispatcherThread = NULL;
    byTokenData = DATA_TOKEN;
    pConfig = CNetConfigurator::GetConfigurator( );

    setObjectName( QString( "[Socket Server Thread ID = %1]" ).arg( qrand( ) ) );
}

void QSocketThread::SetDataParser( QDataParserThread *pThread )
{
    //qDebug( ) << objectName( ) << ":" << pThread->objectName( ) << endl;
    pDataParserThread = pThread;
}

void QSocketThread::InitializeSubThread( )
{

}

QSocketThread::~QSocketThread( )
{
}

void QSocketThread::SendLog( QString& strLog, bool bStatic )
{
    if ( !bStatic && !pConfig->GetDisplayDynamicLog( ) ) {
        return;
    }

    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void QSocketThread::PostEvent( QThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent);
}

void QSocketThread::PostAttachSocketEvent( qintptr nSocket, int nPort )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadSocket, QThreadEvent::EventAttachSocketDescriptor );
    pEvent->SetSocketDescriptor( nSocket );
    pEvent->SetListenPort( nPort );

    PostEvent( pEvent );
}

QSocketThread* QSocketThread::CreateThread( QObject *pParent )
{
    qDebug( ) << Q_FUNC_INFO << endl;

    QSocketThread* pThread = new QSocketThread( pParent );

    pThread->start( );
    pThread->moveToThread( pThread );

    return pThread;
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
    qint64 nTmpTime = QDateTime::currentMSecsSinceEpoch( ) - nThreadStartSleepTime;
    nTmpTime /= 60 * 1000;

    return ( nTmpTime >= nInterval );
}

void QSocketThread::run( )
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QSocketThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QThreadEvent::EventType type = ( QThreadEvent::EventType ) pEvent->type( );

    if ( QThreadEvent::EventAttachSocketDescriptor == type ) {
        ProcessServerAttachSocketEvent( pEvent );
    } else if ( QThreadEvent::EventServerSendData == type ) {
        ProcessServerSendDataEvent( pEvent );
    }
}

void QSocketThread::HandleError( QAbstractSocket::SocketError socketError )
{
    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );
    Q_UNUSED( socketError )

    QString strLog = QString( "Client【%1】.%2" ).arg( pSocket->peerAddress( ).toString( ),
                                                     pSocket->errorString( ) );

    SendLog( strLog, false );
}

void QSocketThread::ConnectSocketEvent( QTcpSocket *pSocket )
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

void QSocketThread::ProcessServerAttachSocketEvent( QThreadEvent* pEvent )
{
    QTcpSocket* pSocket = NULL;

    if ( detachedSocketQueue.isEmpty( ) ) {
        pSocket = new QTcpSocket( );
        ConnectSocketEvent( pSocket );
    } else {
        pSocket = detachedSocketQueue.dequeue( );
    }

    attachedSocketQueue.enqueue( pSocket );
    qintptr nDescriptor = pEvent->GetSocketDescriptor( );
    bool bRet = pSocket->setSocketDescriptor( nDescriptor );

    QString strLog = QString( "Client【%1:%2】 connect to server【%3】 %4" ).arg(
                pSocket->peerAddress( ).toString( ),
                QString::number( pSocket->peerPort( ) ),
                QString::number( pEvent->GetListenPort( ) ),
                bRet ? "Successfully." : QString( "Unsuccessfully.%1" ).arg( pSocket->errorString( ) ) );

    SendLog( strLog, false );
}

void QSocketThread::ProcessServerSendDataEvent( QThreadEvent* pEvent )
{
    QTcpSocket* pSocket = pEvent->GetPeerSocket( );
    QByteArray& byByteArray = pEvent->GetByteArray( );
    qint32 nType = pEvent->GetPackageType( );

    quint32 nDataSize = sizeof ( quint32 );
    quint32 nDataLen = byTokenData.length( ) +
            nDataSize * 3 +
            byByteArray.length( );

    nType = qToBigEndian< qint32 >( nType );
    quint32 nReserved = qToBigEndian< quint32 >( 0 );
    nDataLen = qToBigEndian< quint32 >( nDataLen );

    byByteArray.insert( 0, ( const char* ) &nType, nDataSize );
    byByteArray.insert( 0, ( const char* ) &nReserved, nDataSize );
    byByteArray.insert( 0, ( const char* ) &nDataLen, nDataSize );
    byByteArray.insert( 0, byTokenData );

    pSocket->write( byByteArray );
    pSocket->flush( );
    pSocket->waitForBytesWritten( );
}

void QSocketThread::HandleDataIncoming( )
{
    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );
    QByteArray byData = pSocket->readAll( );
    pDataParserThread->PostTCPDataEvent( pSocket, byData );
    //qDebug( ) << Q_FUNC_INFO << endl;
}

void QSocketThread::HandleConnectFinished( )
{
    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );
    Q_UNUSED( pSocket )
}

void QSocketThread::RemoveSocketFromQueue( QSocketQueue* pQueue, QTcpSocket* pSocket )
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

void QSocketThread::HandleDisconnectFinished( )
{
    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );
    QString strLog = QString( "Client【%1:%2】 disconnect to server." ).arg(
                pSocket->peerAddress( ).toString( ),
                QString::number( pSocket->peerPort( ) ) );

    SendLog( strLog, false );

    RemoveSocketFromQueue( &attachedSocketQueue, pSocket );
    detachedSocketQueue.enqueue( pSocket );

    QSocketDispatcherThread* pDispacher = ( QSocketDispatcherThread* ) pDispatcherThread;
    pDispacher->PostSocketDisconnectionEvent( pSocket );
}
