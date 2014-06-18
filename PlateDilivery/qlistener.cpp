#include "qlistener.h"

QListener::QListener(QObject *parent) :
    QThread(parent)
{
    pTcpServer = new QMyTcpServer( this );
    connect( pTcpServer, SIGNAL( Accept( int ) ), this, SLOT( HandleAccept( int ) ) );
}

void QListener::run( )
{
    pTcpServer->listen( QHostAddress::Any,( quint16 ) 60000 );
    exec( );
}

void QListener::HandleAccept( int socketDescriptor )
{
    emit Accept( socketDescriptor );
}
