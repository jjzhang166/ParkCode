#include "qlistenerthread.h"

QListenerThread* QListenerThread::pThreadInstance = 0;

QListenerThread::QListenerThread(QObject *parent) :
    QMyThread(parent)
{
    setObjectName( "[Listner Thread]" );
}

void QListenerThread::InitializeSubThread( )
{
    pSocketDispatcher = QSocketDispatcherThread::GetSingletonInstance( );
}

QListenerThread* QListenerThread::GetSingletonInstance( QObject *pParent )
{
    if ( 0 == pThreadInstance ) {
        pThreadInstance = new QListenerThread( pParent );
        pThreadInstance->StartThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QListenerThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QListenerThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QCommonLibrary::ThreadEventType type = ( QCommonLibrary::ThreadEventType ) pEvent->type( );
    QString strInfo = "";

    if ( QCommonLibrary::EventExit == type ) {
        PostThreadExit( pSocketDispatcher );
        LaunchThreadExit( );
        pThreadInstance = NULL;
    } else if ( QCommonLibrary::EventStartListen == type ) {
        if ( network.StartServerListen( strInfo ) ) {
            connect( &network, SIGNAL( Accept( qintptr ) ), this, SLOT( HandleAccept( qintptr ) ) );
            connect( &network, SIGNAL( ErrorInfo( qint32, QString ) ), this, SLOT( HandleErrorInfo( qint32,QString ) ) );
        }
    } else if ( QCommonLibrary::EventStopListen == type ) {
        network.StoptServerListen( strInfo );
        disconnect( &network, SIGNAL( Accept( qintptr ) ), this, SLOT( HandleAccept( qintptr ) ) );
        disconnect( &network, SIGNAL( ErrorInfo( qint32, QString ) ), this, SLOT( HandleErrorInfo( qint32,QString ) ) );
    }

    if ( !strInfo.isEmpty( ) ) {
        WriteLog( QCommonLibrary::LogInformation, strInfo, false );
    }
}

void QListenerThread::HandleAccept( qintptr socketDescriptor )
{
    PostSocketDescriptorEvent( socketDescriptor );
}

void QListenerThread::HandleErrorInfo( qint32 logType, QString strText )
{
    WriteLog( ( QCommonLibrary::LogType ) logType, strText, true );
}

void QListenerThread::PostSocketDescriptorEvent( qintptr socketDescriptor )
{
    QCommonLibrary::EventParam uParam;
    uParam.ParamValue.DistpatcherThread.Param.nSocketDescriptor = socketDescriptor;

    PostThreadEvent( pSocketDispatcher,
                     QCommonLibrary::ThreadSocketDispatcher,
                     QCommonLibrary::EventSocketDescriptorDispatch,
                     uParam );
}

void QListenerThread::PostStartListenEvent( )
{
    PostThreadEvent( this, QCommonLibrary::EventStartListen );
}

void QListenerThread::PostStopListenEvent( )
{
    PostThreadEvent( this, QCommonLibrary::EventStopListen );
}
