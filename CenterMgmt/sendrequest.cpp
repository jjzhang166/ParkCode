#include "sendrequest.h"

CSendRequest::CSendRequest( CMgmtThread* pSender ) : pSenderThread( pSender )
{
    setAutoDelete( true );
}

void CSendRequest::run( )
{
    if ( NULL == pSenderThread ) {
        return;
    }

    QUdpSocket udpClient;
    pSenderThread->PeerRequest( &udpClient );
}

CSendRequest* CSendRequest::GetTask( CMgmtThread* pSender )
{
    return new CSendRequest( pSender );
}
