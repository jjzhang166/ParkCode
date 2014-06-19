#include "qlogthread.h"

QLogThread* QLogThread::pThreadInstance = 0;

QLogThread::QLogThread(QObject *parent) :
    QMyThread(parent)
{
    setObjectName( "[Log Thread]" );
}

void QLogThread::InitializeSubThread( )
{

}

QLogThread* QLogThread::GetSingletonInstance( QObject *pParent )
{
    if ( 0 == pThreadInstance ) {
        pThreadInstance = new QLogThread( pParent );
        pThreadInstance->StartThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QLogThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QLogThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QCommonLibrary::ThreadEventType type = ( QCommonLibrary::ThreadEventType ) pEvent->type( );
    QCommonLibrary::EventParam& uParam = pEvent->GetEventParam( );

    if ( QCommonLibrary::EventExit == type ) {
        pThreadInstance = NULL;
        LaunchThreadExit( );
    } else if ( QCommonLibrary::EventWriteLog == type ) {
        ProcessWriteLogEvent( uParam );
    }
}

void QLogThread::PostLogWriteEvent( QCommonLibrary::LogType logType, QString &strText, bool bSingle )
{
    QString strDateTime = "";
    QString strLogType = "";
    QCommonLibrary::GetCurrentDateTime( strDateTime );

    switch ( logType ) {
    case QCommonLibrary::LogInformation :
        strLogType = "信息";
        break;

    case QCommonLibrary::LogWarning :
        strLogType = "警告";
        break;

    case QCommonLibrary::LogError :
        strLogType = "错误";
        break;
    }

    QString strLog = QString( "('%1','%2','%3')" ).arg( strLogType, strText, strDateTime );
    QCommonLibrary::EventParam uParam;
    uParam.ParamValue.LogThread.LogParam.pLogSQLStmt = new QString( strLog );
    uParam.ParamValue.LogThread.LogParam.bSingleRow = bSingle;
    uParam.type = QCommonLibrary::TypeLogContent;

    PostThreadEvent( this, QCommonLibrary::ThreadLog,
                     QCommonLibrary::EventWriteLog, uParam );
}

void QLogThread::ProcessWriteLogEvent( QCommonLibrary::EventParam &uParam )
{
    QString* strLog = uParam.ParamValue.LogThread.LogParam.pLogSQLStmt;
    QCommonLibrary::PrintLog( *strLog );

    if ( QCommonLibrary::GetDisplayLog( ) ) {
        emit DisplayLog( *strLog );
    }

    if ( uParam.ParamValue.LogThread.LogParam.bSingleRow ) {
        WriteDatabase( strLog );
    } else {
        logQueue.enqueue( strLog );
        if ( logQueue.length( ) >= QIniConfigFile::GetLogCount( ) ) {
            ConcatSQL( strLog );
            WriteDatabase( strLog );
        }
    }
}

void QLogThread::ConcatSQL( QString*& strSQL )
{
    if ( logQueue.isEmpty( ) ) {
        return;
    }

    strSQL = logQueue.dequeue( );

    while ( !logQueue.isEmpty( ) ) {
        strSQL->insert( 0, "," );
        strSQL->append( *logQueue.dequeue( ) );
    }
}

void QLogThread::WriteDatabase( QString* strSQL )
{
    // PostLogWriteEvent( ) new QString
    if ( 0 == strSQL ) {
        return;
    }

    strSQL->insert( 0, "Insert Into TabLogInfo Values" );

    delete strSQL;
}
