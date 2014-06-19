#ifndef JVSSDK_H
#define JVSSDK_H

#ifdef _WIN32
#include <windows.h>
#endif
#include "jvsdk.h"
#include <QRect>
#include "../multimedia.h"
#include <QFrame>
#include <QFile>
#include <QHash>

class CJvsSDK : public CMultimedia
{
public:
    CJvsSDK( );
    ~CJvsSDK( );

    virtual int SystemStartup( HWND hOverlayWnd = NULL );
    virtual int SystemShutdown( );
    virtual HANDLE OpenChannel( int nChannelNum );
    virtual int CloseChannel( HANDLE hChannel );
    virtual int PlayVideo( HANDLE hChannel, HWND hWnd, QRect &rect, int nIndex );
    virtual int StopVideo( HANDLE hChannel );
    virtual int CaptureBMP( HANDLE hChannel, QString& strFile );
    virtual int CaptureJpeg( HANDLE hChannel, QString& strFile );
    virtual int GetYuv422Data( HANDLE hChannel, quint8* pData, ULONG& lSize );
    virtual int RegisterStreamCB( HK_STREAM_CB pCBF, PVOID pContext );
    virtual int GetStreamData( HANDLE hChannel, BOOL bStart, quint8 *pData, int nIndex );
    virtual int MotionDetection( HANDLE hChannel, bool bStart );
    virtual int SetupDetection( HANDLE hChannel, HK_MOTION_CB pCBF, int nIndex = 0, LPVOID pContext = NULL );

protected:
    virtual void GetParameters( );
    void GetFunctionPointer( );

private:
    HMODULE hDllMod;

private:
    typedef int WINAPI ( *JVSInitSDK ) (  );
    typedef int WINAPI ( *JVSReleaseSDK ) (  );

    typedef BOOL 	WINAPI ( *JVSOpenChannel ) ( int nChannel );
    typedef void 	WINAPI ( *JVSClosenChannel ) ( int nChannel );

    typedef BOOL 	WINAPI ( *JVSInitPreview ) (  );
    typedef void 	WINAPI ( *JVSSetVideoPreview ) ( int nChannel, HWND hWnd, RECT * rt, BOOL bPreview );
    typedef void 	WINAPI ( *JVSReleasePreview ) (  );
    typedef void WINAPI ( *JVSSetVideoPixelMode ) ( int nChannel, DWORD dwPixelMode, DWORD dwVideoFormat );

    typedef BOOL WINAPI ( *JVSGetBitmapSize ) (int nChannel, DWORD * dwWidth, DWORD * dwHeight );
    typedef BOOL WINAPI ( *JVSGetBitmap ) ( int nChannel, PUCHAR pBuffer );
    typedef void WINAPI ( *JVSSetQualityMode ) ( int nChannel, DWORD dwQualityMode, DWORD dwMBPH );
    typedef void	WINAPI ( *JVSRegisterNotify ) (HWND hWnd, DWORD dwNotifyMsg );
    typedef BOOL WINAPI ( *JVSGetBitmapToFile ) ( int nChannel, PUCHAR pCapBmpFile );

    typedef void WINAPI ( *JVSSetMovDetect ) ( int nChannel, int nScenecutGrade, int nScenecutThreshold, int nScenecutCoeff, int nRectNumber, RECT * pScenecutRect );
    typedef void WINAPI ( *JVSSetCallBack ) ( CALLBACK_ENC_DATA cbEncData, CALLBACK_RAW_DATA cbRawData );

    JVSInitSDK pJVSInitSDK;
    JVSReleaseSDK pJVSReleaseSDK;

    JVSOpenChannel pJVSOpenChannel;
    JVSInitPreview pJVSInitPreview;
    JVSSetVideoPreview pJVSSetVideoPreview;
    JVSClosenChannel pJVSClosenChannel;
    JVSReleasePreview pJVSReleasePreview;
    JVSSetVideoPixelMode pJVSSetVideoPixelMode;

    JVSGetBitmapSize pJVSGetBitmapSize;
    JVSGetBitmap pJVSGetBitmap;
    JVSSetQualityMode pJVSSetQualityMode;
    JVSRegisterNotify pJVSRegisterNotify;
    JVSGetBitmapToFile pJVSGetBitmapToFile;

    JVSSetMovDetect pJVSSetMovDetect;
    JVSSetCallBack pJVSSetCallBack;

    QHash< HANDLE, HWND > wndHash;
};

#endif // JVSSDK_H
