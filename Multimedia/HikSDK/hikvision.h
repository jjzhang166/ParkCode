#ifndef HIKVISION_H
#define HIKVISION_H
#ifdef _WIN32
#include <windows.h>
#endif
#include "HikVisionSdk.h"
#include <QRect>
#include "../multimedia.h"
#include <QFrame>
#include <QFile>

class CHikVision : public CMultimedia
{
    //Q_OBJECT
public:
    CHikVision();
    virtual ~CHikVision( );

public:
    int SystemStartup( HWND hOverlayWnd = NULL );
    int SystemShutdown( );
    HANDLE OpenChannel( int nChannelNum );
    int CloseChannel( HANDLE hChannel );
    int PlayVideo( HANDLE hChannel, HWND hWnd, QRect &rect, int nIndex );
    int StopVideo( HANDLE hChannel );
    int CaptureBMP( HANDLE hChannel, QString& strFile );
    int CaptureJpeg( HANDLE hChannel, QString& strFile );
    int GetYuv422Data( HANDLE hChannel, quint8* pData, ULONG& lSize );
    int RegisterStreamCB( HK_STREAM_CB pCBF, PVOID pContext );
    int GetStreamData( HANDLE hChannel, BOOL bStart, quint8 *pData, int nIndex );
    int MotionDetection( HANDLE hChannel, bool bStart );
    int SetupDetection( HANDLE hChannel, HK_MOTION_CB pCBF, int Index = 0, LPVOID pContext = NULL );

    void WriteH264Data( ULONG lChannel,void *DataBuf,DWORD Length, int FrameType );
    //static int CALLBACK StreamDirectReadCallback(ULONG channelNumber,void *DataBuf,DWORD Length,int FrameType,void *context);

protected:
    void GetParameters( );

private:
    void OpenFile( bool bWriteHeader = false );
    void CloseFile( );

private:
    bool bRecorder;
    QFile fInChannel;
    QFile fOutChannel;
    QByteArray byInHeader;
    QByteArray byOutHeader;
};

#endif // HIKVISION_H
