#include "qjbipc.h"
#include <QApplication>
#define JB_IPC "JBNVSDK.dll"

QIPCThread* QJBIPC::pThreadInstance = NULL;

QJBIPC::QJBIPC(QObject *parent) :
    QIPCThread(parent)
{
    bStarted = false;
    pCodec = CCommonFunction::GetTextCodec( );
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

void QJBIPC::PostIPCEvent( QIPCEvent::IPCEventType evtType )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    qApp->postEvent( this, pEvent );
}

void QJBIPC::PostIPCEvent( QIPCEvent::IPCEventType evtType,
                               QIPCEvent::EventParam &uParam )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    pEvent->SetEventParam( uParam );
    qApp->postEvent( this, pEvent );
}

void QJBIPC::PostIPCStartupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCStartup );
}

void QJBIPC::PostIPCSetConnectTimeoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetConnectTimeout, uParam );
}

void QJBIPC::PostIPCSetReconnectTimeEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetReconnectTime, uParam );
}

void QJBIPC::PostIPCLoginEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogin, uParam );
}

void QJBIPC::PostIPCCaptureJPGEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCCaptureJPG, uParam );
}

void QJBIPC::PostIPCStartRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStartRealPlay, uParam );
}

void QJBIPC::PostIPCStopRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStopRealPlay, uParam );
}

void QJBIPC::PostIPCLogoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogout, uParam );
}

void QJBIPC::PostIPCCleanupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCCleanup );
}

QIPCThread* QJBIPC::GetInstance( )
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
    MyJBNV_OpenServer = NULL;
    MyJBNV_CloseServer = NULL;
    MyJBNV_OpenChannel = NULL;
    MyJBNV_CloseChannel = NULL;

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

void QJBIPC::CapturePreviewImage( HWND hPlayWnd, QString& strFileName )
{
    /*
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    QByteArray byData = pCodec->fromUnicode( strFileName );
    byData.append( char( 0 ) );
    char* pFile = byData.data( );

    LONG lPlayHandle = GetPlayHandle( hPlayWnd );
    if ( -1 == lPlayHandle ) {
        return;
    }

    BOOL bRet = NET_DVR_CapturePicture( lPlayHandle, pFile );
    bRet = TRUE;*/
}

void QJBIPC::CaptureDeviceImage( QString& strIP, QString& strFileName, HWND hPlayWnd )
{
    /*
    Q_UNUSED( hPlayWnd )
    //CProcessData::CaptureSenseImage
    QByteArray byData = pCodec->fromUnicode( strIP );
    byData.append( char( 0 ) );
    char* pIP = byData.data( );
    LONG lUserID = GetUserID( pIP );

    byData = pCodec->fromUnicode( strFileName );
    byData.append( char( 0 ) );
    char* pFile = byData.data( );

    if ( -1 == lUserID ) {
        return;
    }

    BOOL bRet = FALSE;
    NET_DVR_JPEGPARA sJpgData = { 0 };

    sJpgData.wPicSize = 0xff;
    sJpgData.wPicQuality = 0;

    bRet = NET_DVR_CaptureJPEGPicture( lUserID, 1, &sJpgData, pFile );
    */
}

void QJBIPC::run( )
{
    exec( );
}

void QJBIPC::ProcessIPCStartupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJBIPC::ProcessIPCSetConnectTimeoutEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJBIPC::ProcessIPCSetReconnectTimeEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJBIPC::SetUserID( char *pIP, LONG lUserID )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.insert( pIP, lUserID );
}

void QJBIPC::SetPlayHandle( HWND hPlayWnd, LONG lPlayHandle )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.insert( hPlayWnd, lPlayHandle );
}

LONG QJBIPC::GetUserID( char *pIP )
{
    LONG lUserID = -1;

    if ( NULL != pIP ) {
        lUserID = hashIP_UserHandle.value( pIP, -1 );
    }

    return lUserID;
}

void QJBIPC::RemoveUserID( char *pIP )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.remove( pIP );
}

LONG QJBIPC::GetPlayHandle( HWND hPlayWnd )
{
    LONG lPlayHandle = -1;

    if ( INVALID_HANDLE_VALUE != hPlayWnd ) {
        lPlayHandle = hashWnd_PlayHandle.value( hPlayWnd, -1 );
    }

    return lPlayHandle;
}
void QJBIPC::ClearHash( )
{
    hashIP_UserHandle.clear( );
    hashWnd_PlayHandle.clear( );
}

void QJBIPC::RemovePlayHandle( HWND hPlayWnd )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.remove( hPlayWnd );
}

