#include "qtcppeersocket.h"

QTcpPeerSocket::QTcpPeerSocket(QObject *parent) :
    QMyTcpSocket(parent)
{
    bPeerSocket = true;
    connect( this, SIGNAL( connected( ) ), this, SLOT( HandleConnected( ) ) );
    connect( this, SIGNAL( disconnected( ) ), this, SLOT( HandleDisconnected( ) ) );
}

QTcpPeerSocket::~QTcpPeerSocket( )
{

}

void QTcpPeerSocket::HandleConnected( )
{
    emit ConnectFinished( this, true );
}

void QTcpPeerSocket::HandleDisconnected( )
{
    emit DisconnectFinished( this, true );
}
