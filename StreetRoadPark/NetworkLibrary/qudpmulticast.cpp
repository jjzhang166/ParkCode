#include "qudpmulticast.h"
#include "../DatabaseLibrary/Constant.h"
//组播协议分为主机-路由器之间的组成员关系协议和
//路由器-路由器之间的组播路由协议。
//组成员关系协议包括IGMP（互连网组管理协议）。
//组播路由协议分为域内组播路由协议及域间组播路由协议。
//域内组播
//组播路由协议包括PIM-SM、PIM-DM、DVMRP等协议，
//域间组播路由协议包括MBGP、MSDP等协议。
//同时为了有效抑制组播数据在链路层的扩散，
//引入了IGMP Snooping、CGMP等二层组播协议
//224.0.0.0～224.0.0.255为预留的组播地址（永久组地址），地址224.0.0.0保留不做分配，其它地址供路由协议使用；
//224.0.1.0～224.0.1.255是公用组播地址，可以用于Internet；
//224.0.2.0～238.255.255.255为用户可用的组播地址（临时组地址），全网范围内有效；
//239.0.0.0～239.255.255.255为本地管理组播地址，仅在特定的本地范围内有效

QUdpMulticast::QUdpMulticast(QObject *parent) :
    QUdpSocket(parent)
{
    pConfig = CNetConfigurator::GetConfigurator( );
    byTokenData = DATA_TOKEN;
    strMultiIP = pConfig->GetMulticastIP( );
    //multiIP.setAddress( strMultiIP );
    multiIP = QHostAddress::Broadcast;
    nMulticastPort = pConfig->GetMulticastPort( );
    pCodec = pConfig->GetTextCodec( );
    //setSocketOption( );
}

void QUdpMulticast::MulticastData( QString &strJson, qint32 nMulticastType )
{
    QByteArray byData = pCodec->fromUnicode( strJson );
    MulticastData( byData, nMulticastType );
}

void QUdpMulticast::MulticastData( QByteArray &byJson, qint32 nMulticastType  )
{
    quint32 nBodyDataLen = byJson.length( );
    quint32 nDataSize = sizeof ( quint32 );

    qint32 nType = qToBigEndian< qint32 >( nMulticastType );
    byJson.insert( 0, ( const char* ) &nType, nDataSize );

    quint32 nReserved = qToBigEndian< quint32 >( 0 );
    byJson.insert( 0, ( const char* ) &nReserved, nDataSize );

    qint32 nDataLen = byTokenData.length( ) + nDataSize * 3 + nBodyDataLen;
    nDataLen = qToBigEndian< quint32 >( nDataLen );
    byJson.insert( 0, ( const char* ) &nDataLen, nDataSize );

    byJson.insert( 0, byTokenData );

    bool bTimeSync = ( Constant::TypeSystemInfo == nMulticastType );
    writeDatagram( byJson, multiIP, nMulticastPort + ( bTimeSync ? 1 : 0 ));
    flush( );
    waitForBytesWritten( );
    qDebug( ) << Q_FUNC_INFO << errorString( ) << endl;
}