void QJBIPC::ProcessIPCLoginEvent( QIPCEvent* pEvent )
{
    if ( NULL == MyJBNV_OpenServer ) {
        return;
    }

    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    LONG lUserID = GetUserID( uParam.EventLogin.cIP );
    char* pIP = uParam.EventLogin.cIP;

    char cUser[ ] = "admin";
    char cPwd[ ] = "admin";

    if ( -1 != lUserID ) {
        return;
    }

    // Login once, play multiple
    LPVOID pHandleServer;
    DWORD dwRet = MyJBNV_OpenServer( pIP, 8200,cUser,cPwd,&pHandleServer);
    SetUserID( pIP, ( LONG ) pHandleServer );
    Q_UNUSED( dwRet )
}

void QJBIPC::ProcessIPCCaptureJPGEvent( QIPCEvent* pEvent )
{

}

void QJBIPC::ProcessIPCStartRealPlayEvent( QIPCEvent* pEvent )
{
    if ( NULL == MyJBNV_OpenChannel ) {
        return;
    }

    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    LONG lUserID = GetUserID( uParam.EventStartRealPlay.cIP );
    bool bMainStream = uParam.EventStartRealPlay.bMainStream;

    if ( - 1 == lUserID ) {
        return;
    }

    HWND hPlayWnd = uParam.EventStartRealPlay.hPlayWnd;
    LONG lPlayHandle = GetPlayHandle( hPlayWnd );

    if ( -1 != lPlayHandle ) {
        return;
    }

    LPVOID hChannelHandle;
    DWORD dwRet = MyJBNV_OpenChannel( ( HANDLE ) lUserID, 0, 0, 0, 0, hPlayWnd, FALSE,0, &hChannelHandle );
    lPlayHandle = ( LONG ) hChannelHandle;

    if ( -1 == lPlayHandle ) {
        ;
    } else {
        SetPlayHandle( hPlayWnd, lPlayHandle );
    }

    Q_UNUSED( dwRet )
}

void QJBIPC::ProcessIPCStopRealPlayEvent( QIPCEvent* pEvent )
{
    if ( NULL == MyJBNV_CloseChannel ) {
        return;
    }

    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    HWND hPlayWnd = uParam.EventStopRealPlay.hPlayWnd;
    LONG lPlayHandle = GetPlayHandle( hPlayWnd );

    if ( - 1 == lPlayHandle ) {
        return;
    }

    DWORD dwRet = MyJBNV_CloseChannel( ( HANDLE ) lPlayHandle );
    RemovePlayHandle( hPlayWnd );
    Q_UNUSED( dwRet )
}

void QJBIPC::ProcessIPCLogoutEvent( QIPCEvent* pEvent )
{
    if ( NULL == MyJBNV_CloseServer ) {
        return;
    }

    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    char* pIP = uParam.EventLogout.cIP;
    LONG lUserID = GetUserID( pIP );

    if ( - 1 == lUserID ) {
        return;
    }

    DWORD dwRet = MyJBNV_CloseServer( ( HANDLE ) lUserID );
    RemoveUserID( pIP );
    Q_UNUSED( dwRet )
}

void QJBIPC::ProcessIPCCleanupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJBIPC::InitializeThread( )
{

}

void QJBIPC::customEvent( QEvent *e )
{
    QIPCEvent* pEvent = ( QIPCEvent* ) e;
    QIPCEvent::IPCEventType evtType = ( QIPCEvent::IPCEventType ) e->type( );

    switch ( evtType ) {
    case QIPCEvent::IPCStartup :
        ProcessIPCStartupEvent( pEvent );
        break;

    case QIPCEvent::IPCSetConnectTimeout :
        ProcessIPCSetConnectTimeoutEvent( pEvent );
        break;

    case QIPCEvent::IPCSetReconnectTime :
        ProcessIPCSetReconnectTimeEvent( pEvent );
        break;

    case QIPCEvent::IPCLogin :
        ProcessIPCLoginEvent( pEvent );
        break;

    case QIPCEvent::IPCCaptureJPG :
        ProcessIPCCaptureJPGEvent( pEvent );
        break;

    case QIPCEvent::IPCStartRealPlay :
        ProcessIPCStartRealPlayEvent( pEvent );
        break;

    case QIPCEvent::IPCStopRealPlay :
        ProcessIPCStopRealPlayEvent( pEvent );
        break;

    case QIPCEvent::IPCLogout :
        ProcessIPCLogoutEvent( pEvent );
        break;

    case QIPCEvent::IPCCleanup :
        ProcessIPCCleanupEvent( pEvent );
        break;

    default :
        break;
    }
}
