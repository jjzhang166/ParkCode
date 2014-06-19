#ifndef UDPDISPATCHER_H
#define UDPDISPATCHER_H

#include <QObject>
#include <QtCore>
#include <QtNetwork>
#include "netprocessdata.h"
#include <Winsock2.h>
#include "dataparserthread.h"
#include "../Common/commonfunction.h"

class CUdpDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit CUdpDispatcher(QObject *parent = 0);
    ~CUdpDispatcher( );

public:
    bool InitServer( quint16 nPort, quint16 nThreadPool );
    quint64 SendData( QByteArray &byData, const QHostAddress& hostAddr, quint16 nPort );

private:
    QUdpSocket udpServer;
    QThreadPool* svrThreadPool;
    struct sockaddr_in peerAddr;
    int nPeerSize;
    CDataParserThread* pParserThread;
    QSettings* pSettings;

signals:
    void NotifyMessage( QString );

public slots:
    void GetDatagrams( );
    void UdpError( QAbstractSocket::SocketError socketError );

};

#endif // UDPDISPATCHER_H
