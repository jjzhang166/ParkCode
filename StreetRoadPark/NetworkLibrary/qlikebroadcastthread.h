#ifndef QLIKEBROADCASTTHREAD_H
#define QLIKEBROADCASTTHREAD_H

#include <QThread>
#include "qmytcpserver.h"
#include <QTcpSocket>
#include <QList>
#include "qthreadevent.h"

class QLikeBroadcastThread : public QThread
{
    Q_OBJECT
public:
    static QLikeBroadcastThread* CreateThread( QObject* pParent = 0 );
    void PostMulticastSocketEvent( QByteArray& byData );
    void PostStartListenEvent( );
    void PostStopListenEvent( );

protected:
    void run( );
    virtual void customEvent( QEvent* event );

private:
    explicit QLikeBroadcastThread(QObject *parent = 0);
    inline void SendLog( QString& strLog, bool bStatic );
    void InitializeSubThread( );
    void ConnectSocketEvent( QTcpSocket *pSocket );
    inline void PostEvent( QThreadEvent* pEvent );
    void ConnectAccept( bool bConnect );

    inline void StartServer( QThreadEvent *pEvent );
    inline void StopServer( );

private:
    QMyTcpServer* pTcpServer;
    static QLikeBroadcastThread* pThreadInstance;
    QList< QTcpSocket* > lstPeers;
    int nListenerPort;

signals:
    void Log( QString strLog, bool bStatic );

protected slots:
    void HandleDataIncoming( );
    void HandleConnectFinished( );
    void HandleDisconnectFinished( );
    void HandleAccept( qintptr socketDescriptor );
    void HandleAcceptError( QAbstractSocket::SocketError socketError );
    void HandleError( QAbstractSocket::SocketError socketError );
};

#endif // QLIKEBROADCASTTHREAD_H
