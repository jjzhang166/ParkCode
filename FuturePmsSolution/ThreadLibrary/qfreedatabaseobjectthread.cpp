#include "qfreedatabaseobjectthread.h"
#include "qdatabasethread.h"

QFreeDatabaseObjectThread* QFreeDatabaseObjectThread::pThreadInstance = NULL;

QFreeDatabaseObjectThread::QFreeDatabaseObjectThread(QObject *parent) :
    QMyBaseThread(parent)
{
    setObjectName( "QFreeDatabaseObjectThread" );
    OutputMsg( QString( " Created" ) );
}

QFreeDatabaseObjectThread::~QFreeDatabaseObjectThread( )
{
    OutputMsg( "" );
}

QFreeDatabaseObjectThread* QFreeDatabaseObjectThread::GetSingleton( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QFreeDatabaseObjectThread( );
        pThreadInstance->InitializeThread( );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QFreeDatabaseObjectThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QFreeDatabaseObjectThread::InitializeSubThread( )
{

}

void QFreeDatabaseObjectThread::ProcessCheckDatabaseObjectEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    Q_UNUSED( pEventParams );
    QDatabaseThread::ReleaseDatabaseObject( );
}

void QFreeDatabaseObjectThread::customEvent( QEvent *event )
{
    QFreeDatabaseObjectThreadEvent* pEvent = ( QFreeDatabaseObjectThreadEvent* ) event;
    MyEnums::EventType type = ( MyEnums::EventType ) pEvent->type( );
    MyDataStructs::PQQueueEventParams pEventParams = pEvent->GetEventParams( );

    if ( MyEnums::DatabaseObjectFreeCheck == type ) {
        ProcessCheckDatabaseObjectEvent( pEventParams );
    } else if ( MyEnums::ThreadExit == type ) {
        pThreadInstance = NULL;
        LaunchThreadExit( );
    }
}
