#include "QjwsIPCThread.h"
#include <QApplication>

QIPCThread* QJwsIPCThread::pThreadInstance = NULL;

BOOL CALLBACK TmccConnectCallback( HANDLE hTmCC, BOOL bConnect, unsigned int dwResult, void *context )
{
    if ( NULL == context ) {
        return bConnect;
    }

    QJwsIPCThread* pThread = ( QJwsIPCThread* ) context;
    pThread->SendNotify( hTmCC, bConnect, dwResult );

    return bConnect;
}

QJwsIPCThread::QJwsIPCThread(QObject *parent) :
    QIPCThread(parent)
{
    bStarted = false;
    pCodec = CCommonFunction::GetTextCodec( );

    //hTmccCtrl = NULL;
    //hTmccPreview = NULL;
}

void QJwsIPCThread::SendNotify( HANDLE hTmCC, BOOL bConnect, unsigned int dwResult )
{
    Q_UNUSED( dwResult )

    QString strText = "视频流播放 %1";

    strText = strText.arg( bConnect ? "连接" : "断开" );

    EmitMsg( strText, Q_FUNC_INFO );
}

void QJwsIPCThread::PostIPCEvent( QIPCEvent::IPCEventType evtType )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    qApp->postEvent( this, pEvent );
}

void QJwsIPCThread::PostIPCEvent( QIPCEvent::IPCEventType evtType,
                               QIPCEvent::EventParam &uParam )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    pEvent->SetEventParam( uParam );
    qApp->postEvent( this, pEvent );
}

void QJwsIPCThread::PostIPCStartupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCStartup );
}

void QJwsIPCThread::PostIPCSetConnectTimeoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetConnectTimeout, uParam );
}

void QJwsIPCThread::PostIPCSetReconnectTimeEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetReconnectTime, uParam );
}

void QJwsIPCThread::PostIPCLoginEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogin, uParam );
}

void QJwsIPCThread::PostIPCCaptureJPGEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCCaptureJPG, uParam );
}

void QJwsIPCThread::PostIPCStartRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStartRealPlay, uParam );
}

void QJwsIPCThread::PostIPCStopRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStopRealPlay, uParam );
}

void QJwsIPCThread::PostIPCLogoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogout, uParam );
}

void QJwsIPCThread::PostIPCCleanupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCCleanup );
}

QIPCThread* QJwsIPCThread::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        QIPCThread* pThread = new QJwsIPCThread( );

        pThread->InitializeThread( );
        pThread->start( );
        pThread->moveToThread( pThread );

        pThreadInstance = pThread;
    }

    return pThreadInstance;
}

void QJwsIPCThread::InitializeThread( )
{
    bool bRet = connect( this, SIGNAL( started( ) ),
                         this, SLOT( HandleStarted( ) ) );
    bRet = connect( this, SIGNAL( finished( ) ),
                             this, SLOT( HandleFinished( ) ) );
}

void QJwsIPCThread::HandleStarted( )
{
}

void QJwsIPCThread::HandleFinished( )
{
}

void QJwsIPCThread::run( )
{
    exec( );
}

void QJwsIPCThread::CapturePreviewImage( HWND hPlayWnd, QString& strFileName )
{

}

void QJwsIPCThread::CaptureDeviceImage( QString& strIP, QString& strFileName, HWND hPlayWnd )
{
    //CProcessData::CaptureSenseImage
    QByteArray byData = pCodec->fromUnicode( strIP );
    byData.append( char( 0 ) );
    //char* pIP = byData.data( );
    HANDLE lUserID = GetPlayHandle( hPlayWnd );

    if ( NULL == lUserID ) {
        return;
    }

    byData = pCodec->fromUnicode( strFileName );
    byData.append( char( 0 ) );
    char* pFile = byData.data( );
    BOOL bRet = FALSE;
    bRet = TMCC_CapturePictureToFile( lUserID, pFile, "JPEG" );
}

void QJwsIPCThread::GetErrorMessage( )
{
    int nCode = TMCC_GetLastError( );
    QString strText = QString::number( nCode, 16 );
    EmitMsg( strText, Q_FUNC_INFO );
}

void QJwsIPCThread::EmitMsg(QString strMsg, QString strFunName)
{
    emit NotifyMessage( strMsg );
    qDebug( ) << strMsg << ":" << strFunName << endl;
}

