#ifndef CLEDEVENT_H
#define CLEDEVENT_H

#include <QEvent>

class CLedEvent : public QEvent
{
public:
    typedef enum __LedEvent {
        PublishText = User
    } LedEvent;

    static CLedEvent* CreateLedEvent( LedEvent eEvent );

private:
    CLedEvent( LedEvent eEvent );
};

#endif // CLEDEVENT_H
