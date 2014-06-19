#ifndef QUDPSENDERTHREADEVENT_H
#define QUDPSENDERTHREADEVENT_H

#include "qmythreadevent.h"

class QUdpSenderThreadEvent : public QMyThreadEvent
{
public:
    QUdpSenderThreadEvent( Type type );
};

#endif // QUDPSENDERTHREADEVENT_H
