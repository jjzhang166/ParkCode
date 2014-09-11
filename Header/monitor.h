#ifndef MONITOR_H
#define MONITOR_H

#include <QFrame>
#include <QShowEvent>
#include <QCloseEvent>
#include "mainwindow.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"
#include "Multimedia/multimedia.h"
#include <QGraphicsView>
#include <QListView>
#include "Common/CommonType.h"
#include "Header/mylabel.h"
#include "Dialog/dlgalert.h"
#include "ipcvideoframe.h"
#include <QHash>

#include "Thread/qhkcapturecardthread.h"
#include "Thread/qtmcapturecardthread.h"
#include "Thread/qplatethread.h"

//#include "VehicleLicense/vehiclelicense.h"

#define ENCODECHANNEL ( int ) ( 4 )
#define VIDEO_USEDWAY ( int ) ( 4 )
#define VIDEO_BUF     ( int ) ( 1024 * 1024 * 2 )
#define RECOG_RES     ( int ) ( 6 )

namespace Ui {
    class
#if defined( NewUI )
    CONCAT_NEW_NAME( New, CMonitor );
#else
    CONCAT_NEW_NAME( , CMonitor );
#endif
}

class CMonitor : public QFrame
{
    Q_OBJECT

public:
    explicit CMonitor( QWidget* mainWnd, QWidget *parent = 0);
    ~CMonitor();

    bool AllInOneIPIO( char cCan, bool bOpen );
    void DisplayRemoteUI( );

    void SetFileCount( quint32 nCount );
    void PictureRegconize( QString& strFile, int nChannel, QByteArray& byData );

    void ClearStatistics( );
    void ControlSelf( );
    void ControlChargeInfo( QStringList& strInfo );
    void GetParkName( QString& strName, char cCan, int nIndex );
    void LoadCapturedImg( QString& strPath, int nChannel );
    void CaptureImage( QString& strFile, int nChannel, CommonDataType::CaptureImageType capType );
    void CaptureNewImage( QString& strFile, int nChannel, CommonDataType::CaptureImageType capType );
    void GetInOutPixmap( QPixmap& bmpEnter, QPixmap& bmpLeave );
    void UpdateStatistics( int nNumber, int nIndex, bool bInit = false );

    void DisplayPlate( int nChannel );
    void SetBallotSense( bool bSense, int nChannel, QByteArray& byData );
    void SetNewBallotSense( bool bSense, int nChannel, QByteArray& byData );
    void SetMenu( QList< QMenu* >& lstMenu );

    void ControlDetection( int nChannel, bool bStart );

    void StartIPC( );
    void StopIPC( );

    void ManualIPC( );

    void IPCVideo( bool bPlayVideo );

    void StartAvSdk( );
    void StopAvSdk( );

    void StartNewAvSdk( );
    void StopNewAvSdk( );

    void StartPlateRecog( );
    void StopPlateRecog( );

    void StartNewPlateRecog( );
    void StopNewPlateRecog( );

    QLabel* GetDateTimeCtrl( );
    void FillDataGrid( QStringList& lstData );
    void DisplayAlert( QStringList& lstData );
    static void PlateFilter2( int nChannel );
    void SetAlertMsg( const QString& strText );
    void HideAlert( );
    void ControlGateButton( );
    void WriteFrameInfo( QString& strInfo );
    //static void PrcCapSourceStream1( long lnCardID, long pBuf, long lnWidth, long lnHeight, long lnBiCount );
    void SavePicture( QString& strFile );

    static bool bStartRecognization[ VIDEO_USEDWAY ];
    //static bool bPlateFilter[ VIDEO_USEDWAY ];
    //static bool bSuccession[ VIDEO_USEDWAY ];
    static bool GetPlateSuccession( bool bFilter, int nIndex );
    static QString strPlates[ VIDEO_USEDWAY ];
    bool bNocardwork;
    bool bSenseGate;

protected:
    void closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void showEvent(QShowEvent *);
    void CalculatePos( );
    void ControlDataGrid( QTableWidget& tw );
    void keyPressEvent ( QKeyEvent * event );

private:
    void GetAllParkSpaceLot( bool bChannel, bool bEnter = true );
    void InitChannelHandle( );
    void GetFileName( QString& strFileName, QString strExt );
    void SetGateImg( bool bOpen, bool bEnter );
    inline void GetImgBasePath( QString& strPath );
    void LoadImg( );
    void LoadVideoWndBg( qint32 nIndex );
    void InitVideoPlateUI( );
    int GetInsideCard( QStringList& lstRows );
    void GetDefaultParkInfo( );
    void LoadUIImage( );
    void SwitchImage( QPushButton* pBtn, bool bDown, bool bPermission = true );
    void LoadDigital( int nGroup/*1-4*/, int nDigital/*0000-9999*/, char cColor/*r,g,b*/ );
    bool PlateFilter( int nChannel, TH_PlateResult*& pResult );

    //CVehicleLicense* GetPlateRecognization( );
    void InitStatistics( );

    static void MotionDetection( ULONG nChannel, BOOL bMotionDetected, void *context );
    static void ImageStreamCallback( UINT nChannel, PVOID pContent );

    //static void MyPrcCbMotionDetect( long lnCardID, BOOL bMove, LPVOID lpContext );
    //static void PrcCapSourceStream( long lnCardID, long pBuf, long lnWidth, long lnHeight, long lnBiCount );
    static void PrcCapSourceStream( DWORD dwCard, BYTE *pbuff, DWORD dwSize );

