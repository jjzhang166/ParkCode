#ifndef TM_H
#define TM_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <QRect>
#include "Sa7134Capture.h"
//#include "sdk3000_7130.h"
#include "../multimedia.h"
#include <QFrame>

#define VIDEO_WIDTH   ( int ) ( 720 )
#define VIDEO_HEIGHT  ( int ) ( 576 )

class CTm : public CMultimedia
{
    //Q_OBJECT
public:
    CTm( );
    virtual ~CTm( );

public:
    typedef HRESULT WINAPI ( *VCAInitSdk ) ( HWND hWndMain, DISPLAYTRANSTYPE eDispTransType, BOOL bInitAudDev );
    //typedef HRESULT WINAPI ( *VCAInitSdk ) (  );
    typedef HRESULT WINAPI ( *VCAUnInitSdk ) (  );

    //typedef HRESULT WINAPI ( *VCAGetDevNum ) ( int *pDevNum );
    typedef HRESULT WINAPI ( *VCAGetDevNum ) ( );
    typedef HRESULT WINAPI ( *VCAEnableMotionDetect ) ( int nCards, BOOL bEnaDetect, BYTE *pAreaMap,
                                                        LONG nSizeOfMap, LONG nPersistTime, INT nFrameRateReduce,
                                                        LPVOID lpContext,
                                                        PrcCbMotionDetect OnObjectMove );

#if false
    typedef HRESULT WINAPI ( *VCAConnectDevice ) ( int, BOOL, HWND, SIZE&, VIDEOSOURCE, int, VideoSubType );
    typedef HRESULT WINAPI ( *VCADisConnectDevice )( int );

    typedef HRESULT WINAPI ( *VCARun ) ( int nCards );
    typedef HRESULT WINAPI ( *VCAPause ) ( int nCards );
    typedef HRESULT WINAPI ( *VCAStop ) ( int nCards );



    typedef HRESULT WINAPI ( *VCACapturePicture ) ( int nCards, LPCSTR szFileName, enImageType enImgType,
                                                    RECT* rcImg, long nQuality, long nCapCount, BOOL bCapFast  );
    typedef HRESULT WINAPI ( *VCAEnableCapSourceStream ) ( int nCards, BOOL bCapStream,
                                                           VideoFieldType enVideoFieldType, PrcCapSourceStream pCapStream );
    typedef HRESULT WINAPI ( *VCAEnablePicMessage ) ( int nCards, BOOL bPicMessage, PrcPicMessage pPicMessage );

    //得到视频信息
    typedef HRESULT WINAPI ( *VCAGetVideoInfo ) ( int nCards, VIDEOSTREAMINFO* pVSI );
    //设置视频信息
    typedef HRESULT WINAPI ( *VCASetVideoInfo ) ( int nCards, VIDEOSTREAMINFO* pVSI );
    typedef HRESULT WINAPI ( *VCAIsOverlay )( int nCards, BOOL* bIsOverlay );
    typedef HRESULT WINAPI ( *VCASetWindowPos ) ( int nCards, RECT rc );
#endif

