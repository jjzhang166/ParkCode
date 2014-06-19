#ifndef QTHREADGENERATOR_H
#define QTHREADGENERATOR_H

#include "ThreadLibrary_global.h"
#include "ThreadModule.h"
#include <QQueue>

class THREADLIBRARYSHARED_EXPORT QThreadGenerator : public QObject
{
    Q_OBJECT
public:
    static QThreadGenerator* GetSingleton( );

    QTcpClientSocketThread* GenerateTcpClientThread( );
    QUdpSenderThread* GenerateUdpClientThread( );

    QListenerThread* GenerateTcpListenerThread( );
    QUdpReceiverSocketThread* GenerateUdpListenerThread( const bool bServer, const MyEnums::UdpDatagramType dgType );

    QLoggerThread* GenerateLogThread( );

    void ControlTimer( const bool bStart, const int nPeerThreadInterval, const int nDatabaseThreadInterval );

    // Free qQueueEventParams in Event destructor
    void SendEvent( MyEnums::ThreadType thread, MyEnums::EventType event,
                    MyDataStructs::PQQueueEventParams pQueueEventParams = NULL, QThread* pReceiver = NULL );
    void PostEvent( MyEnums::ThreadType thread, MyEnums::EventType event,
                    MyDataStructs::PQQueueEventParams pQueueEventParams = NULL, QThread* pReceiver = NULL );

protected:
    explicit QThreadGenerator(QObject *parent = 0);
    void	timerEvent ( QTimerEvent * event );

private:
    void PostLoggerEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );

    void PostTcpListenerEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );
    void PostTcpPeerEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );
    void PostTcpClientEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );

    void PostUdpListenerEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );
    void PostUdpClientEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );

    void PostFreeTcpPeerSocketThreadEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );
    void PostFreeDatabaseObjectThreadEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );

private:
    static QThreadGenerator* pThreadGenerator;
    int nThreadReleaseTimerID;
    int nDatabaseReleaseTimerID;
    
signals:
    
public slots:

private slots:
    void HandleMessage( void* pstrMsg, QManipulateIniFile::LogTypes type );
    void HandleAccept( int socketDescriptor );
    void HandlePeerThreadReleaseMyself( QTcpPeerSocketThread* pThread );
};

#endif // QTHREADGENERATOR_H
