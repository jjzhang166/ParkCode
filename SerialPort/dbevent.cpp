#include "dbevent.h"

CDbEvent::CDbEvent( Type event ) : QEvent(  event )
{
}

void CDbEvent::SetParameter( QString &strSql, bool bHistory, bool bTimeCard, bool bSelect )
{
    evtParamter.strSql = strSql;
    evtParamter.bDbHistory = bHistory;
    evtParamter.bTimeCard = bTimeCard;
    evtParamter.bSelect = bSelect;
}

void CDbEvent::SetParameter( QString &strSql, bool bHistory, bool bTimeCard, bool bSelect, CommonDataType::BlobType blob, QByteArray &byData )
{
    evtParamter.strSql = strSql;
    evtParamter.bDbHistory = bHistory;
    evtParamter.bTimeCard = bTimeCard;
    evtParamter.bSelect = bSelect;
    evtParamter.blob = blob;
    evtParamter.byData = byData;
}

CDbEvent::WriteParameter& CDbEvent::GetParameter( )
{
    return evtParamter;
}

