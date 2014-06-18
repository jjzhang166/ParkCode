#ifndef QANALOGCAMERATHREAD_H
#define QANALOGCAMERATHREAD_H

#include <QThread>
#include "qcameraevent.h"
#include <windows.h>
#include <QApplication>
#include <QFile>
#include "qcommon.h"
#include "qplatethread.h"

class QAnalogCameraThread : public QThread
{
    Q_OBJECT

public:
    virtual void PostInitCaptureSDKEvent( HWND hParentVideo = NULL );
    virtual void PostUninitCaptureSDKEvent( );

    virtual void PostOpenChannelEvent( int nChannel );
    virtual void PostCloseChannelEvent( int nChannel );

    virtual void PostStartCaptureEvent( int nChannel );
    virtual void PostStopCaptureEvent( int nChannel );

    virtual void PostPlayVideoEvent( int nChannel, HWND hVideo );
    virtual void PostStopVideoEvent( int nChannel );

    virtual void PostCaptrueImageEvent( int nChannel, QString& strFile, bool bRecognize );

    virtual void PostStartMotionDetectEvent( int nChannel );
    virtual void PostStopMotionDetectEvent( int nChannel );

    virtual void PostStartSourceStreamEvent( int nChannel, bool bRegister );
    virtual void PostStopSourceStreamEvent( int nChannel );

    void SendDetectInfo( int nChannel, bool bMotion );
    void SetMotionDetect( bool bMotion, int nChannel );
    bool GetMotionDetect( int nChannel );

    virtual void CaptureStaticImage( QString& strFile, int nChannel );

    QPlateThread* GetPlateThread( );

protected:
    explicit QAnalogCameraThread(QObject *parent = 0);
    void SendCaptureImage( QString& strFile, int nChannel );
    void SendNotifyMessage( QString& strMsg, bool bSuccess );

    bool bMotionDetects[ CHANNEL_WAY ];

private:
    inline void PostEvent( QCameraEvent* pEvent );

private:
    QPlateThread* pPlateThread;

signals:
    void CaptureImage( QString strFile, int nChannel );
    void NotifyMessage( QString strMsg, bool bSuccess );
    void DetectInfo( int nChannel, bool bMotion );
    
public slots:
    
};

#endif // QANALOGCAMERATHREAD_H
