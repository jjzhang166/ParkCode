#include "ping.h"
#include <QHostAddress>

CPing::CPing(QObject *parent) :
    QObject(parent)
{
    hFile = ::LoadLibrary( L"iphlpapi.dll" );
    hIcmpCreateFile = ( IcmpCreateFile ) ::GetProcAddress( hFile, "IcmpCreateFile" );
    hIcmpSendEcho = ( IcmpSendEcho ) ::GetProcAddress( hFile, "IcmpSendEcho" );
    hIcmpCloseHandle = ( ICmpCloseHandle ) ::GetProcAddress( hFile, "IcmpCloseHandle" );
    hIcmpFile = hIcmpCreateFile( );

    pReplyBuffer = NULL;
}

CPing::~CPing( )
{
    if ( NULL != pReplyBuffer ) {
        free( pReplyBuffer );
    }

    if ( NULL != hIcmpCloseHandle &&
         INVALID_HANDLE_VALUE != hIcmpFile ) {
        hIcmpCloseHandle( hIcmpFile );
    }

    if ( NULL != hFile ) {
        ::FreeLibrary( hFile );
    }
}

bool CPing::IcmpPing( QString &strIP )
{
        char SendData[ 32 ] = "Data Buffer";
        DWORD dwReplySize = sizeof ( ICMP_ECHO_REPLY ) +
                                                   sizeof ( SendData );

        if ( NULL == pReplyBuffer ) {
            pReplyBuffer = ( LPVOID* ) malloc( dwReplySize );
        }

        DWORD dwRetVal = 0;

        IPAddr ip;
        QHostAddress addr( strIP );
        unsigned long ipaddr = addr.toIPv4Address( );
        //ipaddr = inet_addr("119.75.218.90");
        ip.S_un.S_addr = ipaddr;

        dwRetVal = hIcmpSendEcho( hIcmpFile, ip, SendData,
                                                            sizeof( SendData ), NULL,
                                                            pReplyBuffer, dwReplySize, 1000 );

    return ( 0 != dwRetVal );
}
