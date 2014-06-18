#include "qdatauploadevent.h"

QDataUploadEvent::QDataUploadEvent( Type evtType ) : QEvent( evtType )
{
}

QDataUploadEvent* QDataUploadEvent::CreateThreadEvent(UploadEvent evtType)
{
    return new QDataUploadEvent( ( Type ) evtType );
}

void QDataUploadEvent::SetEventData( const QByteArray& byData )
{
    byEventData.append( byData );
}

const QByteArray& QDataUploadEvent::GetEventData( )
{
    return byEventData;
}
