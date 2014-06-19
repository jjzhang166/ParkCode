#include "tm.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QTextCodec>

//#define TM_CAPTURE_CARD "sdk3000_7130.dll"
#define TM_CAPTURE_CARD "Sa7134Capture.dll"

CTm::CTm()
{
    hDllMod = NULL;
    GetParameters( );
    GetFunctionPointer( );
}

CTm::~CTm( )
{
    if ( NULL != hDllMod ) {
        BOOL bRet = ::FreeLibrary( hDllMod );
        if ( !bRet ) {

        }
    }
}

void CTm::GetFunctionPointer( )
{
    QString strPath;
    CCommonFunction::GetPath( strPath, CommonDataType::PathExe );
    strPath += TM_CAPTURE_CARD;
    WCHAR* pPath = ( WCHAR* ) strPath.utf16( );

    hDllMod = ::LoadLibrary( pPath );
    if ( NULL == hDllMod ) {
        return;
    }

    MyVCAInitSdk = ( VCAInitSdk ) ::GetProcAddress( hDllMod, "VCAInitSdk" );
    MyVCAUnInitSdk = ( VCAUnInitSdk ) ::GetProcAddress( hDllMod, "VCAUnInitSdk" );
    MyVCAGetDevNum = ( VCAGetDevNum ) ::GetProcAddress( hDllMod, "VCAGetDevNum" );
    MyVCAEnableMotionDetect = ( VCAEnableMotionDetect ) GetProcAddress( hDllMod, "VCAEnableMotionDetect" );
#if false
    MyVCAConnectDevice = ( VCAConnectDevice ) ::GetProcAddress( hDllMod, "VCAConnectDevice" );
    MyVCADisConnectDevice = ( VCADisConnectDevice ) ::GetProcAddress( hDllMod, "VCADisConnectDevice" );
    MyVCARun = ( VCARun ) ::GetProcAddress( hDllMod, "VCARun" );
    MyVCAPause = ( VCAPause ) ::GetProcAddress( hDllMod, "VCAPause" );
    MyVCAStop = ( VCAStop ) ::GetProcAddress( hDllMod, "VCAStop" );

    MyVCACapturePicture = ( VCACapturePicture ) GetProcAddress( hDllMod, "VCACapturePicture" );
    MyVCAEnableCapSourceStream = ( VCAEnableCapSourceStream ) GetProcAddress( hDllMod, "VCAEnableCapSourceStream" );
    MyVCAEnablePicMessage = ( VCAEnablePicMessage ) GetProcAddress( hDllMod, "VCAEnablePicMessage" );
    MyVCAGetVideoInfo = ( VCAGetVideoInfo ) GetProcAddress( hDllMod, "VCAGetVideoInfo" );
    MyVCASetVideoInfo = ( VCASetVideoInfo ) GetProcAddress( hDllMod, "VCASetVideoInfo" );
    MyVCAIsOverlay = ( VCAIsOverlay ) GetProcAddress( hDllMod, "VCAIsOverlay" );
    MyVCASetWindowPos = ( VCASetWindowPos ) GetProcAddress( hDllMod, "VCASetWindowPos" );

#endif
    // VC4000
    MyVCAOpenDevice = ( VCAOpenDevice ) GetProcAddress( hDllMod, "VCAOpenDevice" );
    MyVCACloseDevice = ( VCACloseDevice ) GetProcAddress( hDllMod, "VCACloseDevice" );
    MyVCAStartVideoPreview = ( VCAStartVideoPreview ) GetProcAddress( hDllMod, "VCAStartVideoPreview" );
    MyVCAStopVideoPreview = ( VCAStopVideoPreview ) GetProcAddress( hDllMod, "VCAStopVideoPreview" );
    MyVCASaveAsBmpFile = ( VCASaveAsBmpFile ) GetProcAddress( hDllMod, "VCASaveAsBmpFile" );
    MyVCASaveAsJpegFile = ( VCASaveAsJpegFile ) GetProcAddress( hDllMod, "VCASaveAsJpegFile" );
    MyVCARegVidCapCallBack = ( VCARegVidCapCallBack ) GetProcAddress( hDllMod, "VCARegVidCapCallBack" );
    MyVCASetVidCapColorFormat = ( VCASetVidCapColorFormat ) GetProcAddress( hDllMod, "VCASetVidCapColorFormat" );
    MyVCAStartVideoCapture = ( VCAStartVideoCapture ) GetProcAddress( hDllMod, "VCAStartVideoCapture" );
    MyVCASetVidCapSize = ( VCASetVidCapSize ) GetProcAddress( hDllMod, "VCASetVidCapSize" );
    MyVCAStartVideoCaptureEx = ( VCAStartVideoCaptureEx ) GetProcAddress( hDllMod, "VCAStartVideoCaptureEx" );
    MyVCAStopVideoCaptureEx = ( VCAStopVideoCaptureEx ) GetProcAddress( hDllMod, "VCAStopVideoCaptureEx" );
}

