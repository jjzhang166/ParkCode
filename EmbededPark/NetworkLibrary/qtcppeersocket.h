#ifndef QTCPPEERSOCKET_H
#define QTCPPEERSOCKET_H

#include "QMyTcpSocket.h"

class QTcpPeerSocket : public QMyTcpSocket
{
    Q_OBJECT
public:
    explicit QTcpPeerSocket(QObject *parent = 0);
    ~QTcpPeerSocket( );
    
signals:
    
protected slots:
    void HandleConnected( );
    void HandleDisconnected( );
};

#endif // QTCPPEERSOCKET_H
