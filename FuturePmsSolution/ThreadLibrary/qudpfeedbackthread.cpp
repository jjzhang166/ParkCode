#include "qudpfeedbackthread.h"

QUdpFeedbackThread::QUdpFeedbackThread( QThread* pReceiver, QObject *parent ) :
    QMyBaseThread( parent )
{
    setObjectName( "QUdpFeedbackThread" );
    OutputMsg( QString( " Created" ) );

    pByteArray = NULL;
    pReceiverThread = pReceiver;
    pUdpClientSocket = NULL;

    connect( this, SIGNAL( SetSocketDescriptor( int ) ),
             this, SLOT( HandleSetSocketDescriptor( int ) ) );

    connect( this, SIGNAL( SendFeedbackData( void*, QString, quint16) ),
             this, SLOT( HandleSendFeedbackData( void*, QString, quint16 ) ) );

    InitializeSubThread( );
}

QUdpFeedbackThread::~QUdpFeedbackThread( )
{
    if ( NULL != pUdpClientSocket ) {
        delete pUdpClientSocket;
        pUdpClientSocket = NULL;
    }
}

void QUdpFeedbackThread::SendSetSocketDescriptorSignal( int nSocket )
{
    emit SetSocketDescriptor( nSocket );
}

void QUdpFeedbackThread::HandleSetSocketDescriptor( int nSocket )
{
    if ( pUdpClientSocket->socketDescriptor( ) != nSocket ) {
        pUdpClientSocket->setSocketDescriptor( nSocket );
    }
}

void QUdpFeedbackThread::HandleSendFeedbackData( void *pByteArray, QString senderIP, quint16 senderPort )
{
    QByteArray* pByData = ( QByteArray* ) pByteArray;
    ProcessFeedbackData( pByData, senderIP, senderPort );
    OutputMsg( QString( *pByData ) );
}

void QUdpFeedbackThread::run( )
{
    while ( true ) {
        forever {
            if (  !pUdpClientSocket->hasPendingDatagrams( ) ) {
                usleep( 100 );
            } else {
                break;
            }
        }

        ReadFeedbackData( );
    }
}

void QUdpFeedbackThread::ReadFeedbackData( )
{
    if ( NULL == pByteArray ) {
        pByteArray = new QByteArray( );
    }

    QByteArray* pByteDatagram = new QByteArray( );

    while ( pUdpClientSocket->hasPendingDatagrams( ) ) {
        pByteDatagram->clear( );
        pByteDatagram->resize( pUdpClientSocket->pendingDatagramSize( ) );

        pUdpClientSocket->readDatagram( pByteDatagram->data( ), pByteDatagram->size( ), &senderAddr, &senderPort );
        pByteArray->append( *pByteDatagram );
    }

    if ( 0 < pByteArray->length( ) ) {
        QString strIP = senderAddr.toString( );
        ProcessFeedbackData( pByteArray, strIP, senderPort );
        //emit SendFeedbackData( pByteArray, strIP, senderPort  );

        pByteArray = NULL;
    }

    delete pByteDatagram;
}

void QUdpFeedbackThread::InitializeSubThread( )
{
    if ( NULL == pUdpClientSocket ) {
        pUdpClientSocket = network.GenerateUdpClientSocket( commonFunction.GetTextCodec( ) );
        OutputMsg( objectName( ) );
    }

    connect( &network, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ), this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );
    connect( &network, SIGNAL( GetWholeUdpDatagram( void*, QString,quint16 ) ), this, SLOT( HandleGetWholeUdpDatagram( void*, QString, quint16 ) ) );
}

QUdpFeedbackThread* QUdpFeedbackThread::GetInstance( QThread* pReceiver )
{
    QUdpFeedbackThread* pThreadInstance = new QUdpFeedbackThread( pReceiver );
    pThreadInstance->InitializeThread( );
    //pThreadInstance->start( );
    //pThreadInstance->moveToThread( pThreadInstance );

    return pThreadInstance;
}

void QUdpFeedbackThread::ProcessFeedbackData( QByteArray *pByteArray, QString &strSenderIP, quint16 nSenderPort )
{
    // UDP Unicast Feedback data
    quint32 nBytePointer = ( quint32 ) pByteArray;
    MyDataStructs::PQQueueEventParams pEventParams = new MyDataStructs::QQueueEventParams;
    MyDataStructs::QEventMultiHash hash;

    hash.insertMulti( MyEnums::NetworkParamIP, strSenderIP );
    hash.insertMulti( MyEnums::NetworkParamPort, nSenderPort );
    hash.insertMulti( MyEnums::NetworkParamData, nBytePointer );

    pEventParams->enqueue( hash );
    PostUdpReceiveEvent( MyEnums::UdpClientReceiveDatagram, pEventParams, pReceiverThread );
}

void QUdpFeedbackThread::PostUdpReceiveEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread *pReceiver )
{
    bool bEvent = ( ( MyEnums::UdpClientEventStart < event ) && ( MyEnums::UdpClientEventEnd > event ) ) || ( MyEnums::ThreadExit == event );
    if ( !bEvent ) {
        return;
    }

    QUdpSenderThreadEvent* pEvent = new QUdpSenderThreadEvent( ( QEvent::Type ) event );
    pEvent->SetEventParams( pQueueEventParams );

    qApp->postEvent( pReceiver, pEvent );
}

void QUdpFeedbackThread::HandleGetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort )
{
    OutputMsg( strSenderIP + ":" + QString::number( nSenderPort ) );
    OutputMsg( "Sender:" + sender( )->objectName( ) + "GetWholeUdpDatagram( ... )" );
    emit GetWholeUdpDatagram( pByteArray, strSenderIP, nSenderPort );
}
