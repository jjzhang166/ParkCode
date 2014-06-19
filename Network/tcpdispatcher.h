#ifndef TCPDISPATCHER_H
#define TCPDISPATCHER_H

#include <QObject>
#include "mytcpserver.h"

class CTcpDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit CTcpDispatcher(QObject *parent = 0);
    ~CTcpDispatcher( );
    bool InitServer( quint16 nPort, int nConnections, quint16 nThreadPool );
    void GetPeerSocketHash( QHash< QString, CPeerSocket* >*& peerHash );

private:
    CMyTcpServer* tcpServer;

signals:
    void NotifyMessage( QString strMsg );
public slots:
    void HandleMessage( QString strMsg );
};

#endif // TCPDISPATCHER_H
