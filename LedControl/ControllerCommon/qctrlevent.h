#ifndef QCTRLEVENT_H
#define QCTRLEVENT_H

#include <QEvent>
#include <QByteArray>
#include "ControllerCommon_global.h"

class CONTROLLERCOMMONSHARED_EXPORT QCtrlEvent : public QEvent
{
public:
    QCtrlEvent( Type evtType  );

    typedef enum __CtrlEvent {
        SPWrite = User + 1,
        SPParse
    } CtrlEvent;

    void SetData( QByteArray& data );
    QByteArray& GetData( );
    void SetWaitTime( int nWaitTime );
    int GetWaitTime( );

private:
    QByteArray byData;
    int nSleepTime;
};

#endif // QCTRLEVENT_H
