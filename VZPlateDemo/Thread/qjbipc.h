#ifndef QJBIPC_H
#define QJBIPC_H

#include "qdigitalcamerathread.h"
#include "JBNVSDK.h"

class QJBIPC : public QDigitalCameraThread
{
    Q_OBJECT
public:
    static QDigitalCameraThread* GetInstance( );
    void CaptureStaticImage( QString& strIP, QString& strFileName, HWND hPlayWnd = NULL );
    ~QJBIPC( );

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

    void ProcessIPCStartupEvent( QCameraEvent* pEvent );
    void ProcessIPCSetConnectTimeoutEvent( QCameraEvent* pEvent );
    void ProcessIPCSetReconnectTimeEvent( QCameraEvent* pEvent );
    void ProcessIPCLoginEvent( QCameraEvent* pEvent );
    void ProcessIPCCaptureJPGEvent( QCameraEvent* pEvent );
    void ProcessIPCStartRealPlayEvent( QCameraEvent* pEvent );
    void ProcessIPCStopRealPlayEvent( QCameraEvent* pEvent );
    void ProcessIPCLogoutEvent( QCameraEvent* pEvent );
    void ProcessIPCCleanupEvent( QCameraEvent* pEvent );

    void GetFunctionPointer( );

private:
    static QDigitalCameraThread* pThreadInstance;
    JBNV_OpenServer MyJBNV_OpenServer;
    JBNV_CloseServer MyJBNV_CloseServer;
    JBNV_OpenChannel MyJBNV_OpenChannel;
    JBNV_CloseChannel MyJBNV_CloseChannel;

    HMODULE hDllMod;
    
signals:
    
public slots:
    
};

#endif // QJBIPC_H
