#include "qudpreceiversocketthread.h"

QUdpReceiverSocketThread::QUdpReceiverSocketThread( const MyEnums::UdpDatagramType dgType, QObject *parent) :
    QMyBaseThread(parent)
{
    udpDatagramType = dgType;
    setObjectName( "QUdpReceiverSocketThread" );
    OutputMsg( QString( " Created" ) );
    quint32 nStackSize = GetIniValue( QManipulateIniFile::ThreadPeerStackSize );
    setStackSize( nStackSize );
    bServerEnd = true;
    pUdpServerSocket = NULL;
    pDatabaseThread = NULL;
    qRegisterMetaType< MyEnums::UdpDatagramType >( "MyEnums::UdpDatagramType" );
}

QUdpReceiverSocketThread::~QUdpReceiverSocketThread( )
{
    if ( NULL != pUdpServerSocket ) {
        delete pUdpServerSocket;
        pUdpServerSocket = NULL;
    }

    OutputMsg( "" );
}

QUdpReceiverSocketThread* QUdpReceiverSocketThread::GetInstance(  bool bServer, const MyEnums::UdpDatagramType dgType  )
{
    QUdpReceiverSocketThread* pThreadInstance = new QUdpReceiverSocketThread( dgType );
    pThreadInstance->InitializeThread( );
    pThreadInstance->SetServerFlag( bServer );
    pThreadInstance->start( );
    pThreadInstance->moveToThread( pThreadInstance );

    return pThreadInstance;
}

void QUdpReceiverSocketThread::SetServerFlag( bool bServer )
{
    bServerEnd = bServer;
}

void QUdpReceiverSocketThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

quint32 QUdpReceiverSocketThread::GetIniValue( const QManipulateIniFile::IniFileSectionItems item )
{
    QManipulateIniFile::IniFileNames file = manipulateFile.GetIniFileNameType( );
    QVariant var;

    manipulateFile.IniFileValue( file, QManipulateIniFile::IniThread, item, false, var );

    return var.toUInt( );
}

void QUdpReceiverSocketThread::InitializeSubThread( )
{

    if ( bServerEnd && NULL == pDatabaseThread ) {
        pDatabaseThread = QDatabaseThread::GetSingleton(  );
    }

    if ( NULL == pUdpServerSocket ) {
        pUdpServerSocket = network.GenerateUdpServerSocket( commonFunction.GetTextCodec( ) );
        OutputMsg( objectName( ) );
    }

    connect( &network, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ), this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );
    connect( &network, SIGNAL( GetWholeUdpDatagram( void*, QString,quint16 ) ), this, SLOT( HandleGetWholeUdpDatagram( void*, QString, quint16 ) ) );
}

void QUdpReceiverSocketThread::PostDatabaseEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread *pReceiver )
{
    bool bEvent = ( ( MyEnums::DatabaseEventStart < event ) && ( MyEnums::DatabaseEventEnd > event ) ) || ( MyEnums::ThreadExit == event );
    if ( !bEvent ) {
        return;
    }

    QDatabaseThreadEvent* pEvent = new QDatabaseThreadEvent( ( QEvent::Type ) event );
    pEvent->SetEventParams( pQueueEventParams );

    qApp->postEvent( pReceiver, pEvent );
}

void QUdpReceiverSocketThread::ProcessDatabaseData( QByteArray *pByteArray, const QString& strSenderIP, const quint16 nSenderPort )
{
    //Post Event to Database thread
    quint32 nBytePointer = ( quint32 ) pByteArray;
    quint32 nSocketPointer = ( quint32 ) pUdpServerSocket;

    MyDataStructs::PQQueueEventParams pEventParams = new MyDataStructs::QQueueEventParams;
    MyDataStructs::QEventMultiHash hash;

    hash.insertMulti( MyEnums::NetworkParamData, nBytePointer );
    hash.insertMulti( MyEnums::NetworkParamSenderThread, ( quint32 ) this );
    hash.insertMulti( MyEnums::NetworkParamSocket, nSocketPointer );
    hash.insertMulti( MyEnums::NetworkParamUdpSenderIP, strSenderIP );
    hash.insertMulti( MyEnums::NetworkParamUdpSenderPort, nSenderPort );
    hash.insertMulti( MyEnums::NetworkParamUdpDatagramType, udpDatagramType );

    pEventParams->enqueue( hash );
    PostDatabaseEvent( MyEnums::DatabaseCrud, pEventParams, pDatabaseThread );
}

void QUdpReceiverSocketThread::ProcessOtherData( QByteArray *pByteArray, const QString& strSenderIP, const quint16 nSenderPort )
{
    QThreadPoolTask* pTask = QThreadPoolTask::GetInstance( pByteArray, this, NULL, pUdpServerSocket, NULL, false, strSenderIP, nSenderPort );
    pTask->SetUdpDatagramType( udpDatagramType );
    peerThreadPool.start( pTask );
}

