#ifndef QJWSIPCEVENT_H
#define QJWSIPCEVENT_H

#define JWSIPC_IP_LEN  ( quint8 ) 15
#define JWSIPC_CAPTURE_FILE_LEN 511

#include <QEvent>
#include <QString>
#include <windows.h>
#include <QApplication>
#include "./inc/tmTransDefine.h"
#include "./inc/tmControlClient.h"

class QJwsIPCEvent : public QEvent
{
public:
    typedef enum __IPCEventType {
        IPCStartup = User, //HANDLE hPreview = TMCC_Init(TMCC_INITTYPE_REALSTREAM);
        IPCSetConnectTimeout, //int TMCC_SetTimeOut( HANDLE hTmCC, int dwTime );
        IPCSetReconnectTime, //int TMCC_SetAutoReConnect( HANDLE hTmCC, BOOL bAutoConnect );
        IPCLogin, //int TMCC_Connect( HANDLE hTmCC, tmConnectInfo_t* pConnectInfo, BOOL bSync );
        IPCCaptureJPG, //int TMCC_CapturePictureToFile( HANDLE hTmCC, const char* pFileName, const char* pFmt );
        IPCStartRealPlay, //int TMCC_ConnectStream( HANDLE hClient, tmPlayRealStreamCfg_t* pPlayInfo, HWND hPlayWnd );
        IPCStopRealPlay, //int TMCC_CloseStream( HANDLE hStream );
        IPCLogout, //int TMCC_DisConnect( HANDLE hTmC );
        IPCCleanup //int TMCC_ShutDown( HANDLE hTmCC );int  TMCC_Done( HANDLE hTmCC );
    } IPCEventType;

    // BOOL TMCC_IsConnect( HANDLE hTmCC );

    typedef union __EventParam {
        struct __EventSetConnectTimeout {
            DWORD dwWaitTime; // 300-75000
            DWORD dwTryTimes;
        } EventConnectTimeout;

        struct __EventSetReconnectTimeout {
            DWORD   dwInterval;
            BOOL    bEnableRecon;
        } EventReconnectTimeout;

        struct __EventLogin {
            char cIP[ JWSIPC_IP_LEN + 1 ];
            WORD wPort;
            char cUser[ NAME_LEN + 1 ];
            char cPwd[ PASSWD_LEN + 1 ];
        } EventLogin;

        struct __EventCaptureJPG {
            char cIP[ JWSIPC_IP_LEN + 1 ];
            char cFile[ JWSIPC_CAPTURE_FILE_LEN + 1 ];
            quint32 nChannel;
        } EventCaptureJPG;

        struct __EventStartRealPlay {
            HWND hPlayWnd;
            char cIP[ JWSIPC_IP_LEN + 1 ];
        } EventStartRealPlay;

        struct __EventStopRealPlay {
            HWND hPlayWnd;
        } EventStopRealPlay;

        struct __EventLogout {
            char cIP[ JWSIPC_IP_LEN + 1 ];
        } EventLogout;

        __EventParam( )
        {
            memset( this, 0, sizeof( *this ) );
        }
    } EventParam;

    static QJwsIPCEvent* GetInstance( IPCEventType evtType );
    void SetEventParam( EventParam& uParam );
    EventParam& GetEventParam( );
    ~QJwsIPCEvent( );

private:
    QJwsIPCEvent( Type evtType );
    EventParam evtParam;
};

#endif // QJWSIPCEVENT_H
