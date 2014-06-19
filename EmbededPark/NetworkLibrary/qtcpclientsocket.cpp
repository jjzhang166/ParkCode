#include "qtcpclientsocket.h"

QTcpClientSocket::QTcpClientSocket(QObject *parent) :
    QMyTcpSocket(parent)
{
    bPeerSocket = false;
    connect( this, SIGNAL( connected( ) ), this, SLOT( HandleConnected( ) ) );
    connect( this, SIGNAL( disconnected( ) ), this, SLOT( HandleDisconnected( ) ) );
}

QTcpClientSocket::~QTcpClientSocket( )
{

}

void QTcpClientSocket::HandleConnected( )
{
    emit ConnectFinished( this, false );
}

void QTcpClientSocket::HandleDisconnected( )
{
    emit DisconnectFinished( this, false );
}
