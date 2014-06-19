#include "qtcpclientsocketthread.h"

QTcpClientSocketThread::QTcpClientSocketThread(QObject *parent) :
    QMyBaseThread(parent)
{
    setObjectName( "QTcpClientSocketThread" );
    OutputMsg( QString( " Created" ) );
    pClientSocket = NULL;
}

QTcpClientSocketThread::~QTcpClientSocketThread( )
{
    if ( NULL != pClientSocket ) {
        pClientSocket->close( );
        delete pClientSocket;
        pClientSocket = NULL;
    }

    OutputMsg( "" );
}

QTcpClientSocketThread* QTcpClientSocketThread::GetInstance( )
{
    QTcpClientSocketThread* pThreadInstance = new QTcpClientSocketThread( );
    pThreadInstance->InitializeThread( );
    pThreadInstance->start( );
    pThreadInstance->moveToThread( pThreadInstance );

    return pThreadInstance;
}

void QTcpClientSocketThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QTcpClientSocketThread::InitializeSubThread( )
{
    if ( NULL == pClientSocket ) {
        pClientSocket = network.GenerateTcpClientSocket( commonFunction.GetTextCodec( ) );
        OutputMsg( objectName( ) );
    }

    connect( &network, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ), this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );
    connect( &network, SIGNAL( GetWholeTcpStreamData( QTcpSocket*, void* ) ), this, SLOT( HandleGetWholeTcpStreamData( QTcpSocket*, void* ) ) );
}

void QTcpClientSocketThread::HandleGetWholeTcpStreamData( QTcpSocket* pPeerSocket, void *pByteArray )
{
    OutputMsg( "Sender:" + sender( )->objectName( ) + "GetWholeTcpStreamData( ... )" );
    emit GetWholeTcpStreamData( pPeerSocket, pByteArray );
}

void QTcpClientSocketThread::ProcessSendDataEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );
    QVariant varData = hash.value( MyEnums::NetworkParamData );
    quint32 nBytePointer = varData.toUInt( );

    QByteArray* pByteData = ( QByteArray* ) nBytePointer;
    network.TcpSendData( pClientSocket, *pByteData );

    delete pByteData;
}

void QTcpClientSocketThread::ProcessConnectEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ||
         QAbstractSocket::ConnectedState == pClientSocket->state( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );

    QVariant varIP = hash.value( MyEnums::NetworkParamIP );
    QVariant varPort = hash.value( MyEnums::NetworkParamPort );
    QString strIP = varIP.toString( );
    quint16 nPort = varPort.toString( ).toUShort( );
    QHostAddress addr( strIP );

    bool bRet = network.TcpConnect2Server( pClientSocket, addr, nPort );
    if ( !bRet ) {
        QString* pstrMsg = new QString( QString( "Connect [ %1 : %2 ] to fail" ).arg( strIP, QString::number( nPort ) ) );
        *pstrMsg = LogText( *pstrMsg ) ;
        HandleMessage( pstrMsg, QManipulateIniFile::LogThread );
    }
}

void QTcpClientSocketThread::ProcessDisconnectEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    // ¶ÏÁ´ÖØÁ¬
    pClientSocket->disconnectFromHost( );
}

void QTcpClientSocketThread::customEvent( QEvent *event )
{
    QTcpClientSocketThreadEvent* pEvent = ( QTcpClientSocketThreadEvent* ) event;
    MyEnums::EventType type = ( MyEnums::EventType ) pEvent->type( );
    MyDataStructs::PQQueueEventParams pEventParams = pEvent->GetEventParams( );

   if ( MyEnums::TcpClientSendData == type ) {
       ProcessSendDataEvent( pEventParams );
   } else if ( MyEnums::TcpClientConnect == type ) {
       ProcessConnectEvent( pEventParams );
   } else if ( MyEnums::TcpClientDisconnect == type ) {
       ProcessDisconnectEvent( pEventParams );
   } else if ( MyEnums::ThreadExit == type ) {
       LaunchThreadExit( );
    }
}
