#include "qhkcapturecardthread.h"

QAnalogCameraThread* QHkCaptureCardThread::pThreadInstance = NULL;

QHkCaptureCardThread::QHkCaptureCardThread(QObject *parent) :
    QAnalogCameraThread(parent)
{
    for ( int nIndex = 0; nIndex < CHANNEL_WAY; nIndex++ ) {
        SetChannelHandle( nIndex, INVALID_HANDLE_VALUE );
    }
}

QAnalogCameraThread* QHkCaptureCardThread::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QHkCaptureCardThread( );
        pThreadInstance->moveToThread( pThreadInstance );
        pThreadInstance->start( );
    }

    return pThreadInstance;
}

void QHkCaptureCardThread::run( )
{
    exec( );
}

HANDLE QHkCaptureCardThread::GetChannelHandle( int nChannel )
{
    return hChannels[ nChannel ];
}

void QHkCaptureCardThread::SetChannelHandle(int nChannel, HANDLE hChannel)
{
    hChannels[ nChannel ] = hChannel;
}

void QHkCaptureCardThread::customEvent( QEvent *e )
{
    QCameraEvent* pEvent = ( QCameraEvent* ) e;
    QCameraEvent::CameraEventType eType = ( QCameraEvent::CameraEventType ) e->type( );

    switch ( eType ) {
        case QCameraEvent::CameraInit :
            ProcessInitEvent( pEvent );
            break;

        case QCameraEvent::CameraUninit :
            ProcessUninitEvent( pEvent );
            break;

        case QCameraEvent::CameraOpenChannel :
            ProcessOpenChannelEvent( pEvent );
            break;

        case QCameraEvent::CameraCloseChannel :
            ProcessCloseChannelEvent( pEvent );
            break;

        case QCameraEvent::CameraStartCapture :
            ProcessStartCaptureEvent( pEvent );
            break;

        case QCameraEvent::CameraStopCapture :
            ProcessStopCaptureEvent( pEvent );
            break;

        case QCameraEvent::CameraStartPreview :
            ProcessStartPreviewEvent( pEvent );
            break;

        case QCameraEvent::CameraStopPreview :
            ProcessStopPreviewEvent( pEvent );
            break;

        case QCameraEvent::CameraCaptureImage :
            ProcessCaptureImageEvent( pEvent );
            break;

        case QCameraEvent::CameraStartMotionDetect :
            ProcessStartMotionDetectEvent( pEvent );
            break;

        case QCameraEvent::CameraStopMotionDetect :
            ProcessStopMotionDetectEvent( pEvent );
            break;

        case QCameraEvent::CameraStartSourceStream :
            ProcessStartSourceStreamEvent( pEvent );
            break;

        case QCameraEvent::CameraStopSourceStream :
            ProcessStopSourceStreamEvent( pEvent );
            break;
    }
}

void QHkCaptureCardThread::ProcessInitEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
    int nDsp = InitDSPs( );
    Q_UNUSED( nDsp )
}

void QHkCaptureCardThread::ProcessUninitEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent );
    int nRet = DeInitDSPs( );
    Q_UNUSED( nRet )
}

void QHkCaptureCardThread::ProcessOpenChannelEvent( QCameraEvent* pEvent )
{
    int nChannel = pEvent->GetChannel( );
    HANDLE hChannel = ChannelOpen( nChannel );
    SetChannelHandle( nChannel, hChannel );
}

void QHkCaptureCardThread::ProcessCloseChannelEvent( QCameraEvent* pEvent )
{
    int nChannel = pEvent->GetChannel( );
    int nRet = ChannelClose( GetChannelHandle( nChannel ) );
    Q_UNUSED( nRet )
}

void QHkCaptureCardThread::ProcessStartCaptureEvent( QCameraEvent* pEvent )
{
    int nChannel = pEvent->GetChannel( );
    int nRet  = StartVideoCapture( GetChannelHandle( nChannel ) );
    Q_UNUSED( nRet )
}

void QHkCaptureCardThread::ProcessStopCaptureEvent( QCameraEvent* pEvent )
{
    int nChannel = pEvent->GetChannel( );
    int nRet = StopVideoCapture( GetChannelHandle( nChannel ) );
    Q_UNUSED( nRet )
}

void QHkCaptureCardThread::ProcessStartPreviewEvent( QCameraEvent* pEvent )
{
    int nChannel = pEvent->GetChannel( );
    RECT rcClient;
    HWND hVideo = pEvent->GetVideoWndHandle( );
    //::GetWindowRect( hVideo, &rcClient );
    ::GetClientRect( hVideo, &rcClient );

    int nRet = StartVideoPreview( GetChannelHandle( nChannel ), hVideo, &rcClient, TRUE, 0, 25 );
    Q_UNUSED( nRet )
}

