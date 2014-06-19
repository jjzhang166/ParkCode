#ifndef QFREEDATABASEOBJECTTHREADEVENT_H
#define QFREEDATABASEOBJECTTHREADEVENT_H

#include "QMyThreadEvent.h"

class QFreeDatabaseObjectThreadEvent : public QMyThreadEvent
{
public:
    QFreeDatabaseObjectThreadEvent( Type type );
    ~QFreeDatabaseObjectThreadEvent( );
};

#endif // QFREEDATABASEOBJECTTHREADEVENT_H
