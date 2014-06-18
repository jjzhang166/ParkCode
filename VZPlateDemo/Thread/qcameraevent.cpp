#include "qcameraevent.h"

QCameraEvent::QCameraEvent(Type evtType) : QEvent(evtType)
{
    hVideoWnd = NULL;
    hParentWnd = NULL;
    nChannelNumber = -1;
    bRecognize = false;
    bMainStream = false;
    bRealStream = true;
}

void QCameraEvent::SetChannel( int nChannel )
{
    nChannelNumber = nChannel;
}

int QCameraEvent::GetChannel( )
{
    return nChannelNumber;
}

void QCameraEvent::SetVideoWndHandle( HWND hWnd )
{
    hVideoWnd = hWnd;
}

HWND QCameraEvent::GetVideoWndHandle( )
{
    return hVideoWnd;
}

void QCameraEvent::SetParentWndHandle( HWND hWnd )
{
    hParentWnd = hWnd;
}

HWND QCameraEvent::GetParentWndHandle( )
{
    return hParentWnd;
}

void QCameraEvent::SetImgFile( QString& strFile )
{
    strImgFile = strFile;
}

QString& QCameraEvent::GetImgFile( )
{
    return strImgFile;
}

void QCameraEvent::SetIpcIp( QString& strIP )
{
    strIPCIP = strIP;
}

QString& QCameraEvent::GetIpcIp( )
{
    return strIPCIP;
}

void QCameraEvent::SetRecognize( bool bRecog )
{
    bRecognize = bRecog;
}

bool QCameraEvent::GetRecognize( )
{
    return bRecognize;
}

void QCameraEvent::SetMainStream( bool bMain )
{
    bMainStream = bMain;
}

bool QCameraEvent::GetMainStream( )
{
    return bMainStream;
}

void QCameraEvent::SetRealStream( bool bReal )
{
    bRealStream = bReal;
}

bool QCameraEvent::GetRealStream( )
{
    return bRealStream;
}
