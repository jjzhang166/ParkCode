#ifndef QUDPRECEIVERSOCKETTHREAD_H
#define QUDPRECEIVERSOCKETTHREAD_H

#include "qmybasethread.h"
#include "Event/qudpreceiverthreadevent.h"
#include "../MyNetwork/qudpserver.h"

#include "qdatabasethread.h"
#include "Event/qdatabasethreadevent.h"

class QUdpReceiverSocketThread : public QMyBaseThread
{
    Q_OBJECT
public:
    static QUdpReceiverSocketThread* GetInstance( bool bServer, const MyEnums::UdpDatagramType dgType );
    ~QUdpReceiverSocketThread( );

    void SetServerFlag( bool bServer );

protected:
    explicit QUdpReceiverSocketThread( const MyEnums::UdpDatagramType dgType, QObject *parent = 0);

    void run( );
    void InitializeSubThread( );
    virtual void customEvent( QEvent* event );

private:
    quint32 GetIniValue( const QManipulateIniFile::IniFileSectionItems item );
    void ProcessDatabaseData( QByteArray* pByteArray, const QString& strSenderIP, const quint16 nSenderPort );
    void ProcessOtherData( QByteArray* pByteArray, const QString& strSenderIP, const quint16 nSenderPort );

    void ProcessStartupListeningEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void ProcessJoinMulticastEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void ProcessLeaveMulticastEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void ProcessBroadcastDatagramEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void ProcessSendDatagramEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void ProcessThreadPoolFeedbackEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void PostDatabaseEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );

private:
    MyEnums::UdpDatagramType udpDatagramType;
    QDatabaseThread* pDatabaseThread;
    QThreadPool peerThreadPool;
    bool bServerEnd;
    QUdpServer* pUdpServerSocket;

signals:
    void GetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort, MyEnums::UdpDatagramType dgType );

public slots:

private slots:
    void HandleGetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort );

};

#endif // QUDPRECEIVERSOCKETTHREAD_H
