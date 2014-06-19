#ifndef AVSDK_H
#define AVSDK_H
#include "Multimedia_global.h"
#ifdef _WIN32
#include <windows.h>
#endif

#include <QRect>

class MULTIMEDIASHARED_EXPORT CAvSdk
{
public:
    CAvSdk();
    virtual ~CAvSdk( );

    typedef enum __AvSdk {
        HikSdk,
    } AvSdk;

public:
    static CAvSdk* CreateInstance( AvSdk sdkType );
    static void DestroyInstance( CAvSdk* pInstance );
    virtual int SystemStartup( ) = 0;
    virtual int SystemShutdown( ) = 0;
    virtual HANDLE OpenChannel( int nChannelNum ) = 0;
    virtual int CloseChannel( HANDLE hChannel ) = 0;
    virtual int PlayVideo( HANDLE hChannel, HWND hWnd, QRect& rect, int nFrameRate ) = 0;
    virtual int StopVideo( HANDLE hChannel ) = 0;
};

#endif // AVSDK_H
