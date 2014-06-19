#include "qmyudpsocket.h"
//
// If you want to use the standard QIODevice functions read(), readLine(), write(), etc.,
// you must first connect the socket directly to a peer by calling connectToHost().
// If you just want to send datagrams, you don't need to call bind().
//

QMyUdpSocket::QMyUdpSocket(QObject *parent) :
    QUdpSocket(parent)
{
    pByteArray = NULL;
    setObjectName( "QMyTcpSocket" );
}

void QMyUdpSocket::GetUdpDatagram( QHostAddress& senderAddr, quint16& senderPort )
{
    if ( NULL == pByteArray ) {
        return;
    }

    QByteArray* pByteDatagram = new QByteArray( );

    while ( hasPendingDatagrams( ) ) {
        pByteDatagram->clear( );
        pByteDatagram->resize( pendingDatagramSize( ) );

        readDatagram( pByteDatagram->data( ), pByteDatagram->size( ), &senderAddr, &senderPort );
        pByteArray->append( *pByteDatagram );
    }

    delete pByteDatagram;
}

quint64 QMyUdpSocket::BroadcastDatagram( const QByteArray &byteData, const quint16 targetPort )
{
    return writeDatagram( byteData, QHostAddress::Broadcast, targetPort );
}

quint64 QMyUdpSocket::SendDatagram( const QByteArray &byteData, const QHostAddress &targetAddress, const quint16 targetPort )
{
    return writeDatagram( byteData, targetAddress, targetPort );
}

bool QMyUdpSocket::StartupUdpListening( const quint16 nPort )
{
    bool bRet = ( state( ) != BoundState );

    if ( bRet ) {
        bRet = bind( QHostAddress::Any, nPort, ShareAddress );
    }

    return bRet;
}

bool QMyUdpSocket::OperateMulticast( const QHostAddress &groupAddress, const bool bJoined )
{
    return bJoined ? joinMulticastGroup( groupAddress ) : leaveMulticastGroup( groupAddress );
}
