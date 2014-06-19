#ifndef RECORDEVENT_H
#define RECORDEVENT_H

#include <QEvent>

class CRecordEvent : public QEvent
{
public:
    enum RecordEvent {
        WriteInRecord = User,
        WriteOutRecord
    };

    CRecordEvent( RecordEvent event );
    ~CRecordEvent( );
};

#endif // RECORDEVENT_H
