#include "qdhallinone.h"

#define DH_IPC_SDK "dhnetsdk.dll"
#define NullPointer( pFun ) if ( NULL == pFun ) { return; }

QIPCThread* QDHAllInOne::pThreadInstance = NULL;

QDHAllInOne::QDHAllInOne(QObject *parent) :
    QIPCThread(parent)
{
    bStarted = false;
    pCodec = CCommonFunction::GetTextCodec( );
    GetFunctionPointer( );
}

void QDHAllInOne::MyDisConnect( LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser )
{

}

void QDHAllInOne::PostIPCEvent( QIPCEvent::IPCEventType evtType )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    qApp->postEvent( this, pEvent );
}

void QDHAllInOne::PostIPCEvent( QIPCEvent::IPCEventType evtType,
                               QIPCEvent::EventParam &uParam )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    pEvent->SetEventParam( uParam );
    qApp->postEvent( this, pEvent );
}

void QDHAllInOne::PostIPCStartupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCStartup );
}

void QDHAllInOne::PostIPCSetConnectTimeoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetConnectTimeout, uParam );
}

void QDHAllInOne::PostIPCSetReconnectTimeEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetReconnectTime, uParam );
}

void QDHAllInOne::PostIPCLoginEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogin, uParam );
}

void QDHAllInOne::PostIPCCaptureJPGEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCCaptureJPG, uParam );
}

void QDHAllInOne::PostIPCStartRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStartRealPlay, uParam );
}

void QDHAllInOne::PostIPCStopRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStopRealPlay, uParam );
}

void QDHAllInOne::PostIPCLogoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogout, uParam );
}

void QDHAllInOne::PostIPCCleanupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCCleanup );
}

QIPCThread* QDHAllInOne::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        QIPCThread* pThread = new QDHAllInOne( );

        pThread->InitializeThread( );
        pThread->start( );
        pThread->moveToThread( pThread );

        pThreadInstance = pThread;
    }

    return pThreadInstance;
}

void QDHAllInOne::InitializeThread( )
{
    bool bRet = connect( this, SIGNAL( started( ) ),
                         this, SLOT( HandleStarted( ) ) );
    bRet = connect( this, SIGNAL( finished( ) ),
                             this, SLOT( HandleFinished( ) ) );
}

void QDHAllInOne::HandleStarted( )
{
}

void QDHAllInOne::HandleFinished( )
{
}

void QDHAllInOne::run( )
{
    exec( );
}

void QDHAllInOne::CapturePreviewImage( HWND hPlayWnd, QString& strFileName )
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
    bRet = TRUE;
    */
}

void QDHAllInOne::CaptureDeviceImage( QString& strIP, QString& strFileName, HWND hPlayWnd )
{
    /*
    NullPointer( MyCLIENT_CapturePicture );
    QByteArray byData = pCodec->fromUnicode( strIP );
    byData.append( char( 0 ) );
    char* pIP = byData.data( );
    LONG lUserID = GetUserID( pIP );

    byData = pCodec->fromUnicode( strFileName );
    byData.append( char( 0 ) );
    char* pFile = byData.data( );

    if ( -1 == lUserID ) {
        if ( !QFile::exists( strFileName ) ) {
            QFile file( strFileName );
            if ( file.open( QIODevice::ReadWrite ) ) {
                file.close( );
            }
        }
        return;
    }

    int nRet = MyCLIENT_CapturePicture( hPlayWnd, pFile, 70 );

    if ( nRet ) {
        if ( !QFile::exists( strFileName ) ) {
            QFile file( strFileName );
            if ( file.open( QIODevice::ReadWrite ) ) {
                file.close( );
            }
        }
        return;
    }
    */
}

void QDHAllInOne::ProcessIPCStartupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )

    if( bStarted ) {
        return;
    }

    bStarted = true;
/*
    NullPointer( MyVzLPRClient_Setup );
    int nRet = MyVzLPRClient_Setup( );
    QString strFunName = "VzLPRClient_Setup";
    PrintExceptionCode( nRet, strFunName );*/
}

