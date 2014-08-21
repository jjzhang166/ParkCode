#ifndef QDHALLINONE_H
#define QDHALLINONE_H

#include <QApplication>
#include <windows.h>
#include "../VZPlateDemo/Thread/qplatethread.h"
#include "DHSDK/dhnetsdk.h"
#include "qipcthread.h"
#include "Common/commonfunction.h"
#include "../HKIPC/qipcevent.h"

class QDHAllInOne : public QIPCThread
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
    typedef QHash< int, int > QUserIDChannelHash;

    explicit QDHAllInOne(QObject *parent = 0);
    inline void PostIPCEvent( QIPCEvent::IPCEventType evtType );
    inline void PostIPCEvent( QIPCEvent::IPCEventType evtType,
                              QIPCEvent::EventParam& uParam );
    QString GetPlateMoveDirection( int nDirection );
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

    inline void SetUserIDChannel( int nUserID, int nChannel );
    inline LONG GetUserIDChannel( int nUserID );
    inline void RemoveUserIDChannel( int nUserID );

    inline void SetPlayHandle( HWND hPlayWnd, LONG lPlayHandle );
    inline LONG GetPlayHandle( HWND hPlayWnd );
    inline void RemovePlayHandle( HWND hPlayWnd );
    inline void ClearHash( );

    void GetFunctionPointer( );
    void PrintExceptionCode( int nRet, QString& strFunName );

    static void CALLBACK MyDisConnect( LLONG  lLoginID, char  *pchDVRIP, LONG   nDVRPort, LDWORD dwUser );

private:
    QIPCUserIDHash hashIP_UserHandle;
    QIPCWndPlayHandleHash hashWnd_PlayHandle;
    QUserIDChannelHash hashUserID_Channel;
    bool bStarted;
    static QIPCThread* pThreadInstance;
    HMODULE hDllMod;
    QTextCodec* pCodec;

    typedef BOOL ( WINAPI *CLIENT_Init ) ( fDisConnect cbDisConnect, LDWORD dwUser  );
    typedef void ( WINAPI *CLIENT_Cleanup ) (  );

    typedef void ( WINAPI *CLIENT_SetAutoReconnect ) ( fHaveReConnect cbAutoConnect, LDWORD dwUser );
    typedef void ( WINAPI *CLIENT_SetConnectTime ) ( int  nWaitTime, int  nTryTimes );

    typedef DWORD ( WINAPI *CLIENT_GetLastError ) ( );

    typedef LLONG ( WINAPI *CLIENT_LoginEx ) (
      char             *pchDVRIP,
      WORD             wDVRPort,
      char             *pchUserName,
      char             *pchPassword,
      int              nSpecCap,
      void             *pCapParam,
      LPNET_DEVICEINFO lpDeviceInfo,
      int              *error
    );
    typedef BOOL ( WINAPI *CLIENT_Logout ) (
      LLONG lLoginID
    );

    typedef LLONG ( WINAPI *CLIENT_RealPlay ) (
      LLONG lLoginID,
      int  nChannelID,
      HWND hWnd
    );
    typedef BOOL ( WINAPI *CLIENT_StopRealPlay ) (
      LLONG lRealHandle
    );

    typedef BOOL ( WINAPI *CLIENT_CapturePicture ) (
      LLONG       hPlayHandle,
      const char  *pchPicFileName
    );

    typedef LLONG ( WINAPI *CLIENT_CreateTransComChannel ) (
      LLONG             lLoginID,
      int               TransComType,
      unsigned int      baudrate,
      unsigned int      databits,
      unsigned int      stopbits,
      unsigned int      parity,
      fTransComCallBack cbTransCom,
      LDWORD            dwUser
    );
    typedef BOOL ( WINAPI *CLIENT_SendTransComData ) (
      LLONG  lTransComChannel,
      char   *pBuffer,
      DWORD  dwBufSize
    );
    typedef BOOL ( WINAPI *CLIENT_DestroyTransComChannel ) (
      LLONG lTransComChannel
    );
    typedef BOOL ( WINAPI *CLIENT_QueryTransComParams ) (
      LLONG  lLoginID,
      int    TransComType,
      DH_COMM_STATE  *pCommState,
      int    nWaitTime
    );

    CLIENT_Init MyCLIENT_Init;
    CLIENT_Cleanup MyCLIENT_Cleanup;
    CLIENT_SetAutoReconnect MyCLIENT_SetAutoReconnect;
    CLIENT_SetConnectTime MyCLIENT_SetConnectTime;
    CLIENT_GetLastError MyCLIENT_GetLastError;
    CLIENT_LoginEx MyCLIENT_LoginEx;
    CLIENT_Logout MyCLIENT_Logout;
    CLIENT_RealPlay MyCLIENT_RealPlay;
    CLIENT_StopRealPlay MyCLIENT_StopRealPlay;
    CLIENT_CapturePicture MyCLIENT_CapturePicture;
    CLIENT_CreateTransComChannel MyCLIENT_CreateTransComChannel;
    CLIENT_SendTransComData MyCLIENT_SendTransComData;
    CLIENT_DestroyTransComChannel MyCLIENT_DestroyTransComChannel;
    CLIENT_QueryTransComParams MyCLIENT_QueryTransComParams;

signals:
    void NotifyMessage( QString strMsg );
    void CapturedJPGImage( quint32 nChannel, QString strFileName );


protected slots:
    void HandleStarted( );
    void HandleFinished( );
    
};

#endif // QDHALLINONE_H
