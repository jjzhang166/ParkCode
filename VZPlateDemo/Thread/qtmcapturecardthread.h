#ifndef QTMCAPTURECARDTHREAD_H
#define QTMCAPTURECARDTHREAD_H

#include "QAnalogCameraThread.h"
#include "Sa7134Capture.h"

class QTmCaptureCardThread : public QAnalogCameraThread
{
    Q_OBJECT
public:
    static QAnalogCameraThread* GetInstance( );
    ~QTmCaptureCardThread( );

    void CaptureStaticImage( QString &strFile, int nChannel );

    static void CALLBACK VidCapCallBack( DWORD dwCard, BYTE *pbuff, DWORD dwSize );

private:
    explicit QTmCaptureCardThread(QObject *parent = 0);

    static void CALLBACK MotionDelectCB( DWORD dwCard, BOOL bMove, BYTE *pbuff, DWORD dwSize, LPVOID lpContext );

    typedef HRESULT ( WINAPI *VCAInitSdk ) ( HWND hWndMain, DISPLAYTRANSTYPE eDispTransType, BOOL bInitAudDev );
    typedef HRESULT ( WINAPI *VCAUnInitSdk ) ( );
    typedef HRESULT ( WINAPI *VCAGetDevNum ) ( );

    // VC4000
    typedef HRESULT ( WINAPI *VCAEnableMotionDetect ) ( int nCards, BOOL bEnaDetect, BYTE *pAreaMap,
                                                        LONG nSizeOfMap, LONG nPersistTime, INT nFrameRateReduce,
                                                        LPVOID lpContext,
                                                        PrcCbMotionDetect OnObjectMove );
    typedef BOOL  ( WINAPI *VCAOpenDevice ) ( DWORD dwCard, HWND hPreviewWnd );
    typedef BOOL  ( WINAPI *VCACloseDevice ) ( DWORD dwCard );
    typedef BOOL  ( WINAPI *VCAStartVideoPreview ) ( DWORD dwCard );
    typedef BOOL  ( WINAPI *VCAStopVideoPreview ) ( DWORD dwCard );
    typedef BOOL  ( WINAPI *VCASaveAsBmpFile ) ( DWORD dwCard, LPCSTR lpFileName );
    typedef BOOL  ( WINAPI *VCASaveAsJpegFile ) ( DWORD dwCard, LPCSTR lpFileName, DWORD dwQuality );
    typedef BOOL  ( WINAPI *VCARegVidCapCallBack ) ( DWORD dwCard, PrcVidCapCallBack ppCall );
    typedef BOOL  ( WINAPI *VCASetVidCapColorFormat ) ( DWORD dwCard, COLOR_FORMAT cfColor );
    typedef BOOL  ( WINAPI *VCAStartVideoCapture ) ( DWORD dwCard, CAPMODEL enCapMode, MP4MODEL enMp4Mode, LPCSTR lpFileName );
    typedef BOOL  ( WINAPI *VCAStopVideoCapture ) ( DWORD dwCard );
    typedef BOOL  ( WINAPI *VCAStartVideoCaptureEx ) ( DWORD dwCard );
    typedef BOOL  ( WINAPI *VCAStopVideoCaptureEx ) ( DWORD dwCard );
    typedef BOOL  ( WINAPI *VCASetVidCapSize ) ( DWORD dwCard, DWORD dwWidth, DWORD dwHeight );
    typedef BOOL  ( WINAPI *VCASetVidPreviewSize ) ( DWORD dwCard, DWORD dwWidth, DWORD dwHeight );
    void GetFunctionPointer( );

    HMODULE hDllMod;
    LPVOID pDetectionContext;
    //BYTE rectBlock[ ( VIDEO_WIDTH / 16 ) * ( VIDEO_HEIGHT / 16 ) ];

    VCAInitSdk MyVCAInitSdk;
    VCAUnInitSdk MyVCAUnInitSdk;
    VCAGetDevNum MyVCAGetDevNum;

    // VC4000
    VCAEnableMotionDetect MyVCAEnableMotionDetect;
    VCAOpenDevice MyVCAOpenDevice;
    VCACloseDevice MyVCACloseDevice;
    VCAStartVideoPreview MyVCAStartVideoPreview;
    VCAStopVideoPreview MyVCAStopVideoPreview;
    VCASaveAsBmpFile MyVCASaveAsBmpFile;
    VCASaveAsJpegFile MyVCASaveAsJpegFile;
    VCARegVidCapCallBack MyVCARegVidCapCallBack;
    VCASetVidCapColorFormat MyVCASetVidCapColorFormat;
    VCAStartVideoCapture MyVCAStartVideoCapture;
    VCAStopVideoCapture MyVCAStopVideoCapture;

    VCAStartVideoCaptureEx MyVCAStartVideoCaptureEx;
    VCAStopVideoCaptureEx MyVCAStopVideoCaptureEx;

    VCASetVidCapSize MyVCASetVidCapSize;
    VCASetVidPreviewSize MyVCASetVidPreviewSize;

protected:
    void run( );
    void customEvent( QEvent *e );

private:
    void ProcessInitEvent( QCameraEvent* pEvent );
    void ProcessUninitEvent( QCameraEvent* pEvent );

    void ProcessOpenChannelEvent( QCameraEvent* pEvent );
    void ProcessCloseChannelEvent( QCameraEvent* pEvent );

    void ProcessStartCaptureEvent( QCameraEvent* pEvent );
    void ProcessStopCaptureEvent( QCameraEvent* pEvent );

    void ProcessStartPreviewEvent( QCameraEvent* pEvent );
    void ProcessStopPreviewEvent( QCameraEvent* pEvent );

    void ProcessStartMotionDetectEvent( QCameraEvent* pEvent );
    void ProcessStopMotionDetectEvent( QCameraEvent* pEvent );

    void ProcessStartSourceStreamEvent( QCameraEvent* pEvent );
    void ProcessStopSourceStreamEvent( QCameraEvent* pEvent );

    void ProcessCaptureImageEvent( QCameraEvent* pEvent );

    static QAnalogCameraThread* pThreadInstance;
    
signals:
    
public slots:
    
};

#endif // QTMCAPTURECARDTHREAD_H
