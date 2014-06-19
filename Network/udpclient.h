#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QUdpSocket>
#include <QHostAddress>
#include "netcommfunction.h"
#include <QTextCodec>

class CUdpClient : public QUdpSocket
{
    Q_OBJECT
public:
    explicit CUdpClient(QObject *parent = 0);

    bool Connect2Server( const QHostAddress &hostAddr, quint16 nPort );
    void SetTextCodec( QTextCodec* pCodec );
    quint64 SendData( QByteArray &byData );

private:
    QHostAddress svrAddr;
    quint16 nSvrPort;
    QTextCodec* pTextCodec;

signals:
    void NotifyMessage( QString );

public slots:
    void UdpError( QAbstractSocket::SocketError socketError );

};

#endif // UDPCLIENT_H
