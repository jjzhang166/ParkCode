#ifndef QVZALLINONE_H
#define QVZALLINONE_H

#include <QApplication>
#include <windows.h>
#include "../VZPlateDemo/Thread/qplatethread.h"
#include "LP_SDK/VzLPRClientSDK.h"
#include "qipcthread.h"
#include "Common/commonfunction.h"
#include "../HKIPC/qipcevent.h"

// .net线程间通信 SynchronizationContext
// http://msdn.microsoft.com/en-us/magazine/gg598924.aspx

class QVzAllInOne : public QIPCThread
{
    Q_OBJECT
public:
    static QIPCThread* GetInstance( );
    void InitializeThread( );

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

    void EmitPlate( VzLPRClientHandle handle,
                    const TH_PlateResult *pResult, unsigned uNumPlates,
                    VZ_LPRC_RESULT_TYPE eResultType,
                    const VZ_LPRC_IMAGE_INFO *pImgFull,
                    const VZ_LPRC_IMAGE_INFO *pImgPlateClip );

private:
    typedef QHash< QString, LONG > QIPCUserIDHash;
    typedef QHash< HWND, LONG > QIPCWndPlayHandleHash;
    typedef QHash< int, int > QUserIDChannelHash;

    explicit QVzAllInOne(QObject *parent = 0);
    inline void PostIPCEvent( QIPCEvent::IPCEventType evtType );
    inline void PostIPCEvent( QIPCEvent::IPCEventType evtType,
                              QIPCEvent::EventParam& uParam );
    QString GetPlateMoveDirection( int nDirection );

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

    inline void SetUserIDChannel( int nUserID, int nChannel );
    inline LONG GetUserIDChannel( int nUserID );
    inline void RemoveUserIDChannel( int nUserID );

    inline void ClearHash( );

    void GetFunctionPointer( );
    void PrintExceptionCode( int nRet, QString& strFunName );

    static int WINAPI MyVZLPRC_PLATE_INFO_CALLBACK(VzLPRClientHandle handle, void *pUserData,
                                                   const TH_PlateResult *pResult, unsigned uNumPlates,
                                                   VZ_LPRC_RESULT_TYPE eResultType,
                                                   const VZ_LPRC_IMAGE_INFO *pImgFull,
                                                   const VZ_LPRC_IMAGE_INFO *pImgPlateClip );

private:
    QIPCUserIDHash hashIP_UserHandle;
    QIPCWndPlayHandleHash hashWnd_PlayHandle;
    QUserIDChannelHash hashUserID_Channel;
    bool bStarted;
    static QIPCThread* pThreadInstance;
    HMODULE hDllMod;
    QTextCodec* pCodec;

    typedef int ( WINAPI *VzLPRClient_Setup ) (  );
    typedef int ( WINAPI *VzLPRClient_Cleanup ) ( );

    typedef int ( WINAPI *VzLPRClient_Open )( const char *pStrIP, WORD wPort,
                                              const char *pStrUserName,
                                              const char *pStrPassword );
    typedef int ( WINAPI *VzLPRClient_Close  ) ( int iUserID );

    typedef int ( WINAPI *VzLPRClient_StartRealPlay ) ( int iUserID, void *hWnd );
    typedef int ( WINAPI *VzLPRClient_StopRealPlay ) ( void *hWnd );

    typedef int ( WINAPI *VzLPRClient_SetPlateInfoCallBack )( VzLPRClientHandle handle, VZLPRC_PLATE_INFO_CALLBACK func, void *pUserData, int bEnableImage);
    typedef int ( WINAPI *VzLPRClient_GetSnapShootToJpeg )( void *hWnd, const char *pFullPathName, int nQuality );



    VzLPRClient_Setup MyVzLPRClient_Setup;
    VzLPRClient_Cleanup MyVzLPRClient_Cleanup;

    VzLPRClient_Open MyVzLPRClient_Open;
    VzLPRClient_Close MyVzLPRClient_Close;

    VzLPRClient_StartRealPlay MyVzLPRClient_StartRealPlay;
    VzLPRClient_StopRealPlay MyVzLPRClient_StopRealPlay;

    VzLPRClient_SetPlateInfoCallBack MyVzLPRClient_SetPlateInfoCallBack;
    VzLPRClient_GetSnapShootToJpeg MyVzLPRClient_GetSnapShootToJpeg;

signals:
    void CapturedJPGImage( quint32 nChannel, QString strFileName );
    void UIPlateResult( QString strPlate, int nChannel, bool bSuccess,
                              bool bVideo, int nWidth, int nHeight, int nConfidence,
                              QString strDirection, QByteArray byData, QRect rectPlate, QRect rectVideo );


protected slots:
    void HandleStarted( );
    void HandleFinished( );
    
};

#endif // QVZALLINONE_H
