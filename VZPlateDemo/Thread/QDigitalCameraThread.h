#ifndef QDIGITALCAMERATHREAD_H
#define QDIGITALCAMERATHREAD_H

#include <QThread>
#include "qcameraevent.h"
#include <QApplication>
#include <QHash>
#include "qcommon.h"
#include "qplatethread.h"

class QDigitalCameraThread : public QThread
{
    Q_OBJECT

public:
    virtual void PostIPCStartupEvent( );
    virtual void PostIPCSetConnectTimeoutEvent( );
    virtual void PostIPCSetReconnectTimeEvent( );
    virtual void PostIPCLoginEvent( QString& strIP );
    virtual void PostIPCCaptureJPGEvent( QString& strIP, QString& strFile, bool bRecognize, HWND hPlayWnd = NULL );
    virtual void PostIPCStartRealPlayEvent( QString& strIP, bool bMainStream, bool bRealStream, HWND hPlayWnd );
    virtual void PostIPCStopRealPlayEvent( HWND hPlayWnd );
    virtual void PostIPCLogoutEvent( QString& strIP );
    virtual void PostIPCCleanupEvent( );

    virtual void CaptureStaticImage( QString& strIP, QString& strFileName, HWND hPlayWnd = NULL );
    QPlateThread* GetPlateThread( );

    LONG GetPlayHandleByChannel( LONG lChannel );
    QString GetIP( LONG lPlayHandle );

protected:
    explicit QDigitalCameraThread(QObject *parent = 0);

    void SetUserID( QString& strIP, LONG lUserID );
    LONG GetUserID( QString& strIP );
    void RemoveUserID( QString& strIP );

    void SetIP( LONG lPlayHandle, QString& strIP );
    //QString GetIP( LONG lPlayHandle );
    void RemoveIP( LONG lPlayHandle );

    void SetResolution( LONG lPlayHandle, QString& strResolution );
    QString GetResolution( LONG lPlayHandle );
    void RemoveResolution( LONG lPlayHandle );

    void SetPlayHandle( HWND hPlayWnd, LONG lPlayHandle );
    LONG GetPlayHandle( HWND hPlayWnd );
    HWND GetPlayWnd( LONG lPlayHandle );
    void RemovePlayHandle( HWND hPlayWnd );
    void ClearHash( );

    void SetChannel( LONG lPlayHandle, LONG lChannel );
    LONG GetChannel( LONG lPlayHandle );

    void SendCaptureImage( QString& strFile, QString& strIP );

    QTextCodec* pCodec;

private:
    inline void PostEvent( QCameraEvent* pEvent );

private:
    QPlateThread* pPlateThread;

private:
    typedef QHash< QString, LONG > QIPLoginIDHash;
    typedef QHash< HWND, LONG > QWndPlayHandleHash;
    typedef QHash< LONG, QString > QPlayHandleIP;
    typedef QHash< LONG, QString > QPlayHandleResolution;
    typedef QHash< LONG, LONG > QPlayHandleChannel;

    QIPLoginIDHash hashIP_UserHandle;
    QWndPlayHandleHash hashWnd_PlayHandle;
    QPlayHandleIP hashPlayHandle_IP;
    QPlayHandleResolution hashPlayHandle_Resolution;
    QPlayHandleChannel hashPlayHandleChannel;

signals:
    void CaptureImage( QString strFile, QString strIP );
    
public slots:
    
};

#endif // QDIGITALCAMERATHREAD_H
