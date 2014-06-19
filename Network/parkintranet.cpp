#include "parkintranet.h"
#include <QDebug>
#include <windows.h>

#define BROADCAST_PORT          ( quint16 ) ( 45454 )
#define LOCALHOST_PORT          ( quint16 ) ( 45455 )
#define OUTPUT( strInfo )       qDebug( ) << strInfo << ( bRet ? " Success" : " Failed" ) << endl
#define DATAGRAM_TOKEN          "PMS"
#define SEPERATOR               char( 0 )

CNetwork* CNetwork::pNetwork = NULL;

CNetwork::CNetwork(QObject *parent) :
    QObject(parent)
{
    QSettings* pSystem = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    bMultiCast = !pSystem->value( "CommonCfg/BroadCastData", false ).toBool( );
    if ( bMultiCast ) {
        GetTargetHostIP( );
    }

    QString strFile = "sensapi.dll";
    WCHAR* pPath = ( WCHAR* ) strFile.utf16( );
    hDllMod = ::LoadLibrary( pPath );
    MyIsNetworkAlive = NULL;

    // IsDestinationReachable
    if ( NULL != hDllMod ) {
        MyIsNetworkAlive = ( IsNetworkAlive )::GetProcAddress( hDllMod, "IsNetworkAlive" );
    }

    pParent = qobject_cast< MainWindow* >( parent );
    pCodec = CCommonFunction::GetTextCodec( );
    connect( this, SIGNAL( OnReceiveDatagram( QStringList& ) ), pParent, SLOT( ProcessDatagram( QStringList& ) ) );
    InitBroadcastSocket( );
    Server( );
}

void CNetwork::GetTargetHostIP( )
{
    QString strSql = "select distinct video1ip from roadconerinfo";
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstTargetHostIP );
}

CNetwork& CNetwork::Singleton( QObject* parent )
{
    if ( NULL== pNetwork ) {
        pNetwork = new CNetwork( parent );
    }

    return *pNetwork;
}

void CNetwork::InitBroadcastSocket( )
{
    // Signal/Slot / Object tree
    udpClient = new QUdpSocket( this );
    udpBroadcastServer = new QUdpSocket( this );
    udpLoopbackServer = new QUdpSocket( this );
}

void CNetwork::Server( )
{
    if ( NULL == udpBroadcastServer || NULL == udpLoopbackServer ) {
        return;
    }

    bool bRet = udpBroadcastServer->bind( BROADCAST_PORT, QUdpSocket::ShareAddress );
    OUTPUT( "BroadcastServer->bind" );
    bRet = udpLoopbackServer->bind( QHostAddress::LocalHost, LOCALHOST_PORT, QUdpSocket::ShareAddress );
    OUTPUT( "LoopbackServer->bind" );

    bRet = connect( udpBroadcastServer, SIGNAL( readyRead( ) ), this, SLOT( DataMayRead( ) ) );
    bRet = connect( udpLoopbackServer, SIGNAL( readyRead( ) ), this, SLOT( DataMayRead( ) ) );
}

void CNetwork::DataMayRead( )
{
    QByteArray byData;
    QUdpSocket* udpServer = qobject_cast< QUdpSocket* > ( sender( ) );

    while ( udpServer->hasPendingDatagrams( ) ) {
        byData.resize( udpServer->pendingDatagramSize( ) );
        udpServer->readDatagram( byData.data( ), byData.size( ) );
        ProcessData( byData );
    }
}

void CNetwork::ProcessData( QByteArray &byData )
{
    if ( byData.isEmpty( ) ) {
        return;
    }

    QStringList lstData;

    int nCount = byData.count( SEPERATOR );
    int nIndex = byData.indexOf( SEPERATOR );

    if ( 2 > nCount || -1 == nIndex ) {
        return;
    }

    QString strType( byData.left( nIndex ) );
    if ( DATAGRAM_TOKEN != strType ) {
        return;
    }
    byData.remove( 0, nIndex + 1 );

    for ( int nItem = 0; nItem < nCount - 1; nItem++ ) {
        nIndex = byData.indexOf( SEPERATOR );
        lstData << byData.left( nIndex );
        byData.remove( 0, nIndex + 1 );
    }

    lstData << byData; // Last One

    emit OnReceiveDatagram( lstData );
}

void CNetwork::MultiCastData( const QByteArray& byData )
{
    QHostAddress hostAddr;

    foreach ( const QString& strIP, lstTargetHostIP ) {
        hostAddr.setAddress( strIP );
        //udpClient->connectToHost( hostAddr, BROADCAST_PORT ); // read write / QIODevice
        udpClient->writeDatagram( byData, hostAddr, BROADCAST_PORT ); // bind
        //udpClient->disconnectFromHost( );
    }
}

void CNetwork::BroadcastDatagram( CommonDataType::DatagramType dgType, QStringList &lstData, QString &strDestIP )
{
    QByteArray byType;
    OrgnizeData( dgType, lstData, byType );

    if ( 0 == byType.count( ) ) {
        return;
    }

    BOOL bRet = CheckNetwork( );

    if ( bRet ) {
        QHostAddress addr( strDestIP );
        udpClient->writeDatagram( byType, addr, BROADCAST_PORT );
    } else {
        udpClient->writeDatagram( byType, QHostAddress::LocalHost, LOCALHOST_PORT );
    }
}

void CNetwork::OrgnizeData( CommonDataType::DatagramType dgType, QStringList& lstData, QByteArray& byType )
{
    bool bType = ( -1 < dgType && dgType < CommonDataType::DGTypeCount );
    if ( NULL == udpClient || 0 == lstData.count( ) || !bType) {
        return;
    }

    // Format : Token Type Data
    byType = DATAGRAM_TOKEN;
    byType.append( SEPERATOR );

    QString strType = QString::number( dgType );
    byType.append( pCodec->fromUnicode( strType ) );

    foreach ( strType, lstData ) {
        byType.append( SEPERATOR ); // Seperator
        byType.append( pCodec->fromUnicode( strType ) );
    }
}

bool CNetwork::CheckNetwork( )
{
    BOOL bRet = false;

    if ( NULL != MyIsNetworkAlive ) {
        DWORD dwType;
        bRet = MyIsNetworkAlive( &dwType );
        DWORD dwError = GetLastError( );
        //bRet = ( ( 0 == dwError ) && bRet );

        if ( 0 == dwError && bRet ) {
            bRet = true;
        } else if ( 0 == dwError && !bRet ) {
            bRet = false;
        }
    }

    return bRet;
}

void CNetwork::BroadcastDatagram( CommonDataType::DatagramType dgType, QStringList &lstData )
{
    QByteArray byType;
    OrgnizeData( dgType, lstData, byType );

    if ( 0 == byType.count( ) ) {
        return;
    }

    BOOL bRet = CheckNetwork( );

    if ( bRet ) {
        if ( bMultiCast ) {
            MultiCastData( byType );
        } else {
            udpClient->writeDatagram( byType, QHostAddress::Broadcast, BROADCAST_PORT );
        }
    } else {
        udpClient->writeDatagram( byType, QHostAddress::LocalHost, LOCALHOST_PORT );
    }
}
