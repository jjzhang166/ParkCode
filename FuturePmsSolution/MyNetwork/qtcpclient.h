#ifndef QTCPCLIENT_H
#define QTCPCLIENT_H

#include "qmytcpsocket.h"

class QTcpClient : public QMyTcpSocket
{
    Q_OBJECT
public:
    explicit QTcpClient( QTextCodec* pCodec, QObject *parent = 0);
    ~QTcpClient( );

    bool Connect2Server( const QHostAddress &hostAddr, quint16 nPort );

private:
    void Connect2Host( );

private:
    QHostAddress serverAddress;
    quint16 nServerPort;
    
signals:
    void GetWholeTcpStreamData( QTcpSocket* pPeerSocket, void* pByteArray );

protected:
    void timerEvent( QTimerEvent * event );
    
public slots:
    
private slots:
    void HandleDisconnected( );
    void HandleConnected( );
    void HandleError ( QAbstractSocket::SocketError socketError );

    void IncomingData( );
};

#endif // QTCPCLIENT_H
