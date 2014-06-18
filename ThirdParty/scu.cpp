#include "ThirdParty\scu.h"
#include <windows.h>

CScu::CScu(QObject *parent) :
    QObject(parent)
{
    pTxtCodec = CCommonFunction::GetTextCodec( );
    pSystemSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    byBuffer.setBuffer( &bySendData );
}

void CScu::InteractWithScu( QStringList &lstData )
{
    pSystemSet->sync( );

    HttpSendData( lstData );

    bool bScuMsgCenter = pSystemSet->value( "ThirdParty/ScuMsgCenter", false ).toBool( );
    if ( !bScuMsgCenter ) {
        return;
    }

    ContructDatagram( lstData );
    SendDatagram( );
}

void CScu::ContructDatagram( QStringList &lstData )
{
    bySendData.clear( );

    if ( 0 == lstData.count( ) || !byBuffer.open( QIODevice::WriteOnly ) ) {
        return;
    }

    int nItems = lstData.count( );
    QByteArray byContent = pTxtCodec->fromUnicode( lstData.join( "##" ) );

    QDataStream stream( &byBuffer );
    //数据	长度(字节)	数据类型	偏移量
    //校验起始符	1	char	0
    //保留字段	1	byte	1
    //所属系统	1	byte	2
    //设备类型	1	byte	3
    //设备编号	10	string	4
    //数据类型(来源)	1	byte	14
    //级别	1	byte	15
    //内容长度	2	short	16
    //内容数目	1	byte	18
    //内容	N	string	19
    //校验结束符	2	string	19+N
    //校验和	2	string	21+N
    quint8 nDeviceType = ( quint8 ) pSystemSet->value( "ThirdParty/DeviceType", 100 ).toUInt( );
    QString strDeviceID = pSystemSet->value( "ThirdParty/DeviceID", "0000000001" ).toString( );
    quint32 nSystemType = pSystemSet->value( "ThirdParty/SystemType", 12 ).toUInt( );
    QByteArray byDeviceID = pTxtCodec->fromUnicode( strDeviceID );

    stream << ( quint8 ) '$' << ( quint8 ) 1 << ( quint8 ) nSystemType << nDeviceType;
    byBuffer.write( byDeviceID );
    stream << ( quint8 ) 2 << ( quint8 ) 1 << ( qint16 ) byContent.count( ) <<( quint8 ) nItems;
    byBuffer.write( byContent );
    stream << ( quint8 ) '*' << ( quint8 ) '*';

    qint16 nCheckSum = bySendData.at( 1 );
    for ( int nIndex = 2; nIndex < bySendData.count( ) - 2; nIndex++ ) {
        nCheckSum ^= bySendData.at( nIndex );
    }

    QChar fillChar( '0' );
    QString strCheckSum = QString( "%1" ).arg( nCheckSum, 2, 16, fillChar );
    byBuffer.write( pTxtCodec->fromUnicode( strCheckSum ) );

    byBuffer.close( );
}

void CScu::HttpSendData( QStringList &lstData )
{
    bool bServer = pSystemSet->value( "Database/Server", false ).toBool( );
    if ( !bServer ) {
        return;
    }
    //Http=http://192.168.1.49:8080/Packing/action
    QString strUrl = pSystemSet->value( "ThirdParty/Http", "" ).toString( );

    if ( strUrl.isEmpty( ) ) {
        return;
    }

    QString strDeviceID = pSystemSet->value( "ThirdParty/DeviceID", "0000000001" ).toString( );
    QString strData = strDeviceID + "," + lstData.join( "," );
    QByteArray byData = pTxtCodec->fromUnicode( strData );
    http.HttpPost( strUrl, byData );
}

void CScu::SendDatagram( )
{
    //::gethostbyaddr( ) 据IP获取对应主机信息
    // getnameinfo

    //::getaddrinfo 据域名获取对应主机信息
    hostent* pHost = ::gethostbyname( "www.google.com.hk" );
    int i = 0;
    struct in_addr addr;
    while ( NULL != pHost && pHost->h_addr_list[ i ] != 0
            && AF_INET == pHost->h_addrtype ) {
        addr.s_addr = *( u_long* ) pHost->h_addr_list[ i++ ];
        qDebug( ) << inet_ntoa( addr ) << endl;
    }

    if ( QAbstractSocket::ConnectedState != udpClient.state( ) ) {
        QString strIP = pSystemSet->value( "ThirdParty/ScuMsgCenterIP", "127.0.0.1" ).toString( );
        QString strPort = pSystemSet->value( "ThirdParty/ScuMsgCenterPort", "32009" ).toString( );
        QHostAddress address( strIP );
        quint16 nPort = strPort.toUShort( );

        udpClient.Connect2Server( address, nPort );
    }

    quint64 nRet = udpClient.SendData( bySendData );
    qDebug( ) << "Scu:" << nRet << endl;
}
