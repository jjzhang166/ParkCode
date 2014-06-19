#include "localsvrcommunication.h"

CLocalSvrCommunication* CLocalSvrCommunication::pLocalComm = NULL;

CLocalSvrCommunication::CLocalSvrCommunication( QTextCodec* pCodec, QObject *parent ) :
    QObject(parent)
{
    localServer.setParent( this );
    pTextCodec = pCodec;
    connect( &localServer, SIGNAL( newConnection( ) ), this, SLOT( AcceptConnection( ) ) );
}

CLocalSvrCommunication::~CLocalSvrCommunication( )
{
    localServer.close( );
}

CLocalSvrCommunication* CLocalSvrCommunication::GetInstance( QTextCodec* pCodec, QObject *parent )
{
    if ( NULL == pLocalComm ) {
        pLocalComm = new CLocalSvrCommunication( pCodec, parent );
    }

    return pLocalComm;
}

void CLocalSvrCommunication::ReleaseInstance( )
{
    if ( NULL != pLocalComm ) {
        delete pLocalComm;
        pLocalComm = NULL;
    }
}

void CLocalSvrCommunication::StartupServer( )
{
    bool bRet = localServer.listen( LOCAL_COMM_NAME );

    if ( !bRet ) {
        emit NotifyMsg( localServer.errorString( ) );
    }
}

void CLocalSvrCommunication::GetData( )
{
    QLocalSocket* pSocket = qobject_cast< QLocalSocket* >( sender( ) );

    quint64 nDataSize = pSocket->bytesAvailable( );
    if ( 0 == nDataSize ) {
        return;
    }

    QByteArray byData = pSocket->readAll( );
    QString strMsg( byData );
    emit NotifyMsg( strMsg );
}

void CLocalSvrCommunication::AcceptConnection( )
{
    if ( !localServer.hasPendingConnections( ) ) {
        return;
    }

    QLocalSocket* peerSocket = localServer.nextPendingConnection( );
    connect( peerSocket, SIGNAL( readyRead( ) ), this, SLOT( GetData( ) ) );
    connect( peerSocket, SIGNAL(disconnected( ) ), this, SLOT( HandleServerDisconnect( ) ) );
    connect( peerSocket, SIGNAL( error( QLocalSocket::LocalSocketError ) ), this, SLOT( SocketError( QLocalSocket::LocalSocketError ) ) );
}

void CLocalSvrCommunication::HandleServerDisconnect( )
{
    QLocalSocket* pSocket = qobject_cast< QLocalSocket* >( sender( ) );
    pSocket->close( );
    pSocket->deleteLater( );
}

void CLocalSvrCommunication::SocketError( QLocalSocket::LocalSocketError )
{
    QLocalSocket* pSocket = qobject_cast< QLocalSocket* >( sender( ) );
    emit NotifyMsg( pSocket->errorString( ) );
}
