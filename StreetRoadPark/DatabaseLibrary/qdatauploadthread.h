#ifndef QDATAUPLOADTHREAD_H
#define QDATAUPLOADTHREAD_H

#include <QThread>
#include <QtNetwork>
#include <QUrl>
#include "cdbconfigurator.h"
#include "qdatauploadevent.h"
//#include <QApplication>

class QDataUploadThread : public QThread
{
    Q_OBJECT
public:
    static QDataUploadThread* CreateThread( QObject* parent = NULL );
    ~QDataUploadThread( );

    void PostUploadEvent( const QByteArray& byData, QDataUploadEvent::UploadEvent evtType );

private:
    explicit QDataUploadThread(QObject *parent = 0);

    void HttpPost( const QByteArray& byData );
    void ConnectReplyEvent( QNetworkReply* reply );
    inline void SendLog( QString& strLog, bool bStatic );

protected:
    void run( );
    void customEvent( QEvent *event );

    void InitializeSubThread( );

private:
    static QDataUploadThread* pThreadInstance;
    QNetworkAccessManager httpManager;
    QNetworkRequest httRequest;
    QUrl* pUrl;
    CDbConfigurator* pConfigurator;
    //QByteArray byHttpData;

signals:
    void Log( QString strLog, bool bStatic );

public slots:
    void HttpMngrFinished( QNetworkReply* reply );
    void ReplyFinished( );
    void GetReplyData( );
    void HttpError( QNetworkReply::NetworkError errCode );
};

#endif // QDATAUPLOADTHREAD_H
