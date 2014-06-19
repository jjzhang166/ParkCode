#include "qctrlevent.h"

QCtrlEvent::QCtrlEvent( Type evtType ) : QEvent( evtType )
{
    nSleepTime = 0;
}

void QCtrlEvent::SetData( QByteArray &data )
{
    byData.append( data );
}

QByteArray& QCtrlEvent::GetData( )
{
    return byData;
}

void QCtrlEvent::SetWaitTime( int nWaitTime )
{
    nSleepTime = nWaitTime;
}

int QCtrlEvent::GetWaitTime( )
{
    return nSleepTime;
}
