#ifndef QTCPPEERCLIENT_H
#define QTCPPEERCLIENT_H

#include "qmytcpsocket.h"

class QTcpPeerClient : public QMyTcpSocket
{
    Q_OBJECT
public:
    explicit QTcpPeerClient( QTextCodec* pCodec, QObject *parent = 0);
    ~QTcpPeerClient( );
    
private:

private:

signals:
    void EnqueueThread( QTcpSocket* pPeerSocket );
    void GetWholeTcpStreamData( QTcpSocket* pPeerSocket, void* pByteArray );
    
public slots:
    
private slots:
    void HandleDisconnected( );
    void HandleConnected( );
    void HandleError ( QAbstractSocket::SocketError socketError );

    void IncomingData( );
};

#endif // QTCPPEERCLIENT_H
