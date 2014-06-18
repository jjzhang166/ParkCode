// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the USBCAMERADLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// USBCAMERADLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifndef USBCAMERA_DLL_API
#define USBCAMERA_DLL_API
#include <windows.h>
#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

typedef void ( CALLBACK *FrameDataCB ) ( LPBYTE pFrameData, long lFrameSize, long lWidth, long lHeight );

    WINBASEAPI BOOL WINAPI StartUsbCamera( int nDeviceIndex );
    WINBASEAPI BOOL WINAPI StopUsbCamera( BOOL bReleaseResource );
    WINBASEAPI std::vector< std::string > WINAPI GetDeviceList( FrameDataCB pfFrameDataCB, HWND hOwnerWnd );
    WINBASEAPI BOOL WINAPI GetDeviceList2( char* pDeviceList, int& nBufSize, FrameDataCB pfFrameDataCB, HWND hOwnerWnd );

#ifdef __cplusplus
}
#endif

#endif
