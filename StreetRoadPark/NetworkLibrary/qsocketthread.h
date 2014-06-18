#ifndef QSOCKETTHREAD_H
#define QSOCKETTHREAD_H

#include "qdataparserthread.h"

class QSocketThread : public QThread
{
    Q_OBJECT
public:
    ~QSocketThread( );
    static QSocketThread* CreateThread( QObject* pParent = NULL );
    void SetDispatcherThread( QThread* pThread );
    void SetThreadStartSleepTime(  );
    bool TimerRecycle( qint32 nInterval /*Minute*/ );

    void PostAttachSocketEvent( qintptr nSocket, int nPort );
    void SetDataParser( QDataParserThread* pThread );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    typedef QQueue< QTcpSocket* > QSocketQueue;
    typedef QHash< QString, QTcpSocket* > QHostSocketHash;
    QSocketThread( QObject *parent = 0);

    void ProcessServerAttachSocketEvent( QThreadEvent* pEvent );
    void ProcessServerSendDataEvent( QThreadEvent* pEvent );

    void ConnectSocketEvent( QTcpSocket* pSocket );
    inline void PostEvent( QThreadEvent* pEvent );

    inline void SendLog( QString& strLog, bool bStatic );
    void RemoveSocketFromQueue( QSocketQueue* pQueue, QTcpSocket* pSocket );

private:
    QDataParserThread* pDataParserThread;
    QThread* pDispatcherThread;
    qint64 nThreadStartSleepTime;
    QByteArray byTokenData;
    CNetConfigurator* pConfig;

    QSocketQueue attachedSocketQueue;
    QSocketQueue detachedSocketQueue;
    
signals:
    void Log( QString strLog, bool bStatic );
    void DataIncoming( QTcpSocket* pSocket, QByteArray* pByteArray );
    
protected slots:
    void HandleDataIncoming( );
    void HandleConnectFinished( );
    void HandleDisconnectFinished( );
    void HandleError( QAbstractSocket::SocketError socketError );
};

#endif // QSOCKETTHREAD_H
