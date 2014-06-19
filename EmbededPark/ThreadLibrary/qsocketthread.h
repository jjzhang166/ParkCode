#ifndef QSOCKETTHREAD_H
#define QSOCKETTHREAD_H

#include "qdataparserthread.h"
#include "../NetworkLibrary/qnetworklibrary.h"

class QSocketThread : public QMyThread
{
    Q_OBJECT
public:
    ~QSocketThread( );
    static QSocketThread* GetSingletonInstance( bool bServerSide, QObject* pUIReceiver = 0, QObject* pParent = 0);
    static QSocketThread* GetInstance( bool bServerSide, QDataParserThread* pDataParser, QObject* pUIReceiver = 0, QObject* pParent = 0 );
    void SetDispatcherThread( QThread* pThread );
    void SetThreadStartSleepTime(  );
    bool TimerRecycle( qint32 nInterval /*Minute*/ );

    void PostClientConnectEvent( QCommonLibrary::EventParam& uParam );
    void PostClientDisconnectEvent( QCommonLibrary::EventParam& uParam );
    void PostClientSendDataEvent( QCommonLibrary::EventParam& uParam );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    typedef QHash< QString, QTcpSocket* > QHostSocketHash;
    QSocketThread( bool bServerSide, QDataParserThread* pDataParser, QObject *parent = 0);
    inline QTcpSocket* GetTargetSocket( QCommonLibrary::EventParam& uParam );
    inline void GetKey( QCommonLibrary::EventParam& uParam, QString& strKey );
    static QSocketThread* CreateThread( bool bServerSide, QDataParserThread* pDataParser, QObject* pUIReceiver, QObject* pParent );
    void ProcessServerAttachSocketEvent( QCommonLibrary::EventParam& uParam );
    void ProcessServerDetachSocketEvent( QCommonLibrary::EventParam& uParam );
    void ProcessServerSendDataEvent( QCommonLibrary::EventParam& uParam );
    void ProcessClientSendDataEvent( QCommonLibrary::EventParam& uParam );
    void ProcessClientConnectionEvent( QCommonLibrary::EventParam& uParam );
    void ProcessClientDisconnectionEvent( QCommonLibrary::EventParam& uParam );
    void FreeNetwork( );

private:
    QNetworkLibrary* pNetwork;
    static QSocketThread* pThreadInstance;
    bool bServerSideThread;
    QDataParserThread* pDataParserThread;
    QThread* pDispatcherThread;
    qint64 nThreadStartSleepTime;
    QHostSocketHash* pHostSocketHash;
    
signals:
    void ClientReconnect( QTcpSocket* pSocket );
    void ClientDisconnect( QTcpSocket* pSocket );
    void ErrorCode( QTcpSocket* pSocket );
    void DataIncoming( QTcpSocket* pSocket, QByteArray* pByteArray );
    
protected slots:
    void HandleDataIncoming( void* pSocket, void* pByteArray );
    void HandlePeerDisconenct( QTcpSocket* pSocket );
    void HandleErrorInfo( qint32 logType, QString strText );
    void HandleErrorCode( QTcpSocket* pSocket );
    void HandleClientReconnect( QTcpSocket* pSocket );
    void HandleClientDisconnect( QTcpSocket* pSocket );
};

#endif // QSOCKETTHREAD_H
