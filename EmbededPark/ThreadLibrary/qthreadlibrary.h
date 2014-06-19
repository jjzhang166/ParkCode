#ifndef QTHREADLIBRARY_H
#define QTHREADLIBRARY_H

#include "ThreadLibrary_global.h"
#include "qlistenerthread.h"

class THREADLIBRARYSHARED_EXPORT QThreadLibrary : public QObject
{
    Q_OBJECT
public:
    QThreadLibrary( );
    ~QThreadLibrary( );

    void PostListenerThreadEvent( QCommonLibrary::ThreadEventType eEvent );
    void PostClientSocketThreadEvent( QCommonLibrary::ThreadEventType eEvent,
                                      QCommonLibrary::EventParam& uParam,
                                      bool bSingelton,
                                      QObject* pUIReceiver = NULL );

private:
    typedef QHash< QString, QSocketThread* > QSocketThreadHash;

    void PostSingeltonEvent( QCommonLibrary::ThreadEventType eEvent,
                             QCommonLibrary::EventParam& uParam,
                             QObject* pUIReceiver );
    void PostInstanceEvent( QCommonLibrary::ThreadEventType eEvent,
                            QCommonLibrary::EventParam& uParam,
                            QObject* pUIReceiver );
    void PostEventByHash( QCommonLibrary::ThreadEventType eEvent,
                           QCommonLibrary::EventParam& uParam,
                           QThreadLibrary::QSocketThreadHash* pHash );
    void PostClientEvent( QCommonLibrary::ThreadEventType eEvent, QCommonLibrary::EventParam& uParam,
                          QSocketThread* pThread );

    void InitializePointer( );
    void ListenerThreadEixt( );
    void ClientThreadExit( QThreadLibrary::QSocketThreadHash* pHash );
    void GetKey( QString& strKey, QCommonLibrary::EventParam& uParam );
    void ChangeHash( QTcpSocket* pSocket, bool bReconnect );
    inline void ConnectClientSocktThreadEvent( QSocketThread* pThread );

private:

    QListenerThread* pListenerThread;
    QSocketThreadHash* pClientConnectHash;
    QSocketThreadHash* pClientDisconnectHash;

signals:
    void DisplayLog( QString strText );

protected slots:
    void HandleClientReconnect( QTcpSocket* pSocket );
    void HandleClientDisconnect( QTcpSocket* pSocket );
    void HandleDisplayLog( QString strText );
    void HandleErrorCode( QTcpSocket* pSocket );
};

#endif // QTHREADLIBRARY_H
