#include "quv200thread.h"

#define TM_CAPTURE_UV200 "sdk_uv200.dll"

QAnalogCameraThread* QUv200Thread::pThreadInstance = NULL;

QUv200Thread::QUv200Thread(QObject *parent) :
    QAnalogCameraThread(parent)
{
    GetFunctionPointer( );
    bDeleteFile = false;
}

QUv200Thread::~QUv200Thread( )
{
    if ( NULL != hDllMod ) {
        BOOL bRet = ::FreeLibrary( hDllMod );
        if ( !bRet ) {

        }
    }
}

void QUv200Thread::SetDeleteFile( bool bDelete )
{
    bDeleteFile = bDelete;
}

QAnalogCameraThread* QUv200Thread::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QUv200Thread( );
        pThreadInstance->moveToThread( pThreadInstance );
        pThreadInstance->start( );
    }

    return pThreadInstance;
}

void QUv200Thread::GetFunctionPointer( )
{
    QString strPath = qApp->applicationDirPath( ) + "/" + TM_CAPTURE_UV200;
    WCHAR* pPath = ( WCHAR* ) strPath.utf16( );

    hDllMod = ::LoadLibrary( pPath );
    if ( NULL == hDllMod ) {
        return;
    }

    MyVCAInitSdk = ( VCAInitSdk ) ::GetProcAddress( hDllMod, "VCAInitSdk" );
    MyVCAUnInitSdk = ( VCAUnInitSdk ) ::GetProcAddress( hDllMod, "VCAUnInitSdk" );
    MyVCAConnectDevice = ( VCAConnectDevice ) GetProcAddress( hDllMod, "VCAConnectDevice" );
    MyVCADisConnectDevice = ( VCADisConnectDevice ) GetProcAddress( hDllMod, "VCADisConnectDevice" );
    MyVCAEnableMotionDetect = ( VCAEnableMotionDetect ) GetProcAddress( hDllMod, "VCAEnableMotionDetect" );
    MyVCACapturePicture = ( VCACapturePicture ) GetProcAddress( hDllMod, "VCACapturePicture" );
    MyVCARun = ( VCARun ) GetProcAddress( hDllMod, "VCARun" );
    MyVCAPause = ( VCAPause ) GetProcAddress( hDllMod, "VCAPause" );
    MyVCAStop = ( VCAStop ) GetProcAddress( hDllMod, "VCAStop" );
    MyVCAEnableCapSourceStream = ( VCAEnableCapSourceStream ) GetProcAddress( hDllMod, "VCAEnableCapSourceStream" );
    MyVCAStartCapture = ( VCAStartCapture ) GetProcAddress( hDllMod, "VCAStartCapture" );
    MyVCAStopCapture = ( VCAStopCapture ) GetProcAddress( hDllMod, "VCAStopCapture" );
    MyVCASetCaptureFile = ( VCASetCaptureFile ) GetProcAddress( hDllMod, "VCASetCaptureFile" );
    MyVCASetCurrentVideoCompressor = ( VCASetCurrentVideoCompressor ) GetProcAddress( hDllMod, "VCASetCurrentVideoCompressor" );
}

void QUv200Thread::run( )
{
    exec( );
}

void QUv200Thread::customEvent( QEvent *e )
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

void QUv200Thread::ProcessInitEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
    int nRet;
    nRet = MyVCAInitSdk( );
    nRet = 0;
}

void QUv200Thread::ProcessUninitEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
    MyVCAUnInitSdk( );
}

void QUv200Thread::ProcessOpenChannelEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QUv200Thread::ProcessCloseChannelEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QUv200Thread::ProcessStartCaptureEvent( QCameraEvent* pEvent )
{
    return;
    int nChannel = pEvent->GetChannel( );
    int nRet = MyVCASetCaptureFile( nChannel, ( char* ) "c:\\20130923-110456.avi" );
    nRet = MyVCASetCurrentVideoCompressor( nChannel, ( char* ) "XviD MPEG-4 Code");
    nRet = MyVCAStartCapture( nChannel );
    nRet = 0;
}