void QHkCaptureCardThread::ProcessStopPreviewEvent( QCameraEvent* pEvent )
{
    int nChannel = pEvent->GetChannel( );
    int nRet = StopVideoPreview( GetChannelHandle( nChannel ) );
    Q_UNUSED( nRet )
}

void QHkCaptureCardThread::MotionDetectCB( ULONG channelNumber, BOOL bMotionDetected, void *context )
{
    Q_UNUSED( context )
    //qDebug( ) << Q_FUNC_INFO << endl;

    if ( NULL != pThreadInstance ) {
        pThreadInstance->SendDetectInfo( channelNumber, bMotionDetected );
    }
}

QByteArray& QHkCaptureCardThread::GetChannelVideo( int nChannel )
{
    return objVideoStream[ nChannel ];
}

void QHkCaptureCardThread::ImageStreamCB( UINT channelNumber, void *context )
{
    QHkCaptureCardThread* pThread = ( QHkCaptureCardThread* ) context;

    if ( !pThread->GetMotionDetect( channelNumber ) ) {
        //return;
    }

    pThread->SetMotionDetect( false, channelNumber );

    QByteArray byVideo;
    byVideo.append( pThread->GetChannelVideo( channelNumber ) );

    QPlateThread* pPlate = pThread->GetPlateThread( );
    pPlate->PostPlateVideoRecognize( byVideo, 704, 576, channelNumber + 1, true );
}

void QHkCaptureCardThread::ProcessStartMotionDetectEvent( QCameraEvent* pEvent )
{
    int nRet = 0;
    int nChannel = pEvent->GetChannel( );
    RECT rc = { 0, 0, 703,575 };
    HANDLE hChannel = GetChannelHandle( nChannel );

    int nGradeValue = 6;
    int nFastFps = 6;
    int nSlowFps = 18;
    quint32 nDelayTime = 0;
    int nCount = 1;
    int nReserve = ( int ) this;

    nRet = SetupMotionDetectionEx( hChannel, nGradeValue, nFastFps,
                                   nSlowFps, nDelayTime, &rc, nCount, MotionDetectCB, nReserve );
    nRet = StartMotionDetection( hChannel );
    nRet = 0;
}

void QHkCaptureCardThread::ProcessStopMotionDetectEvent( QCameraEvent* pEvent )
{
    int nRet = 0;
    int nChannel = pEvent->GetChannel( );
    nRet = StopMotionDetection( GetChannelHandle( nChannel ) );
}

void QHkCaptureCardThread::ProcessStartSourceStreamEvent( QCameraEvent* pEvent )
{
    int nRet = 0;
    int nChannel = pEvent->GetChannel( );
    bool bRegister = pEvent->GetRecognize( );

    if ( bRegister ) {
        nRet = RegisterImageStreamCallback( ImageStreamCB, this );
    }

    QByteArray& byVideo = objVideoStream[ nChannel ];
    byVideo.resize( 704 * 576 * 3 / 2);
    nRet = SetImageStream( GetChannelHandle( nChannel ), TRUE, 25, 704, 576, ( PBYTE ) byVideo.data( ) );
}

void QHkCaptureCardThread::ProcessStopSourceStreamEvent( QCameraEvent* pEvent )
{
    int nRet = 0;
    int nChannel = pEvent->GetChannel( );
    nRet = SetImageStream( GetChannelHandle( nChannel ), FALSE, 25, 704, 576, NULL  );
}

void QHkCaptureCardThread::CaptureStaticImage( QString &strFile, int nChannel )
{
    int nRet = 0;
    ULONG lSize = 1024 * 1024 * 1;
    PUCHAR pImgBuff = new UCHAR[ lSize ];
    nRet = GetJpegImage( GetChannelHandle( nChannel ), pImgBuff, &lSize, 65 );
    if ( 0 != nRet ) {
        delete [ ] pImgBuff;
        return;
    }

    QFile imgFile( strFile );
    if ( imgFile.open( QIODevice::WriteOnly ) ) {
        const char* pData = ( const char* ) pImgBuff;
        imgFile.write( pData, lSize );
        imgFile.close( );
    }

    delete [ ] pImgBuff;
}

void QHkCaptureCardThread::ProcessCaptureImageEvent( QCameraEvent* pEvent )
{
    int nChannel = pEvent->GetChannel( );
    bool bRecognize = pEvent->GetRecognize( );
    QString& strFile = pEvent->GetImgFile( );

    CaptureStaticImage( strFile, nChannel );
    SendCaptureImage( strFile, nChannel );

    if ( bRecognize ) {
        GetPlateThread( )->PostPlateFileRecognize( strFile, nChannel );
    }
}
