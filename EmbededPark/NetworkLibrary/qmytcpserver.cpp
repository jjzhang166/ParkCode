#include "qmytcpserver.h"

QMyTcpServer::QMyTcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

void QMyTcpServer::incomingConnection( qintptr socketDescriptor )
{
    emit Accept( socketDescriptor );
}
