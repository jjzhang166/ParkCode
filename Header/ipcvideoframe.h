#ifndef IPCVIDEOFRAME_H
#define IPCVIDEOFRAME_H

#include <QFrame>
#include <QResizeEvent>
#include <QCloseEvent>
#include "./HKIPC/qhkipcthread.h"
#include "./JWSIPC/qjwsipcthread.h"
#include "./JbIPC/qjbipc.h"
#include "./AllInOne/qvzallinone.h"

namespace Ui {
class CIPCVideoFrame;
}

class CIPCVideoFrame : public QFrame
{
    Q_OBJECT
    
public:
    explicit CIPCVideoFrame( bool bIPC, QWidget *parent = 0);
    ~CIPCVideoFrame();
    void LocalIPCStartVideo( QString& strIP, HWND hPlayWnd, int nChannel );
    void LocalIPCStopVideo( HWND hPlayWnd );
    void LocalIPCLogout( );
    void LocalIPCLogin( );

    void CapturePreviewImage( HWND hPlayWnd, QString& strFileName );
    void CaptureDeviceImage( QString& strIP, QString& strFileName, HWND hPlayWnd );

protected:
    void resizeEvent( QResizeEvent * event );
    void closeEvent( QCloseEvent * event );
    void showEvent( QShowEvent * event );

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_btnOpen_clicked();

    void on_btnClose_clicked();

    void on_btnOpenAll_clicked();

    void on_btnCloseAll_clicked();

    void HandleNotifyMessage( QString strMsg );
    void HandleUIPlateResult( QString strPlate, int nChannel, bool bSuccess,
                              bool bVideo, int nWidth, int nHeight, int nConfidence,
                              QString strDirection, QByteArray byData, QRect rectPlate, QRect rectVideo );

signals:
    void NotifyMessage( QString strMsg );
    void UIPlateResult( QString strPlate, int nChannel, bool bSuccess,
                              bool bVideo, int nWidth, int nHeight, int nConfidence,
                              QString strDirection, QByteArray byData, QRect rectPlate, QRect rectVideo );

private:
    typedef QMultiHash< QString, QString > QHostIPCHash;
    typedef QMultiHash< int, QString > QHostIPCName;

    void InitializeIPC( );
    void UninitializeIPC( );

    void LoginIPC( const QString& strIP );
    void LogoutIPC( const QString& strIP );

   void StartPlayIPC( const QString& strIP, HWND hPlayWnd, int nChannel = 1, bool bChannel = false );
    void StopPlayIPC( HWND hPlayWnd );

    void GetHostIPC( );
    void LogIPC( bool bLocal, bool bLogin );
    void VideoIPC( bool bPlay );

    void FillTable( );
    void OperateGate( bool bOpen, bool bAll );
    
private:
    Ui::CIPCVideoFrame *ui;
    QIPCThread* pVideoThread;
    QHostIPCHash hashHostIPC;
    QHostIPCName hashIPCName;
    QHostIPCName hashIPCIP;
    bool bNetworkCamera;
    QRect recSmallSize;
    QRect recBigSize;
    QSettings* pSettings;
};

#endif // IPCVIDEOFRAME_H
