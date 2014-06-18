#ifndef QDATADOWNLOADTHREAD_H
#define QDATADOWNLOADTHREAD_H

#include <QThread>
#include <QtNetwork>

class QDataDownloadThread : public QThread
{
    Q_OBJECT
public:
    static QDataDownloadThread* CreateThread( QObject* parent = NULL );

private:
    explicit QDataDownloadThread(QObject *parent = 0);
    void SendLog( QString &strLog, bool bStatic );

protected:
    void run( );
    void customEvent( QEvent *event );

    void InitializeSubThread( );

private:
    static QDataDownloadThread* pThreadInstance;
    QNetworkAccessManager httpManager;

signals:
    void Log( QString strLog, bool bStatic );

public slots:
    void HttpVerbFinished( QNetworkReply* reply );
};

#endif // QDATADOWNLOADTHREAD_H
