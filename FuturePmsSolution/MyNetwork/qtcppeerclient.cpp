#include "qtcppeerclient.h"
#include "qnetcommfunction.h"

QTcpPeerClient::QTcpPeerClient( QTextCodec* pCodec, QObject *parent ) :
    QMyTcpSocket(parent)
{
    pTextCodec = pCodec;
    setObjectName( "QTcpPeerClient" );
    connect( this, SIGNAL( disconnected( ) ), this, SLOT( HandleDisconnected( ) ) );
    connect( this, SIGNAL( readyRead( ) ), this, SLOT( IncomingData( ) ) );
    connect( this, SIGNAL( error( QAbstractSocket::SocketError ) ), this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );
}

QTcpPeerClient::~QTcpPeerClient( )
{
    if ( NULL != pByteArray ) {
        delete pByteArray;
        pByteArray = NULL;
    }
}

void QTcpPeerClient::HandleDisconnected( )
{
    GenerateLogText( false );
    close( );

    OutputMsg( "Sender:" + sender( )->objectName( ) + "emit EnqueueThread( ... )");
    // Peer thread to enqueue;
    emit EnqueueThread( this );
}

void QTcpPeerClient::HandleConnected( )
{
    GenerateLogText( true );
}

void QTcpPeerClient::HandleError( QAbstractSocket::SocketError socketError )
{
    QString* pstrMsg = new QString( );
    QNetCommFunction::GetErrorMsg( *pstrMsg, socketError, this );

    *pstrMsg = LogText( *pstrMsg );
    OutputMsg( "Sender:" + sender( )->objectName( ) + QString( ":emit NotifyMessage( %1, QManipulateIniFile::LogNetwork )" ).arg( *pstrMsg ) );

    emit NotifyMessage( pstrMsg, QManipulateIniFile::LogNetwork );
}

void QTcpPeerClient::IncomingData( )
{
    OutputMsg( "Receive data" );

    if ( NULL == pByteArray ) {
        pByteArray = new QByteArray( );
    }

    *pByteArray = readAll( );
    emit GetWholeTcpStreamData( this, pByteArray );
    pByteArray = NULL;
    return;
    bool bRet = GetTcpStreamData( );

    if ( bRet ) {
        emit GetWholeTcpStreamData( this, pByteArray );
        pByteArray = NULL;
    }
}
