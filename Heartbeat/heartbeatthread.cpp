#ifdef PARKDATARECEIVER_APP
#include "../Heartbeat/heartbeatthread.h"
#else
#include "Heartbeat/heartbeatthread.h"
#endif
#include <windows.h>
#include <iphlpapi.h>
#include <winsock2.h>

CHeartbeatThread::CHeartbeatThread(QObject *parent) :
    QThread(parent)
{
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    pTextCodec = CCommonFunction::GetTextCodec( );
    connect( this, SIGNAL( finished( ) ), this, SLOT( ExitThread( ) ) );

    udpClient = &CNetClient::GetInstance( false, true, pTextCodec, this ); // Communicate with center server
    tcpClient = &CNetClient::GetInstance( true, true, pTextCodec, this ); // Communicate with center server

    int nInterval = pSettings->value( "CenterServer/HeartbeatIPInterval", 300000 ).toInt( );
    //strClientServerPort = pSettings->value( "Database/UdpPort", CLIENT_SERVER_UDP_PORT ).toString( );
    strClientServerPort = pSettings->value( "CenterServer/UdpPort", CLIENT_SERVER_UDP_PORT ).toString( );

    nIPTimerID = startTimer( nInterval );

    nInterval = pSettings->value( "CenterServer/HeartbeatNetStateInterval", 600000 ).toInt( );
    nNetStateTimerID = startTimer( nInterval );

    nInterval = pSettings->value( "CenterServer/HeartbeatImgRequest", 300000 ).toInt( );
    nImgRequestTimerID = startTimer( nInterval );

    strCenterIP = pSettings->value( "CenterServer/CenterIP", "192.168.1.52" ).toString( );

    strHostIP = CCommonFunction::GetHostIP( );
    strParkID = CCommonFunction::GetParkID( );
}

CHeartbeatThread::~CHeartbeatThread( )
{
    killTimer( nIPTimerID );
    killTimer( nNetStateTimerID );
}

CHeartbeatThread& CHeartbeatThread::GetInstance( QObject *parent )
{
    CHeartbeatThread* pThread = new CHeartbeatThread( parent );

    return *pThread;
}

void CHeartbeatThread::timerEvent( QTimerEvent * e )
{
    int nTimerID = e->timerId( );

    if ( nTimerID   == nIPTimerID ) {
        GetLiveNetworkInterfaceIP( );
    } else if ( nTimerID == nNetStateTimerID ){
        SyncNetState( );
    } else if ( nTimerID == nImgRequestTimerID ) {
        GetImgRequest( );
    }
}

void CHeartbeatThread::GetImgRequest( )
{
    udpClient->SendHeartbeatData( strParkID, NetTransport::HbImgRequest );
}

void CHeartbeatThread::SyncNetState( )
{
    static QString strFormat = "%1,%2,%3";
    QString strBody = strFormat.arg( strParkID, strHostIP /*MachineIP*/,
                                                 QString::number( QDateTime::currentMSecsSinceEpoch( ) ) );
    udpClient->SendHeartbeatData( strBody, NetTransport::HbNetState );
}

