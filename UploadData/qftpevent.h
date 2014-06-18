#ifndef QFTPEVENT_H
#define QFTPEVENT_H

#include <QEvent>
#include <QtNetwork>

class QFtpEvent : public QEvent
{
public:
    typedef enum __FtpEvent {
        UploadFile = User,
        DownloadFile
    } FtpEvent;

    static QFtpEvent* CreateFtpEvent( FtpEvent eEvent );

    void SetFileName( QString& strName );
    QString& GetFileName( );

    void SetFileData( QByteArray& byData );
    QByteArray& GetFileData( );

private:
    QFtpEvent( FtpEvent eEvent );

private:
    QString strFileName;
    QByteArray byFileData;
};

#endif // QFTPEVENT_H
