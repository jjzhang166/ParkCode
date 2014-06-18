#ifndef QFTPTHREADEVENT_H
#define QFTPTHREADEVENT_H

#include <QEvent>
#include <QString>
#include <QByteArray>

class QFtpThreadEvent : public QEvent
{
public:
    typedef enum __FtpEvent {
        UploadFile = User
    } FtpEvent;

    static QFtpThreadEvent* CreateEvent( FtpEvent eEvent );

    void SetFileName( QString& strName );
    QString& GetFileName( );

    void SetImageData( QByteArray& byData );
    QByteArray& GetImageData( );

private:
    QFtpThreadEvent( FtpEvent eEvent );

private:
    QString strFileName;
    QByteArray byImageData;
};

#endif // QFTPTHREADEVENT_H