void CHeartbeatThread::GetLiveNetworkInterfaceIP( )
{
    //SyncIP( strHostIP );
    SyncIP( strCenterIP );
    return;
    DWORD dwSize = 0;
    PMIB_IFROW pIfRow = NULL;
    PIP_ADAPTER_ADDRESSES pAddress = NULL;
    PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
    struct sockaddr_in* inAddr = NULL;
    char cPhyAddr[ MAXLEN_PHYSADDR ] = { 0 };
    QByteArray byPhyAddr1;//
    QByteArray byPhyAddr2;
    DWORD dwRet = GetIfTable ( NULL, &dwSize, FALSE );
    if ( ERROR_INSUFFICIENT_BUFFER != dwRet ) {
        return;
    }

    HANDLE hHeap = ::GetProcessHeap( );
    PMIB_IFTABLE pIfTable = ( PMIB_IFTABLE ) ::HeapAlloc( hHeap, HEAP_ZERO_MEMORY, dwSize );
    if ( NULL == pIfTable ) {
        return;
    }

    dwRet = GetIfTable ( pIfTable, &dwSize, FALSE );
    if ( NO_ERROR != dwRet ) {
        goto FREEMEMORY;
    }

    for ( DWORD nIndex = 0; nIndex < pIfTable->dwNumEntries; nIndex++ ) {
        pIfRow = &pIfTable->table[ nIndex ];
        if ( IF_TYPE_SOFTWARE_LOOPBACK == pIfRow->dwType ) {
            pIfRow = NULL;
            continue;
        }

        if ( IF_OPER_STATUS_CONNECTED == pIfRow->dwOperStatus ||
             IF_OPER_STATUS_OPERATIONAL == pIfRow->dwOperStatus ) {
            strncpy( cPhyAddr, ( LPCSTR ) pIfRow->bPhysAddr, pIfRow->dwPhysAddrLen );
            byPhyAddr1 = QByteArray::fromRawData( cPhyAddr, pIfRow->dwPhysAddrLen );
            break;
        }

        pIfRow = NULL;
    }

    FREEMEMORY:
    BOOL bRet = HeapFree( hHeap, 0, pIfTable );

    if ( NULL == pIfRow ) {
        return;
    }

    dwRet = GetAdaptersAddresses( AF_UNSPEC, GAA_FLAG_SKIP_ANYCAST |
                                                                          GAA_FLAG_SKIP_MULTICAST |
                                                                          GAA_FLAG_SKIP_DNS_SERVER |
                                                                          GAA_FLAG_SKIP_FRIENDLY_NAME,
                                                                          NULL, NULL, &dwSize );

    if ( ERROR_BUFFER_OVERFLOW != dwRet ) {
        return;
    }

    pAddress = ( PIP_ADAPTER_ADDRESSES ) ::HeapAlloc( hHeap, HEAP_ZERO_MEMORY, dwSize );
    dwRet = GetAdaptersAddresses( AF_UNSPEC, GAA_FLAG_SKIP_ANYCAST |
                                                                          GAA_FLAG_SKIP_MULTICAST |
                                                                          GAA_FLAG_SKIP_DNS_SERVER |
                                                                          GAA_FLAG_SKIP_FRIENDLY_NAME,
                                                                          NULL, pAddress, &dwSize );

    if ( NO_ERROR != dwRet ) {
        goto FREEMEMORY2;
    }

    do {
        byPhyAddr2 = QByteArray::fromRawData( ( LPCSTR ) pAddress->PhysicalAddress, pAddress->PhysicalAddressLength );
        if ( byPhyAddr1 == byPhyAddr2 ) {
            pUnicast = pAddress->FirstUnicastAddress;
            break;
        }
        pAddress = pAddress->Next;
    } while ( NULL != pAddress );

    if ( NULL == pUnicast ) {
        goto FREEMEMORY2;
    }

    inAddr = ( struct sockaddr_in* ) pUnicast->Address.lpSockaddr;
    //SyncIP( inet_ntoa( inAddr->sin_addr ) );

    FREEMEMORY2:
    bRet = HeapFree( hHeap, 0, pAddress );
}

void CHeartbeatThread::SyncIP( QString& strIP )
{

    static QString strFormat = "%1,%2,%3" ;

    QString strBody = strFormat.arg( strParkID, strIP, strClientServerPort );
    udpClient->SendHeartbeatData( strBody, NetTransport::HbClientIP );
}

void CHeartbeatThread::run( )
{
    exec( );
}

void CHeartbeatThread::customEvent( QEvent *e )
{
    CHbEvent::UserEvent evtType = ( CHbEvent::UserEvent ) e->type( );
    CHbEvent* pEvent = ( CHbEvent* ) e;

    CHbEvent::TableData& table = pEvent->GetPassRecord( );

    switch ( evtType ) {
    case CHbEvent::HbInOutImg :
        break;

    case CHbEvent::HbPassRecord :
        tcpClient->SendTableData( table.strPass, table.nRows, table.nCols, ( NetTransport::eTableType ) table.tabType );
        break;

    case CHbEvent::HbForward :
        {
            bool bTcp = pEvent->GetProtocolType( );
            CNetClient* pClient =  bTcp ? tcpClient : udpClient;
            pClient->SocketSendData( bTcp ? CNetClient::ClientTCPClient : CNetClient::ClientUDPClient, pEvent->GetByteArrayData( ) );
        }
        break;

    case CHbEvent::HbImgLog :
        udpClient->SendTableData( pEvent->GetImgLog( ), 1, 1, NetTransport::TabImgLog );
        break;
    }
}

void CHeartbeatThread::ExitThread( )
{
    delete this;
}
