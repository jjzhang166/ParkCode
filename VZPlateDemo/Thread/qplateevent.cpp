#include "qplateevent.h"

QPlateEvent::QPlateEvent( Type evtType ) : QEvent( evtType )
{
    nImageFormat = 0;
    nInOutChannel = -1;
    nVideoWidth = 0;
    nVideoHeight = 0;
    bMultiThread = false;
    bIpcVideoSource = false;
    bDeleteFile = false;
}

void QPlateEvent::SetFilePath( QString &strFile )
{
    strPicFile = strFile;
}

QString& QPlateEvent::GetFilePath( )
{
    return strPicFile;
}

void QPlateEvent::SetIpcIp( QString& strIp )
{
    strIpcIp= strIp;
}

QString& QPlateEvent::GetIpcIp( )
{
    return strIpcIp;
}

void QPlateEvent::SetVideoFrame( QByteArray &byVideo )
{
    byVideoFrame.append( byVideo );
}

QByteArray& QPlateEvent::GetVideoFrame( )
{
    return byVideoFrame;
}

void QPlateEvent::SetImageFormat( int nFormat )
{
   nImageFormat = nFormat;
}

int QPlateEvent::GetImageFormat( )
{
    return nImageFormat;
}

void QPlateEvent::SetChannel( int nChannel )
{
    nInOutChannel = nChannel;
}

int QPlateEvent::GetChannel( )
{
    return nInOutChannel;
}

void QPlateEvent::SetVideoWidth( int nWidth )
{
    nVideoWidth = nWidth;
}

int QPlateEvent::GetVideoWidth( )
{
    return nVideoWidth;
}

void QPlateEvent::SetVideoHeight( int nHeight )
{
    nVideoHeight = nHeight;
}

int QPlateEvent::GetVideoHeight( )
{
    return nVideoHeight;
}

void QPlateEvent::SetByData( QByteArray& byData )
{
    bySerialData = byData;
}

QByteArray& QPlateEvent::GetByData( )
{
    return bySerialData;
}

void QPlateEvent::SetIpcVideoSource( bool bIPC )
{
    bIpcVideoSource = bIPC;
}

bool QPlateEvent::GetIpcVideoSource( )
{
    return bIpcVideoSource;
}

void QPlateEvent::SetMultiThread( bool bMulti )
{
   bMultiThread = bMulti;
}

bool QPlateEvent::GetMultiThread( )
{
    return bMultiThread;
}

void QPlateEvent::SetDeletFile( bool bDelete )
{
    bDeleteFile = bDelete;
}

bool QPlateEvent::GetDeletFile( )
{
    return bDeleteFile;
}
