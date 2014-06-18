#include "PmsLog\pmslog.h"

CPmsLog* CPmsLog::pLogger = NULL;

CPmsLog::CPmsLog(QObject *parent) :
    QObject(parent)
{
    pDataOperator = CLogicInterface::GetInterface( );
}

void CPmsLog::WriteLog( QStringList &lstLogs )
{
    if ( NULL == pDataOperator || 0 == lstLogs.count( ) ) {
        return;
    }

    QStringList lstTotalSql;
    QStringList lstSql;
    QString strSeperator = ",";
    QString strQuotation = "'";

    int nCols = 3;
    int nRows = lstLogs.count( ) / nCols;

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        lstSql.clear( );

        for ( int nCol = 0; nCol < nCols; nCol++ ) {
            lstSql << ( strQuotation + lstLogs.at( nCol + nRow * nCols ) + strQuotation );
        }

        lstTotalSql << ( "(" + lstSql.join( strSeperator ) + ")");
    }

    QString strSql = QString( "Insert Into PmsLog( MsgKind, MsgText, MsgDateTime ) VALUES %1" ).arg( lstTotalSql.join( strSeperator ) );
    pDataOperator->ExecuteSql( strSql );
}

CPmsLog* CPmsLog::GetInstance( )
{
    if ( NULL == pLogger ) {
        pLogger = new CPmsLog( );
    }

    return pLogger;
}

void CPmsLog::ReleaseInstance( )
{
    if ( NULL != pLogger ) {
        delete pLogger;
        pLogger = NULL;
    }
}