    // VC4000
    typedef BOOL  WINAPI ( *VCAOpenDevice ) ( DWORD dwCard, HWND hPreviewWnd );
    typedef BOOL  WINAPI ( *VCACloseDevice ) ( DWORD dwCard );
    typedef BOOL  WINAPI ( *VCAStartVideoPreview ) ( DWORD dwCard );
    typedef BOOL  WINAPI ( *VCAStopVideoPreview ) ( DWORD dwCard );
    typedef BOOL  WINAPI ( *VCASaveAsBmpFile ) ( DWORD dwCard, LPCSTR lpFileName );
    typedef BOOL  WINAPI ( *VCASaveAsJpegFile ) ( DWORD dwCard, LPCSTR lpFileName, DWORD dwQuality );
    typedef BOOL  WINAPI ( *VCARegVidCapCallBack ) ( DWORD dwCard, PrcVidCapCallBack ppCall );
    typedef BOOL  WINAPI ( *VCASetVidCapColorFormat ) ( DWORD dwCard, COLOR_FORMAT cfColor );
    typedef BOOL  WINAPI ( *VCAStartVideoCapture ) ( DWORD dwCard, CAPMODEL enCapMode, MP4MODEL enMp4Mode, LPCSTR lpFileName );
    typedef BOOL  WINAPI ( *VCASetVidCapSize ) ( DWORD dwCard, DWORD dwWidth, DWORD dwHeight );
    typedef BOOL  WINAPI ( *VCAStartVideoCaptureEx ) ( DWORD dwCard );
    typedef BOOL  WINAPI ( *VCAStopVideoCaptureEx ) ( DWORD dwCard );


public:
    int SystemStartup( HWND hOverlayWnd = NULL );
    int SystemShutdown( );
    HANDLE OpenChannel( int nChannelNum );
    int CloseChannel( HANDLE hChannel );
    int PlayVideo( HANDLE hChannel, HWND hWnd, QRect &rect, int nIndex );
    int StopVideo( HANDLE hChannel );
    int CaptureBMP( HANDLE hChannel, QString& strFile );
    int CaptureJpeg( HANDLE hChannel, QString& strFile );
    int GetYuv422Data( HANDLE hChannel, quint8* pData, ULONG& lSize );
    int RegisterStreamCB( HK_STREAM_CB pCBF, PVOID pContext );
    int GetStreamData( HANDLE hChannel, BOOL bStart, quint8 *pData, int nIndex );
    int MotionDetection( HANDLE hChannel, bool bStart );
    int SetupDetection( HANDLE hChannel, HK_MOTION_CB pCBF, int Index = 0, LPVOID pContext = NULL );
    int TmEnablePicMessage( int nCards, BOOL bPicMessage, MyPrcPicMessage pPicMessage );

protected:
    void GetParameters( );
    void GetFunctionPointer( );

private:
    HMODULE hDllMod;
    LPVOID pDetectionContext;
    BYTE rectBlock[ ( VIDEO_WIDTH / 16 ) * ( VIDEO_HEIGHT / 16 ) ];

    VCAInitSdk MyVCAInitSdk;
    VCAUnInitSdk MyVCAUnInitSdk;
    VCAGetDevNum MyVCAGetDevNum;
#if false
    VCAConnectDevice MyVCAConnectDevice;
    VCADisConnectDevice MyVCADisConnectDevice;
    VCARun MyVCARun;
    VCAPause MyVCAPause;
    VCAStop MyVCAStop;

    VCACapturePicture MyVCACapturePicture;
    VCAEnableCapSourceStream MyVCAEnableCapSourceStream;
    VCAEnablePicMessage MyVCAEnablePicMessage;
    VCAGetVideoInfo MyVCAGetVideoInfo;
    VCASetVideoInfo MyVCASetVideoInfo;
    VCAIsOverlay MyVCAIsOverlay;
    VCASetWindowPos MyVCASetWindowPos;
#endif

    // VC4000
    VCAOpenDevice MyVCAOpenDevice;
    VCACloseDevice MyVCACloseDevice;
    VCAStartVideoPreview MyVCAStartVideoPreview;
    VCAStopVideoPreview MyVCAStopVideoPreview;
    VCASaveAsBmpFile MyVCASaveAsBmpFile;
    VCASaveAsJpegFile MyVCASaveAsJpegFile;
    VCARegVidCapCallBack MyVCARegVidCapCallBack;
    VCASetVidCapColorFormat MyVCASetVidCapColorFormat;
    VCAStartVideoCapture MyVCAStartVideoCapture;
    VCASetVidCapSize MyVCASetVidCapSize;
    VCAEnableMotionDetect MyVCAEnableMotionDetect;
    VCAStartVideoCaptureEx MyVCAStartVideoCaptureEx;
    VCAStopVideoCaptureEx MyVCAStopVideoCaptureEx;

    //typedef void (CALLBACK *PrcVidCapCallBack)( DWORD dwCard, BYTE *pbuff, DWORD dwSize );
    PrcVidCapCallBack capVideoStream;//PrcCapSourceStream
};

#endif // TM_H
