#ifndef QMYTCPSERVER_H
#define QMYTCPSERVER_H

#include <QTcpServer>

class QMyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QMyTcpServer( QObject *parent = 0);
    ~QMyTcpServer( );

protected:
    void incomingConnection( int socketDescriptor );

private:
    
signals:
    void Accept( int socketDescriptor );

private:
    
public slots:

private slots:
    
};

#endif // QMYTCPSERVER_H
