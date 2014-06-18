#ifndef QDATAUPLOADEVENT_H
#define QDATAUPLOADEVENT_H

#include <QEvent>
#include <QByteArray>

class QDataUploadEvent : public QEvent
{
public:
    typedef enum __UploadEvent {
        UploadInOutRecordInsert = User,
        UploadInoutRecordUpdate,
        UploadFeeInfoInsert,
        UploadFeeInfoUpdate
    } UploadEvent;

    static QDataUploadEvent* CreateThreadEvent( UploadEvent evtType );

    void SetEventData( const QByteArray& byData );
    const QByteArray& GetEventData( );

private:
    QDataUploadEvent( Type evtType );

    QByteArray byEventData;
};

#endif // QDATAUPLOADEVENT_H
