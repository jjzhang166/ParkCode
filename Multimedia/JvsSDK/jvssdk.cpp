#include "jvssdk.h"

#define JVS_CAPTURE_CARD    "jVSDK.DLL"

CJvsSDK::CJvsSDK()
{
    hDllMod = NULL;
    GetParameters( );
    GetFunctionPointer( );
}

CJvsSDK::~CJvsSDK( )
{
    if ( NULL != hDllMod ) {
        BOOL bRet = ::FreeLibrary( hDllMod );
        if ( !bRet ) {

        }
    }
}

int CJvsSDK::SystemStartup( HWND hOverlayWnd )
{
    int nRet = 0;

    if ( NULL != pJVSInitSDK ) {
        nRet = pJVSInitSDK( );
    }

    if ( 0 < nRet && NULL != pJVSInitPreview ) {
        nRet = pJVSInitPreview( );
    }

    //if ( NULL != pJVSRegisterNotify ) {
    //    pJVSRegisterNotify( hOverlayWnd, WM_SDK_NOTIFY );
    //}

    return nRet;
}

int CJvsSDK::SystemShutdown( )
{
    if ( NULL != pJVSReleasePreview ) {
        pJVSReleasePreview( );
    }

    if ( NULL != pJVSReleaseSDK ) {
        pJVSReleaseSDK( );
    }

    return 0;
}

HANDLE CJvsSDK::OpenChannel( int nChannelNum )
{
    if ( NULL != pJVSOpenChannel ) {
        pJVSOpenChannel( nChannelNum );
    }

    if ( NULL != pJVSSetVideoPixelMode ) {
        pJVSSetVideoPixelMode( nChannelNum, 5, 0 );
    }

    return ( HANDLE ) nChannelNum;
}

int CJvsSDK::CloseChannel( HANDLE hChannel )
{
    if ( NULL != pJVSClosenChannel ) {
        pJVSClosenChannel( ( int ) hChannel );
    }

    return 0;
}

int CJvsSDK::PlayVideo( HANDLE hChannel, HWND hWnd, QRect &rect, int nIndex )
{
    if( !wndHash.contains( hChannel ) ) {
        wndHash.insert( hChannel, hWnd );
    }

    RECT rt;
    rt.left = rect.left( );
    rt.top = rect.top( );
    rt.right = rect.right( );
    rt.bottom = rect.bottom( );

    ::GetWindowRect( hWnd, &rt );
    if ( NULL != pJVSSetVideoPreview ) {
        pJVSSetVideoPreview( ( int ) hChannel, hWnd, &rt, TRUE );
    }

    return 0;
}

int CJvsSDK::StopVideo( HANDLE hChannel )
{
    if ( wndHash.contains( hChannel ) && NULL != pJVSSetVideoPreview ) {
        pJVSSetVideoPreview( ( int ) hChannel, wndHash.value( hChannel ), NULL, FALSE );
    }

    return 0;
}

int CJvsSDK::CaptureBMP( HANDLE hChannel, QString& strFile )
{
    BOOL bRet = FALSE;
    quint8* pFile = NULL;
    QByteArray byData;

    if ( pJVSGetBitmapToFile ) {
        byData = CCommonFunction::GetTextCodec( )->fromUnicode( strFile );
        pFile = ( quint8* ) byData.data( );
        //pFile = ( quint8* ) "d:/1353401688.bmp";
        bRet = pJVSGetBitmapToFile( ( int ) hChannel, pFile );
    }

    return 0;
}

int CJvsSDK::CaptureJpeg( HANDLE hChannel, QString& strFile )
{
    return 0;
}

int CJvsSDK::GetYuv422Data( HANDLE hChannel, quint8* pData, ULONG& lSize )
{
    return 0;
}

int CJvsSDK::RegisterStreamCB( HK_STREAM_CB pCBF, PVOID pContext )
{
    return 0;
}

int CJvsSDK::GetStreamData( HANDLE hChannel, BOOL bStart, quint8 *pData, int nIndex )
{
    return 0;
}

int CJvsSDK::MotionDetection( HANDLE hChannel, bool bStart )
{
    return 0;

    if ( NULL != pJVSSetMovDetect ) {
        pJVSSetMovDetect( ( int ) hChannel, bStart ? 80 : 0, 50, 30, 0, NULL );
    }

    return 0;
}

