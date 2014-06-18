#include "serialevent.h"

CSerialEvent::CSerialEvent( Type event ) : QEvent(  event )
{
    nSerialPortIndex = 0;
}

void CSerialEvent::SetSerialData( const QByteArray &byData, const int nIndex )
{
    bySerialData.append( byData );
    nSerialPortIndex = nIndex;
}

QByteArray& CSerialEvent::GetSerialData( )
{
    return bySerialData;
}

int CSerialEvent::GetSerialIndex( )
{
    return nSerialPortIndex;
}
