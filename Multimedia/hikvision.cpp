#include "HikSDK\hikvision.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QTextCodec>

CHikVision::CHikVision()
{

}

CHikVision::~CHikVision( )
{

}

int CHikVision::SystemStartup( )
{
    int nEncodeChannel = InitDSPs( );
    qDebug( ) << "Encode Channel Number :" << nEncodeChannel << endl;

    return nEncodeChannel;
}

int CHikVision::SystemShutdown( )
{
    return DeInitDSPs( );
}

HANDLE CHikVision::OpenChannel( int nChannelNum )
{
    return ChannelOpen( nChannelNum );
}

int CHikVision::CloseChannel( HANDLE hChannel )
{
    return ChannelClose( hChannel );
}

int CHikVision::CaptureBMP( HANDLE hChannel, QString &strFile )
{
    int nRet = -1;
    ULONG lSize = 1024 * 1024 * 2;
    PUCHAR pImgBuff = new UCHAR[ lSize ];
    nRet = GetOriginalImage( hChannel, pImgBuff, &lSize );
    if( 0 != nRet ) {
        delete [ ] pImgBuff;
        return nRet;
    }

    int nWidth = 0;
    int nHeight = 0;

    // 16 BMP
    switch ( lSize ) {
    case 704 * 576 * 2 : // 405504
        nWidth = 704;
        nHeight = 576;
        break;

    case 704 * 480 * 2 : // 337920
        nWidth = 704;
        nHeight = 480;
        break;

    case 352 * 288 * 2 : // 101376
        nWidth = 352;
        nHeight = 288;
        break;

    case 352 * 240 * 2 : // 84480
        nWidth = 352;
        nHeight = 240;
        break;

    case 352 * 144 * 2 : // 50688
        nWidth = 352;
        nHeight = 144;
        break;

    case 352 * 120 * 2 : // 42240
        nWidth = 352;
        nHeight = 120;
        break;

    //case 176 * 288 * 2 : // 50688
    //    nWidth = 176;
    //   nHeight = 288;
    //    break;

    //case 176 * 240 * 2 : // 42240
    //    nWidth = 176;
    //    nHeight = 240;
    //    break;

    case 176 * 144 * 2 : // 25344
        nWidth = 176;
        nHeight = 144;
        break;

    case 176 * 120 * 2 : // 21120
        nWidth = 176;
        nHeight = 120;
        break;
    }

    QByteArray byData = strFile.toAscii( );
    char* pFile = byData.data( );

    nRet = SaveYUVToBmpFile( pFile, pImgBuff, nWidth, nHeight );
    delete [ ] pImgBuff;

    return nRet;
}

int CHikVision::CaptureJpeg( HANDLE hChannel, QString& strFile )
{
    int nRet = 0;
    ULONG lSize = 1024 * 1024 * 3;
    PUCHAR pImgBuff = new UCHAR[ lSize ];
    nRet = GetJpegImage( hChannel, pImgBuff, &lSize, 100 );
    if ( 0 != nRet ) {
        delete [ ] pImgBuff;
        return nRet;
    }
    // DS-40xxHC/HC+/HF/HCS JPEG4CIF(QCIF)
    // 4CIF 704¡Á576 QCIF 176¡Á144 CIF 352¡Á288
    // Save File

    QFile imgFile( strFile );
    if ( imgFile.open( QIODevice::WriteOnly ) ) {
        const char* pData = ( const char* ) pImgBuff;
        imgFile.write( pData, lSize );
        imgFile.close( );
    }

    delete [ ] pImgBuff;
    return nRet;
}

int CHikVision::PlayVideo(HANDLE hChannel, HWND hWnd, QRect &rect, int nFrameRate)
{
    RECT winRect;
    POINT point;
    point.x = rect.left( );
    point.y = rect.top( );

    //BOOL bRet = ClientToScreen( hWnd, &point );

    winRect.left   = point.x;
    winRect.top    = point.y;
    winRect.right  = point.x + rect.right( );
    winRect.bottom = point.y + rect.bottom( );

    qDebug( ) << "left = "
              << winRect.left
              << "top = "
              << winRect.top
              << "right = "
              << winRect.right
              << "bottom = "
              << winRect.bottom
              << endl;

    //int nRet = SetPreviewOverlayMode( TRUE );
    int nRet = StartVideoPreview( hChannel, hWnd, &winRect, true, 0, nFrameRate );
    return nRet;
}

int CHikVision::StopVideo( HANDLE hChannel )
{
    return StopVideoPreview( hChannel );
}
