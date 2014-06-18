#include "quv200timerthread.h"
#include <QDateTime>

QAnalogCameraThread* QUV200TimerThread::pThreadInstance = NULL;
bool QUV200TimerThread::bUv200Video = false;

QUV200TimerThread::QUV200TimerThread(QObject *parent) :
    QAnalogCameraThread(parent)
{
    pUv200Thread = NULL;
    strPlateDir = qApp->applicationDirPath( ) + "/PlatePic/";
    nTimerID = 0;
}

QUV200TimerThread::~QUV200TimerThread( )
{

}

void QUV200TimerThread::CaptureStaticImage( QString &strFile, int nChannel )
{
    pUv200Thread->CaptureStaticImage( strFile, nChannel );
}

void QUV200TimerThread::run()
{
    pUv200Thread = QUv200Thread::GetInstance( );
    QUv200Thread* pThread = ( QUv200Thread* ) pUv200Thread;
    pThread->SetDeleteFile( bUv200Video );

    exec( );
}

void QUV200TimerThread::customEvent(QEvent *e)
{
    Q_UNUSED( e )

    switch ( e->type( ) ) {
    case QEvent::User :
        nTimerID = startTimer( 20 );
        break;

    case QEvent::User + 1 :
        killTimer( nTimerID );
        break;
    }
}

void QUV200TimerThread::timerEvent( QTimerEvent *e )
{
    Q_UNUSED( e )

    QString strFile = strPlateDir + QString::number( QDateTime::currentMSecsSinceEpoch( ) ) + ".JPG";

    int nChannel = 0;
    pUv200Thread->PostCaptrueImageEvent( nChannel, strFile, true );
}

QAnalogCameraThread* QUV200TimerThread::GetInstance( bool bVideo )
{
    if ( NULL == pThreadInstance ) {
        bUv200Video = bVideo;
        pThreadInstance = new QUV200TimerThread( );
        pThreadInstance->moveToThread( pThreadInstance );
        pThreadInstance->start( );
    }

    return pThreadInstance;
}

void QUV200TimerThread::PostInitCaptureSDKEvent( HWND hParentVideo )
{
    pUv200Thread->PostInitCaptureSDKEvent( hParentVideo );
}

void QUV200TimerThread::PostUninitCaptureSDKEvent( )
{
    pUv200Thread->PostUninitCaptureSDKEvent( );
}

void QUV200TimerThread::PostOpenChannelEvent( int nChannel )
{
    pUv200Thread->PostOpenChannelEvent( nChannel );
}

void QUV200TimerThread::PostCloseChannelEvent( int nChannel )
{
    pUv200Thread->PostCloseChannelEvent( nChannel );
}

void QUV200TimerThread::PostStartCaptureEvent( int nChannel )
{
    pUv200Thread->PostStartCaptureEvent( nChannel );
}

void QUV200TimerThread::PostStopCaptureEvent( int nChannel )
{
    pUv200Thread->PostStopCaptureEvent( nChannel );
}

void QUV200TimerThread::PostPlayVideoEvent( int nChannel, HWND hVideo )
{
    pUv200Thread->PostPlayVideoEvent( nChannel, hVideo );

    if ( bUv200Video ) {
        //startTimer( 1 );
        QEvent* pEvent = new QEvent( QEvent::User );
        qApp->postEvent( this, pEvent );
    }
}

void QUV200TimerThread::PostStopVideoEvent( int nChannel )
{
    pUv200Thread->PostStopVideoEvent( nChannel );

    if ( bUv200Video ) {
        //startTimer( 1 );
        QEvent* pEvent = new QEvent( ( QEvent::Type ) ( ( int ) QEvent::User + 1 ) );
        qApp->postEvent( this, pEvent );
    }
}

void QUV200TimerThread::PostCaptrueImageEvent( int nChannel, QString& strFile, bool bRecognize )
{
    pUv200Thread->PostCaptrueImageEvent( nChannel, strFile, bRecognize );
}

void QUV200TimerThread::PostStartMotionDetectEvent( int nChannel )
{
    pUv200Thread->PostStartMotionDetectEvent( nChannel );
}

void QUV200TimerThread::PostStopMotionDetectEvent( int nChannel )
{
    pUv200Thread->PostStopMotionDetectEvent( nChannel );
}

void QUV200TimerThread::PostStartSourceStreamEvent( int nChannel, bool bRegister )
{
    pUv200Thread->PostStartSourceStreamEvent( nChannel, bRegister );
}

void QUV200TimerThread::PostStopSourceStreamEvent( int nChannel )
{
    pUv200Thread->PostStopSourceStreamEvent( nChannel );
}
