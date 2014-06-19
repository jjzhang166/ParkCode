#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include "Multimedia_global.h"
#ifdef _WIN32
#include <windows.h>
#endif

#include <QObject>
#include <QRect>
#include <QFrame>
#include "../Common/commonfunction.h"
#define VIDEO_WAY ( int ) ( 4 )
#define INVALID_HANDLE ( HANDLE ) ( 0XFFFFFFFF )
#define WM_SDK_NOTIFY		WM_USER + 0x600

typedef void ( *HK_STREAM_CB )( UINT, void* );
typedef void ( *HK_MOTION_CB )( ULONG, BOOL, void* );
typedef void ( CALLBACK *MyPrcPicMessage )( long lnCardID, long pBuf, long lnWidth, long lnHeight);

class MULTIMEDIASHARED_EXPORT CMultimedia : public QObject
{
    //Q_OBJECT

public:
    explicit CMultimedia( QObject *parent = 0 );
    virtual ~CMultimedia( );

public:
    typedef enum __AvSdk {
        HikSdk,
        TmSDK,
        JvsSDK
    } AvSdk;

public:
    virtual int SystemStartup( HWND hOverlayWnd = NULL ) = 0;
    virtual int SystemShutdown( ) = 0;
    virtual HANDLE OpenChannel( int nChannelNum ) = 0;
    virtual int CloseChannel( HANDLE hChannel ) = 0;
    virtual int PlayVideo( HANDLE hChannel, HWND hWnd, QRect &rect, int nIndex ) = 0;
    virtual int StopVideo( HANDLE hChannel ) = 0;
    virtual int CaptureBMP( HANDLE hChannel, QString& strFile ) = 0;
    virtual int CaptureJpeg( HANDLE hChannel, QString& strFile ) = 0;
    virtual int GetYuv422Data( HANDLE hChannel, quint8* pData, ULONG& lSize ) = 0;
    virtual int RegisterStreamCB( HK_STREAM_CB pCBF, PVOID pContext ) = 0;
    virtual int GetStreamData( HANDLE hChannel, BOOL bStart, quint8 *pData, int nIndex ) = 0;
    virtual int MotionDetection( HANDLE hChannel, bool bStart ) = 0;
    virtual int SetupDetection( HANDLE hChannel, HK_MOTION_CB pCBF, int nIndex = 0, LPVOID pContext =NULL ) = 0;
    virtual int TmEnablePicMessage( int nCards, BOOL bPicMessage, MyPrcPicMessage pPicMessage );
    static CMultimedia* CreateInstance( AvSdk sdkType );
    static void DestroyInstance( CMultimedia* pInstance );

protected:
    virtual void GetParameters( ) = 0;

protected:
    QTextCodec* pCodec;
    QSettings* pSettings;
    int nFps[VIDEO_WAY ];
    int nDelay[ VIDEO_WAY ];
    int nGrade[ VIDEO_WAY ];
    RECT rDetectionRange[ VIDEO_WAY ];

private:

//signals:

//public slots:

};

#endif // MULTIMEDIA_H
