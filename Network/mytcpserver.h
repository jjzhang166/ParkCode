#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QtCore>
#include <QtNetwork>
#include "NetProcessData.h"
#include "peersocket.h"
#include "dataparserthread.h"

class CMyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CMyTcpServer( quint16 nThreadPool, QObject *parent = 0);
    ~CMyTcpServer( );

    QHash< QString, CPeerSocket* >& GetPeerSocketHash( );

protected:
    void incomingConnection( int socketDescriptor );

private:
    void GetKeyMsg( QTcpSocket* pSocket, QString& strKey, QString& strMsg, bool bConnected );
    bool GetMgmtTCPFlag( );

private:
    QHash< QString, CPeerSocket* > clientHash;
    QThreadPool* svrThreadPool;
    CManipulateMessage processMsg;
    CDataParserThread* pParserThread;

signals:
    void NotifyMessage( QString );
public slots:
    void HandleDisconnect( );
    void GetStream( );
    void GetMgmtStream( );
    void TcpError( QAbstractSocket::SocketError socketError );
};

#endif // MYTCPSERVER_H