QString QDHAllInOne::GetPlateMoveDirection( int nDirection )
{
    QString strDirection = "";

    switch ( nDirection ) {
    case DIRECTION_LEFT :
        strDirection = "вС";
        break;

    case DIRECTION_RIGHT :
        strDirection = "ср";
        break;

    case DIRECTION_UP :
        strDirection = "ио";
        break;

    case DIRECTION_DOWN :
        strDirection = "об";
        break;
    default :
        strDirection = "нч";
        break;
    }

    return strDirection;
}

/*
void QDHAllInOne::EmitPlate( VzLPRClientHandle handle,
                             const TH_PlateResult *pResult,
                             unsigned uNumPlates,
                             VZ_LPRC_RESULT_TYPE eResultType,
                             const VZ_LPRC_IMAGE_INFO *pImgFull,
                             const VZ_LPRC_IMAGE_INFO *pImgPlateClip )
{
    QString strPlate;
    int nWidth = 0;
    int nHeight = 0;
    QRect rect;
    QRect rectVideo;

    rectVideo.setLeft( 0 );
    rectVideo.setTop( 0 );
    rectVideo.setWidth( 0 );
    rectVideo.setHeight( 0 );

    QByteArray byData;
    int nChannel = GetUserIDChannel( handle );
    bool bSuccess = true;
    bool bVideo = true;

    for ( int nIndex = 0; nIndex < uNumPlates; nIndex++ ) {
        strPlate = QString( pResult[ nIndex ].license );
        nWidth = pResult[ nIndex ].rcLocation.right - pResult[ nIndex ].rcLocation.left;
        nHeight = pResult[ nIndex ].rcLocation.bottom - pResult[ nIndex ].rcLocation.top;

        rect.setRect( pResult[ nIndex ].rcLocation.left, pResult[ nIndex ].rcLocation.top,
                      nWidth, nHeight );
        emit UIPlateResult( strPlate, nChannel - 1, bSuccess, bVideo, nWidth, nHeight,
                            pResult[ nIndex ].nConfidence,
                            GetPlateMoveDirection( pResult[ nIndex ].nDirection ), byData, rect, rectVideo );
    }

    //qDebug( ) << Q_FUNC_INFO << QString::number( nChannel ) << ( int ) this << endl;
}
*/

void QDHAllInOne::ProcessIPCSetConnectTimeoutEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QDHAllInOne::ProcessIPCSetReconnectTimeEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QDHAllInOne::SetUserID( char *pIP, LONG lUserID )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.insert( pIP, lUserID );
}

void QDHAllInOne::SetPlayHandle( HWND hPlayWnd, LONG lPlayHandle )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.insert( hPlayWnd, lPlayHandle );
}

LONG QDHAllInOne::GetUserID( char *pIP )
{
    LONG lUserID = -1;

    if ( NULL != pIP ) {
        lUserID = hashIP_UserHandle.value( pIP, -1 );
    }

    return lUserID;
}

void QDHAllInOne::RemoveUserID( char *pIP )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.remove( pIP );
}

LONG QDHAllInOne::GetPlayHandle( HWND hPlayWnd )
{
    LONG lPlayHandle = -1;

    if ( INVALID_HANDLE_VALUE != hPlayWnd ) {
        lPlayHandle = hashWnd_PlayHandle.value( hPlayWnd, -1 );
    }

    return lPlayHandle;
}

void QDHAllInOne::RemovePlayHandle( HWND hPlayWnd )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.remove( hPlayWnd );
}

void QDHAllInOne::ProcessIPCLoginEvent( QIPCEvent* pEvent )
{
    /*
    NullPointer( MyVzLPRClient_Open );
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    LONG lUserID = GetUserID( uParam.EventLogin.cIP );
    char* pIP = uParam.EventLogin.cIP;

    if ( -1 != lUserID ) {
        return;
    }

    char cUser[ ] = "admin";
    char cPwd[ ] = "admin";

    // Login once, play multiple
    lUserID = MyVzLPRClient_Open( pIP, 80, cUser, cPwd );
    SetUserID( pIP, lUserID );

    QString strFunName = "VzLPRClient_Open";
    PrintExceptionCode( -1 == lUserID, strFunName );

    MyVzLPRClient_SetPlateInfoCallBack( lUserID, MyVZLPRC_PLATE_INFO_CALLBACK, this, 0 );
    */
}

