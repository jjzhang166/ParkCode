#include "qmythreadevent.h"

QMyThreadEvent::QMyThreadEvent( Type type ) : QEvent( type )
{
}

QMyThreadEvent::~QMyThreadEvent( )
{
    if ( NULL != pEventParams ) {
        delete pEventParams;
        pEventParams = NULL;
    }
}

void QMyThreadEvent::SetEventParams( MyDataStructs::PQQueueEventParams const pQueueEventParams )
{
    pEventParams = pQueueEventParams;
}

MyDataStructs::PQQueueEventParams QMyThreadEvent::GetEventParams( ) const
{
    return pEventParams;
}