void QJwsIPCThread::ProcessIPCStartupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )

    if( bStarted ) {
        EmitMsg( "已经初始化了。", Q_FUNC_INFO );
        return;
    }

    bStarted = true; //TMCC_ERR_SUCCESS

    //hTmccCtrl = TMCC_Init( TMCC_INITTYPE_CONTROL );
    //if ( NULL == hTmccCtrl ) {
    //    GetErrorMessage( );
    //}

    //TMCC_RegisterConnectCallBack( hTmccCtrl, TmccConnectCallback, this );

    //hTmccPreview = TMCC_Init( TMCC_INITTYPE_REALSTREAM );
    //if ( NULL == hTmccPreview ) {
    //    GetErrorMessage( );
    //}

    //TMCC_RegisterConnectCallBack( hTmccPreview, TmccConnectCallback, this );
}

void QJwsIPCThread::ProcessIPCSetConnectTimeoutEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
    // 300,75000 // Reserved
    //QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );

    //int nRet = TMCC_SetTimeOut( hTmccCtrl, uParam.EventConnectTimeout.dwWaitTime );
    //if ( TMCC_ERR_SUCCESS != nRet ) {
    //    GetErrorMessage( );
    //}

    //int nRet = TMCC_SetTimeOut( hTmccPreview, uParam.EventConnectTimeout.dwWaitTime );
    //if ( TMCC_ERR_SUCCESS != nRet ) {
    //    GetErrorMessage( );
    //}
}

void QJwsIPCThread::ProcessIPCSetReconnectTimeEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
    //QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );

    //int nRet = TMCC_SetAutoReConnect( hTmccCtrl, uParam.EventReconnectTimeout.bEnableRecon );
    //if ( TMCC_ERR_SUCCESS != nRet ) {
    //    GetErrorMessage( );
    //}

    //int nRet = TMCC_SetAutoReConnect( hTmccPreview, uParam.EventReconnectTimeout.bEnableRecon );
    //if ( TMCC_ERR_SUCCESS != nRet ) {
    //    GetErrorMessage( );
    //}
}

void QJwsIPCThread::SetUserID( char *pIP, HANDLE lUserID )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.insert( pIP, lUserID );
}

void QJwsIPCThread::SetPlayHandle( HWND hPlayWnd, HANDLE lPlayHandle )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.insert( hPlayWnd, lPlayHandle );
}

HANDLE QJwsIPCThread::GetUserID( char *pIP )
{
    HANDLE lUserID = NULL;

    if ( NULL != pIP ) {
        lUserID = hashIP_UserHandle.value( pIP, NULL );
    }

    return lUserID;
}

void QJwsIPCThread::RemoveUserID( char *pIP )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.remove( pIP );
}

HANDLE QJwsIPCThread::GetPlayHandle( HWND hPlayWnd )
{
    HANDLE lPlayHandle = NULL;

    if ( INVALID_HANDLE_VALUE != hPlayWnd ) {
        lPlayHandle = hashWnd_PlayHandle.value( hPlayWnd, NULL );
    }

    return lPlayHandle;
}

void QJwsIPCThread::RemovePlayHandle( HWND hPlayWnd )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.remove( hPlayWnd );
}

void QJwsIPCThread::JwsConnect( QIPCEvent* pEvent, HANDLE hCtrl )
{
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    char* pIP = uParam.EventLogin.cIP;

    if ( TMCC_IsConnect( hCtrl ) ) {
        EmitMsg( QString( "已经登录【%1】." ).arg( pIP ), Q_FUNC_INFO );
        return;
    }

    tmConnectInfo_t tConnInfo = { 0 };

    tConnInfo.dwSize = sizeof ( tmConnectInfo_t );
    strcpy( tConnInfo.pIp, pIP );
    tConnInfo.iPort = uParam.EventLogin.wPort;
    strcpy( tConnInfo.szUser, uParam.EventLogin.cUser );
    strcpy( tConnInfo.szPass, uParam.EventLogin.cPwd );

    int nRet = TMCC_Connect( hCtrl, &tConnInfo, TRUE );
    if ( TMCC_ERR_SUCCESS != nRet ) {
        GetErrorMessage( );
    }
}

