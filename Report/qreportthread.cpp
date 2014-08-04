#include "qreportthread.h"
QReportThread* QReportThread::pThreadInstance = NULL;

QReportThread::QReportThread(QObject *parent) :
    QThread(parent)
{
    strSpSql = "CALL ParkReport( %1, '%2' )";
}

QReportThread* QReportThread::CreateReportThread( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QReportThread( );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

bool QReportThread::ConnectDb( )
{
    QStringList lstParams;
    CCommonFunction::ConnectMySql( lstParams, false );
    bool bRet = interfaceNormal.GetMysqlDb( ).DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ],
                                                     lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );

    return bRet;
}

void QReportThread::run( )
{
    ConnectDb( );
    exec( );
}

void QReportThread::customEvent(QEvent *e)
{
    QMyReportEvent* pEvent = ( QMyReportEvent* ) e;
    QMyReportEvent::MyReportEvent eEvent = ( QMyReportEvent::MyReportEvent ) e->type( );
    const QString strXml = pEvent->GetXmlParams( );
    QString strSQL;
    bool bResult = pEvent->GetResultset( );

    if ( QMyReportEvent::ExecuteSQL == eEvent ||
         QMyReportEvent::StayingMonth == eEvent ||
         QMyReportEvent::StayingTime == eEvent ||
         QMyReportEvent::StayingNoCard == eEvent ) {
        strSQL = strXml;
    } else {
        strSQL = strSpSql.arg(
                    QString::number( eEvent - QEvent::User ), strXml );
    }

    ProcessEvent( eEvent, strSQL, bResult );
}

void QReportThread::PostEvent( QMyReportEvent* pEvent )
{
    qApp->postEvent( this, pEvent );
}

void QReportThread::ProcessEvent( int nType, QString& strSQL, bool bResult )
{
   QStringList lstRows;
   int nRows = 0;
   if ( bResult ) {
       nRows = interfaceNormal.ExecuteSql( strSQL, lstRows );
   } else {
       interfaceNormal.ExecuteSql( strSQL );
       emit RefresehData( nType );
       return;
   }

   if ( QMyReportEvent::ExecuteSQL == nType ||
        QMyReportEvent::StayingMonth == nType ||
        QMyReportEvent::StayingTime == nType ||
        QMyReportEvent::StayingNoCard == nType ) {
        emit ExecuteSQLData( nType, lstRows, nRows );
   } else {
        emit ReportData( nType, lstRows );
   }
}

void QReportThread::PostReportEvent(const QString &strXmlParams, QMyReportEvent::MyReportEvent eEvent, bool bResult )
{
    QMyReportEvent* pEvent = QMyReportEvent::CreateInstance( eEvent );
    pEvent->SetXmlParams( strXmlParams );
    pEvent->SetResultset( bResult );
    PostEvent( pEvent );
}
