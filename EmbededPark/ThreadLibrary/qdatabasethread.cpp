#include "qdatabasethread.h"

QDatabaseThread* QDatabaseThread::pThreadInstance = 0;

QDatabaseThread::QDatabaseThread(QObject *parent) :
    QMyThread(parent)
{
    setObjectName( "[Data Thread]" );
}

void QDatabaseThread::InitializeSubThread( )
{

}

QDatabaseThread* QDatabaseThread::GetSingletonInstance( QObject *pParent )
{
    if ( 0 == pThreadInstance ) {
        pThreadInstance = new QDatabaseThread( pParent );
        pThreadInstance->StartThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QDatabaseThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QDatabaseThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QCommonLibrary::ThreadEventType type = ( QCommonLibrary::ThreadEventType ) pEvent->type( );
    QCommonLibrary::EventParam& uParam = pEvent->GetEventParam( );

    if ( QCommonLibrary::EventExit == type ) {
        pThreadInstance = NULL;
        LaunchThreadExit( );
    }
}
