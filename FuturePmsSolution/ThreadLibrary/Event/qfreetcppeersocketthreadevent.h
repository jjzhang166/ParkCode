#ifndef QFREETCPPEERSOCKETTHREADEVENT_H
#define QFREETCPPEERSOCKETTHREADEVENT_H

#include "QMyThreadEvent.h"

class QFreeTcpPeerSocketThreadEvent : public QMyThreadEvent
{
public:
    QFreeTcpPeerSocketThreadEvent( Type type );
    ~QFreeTcpPeerSocketThreadEvent( );
};

#endif // QFREETCPPEERSOCKETTHREADEVENT_H
