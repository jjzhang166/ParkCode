#include "qmytcpserver.h"

QMyTcpServer::QMyTcpServer( QObject *parent ) :
    QTcpServer(parent)
{    
    setObjectName( "QMyTcpServer" );
}

QMyTcpServer::~QMyTcpServer( )
{
    if ( isListening( ) ) {
        close( );
    }
}

void QMyTcpServer::incomingConnection( int socketDescriptor )
{
    emit Accept( socketDescriptor );
}
