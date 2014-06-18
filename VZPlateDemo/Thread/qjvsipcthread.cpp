#include "qjvsipcthread.h"

QDigitalCameraThread* QJvsIPCThread::pThreadInstance = NULL;

QJvsIPCThread::QJvsIPCThread(QObject *parent) :
    QDigitalCameraThread(parent)
{

}

QDigitalCameraThread* QJvsIPCThread::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QJvsIPCThread( );
        pThreadInstance->moveToThread( pThreadInstance );
        pThreadInstance->start( );
    }

    return pThreadInstance;
}

void QJvsIPCThread::run( )
{
    exec( );
}

int QJvsIPCThread::RealDataStreamCallback( HANDLE hTmCC, tmRealStreamInfo_t* pStreamInfo, void *pContext )
{
    int nRet = 0;

    if ( NULL == pContext ) {
        return nRet;
    }

    QJvsIPCThread* pThread = ( QJvsIPCThread* ) pContext;
    pThread->RealStream( hTmCC, pStreamInfo );

    return nRet;
}

void QJvsIPCThread::RealStream( HANDLE hTmCC, tmRealStreamInfo_t *pStreamInfo )
{
    ProcessDataStream( hTmCC, pStreamInfo );
}

void QJvsIPCThread::ProcessDataStream(HANDLE hTmCC, tmRealStreamInfo_t *pStreamInfo)
{
    if ( 0 != pStreamInfo->byFrameType ) { //帧类型0-视频，1-音频，2-数据流头
        return;
    }

    QString strIP = GetIP( ( LONG ) hTmCC );
    QByteArray byVideo;
    byVideo.append( ( const char* ) pStreamInfo->pBuffer, pStreamInfo->iBufferSize );

    GetPlateThread( )->PostPlateVideoRecognize( byVideo, pStreamInfo->iWidth, pStreamInfo->iHeight, strIP );
}

int QJvsIPCThread::RealStandardDataStreamCallback( HANDLE hTmCC, tmRealStreamInfo_t* pStreamInfo, void *pContext )
{
    int nRet = 0;

    if ( NULL == pContext ) {
        return nRet;
    }

    QJvsIPCThread* pThread = ( QJvsIPCThread* ) pContext;
    pThread->RealStandardStream( hTmCC, pStreamInfo );

    return nRet;
}

void QJvsIPCThread::RealStandardStream( HANDLE hTmCC, tmRealStreamInfo_t *pStreamInfo )
{
    ProcessDataStream( hTmCC, pStreamInfo );
}

void QJvsIPCThread::ProcessIPCStartupEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJvsIPCThread::ProcessIPCSetConnectTimeoutEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJvsIPCThread::ProcessIPCSetReconnectTimeEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJvsIPCThread::ProcessIPCLoginEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent );
}

void QJvsIPCThread::ProcessIPCCaptureJPGEvent( QCameraEvent* pEvent )
{
    QString& strIP = pEvent->GetIpcIp( );
    QString& strFile = pEvent->GetImgFile( );
    HWND hPlayWnd = pEvent->GetVideoWndHandle( );
    bool bRecognize = pEvent->GetRecognize( );

    CapturePicture( strFile, hPlayWnd );
    SendCaptureImage( strFile, strIP );

    if ( bRecognize ) {
        GetPlateThread( )->PostPlateFileRecognize( strFile, strIP );
    }
}

void QJvsIPCThread::CapturePicture( QString &strFileName, HWND hPlayWnd )
{
    HANDLE lUserID = ( HANDLE ) GetPlayHandle( hPlayWnd );

    if ( NULL == lUserID || INVALID_HANDLE_VALUE == lUserID ) {
        return;
    }

    QByteArray byData = pCodec->fromUnicode( strFileName );
    byData.append( char( 0 ) );
    char* pFile = byData.data( );
    BOOL bRet = FALSE;
    bRet = TMCC_CapturePictureToFile( lUserID, pFile, "JPEG" );
}

void QJvsIPCThread::CaptureStaticImage( QString& strIP, QString& strFileName, HWND hPlayWnd )
{
    //CProcessData::CaptureSenseImage
    Q_UNUSED( strIP )
    CapturePicture( strFileName, hPlayWnd );
}

