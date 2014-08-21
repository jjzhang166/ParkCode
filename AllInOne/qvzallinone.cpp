#include "qvzallinone.h"
#include <QFile>

#define VZ_IVS_SDK "VzLPRSDK.dll"
#define NullPointer( pFun ) if ( NULL == pFun ) { return; }

QIPCThread* QVzAllInOne::pThreadInstance = NULL;

QVzAllInOne::QVzAllInOne(QObject *parent) :
    QIPCThread(parent)
{
    bStarted = false;
    pCodec = CCommonFunction::GetTextCodec( );
    GetFunctionPointer( );
}

void QVzAllInOne::PostIPCEvent( QIPCEvent::IPCEventType evtType )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    qApp->postEvent( this, pEvent );
}

void QVzAllInOne::PostIPCEvent( QIPCEvent::IPCEventType evtType,
                               QIPCEvent::EventParam &uParam )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    pEvent->SetEventParam( uParam );
    qApp->postEvent( this, pEvent );
}

void QVzAllInOne::PostIPCStartupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCStartup );
}

void QVzAllInOne::PostIPCSetConnectTimeoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetConnectTimeout, uParam );
}

void QVzAllInOne::PostIPCSetReconnectTimeEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetReconnectTime, uParam );
}

void QVzAllInOne::PostIPCLoginEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogin, uParam );
}

void QVzAllInOne::PostIPCCaptureJPGEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCCaptureJPG, uParam );
}

void QVzAllInOne::PostIPCStartRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStartRealPlay, uParam );
}

void QVzAllInOne::PostIPCStopRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStopRealPlay, uParam );
}

void QVzAllInOne::PostIPCLogoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogout, uParam );
}

void QVzAllInOne::PostIPCCleanupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCCleanup );
}

QIPCThread* QVzAllInOne::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        QIPCThread* pThread = new QVzAllInOne( );

        pThread->InitializeThread( );
        pThread->start( );
        pThread->moveToThread( pThread );

        pThreadInstance = pThread;
    }

    return pThreadInstance;
}

void QVzAllInOne::InitializeThread( )
{
    bool bRet = connect( this, SIGNAL( started( ) ),
                         this, SLOT( HandleStarted( ) ) );
    bRet = connect( this, SIGNAL( finished( ) ),
                             this, SLOT( HandleFinished( ) ) );
}

void QVzAllInOne::HandleStarted( )
{
}

void QVzAllInOne::HandleFinished( )
{
}

void QVzAllInOne::run( )
{
    exec( );
}

void QVzAllInOne::CapturePreviewImage( HWND hPlayWnd, QString& strFileName )
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

void QVzAllInOne::CaptureDeviceImage( QString& strIP, QString& strFileName, HWND hPlayWnd )
{
    NullPointer( MyVzLPRClient_GetSnapShootToJpeg );
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

    int nRet = MyVzLPRClient_GetSnapShootToJpeg( hPlayWnd, pFile, 70 );

    if ( nRet ) {
        if ( !QFile::exists( strFileName ) ) {
            QFile file( strFileName );
            if ( file.open( QIODevice::ReadWrite ) ) {
                file.close( );
            }
        }
        return;
    }
}

void QVzAllInOne::ProcessIPCStartupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )

    if( bStarted ) {
        return;
    }

    bStarted = true;

    NullPointer( MyVzLPRClient_Setup );
    int nRet = MyVzLPRClient_Setup( );
    QString strFunName = "VzLPRClient_Setup";
    PrintExceptionCode( nRet, strFunName );
}

int QVzAllInOne::MyVZLPRC_PLATE_INFO_CALLBACK(VzLPRClientHandle handle, void *pUserData,
                                               const TH_PlateResult *pResult, unsigned uNumPlates,
                                               VZ_LPRC_RESULT_TYPE eResultType,
                                               const VZ_LPRC_IMAGE_INFO *pImgFull,
                                               const VZ_LPRC_IMAGE_INFO *pImgPlateClip )
{
    return 0;
    QVzAllInOne* pThread = ( QVzAllInOne* ) pUserData;
    pThread->EmitPlate( handle,
                        pResult, uNumPlates,
                        eResultType,
                        pImgFull,
                        pImgPlateClip );
    return 0;
}

QString QVzAllInOne::GetPlateMoveDirection( int nDirection )
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

void QVzAllInOne::EmitPlate( VzLPRClientHandle handle,
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

void QVzAllInOne::ProcessIPCSetConnectTimeoutEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QVzAllInOne::ProcessIPCSetReconnectTimeEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

void QVzAllInOne::SetUserID( char *pIP, LONG lUserID )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.insert( pIP, lUserID );
}

void QVzAllInOne::SetPlayHandle( HWND hPlayWnd, LONG lPlayHandle )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.insert( hPlayWnd, lPlayHandle );
}

