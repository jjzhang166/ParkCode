#ifndef QLISTENERTHREADEVENT_H
#define QLISTENERTHREADEVENT_H

#include "qmythreadevent.h"

class QListenerThreadEvent : public QMyThreadEvent
{
public:
    QListenerThreadEvent( Type type );
};

#endif // QLISTENERTHREADEVENT_H
