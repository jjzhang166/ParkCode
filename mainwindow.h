#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define CONCAT_NEW_NAME( Prefix, Suffix ) Prefix##Suffix

#include <QMainWindow>
#include <QMdiArea>
#include <QSignalMapper>
#include <QMap>
#include <QString>
#include <QWidget>
#include <QFrame>
#include <QCloseEvent>
#include <QTableWidget>
#include "Header/logindialog.h"
#include "Common/CommonType.h"
#include <QTimer>
#include <QLabel>
#include "Common/logicinterface.h"
#include "SerialPort/winserialport.h"
#include "Database/mysqldatabase.h"
#include <QLineEdit>
#include <QSettings>
#include <QShowEvent>
#include "Network/svrthread.h"
#include "Heartbeat/heartbeatthread.h"
#include "license/checkthread.h"
#include "qserialframe.h"

namespace Ui {
    class MainWindow;
    typedef QMap<QString, QWidget* > childMap;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0 );//= Qt::FramelessWindowHint );
    ~MainWindow();

    void SetFileCount( quint32 nCount );
    void PictureRegconize( QString &strFile, int nChannel, QByteArray& byData );
    void ControlChild( QCloseEvent* event, QWidget* child );
    void ControlMonitor( bool bShow );
    CLogicInterface* GetLogicInterface( );
    void GetAppInfo( CommonDataType::AppInfoType appInfo, QString& strInfo );
    void WriteLog( QString strType, QString& strContent, CommonDataType::SysLogType logType, QDateTime& dtDateTime, char cCan = 0 );
    QString GetUserName( );
    void GetParkName( QString& strName, char cCan, int nIndex );

    CMySqlDatabase* GetMysqlDb( );
    CWinSerialPort* GetSerialPort( );
    bool SetCardNumber( QString& strNumber );
    void SetCardControl( QLineEdit* edtCtrl );
    void ControlChargeInfo( QStringList& strInfo );
    QPixmap& GetPixmap( QString& strFile );
    void CaptureImage( QString& strFile, int nChannel, CommonDataType::CaptureImageType capType );
    void LoadCapturedImg( QString& strPath, int nChannel );
    void GetInOutPixmap(QPixmap &bmpEnter, QPixmap &bmpLeave);
    void UpdateStatistics( int nNumber, int nIndex );
    void EmployeeCard( QString& strCardno );
    QString GetCurrentUserID( );

    void SetBallotSense( bool bSense, int nChannel, QByteArray& byData );
    void SendInOutImg( QString& strFile, bool bEnter, QDateTime& dtCurrent, QString& strPlate, QString& strCardNo );
    void SetAlertMsg( const QString& strText );
    bool ShiftDlgISVisible( );
    void DisplayAlert( QStringList& lstData );
    QString GetPictureName( QString strName );

private:
    void SetMaxMinSize( );
    void ClearAllFiles( );
    void ModiyToobar( );
    void CreateChildren( );
    void ControlDatabase( bool bOpen );
    void ControlSerial( bool bOpen );
    void CheckCenterContronller( );
    void Singleton( );
    void CheckResolution( );
    void HideCtrl( bool bVisible = true );
    void GetCardEntityInfo( );
    void SyncTime( QStringList& lstData );
    void StartSycnTime( );
    void InitPMS( );
    void ClearStatistics( QTime& time );
    void SetDateTimeFormat( );
    void ServerFunction( );
    void ClientFunction( );
    void GatherData( );
    void ForwardPassRecord( QStringList& lstData );
    void StartLicense( );
    bool GenerateLicense( QString& strSpecialUser, QString& strSpecialPwd );
    void RegisterAxCtrl( );
    void StartupMgmt( );

protected:
    void closeEvent( QCloseEvent* event );
    void showEvent(QShowEvent *);

