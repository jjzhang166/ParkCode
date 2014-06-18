#include "ccomthreadevent.h"

CComThreadEvent::CComThreadEvent( ThreadType thrType, Type evtType ) : QEvent( evtType ),
    typeThread( thrType ), typeEvent( ( EventType ) evtType )
{
}

CComThreadEvent* CComThreadEvent::CreateThreadEvent( ThreadType thrType, EventType evtType )
{
    return new CComThreadEvent( thrType, ( Type ) evtType );
}

void CComThreadEvent::SetPortName( const QString &strCOMx )
{
    strCOM = strCOMx;
}

const QString& CComThreadEvent::GetPortName( ) const
{
    return strCOM;
}

void CComThreadEvent::SetByteArrayData( QByteArray &byData )
{
    byByteArrayData.append( byData );
}

QByteArray& CComThreadEvent::GetByteArrayData( )
{
    return byByteArrayData;
}

void CComThreadEvent::SetComParkID( QString& strParkID )
{
    strComParkID = strParkID;
}

QString& CComThreadEvent::GetComParkID( )
{
    return strComParkID;
}