int CJvsSDK::SetupDetection( HANDLE hChannel, HK_MOTION_CB pCBF, int nIndex, LPVOID pContext )
{
    return 0;

    if ( NULL != pJVSSetCallBack ) {
        pJVSSetCallBack( ( CALLBACK_ENC_DATA ) pCBF, ( CALLBACK_RAW_DATA ) pContext );
    }

    //(int nChannel, int nScenecutGrade, int nScenecutThreshold, int nScenecutCoeff, int nRectNumber, RECT * pScenecutRect);
    if ( NULL != pJVSSetMovDetect ) {
        pJVSSetMovDetect( ( int ) hChannel, 80,  30, 50, 0, NULL );
    }

    return 0;
}

void CJvsSDK::GetParameters( )
{

}

void CJvsSDK::GetFunctionPointer( )
{
    pJVSInitSDK = NULL;
    pJVSReleaseSDK = NULL;

    pJVSOpenChannel = NULL;
    pJVSInitPreview = NULL;
    pJVSSetVideoPreview = NULL;
    pJVSClosenChannel = NULL;
    pJVSReleasePreview = NULL;
    pJVSSetVideoPixelMode = NULL;

    pJVSGetBitmapSize = NULL;
    pJVSGetBitmap = NULL;
    pJVSSetQualityMode = NULL;
    pJVSRegisterNotify = NULL;
    pJVSGetBitmapToFile = NULL;

    pJVSSetMovDetect = NULL;
    pJVSSetCallBack = NULL;

    QString strPath;
    //CCommonFunction::GetPath( strPath, CommonDataType::PathExe );
    strPath += JVS_CAPTURE_CARD;
    WCHAR* pPath = ( WCHAR* ) strPath.utf16( );

    hDllMod = ::LoadLibrary( pPath );
    if ( NULL == hDllMod ) {
        return;
    }

    pJVSInitSDK = ( JVSInitSDK ) ::GetProcAddress( hDllMod, "JVS_InitSDK" );
    pJVSReleaseSDK = ( JVSReleaseSDK ) ::GetProcAddress( hDllMod, "JVS_ReleaseSDK" );

    pJVSOpenChannel = ( JVSOpenChannel ) ::GetProcAddress( hDllMod, "JVS_OpenChannel" );
    pJVSInitPreview = ( JVSInitPreview ) ::GetProcAddress( hDllMod, "JVS_InitPreview" );
    pJVSSetVideoPreview = ( JVSSetVideoPreview ) ::GetProcAddress( hDllMod, "JVS_SetVideoPreview" );
    pJVSClosenChannel = ( JVSClosenChannel ) ::GetProcAddress( hDllMod, "JVS_ClosenChannel" );
    pJVSReleasePreview = ( JVSReleasePreview ) ::GetProcAddress( hDllMod, "JVS_ReleasePreview" );
    pJVSSetVideoPixelMode = ( JVSSetVideoPixelMode ) ::GetProcAddress( hDllMod, "JVS_SetVideoPixelMode" );

    pJVSGetBitmapSize = ( JVSGetBitmapSize ) ::GetProcAddress( hDllMod, "JVS_GetBitmapSize" );
    pJVSGetBitmap = ( JVSGetBitmap ) ::GetProcAddress( hDllMod, "JVS_GetBitmap" );
    pJVSSetQualityMode = ( JVSSetQualityMode ) ::GetProcAddress( hDllMod, "JVS_SetQualityMode" );
    pJVSRegisterNotify = ( JVSRegisterNotify )  ::GetProcAddress( hDllMod, "JVS_RegisterNotify" );
    pJVSGetBitmapToFile = ( JVSGetBitmapToFile ) ::GetProcAddress( hDllMod, "JVS_GetBitmapToFile" );

    pJVSSetMovDetect = ( JVSSetMovDetect ) ::GetProcAddress( hDllMod, "JVS_SetMovDetect" );
    pJVSSetCallBack = ( JVSSetCallBack ) ::GetProcAddress( hDllMod, "JVS_SetCallBack" );
}