int CTm::SystemStartup( HWND hOverlayWnd )
{
    int nRet = 0;
    nRet = MyVCAInitSdk( hOverlayWnd, PCI_OFFSCREEN_VIDEOMEMORY, FALSE );
    //nRet = MyVCAInitSdk( );
    int nDeviceNum = 0;
    nDeviceNum = MyVCAGetDevNum(  );

    return nDeviceNum;
}

int CTm::TmEnablePicMessage( int nCards, BOOL bPicMessage, MyPrcPicMessage pPicMessage )
{
    int nRet = 0;
    //nRet = MyVCAEnablePicMessage( nCards, bPicMessage, pPicMessage );

    return nRet;
}

int CTm::SystemShutdown( )
{
    int nRet = 0;
    nRet = MyVCAUnInitSdk( );

    return nRet;
}

HANDLE CTm::OpenChannel( int nChannelNum )
{
    return ( HANDLE ) nChannelNum;
}

int CTm::CloseChannel( HANDLE hChannel )
{
    int nRet = 0;
    return nRet;
}

int CTm::PlayVideo( HANDLE hChannel, HWND hWnd, QRect &rect, int nIndex )
{
    int nRet = 0;
    SIZE cliSize;
    int nCard = ( int ) hChannel;
    cliSize.cx = VIDEO_WIDTH;//rect.width( );
    cliSize.cy = VIDEO_HEIGHT;//rect.height( );

    //HDC hWndDc = GetWindowDC( hWnd );
    //SetBkColor( hWndDc, RGB( 255, 0, 255 ) );
    //ReleaseDC( hWnd, hWndDc );

    // Card 0 1 2 3 4
    nRet = MyVCASetVidCapColorFormat( nCard, RGB888 );
    nRet = MyVCARegVidCapCallBack( nCard, capVideoStream );
    nRet = MyVCAOpenDevice( nCard, hWnd );
    //nRet = MyVCASetVidCapSize( nCard, 352, 288 );

    nRet = MyVCAStartVideoPreview( nCard );
    //nRet = MyVCAStartVideoCaptureEx( nCard );
#if false
    RECT rec;
    rec.bottom = rect.bottom( );
    rec.top = rect.top( );
    rec.left = rect.left( );
    rec.right = rect.right( );
    nRet = MyVCAConnectDevice( nCard, TRUE, hWnd, cliSize, VIDEO_IN_1, nFps[ nIndex ], VideoSubType_YUY2 );
    //nRet = MyVCASetWindowPos( nCard, rec );
    nRet = MyVCARun( nCard );
#endif

    return nRet;
}

int CTm::StopVideo( HANDLE hChannel )
{
    int nRet = 0;
    int nCard = ( int ) hChannel;
    nRet = MyVCAStopVideoPreview( nCard );
    nRet = MyVCACloseDevice( nCard );
    //nRet = MyVCAStop( nCard );
    //nRet = MyVCADisConnectDevice( nCard );
    return nRet;
}

int CTm::CaptureBMP( HANDLE hChannel, QString& strFile )
{
    int nRet = 0;
    QByteArray byData = pCodec->fromUnicode( strFile );
    char* pFile = byData.data( );
    nRet = MyVCASaveAsBmpFile( ( int ) hChannel, pFile );
    //nRet = MyVCACapturePicture( ( int ) hChannel, pFile, IMAGE_BMP, NULL, 90, 1, FALSE );

    return nRet;
}