void QUv200Thread::ProcessStopCaptureEvent( QCameraEvent* pEvent )
{
    return;
    int nChannel = pEvent->GetChannel( );
    int nRet = MyVCAStopCapture( nChannel );
    nRet = 0;
}

void QUv200Thread::VidCapCallBack( long lnCardID, long pBuf, long lnWidth, long lnHeight, long lnBiCount )
{
    if ( 0 == pBuf || NULL == pThreadInstance ) {
        return;
    }

    if ( !pThreadInstance->GetMotionDetect( lnCardID ) ) {
        //return;
    }

    pThreadInstance->SetMotionDetect( false, lnCardID );

    QByteArray byVideo;
    byVideo.append( ( const char* ) pBuf, lnWidth * lnHeight * lnBiCount / 8 );

    pThreadInstance->GetPlateThread( )->PostPlateVideoRecognize( byVideo, lnWidth, lnHeight, lnCardID );
}

void QUv200Thread::MotionDelectCB( long lnCardID, BOOL bMove, LPVOID lpContext )
{
    QUv200Thread* pThread = ( QUv200Thread* ) lpContext;
    pThread->SendDetectInfo( lnCardID, bMove );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QUv200Thread::ProcessStartPreviewEvent( QCameraEvent* pEvent )
{
    int nRet = 0;
    int nChannel = pEvent->GetChannel( );
    HWND hVideoWnd = pEvent->GetVideoWndHandle( );
    SIZE nSize;
    nSize.cx = 720;
    nSize.cy = 576;

    nRet = MyVCAConnectDevice( nChannel, FALSE, hVideoWnd, nSize, Source_AV, 15, VideoSubType_RGB24 );
    //nRet = MyVCAEnableCapSourceStream( nChannel, TRUE, Odd_Even_Field, VidCapCallBack );
    //nRet = MyVCARun( nChannel );
    nRet = 0;
}

void QUv200Thread::ProcessStopPreviewEvent( QCameraEvent* pEvent )
{
    int nRet = 0;
    int nChannel = pEvent->GetChannel( );
    //nRet = MyVCAStop( nChannel );
    nRet = MyVCADisConnectDevice( nChannel );
    nRet = 0;
}

void QUv200Thread::ProcessStartMotionDetectEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QUv200Thread::ProcessStopMotionDetectEvent( QCameraEvent* pEvent )
{
    int nRet = 0;
    int nChannel = pEvent->GetChannel( );
}

void QUv200Thread::ProcessStartSourceStreamEvent( QCameraEvent* pEvent )
{
    int nRet = 0;
    int nChannel = pEvent->GetChannel( );
    //nRet = MyVCARegVidCapCallBack( nChannel, VidCapCallBack );
}

void QUv200Thread::ProcessStopSourceStreamEvent( QCameraEvent* pEvent )
{
    int nRet = 0;
    int nChannel = pEvent->GetChannel( );
    //nRet = MyVCARegVidCapCallBack( nChannel, NULL );
}

void QUv200Thread::CaptureStaticImage(QString &strFile, int nChannel)
{
    int nRet = 0;
    QByteArray byData = QCommon::GetTextCodec( )->fromUnicode( strFile );
    char* pFile = byData.data( );
    nRet = MyVCACapturePicture( nChannel, pFile, IMAGE_JPG, NULL, 80, 1, TRUE );
    Sleep( 20 );
    nRet = 0;
}

void QUv200Thread::ProcessCaptureImageEvent( QCameraEvent* pEvent )
{
    int nChannel = pEvent->GetChannel( );
    bool bRecognize = pEvent->GetRecognize( );
    QString& strFile = pEvent->GetImgFile( );

    CaptureStaticImage( strFile, nChannel );
    SendCaptureImage( strFile, nChannel );

    if ( bRecognize ) {
        GetPlateThread( )->PostPlateFileRecognize( strFile, nChannel, false, bDeleteFile );
    }
}
