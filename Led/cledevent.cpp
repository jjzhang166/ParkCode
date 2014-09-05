#include "cledevent.h"

CLedEvent::CLedEvent( LedEvent eEvent ) : QEvent( ( Type ) eEvent)
{
}

CLedEvent * CLedEvent::CreateLedEvent(LedEvent eEvent)
{
    return new CLedEvent( eEvent );
}
