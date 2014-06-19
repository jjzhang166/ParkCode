#ifndef QTCPPEERTHREADEVENT_H
#define QTCPPEERTHREADEVENT_H

#include "QMyThreadEvent.h"

class QTcpPeerSocketThreadEvent : public QMyThreadEvent
{
public:
    explicit QTcpPeerSocketThreadEvent( Type type );
    
};

#endif // QTCPPEERTHREADEVENT_H
