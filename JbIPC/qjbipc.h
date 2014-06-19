#ifndef QJBIPC_H
#define QJBIPC_H

#include <QHash>
#include <QThread>
#include "../HKIPC/qipcevent.h"
#include "Common/commonfunction.h"
#include "../../qipcthread.h"
#include "JBNVSDK.h"

class QJBIPC : public QIPCThread
{
    Q_OBJECT
public:
    static QIPCThread* GetInstance( );
    void InitializeThread( );
    void CapturePreviewImage( HWND hPlayWnd, QString& strFileName );
    void CaptureDeviceImage( QString& strIP, QString& strFileName, HWND hPlayWnd = NULL );

    ~QJBIPC( );

    void PostIPCStartupEvent( );
    void PostIPCSetConnectTimeoutEvent( QIPCEvent::EventParam& uParam );
    void PostIPCSetReconnectTimeEvent( QIPCEvent::EventParam& uParam  );
    void PostIPCLoginEvent( QIPCEvent::EventParam& uParam  );
    void PostIPCCaptureJPGEvent( QIPCEvent::EventParam& uParam  );
    void PostIPCStartRealPlayEvent( QIPCEvent::EventParam& uParam  );
    void PostIPCStopRealPlayEvent( QIPCEvent::EventParam& uParam );
    void PostIPCLogoutEvent( QIPCEvent::EventParam& uParam );
    void PostIPCCleanupEvent( );

private:
    typedef QHash< QString, LONG > QIPCUserIDHash;
        typedef QHash< HWND, LONG > QIPCWndPlayHandleHash;

        inline void PostIPCEvent( QIPCEvent::IPCEventType evtType );
        inline void PostIPCEvent( QIPCEvent::IPCEventType evtType,
                                  QIPCEvent::EventParam& uParam );

protected:
    void run( );
    void customEvent( QEvent *e );

private:
    typedef DWORD ( WINAPI *JBNV_OpenServer )(LPCSTR lpServerDNS,WORD wServerPort,
    LPCSTR lpszUserName,LPCSTR lpszPassword,LPVOID *lpHandle);
    typedef DWORD ( WINAPI *JBNV_CloseServer )(HANDLE hServer);
    typedef DWORD ( WINAPI *JBNV_OpenChannel )(HANDLE hServer,
    DWORD dwChannelNo,
    DWORD dwClientIndex,
    DWORD dwNetProtocol,
    DWORD dwStreamType,
    HWND hDispWnd, //ÏÔÊ¾´°¿Ú
    BOOL bUserDecode,
    DWORD dwShowMode,
    LPVOID *lpHandle);
    typedef DWORD ( WINAPI *JBNV_CloseChannel )(HANDLE hChannel);

private:
    explicit QJBIPC(QObject *parent = 0);

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

    void GetFunctionPointer( );

private:
    static QIPCThread* pThreadInstance;
    JBNV_OpenServer MyJBNV_OpenServer;
    JBNV_CloseServer MyJBNV_CloseServer;
    JBNV_OpenChannel MyJBNV_OpenChannel;
    JBNV_CloseChannel MyJBNV_CloseChannel;

    HMODULE hDllMod;

private:
    QIPCUserIDHash hashIP_UserHandle;
    QIPCWndPlayHandleHash hashWnd_PlayHandle;
    bool bStarted;
    QTextCodec* pCodec;
    
signals:
    
public slots:
    
};

#endif // QJBIPC_H
