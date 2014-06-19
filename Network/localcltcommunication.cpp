#include "localcltcommunication.h"

CLocalCltCommunication::CLocalCltCommunication( QTextCodec* pCodec, QObject *parent ) :
    QObject(parent)
{
    pTextCodec = pCodec;
    clientSocket.setParent( this );
    connect( &clientSocket, SIGNAL(disconnected( ) ), this, SLOT( HandleClientDisconnect( ) ) );
    connect( &clientSocket, SIGNAL( error( QLocalSocket::LocalSocketError ) ), this, SLOT( SocketError( QLocalSocket::LocalSocketError ) ) );
}

CLocalCltCommunication::~CLocalCltCommunication( )
{
    disconnect( &clientSocket, SIGNAL( disconnected( ) ), this, SLOT( HandleClientDisconnect( ) ) );
}

void CLocalCltCommunication::Connect2Server( )
{
    clientSocket.connectToServer( LOCAL_COMM_NAME );
}

void CLocalCltCommunication::Disconnect2Server( )
{
    clientSocket.close( );
}

void CLocalCltCommunication::SendData( QString &strMsg )
{
    if ( strMsg.isEmpty( ) ) {
        return;
    }

#ifndef QT_NO_DEBUG
    qDebug( ) << strMsg << endl;
#endif
    QByteArray byData = pTextCodec->fromUnicode( strMsg );
    clientSocket.write( byData );
}

void CLocalCltCommunication::HandleClientDisconnect( )
{
    QLocalSocket* pSocket = qobject_cast< QLocalSocket* >( sender( ) );
    if ( QLocalSocket::UnconnectedState == pSocket->state( ) ) {
        Connect2Server( );
    }
}

void CLocalCltCommunication::SocketError( QLocalSocket::LocalSocketError )
{
    QLocalSocket* pSocket = qobject_cast< QLocalSocket* >( sender( ) );
    emit NotifyMsg( pSocket->errorString( ) );
}
