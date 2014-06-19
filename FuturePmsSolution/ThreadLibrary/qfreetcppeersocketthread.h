#ifndef QFREETCPPEERSOCKETTHREAD_H
#define QFREETCPPEERSOCKETTHREAD_H

#include "QMyBaseThread.h"
#include "Event/qfreetcppeersocketthreadevent.h"

class QFreeTcpPeerSocketThread : public QMyBaseThread
{
    Q_OBJECT
public:
    static QFreeTcpPeerSocketThread* GetSingleton( );
    ~QFreeTcpPeerSocketThread( );

protected:
    explicit QFreeTcpPeerSocketThread(QObject *parent = 0);

    void run( );
    void InitializeSubThread( );
    virtual void customEvent( QEvent* event );

private:
    void ProcessCheckPeerThreadEvent( MyDataStructs::PQQueueEventParams pEventParams );

private:

private:
    static QFreeTcpPeerSocketThread* pThreadInstance;

signals:

public slots:

private slots:

};

#endif // QFREETCPPEERSOCKETTHREAD_H
