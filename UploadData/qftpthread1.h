#ifndef QFTPTHREAD_H
#define QFTPTHREAD_H

#include <QThread>
#include <QFtp>
#include <QHash>
#include <QStringList>
#include "qftpthreadevent.h"

class QFtpThread : public QThread
{
    Q_OBJECT
public:
    static QFtpThread* CreateInstance( QObject* pParent = NULL );
    void PostUploadFileEvent( QString& strFileName, QByteArray& byImageData );
    void SetFtpServer( QStringList& lstParams );

protected:
    void run( );
    void customEvent( QEvent* e );

private:
    explicit QFtpThread(QObject *parent = 0);
    void ProcessUploadFile( QFtpThreadEvent* pEvent );

    inline void PostEvent( QFtpThreadEvent* pEvent );

private:
    static QFtpThread* pThreadInstance;
    QFtp ftpClient;
    QHash< int, QByteArray* > dataHash;
    QStringList lstFtpServer;
    
signals:
    
private slots:
    void ThreadExit( );
    void FtpCmdFinished( int nId, bool bError );
    void StateChanged( int nState );
    void FtpCommandStarted( int nId );
};

#endif // QFTPTHREAD_H
