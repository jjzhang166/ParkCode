#ifndef QDATABASETHREADEVENT_H
#define QDATABASETHREADEVENT_H

#include "qmythreadevent.h"

class QDatabaseThreadEvent : public QMyThreadEvent
{
public:
    explicit QDatabaseThreadEvent( Type type );
};

#endif // QDATABASETHREADEVENT_H
