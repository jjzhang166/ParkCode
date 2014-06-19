#ifndef QIPCEVENT_H
#define QIPCEVENT_H

#include <QEvent>
#include <QString>
#include <windows.h>
#include "./inc/HCNetSDK.h"

// 255.255.255.255
#define IPC_IP_LEN  ( quint8 ) 15
#define IPC_CAPTURE_FILE_LEN 511

class QIPCEvent : public QEvent
{
public:
    typedef enum __IPCEventType {
        IPCStartup = User,
        IPCSetConnectTimeout,
        IPCSetReconnectTime,
        IPCLogin,
        IPCCaptureJPG,
        IPCStartRealPlay,
        IPCStopRealPlay,
        IPCLogout,
        IPCCleanup
    } IPCEventType;

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
            char cIP[ IPC_IP_LEN + 1 ];
            WORD wPort;
            char cUser[NAME_LENGTH + 1 ];
            char cPwd[ PASSWD_LEN + 1 ];
        } EventLogin;

        struct __EventCaptureJPG {
            char cIP[ IPC_IP_LEN + 1 ];
            char cFile[ IPC_CAPTURE_FILE_LEN + 1 ];
            quint32 nChannel;
        } EventCaptureJPG;

        struct __EventStartRealPlay {
            HWND hPlayWnd;
            char cIP[ IPC_IP_LEN + 1 ];
            bool bMainStream;
        } EventStartRealPlay;

        struct __EventStopRealPlay {
            HWND hPlayWnd;
        } EventStopRealPlay;

        struct __EventLogout {
            char cIP[ IPC_IP_LEN + 1 ];
        } EventLogout;

        __EventParam( )
        {
            memset( this, 0, sizeof( *this ) );
        }
    } EventParam;

    static QIPCEvent* GetInstance( IPCEventType evtType );
    void SetEventParam( EventParam& uParam );
    EventParam& GetEventParam( );
    ~QIPCEvent( );

private:
    QIPCEvent( Type evtType );

    EventParam evtParam;
};

#endif // QIPCEVENT_H
