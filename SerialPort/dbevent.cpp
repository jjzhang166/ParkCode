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

void CDbEvent::SetParameter( QString& strSql, bool bHistory, bool bTimerCard, bool bSelect, CommonDataType::BlobType blob, QByteArray& byData )
{
    evtParamter.strSql = strSql;
    evtParamter.bDbHistory = bHistory;
    evtParamter.bTimeCard = bTimerCard;
    evtParamter.bSelect = bSelect;
    evtParamter.blob = blob;
    evtParamter.byData = byData;
}

void CDbEvent::SetParameter( QString &strSql, bool bHistory, bool bTimeCard,
                             bool bEnter, QString& strCardNo, bool bGarage, int nType,
                             bool bSelect, CommonDataType::BlobType blob,
                             QByteArray &byData )
{
    evtParamter.strSql = strSql;
    evtParamter.bDbHistory = bHistory;
    evtParamter.bTimeCard = bTimeCard;
    evtParamter.bSelect = bSelect;
    evtParamter.blob = blob;
    evtParamter.byData = byData;
    evtParamter.bEnter = bEnter;
    evtParamter.strCardNo = strCardNo;
    evtParamter.bGarage = bGarage;
    evtParamter.nType = nType;
}

void CDbEvent::SetParameter( bool bEnter, int nType, bool bGarage, QString &strCardNo, QByteArray &byData )
{
    evtParamter.bEnter = bEnter;
    evtParamter.nType = nType;
    evtParamter.strCardNo = strCardNo;
    evtParamter.byData = byData;
    evtParamter.bGarage = bGarage;
    evtParamter.bDbHistory = false;
}

CDbEvent::WriteParameter& CDbEvent::GetParameter( )
{
    return evtParamter;
}

