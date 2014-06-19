#include "tcpclient.h"

CTcpClient::CTcpClient(QObject *parent) :
    QTcpSocket(parent)
{
    pData = NULL;
    Clear( );
    pData = new QByteArray( );

    pTextCodec = NULL;
    connect( this, SIGNAL( disconnected( ) ), this, SLOT( HandleDisconnect( ) ) );
    connect( this, SIGNAL( error( QAbstractSocket::SocketError ) ),
                  this, SLOT( TcpError( QAbstractSocket::SocketError ) ) );
}

CTcpClient::~CTcpClient( )
{
    if ( NULL != pData ) {
        delete pData;
        pData = NULL;
    }
}

void CTcpClient::SetMaxDataSize( quint64 nSize )
{
    nDataLen = nSize;
}

quint64 CTcpClient::GetMaxDataSize( )
{
    return nDataLen;
}

void CTcpClient::Clear( )
{
    if ( NULL != pData ) {
        pData->resize( 0 );
    }

    nDataLen = 0;
    nCurrentLen = 0;
}

void CTcpClient::SetCurrentDataSize( quint64 nSize )
{
    nCurrentLen += nSize;
}

quint64 CTcpClient::GetCurrentDataSize( )
{
    return nCurrentLen;
}

QByteArray* CTcpClient::GetData( )
{
    return pData;
}

void CTcpClient::SetTextCodec( QTextCodec *pCodec )
{
    pTextCodec = pCodec;
}

bool CTcpClient::Connect2Server( const QHostAddress &hostAddr, quint16 nPort )
{
    svrAddr = hostAddr;
    nSvrPort = nPort;

    try {
        connectToHost( svrAddr, nSvrPort );
    } catch ( ... ) {
        int n = 0;
        n++;
        return false;
    }

    return true;
}

void CTcpClient::TcpError( QAbstractSocket::SocketError socketError )
{
    QString strMsg;
    CNetCommFunction::GetErrorMsg( strMsg, socketError, this );
    strMsg = "Tcp socket :\r\n" + strMsg;
    emit NotifyMessage( strMsg );

    HandleDisconnect( );
}

void CTcpClient::HandleDisconnect( )
{
    //QString strIP = svrAddr.toString( );
    //if ( ping.IcmpPing( strIP ) ) {
    if ( QAbstractSocket::ConnectedState != state( ) ) {
        connectToHost( svrAddr, nSvrPort );
        qDebug( ) << "CTcpClient::HandleDisconnect( )" << endl;
    }
}

quint64 CTcpClient::SendData( const char * data, qint64 maxSize )
{
    HandleDisconnect( );
    return write( data, maxSize );
}

quint64 CTcpClient::SendData( const QByteArray & byteArray )
{
    HandleDisconnect( );
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

    if ( !flush( ) ) {
        waitForBytesWritten( );
    }

    return nRet;
}

quint64 CTcpClient::ReceiveData( char* data, qint64 maxSize )
{
    return read( data, maxSize );
}

QByteArray CTcpClient::ReceiveData( qint64 maxSize )
{
    return read( maxSize );
}

QByteArray CTcpClient::ReceiveData(  )
{
    return readAll( );
}
