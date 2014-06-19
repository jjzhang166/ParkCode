#include "qipcevent.h"

QIPCEvent::QIPCEvent( Type evtType ) : QEvent( evtType )
{

}

QIPCEvent::~QIPCEvent( )
{

}

QIPCEvent* QIPCEvent::GetInstance( IPCEventType evtType )
{
    QIPCEvent* pEvent = new QIPCEvent( ( Type ) evtType );

    return pEvent;
}

void QIPCEvent::SetEventParam( EventParam &uParam )
{
    evtParam = uParam;
}

QIPCEvent::EventParam& QIPCEvent::GetEventParam( )
{
    return evtParam;
}
