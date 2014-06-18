#ifndef CUSBCAMERATHREAD_H
#define CUSBCAMERATHREAD_H

#include "QAnalogCameraThread.h"
#include <QLibrary>

class CUsbCameraThread : public QAnalogCameraThread
{
    Q_OBJECT
public:
    static QAnalogCameraThread* GetInstance( );
    ~CUsbCameraThread( );

    void CaptureStaticImage( QString &strFile, int nChannel );
    void GetDevice( QStringList& lstDevice, HWND hOwner );

    static void WINAPI VidCapCallBack( LPBYTE pFrameData, long lFrameSize, long lWidth, long lHeight );


private:
    explicit CUsbCameraThread(QObject *parent = 0);
    typedef void ( CALLBACK *FrameDataCB ) ( LPBYTE pFrameData, long lFrameSize, long lWidth, long lHeight );

    typedef BOOL ( WINAPI *StartUsbCamera ) ( int nDeviceIndex );
    typedef BOOL ( WINAPI *StopUsbCamera ) ( BOOL bReleaseResource );
    typedef std::vector< std::string > ( WINAPI *GetDeviceList ) ( FrameDataCB pfFrameDataCB, HWND hOwnerWnd, LPBYTE pBuffer, int nVidBufSize );
    typedef BOOL ( WINAPI *GetDeviceList2 ) ( char* pDeviceList, int& nBufSize, FrameDataCB pfFrameDataCB, HWND hOwnerWnd, LPBYTE pBuffer, int nVidBufSize );

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
    StartUsbCamera MyStartUsbCamera;
    StopUsbCamera MyStopUsbCamera;
    GetDeviceList MyGetDeviceList;
    GetDeviceList2 MyGetDeviceList2;

    QLibrary hLib;

signals:

public slots:

};

#endif // CUSBCAMERATHREAD_H
