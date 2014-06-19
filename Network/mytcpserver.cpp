
#include <QObject>
#include "mytcpserver.h"

CMyTcpServer::CMyTcpServer( quint16 nThreadPool, QObject *parent) :
    QTcpServer(parent)
{
    svrThreadPool = NULL;//new QThreadPool( this );
    //svrThreadPool->setMaxThreadCount( nThreadPool );
    //svrThreadPool->setExpiryTimeout( -1 );

    pParserThread = CDataParserThread::GetInstance( nThreadPool, true );
}

CMyTcpServer::~CMyTcpServer( )
{
    if ( NULL != svrThreadPool ) {
        delete svrThreadPool;
    }
}

void CMyTcpServer::TcpError( QAbstractSocket::SocketError socketError )
{
    QString strMsg;
    QTcpSocket* pTcpServer = qobject_cast< QTcpSocket* > ( sender( ) );
    CNetCommFunction::GetErrorMsg( strMsg, socketError, pTcpServer );
    strMsg = "Tcp client peer socket :\r\n" + strMsg;
    emit NotifyMessage( strMsg );
}

bool CMyTcpServer::GetMgmtTCPFlag( )
{
    bool bRet = CCommonFunction::GetSettings( CommonDataType::CfgSystem )->value( "Mgmt/MgmtTCP", false ).toBool( );

    return bRet;
}

QHash< QString, CPeerSocket* >& CMyTcpServer::GetPeerSocketHash( )
{
    return clientHash;
}

void CMyTcpServer::incomingConnection( int socketDescriptor )
{
    // client endpoint / connectToHost
    CPeerSocket* pSocket = new CPeerSocket( this );
    pSocket->setSocketDescriptor( socketDescriptor );
    //addPendingConnection( pSocket );
    connect( pSocket, SIGNAL( disconnected( ) ), this, SLOT( HandleDisconnect( ) ) );

    if ( GetMgmtTCPFlag( ) ) {
        connect( pSocket, SIGNAL( readyRead( ) ), this, SLOT( GetMgmtStream( ) ) );
    } else {
        connect( pSocket, SIGNAL( readyRead( ) ), this, SLOT( GetStream( ) ) );
    }

    connect( pSocket, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( TcpError( QAbstractSocket::SocketError ) ) );

    QString strKey;
    QString strMsg;
    GetKeyMsg( pSocket, strKey, strMsg, true );

    clientHash.insert( strKey, pSocket );

    emit NotifyMessage( strMsg );
}

void CMyTcpServer::GetKeyMsg( QTcpSocket *pSocket, QString &strKey, QString &strMsg, bool bConnected )
{
    strKey = QString( "%1:%2" ).arg( pSocket->peerAddress( ).toString( ),
                                     QString::number( pSocket->peerPort( ) ) );

    QDateTime dt = QDateTime::currentDateTime( );
    strMsg = QString ( "%1%2%3%4" ).arg(
            dt.toString( "yyyy-MM-dd hh:mm:ss " ),
            strKey,
            bConnected ? " Connected" : " Disconnected" , " to Server.\r\n" );
}

void CMyTcpServer::HandleDisconnect( ) // Client / reconnect
{
    CPeerSocket* pSocket = qobject_cast< CPeerSocket* >( sender( ) );

    QString strKey;
    QString strMsg;
    GetKeyMsg( pSocket, strKey, strMsg, false );

#ifndef QT_NO_DEBUG
    qDebug( ) << "HandleDisconnect( ) ,Peer host "
            << pSocket->peerAddress( ).toString( )
            << ":"
            << QString::number( pSocket->peerPort( ) )
            << endl;
#endif

    clientHash.remove( strKey );
    pSocket->close( );
    pSocket->deleteLater( ); // Leave event loop to delete
    pParserThread->PostReleaseMessage( ( quint32 ) pSocket );

    emit NotifyMessage( strMsg );
}

