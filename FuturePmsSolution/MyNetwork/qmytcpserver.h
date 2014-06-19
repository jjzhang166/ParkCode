#ifndef QMYTCPSERVER_H
#define QMYTCPSERVER_H

#include <QTcpServer>
#include "../ManipulateIniFile/qmanipulateinifile.h"

class QMyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QMyTcpServer( quint16 nPort, int nMaxConnections, QObject *parent = 0);
    ~QMyTcpServer( );

    void Initialize( );

protected:
    void incomingConnection( int socketDescriptor );

private:
    void Initialize( quint16 nPort, int nMaxConnections );
    
signals:
    void Accept( int socketDescriptor );
    void NotifyMessage( void* pstrMsg, QManipulateIniFile::LogTypes type );

private:
    quint16 nServerPort;
    int nPendingMaxConnection;
    
public slots:

private slots:
    
};

#endif // QMYTCPSERVER_H