void QJwsIPCThread::ProcessIPCLoginEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent );
    //JwsConnect( pEvent, hTmccCtrl );
    //JwsConnect( pEvent, hTmccPreview );
    //int nRet = TMCC_SetDisplayShow( hTmccPreview, TRUE );
    //if ( TMCC_ERR_SUCCESS != nRet ) {
    //    GetErrorMessage( );
    //}
}

void QJwsIPCThread::ProcessIPCCaptureJPGEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QJwsIPCThread::ProcessIPCStartRealPlayEvent( QIPCEvent* pEvent )
{
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    char* pIP = uParam.EventStartRealPlay.cIP;
    HWND hPlayWnd = uParam.EventStartRealPlay.hPlayWnd;
    bool bMainStream = uParam.EventStartRealPlay.bMainStream;

    tmPlayRealStreamCfg_t tPlayInfo = { 0 };
    tPlayInfo.dwSize = sizeof ( tmPlayRealStreamCfg_t );
    strcpy( tPlayInfo.szAddress, pIP );
    tPlayInfo.iPort = 6002;
    strcpy( tPlayInfo.szUser, "system" );
    strcpy( tPlayInfo.szPass, "system" );
    tPlayInfo.byStream = bMainStream ? 0 : 1;

    HANDLE hPreview = TMCC_Init( TMCC_INITTYPE_REALSTREAM );
    if ( NULL == hPreview ) {
        GetErrorMessage( );
        return;
    }

    //SetUserID( pIP, hPreview );
    SetPlayHandle( hPlayWnd, hPreview );

    int nRet = TMCC_SetAutoReConnect( hPreview, TRUE );
    if ( TMCC_ERR_SUCCESS != nRet ) {
        GetErrorMessage( );
    }

    nRet = TMCC_ConnectStream( hPreview, &tPlayInfo, hPlayWnd);
    if ( TMCC_ERR_SUCCESS != nRet ) {
        GetErrorMessage( );
    }
}

void QJwsIPCThread::ProcessIPCStopRealPlayEvent( QIPCEvent* pEvent )
{
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    HWND hPlayWnd = uParam.EventStopRealPlay.hPlayWnd;
    HANDLE hPreview = GetPlayHandle( hPlayWnd );
    RemovePlayHandle( hPlayWnd );

    if ( NULL == hPreview ) {
        return;
    }

    int nRet = TMCC_CloseStream( hPreview );
    if ( TMCC_ERR_SUCCESS != nRet ) {
        GetErrorMessage( );
    }

    nRet = TMCC_DisConnect( hPreview );
    if ( TMCC_ERR_SUCCESS != nRet ) {
        GetErrorMessage( );
    }

    JwsCleanup( hPreview );
}

void QJwsIPCThread::ProcessIPCLogoutEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent );

    //int nRet = TMCC_DisConnect( hTmccCtrl );
    //if ( TMCC_ERR_SUCCESS != nRet ) {
    //    GetErrorMessage( );
    //}

    //int nRet = TMCC_DisConnect( hTmccPreview );
    //if ( TMCC_ERR_SUCCESS != nRet ) {
    //    GetErrorMessage( );
    //}
}

void QJwsIPCThread::ClearHash( )
{
    hashIP_UserHandle.clear( );
    hashWnd_PlayHandle.clear( );
}

void QJwsIPCThread::JwsCleanup( HANDLE hCtrl )
{
    if ( NULL == hCtrl ) {
        return;
    }

    int nRet = TMCC_ShutDown( hCtrl );
    if ( TMCC_ERR_SUCCESS != nRet ) {
        GetErrorMessage( );
    }

    nRet = TMCC_Done( hCtrl );
    if ( TMCC_ERR_SUCCESS != nRet ) {
        GetErrorMessage( );
    }
}

void QJwsIPCThread::ProcessIPCCleanupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )

    //JwsCleanup( hTmccCtrl );
    //JwsCleanup( hTmccPreview );

    ClearHash( );
    bStarted = false;
}

void QJwsIPCThread::customEvent( QEvent* event )
{
    QIPCEvent* pEvent = ( QIPCEvent* ) event;
    QIPCEvent::IPCEventType evtType = ( QIPCEvent::IPCEventType ) pEvent->type( );

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
