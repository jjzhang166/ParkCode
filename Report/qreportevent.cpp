#include "qreportevent.h"

QMyReportEvent::QMyReportEvent( Type eEvent ) : QEvent( eEvent )
{
}

QMyReportEvent* QMyReportEvent::CreateInstance( MyReportEvent eEvent )
{
    return new QMyReportEvent( ( Type ) eEvent );
}

void QMyReportEvent::SetXmlParams( const QString& strXml )
{
    strXmlValue = strXml;
}

const QString& QMyReportEvent::GetXmlParams( )
{
    return strXmlValue;
}
