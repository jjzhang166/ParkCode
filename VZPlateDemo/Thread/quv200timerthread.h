#ifndef QUV200TIMERTHREAD_H
#define QUV200TIMERTHREAD_H

#include <QThread>

#include "quv200thread.h"

class QUV200TimerThread : public QAnalogCameraThread
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

    static QAnalogCameraThread* GetInstance( bool bVideo = false );
    ~QUV200TimerThread( );

    void CaptureStaticImage( QString &strFile, int nChannel );

protected:
    void run( );
    void customEvent( QEvent *e );
    void timerEvent( QTimerEvent *e );

private:
    QUV200TimerThread( QObject* parent = NULL );

    QAnalogCameraThread* pUv200Thread;
    static QAnalogCameraThread* pThreadInstance;
    static bool bUv200Video;
    QString strPlateDir;
    int nTimerID;
    
signals:
    
public slots:
    
};

#endif // QUV200TIMERTHREAD_H
