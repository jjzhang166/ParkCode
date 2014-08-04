#ifndef QUPLOADDATAEVENT_H
#define QUPLOADDATAEVENT_H

#include <QEvent>
#include <QStringList>
#include <QByteArray>

class QUploadDataEvent : public QEvent
{
public:
    typedef enum __UploadDataEvent {
        InOutRecord = User
    } UploadDataEvent;

    static QUploadDataEvent* CreateUploadDataEvent( UploadDataEvent eEvent );

    void SetRecordParams( QStringList& lstParam, QByteArray& byImage );
    QStringList& GetRecordParams( );
    QByteArray& GetImageData( );

private:
    QUploadDataEvent( Type eEvent );

    QStringList lstRecordParams;
    QByteArray byImageData;
};

#endif // QUPLOADDATAEVENT_H
