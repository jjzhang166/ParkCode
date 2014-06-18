#include "qdbthreadevent.h"

QDbThreadEvent::QDbThreadEvent( ThreadType thrType, Type evtType ) : QEvent( evtType ),
    typeThread( thrType ), typeEvent( ( EventType ) evtType )
{
    bReconnect = false;
}

QDbThreadEvent::~QDbThreadEvent( )
{

}

void QDbThreadEvent::SetByteArray( QByteArray& byData )
{
    byByteArray.append( byData );
}

QByteArray& QDbThreadEvent::GetByteArray( )
{
    return byByteArray;
}

void QDbThreadEvent::SetDataPackageType( qint32 nType )
{
    nDataPackageType = nType;
}

qint32 QDbThreadEvent::GetDataPackageType( )
{
    return nDataPackageType;
}

void QDbThreadEvent::SetPeerSocket( QTcpSocket* pSocket )
{
    pPeerSocket = pSocket;
}

QTcpSocket* QDbThreadEvent::GetPeerSocket( )
{
    return pPeerSocket;
}

QDbThreadEvent* QDbThreadEvent::CreateThreadEvent( ThreadType thrType, EventType evtType )
{
    return new QDbThreadEvent( thrType, ( Type ) evtType );
}

void QDbThreadEvent::SetComParkID( QString& strParkID )
{
    strComParkID = strParkID;
}

QString& QDbThreadEvent::GetComParkID( )
{
    return strComParkID;
}

void QDbThreadEvent::SetReconnect( bool bReconn )
{
    bReconnect = bReconn;
}

bool QDbThreadEvent::GetReconnect( )
{
    return bReconnect;
}
