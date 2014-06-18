#include "qresponseevent.h"

QResponseEvent::QResponseEvent( Type event ) : QEvent(  event )
{
}

void QResponseEvent::SetReponseData( const QByteArray &byData )
{
    byReponseData.append( byData );
}

QByteArray& QResponseEvent::GetReponseData( )
{
    return byReponseData;
}
