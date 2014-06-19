#include "qmytcpserver.h"
#include "../CommonLibrary/CommonMacro.h"

QMyTcpServer::QMyTcpServer( quint16 nPort, int nMaxConnections, QObject *parent ) :
    QTcpServer(parent), nServerPort( nPort ), nPendingMaxConnection( nMaxConnections )
{    
    setObjectName( "QMyTcpServer" );
}

QMyTcpServer::~QMyTcpServer( )
{
    if ( isListening( ) ) {
        close( );
    }
}

void QMyTcpServer::Initialize( )
{
    Initialize( nServerPort, nPendingMaxConnection );
}

void QMyTcpServer::Initialize( quint16 nPort, int nMaxConnections )
{
    if ( isListening( ) ) {
        return;
    }

    setMaxPendingConnections( nMaxConnections );
    bool bRet = listen( QHostAddress::Any, nPort );

    QString* pstrMsg = new QString( QString( "Listen Port->Conn %1->%2 %3" ).arg(
                                        QString::number( nPort ), QString::number( nMaxConnections ), LogText( errorString( ) ) ) );

    if ( !bRet) {
        OutputMsg( QString( "emit NotifyMessage( %1, QManipulateIniFile::LogNetwork )" ).arg( *pstrMsg ) );
    }

    emit NotifyMessage( pstrMsg, QManipulateIniFile::LogNetwork );
}

void QMyTcpServer::incomingConnection( int socketDescriptor )
{
    OutputMsg( QString( "emit Accetp( %1 )" ).arg( socketDescriptor ) );
    emit Accept( socketDescriptor );
}
