#include "svrthread.h"

CSvrThread::CSvrThread(QObject *parent) :
    QThread(parent)
{
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );

    for ( int nIndex = 0; nIndex < SERVER_INSTANCE; nIndex++ ) {
        tcpServer[ nIndex ] = NULL;
        udpServer[ nIndex ] = NULL;
    }
}

CSvrThread* CSvrThread::GetInstance( QObject *parent )
{
    CSvrThread* pThread = new CSvrThread( parent );

    return pThread;
}

void CSvrThread::NotifyMessage( QString strMsg )
{
    emit Notify( strMsg );
}

bool CSvrThread::StartupUdpServer( bool bServerEnd )
{
    bool bRet = false;
    try {
    CUdpDispatcher** pServer = &udpServer[ bServerEnd ];
    if ( NULL == *pServer ) {
        *pServer = new CUdpDispatcher( this );
         connect( *pServer , SIGNAL( NotifyMessage( QString ) ), this, SLOT( NotifyMessage( QString ) ) );
    }

    quint16 nPort = GetPort( bServerEnd, false );
    quint16 nThreadPool = GetThreadPoolCount( bServerEnd, false );
    bRet = ( *pServer )->InitServer( nPort, nThreadPool );
    } catch ( ... ) {
        int n = 0;
        n++;
    }

    return bRet;
}

bool CSvrThread::StartupTcpServer( bool bServerEnd )
{
    bool bRet = false;
    try {
    CTcpDispatcher** pServer = &tcpServer[ bServerEnd ];
    if ( NULL == *pServer ) {
        *pServer = new CTcpDispatcher( this );
        connect( *pServer , SIGNAL( NotifyMessage( QString ) ), this, SLOT( NotifyMessage( QString ) ) );
    }

    quint16 nPort = GetPort( bServerEnd, true );
    int nMaxPendingConn = GetMaxPendingCount( bServerEnd );
    quint16 nThreadPool = GetThreadPoolCount( bServerEnd, true );
    bRet = ( *pServer )->InitServer( nPort, nMaxPendingConn, nThreadPool );
    } catch ( ... ) {
        int n = 0;
        n++;
    }

    return bRet;
}

quint16 CSvrThread::GetPort( bool bServerEnd, bool bTcp )
{
    QString strKey = QString( "%1" ).arg( bServerEnd ? "ServerInfo" : "Database" ) + "/%1";
    QString strPort = bTcp ? "TcpPort" : "UdpPort";
    quint16 nDefaultPort = bServerEnd ? ( bTcp ? TCP_DISPATCHER_PORT : UDP_DISPATCHER_PORT ) :
                                                            ( bTcp ? CLIENT_SERVER_TCP_PORT : CLIENT_SERVER_UDP_PORT );
    quint16 nPort = pSettings->value( strKey.arg( strPort ), nDefaultPort ).toUInt( );

    return nPort;
}

quint16 CSvrThread::GetMaxPendingCount( bool bServerEnd )
{
    QString strKey = QString( "%1" ).arg( bServerEnd ? "ServerInfo" : "Database" ) + "/%1";
    quint16 nMaxPendingCount = pSettings->value( strKey.arg( "MaxPendingConn" ), TCP_MAXPENDIG_CONN ).toUInt( );

    return nMaxPendingCount;
}

quint16 CSvrThread::GetThreadPoolCount( bool bServerEnd, bool bTcp )
{
    QString strKey = QString( "%1" ).arg( bServerEnd ? "ServerInfo" : "Database" ) + "/%1";
    QString strThreadPool = bTcp ? "TcpThreadPool" : "UdpThreadPool";
    quint16 nDefaultThreadPool = bTcp ? TCP_THREADPOOL_THREAD : UDP_THREADPOOL_THREAD;
    quint16 nThreadPool = pSettings->value( strKey.arg( strThreadPool ), nDefaultThreadPool ).toUInt( );

    return nThreadPool;
}

void CSvrThread::run( )
{
    try {
    exec( ); // Event loop to communicate with other thread
    } catch ( ... ) {
        int n = 0;
        n++;
    }
}
