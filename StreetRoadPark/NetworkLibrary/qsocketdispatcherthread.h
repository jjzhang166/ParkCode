#ifndef QSOCKETDISPATCHERTHREAD_H
#define QSOCKETDISPATCHERTHREAD_H

#include "qsocketthread.h"

class QSocketDispatcherThread : public QThread
{
    Q_OBJECT
public:
    static QSocketDispatcherThread* CreateThread( QObject* pParent = 0 );
    ~QSocketDispatcherThread( );

    void PostDispatchSocketEvent( qintptr nSocket, int nPort);
    void PostSocketDisconnectionEvent( QTcpSocket* pSocket );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    typedef QQueue< QSocketThread* > QSocketThreadQueue;
    typedef QHash< qint32, QSocketThreadQueue * > QSocketThreadHash;
    typedef QMultiHash< QDataParserThread*, QSocketThread* > QParserSocketThreadHash;

    QSocketDispatcherThread(QObject *parent = 0);
    inline void PostEvent( QThreadEvent* pEvent );

    void ProcessSocketDispatchEvent( QThreadEvent* pEvent );
    void ProcessSocketDisconnectionEvent( QThreadEvent* pEvent );
    QSocketThread* FindSocketThread( );
    QSocketThreadQueue* FindSocketThreadQueue( qint32& nKey );
    void RemoveThreadFromQueue( QSocketThreadQueue* pQueue, QSocketThread* pThread );
    void FreeQueue( );

    inline void SendLog( QString& strLog, bool bStatic );

private:
    QSocketThreadHash hashSocketThreads;
    QParserSocketThreadHash hashParserSocketThread;
    qint32 nSocketCountEachServerThread;
    qint32 nServerThreadCountEachDataParser;
    qint32 nSocketThreadSleepTime;
    qint32 nDataDispatcherParserCount;
    CNetConfigurator* pConfig;
    
signals:
    void Log( QString strLog, bool bStatic );

public slots:

private slots:
    void HandleLog( QString strLog, bool bStatic );
    
};

#endif // QSOCKETDISPATCHERTHREAD_H
