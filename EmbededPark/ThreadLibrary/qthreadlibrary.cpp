#include "qthreadlibrary.h"
#include "qlogthread.h"


QThreadLibrary::QThreadLibrary()
{
    InitializePointer( );
    connect( QLogThread::GetSingletonInstance( ), SIGNAL( DisplayLog( QString ) ),
             this, SLOT( HandleDisplayLog( QString ) ) );
}

void QThreadLibrary::HandleDisplayLog( QString strText )
{
    emit DisplayLog( strText );
}

void QThreadLibrary::HandleErrorCode( QTcpSocket *pSocket )
{
    ChangeHash( pSocket, false );
}

void QThreadLibrary::HandleClientDisconnect( QTcpSocket *pSocket )
{
    ChangeHash( pSocket, false );
}

void QThreadLibrary::ChangeHash( QTcpSocket *pSocket, bool bReconnect )
{
    QSocketThread* pThread = ( QSocketThread* )pSocket->thread( );
    const QString strKey = ( bReconnect ? pClientDisconnectHash : pClientConnectHash )->key( pThread );

    if ( strKey.isEmpty( ) ) {
        return;
    }

    ( bReconnect ? pClientConnectHash : pClientDisconnectHash )->insert( strKey, pThread );
    ( bReconnect ? pClientDisconnectHash : pClientConnectHash )->take( strKey );
}

void QThreadLibrary::HandleClientReconnect( QTcpSocket *pSocket )
{
    ChangeHash( pSocket, true );
}

void QThreadLibrary::InitializePointer( )
{
    pListenerThread = NULL;
    pClientConnectHash = NULL;
    pClientDisconnectHash = NULL;
}

void QThreadLibrary::ListenerThreadEixt( )
{
    if ( 0 != pListenerThread ) { // Server
        pListenerThread->PostThreadExit( pListenerThread );
        pListenerThread = NULL;
    }
}

void QThreadLibrary::ConnectClientSocktThreadEvent( QSocketThread *pThread )
{
    connect( pThread, SIGNAL( ClientDisconnect( QTcpSocket* ) ),
             this, SLOT( HandleClientDisconnect( QTcpSocket* ) ) );
    connect( pThread, SIGNAL( ClientReconnect( QTcpSocket* ) ),
             this, SLOT( HandleClientReconnect( QTcpSocket* ) ) );
    connect( pThread, SIGNAL( ErrorCode( QTcpSocket* ) ),
             this, SLOT( HandleErrorCode( QTcpSocket* ) ) );
}

void QThreadLibrary::ClientThreadExit( QThreadLibrary::QSocketThreadHash *pHash )
{
    QCommonLibrary::EventParam uParam;

    if ( 0 != pHash ) { // Client
        PostEventByHash( QCommonLibrary::EventExit, uParam, pHash );
        delete pHash;
    }
}

QThreadLibrary::~QThreadLibrary( )
{
    ListenerThreadEixt( );
    ClientThreadExit( pClientConnectHash );
    ClientThreadExit( pClientDisconnectHash );
    InitializePointer( );
}

void QThreadLibrary::PostListenerThreadEvent( QCommonLibrary::ThreadEventType eEvent )
{
    if ( 0 == pListenerThread ) {
        pListenerThread = QListenerThread::GetSingletonInstance( );
    }

    if ( QCommonLibrary::EventStartListen == eEvent ) {
        pListenerThread->PostStartListenEvent( );
    } else if( QCommonLibrary::EventStopListen == eEvent ) {
        pListenerThread->PostStopListenEvent( );
    } else if ( QCommonLibrary::EventExit == eEvent ) {
        ListenerThreadEixt( );
    }
}

void QThreadLibrary::PostClientSocketThreadEvent( QCommonLibrary::ThreadEventType eEvent,
                                                  QCommonLibrary::EventParam& uParam,
                                                  bool bSingelton,
                                                  QObject* pUIReceiver )
{
    if ( 0 == pClientConnectHash ) {
        pClientConnectHash = new QSocketThreadHash( );
    }

    if ( 0 == pClientDisconnectHash ) {
        pClientDisconnectHash = new QSocketThreadHash( );
    }

    if ( bSingelton ) {
        PostSingeltonEvent( eEvent, uParam, pUIReceiver );
    } else {
        PostInstanceEvent( eEvent, uParam, pUIReceiver );
    }
}

void QThreadLibrary::PostClientEvent( QCommonLibrary::ThreadEventType eEvent,
                                      QCommonLibrary::EventParam& uParam, QSocketThread *pThread )
{
    if ( 0 == pThread ) {
        return;
    }

    if ( QCommonLibrary::EventExit == eEvent ) {
        pThread->PostThreadExit( pThread );
    } else if ( QCommonLibrary::EventClientConnection == eEvent ) {
        pThread->PostClientConnectEvent( uParam );
    } else if ( QCommonLibrary::EventClientDisconnection == eEvent ) {
        pThread->PostClientDisconnectEvent( uParam );
    } else if ( QCommonLibrary::EventClientSendData == eEvent ) {
        pThread->PostClientSendDataEvent( uParam );
    }
}

