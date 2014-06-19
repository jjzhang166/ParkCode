#ifndef QUDPRECEIVERTHREADEVENT_H
#define QUDPRECEIVERTHREADEVENT_H

#include "qmythreadevent.h"

class QUdpReceiverSocketThreadEvent : public QMyThreadEvent
{
public:
    QUdpReceiverSocketThreadEvent( Type type );
};

#endif // QUDPRECEIVERTHREADEVENT_H
