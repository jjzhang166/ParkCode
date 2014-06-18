#include "qthreadevent.h"

QThreadEvent::QThreadEvent( ThreadType thrType, Type evtType ) : QEvent( evtType ),
    typeThread( thrType ), typeEvent( ( EventType ) evtType )
{
}

QThreadEvent::~QThreadEvent( )
{
}

QThreadEvent* QThreadEvent::CreateThreadEvent(ThreadType thrType, EventType evtType)
{
    return new QThreadEvent( thrType, ( Type ) evtType );
}

void QThreadEvent::SetListenPort( const quint16 nPort )
{
    tcpServerPort = nPort;
}

quint16 QThreadEvent::GetListenPort( ) const
{
    return tcpServerPort;
}

void QThreadEvent::SetMaxPendingConnection( const qint32 nMaxConn )
{
    nMaxPendingConnection = nMaxConn;
}

qint32 QThreadEvent::GetMaxPendingConnection( ) const
{
    return nMaxPendingConnection;
}

void QThreadEvent::SetSocketDescriptor( const qintptr nSocket )
{
    nSocketDescriptor = nSocket;
}

qintptr QThreadEvent::GetSocketDescriptor( ) const
{
    return nSocketDescriptor;
}

void QThreadEvent::SetPeerSocket( QTcpSocket* pSocket )
{
    pPeerSocket = pSocket;
}

QTcpSocket* QThreadEvent::GetPeerSocket( ) const
{
    return pPeerSocket;
}

void QThreadEvent::SetByteArray( const QByteArray& byByteArray )
{
    byEventByteArray.append( byByteArray );
}

QByteArray& QThreadEvent::GetByteArray( )
{
    return byEventByteArray;
}

void QThreadEvent::SetPackageType( qint32 nType )
{
    nPackageType = nType;
}

qint32 QThreadEvent::GetPackageType( )
{
    return nPackageType;
}
