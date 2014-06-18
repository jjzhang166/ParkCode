#ifndef QUV200THREAD_H
#define QUV200THREAD_H

#include "QAnalogCameraThread.h"
#include "Sa7134Capture.h"

class QUv200Thread : public QAnalogCameraThread
{
    Q_OBJECT
public:
    static QAnalogCameraThread* GetInstance( );
    ~QUv200Thread( );
    void SetDeleteFile( bool bDelete );

    void CaptureStaticImage( QString &strFile, int nChannel );

    static void CALLBACK VidCapCallBack( long lnCardID, long pBuf, long lnWidth, long lnHeight, long lnBiCount );

private:
    explicit QUv200Thread(QObject *parent = 0);

    static void CALLBACK MotionDelectCB( long lnCardID, BOOL bMove, LPVOID lpContext );
    void GetFunctionPointer( );

    typedef HRESULT ( WINAPI *VCAInitSdk ) ( );
    typedef void ( WINAPI *VCAUnInitSdk ) ( );
    typedef HRESULT	( WINAPI *VCAConnectDevice ) ( int nCards, BOOL bOverlay,
                                                   HWND hParentWnd, SIZE& szVidSize,
                                                   VIDEOSOURCE enVideoSource, int nFrameRate,
                                                   VideoSubType enVideoSubType );
    typedef HRESULT ( WINAPI *VCADisConnectDevice ) ( int nCards );
    typedef HRESULT ( WINAPI *VCAEnableMotionDetect ) ( int nCards, BOOL bEnaDetect,
                                                        BYTE *pAreaMap, LONG nSizeOfMap,
                                                        LONG nPersistTime, LPVOID lpContext,
                                                        PrcCbMotionDetectUV200 OnObjectMove );
    typedef HRESULT ( WINAPI *VCACapturePicture ) ( int nCards, LPCSTR szFileName,
                                                    enImageType enImgType, RECT* rcImg,
                                                    long nQuality, long nCapCount, BOOL bCapFast );
    typedef HRESULT ( WINAPI *VCARun ) ( int nCards );
    typedef HRESULT ( WINAPI *VCAPause ) ( int nCards );
    typedef HRESULT ( WINAPI *VCAStop ) ( int nCards );
    typedef HRESULT ( WINAPI *VCAEnableCapSourceStream ) ( int nCards, BOOL bCapStream,
                                                           VideoFieldType enVideoFieldType,
                                                           PrcCapSourceStream pCapStream );
    typedef HRESULT ( WINAPI *VCAStartCapture ) ( int nCards );
    typedef HRESULT ( WINAPI *VCAStopCapture ) ( int nCards );
    typedef HRESULT ( WINAPI *VCASetCaptureFile ) ( int nCards, LPCSTR szFileName );
    typedef HRESULT ( WINAPI *VCASetCurrentVideoCompressor ) ( int nCards, LPCSTR pCompDevName );

    VCAInitSdk MyVCAInitSdk;
    VCAUnInitSdk MyVCAUnInitSdk;
    VCAConnectDevice MyVCAConnectDevice;
    VCADisConnectDevice MyVCADisConnectDevice;
    VCAEnableMotionDetect MyVCAEnableMotionDetect;
    VCACapturePicture MyVCACapturePicture;
    VCARun MyVCARun;
    VCAPause MyVCAPause;
    VCAStop MyVCAStop;
    VCAEnableCapSourceStream MyVCAEnableCapSourceStream;
    VCAStartCapture MyVCAStartCapture;
    VCAStopCapture MyVCAStopCapture;
    VCASetCaptureFile MyVCASetCaptureFile;
    VCASetCurrentVideoCompressor MyVCASetCurrentVideoCompressor;

    HMODULE hDllMod;
    
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
    bool bDeleteFile;

signals:

public slots:

};

#endif // QUV200THREAD_H
