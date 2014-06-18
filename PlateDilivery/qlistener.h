#ifndef QLISTENER_H
#define QLISTENER_H

#include <QThread>
#include "qmytcpserver.h"

class QListener : public QThread
{
    Q_OBJECT
public:
    explicit QListener(QObject *parent = 0);

protected:
    void run( );

private:
    QMyTcpServer* pTcpServer;

signals:
    void Accept( int socketDescriptor );
    
public slots:
    
private slots:
    void HandleAccept( int socketDescriptor );
};

#endif // QLISTENER_H
