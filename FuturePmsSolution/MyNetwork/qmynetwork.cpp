#include "qmynetwork.h"

QMyNetwork::QMyNetwork( QObject* parent ) : QObject( parent )
{
    qRegisterMetaType< QAbstractSocket::SocketError >( "QAbstractSocket::SocketError" );
    pTcpServer = NULL;
    setObjectName( "QMyNetwork" );
}

QMyNetwork::~QMyNetwork( )
{
    if ( NULL != pTcpServer ) {
        delete pTcpServer;
    }
}

void QMyNetwork::HandleGetWholeTcpStreamData( QTcpSocket* pPeerSocket, void *pByteArray )
{
    OutputMsg( "Sender:" + sender( )->objectName( ) + ":emit GetWholeTcpStreamData( ... )" );
    emit GetWholeTcpStreamData( pPeerSocket, pByteArray );
}

void QMyNetwork::HandleGetWholeUdpDatagram( void *pByteArray, QString strSenderIP, quint16 nSenderPort )
{
    OutputMsg( strSenderIP + ":" + QString::number( nSenderPort ) );
    OutputMsg( "Sender:" + sender( )->objectName( ) + ":emit GetWholeUdpDatagram( ... )" );
    emit GetWholeUdpDatagram( pByteArray, strSenderIP, nSenderPort );
}

void QMyNetwork::HandleThreadEnqueue( QTcpSocket* pPeerSocket )
{
    OutputMsg( "Sender:" + sender( )->objectName( ) + ":emit EnqueueThread( ... )" );
    emit EnqueueThread( pPeerSocket );
}

void QMyNetwork::StartupTcpServer( quint16 nPort, int nMaxConnections )
{
    if ( NULL == pTcpServer ) {
        pTcpServer = new QMyTcpServer( nPort, nMaxConnections );
        connect( pTcpServer, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ), this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );
        connect( pTcpServer, SIGNAL( Accept( int ) ), this, SLOT( HandleAccept( int ) ) );
        pTcpServer->Initialize( );
    }
}

QTcpPeerClient* QMyNetwork::GenerateTcpPeerSocket( QTextCodec* pCodec )
{
    QTcpPeerClient* pPeerSocket = new QTcpPeerClient( pCodec );
    connect( pPeerSocket, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ), this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );
    connect( pPeerSocket, SIGNAL( EnqueueThread( QTcpSocket* ) ), this, SLOT( HandleThreadEnqueue( QTcpSocket*  ) ) );
    connect( pPeerSocket, SIGNAL( GetWholeTcpStreamData( QTcpSocket*, void* ) ), this, SLOT( HandleGetWholeTcpStreamData( QTcpSocket*, void* ) ) );

    return pPeerSocket;
}

QTcpClient* QMyNetwork::GenerateTcpClientSocket( QTextCodec *pCodec )
{
    QTcpClient* pClientSocket = new QTcpClient( pCodec );
    connect( pClientSocket, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ), this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );
    connect( pClientSocket, SIGNAL( GetWholeTcpStreamData( QTcpSocket*, void* ) ), this, SLOT( HandleGetWholeTcpStreamData( QTcpSocket*, void* ) ) );

    return pClientSocket;
}

QUdpClient* QMyNetwork::GenerateUdpClientSocket( QTextCodec* pCodec )
{
    QUdpClient* pClientSocket = new QUdpClient( pCodec );
    connect( pClientSocket, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ),
             this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );
    connect( pClientSocket, SIGNAL( GetWholeUdpDatagram( void*, QString, quint16 ) ),
             this, SLOT( HandleGetWholeUdpDatagram( void*, QString, quint16 ) ) );

    return pClientSocket;
}

QUdpServer* QMyNetwork::GenerateUdpServerSocket( QTextCodec* pCodec )
{
    QUdpServer* pServerSocket = new QUdpServer( pCodec );
    connect( pServerSocket, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ),
             this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );
    connect( pServerSocket, SIGNAL( GetWholeUdpDatagram( void*, QString, quint16 ) ),
             this, SLOT( HandleGetWholeUdpDatagram( void*, QString, quint16 ) ) );

    return pServerSocket;
}

void QMyNetwork::HandleMessage( void* pstrMsg, QManipulateIniFile::LogTypes type )
{
    OutputMsg( "Sender:" + sender( )->objectName( ) + QString( ":emit NotifyMessage( %1, LogTypes=%2 ) " ).arg( *( QString* ) pstrMsg, QString::number( type ) ) );
    emit NotifyMessage( pstrMsg, type );
}

void QMyNetwork::HandleAccept( int socketDescriptor )
{
    OutputMsg( "Sender:" + sender( )->objectName( ) + QString( ":emit Accept( %1 )" ).arg( socketDescriptor ) );
    emit Accept( socketDescriptor );
}

bool QMyNetwork::TcpConnect2Server( QTcpClient* pTcpClient, const QHostAddress &hostAddr, quint16 nPort )
{
    return pTcpClient->Connect2Server( hostAddr, nPort );
}

quint64 QMyNetwork::TcpSendData( QMyTcpSocket* pTcpSocket,  const char * data, qint64 maxSize )
{
    return pTcpSocket->SendData( data, maxSize );
}

quint64 QMyNetwork::TcpSendData( QMyTcpSocket* pTcpSocket,  const QByteArray & byteArray )
{
    return pTcpSocket->SendData( byteArray );
}

quint64 QMyNetwork::TcpReceiveData( QMyTcpSocket* pTcpSocket,  char* data, qint64 maxSize )
{
    return pTcpSocket->ReceiveData( data, maxSize );
}

QByteArray QMyNetwork::QMyNetwork::TcpReceiveData( QMyTcpSocket* pTcpSocket,  qint64 maxSize )
{
    return pTcpSocket->ReceiveData( maxSize );
}

QByteArray QMyNetwork::TcpReceiveData( QMyTcpSocket* pTcpSocket )
{
    return pTcpSocket->ReceiveData( );
}

quint64 QMyNetwork::UdpBroadcastDatagram( QMyUdpSocket* pUdpSocket, const QByteArray& byteData, const quint16 targetPort )
{
    return pUdpSocket->BroadcastDatagram( byteData, targetPort );
}

bool QMyNetwork::StartupUdpListening( QMyUdpSocket* pUdpSocket, const quint16 nPort )
{
    return pUdpSocket->StartupUdpListening( nPort );
}

bool QMyNetwork::UdpOperateMulticast( QMyUdpSocket* pUdpSocket, const QHostAddress& groupAddress, const bool bJoined )
{
    return pUdpSocket->OperateMulticast( groupAddress, bJoined );
}

quint64 QMyNetwork::UdpSendDatagram( QMyUdpSocket* pUdpSocket, const QByteArray& byteData, const QHostAddress& targetAddress, const quint16 targetPort )
{
    return pUdpSocket->SendDatagram( byteData, targetAddress, targetPort );
}