int CTm::CaptureJpeg( HANDLE hChannel, QString& strFile )
{
    int nRet = 0;
    QByteArray byData = pCodec->fromUnicode( strFile );
    char* pFile = byData.data( );
    nRet = MyVCASaveAsJpegFile( ( int ) hChannel, pFile, 80 );
    //nRet = MyVCACapturePicture( ( int ) hChannel, pFile, IMAGE_JPG, NULL, 80, 1, FALSE );
    return nRet;
}

int CTm::GetYuv422Data( HANDLE hChannel, quint8* pData, ULONG& lSize )
{
    int nRet = 0;
    pData = NULL;
    lSize = 0;
    hChannel = 0;
    return nRet;
}

int CTm::RegisterStreamCB( HK_STREAM_CB pCBF, PVOID pContext )
{
    int nRet = 0;
    pContext = NULL;
    capVideoStream = ( PrcVidCapCallBack ) pCBF;
    //capVideoStream = ( PrcCapSourceStream ) pCBF;
    return nRet;
}

int CTm::GetStreamData( HANDLE hChannel, BOOL bStart, quint8 *pData, int nIndex )
{
    int nRet = 0;
    pData = NULL;
    int nCard = ( int ) hChannel;
    //nRet = MyVCARegVidCapCallBack( nCard, capVideoStream );
    //nRet = MyVCAStartVideoCapture( nCard, CAP_ORIGIN_STREAM, MPEG4_AVIFILE_CALLBACK, "" );
    nRet = MyVCAStartVideoCaptureEx( nCard );
    //nRet = MyVCAEnableCapSourceStream( nCard, bStart, ( VideoFieldType ) nIndex, capVideoStream );
    return nRet;
}

int CTm::MotionDetection( HANDLE hChannel, bool bStart )
{
    int nRet = 0;
    hChannel = 0;
    bStart = false;
    return nRet;
}

int CTm::SetupDetection( HANDLE hChannel, HK_MOTION_CB pCBF, int Index , LPVOID pContext )
{
    int nRet = 0;
    pDetectionContext = pContext;
    Index = 0;
    int nRows = VIDEO_HEIGHT / 16;
    int nCols = VIDEO_WIDTH / 16;
    memset( rectBlock, nGrade[ Index ], nRows * nCols );
    //( DWORD dwCard, BOOL bMove, BYTE *pbuff, DWORD dwSize, LPVOID lpContext );
    //nRet = MyVCAEnableMotionDetect( ( int ) hChannel, TRUE, rectBlock, sizeof ( rectBlock ) / sizeof ( BYTE ),
    //                                nDelay[ Index ], 2,  pContext, ( PrcCbMotionDetect ) pCBF );
    //DWORD dwError = MyVCAGetLastError( );
    return nRet;
}

void CTm::GetParameters( )
{
    QString strKey = QString( "WintonePlate/WintonePlate%1/%2" );

    for ( int nIndex = 0; nIndex < VIDEO_WAY; nIndex++ ) {
        nGrade[ nIndex ] = pSettings->value( strKey.arg( QString::number( nIndex ), "PlateGrade" ), 2 ).toInt( );
        nDelay[ nIndex ] = pSettings->value( strKey.arg( QString::number( nIndex ), "PlateDetectionDelay" ), 5 ).toInt( );
        nFps[ nIndex ] = pSettings->value( strKey.arg( QString::number( nIndex ), "PlateFrameRate" ), 25 ).toInt( );

        rDetectionRange[ nIndex ].left = pSettings->value( strKey.arg( QString::number( nIndex ), "PlateDetectionLeft" ), 0 ).toInt( );
        rDetectionRange[ nIndex ].right = pSettings->value( strKey.arg( QString::number( nIndex ), "PlateDetectionRight" ), 703 ).toInt( );
        rDetectionRange[ nIndex ].top = pSettings->value( strKey.arg( QString::number( nIndex ), "PlateDetectionUp" ), 0 ).toInt( );
        rDetectionRange[ nIndex ].bottom = pSettings->value( strKey.arg( QString::number( nIndex ), "PlateDetectionDown" ), 575 ).toInt( );
    }
}
