#ifndef HTTP_H
#define HTTP_H

// Communicate with webserver
#include <QObject>
#include <QtNetwork>
#include <QMutex>
#include "CommonData.h"
#include <QTextCodec>

class CHttp : public QObject
{
    Q_OBJECT
public:
    explicit CHttp(QObject *parent = 0);

    void HttpGet( QString& strUrl );

    void HttpPut( QString& strUrl, QIODevice* pData );
    void HttpPut( QString& strUrl, const QByteArray& data );

    void HttpPost( QString& strUrl, QIODevice* pData );
    void HttpPost( QString& strUrl, const QByteArray& data );

    void HttpDelete( QString& strUrl );

    void HttpHead( QString& strUrl );

    void SetTextCodec( QTextCodec* pCodec );

private:
    void ConnectReplyEvent( QNetworkReply* reply );
    inline QNetworkRequest CreateRequest( QString& strUrl );

    void HandleGetResponse( QNetworkReply* reply );
    void HandlePutResponse( QNetworkReply* reply );
    void HandlePostResponse( QNetworkReply* reply );
    void HandleDeleteResponse( QNetworkReply* reply );
    void HandleHeadResponse( QNetworkReply* reply );
    void HandleCustomResponse( QNetworkReply* reply );
    void HandleUnknownResponse( QNetworkReply* reply );
    void ProcessResponse( QNetworkReply* reply );
    inline QByteArray& GetByteData( QNetworkReply* reply );

    inline void Sync( bool bLock );
    inline bool Trysync( );

private:
    QNetworkAccessManager manager;
    QMutex mutex;
    QTextCodec* pTextCodec;
    QByteArray byResponse[ QNetworkAccessManager::CustomOperation ];

signals:
    void NotifyMessage( QString strMsg );

private slots:
    void GetReplyData( );
    void MngrFinished( QNetworkReply* reply );
    void ReplyFinished( );
    void HttpError( QNetworkReply::NetworkError code );
    void DownloadProcess( qint64 bytesReceived, qint64 bytesTotal );
    void UploadProcess( qint64 bytesSent, qint64 bytesTotal );

};

#endif // HTTP_H
