#include "qlistenerthread.h"

QListenerThread::QListenerThread(QObject *parent) :
    QMyBaseThread(parent)
{
    setObjectName( "QListenerThread" );
    OutputMsg( QString( " Created" ) );
}

QListenerThread::~QListenerThread( )
{
    OutputMsg( "" );
}

QListenerThread* QListenerThread::GetInstance( )
{
    QListenerThread* pThreadInstance = new QListenerThread( );
    pThreadInstance->InitializeThread( );
    pThreadInstance->start( );
    pThreadInstance->moveToThread( pThreadInstance );

    return pThreadInstance;
}

void QListenerThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QListenerThread::InitializeSubThread( )
{
    connect( &network, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ), this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );
    connect( &network, SIGNAL( Accept( int ) ), this, SLOT( HandleAccept( int ) ) );
}

void QListenerThread::HandleAccept( int socketDescriptor ) // IOC IPC
{
    OutputMsg( "Sender:" + sender( )->objectName( ) + QString( ":emit Accept( %1 )" ).arg( socketDescriptor ) );
    emit Accept( socketDescriptor );
}

void QListenerThread::ProcessListenerStartupEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );

    QVariant varPort = hash.value( MyEnums::NetworkParamListenerPort );
    QVariant varMaxConnection = hash.value( MyEnums::NetworkParamListenerMaxConnections );
    network.StartupTcpServer( ( quint16 ) varPort.toUInt( ), varMaxConnection.toInt( ) );
}

void QListenerThread::customEvent( QEvent *event )
{
    QListenerThreadEvent* pEvent = ( QListenerThreadEvent* ) event;
    MyEnums::EventType type = ( MyEnums::EventType ) pEvent->type( );
    MyDataStructs::PQQueueEventParams pEventParams = pEvent->GetEventParams( );

    if ( MyEnums::TcpListenerStartup == type ) {
        ProcessListenerStartupEvent( pEventParams );
    } else if ( MyEnums::ThreadExit == type ) {
        LaunchThreadExit( );
    }
}
