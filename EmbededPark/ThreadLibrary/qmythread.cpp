#include "qmythread.h"
#include "qlogthread.h"

QMyThread::QMyThread(QObject *parent) :
    QThread(parent)
{
}

void QMyThread::LaunchThreadExit( )
{
    ThreadStartExitLog( false );
    moveToThread( qApp->thread( ) );
    exit( );
}

void QMyThread::InitializeThread( )
{
    bool bRet = false;
    bRet = connect( this, SIGNAL( finished( ) ), this, SLOT( ThreadFinished( ) ) );
    bRet = connect( this, SIGNAL( started( ) ), this, SLOT( ThreadStarted( ) ) );
}

void QMyThread::ThreadFinished( )
{
    deleteLater( );
}

void QMyThread::ThreadStartExitLog( bool bStarted )
{
    QString strDateTime = "";
    QCommonLibrary::GetCurrentDateTime( strDateTime );
    QString strObjName = objectName( );

    QString strLog = QString( "%1 %2 %3." ).arg(
                strObjName, strDateTime,
                bStarted ? "Started" : "Exited" );

    WriteLog( QCommonLibrary::LogInformation, strLog, true );
}

void QMyThread::ThreadStarted( )
{
    ThreadStartExitLog( true );
}

void QMyThread::WriteLog( QCommonLibrary::LogType logType, QString &strText, bool bSingle )
{
    //ID LogType Content DateTime
    QLogThread* pThread = QLogThread::GetSingletonInstance( );
    pThread->PostLogWriteEvent( logType, strText, bSingle );
}

void QMyThread::StartThread( QMyThread *pThread )
{
    pThread->InitializeThread( );
    pThread->start( );
    //pThread->wait( 1000L );
    pThread->moveToThread( pThread );
}

void QMyThread::PostThreadEvent( QThread *pThreadReceiver,
                                 QCommonLibrary::ThreadEventType eEvent )
{
    QEvent::Type evtType = ( QEvent::Type ) eEvent;
    QThreadEvent* pEvent = QThreadEvent::GetInstance( evtType );

    qApp->postEvent( pThreadReceiver, pEvent );
}

void QMyThread::PostThreadEvent( QThread *pThreadReceiver,
                                 QCommonLibrary::ThreadType eThread,
                                 QCommonLibrary::ThreadEventType eEvent,
                                 QCommonLibrary::EventParam& uParam )
{
    QEvent::Type evtType = ( QEvent::Type ) eEvent;
    QThreadEvent* pEvent = QThreadEvent::GetInstance( evtType );

    pEvent->SetEventParam( uParam, eThread, eEvent );
    qApp->postEvent( pThreadReceiver, pEvent );
}

void QMyThread::PostThreadExit( QMyThread *pThread )
{
    PostThreadEvent( pThread, QCommonLibrary::EventExit );
}
