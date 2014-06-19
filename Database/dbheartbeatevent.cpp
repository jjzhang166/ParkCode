#include "dbheartbeatevent.h"

CDbHeartbeatEvent::CDbHeartbeatEvent( QString& strDbSql, SqlHB event ) : QEvent( ( Type ) event )
{
    strSql = strDbSql;
}

QString& CDbHeartbeatEvent::GetSql( )
{
    return strSql;
}
