#include "qjbipc.h"
#define JB_IPC "JBNVSDK.dll"

QDigitalCameraThread* QJBIPC::pThreadInstance = NULL;

QJBIPC::QJBIPC(QObject *parent) :
    QDigitalCameraThread(parent)
{
    GetFunctionPointer( );
}

QJBIPC::~QJBIPC( )
{
    if ( NULL != hDllMod ) {
        BOOL bRet = ::FreeLibrary( hDllMod );
        if ( !bRet ) {

        }
    }
}

QDigitalCameraThread* QJBIPC::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QJBIPC( );
        pThreadInstance->moveToThread( pThreadInstance );
        pThreadInstance->start( );
    }

    return pThreadInstance;
}

void QJBIPC::GetFunctionPointer( )
{
    QString strPath = qApp->applicationDirPath( ) + "/" + JB_IPC;
    WCHAR* pPath = ( WCHAR* ) strPath.utf16( );

    hDllMod = ::LoadLibrary( pPath );
    if ( NULL == hDllMod ) {
        return;
    }

    MyJBNV_OpenServer = ( JBNV_OpenServer ) ::GetProcAddress( hDllMod, "JBNV_OpenServer" );
    MyJBNV_CloseServer = ( JBNV_CloseServer ) ::GetProcAddress( hDllMod, "JBNV_CloseServer" );
    MyJBNV_OpenChannel = ( JBNV_OpenChannel ) ::GetProcAddress( hDllMod, "JBNV_OpenChannel" );
    MyJBNV_CloseChannel = ( JBNV_CloseChannel ) ::GetProcAddress( hDllMod, "JBNV_CloseChannel" );
}

void QJBIPC::run( )
{
    exec( );
}

void QJBIPC::ProcessIPCStartupEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJBIPC::ProcessIPCSetConnectTimeoutEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJBIPC::ProcessIPCSetReconnectTimeEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJBIPC::ProcessIPCLoginEvent( QCameraEvent* pEvent )
{
    QString& strIP = pEvent->GetIpcIp( );
    QByteArray byData = strIP.toAscii( );
    byData.append( char( 0 ) );

    char* pIP = byData.data( );
    char cUser[ ] = "admin";
    char cPwd[ ] = "admin";

    LONG lUserID = GetUserID( strIP );
    if ( -1 != lUserID ) {
        return;
    }

    // Login once, play multiple
    LPVOID pHandleServer;
    DWORD dwRet = MyJBNV_OpenServer( pIP, 8200,cUser,cPwd,&pHandleServer);
    SetUserID( strIP, ( LONG ) pHandleServer );
    Q_UNUSED( dwRet )
}

void QJBIPC::ProcessIPCCaptureJPGEvent( QCameraEvent* pEvent )
{

}

void QJBIPC::CaptureStaticImage( QString& strIP, QString& strFileName, HWND hPlayWnd )
{
    //CProcessData::CaptureSenseImage
    Q_UNUSED( strIP )
    //CapturePicture( strFileName, hPlayWnd );
}

void QJBIPC::ProcessIPCStartRealPlayEvent( QCameraEvent* pEvent )
{

    QString& strIP = pEvent->GetIpcIp( );
    LONG lUserID = GetUserID( strIP );
    HWND hPlayWnd = pEvent->GetVideoWndHandle( );
    LONG lPlayHandle = GetPlayHandle( hPlayWnd );

    if ( -1 != lPlayHandle ) {
        return;
    }

    LPVOID hChannelHandle;
    DWORD dwRet = MyJBNV_OpenChannel( ( HANDLE ) lUserID, 0, 0, 0, 0, hPlayWnd, FALSE,0, &hChannelHandle );
    lPlayHandle = ( LONG ) hChannelHandle;

    SetIP( lPlayHandle, strIP );
    SetPlayHandle( hPlayWnd, lPlayHandle );
    Q_UNUSED( dwRet )
}

void QJBIPC::ProcessIPCStopRealPlayEvent( QCameraEvent* pEvent )
{
    HWND hPlayWnd = pEvent->GetVideoWndHandle( );
    LONG lPlayHandle = GetPlayHandle( hPlayWnd );
    RemoveIP( lPlayHandle );
    RemovePlayHandle( hPlayWnd );

    if ( - 1 == lPlayHandle ) {
        return;
    }

    DWORD dwRet = MyJBNV_CloseChannel( ( HANDLE ) lPlayHandle );
    Q_UNUSED( dwRet )
}

void QJBIPC::ProcessIPCLogoutEvent( QCameraEvent* pEvent )
{
    QString& strIP = pEvent->GetIpcIp( );
    LONG lUserID = GetUserID( strIP );

    if ( - 1 == lUserID ) {
        return;
    }

    DWORD dwRet = MyJBNV_CloseServer( ( HANDLE ) lUserID );
    RemoveUserID( strIP );

    Q_UNUSED( dwRet )
}

void QJBIPC::ProcessIPCCleanupEvent( QCameraEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJBIPC::customEvent( QEvent *e )
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
