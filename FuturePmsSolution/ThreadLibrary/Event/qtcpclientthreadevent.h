#ifndef QTCPCLIENTTHREADEVENT_H
#define QTCPCLIENTTHREADEVENT_H

#include "QMyThreadEvent.h"

class QTcpClientSocketThreadEvent : public QMyThreadEvent
{
public:
    explicit QTcpClientSocketThreadEvent( Type type );
};

#endif // QTCPCLIENTTHREADEVENT_H
