#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QRect>
#include "Multimedia/multimedia.h"
#include "Thread/qanalogcamerathread.h"

class CMyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CMyLabel( int nIndexFps, const QRect& rect, bool bIPC, QWidget *parent = 0 );

    void SetParams( HANDLE hChannelHk, CMultimedia* pMultiHk );
    void SetParams( int nChannel, QAnalogCameraThread* pAnalog );

protected:
     void  mouseDoubleClickEvent ( QMouseEvent *  );

private:
     void mouseDoubleClickEvent4NewVideo( );

private:
     bool bSwitch;
     QRect recRawSize;
     QRect recWholeSize;
     QWidget* pParent;
     HANDLE hChannel;
     int nChannel;
     CMultimedia* pMulti;
     QAnalogCameraThread* pCamera;
     bool bIPCVideo;
     int nIndex;

signals:
     void HideCtrl( int nIndex, bool bVisible );

public slots:

};

#endif // MYLABEL_H
