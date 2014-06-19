#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtNetwork>
#ifdef PARKDATARECEIVER_APP
#include "../Common/logicinterface.h"
#else
#include "Common/logicinterface.h"
#endif
#include "mainwindow.h"

class CNetwork : public QObject
{
    Q_OBJECT
public:
    explicit CNetwork(QObject *parent = 0);

    void BroadcastDatagram( CommonDataType::DatagramType dgType, QStringList& lstData );
    void BroadcastDatagram( CommonDataType::DatagramType dgType, QStringList& lstData, QString& strDestIP );

    static CNetwork& Singleton( QObject* parent = 0 );

private:
    void InitBroadcastSocket( );
    void Server( );
    void ProcessData( QByteArray& byData );
    void GetTargetHostIP( );
    void MultiCastData( const QByteArray& byData );
    void OrgnizeData( CommonDataType::DatagramType dgType, QStringList& lstData, QByteArray& byType );
    bool CheckNetwork( );

signals:
    void OnReceiveDatagram( QStringList& lstData );

public slots:
    void DataMayRead( );
private:
    typedef WINAPI BOOL ( *IsNetworkAlive ) ( LPDWORD lpdwFlags );
    QUdpSocket* udpClient;
    QUdpSocket* udpBroadcastServer;
    QUdpSocket* udpLoopbackServer;
    QTextCodec* pCodec;
    MainWindow* pParent;
    HMODULE hDllMod;
    IsNetworkAlive MyIsNetworkAlive;
    static CNetwork* pNetwork;
    bool bMultiCast;
    QStringList lstTargetHostIP;
};

#endif // NETWORK_H
