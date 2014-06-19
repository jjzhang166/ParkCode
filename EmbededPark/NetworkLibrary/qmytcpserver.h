#ifndef QMYTCPSERVER_H
#define QMYTCPSERVER_H

#include <QTcpServer>

class QMyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QMyTcpServer(QObject *parent = 0);

protected:
    void incomingConnection( qintptr socketDescriptor );
    
signals:
    void Accept( qintptr socketDescriptor );
    
public slots:
    
};

#endif // QMYTCPSERVER_H