void QThreadLibrary::GetKey( QString &strKey, QCommonLibrary::EventParam &uParam )
{
    quint32 nIP = uParam.ParamValue.ClientSocketThread.Host.nIP;
    quint16 nPort = uParam.ParamValue.ClientSocketThread.Host.nPort;
    quint16 nSequence = uParam.ParamValue.ClientSocketThread.Host.nSequence;
    QString strSeperator = QCommonLibrary::GetKeySeperator( );

    strKey = QString( "%1%2%3%4%5" ).arg( QString::number( nIP  ),
                                          strSeperator,
                                          QString::number( nPort  ),
                                          strSeperator,
                                          QString::number( nSequence  ) );
}

void QThreadLibrary::PostSingeltonEvent( QCommonLibrary::ThreadEventType eEvent,
                                         QCommonLibrary::EventParam& uParam,
                                         QObject* pUIReceiver )
{
    QSocketThread* pThread = NULL;
    QString strKey = "";
    GetKey( strKey, uParam );

    if ( pClientDisconnectHash->isEmpty( ) ) {
        pThread = QSocketThread::GetSingletonInstance( false, pUIReceiver );
        ConnectClientSocktThreadEvent( pThread );

    } else {
        pThread = pClientDisconnectHash->take( strKey );
    }

    pClientConnectHash->insert( strKey, pThread );

    PostClientEvent( eEvent, uParam, pThread );
}

void QThreadLibrary::PostInstanceEvent( QCommonLibrary::ThreadEventType eEvent,
                                        QCommonLibrary::EventParam& uParam,
                                        QObject* pUIReceiver )
{
    QSocketThread* pThread = NULL;
    QString strKey = "";
    GetKey( strKey, uParam );

    if ( QCommonLibrary::EventClientConnection == eEvent ) {
        if ( pClientDisconnectHash->isEmpty( ) ) {
            pThread = QSocketThread::GetInstance( false, QDataParserThread::GetInstance( ), pUIReceiver );
            ConnectClientSocktThreadEvent( pThread );
        } else {
            pThread = pClientDisconnectHash->take( strKey );
        }

        pClientConnectHash->insert( strKey, pThread );
        PostClientEvent( eEvent,uParam, pThread );
    } else {
        if ( uParam.ParamValue.ClientSocketThread.Host.bAll ) {
            PostEventByHash( eEvent, uParam, pClientConnectHash );

            if ( QCommonLibrary::EventClientDisconnection == eEvent ) {
                foreach( const QString& str, pClientConnectHash->keys( ) ) {
                    pThread = pClientConnectHash->take( str );
                    pClientDisconnectHash->insert( str, pThread );
                }
            } else if ( QCommonLibrary::EventExit == eEvent ) {
                PostEventByHash( eEvent, uParam, pClientDisconnectHash );
                pClientConnectHash->clear( );
                pClientDisconnectHash->clear( );
            }
        } else {
            if ( QCommonLibrary::EventClientDisconnection == eEvent ) {
                pThread = pClientConnectHash->take( strKey );
                pClientDisconnectHash->insert( strKey, pThread );
            } else if ( QCommonLibrary::EventExit == eEvent ) {
                pThread = pClientConnectHash->take( strKey );

                if ( 0 == pThread ) {
                    pThread = pClientDisconnectHash->take( strKey );
                }
            } else { // Send Data
                pThread = pClientConnectHash->value( strKey );
            }

            PostClientEvent( eEvent, uParam, pThread );
        }
    }
}

void QThreadLibrary::PostEventByHash( QCommonLibrary::ThreadEventType eEvent, QCommonLibrary::EventParam& uParam, QThreadLibrary::QSocketThreadHash *pHash )
{
    QSocketThread* pThread = NULL;
    QList< QSocketThread* > lstThread = pHash->values( );
    qint32 nThread = lstThread.length( );
    QByteArray byData;
    QByteArray* pByteArray = NULL;
    QString strKey = "";
    QString strSeperator = QCommonLibrary::GetKeySeperator( );
    QStringList lstHostInfo;

    for ( qint32 nIndex = 0; nIndex < nThread; nIndex++ ) {
        pThread = lstThread.at( nIndex );
        strKey = pHash->key( pThread );
        lstHostInfo = strKey.split( strSeperator );

        if ( 3 != lstHostInfo.length( ) ) {
            continue;
        }

        if ( QCommonLibrary::EventClientSendData == eEvent &&
             1 < nThread ) {
            if ( 0 == nIndex ) {
                pByteArray = uParam.ParamValue.ClientSocketThread.Data.pByteArray;
                byData.append( *pByteArray );
            } else {
                pByteArray = new QByteArray( byData );
                uParam.ParamValue.ClientSocketThread.Data.pByteArray = pByteArray;
            }
        }

        uParam.ParamValue.ClientSocketThread.Data.Host.nSequence = lstHostInfo.at( 2 ).toUShort( );
        PostClientEvent( eEvent, uParam, pThread );
    }
}
