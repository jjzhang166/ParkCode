#ifndef QLISTENERTHREAD_H
#define QLISTENERTHREAD_H

#include "qmytcpserver.h"
#include "qsocketdispatcherthread.h"
#include "qlikebroadcastthread.h"

class QListenerThread : public QThread
{
    Q_OBJECT
public:
    static QListenerThread* CreateThread( QObject* pParent = 0 );

    void PostStartListenEvent( quint16 nPort, qint32 nMaxConn );
    void PostStopListenEvent( );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    QListenerThread(QObject *parent = 0);

    inline void StopServer( );
    inline void StartServer( QThreadEvent* pEvent );

    inline void SendLog( QString& strLog, bool bStatic );
    inline void PostEvent( QThreadEvent *pEvent );

    void ConnectAccept( bool bConnect );
private:
    QSocketDispatcherThread* pSocketDispatcher;
    QMyTcpServer* pTcpServer;
    
signals:
    void Log( QString strLog, bool bStatic );
    
protected slots:
    void HandleAccept( qintptr socketDescriptor );
    void HandleLog( QString strLog, bool bStatic );
    void HandleAcceptError( QAbstractSocket::SocketError socketError );
    
};

#endif // QLISTENERTHREAD_H
