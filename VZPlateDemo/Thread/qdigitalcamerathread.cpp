#include "qdigitalcamerathread.h"

//网络摄像机线程，完成图片抓取，视频流截取

QDigitalCameraThread::QDigitalCameraThread(QObject *parent) :
    QThread(parent)
{
    pPlateThread = QPlateThread::GetInstance( );
    pCodec = QCommon::GetTextCodec( );
}

QPlateThread* QDigitalCameraThread::GetPlateThread( )
{
    return pPlateThread;
}

void QDigitalCameraThread::SendCaptureImage( QString& strFile, QString& strIP )
{
    emit CaptureImage( strFile, strIP );
}

void QDigitalCameraThread::PostEvent( QCameraEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void QDigitalCameraThread::PostIPCStartupEvent( )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::IPCStartup );
    PostEvent( pEvent );
}

void QDigitalCameraThread::PostIPCSetConnectTimeoutEvent( )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::IPCSetConnectTimeout );
    PostEvent( pEvent );
}

void QDigitalCameraThread::PostIPCSetReconnectTimeEvent( )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::IPCSetReconnectTime );
    PostEvent( pEvent );
}

void QDigitalCameraThread::PostIPCLoginEvent( QString& strIP  )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::IPCLogin );
    pEvent->SetIpcIp( strIP );
    PostEvent( pEvent );
}

void QDigitalCameraThread::PostIPCCaptureJPGEvent( QString& strIP, QString& strFile, bool bRecognize, HWND hPlayWnd )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::IPCCaptureJPG );
    pEvent->SetIpcIp( strIP );
    pEvent->SetImgFile( strFile );
    pEvent->SetVideoWndHandle( hPlayWnd );
    pEvent->SetRecognize( bRecognize );
    PostEvent( pEvent );
}

void QDigitalCameraThread::PostIPCStartRealPlayEvent( QString& strIP, bool bMainStream, bool bRealStream, HWND hPlayWnd )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::IPCStartRealPlay );
    pEvent->SetIpcIp( strIP );
    pEvent->SetMainStream( bMainStream );
    pEvent->SetRealStream( bRealStream );
    pEvent->SetVideoWndHandle( hPlayWnd );
    PostEvent( pEvent );
}

void QDigitalCameraThread::PostIPCStopRealPlayEvent( HWND hPlayWnd )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::IPCStopRealPlay );
    pEvent->SetVideoWndHandle( hPlayWnd );
    PostEvent( pEvent );
}

void QDigitalCameraThread::PostIPCLogoutEvent( QString& strIP )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::IPCLogout );
    pEvent->SetIpcIp( strIP );
    PostEvent( pEvent );
}

void QDigitalCameraThread::PostIPCCleanupEvent( )
{
    QCameraEvent* pEvent = new QCameraEvent( ( QEvent::Type ) QCameraEvent::IPCCleanup );
    PostEvent( pEvent );
}

void QDigitalCameraThread::CaptureStaticImage( QString &strIP, QString &strFileName, HWND hPlayWnd )
{
    Q_UNUSED( strIP )
    Q_UNUSED( strFileName )
    Q_UNUSED( hPlayWnd )
}

void QDigitalCameraThread::SetUserID( QString& strIP, LONG lUserID )
{
    hashIP_UserHandle.insert( strIP, lUserID );
}

void QDigitalCameraThread::SetPlayHandle( HWND hPlayWnd, LONG lPlayHandle )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.insert( hPlayWnd, lPlayHandle );
}

void QDigitalCameraThread::SetIP( LONG lPlayHandle, QString& strIP )
{
    hashPlayHandle_IP.insert( lPlayHandle, strIP );
}

QString QDigitalCameraThread::GetIP( LONG lPlayHandle )
{
    return hashPlayHandle_IP.value( lPlayHandle );
}

void QDigitalCameraThread::RemoveIP( LONG lPlayHandle )
{
    hashPlayHandle_IP.remove( lPlayHandle );
}

void QDigitalCameraThread::SetResolution( LONG lPlayHandle, QString& strResolution )
{
    hashPlayHandle_Resolution.insert( lPlayHandle, strResolution );
}

QString QDigitalCameraThread::GetResolution( LONG lPlayHandle )
{
    return hashPlayHandle_Resolution.value( lPlayHandle );
}

void QDigitalCameraThread::RemoveResolution( LONG lPlayHandle )
{
    hashPlayHandle_Resolution.remove( lPlayHandle );
}

LONG QDigitalCameraThread::GetUserID( QString& strIP )
{
    return hashIP_UserHandle.value( strIP, -1 );
}

void QDigitalCameraThread::RemoveUserID( QString& strIP )
{
    hashIP_UserHandle.remove( strIP );
}

LONG QDigitalCameraThread::GetPlayHandle( HWND hPlayWnd )
{
    return hashWnd_PlayHandle.value( hPlayWnd, -1 );
}

HWND QDigitalCameraThread::GetPlayWnd( LONG lPlayHandle )
{
    return hashWnd_PlayHandle.key( lPlayHandle );
}

void QDigitalCameraThread::SetChannel( LONG lPlayHandle, LONG lChannel )
{
    hashPlayHandleChannel.insert( lPlayHandle, lChannel );
}

LONG QDigitalCameraThread::GetChannel( LONG lPlayHandle )
{
    return hashPlayHandleChannel.value( lPlayHandle );
}

LONG QDigitalCameraThread::GetPlayHandleByChannel( LONG lChannel )
{
    return hashPlayHandleChannel.key( lChannel );
}

void QDigitalCameraThread::RemovePlayHandle( HWND hPlayWnd )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.remove( hPlayWnd );
}

void QDigitalCameraThread::ClearHash( )
{
    hashIP_UserHandle.clear( );
    hashWnd_PlayHandle.clear( );
}