void QUdpReceiverSocketThread::HandleGetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort )
{
    OutputMsg( strSenderIP + ":" + QString::number( nSenderPort ) );
    if ( NULL == pByteArray ) {
        return;
    }

    QByteArray* pByteData = ( QByteArray* ) pByteArray;

    if ( bServerEnd ) {
        //if ( Database ) {
            ProcessDatabaseData( pByteData, strSenderIP, nSenderPort );
        //} else if ( ... ) {
            //ProcessOtherData(  pByteData, strSenderIP, nSenderPort );
        //}
    } else {
        emit GetWholeUdpDatagram( pByteArray, strSenderIP, nSenderPort, udpDatagramType );
    }
}

void QUdpReceiverSocketThread::ProcessThreadPoolFeedbackEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );

    QVariant varData = hash.value( MyEnums::NetworkParamSocket );
    quint32 nSocketPointer = varData.toUInt( );
    QMyUdpSocket* pPeerSocket = ( QMyUdpSocket* ) nSocketPointer;

    varData = hash.value( MyEnums::NetworkParamData );
    quint32 nBytePointer = varData.toUInt( );
    QByteArray* pByteData = ( QByteArray* ) nBytePointer;

    varData = hash.value( MyEnums::NetworkParamUdpSenderIP );
    QString strSenderIP = varData.toString( );
    QHostAddress hostAddr( strSenderIP );

    varData = hash.value( MyEnums::NetworkParamUdpSenderPort );
    quint16 nSenderPort = ( quint16 ) varData.toUInt( );

    varData = hash.value( MyEnums::NetworkParamUdpDatagramType );
    MyEnums::UdpDatagramType dgType = ( MyEnums::UdpDatagramType ) varData.toInt( );
    const char* pDgType = ( const char* ) &dgType;
    int nDataSize = sizeof ( MyEnums::UdpDatagramType );

    pByteData->insert( 0, pDgType, nDataSize );

    network.UdpSendDatagram( pPeerSocket, *pByteData, hostAddr, nSenderPort ); // Feedback data to client endpoint
    msleep( 100 );

    delete pByteData;
}

void QUdpReceiverSocketThread::ProcessStartupListeningEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );
    QVariant varData = hash.value( MyEnums::NetworkParamListenerPort );
    quint16 nPort = ( quint16 ) varData.toUInt( );

    network.StartupUdpListening( pUdpServerSocket, nPort );
}

void QUdpReceiverSocketThread::ProcessJoinMulticastEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );
    QVariant varData = hash.value( MyEnums::NetworkParamIP );
    QString strIP = varData.toString( );
    QHostAddress groupAddress( strIP );

    network.UdpOperateMulticast( pUdpServerSocket, groupAddress, true );
}

void QUdpReceiverSocketThread::ProcessLeaveMulticastEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );
    QVariant varData = hash.value( MyEnums::NetworkParamIP );
    QString strIP = varData.toString( );
    QHostAddress groupAddress( strIP );

    network.UdpOperateMulticast( pUdpServerSocket, groupAddress, false );
}

void QUdpReceiverSocketThread::ProcessBroadcastDatagramEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );
    QVariant varData = hash.value( MyEnums::NetworkParamPort );
    quint16 nPort = ( quint16 ) varData.toUInt( );

    varData = hash.value( MyEnums::NetworkParamData );
    quint32 nBytePointer = varData.toUInt( );
    QByteArray* pByteArray = ( QByteArray* ) nBytePointer;

    network.UdpBroadcastDatagram( pUdpServerSocket, *pByteArray, nPort );

    delete pByteArray;
}

void QUdpReceiverSocketThread::ProcessSendDatagramEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );
    QVariant varData = hash.value( MyEnums::NetworkParamPort );
    quint16 nPort = ( quint16 ) varData.toUInt( );

    varData = hash.value( MyEnums::NetworkParamData );
    quint32 nBytePointer = varData.toUInt( );
    QByteArray* pByteArray = ( QByteArray* ) nBytePointer;

    varData = hash.value( MyEnums::NetworkParamIP );
    QString strIP = varData.toString( );
    QHostAddress hostAddress( strIP );

    network.UdpSendDatagram( pUdpServerSocket, *pByteArray, hostAddress, nPort );

    delete pByteArray;
}

void QUdpReceiverSocketThread::customEvent( QEvent *event )
{
    QUdpReceiverSocketThreadEvent* pEvent = ( QUdpReceiverSocketThreadEvent* ) event;
    MyEnums::EventType type = ( MyEnums::EventType ) pEvent->type( );
    MyDataStructs::PQQueueEventParams pEventParams = pEvent->GetEventParams( );

    if ( MyEnums::UdpServerStartupListening == type ) {
        ProcessStartupListeningEvent( pEventParams );
    } else if ( MyEnums::UdpServerJoinMulticast == type ) {
        ProcessJoinMulticastEvent( pEventParams );
    } else if ( MyEnums::UdpServerLeaveMulticast == type ) {
        ProcessLeaveMulticastEvent( pEventParams );
    } else if ( MyEnums::UdpServerBroadcastDatagram == type ) {
        ProcessBroadcastDatagramEvent( pEventParams );
    } else if ( MyEnums::UdpServerSendDatagram == type ) {
        ProcessSendDatagramEvent( pEventParams );
    } else if ( MyEnums::UdpServerThreadPoolFeedback == type ) {
        ProcessThreadPoolFeedbackEvent( pEventParams );
    } else if ( MyEnums::ThreadExit == type ) {
       LaunchThreadExit( );
    }
}

