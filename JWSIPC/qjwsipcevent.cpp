#include "qjwsipcevent.h"

QJwsIPCEvent::QJwsIPCEvent( Type evtType ) : QEvent( evtType )
{
}

QJwsIPCEvent::~QJwsIPCEvent( )
{

}

QJwsIPCEvent* QJwsIPCEvent::GetInstance( IPCEventType evtType )
{
    QJwsIPCEvent* pEvent = new QJwsIPCEvent( ( Type ) evtType );

    return pEvent;
}

void QJwsIPCEvent::SetEventParam( EventParam &uParam )
{
    evtParam = uParam;
}

QJwsIPCEvent::EventParam& QJwsIPCEvent::GetEventParam( )
{
    return evtParam;
}
