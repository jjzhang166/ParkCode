#ifndef QFTPTHREAD_H
#define QFTPTHREAD_H

#include <QThread>
#include <QtNetwork>
#include "qftpevent.h"
#include <wininet.h>

class QFtpThread : public QThread
{
    Q_OBJECT
public:
    static QFtpThread* CreateInstance( );

    void PostUploadFileEvent( QString& strName, QByteArray& byFileData );
    void PostDownloadFileEvent( QString& strName );

protected:
    void run( );
    void customEvent( QEvent* pEvent );
    bool ThreadInitialize( );
    void ThreadUninitialize( );

private:
    explicit QFtpThread(QObject *parent = 0);
    void GetFtpUrl( QUrl& url, QString& strName );

    void Encoding( QString &strRaw, QString &strResult );
    void Decoding( QString &strRaw, QString &strResult );

    void ProcessUploadFileEvent( QFtpEvent* pEvent );
    void ProcessDownloadFileEvent( QFtpEvent* pEvent );

    inline void PostEvent( QFtpEvent *pEvent );
    void EmitLog( QString& strLog );

    void ConnectFtp( );

    static void CALLBACK MyInternetStatusCallback(
              HINTERNET hInternet,
              DWORD_PTR dwContext,
              DWORD dwInternetStatus,
              LPVOID lpvStatusInformation,
              DWORD dwStatusInformationLength
          );

private:
    static QFtpThread* pThreadInstance;
    QNetworkAccessManager* pNetworkAccessManager;
    QString strFtpHost;
    quint16 nFtpHostPort;
    QString strFtpUser;
    QString strFtpPwd;
    QString strFtpBasePath;
    HINTERNET hInternet;
    HINTERNET hFtpConnect;

signals:

private slots:
    void HandleNamFinished( QNetworkReply * reply );
    void HandleUploadReplyFinished( );
    void HandleUploadReplyError( QNetworkReply::NetworkError code );
};

#endif // QFTPTHREAD_H
