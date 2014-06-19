#include "ftpevent.h"

CFtpEvent::CFtpEvent( FtpEvent event ) : QEvent( ( Type ) event )
{
}

QStringList& CFtpEvent::GetParams( )
{
    return lstParams;
}

void CFtpEvent::SetParams( QStringList lstParam )
{
    lstParams = lstParam;
}