void QJvsIPCThread::ProcessIPCStartRealPlayEvent( QCameraEvent* pEvent )
{
    QString& strIP = pEvent->GetIpcIp( );
    QByteArray byData = strIP.toAscii( );
    byData.append( char( 0 ) );
    char* pIP = byData.data( );
    bool bRealStream = pEvent->GetRealStream( );

    HWND hPlayWnd = pEvent->GetVideoWndHandle( );
    bool bMainStream = pEvent->GetMainStream( );

    tmPlayRealStreamCfg_t tPlayInfo = { 0 };
    tPlayInfo.dwSize = sizeof ( tmPlayRealStreamCfg_t );
    strcpy( tPlayInfo.szAddress, pIP );
    tPlayInfo.iPort = 6002;
    strcpy( tPlayInfo.szUser, "system" );
    strcpy( tPlayInfo.szPass, "system" );
    tPlayInfo.byStream = bMainStream ? 0 : 1;

    HANDLE hPreview = TMCC_Init( TMCC_INITTYPE_REALSTREAM );
    if ( NULL == hPreview ) {
        return;
    }

    if ( bRealStream ) {
        TMCC_RegisterStreamCallBack( hPreview, RealDataStreamCallback, this );
    } else {
        TMCC_RegisterRtpStreamCallBack( hPreview, RealStandardDataStreamCallback, this );
    }

    SetIP( ( LONG ) hPreview, strIP );
    SetPlayHandle( hPlayWnd, ( LONG ) hPreview );
    int nRet = TMCC_SetAutoReConnect( hPreview, TRUE );
    nRet = TMCC_ConnectStream( hPreview, &tPlayInfo, hPlayWnd );
}

void QJvsIPCThread::ProcessIPCStopRealPlayEvent( QCameraEvent* pEvent )
{
    HWND hPlayWnd = pEvent->GetVideoWndHandle( );
    HANDLE hPreview = ( HANDLE ) GetPlayHandle( hPlayWnd );
    RemovePlayHandle( hPlayWnd );
    RemoveIP( ( LONG ) hPreview );

    if ( NULL == hPreview ) {
        return;
    }

    TMCC_RegisterStreamCallBack( hPreview, NULL, NULL );
    int nRet = TMCC_CloseStream( hPreview );
    nRet = TMCC_DisConnect( hPreview );
    JwsCleanup( hPreview );
}

void QJvsIPCThread::ProcessIPCLogoutEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent );
}

void QJvsIPCThread::ProcessIPCCleanupEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
    ClearHash( );
}

void QJvsIPCThread::JwsCleanup( HANDLE hCtrl )
{
    if ( NULL == hCtrl ) {
        return;
    }

    int nRet = TMCC_ShutDown( hCtrl );
    nRet = TMCC_Done( hCtrl );
}

void QJvsIPCThread::customEvent( QEvent *e )
{
    QCameraEvent* pEvent = ( QCameraEvent* ) e;
    QCameraEvent::CameraEventType evtType = ( QCameraEvent::CameraEventType ) pEvent->type( );

    switch ( evtType ) {
    case QCameraEvent::IPCStartup :
        ProcessIPCStartupEvent( pEvent );
        break;

    case QCameraEvent::IPCSetConnectTimeout :
        ProcessIPCSetConnectTimeoutEvent( pEvent );
        break;

    case QCameraEvent::IPCSetReconnectTime :
        ProcessIPCSetReconnectTimeEvent( pEvent );
        break;

    case QCameraEvent::IPCLogin :
        ProcessIPCLoginEvent( pEvent );
        break;

    case QCameraEvent::IPCCaptureJPG :
        ProcessIPCCaptureJPGEvent( pEvent );
        break;

    case QCameraEvent::IPCStartRealPlay :
        ProcessIPCStartRealPlayEvent( pEvent );
        break;

    case QCameraEvent::IPCStopRealPlay :
        ProcessIPCStopRealPlayEvent( pEvent );
        break;

    case QCameraEvent::IPCLogout :
        ProcessIPCLogoutEvent( pEvent );
        break;

    case QCameraEvent::IPCCleanup :
        ProcessIPCCleanupEvent( pEvent );
        break;

    default :
        break;
    }
}
