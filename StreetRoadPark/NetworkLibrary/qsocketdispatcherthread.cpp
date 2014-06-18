#include "qsocketdispatcherthread.h"
#include "databasecontroller.h"

QSocketDispatcherThread::QSocketDispatcherThread(QObject *parent) :
    QThread(parent)
{
    setObjectName( QString( "[Socket Dispatcher Thread ID = %1]" ).arg( qrand( ) ) );
    pConfig = CNetConfigurator::GetConfigurator( );
    nSocketCountEachServerThread = pConfig->GetThreadSocketCount( );
    nServerThreadCountEachDataParser = pConfig->GetPaserPeerCount( );
    nSocketThreadSleepTime = pConfig->GetPeerThreadSleep( );
    nDataDispatcherParserCount = pConfig->GetDataDispatcherParserCount( );
}

void QSocketDispatcherThread::InitializeSubThread( )
{
    QSocketThreadQueue* pQueue;

    for ( qint32 nIndex = 0; nIndex <= nSocketCountEachServerThread; nIndex++ ) {
        pQueue = new QSocketThreadQueue( );
        hashSocketThreads.insert( nIndex, pQueue );
    }
}

QSocketDispatcherThread::~QSocketDispatcherThread( )
{
    FreeQueue( );
}

void QSocketDispatcherThread::FreeQueue( )
{
    for ( qint32 nIndex = 0; nIndex < hashSocketThreads.count( ); nIndex++ ) {
        QSocketThreadQueue* pQueue = hashSocketThreads.value( nIndex );
        if ( 0 == pQueue ) {
            continue;
        }

        delete pQueue;
    }

    hashSocketThreads.clear( );
}

void QSocketDispatcherThread::PostEvent( QThreadEvent *pEvent )
{
    qApp->postEvent( this,  pEvent );
}

void QSocketDispatcherThread::PostDispatchSocketEvent( qintptr nSocket, int nPort )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadDispatcher, QThreadEvent::EventDispatchSocket );
    pEvent->SetSocketDescriptor( nSocket );
    pEvent->SetListenPort( nPort );

    PostEvent( pEvent );
}

void QSocketDispatcherThread::PostSocketDisconnectionEvent( QTcpSocket *pSocket )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadDispatcher, QThreadEvent::EventSocketDisconnection );
    pEvent->SetPeerSocket( pSocket );

    PostEvent( pEvent );
}

QSocketDispatcherThread* QSocketDispatcherThread::CreateThread( QObject *pParent )
{
    qDebug( ) << Q_FUNC_INFO << endl;

    QSocketDispatcherThread* pThread = new QSocketDispatcherThread( pParent );

    pThread->start( );
    pThread->moveToThread( pThread );

    return pThread;
}

void QSocketDispatcherThread::run( )
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QSocketDispatcherThread::RemoveThreadFromQueue( QSocketThreadQueue* pQueue, QSocketThread* pThread )
{
    QSocketThreadQueue::Iterator ite = pQueue->begin( );

    while ( pQueue->end( ) != ite ) {
        if ( *ite == pThread ) {
            pQueue->erase( ite );
            break;
        }

        ite++;
    }
}

// Find a thread queue to least relate with Socket
QSocketDispatcherThread::QSocketThreadQueue* QSocketDispatcherThread::FindSocketThreadQueue( qint32 &nKey )
{
    QSocketThreadQueue* pQueue = NULL;
    bool bFound = false;

    for ( qint32 nIndex = 0; nIndex < nSocketCountEachServerThread; nIndex++ ) {
        pQueue = hashSocketThreads.value( nIndex );

        if ( pQueue->isEmpty( ) ) {
            continue;
        }

        nKey = nIndex;
        bFound = true;
        break;
    }

    if ( !bFound ) { // First
        nKey = 0;
        pQueue = hashSocketThreads.value( nKey );
    }

    return pQueue;
}

void QSocketDispatcherThread::HandleLog( QString strLog, bool bStatic )
{
    //SendLog( strLog, bStatic );
    emit Log( strLog, bStatic );
}

void QSocketDispatcherThread::SendLog( QString& strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

QSocketThread* QSocketDispatcherThread::FindSocketThread( )
{
    QSocketThread* pSocketThread = NULL;
    qint32 nKey = 0;
    QSocketThreadQueue* pQueue = FindSocketThreadQueue( nKey );

    if ( pQueue->isEmpty( ) ) {
        static qint32 nParser = nServerThreadCountEachDataParser;
        static QDataParserThread* pParserThread = NULL;
        static qint32 nDispatcher = nDataDispatcherParserCount;
        static QDataDispactherThread* pDispatcherThread = NULL;

        pSocketThread = QSocketThread::CreateThread( );
        connect( pSocketThread, SIGNAL( Log( QString, bool ) ),
                 this, SLOT( HandleLog( QString, bool ) ) );
        pSocketThread->SetDispatcherThread( this );

        if ( 0 == pParserThread ) {
            pParserThread = QDataParserThread::CreateThread( ); 
            connect( pParserThread, SIGNAL( Log( QString, bool ) ),
                     this, SLOT( HandleLog( QString, bool ) ) );

            if ( 0 == pDispatcherThread ) {
                pDispatcherThread = DatabaseController::GetController( )->CreateDispactherThread( );
            }

            pParserThread->SetDataDispatcher( pDispatcherThread );

            nDispatcher--;
            if ( 0 == nDispatcher ) {
                nDispatcher = nDataDispatcherParserCount;
                pDispatcherThread = NULL;
            }
        }

        pSocketThread->SetDataParser( pParserThread );
        hashParserSocketThread.insertMulti( pParserThread, pSocketThread );

        nParser--;
        if ( 0 == nParser ) {
            nParser = nServerThreadCountEachDataParser;
            pParserThread = NULL;
        }
    } else {
        pSocketThread = pQueue->dequeue( );
    }

    //RemoveThreadFromQueue( pQueue, pThread );
    pQueue = hashSocketThreads.value( nKey + 1 );
    pQueue->enqueue( pSocketThread );

    return pSocketThread;
}

void QSocketDispatcherThread::ProcessSocketDispatchEvent( QThreadEvent* pEvent )
{
    QSocketThread* pThread = FindSocketThread( );
    pThread->PostAttachSocketEvent( pEvent->GetSocketDescriptor( ), pEvent->GetListenPort( ) );
}

void QSocketDispatcherThread::ProcessSocketDisconnectionEvent( QThreadEvent* pEvent )
{
    QSocketThread* pThread = ( QSocketThread* ) pEvent->GetPeerSocket( )->thread( );
    QSocketThreadQueue* pQueue;

    for ( qint32 nIndex = 1; nIndex <= nSocketCountEachServerThread; nIndex++ ) {
        pQueue = hashSocketThreads.value( nIndex );

        if ( pQueue->contains( pThread ) ) {
            RemoveThreadFromQueue( pQueue, pThread );
            pQueue = hashSocketThreads.value( nIndex - 1 );
            pQueue->enqueue( pThread );

            if ( 1 == nIndex ) { // All Disconnected
                pThread->SetThreadStartSleepTime( );
            }
            break;
        }
    }
}

void QSocketDispatcherThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QThreadEvent::EventType type = ( QThreadEvent::EventType ) pEvent->type( );

    if ( QThreadEvent::EventDispatchSocket == type ) {
        ProcessSocketDispatchEvent( pEvent );
    } else if ( QThreadEvent::EventSocketDisconnection == type ) {
        ProcessSocketDisconnectionEvent( pEvent );
    }
}
