#ifndef QSOCKETDISPATCHERTHREAD_H
#define QSOCKETDISPATCHERTHREAD_H

#include "qsocketthread.h"

class QSocketDispatcherThread : public QMyThread
{
    Q_OBJECT
public:
    static QSocketDispatcherThread* GetSingletonInstance( QObject* pParent = 0 );
    ~QSocketDispatcherThread( );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    typedef QQueue< QSocketThread* > QSocketThreadQueue;
    typedef QHash< qint32, QSocketThreadQueue * > QSocketThreadHash;
    typedef QMultiHash< QDataParserThread*, QSocketThread* > QParserSocketThreadHash;

    QSocketDispatcherThread(QObject *parent = 0);
    void SocketThreadExit( );
    void DataParserThreadExit( QSocketThread* pThread );
    void ProcessSocketDispatchEvent( QCommonLibrary::EventParam& uParam );
    void ProcessSocketDisconnectionEvent( QCommonLibrary::EventParam& uParam );
    void ProcessTimerRecycleSocketThreadEvent( );
    QSocketThread* FindSocketThread( );
    QSocketThreadQueue* FindSocketThreadQueue( qint32& nKey );
    void RemoveThreadFromQueue( QSocketThreadQueue* pQueue, QSocketThread* pThread );

private:
    static QSocketDispatcherThread* pThreadInstance;
    QSocketThreadHash hashSocketThreads;
    QParserSocketThreadHash hashParserSocketThread;
    qint32 nSocketCountEachServerThread;
    qint32 nServerThreadCountEachDataParser;
    qint32 nSocketThreadSleepTime;
    
signals:
    
public slots:
    
};

#endif // QSOCKETDISPATCHERTHREAD_H
