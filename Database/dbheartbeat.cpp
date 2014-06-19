#include "dbheartbeat.h"
#include "dbheartbeatevent.h"
#include <QApplication>
#include "../Database/mssqlserver.h"

CDbHeartbeat* CDbHeartbeat::pThreadInstance = NULL;

CDbHeartbeat::CDbHeartbeat(QObject *parent) :
    QThread(parent)
{

}

CDbHeartbeat* CDbHeartbeat::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new CDbHeartbeat( );
        pThreadInstance->moveToThread( pThreadInstance );
        pThreadInstance->start( );
    }

    return pThreadInstance;
}

void CDbHeartbeat::run( )
{
    exec( );
}

void CDbHeartbeat::ExecSql( QString &strSql )
{
    CMsSqlServer& dbServer = CMsSqlServer::CreateSingleton( );
    QSqlDatabase* pDb = dbServer.GetHeartbeatDb( );
    dbServer.ExecuteSql( strSql, pDb );
}

void CDbHeartbeat::customEvent( QEvent *e )
{
    CDbHeartbeatEvent* pEvent = ( CDbHeartbeatEvent* ) e;
    CDbHeartbeatEvent::SqlHB event = ( CDbHeartbeatEvent::SqlHB ) e->type( );
    QString& strSql = pEvent->GetSql( );

    switch ( event ) {
    case CDbHeartbeatEvent::SqlData :
        ExecSql( strSql );
        break;
    }
}

void CDbHeartbeat::PostSql( QString &strSql )
{
    CDbHeartbeatEvent* pEvent = new CDbHeartbeatEvent( strSql, CDbHeartbeatEvent::SqlData );

    qApp->postEvent( this, pEvent );
}
