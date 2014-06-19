#ifndef QHKIPCTHREAD_H
#define QHKIPCTHREAD_H

#include <QHash>
#include <QThread>
#include "qipcevent.h"
#include "Common/commonfunction.h"
#include "../../qipcthread.h"

class QHkIPCThread : public QIPCThread
{
    Q_OBJECT
public:
    static QIPCThread* GetInstance( );
    void InitializeThread( );
    void SendNotify( DWORD dwType,
                     LONG lUserID,
                     LONG lHandle );

    void PostIPCStartupEvent( );
    void PostIPCSetConnectTimeoutEvent( QIPCEvent::EventParam& uParam );
    void PostIPCSetReconnectTimeEvent( QIPCEvent::EventParam& uParam  );
    void PostIPCLoginEvent( QIPCEvent::EventParam& uParam  );
    void PostIPCCaptureJPGEvent( QIPCEvent::EventParam& uParam  );
    void PostIPCStartRealPlayEvent( QIPCEvent::EventParam& uParam  );
    void PostIPCStopRealPlayEvent( QIPCEvent::EventParam& uParam );
    void PostIPCLogoutEvent( QIPCEvent::EventParam& uParam );
    void PostIPCCleanupEvent( );

    void CapturePreviewImage( HWND hPlayWnd, QString& strFileName );
    void CaptureDeviceImage( QString& strIP, QString& strFileName, HWND hPlayWnd = NULL );

private:
    typedef QHash< QString, LONG > QIPCUserIDHash;
    typedef QHash< HWND, LONG > QIPCWndPlayHandleHash;

    explicit QHkIPCThread(QObject *parent = 0);
    inline void PostIPCEvent( QIPCEvent::IPCEventType evtType );
    inline void PostIPCEvent( QIPCEvent::IPCEventType evtType,
                              QIPCEvent::EventParam& uParam );
    inline void GetErrorMessage( );
    inline void EmitMsg( QString strMsg, QString strFunName );

protected:
    void run( );
    void customEvent( QEvent* event );

private:
    void ProcessIPCStartupEvent( QIPCEvent* pEvent );
    void ProcessIPCSetConnectTimeoutEvent( QIPCEvent* pEvent );
    void ProcessIPCSetReconnectTimeEvent( QIPCEvent* pEvent );
    void ProcessIPCLoginEvent( QIPCEvent* pEvent );
    void ProcessIPCCaptureJPGEvent( QIPCEvent* pEvent );
    void ProcessIPCStartRealPlayEvent( QIPCEvent* pEvent );
    void ProcessIPCStopRealPlayEvent( QIPCEvent* pEvent );
    void ProcessIPCLogoutEvent( QIPCEvent* pEvent );
    void ProcessIPCCleanupEvent( QIPCEvent* pEvent );

    inline void SetUserID( char* pIP, LONG lUserID );
    inline LONG GetUserID( char* pIP );
    inline void RemoveUserID( char* pIP );

    inline void SetPlayHandle( HWND hPlayWnd, LONG lPlayHandle );
    inline LONG GetPlayHandle( HWND hPlayWnd );
    inline void RemovePlayHandle( HWND hPlayWnd );
    inline void ClearHash( );

private:
    QIPCUserIDHash hashIP_UserHandle;
    QIPCWndPlayHandleHash hashWnd_PlayHandle;
    bool bStarted;
    static QIPCThread* pThreadInstance;
    QTextCodec* pCodec;

signals:
    void NotifyMessage( QString strMsg );
    void CapturedJPGImage( quint32 nChannel, QString strFileName );

    
protected slots:
    void HandleStarted( );
    void HandleFinished( );
};

#endif // QHKIPCTHREAD_H
