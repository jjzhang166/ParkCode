#include "udpclient.h"

CUdpClient::CUdpClient(QObject *parent) :
    QUdpSocket(parent)
{
    pTextCodec = NULL;
    connect( this, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( UdpError( QAbstractSocket::SocketError ) ) );
}

void CUdpClient::SetTextCodec( QTextCodec *pCodec )
{
    pTextCodec = pCodec;
}

bool CUdpClient::Connect2Server( const QHostAddress &hostAddr, quint16 nPort )
{
    svrAddr = hostAddr;
    nSvrPort = nPort;

    connectToHost( svrAddr, nSvrPort );
    return true;
}

quint64 CUdpClient::SendData( QByteArray &byData )
{
    return writeDatagram( byData, svrAddr, nSvrPort );
}

void CUdpClient::UdpError( QAbstractSocket::SocketError socketError )
{
    QString strMsg;
    CNetCommFunction::GetErrorMsg( strMsg, socketError, this );
    strMsg = "Udp socket :\r\n" + strMsg;
    emit NotifyMessage( strMsg );
}
