#ifndef QLOGGEREVENT_H
#define QLOGGEREVENT_H

#include "qmythreadevent.h"

class QLoggerThreadEvent : public QMyThreadEvent
{
public:
    explicit QLoggerThreadEvent( Type type );
    ~QLoggerThreadEvent( );

};

#endif // QLOGGEREVENT_H
