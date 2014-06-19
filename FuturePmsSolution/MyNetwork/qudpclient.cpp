#include "qudpclient.h"
#include "qnetcommfunction.h"

QUdpClient::QUdpClient( QTextCodec* pCodec, QObject *parent) :
    QMyUdpSocket(parent)
{
    pTextCodec = pCodec;
     setObjectName( "QUdpClient" );
     connect( this, SIGNAL( readyRead( ) ), this, SLOT( IncomingData( ) ) );
     connect( this, SIGNAL( error( QAbstractSocket::SocketError ) ), this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );
}

QUdpClient::~QUdpClient( )
{
    if ( NULL != pByteArray ) {
        delete pByteArray;
        pByteArray = NULL;
    }
}

void QUdpClient::HandleError( QAbstractSocket::SocketError socketError )
{
    QString* pstrMsg = new QString( );
    QNetCommFunction::GetErrorMsg( *pstrMsg, socketError, this );

    *pstrMsg = LogText( *pstrMsg  );
    OutputMsg( "Sender:" + sender( )->objectName( ) + QString( "emit NotifyMessage( %1, QManipulateIniFile::LogNetwork )" ).arg( *pstrMsg ) );

    emit NotifyMessage( pstrMsg, QManipulateIniFile::LogNetwork );
}

void QUdpClient::IncomingData( )
{
    //OutputMsg( "Receive data" );

    if ( NULL == pByteArray ) {
        pByteArray = new QByteArray( );
    }

    QHostAddress senderAddr;
    quint16 senderPort;
    GetUdpDatagram( senderAddr, senderPort );

    OutputMsg( senderAddr.toString( ) + ":" + QString::number( senderPort ) );

    emit GetWholeUdpDatagram( pByteArray, senderAddr.toString( ), senderPort );

    pByteArray = NULL;
}