void QDHAllInOne::ProcessIPCCaptureJPGEvent( QIPCEvent* pEvent )
{
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    LONG lUserID = GetUserID( uParam.EventCaptureJPG.cIP );
    char* pFile = uParam.EventCaptureJPG.cFile;

    if ( -1 == lUserID ) {
        return;
    }

    if ( NULL == pFile ) {
        return;
    }
/*
    BOOL bRet = FALSE;
    NET_DVR_JPEGPARA sJpgData = { 0 };

    sJpgData.wPicSize = 0xff;
    sJpgData.wPicQuality = 0;

    bRet = NET_DVR_CaptureJPEGPicture( lUserID, 1, &sJpgData, pFile );
    if ( !bRet ) {
        GetErrorMessage( );
        return;
    }

    QString strFile = pFile;

    emit CapturedJPGImage( uParam.EventCaptureJPG.nChannel, strFile ); // Send to UI
    */
}

void QDHAllInOne::ProcessIPCStartRealPlayEvent( QIPCEvent* pEvent )
{
    /*
    NullPointer( MyVzLPRClient_StartRealPlay );
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    LONG lUserID = GetUserID( uParam.EventStartRealPlay.cIP );

    if ( -1 == lUserID ) {
        return;
    }

    HWND hPlayWnd = uParam.EventStartRealPlay.hPlayWnd;
    LONG lPlayHandle = GetPlayHandle( hPlayWnd );
    int nChannel = uParam.EventStartRealPlay.nChannel;

    if ( -1 != lPlayHandle ) {
        return;
    }

    lPlayHandle = MyVzLPRClient_StartRealPlay( lUserID, hPlayWnd );
    SetPlayHandle( hPlayWnd, lPlayHandle );

    SetUserIDChannel( lUserID, nChannel );

    QString strFunName = "VzLPRClient_StartRealPlay";
    PrintExceptionCode( -1 == lPlayHandle, strFunName );
    */
}

void QDHAllInOne::ProcessIPCStopRealPlayEvent( QIPCEvent* pEvent )
{
    /*
    NullPointer( MyVzLPRClient_StopRealPlay );
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    HWND hPlayWnd = uParam.EventStopRealPlay.hPlayWnd;
    LONG lPlayHandle = GetPlayHandle( hPlayWnd );
    RemovePlayHandle( hPlayWnd );

    if ( -1 == lPlayHandle ) {
        return;
    }

    int nRet = MyVzLPRClient_StopRealPlay( hPlayWnd );
    QString strFunName = "VzLPRClient_StopRealPlay";
    PrintExceptionCode( nRet, strFunName );
    */
}

void QDHAllInOne::ProcessIPCLogoutEvent( QIPCEvent* pEvent )
{
    /*
    NullPointer( MyVzLPRClient_Close  );
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    char* pIP = uParam.EventLogout.cIP;
    LONG lUserID = GetUserID( pIP );

    if ( - 1 == lUserID ) {
        return;
    }

    int nRet = MyVzLPRClient_Close( lUserID );
    RemoveUserID( pIP );
    RemoveUserIDChannel( lUserID );

    QString strFunName = "VzLPRClient_Close";
    PrintExceptionCode( nRet, strFunName );
    */
}

void QDHAllInOne::SetUserIDChannel( int nUserID, int nChannel )
{
    hashUserID_Channel.insert( nUserID, nChannel );
}

LONG QDHAllInOne::GetUserIDChannel( int nUserID )
{
    return hashUserID_Channel.value( nUserID, 1 );
}

void QDHAllInOne::RemoveUserIDChannel( int nUserID )
{
    hashUserID_Channel.remove( nUserID );
}

