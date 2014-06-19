#ifndef QUDPCLIENT_H
#define QUDPCLIENT_H

#include "qmyudpsocket.h"

class QUdpClient : public QMyUdpSocket
{
    Q_OBJECT
public:
    explicit QUdpClient( QTextCodec* pCodec, QObject *parent = 0);
    ~QUdpClient( );
    
signals:
    void GetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort );
    
public slots:

private slots:
    void HandleError ( QAbstractSocket::SocketError socketError );

    void IncomingData( );
    
};

#endif // QUDPCLIENT_H
