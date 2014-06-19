#ifndef QUDPSERVER_H
#define QUDPSERVER_H

#include "qmyudpsocket.h"

class QUdpServer : public QMyUdpSocket
{
    Q_OBJECT
public:
    explicit QUdpServer( QTextCodec* pCodec, QObject *parent = 0);
    ~QUdpServer( );
    
signals:
     void GetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort );
    
public slots:

private slots:
    void HandleError ( QAbstractSocket::SocketError socketError );

    void IncomingData( );
    
};

#endif // QUDPSERVER_H
