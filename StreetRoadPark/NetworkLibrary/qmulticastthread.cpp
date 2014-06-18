#include "qmulticastthread.h"
#include "../DatabaseLibrary/Constant.h"

QMulticastThread::QMulticastThread(QObject *parent) :
    QThread(parent)
{
    setObjectName( QString( "[Multicast Thread ID = %1]" ).arg( qrand( ) ) );
    pMulticast = NULL;
    pConfig = CNetConfigurator::GetConfigurator( );

    strTimeSyncJson = "{\"ClientID\":\"-1\","
                      "\"TypeCode\":\"TimeSync\","
                      "\"UserID\":\"-1\","
                      "\"Data\":{"
                      "\"CurrentTime\":\"%1\"}}";
    nTimeSyncInterval = pConfig->GetTimeSyncInterval( ) * 1000;
    nTimeSyncTimerID = 0;
}

QMulticastThread::~QMulticastThread( )
{
    if ( 0 != nTimeSyncTimerID ) {
        killTimer( nTimeSyncTimerID );
    }

    if ( NULL != pMulticast ) {
        delete pMulticast;
        pMulticast = NULL;
    }
}

void QMulticastThread::InitializeSubThread( )
{
    pMulticast = new QUdpMulticast( );

    if ( 0 < nTimeSyncInterval ) {
        //nTimeSyncTimerID = startTimer( nTimeSyncInterval );
    }
}

void QMulticastThread::run( )
{
    QString strLog = objectName() + " Started.";
    SendLog( strLog, true );
    InitializeSubThread( );
    exec() ;
}

void QMulticastThread::PrintIntervalTime( )
{
    return;
    QString strTime = QTime::currentTime( ).toString( "hh:mm:ss" );
    qDebug( ) << Q_FUNC_INFO << strTime << endl;
}

void QMulticastThread::timerEvent( QTimerEvent *event )
{
    if ( nTimeSyncTimerID != event->timerId( ) ) {
        return;
    }

    PrintIntervalTime( );
    QByteArray byJson = strTimeSyncJson.arg( pConfig->GetDateTime( ) ).toUtf8( );
    pMulticast->MulticastData( byJson, Constant::TypeSystemInfo );
}

void QMulticastThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QThreadEvent::EventType evtType = ( QThreadEvent::EventType ) pEvent->type( );

    if ( QThreadEvent::EventMulticastData == evtType ) {
        ProcessMultiDataEvent( pEvent );
    }
}

void QMulticastThread::SendLog( QString &strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void QMulticastThread::PostUDPMultiDataEvent(QByteArray &byUdpData, qint32 nPackageType )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadMulticast, QThreadEvent::EventMulticastData );

    pEvent->SetByteArray( byUdpData );
    pEvent->SetPackageType( nPackageType );
    PostEvent( pEvent );
}

void QMulticastThread::PostEvent( QThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void QMulticastThread::ProcessMultiDataEvent( QThreadEvent* pEvent )
{
    QByteArray& byJson = pEvent->GetByteArray( );
    qint32 nMulticastType = pEvent->GetPackageType( );
    pMulticast->MulticastData( byJson, nMulticastType );
}

QMulticastThread* QMulticastThread::CreateThread( QObject *pParent )
{
    qDebug( ) << Q_FUNC_INFO << endl;

    QMulticastThread* pThread = new QMulticastThread( pParent );

    pThread->start( );
    pThread->moveToThread( pThread );

    return pThread;
}
