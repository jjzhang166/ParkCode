#ifndef QTHREADEVENT_H
#define QTHREADEVENT_H

#include <QThread>
#include <QEvent>
#include <QGuiApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QQueue>
#include <QtEndian>
#include <QDateTime>
#include <QHostAddress>
#include "cnetconfigurator.h"

#define DATA_TOKEN      "StreetRoadPark"

class QThreadEvent : public QEvent
{
public:
    ~QThreadEvent( );
    typedef enum __ThreadType {
        ThreadListener,
        ThreadSocket,
        ThreadParser,
        ThreadDispatcher,
        ThreadMulticast
    } ThreadType;

    typedef enum __EventType {
        EventStartListen = User,
        EventStopListen, // ListenerThread

        EventDispatchSocket,
        EventSocketDisconnection, // DispatcherThread

        EventAttachSocketDescriptor,
        EventServerSendData, // SocketThread

        EventTCPData,
        EventUDPData, // ParserThread

        EventMulticastData
    } EventType;

    static QThreadEvent* CreateThreadEvent( ThreadType thrType, EventType evtType );

    void SetListenPort( const quint16 nPort );
    quint16 GetListenPort( ) const;

    void SetMaxPendingConnection( const qint32 nMaxConn );
    qint32 GetMaxPendingConnection( ) const;

    void SetSocketDescriptor( const qintptr nSocket );
    qintptr GetSocketDescriptor( ) const;

    void SetPeerSocket( QTcpSocket* pSocket );
    QTcpSocket* GetPeerSocket( ) const;

    void SetByteArray( const QByteArray& byByteArray );
    QByteArray& GetByteArray( );

    void SetPackageType( qint32 nType );
    qint32 GetPackageType( );

private:
    QThreadEvent( ThreadType thrType, Type evtType );
    ThreadType typeThread;
    EventType typeEvent;

    quint16 tcpServerPort;
    qint32 nMaxPendingConnection;

    qintptr nSocketDescriptor;
    QTcpSocket* pPeerSocket;

    QByteArray byEventByteArray;

    qint32 nPackageType;
};

#endif // QTHREADEVENT_H
