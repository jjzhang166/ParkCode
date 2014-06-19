#include "qsocketdispatcherthread.h"
#include "../IniConfigFile/qiniconfigfile.h"

QSocketDispatcherThread* QSocketDispatcherThread::pThreadInstance = 0;

QSocketDispatcherThread::QSocketDispatcherThread(QObject *parent) :
    QMyThread(parent)
{
    setObjectName( "[Socket Dispatcher Thread]" );
    nSocketCountEachServerThread = QIniConfigFile::GetSocketCountEachServerThread( );
    nServerThreadCountEachDataParser = QIniConfigFile::GetServerThreadCountEachDataParser( );
    nSocketThreadSleepTime = QIniConfigFile::GetSocketThreadServerSleepTime( );
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
    SocketThreadExit( );
}

QSocketDispatcherThread* QSocketDispatcherThread::GetSingletonInstance( QObject *pParent )
{
    if ( 0 == pThreadInstance ) {
        pThreadInstance = new QSocketDispatcherThread( pParent );
        pThreadInstance->StartThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QSocketDispatcherThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QSocketDispatcherThread::DataParserThreadExit( QSocketThread *pThread )
{
    QDataParserThread* pParser = hashParserSocketThread.key( pThread, NULL );
    if ( 0 == pParser ) {
        return;
    }

    hashParserSocketThread.remove( pParser );
    PostThreadExit( pParser );
}

void QSocketDispatcherThread::SocketThreadExit( )
{
    for ( qint32 nIndex = 0; nIndex < hashSocketThreads.count( ); nIndex++ ) {
        QSocketThreadQueue* pQueue = hashSocketThreads.value( nIndex );
        if ( 0 == pQueue ) {
            continue;
        }

        while ( !pQueue->isEmpty( ) ) {
            QSocketThread* pThread = pQueue->dequeue( );
            DataParserThreadExit( pThread );
            PostThreadExit( pThread );
        }

        delete pQueue;
    }

    hashSocketThreads.clear( );
}

void QSocketDispatcherThread::RemoveThreadFromQueue( QSocketDispatcherThread::QSocketThreadQueue* pQueue, QSocketThread* pThread )
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

QSocketThread* QSocketDispatcherThread::FindSocketThread( )
{
    QSocketThread* pThread = NULL;
    qint32 nKey = 0;
    QSocketThreadQueue* pQueue = FindSocketThreadQueue( nKey );

    if ( pQueue->isEmpty( ) ) {
        static qint32 nParser = nServerThreadCountEachDataParser;
        static QDataParserThread* pParserThread = NULL;

        if ( 0 == pParserThread ) {
            pParserThread = QDataParserThread::GetInstance( );
        }

        pThread = QSocketThread::GetInstance( true, pParserThread );
        pThread->SetDispatcherThread( this );
        hashParserSocketThread.insertMulti( pParserThread, pThread );

        nParser--;
        if ( 0 == nParser ) {
            nParser = nServerThreadCountEachDataParser;
            pParserThread = NULL;
        }
    } else {
        pThread = pQueue->dequeue( );
    }

    //RemoveThreadFromQueue( pQueue, pThread );
    pQueue = hashSocketThreads.value( nKey + 1 );
    pQueue->enqueue( pThread );

    return pThread;
}

void QSocketDispatcherThread::ProcessSocketDispatchEvent( QCommonLibrary::EventParam &uParam )
{
    QSocketThread* pThread = FindSocketThread( );
    QCommonLibrary::EventParam uTmpParam;
    uTmpParam.ParamValue.ServerSocketThread.Param.SocketDescriptor.nSocketDescriptor = uParam.ParamValue.DistpatcherThread.Param.nSocketDescriptor;

    PostThreadEvent( pThread,
                     QCommonLibrary::ThreadSocketServer,
                     QCommonLibrary::EventAttachSocketDescriptor,
                     uTmpParam );
}

void QSocketDispatcherThread::ProcessSocketDisconnectionEvent( QCommonLibrary::EventParam &uParam )
{
    QSocketThread* pThread = ( QSocketThread* ) uParam.ParamValue.DistpatcherThread.Param.pSocket->thread( );
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

void QSocketDispatcherThread::ProcessTimerRecycleSocketThreadEvent( )
{
    QSocketThreadQueue* pQueue = hashSocketThreads.value( 0 );

    foreach ( QSocketThread* pThread, pQueue->toStdList( ) ) {
        if ( pThread->TimerRecycle( nSocketThreadSleepTime ) ) {
            RemoveThreadFromQueue( pQueue, pThread );
            DataParserThreadExit( pThread );
            PostThreadExit( pThread );
        }
    }
}

void QSocketDispatcherThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QCommonLibrary::ThreadEventType type = ( QCommonLibrary::ThreadEventType ) pEvent->type( );
    QCommonLibrary::EventParam& uParam = pEvent->GetEventParam( );

    if ( QCommonLibrary::EventExit == type ) {
        SocketThreadExit( );
        LaunchThreadExit( );
        pThreadInstance = NULL;
    } else if ( QCommonLibrary::EventSocketDescriptorDispatch == type ) {
        ProcessSocketDispatchEvent( uParam );
    } else if ( QCommonLibrary::EventTimerRecycleSocketThread == type ) {
        ProcessTimerRecycleSocketThreadEvent( );
    } else if ( QCommonLibrary::EventSocketDisconnection == type ) {
        ProcessSocketDisconnectionEvent( uParam );
    }
}