void QDHAllInOne::ClearHash( )
{
    hashUserID_Channel.clear( );
    hashIP_UserHandle.clear( );
    hashWnd_PlayHandle.clear( );
}

void QDHAllInOne::GetFunctionPointer( )
{
    MyCLIENT_Init = NULL;
    MyCLIENT_Cleanup = NULL;
    MyCLIENT_SetAutoReconnect = NULL;
    MyCLIENT_SetConnectTime = NULL;
    MyCLIENT_GetLastError = NULL;
    MyCLIENT_LoginEx = NULL;
    MyCLIENT_Logout = NULL;
    MyCLIENT_RealPlay = NULL;
    MyCLIENT_StopRealPlay = NULL;
    MyCLIENT_CapturePicture = NULL;
    MyCLIENT_CreateTransComChannel  = NULL;
    MyCLIENT_SendTransComData  = NULL;
    MyCLIENT_DestroyTransComChannel  = NULL;
    MyCLIENT_QueryTransComParams  = NULL;

    QString strPath = qApp->applicationDirPath( ) + "/" + DH_IPC_SDK;
    WCHAR* pPath = ( WCHAR* ) strPath.utf16( );

    hDllMod = ::LoadLibrary( pPath );
    if ( NULL == hDllMod ) {
        return;
    }

    MyCLIENT_Init = ( CLIENT_Init ) ::GetProcAddress( hDllMod, "CLIENT_Init" );
    MyCLIENT_Cleanup = ( CLIENT_Cleanup ) ::GetProcAddress( hDllMod, "CLIENT_Cleanup" );

    MyCLIENT_SetAutoReconnect = ( CLIENT_SetAutoReconnect ) ::GetProcAddress( hDllMod, "CLIENT_SetAutoReconnect" );
    MyCLIENT_SetConnectTime = ( CLIENT_SetConnectTime ) ::GetProcAddress( hDllMod, "CLIENT_SetConnectTime" );

    MyCLIENT_GetLastError = ( CLIENT_GetLastError ) ::GetProcAddress( hDllMod, "CLIENT_GetLastError" );

    MyCLIENT_LoginEx = ( CLIENT_LoginEx ) ::GetProcAddress( hDllMod, "CLIENT_LoginEx" );
    MyCLIENT_Logout = ( CLIENT_Logout ) ::GetProcAddress( hDllMod, "CLIENT_Logout" );

    MyCLIENT_RealPlay = ( CLIENT_RealPlay ) ::GetProcAddress( hDllMod, "CLIENT_RealPlay" );
    MyCLIENT_StopRealPlay = ( CLIENT_StopRealPlay ) ::GetProcAddress( hDllMod, "CLIENT_StopRealPlay" );

    MyCLIENT_CapturePicture = ( CLIENT_CapturePicture ) ::GetProcAddress( hDllMod, "CLIENT_CapturePicture" );

    MyCLIENT_CreateTransComChannel = ( CLIENT_CreateTransComChannel ) ::GetProcAddress( hDllMod, "CLIENT_CreateTransComChannel" );
    MyCLIENT_SendTransComData = ( CLIENT_SendTransComData ) ::GetProcAddress( hDllMod, "CLIENT_SendTransComData" );
    MyCLIENT_DestroyTransComChannel  = ( CLIENT_DestroyTransComChannel ) ::GetProcAddress( hDllMod, "CLIENT_DestroyTransComChannel" );
    MyCLIENT_QueryTransComParams  = ( CLIENT_QueryTransComParams ) ::GetProcAddress( hDllMod, "CLIENT_QueryTransComParams" );
}

void QDHAllInOne::PrintExceptionCode( int nRet, QString& strFunName )
{
    return;
}

void QDHAllInOne::ProcessIPCCleanupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
/*
    NullPointer( MyVzLPRClient_Cleanup );
    int nRet = MyVzLPRClient_Cleanup( );
    QString strFunName = "VzLPRClient_Cleanup";
    PrintExceptionCode( nRet, strFunName );

    ClearHash( );
    bStarted = false;
    */
}

void QDHAllInOne::customEvent( QEvent* event )
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
