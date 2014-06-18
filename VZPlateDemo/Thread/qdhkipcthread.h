#ifndef QHKIPCTHREAD_H
#define QHKIPCTHREAD_H

#include "QDigitalCameraThread.h"
#include "HCNetSDK.h"
#include "PlayM4.h"

#define MAX_IPC_WAY ( int ) 100

class QDHkIPCThread : public QDigitalCameraThread
{
    Q_OBJECT
public:
    ~QDHkIPCThread( );
    static QDigitalCameraThread* GetInstance( );
    void CaptureStaticImage( QString &strIP, QString &strFileName, HWND hPlayWnd = NULL );

protected:
    void run( );
    void customEvent( QEvent *e );

private:
    explicit QDHkIPCThread(QObject *parent = 0);
    void GetFunctionPointer( );

    void ProcessIPCStartupEvent( QCameraEvent* pEvent );
    void ProcessIPCSetConnectTimeoutEvent( QCameraEvent* pEvent );
    void ProcessIPCSetReconnectTimeEvent( QCameraEvent* pEvent );
    void ProcessIPCLoginEvent( QCameraEvent* pEvent );
    void ProcessIPCCaptureJPGEvent( QCameraEvent* pEvent );
    void ProcessIPCStartRealPlayEvent( QCameraEvent* pEvent );
    void ProcessIPCStopRealPlayEvent( QCameraEvent* pEvent );
    void ProcessIPCLogoutEvent( QCameraEvent* pEvent );
    void ProcessIPCCleanupEvent( QCameraEvent* pEvent );
    void ProcessIPCCaptureImage( QCameraEvent* pEvent );

    void CapturePicture( QString& strIP, QString& strFile );

    static void CALLBACK ExceptionCallback( DWORD dwType, LONG lUserID, LONG lHandle, void* pUser );
    void SendNotify( DWORD dwType, LONG lUserID, LONG lHandle );

    static void CALLBACK RealDataStreamCallback( LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser );
    void RealStream( LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize );

    static void CALLBACK RealDataCallback( LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void* pUser );
    void ProcessRealDataCallback( LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize );
    static void CALLBACK DisplayCBFun( long nPort, char* pBuf, long nSize,
                                       long nWidth, long nHeight, long nStamp,
                                       long nType, long nReceved );

    static void CALLBACK RealStandardDataStreamCallback( LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser );
    void RealStandardStream( LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize );

    void ProcessDataStream( LONG lRealHandle, BYTE *pBuffer, DWORD dwBufSize );
    void ParseResolution( LONG lRealHandle, int& nWidth, int& nHeight );
    void GetDeviceAbility( LONG lUserID, LONG lRealHandle );

private:
    static QDigitalCameraThread* pThreadInstance;
    LONG lPlayPorts[ MAX_IPC_WAY ];
    HMODULE hDllMod;
    int nChannel;

    typedef BOOL ( WINAPI *PlayM4_GetPort ) ( LONG* nPort );
    typedef BOOL ( WINAPI *PlayM4_SetStreamOpenMode ) ( LONG nPort, DWORD nMode );
    typedef BOOL ( WINAPI *PlayM4_OpenStream ) ( LONG nPort, PBYTE pFileHeadBuf, DWORD nSize,
                                                 DWORD nBufPoolSize );
    typedef BOOL ( WINAPI *PlayM4_Play ) ( LONG nPort, HWND hWnd );
    typedef BOOL ( WINAPI *PlayM4_SetDisplayCallBack ) ( LONG nPort,
                                                         void ( CALLBACK* DisplayCBFun )( long nPort,char * pBuf, long nSize, long nWidth,
                                                                                       long nHeight, long nStamp, long nType, long nReserved ) );
    typedef BOOL ( WINAPI *PlayM4_InputData ) ( LONG nPort, PBYTE pBuf, DWORD nSize );

    PlayM4_GetPort MyPlayM4_GetPort;
    PlayM4_SetStreamOpenMode MyPlayM4_SetStreamOpenMode;
    PlayM4_OpenStream MyPlayM4_OpenStream;
    PlayM4_SetDisplayCallBack MyPlayM4_SetDisplayCallBack;
    PlayM4_InputData MyPlayM4_InputData;
    PlayM4_Play MyPlayM4_Play;
    
signals:
    
public slots:
    
};

#endif // QHKIPCTHREAD_H