LONG QVzAllInOne::GetUserID( char *pIP )
{
    LONG lUserID = -1;

    if ( NULL != pIP ) {
        lUserID = hashIP_UserHandle.value( pIP, -1 );
    }

    return lUserID;
}

void QVzAllInOne::RemoveUserID( char *pIP )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.remove( pIP );
}

LONG QVzAllInOne::GetPlayHandle( HWND hPlayWnd )
{
    LONG lPlayHandle = -1;

    if ( INVALID_HANDLE_VALUE != hPlayWnd ) {
        lPlayHandle = hashWnd_PlayHandle.value( hPlayWnd, -1 );
    }

    return lPlayHandle;
}

void QVzAllInOne::RemovePlayHandle( HWND hPlayWnd )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.remove( hPlayWnd );
}

void QVzAllInOne::ProcessIPCLoginEvent( QIPCEvent* pEvent )
{
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
}

void QVzAllInOne::ProcessIPCCaptureJPGEvent( QIPCEvent* pEvent )
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

void QVzAllInOne::ProcessIPCStartRealPlayEvent( QIPCEvent* pEvent )
{
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
}

void QVzAllInOne::ProcessIPCStopRealPlayEvent( QIPCEvent* pEvent )
{
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
}

void QVzAllInOne::ProcessIPCLogoutEvent( QIPCEvent* pEvent )
{
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
}

void QVzAllInOne::SetUserIDChannel( int nUserID, int nChannel )
{
    hashUserID_Channel.insert( nUserID, nChannel );
}

LONG QVzAllInOne::GetUserIDChannel( int nUserID )
{
    return hashUserID_Channel.value( nUserID, 1 );
}

void QVzAllInOne::RemoveUserIDChannel( int nUserID )
{
    hashUserID_Channel.remove( nUserID );
}

void QVzAllInOne::ClearHash( )
{
    hashUserID_Channel.clear( );
    hashIP_UserHandle.clear( );
    hashWnd_PlayHandle.clear( );
}

void QVzAllInOne::GetFunctionPointer( )
{
    MyVzLPRClient_Setup  = NULL;
    MyVzLPRClient_Cleanup = NULL;
    MyVzLPRClient_Open = NULL;
    MyVzLPRClient_Close = NULL;
    MyVzLPRClient_StartRealPlay = NULL;
    MyVzLPRClient_StopRealPlay = NULL;
    MyVzLPRClient_SetPlateInfoCallBack = NULL;
    MyVzLPRClient_GetSnapShootToJpeg = NULL;

    QString strPath = qApp->applicationDirPath( ) + "/" + VZ_IVS_SDK;
    WCHAR* pPath = ( WCHAR* ) strPath.utf16( );

    hDllMod = ::LoadLibrary( pPath );
    if ( NULL == hDllMod ) {
        return;
    }

    MyVzLPRClient_Setup = ( VzLPRClient_Setup ) ::GetProcAddress( hDllMod, "VzLPRClient_Setup" );
    MyVzLPRClient_Cleanup = ( VzLPRClient_Cleanup ) ::GetProcAddress( hDllMod, "VzLPRClient_Cleanup" );

    MyVzLPRClient_Open = ( VzLPRClient_Open ) ::GetProcAddress( hDllMod, "VzLPRClient_Open" );
    MyVzLPRClient_Close = ( VzLPRClient_Close ) ::GetProcAddress( hDllMod, "VzLPRClient_Close" );

    MyVzLPRClient_StartRealPlay = ( VzLPRClient_StartRealPlay ) ::GetProcAddress( hDllMod, "_VzLPRClient_StartRealPlay@8" );
    MyVzLPRClient_StopRealPlay = ( VzLPRClient_StopRealPlay ) ::GetProcAddress( hDllMod, "_VzLPRClient_StopRealPlay@4" );

    MyVzLPRClient_SetPlateInfoCallBack = ( VzLPRClient_SetPlateInfoCallBack ) ::GetProcAddress( hDllMod, "VzLPRClient_SetPlateInfoCallBack" );
    MyVzLPRClient_GetSnapShootToJpeg = ( VzLPRClient_GetSnapShootToJpeg ) ::GetProcAddress( hDllMod, "VzLPRClient_GetSnapShootToJpeg" );
}

void QVzAllInOne::PrintExceptionCode( int nRet, QString& strFunName )
{
    return;
}

void QVzAllInOne::ProcessIPCCleanupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )

    NullPointer( MyVzLPRClient_Cleanup );
    int nRet = MyVzLPRClient_Cleanup( );
    QString strFunName = "VzLPRClient_Cleanup";
    PrintExceptionCode( nRet, strFunName );

    ClearHash( );
    bStarted = false;
}

void QVzAllInOne::customEvent( QEvent* event )
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
