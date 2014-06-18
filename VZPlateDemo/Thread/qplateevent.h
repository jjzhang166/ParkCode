#ifndef QPLATEEVENT_H
#define QPLATEEVENT_H

#include <QEvent>
#include <QString>
#include <QByteArray>

class QPlateEvent : public QEvent
{
public:
    typedef enum __PlateEventType {
        PlateVideoRecognize = User,
        PlateFileRecognize,
        PlateInit,
        PlateUninit
    } PlateEventType;

public:
    QPlateEvent( Type evtType );

    void SetFilePath( QString& strFile );
    QString& GetFilePath( );

    void SetIpcIp( QString& strIp );
    QString& GetIpcIp( );

    void SetVideoFrame( QByteArray& byVideo );
    QByteArray& GetVideoFrame( );

    void SetImageFormat( int nFormat );
    int GetImageFormat( );

    void SetChannel( int nChannel );
    int GetChannel( );

    void SetVideoWidth( int nWidth );
    int GetVideoWidth( );

    void SetVideoHeight( int nHeight );
    int GetVideoHeight( );

    void SetByData( QByteArray& byData );
    QByteArray& GetByData( );

    void SetIpcVideoSource( bool bIPC );
    bool GetIpcVideoSource( );

    void SetMultiThread( bool bMulti );
    bool GetMultiThread( );

    void SetDeletFile( bool bDelete );
    bool GetDeletFile( );

private:
    QString strPicFile;
    QByteArray byVideoFrame;
    int nImageFormat;
    int nInOutChannel;
    int nVideoWidth;
    int nVideoHeight;
    QByteArray bySerialData;
    QString strIpcIp;
    bool bIpcVideoSource;
    bool bMultiThread;
    bool bDeleteFile;
};

#endif // QPLATEEVENT_H