void CMyTcpServer::GetStream( )
{
    CPeerSocket* pSocket = qobject_cast< CPeerSocket* >( sender( ) );
    QByteArray byData = pSocket->readAll( );

    pParserThread->PostDataMessage( byData, ( quint32 ) pSocket );
    return;

    quint64 nDataLen = pSocket->bytesAvailable( );

    QByteArray* pByteArray = pSocket->GetData( );
    quint64 nPreSize = pSocket->GetCurrentDataSize( );
    quint64 nCurDataSize = nPreSize + nDataLen;
    if ( 0 == pSocket->GetMaxDataSize( ) || processMsg.GetCommonHeaderSize( ) > nCurDataSize ) {
        pByteArray->resize( nCurDataSize );
    }

    char* pSegData = ( char* ) ( ( quint64 ) pByteArray->data( ) + nPreSize );
    quint64 nDataRetLen = pSocket->read( pSegData, nDataLen );
    pSocket->SetCurrentDataSize( nDataRetLen );

    if ( 0 == pSocket->GetMaxDataSize( ) && processMsg.GetCommonHeaderSize( ) <= nCurDataSize ) {
        NetTransport::CommonHeader& commHeader = processMsg.GetCommonHeader( pSegData );
        pSocket->SetMaxDataSize( commHeader.nDataLen );
        pByteArray->resize( commHeader.nDataLen );
    }

#ifndef QT_NO_DEBUG
    if ( nDataRetLen != nDataLen ) {
        qDebug( ) << "Read Client : " << pSocket->peerAddress( ).toString( ) << " error" << endl;
    }
#endif

    if ( pSocket->GetCurrentDataSize( ) == pSocket->GetMaxDataSize( ) ) {
        nDataLen = pSocket->GetCurrentDataSize( );
        char* pData = new char[ nDataLen + 1 ];
        memcpy( pData, pByteArray->data( ), nDataLen );
        pData[ nDataLen ] = '\0';
        pSocket->Clear( );

        pSocket->write( HANDSHAKE );
        CNetProcessData* processor  = CNetProcessData::GetInstance( pData, nDataLen );
        svrThreadPool->start( processor );
    }
}

void CMyTcpServer::GetMgmtStream( )
{
    return;
    CPeerSocket* pSocket = qobject_cast< CPeerSocket* >( sender( ) );
    quint64 nDataLen = pSocket->bytesAvailable( );

    QByteArray* pByteArray = pSocket->GetData( );
    quint64 nPreSize = pSocket->GetCurrentDataSize( );
    quint64 nCurDataSize = nPreSize + nDataLen;
    if ( 0 == pSocket->GetMaxDataSize( ) || processMsg.GetCommonHeaderSize( ) > nCurDataSize ) {
        pByteArray->resize( nCurDataSize );
    }

    char* pSegData = ( char* ) ( ( quint64 ) pByteArray->data( ) + nPreSize );
    quint64 nDataRetLen = pSocket->read( pSegData, nDataLen );
    pSocket->SetCurrentDataSize( nDataRetLen );

    if ( 0 == pSocket->GetMaxDataSize( ) && processMsg.GetCommonHeaderSize( ) <= nCurDataSize ) {
        NetTransport::CommonHeader& commHeader = processMsg.GetCommonHeader( pSegData );
        pSocket->SetMaxDataSize( commHeader.nDataLen );
        pByteArray->resize( commHeader.nDataLen );
    }

#ifndef QT_NO_DEBUG
    if ( nDataRetLen != nDataLen ) {
        qDebug( ) << "Read Client : " << pSocket->peerAddress( ).toString( ) << " error" << endl;
    }
#endif

    if ( pSocket->GetCurrentDataSize( ) == pSocket->GetMaxDataSize( ) ) {
        nDataLen = pSocket->GetCurrentDataSize( );
        char* pData = new char[ nDataLen + 1 ];
        memcpy( pData, pByteArray->data( ), nDataLen );
        pData[ nDataLen ] = '\0';
        pSocket->Clear( );

        pSocket->write( HANDSHAKE );
        CNetProcessData* processor  = CNetProcessData::GetInstance( pData, nDataLen );
        svrThreadPool->start( processor );
    }
}