    void GetCanParkIndexNum( );

    void PublishSpaceInfo( int nTotal, int nUsed );

private:
    //static quint8 imgData[ VIDEO_USEDWAY ][ VIDEO_BUF ];
    static TH_PlateResult recogResult[ VIDEO_USEDWAY ][ RECOG_RES ];
    static TH_PlateResult structPlates[ VIDEO_USEDWAY ];
    QLabel* lblDirection[ VIDEO_USEDWAY ];
    QLabel* lblMoving[ VIDEO_USEDWAY ];
    QLabel* lblVideoWnd[ VIDEO_USEDWAY ];
    QLabel* lblLicense[ VIDEO_USEDWAY ][ 8 ];
    QHash< QString, int > plateResult[ 4 ][ 8 ];
    int nCanAddressWinIndex[ VIDEO_USEDWAY ];

    bool bPlateStart[ VIDEO_USEDWAY ];
    bool bBallotSense[ ENCODECHANNEL ];
    int nUsedWay;
    QLabel* lblStatistics[ 6 ];
    int nCurrentTotal[ 6 ];
    QString strCapture;
    int nCapture;
    bool bMultiThread;
    QPlateThread* pPlateThread;
    bool bDongleOneWay;

    //bool bPlateFilter[ VIDEO_USEDWAY ];
    //bool bSuccession[ VIDEO_USEDWAY ];

    CIPCVideoFrame* ipcVideoFrame;
    QAnalogCameraThread* pNewAnalogVideo;
    CDlgAlert* pDlgAlert;
    bool bDisplayAlert;
    int nRefreshParkspaceTime;
    bool bPlateVideo;
    bool bSavePicture;
    bool bNetworkCamera;

#if defined( NewUI )
    Ui::CONCAT_NEW_NAME( New, CMonitor )
#else
    Ui::CONCAT_NEW_NAME( , CMonitor )
#endif
     *ui;
    MainWindow* pParent;
    QStringList lstRows;
    HANDLE hChannelHandle[ ENCODECHANNEL ];
    CMultimedia* pMultimedia;
    //CVehicleLicense* pVehicle;
    QString strImagePath;
    QString strRegPicPath;
    QString strButtonStyle;
    int nEncode;
    QStringList lstPark;
    int nTotalParkSpace;
    QString strParkName;
    QString strUserID;
    QSettings* pSysSet;
    QSettings* pSystem;
    int nRealTimeRecord;
    QStringList lstEnterCanOpen;
    QStringList lstEnterCanClose;
    QStringList lstLeaveCanOpen;
    QStringList lstLeaveCanClose;
    bool bPlateBox;

    inline void ReadDefaultCan( QStringList& lstCan, bool bEnter, bool bOpen );
    inline void WriteDefaultCan( QStringList& lstCan, bool bEnter, bool bOpen );
    bool ConfigDefaultCan( QStringList& lstCan, bool bEnter, bool bOpen );
    QStringList& GetDefaultGateCan( bool bEnter, bool bOpen );
    void CreateGateButton( );

    void PlayVideo( int nIndex, QFrame* pVideo );
    void StopVideo( int nIndex );
    inline void ControlGate( bool bOpen, bool bEnter, QObject* sender );
    void SetDlgBackground( QDialog& dlg );
    void StartSpaceTimer( );

    void VerifyClecked( int nChannel );
    void PlateSort( QHash< QString, int > hash[ ], QString& strPlate );
    void ReplacePlateChinese( QString& strPlate );

private slots:
    void GateButtonRightClicked( );
    void on_tabRecord_cellDoubleClicked(int row, int column);
    void onBtnVerifyInClicked();
    void onBtnVerifyOutClicked();
    void on_btnPass_clicked();
    void onLinkActivated(QString link);
    void on_btnDispatcherClose_clicked();
    void on_btnBarcode_clicked();
    void on_btnDispatcherOpen_clicked();
    void on_btnGate3Channel_clicked();
    void on_btnGateChannel2_clicked();
    void on_btnGateChannel1_clicked();
    void on_btnDispatcherInfo_clicked();

    void GateClose2(  );
    void GateOpen2(  );
    void GateClose1(  );
    void GateOpen1(  );
    void ChangeUser( QString& strUser, QString& strID );
    void BtnPressed( );
    void BtnReleased( );
    void BtnPermission( bool bNormal, int nIndex );
    void DirectionIndicator( int nChannel, bool bMoving );
    void OnClickedDlgPopup( );
    void SpaceInfo(  );
    void PlateCheck( QString strChar, int nChannel, int nIndex );
    void ManualRecogonization( int nChannel);
    void ManualRecogonization( int nChannel, QString strPlate );
    void HideCtrl( int nIndex, bool bVisible );
    void ClearPlate( int nPlateChannel );
    void DisplayDbError( QString strMsg );
    void HandleIPCMsg( QString strMsg );
    void HandleUIPlateResult( QString strPlate, int nChannel, bool bSuccess,
                              bool bVideo, int nWidth, int nHeight, int nConfidence,
                              QString strDirection, QByteArray byData, QRect rectPlate, QRect rectVideo );
    void HandleDetectInfo( int nChannel, bool bMotion );

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public:
signals:
    void OnRecognizePlate( QString strPlate, int nChannel, int nConfidence, bool bNocard, QByteArray byData );
    void OnDirectionIndicator( int nChannel, bool bMoving );
};

#endif // MONITOR_H
