#ifndef CHECKTHREAD_H
#define CHECKTHREAD_H

#include <QThread>
#include <QString>
#include <QDate>

class CCheckThread : public QThread
{
    Q_OBJECT
public:
    explicit CCheckThread( QObject *parent = 0 );
    static CCheckThread& GetInstance( QObject *parent );
    bool GetBlob( QString& strParkID );
    bool Import2Database( );
    void GetEndDate( QDate& dtDate );

protected:
    void run( );

private:
    static CCheckThread* pThread;
    QByteArray byData;

signals:
    void ExpirationSender( QString strMsg, bool bExpiration, bool bRetry );

private slots:
    void ExitThread( );
    void DongleException( QString strMsg, bool bExit, bool bRetry );

};

#endif // CHECKTHREAD_H