private:
    QWidget* CreateChildWnd( CommonDataType::ChildWndType childType );
    void ShowWnd( CommonDataType::ChildWndType childType );
    void Login( bool bStart );
    void WriteShiftLog( bool bLogin );
    void Permission( );
    void IconLoad( QWidget& frame );
    void LoadUIImage( );
    void CreateChildTime( quint64 nTime, CommonDataType::ChildWndType childType );
    void ProcessCpuidRequest( QStringList& lstData );
    void ProcessGateCommand( QStringList& lstData );
    CMySqlDatabase* pMysqlDb;
    QLineEdit* edtCardNumner;
    CCheckThread* pCheckThread;

private:
    Ui::MainWindow *ui;
    QMdiArea *pMdiArea;
    QSignalMapper *pWindowMapper;
    Ui::childMap* pChildMap;
    CLoginDialog* pDlgLogin;
    QString strUserName;
    QString strUserPwd;
    QTimer* pTimer;
    QLabel* pLblTime;
    QString strTimeText;
    QString strIconPath;
    CWinSerialPort *pSerialPort;
    QSettings* pSettings;
    CLogicInterface* pLogicInterface;
    bool bSyncServer;
    CSvrThread* netServer;
    QString strPassRecord;
    QString strParkID;
    int nTransferRecord;
    bool bToInternet;
    bool bAlert;
    QSerialFrame frmSerial;

private slots:
#if false
    void on_actStopPlateTwo_triggered();
    void on_actStopPlateOne_triggered();
    void on_actStartPlateTwo_triggered();
    void on_actStartPlateOne_triggered();
    void on_actStopVideoTwo_triggered();
    void on_actStopVideoOne_triggered();
    void on_actStartVideoTwo_triggered();
    void on_actStartVideoOne_triggered();
#endif
    void on_actRestart_triggered();
    void on_actShiftLogout_hovered();
    void on_actPublishLEDInfo_triggered();
    void on_actSyncTime_triggered();
    void on_actStartPlate_triggered( );
    void on_actStopPlate_triggered( );
    void on_actStartVideo_triggered( );
    void on_actStopVideo_triggered( );
    void on_actConnectDb_triggered();
    void on_actPlateRecognizationSet_triggered();
    void on_actSerialPort_triggered();
    void on_actBlacklist_triggered();
    void on_actDocment_triggered();
    void on_actAbout_triggered();
    void on_actHandheldICProcess_triggered();
    void on_actPrintYearlyReport_triggered();
    void on_actPrintMonthlyReport_triggered();
    void on_actPrintDaylyReport_triggered();
    void on_actDiscountSummaryReport_triggered();
    void on_actReewalRecords_triggered();
    void on_actAccess2Records_triggered();
    void on_actTimeCard_triggered();
    void on_actValueCard_triggered();
    void on_actMonthlyCard_triggered();
    void on_actSysExit_triggered();
    void on_actPwdModification_triggered();
    void on_actSysLog_triggered();
    void on_actDBMaintenance_triggered();
    void on_actTariffSetting_triggered();
    void on_actRightMgm_triggered();
    void on_actShiftLogout_triggered();
    void on_actTollDiscountTypeSet_triggered();
    void on_actBatchSetCardAccess_triggered();
    void on_actSysSetting_triggered();
    void on_actDeviceConfig_triggered();
    void DataMayRead();
    void ProcessDatagram( QStringList& lstData );
    void ProcessMonitorMsg( CommonDataType::DatagramType nType, QStringList& lstData);
    void UpdateLableText(  );
    void SendStateHB( );
    void ReconnectDatabase( );
    void RecognizePlate( QString strPlate, int nChannel, int nConfidence, bool bNocard, QByteArray byData );
    void SendTime( );
    void Expiration( QString strMsg, bool bExpiration, bool bRetry );

    void on_actLicense_triggered();

    void on_actStay_triggered();

    void on_actRemoteMgmt_triggered();

    void on_actIPC_triggered();

signals:
    void OnUserChanged( QString& strUser, QString& strID );
    void OnPermission( bool bNormal, int nIndex );

    void OnStartDlg( );
    void OnDestroyDlg( );
    void OnUpdateInfo( QString strInfo );
};

#endif // MAINWINDOW_H
