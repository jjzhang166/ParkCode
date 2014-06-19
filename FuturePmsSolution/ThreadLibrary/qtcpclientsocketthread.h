#ifndef QTCPCLIENTSOCKETTHREAD_H
#define QTCPCLIENTSOCKETTHREAD_H

#include "qmybasethread.h"
#include "Event/qtcpclientthreadevent.h"

class QTcpClientSocketThread : public QMyBaseThread
{
    Q_OBJECT
public:
    static QTcpClientSocketThread* GetInstance( );
    ~QTcpClientSocketThread( );

protected:
    explicit QTcpClientSocketThread(QObject *parent = 0);

    void run( );
    void InitializeSubThread( );
    virtual void customEvent( QEvent* event );

private:
    void ProcessSendDataEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void ProcessConnectEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void ProcessDisconnectEvent( MyDataStructs::PQQueueEventParams pEventParams );

private:
    QTcpClient* pClientSocket;

signals:
    void GetWholeTcpStreamData( QTcpSocket* pPeerSocket, void* pByteArray );

public slots:

private slots:
    void HandleGetWholeTcpStreamData( QTcpSocket* pPeerSocket, void* pByteArray );
    
};

#endif // QTCPCLIENTSOCKETTHREAD_H
