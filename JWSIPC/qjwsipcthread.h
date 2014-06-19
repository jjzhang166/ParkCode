#ifndef QJWSIPCTHREAD_H
#define QJWSIPCTHREAD_H

#include <QHash>
#include <QThread>
#include "../HKIPC/qipcevent.h"
#include <QTextCodec>
#include <QDebug>
#include "../Common/commonfunction.h"
#include "../../qipcthread.h"

#include "./inc/tmTransDefine.h"
#include "./inc/tmControlClient.h"

class QJwsIPCThread : public QIPCThread
{
    Q_OBJECT
public:
    static QIPCThread* GetInstance( );
    void InitializeThread( );
    void SendNotify( HANDLE hTmCC, BOOL bConnect, unsigned int dwResult );

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
    typedef QHash< QString, HANDLE > QIPCUserIDHash;
    typedef QHash< HWND, HANDLE > QIPCWndPlayHandleHash;

    explicit QJwsIPCThread(QObject *parent = 0);
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

    inline void SetUserID( char* pIP, HANDLE lUserID );
    inline HANDLE GetUserID( char* pIP );
    inline void RemoveUserID( char* pIP );

    inline void SetPlayHandle( HWND hPlayWnd, HANDLE lPlayHandle );
    inline HANDLE GetPlayHandle( HWND hPlayWnd );
    inline void RemovePlayHandle( HWND hPlayWnd );
    inline void ClearHash( );

    inline void JwsCleanup( HANDLE hCtrl );
    void JwsConnect( QIPCEvent* pEvent, HANDLE hCtrl );

private:
    QIPCUserIDHash hashIP_UserHandle;
    QIPCWndPlayHandleHash hashWnd_PlayHandle;
    bool bStarted;
    static QIPCThread* pThreadInstance;
    QTextCodec* pCodec;

    //HANDLE hTmccCtrl;
    //HANDLE hTmccPreview;

signals:
    void NotifyMessage( QString strMsg );
    void CapturedJPGImage( quint32 nChannel, QString strFileName );


protected slots:
    void HandleStarted( );
    void HandleFinished( );
};

#endif // QJWSIPCTHREAD_H
