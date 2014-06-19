#ifndef QTCPCLIENTSOCKET_H
#define QTCPCLIENTSOCKET_H

#include "QMyTcpSocket.h"

class QTcpClientSocket : public QMyTcpSocket
{
    Q_OBJECT
public:
    explicit QTcpClientSocket(QObject *parent = 0);
    ~QTcpClientSocket( );
    
signals:
    
protected slots:
    void HandleConnected( );
    void HandleDisconnected( );
    
};

#endif // QTCPCLIENTSOCKET_H
