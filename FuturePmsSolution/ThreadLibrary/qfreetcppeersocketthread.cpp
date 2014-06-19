#include "qfreetcppeersocketthread.h"
#include "qtcppeersocketthread.h"

QFreeTcpPeerSocketThread* QFreeTcpPeerSocketThread::pThreadInstance = NULL;

QFreeTcpPeerSocketThread::QFreeTcpPeerSocketThread(QObject *parent) :
    QMyBaseThread(parent)
{
    setObjectName( "QFreeTcpPeerSocketThread" );
    OutputMsg( QString( " Created" ) );
}

QFreeTcpPeerSocketThread::~QFreeTcpPeerSocketThread( )
{
    OutputMsg( "" );
}

QFreeTcpPeerSocketThread* QFreeTcpPeerSocketThread::GetSingleton( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QFreeTcpPeerSocketThread( );
        pThreadInstance->InitializeThread( );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QFreeTcpPeerSocketThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QFreeTcpPeerSocketThread::InitializeSubThread( )
{

}

void QFreeTcpPeerSocketThread::ProcessCheckPeerThreadEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    Q_UNUSED( pEventParams );
    QTcpPeerSocketThread::ReleaseThread( );
}

void QFreeTcpPeerSocketThread::customEvent( QEvent *event )
{
    QFreeTcpPeerSocketThreadEvent* pEvent = ( QFreeTcpPeerSocketThreadEvent* ) event;
    MyEnums::EventType type = ( MyEnums::EventType ) pEvent->type( );
    MyDataStructs::PQQueueEventParams pEventParams = pEvent->GetEventParams( );

    if ( MyEnums::TcpPeerSocketThreadFreeCheck == type ) {
        ProcessCheckPeerThreadEvent( pEventParams );
    } else if ( MyEnums::ThreadExit == type ) {
        pThreadInstance = NULL;
        LaunchThreadExit( );
    }
}
