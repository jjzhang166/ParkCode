#include "qmytcpsocket.h"

QMyTcpSocket::QMyTcpSocket(QObject *parent) :
    QTcpSocket(parent)
{
    bPeerSocket = false;
    connect( this, SIGNAL( readyRead( ) ), this, SLOT( ReceiveData( ) ) );
    connect( this, SIGNAL( error( QAbstractSocket::SocketError ) ), this, SLOT( TcpError( QAbstractSocket::SocketError ) ) );
}

QMyTcpSocket::~QMyTcpSocket( )
{

}

void QMyTcpSocket::ReceiveData( )
{
    QByteArray* pByteArray = new QByteArray( readAll( ) );
    emit DataIncoming( this, pByteArray );
}

quint64 QMyTcpSocket::SendData(const QByteArray &byteArray)
{
    //HandleDisconnect( );
    quint64 nRet = 0;

    int nPackageSize = 10 * 1024 * 1024;
    int nTotalSize = byteArray.count( );
    int nMode = nTotalSize / nPackageSize;
    int nSurplus = nTotalSize % nPackageSize;
    const char* pData = byteArray.data( );
    const char* pPkgData = NULL;

    if ( 0 == nMode ) { // < 10M
        nRet += write( byteArray );
    } else { // >= 10M
        int nIndex = 0;
        for ( nIndex = 0; nIndex < nMode; nIndex++ ) {
            pPkgData = ( pData + nIndex * nPackageSize );
            nRet += write( pPkgData, nPackageSize );
        }

        if ( 0 != nSurplus ) {
            pPkgData = ( pData + nIndex * nPackageSize );
            nRet += write( pPkgData, nSurplus );
        }
    }

    flush( );
    waitForBytesWritten( );

    return nRet;
}

void QMyTcpSocket::TcpError( QAbstractSocket::SocketError socketError )
{
    QString strHostInfo = QString( "localIP:%1 loclaPort:%2 remoteIP:%3 romtePort:%4 " ).arg(
                localAddress( ).toString( ),
                QString::number( localPort( ) ),
                peerAddress( ).toString( ),
                QString::number( peerPort( ) ) );

    QString strMsg = "";
    GetErrorMsg( strMsg, socketError, this );
    strMsg = strHostInfo + strMsg;

    if ( !bPeerSocket ) {
        emit ErrorCode( this );
    }
    emit ErrorInfo( QCommonLibrary::LogError, strMsg );
}

void QMyTcpSocket::GetErrorMsg( QString& strMsg, QAbstractSocket::SocketError code, QIODevice* pDevice )
{
    switch ( code ) {
    case QAbstractSocket::ConnectionRefusedError :
        strMsg = "QAbstractSocket::ConnectionRefusedError";
        break;
    case QAbstractSocket::RemoteHostClosedError :
        strMsg = "QAbstractSocket::RemoteHostClosedError";
        break;
    case QAbstractSocket::HostNotFoundError :
        strMsg = "QAbstractSocket::HostNotFoundError";
        break;
    case QAbstractSocket::SocketAccessError :
        strMsg = "QAbstractSocket::SocketAccessError";
        break;
    case QAbstractSocket::SocketResourceError :
        strMsg = "QAbstractSocket::SocketResourceError";
        break;
    case QAbstractSocket::SocketTimeoutError :
        strMsg = "QAbstractSocket::SocketTimeoutError";
        break;
    case QAbstractSocket::DatagramTooLargeError :
        strMsg = "QAbstractSocket::DatagramTooLargeError";
        break;
    case QAbstractSocket::NetworkError :
        strMsg = "QAbstractSocket::NetworkError";
        break;
    case QAbstractSocket::AddressInUseError :
        strMsg = "QAbstractSocket::AddressInUseError";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError :
        strMsg = "QAbstractSocket::SocketAddressNotAvailableError";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError :
        strMsg = "QAbstractSocket::UnsupportedSocketOperationError";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError :
        strMsg = "QAbstractSocket::UnfinishedSocketOperationError";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError :
        strMsg = "QAbstractSocket::ProxyAuthenticationRequiredError";
        break;
    case QAbstractSocket::SslHandshakeFailedError :
        strMsg = "QAbstractSocket::SslHandshakeFailedError";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError :
        strMsg = "QAbstractSocket::ProxyConnectionRefusedError";
        break;
    case QAbstractSocket::ProxyConnectionClosedError :
        strMsg = "QAbstractSocket::ProxyConnectionClosedError";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError :
        strMsg = "QAbstractSocket::ProxyConnectionTimeoutError";
        break;
    case QAbstractSocket::ProxyNotFoundError :
        strMsg = "QAbstractSocket::ProxyNotFoundError";
        break;
    case QAbstractSocket::ProxyProtocolError :
        strMsg = "QAbstractSocket::ProxyProtocolError";
        break;
    case QAbstractSocket::UnknownSocketError :
        strMsg = "QAbstractSocket::UnknownSocketError";
        break;
    }

    strMsg += "\r\n";

    if ( NULL != pDevice) {
        strMsg += pDevice->errorString( );
        strMsg += "\r\n";
    }
}
