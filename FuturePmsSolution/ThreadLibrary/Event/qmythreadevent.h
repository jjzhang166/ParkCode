#ifndef QMYTHREADEVENT_H
#define QMYTHREADEVENT_H

#include <QEvent>
#include "../../CommonLibrary/CommonDataStruct.h"

class QMyThreadEvent : public QEvent
{
public:
    explicit QMyThreadEvent( Type type );
    ~QMyThreadEvent( );

    void SetEventParams( MyDataStructs::PQQueueEventParams const pQueueEventParams );
    MyDataStructs::PQQueueEventParams GetEventParams( ) const;

private:
    MyDataStructs::PQQueueEventParams pEventParams;
};

#endif // QMYTHREADEVENT_H
