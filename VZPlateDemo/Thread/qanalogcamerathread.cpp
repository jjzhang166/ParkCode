#include "qanalogcamerathread.h"

//采集卡线程，完成图片抓取，视频流截取

QAnalogCameraThread::QAnalogCameraThread(QObject *parent) :
    QThread(parent)
{
    pPlateThread = QPlateThread::GetInstance( );

    for ( int nIndex = 0; nIndex < CHANNEL_WAY; nIndex++ ) {
        SendDetectInfo( nIndex, false );
    }
}

QPlateThread* QAnalogCameraThread::GetPlateThread( )
{
    return pPlateThread;
}

void QAnalogCameraThread::PostEvent( QCameraEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void QAnalogCameraThread::PostInitCaptureSDKEvent( HWND hParentVideo )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraInit );
    pEvent->SetParentWndHandle( hParentVideo );
    PostEvent( pEvent );
}

void QAnalogCameraThread::SendCaptureImage( QString& strFile, int nChannel )
{
    emit CaptureImage( strFile, nChannel );
}

void QAnalogCameraThread::SendNotifyMessage( QString& strMsg, bool bSuccess )
{
    emit NotifyMessage( strMsg, bSuccess );
}

void QAnalogCameraThread::SendDetectInfo( int nChannel, bool bMotion )
{
    bMotionDetects[ nChannel ] = bMotion;
    emit DetectInfo( nChannel, bMotion );
}

void QAnalogCameraThread::SetMotionDetect( bool bMotion, int nChannel )
{
    bMotionDetects[ nChannel ] = bMotion;
}

void QAnalogCameraThread::CaptureStaticImage( QString &strFile, int nChannel )
{
    Q_UNUSED( strFile )
    Q_UNUSED( nChannel )
}

bool QAnalogCameraThread::GetMotionDetect( int nChannel )
{
    return bMotionDetects[ nChannel ];
}

void QAnalogCameraThread::PostUninitCaptureSDKEvent( )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraUninit );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostOpenChannelEvent( int nChannel )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraOpenChannel );
    pEvent->SetChannel( nChannel );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostCloseChannelEvent( int nChannel )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraCloseChannel );
    pEvent->SetChannel( nChannel );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostStartCaptureEvent( int nChannel )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraStartCapture );
    pEvent->SetChannel( nChannel );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostStopCaptureEvent( int nChannel )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraStopCapture );
    pEvent->SetChannel( nChannel );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostCaptrueImageEvent( int nChannel, QString& strFile, bool bRecognize )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraCaptureImage );
    pEvent->SetChannel( nChannel );
    pEvent->SetImgFile( strFile );
    pEvent->SetRecognize( bRecognize );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostPlayVideoEvent( int nChannel, HWND hVideo )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraStartPreview );
    pEvent->SetChannel( nChannel );
    pEvent->SetVideoWndHandle( hVideo );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostStopVideoEvent( int nChannel )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraStopPreview );
    pEvent->SetChannel( nChannel );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostStartMotionDetectEvent( int nChannel )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraStartMotionDetect );
    pEvent->SetChannel( nChannel );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostStopMotionDetectEvent( int nChannel )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraStopMotionDetect );
    pEvent->SetChannel( nChannel );
    PostEvent( pEvent );

}

void QAnalogCameraThread::PostStartSourceStreamEvent( int nChannel, bool bRegister )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraStartSourceStream );
    pEvent->SetChannel( nChannel );
    pEvent->SetRecognize( bRegister );
    PostEvent( pEvent );
}

void QAnalogCameraThread::PostStopSourceStreamEvent( int nChannel )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::CameraStopSourceStream );
    pEvent->SetChannel( nChannel );
    PostEvent( pEvent );
}
