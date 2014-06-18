#ifndef QIPCTHREAD_H
#define QIPCTHREAD_H

#include <QThread>
#include <windows.h>
#include "./HKIPC/qipcevent.h"

class QIPCThread : public QThread
{
    Q_OBJECT
public:
    explicit QIPCThread(QObject *parent = 0);

    virtual void InitializeThread( ) = 0;

    virtual void PostIPCStartupEvent( ) = 0;
    virtual void PostIPCSetConnectTimeoutEvent( QIPCEvent::EventParam& uParam ) = 0;
    virtual void PostIPCSetReconnectTimeEvent( QIPCEvent::EventParam& uParam  ) = 0;
    virtual void PostIPCLoginEvent( QIPCEvent::EventParam& uParam  ) = 0;
    virtual void PostIPCCaptureJPGEvent( QIPCEvent::EventParam& uParam  ) = 0;
    virtual void PostIPCStartRealPlayEvent( QIPCEvent::EventParam& uParam  ) = 0;
    virtual void PostIPCStopRealPlayEvent( QIPCEvent::EventParam& uParam ) = 0;
    virtual void PostIPCLogoutEvent( QIPCEvent::EventParam& uParam ) = 0;
    virtual void PostIPCCleanupEvent( ) = 0;

    virtual void CapturePreviewImage( HWND hPlayWnd, QString& strFileName ) = 0;
    virtual void CaptureDeviceImage( QString& strIP, QString& strFileName, HWND hPlayWnd = NULL ) = 0;
    
signals:
    
public slots:
    
};

#endif // QIPCTHREAD_H
