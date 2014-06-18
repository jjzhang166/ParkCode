#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Header/shiftlogout.h"
#include "Header/rightmgm.h"
#include "Header/tariffsetting.h"
#include "Header/dbmaintenance.h"
#include "Header/syslog.h"
#include "Header/pwdmodification.h"
#include "Header/monthlycard.h"
#include "Header/valuecard.h"
#include "Header/timecard.h"
#include "Header/publishledinfo.h"
#include "Header/deviceconfig.h"
#include "Header/syssetting.h"
#include "Header/batchsetcardaccess.h"
#include "Header/tolldiscounttypeset.h"
#include "Header/access2records.h"
#include "Header/reewalrecords.h"
#include "Header/discountsummaryreport.h"
#include "Header/printdaylyreport.h"
#include "Header/printmonthlyreport.h"
#include "Header/printyearlyreport.h"
#include "Header/handheldicprocess.h"
#include "Header/ipcvideoframe.h"
#include "Header/picturecontrast.h"
#include "Dialog/pwddialog.h"
#include "Dialog/ledinfodialog.h"
#include "Dialog/syssettingdialog.h"
#include "Header/blacklist.h"
#include "Dialog/handicdialog.h"
#include <QLabel>
#include "Dialog/passdlg.h"
#include "Dialog/recognizeparamdlg.h"
#include <Common/mytimer.h>

#include <QDebug>
#include <QDateTime>
#include <QtGui/QApplication>
#include "Common/commonfunction.h"
#include "Dialog/serialportdialog.h"
#include "SerialPort/processdata.h"
#include <QScreen>
#include <QDesktopWidget>
#include "Network/parkintranet.h"
#include "Network/ftp.h"

#include "startupthread.h"

#include <QProcess>
//#include "Lunar/SolarDate.h"
//#include "Lunar/ChineseDate.h"
#include "DbBackup/dbbackupthread.h"
#include "DbBackup/RdAutoDeleteThread.h"
#include "Network/localsvrcommunication.h"
#include "Network/localcltcommunication.h"
#include "Network/ftp.h"
#include "Dialog/dlgabout.h"
#include "Dialog/dlgmakelicense.h"
#include <QPushButton>
#include "CenterMgmt/mgmtthread.h"
#include "Dialog/dlgstaying.h"
#include "Timer/timerthread.h"

#include "Header/monitor.h"

CHeartbeatThread* g_pHeartbeatThread = NULL;
CLocalCltCommunication* g_pLocalCltComm = NULL;
CFtp* g_pFtp = NULL;

void MainWindow::SetFileCount( quint32 nCount )
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->SetFileCount( nCount );
}

void MainWindow::PictureRegconize( QString &strFile, int nChannel, QByteArray& byData )
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->PictureRegconize( strFile, nChannel, byData );
}

bool MainWindow::ShiftDlgISVisible( )
{
    bool bRet = false;
    if ( NULL != pDlgLogin ) {
        bRet = pDlgLogin->isVisible( );
    }

    return bRet;
}

void MainWindow::SetDateTimeFormat( )
{
    LCID localeID = ::GetSystemDefaultLCID( );

    BOOL bRet = ::SetLocaleInfo( localeID, LOCALE_SSHORTDATE, L"yyyy-M-d" );
    bRet = ::SetLocaleInfo( localeID, LOCALE_SDATE, L"-" );

    bRet = ::SetLocaleInfo( localeID, LOCALE_STIMEFORMAT, L"H:mm:ss" );
    bRet = ::SetLocaleInfo( localeID, LOCALE_STIME, L":" );

    QString strFormat = "yyyy'年'M'月'd'日' dddd";
    LPCWSTR lpLongFormat = ( LPCWSTR ) strFormat.utf16( );
    bRet = ::SetLocaleInfo( localeID, LOCALE_SLONGDATE, lpLongFormat );
}

void MainWindow::StartupMgmt( )
{
    bool bRet = pSettings->value( "Mgmt/MgmtTCP", false ).toBool( );
    if ( !bRet ) {
        return;
    }

    if ( pSettings->value( "Mgmt/StartupSenderThread", false ).toBool( ) ) {
        CMgmtThread::GetThread( true );
    } else if (  pSettings->value( "Mgmt/StartupReceiverThread", false ).toBool( ) ) {
        CMgmtThread::GetThread( false );
    }
}

void MainWindow::SetAlertMsg( const QString &strText )
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->SetAlertMsg( strText );
}

QString MainWindow::GetPictureName( QString strName )
{
    int nWidth = width( );
    int nHeight = height( );

    QString strTmp = "%1x%2";

    if ( 1440 == nWidth && 900== nHeight ) {
        strTmp.clear( );
    } else if ( 1366 == nWidth && 768 == nHeight ) {
        strTmp = strTmp.arg( QString::number( nWidth ), QString::number( nHeight ) );
    }

    return strName.arg( strTmp );
}

void MainWindow::LoadUIImage( )
{
    QString strStyle= "background-image:url(" + strIconPath + GetPictureName( "MainBG%1.jpg);" );
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->setStyleSheet( strStyle );

    //QString strMenuStyle = "QMenu::item{%1padding:5px;background-color: rgb(255, 255, 255);}";
    QList< QMenu* > lstMenu;

    lstMenu.append( ui->menuSysMgm );
    //QString strTmp =strMenuStyle.arg( "width:85px;" );
    //ui->menuSysMgm->setStyleSheet( strTmp );

    //strMenuStyle = strMenuStyle.arg( "" );
    lstMenu.append( ui->menuCardTicketsMgm );
    //ui->menuCardTicketsMgm->setStyleSheet( strMenuStyle );

    lstMenu.append( ui->menuAdvSetting );
    //ui->menuAdvSetting->setStyleSheet( strMenuStyle );

    lstMenu.append( ui->menuQueryReport );
    //ui->menuQueryReport->setStyleSheet( strMenuStyle );

    lstMenu.append( ui->menuHelp );
    //ui->menuHelp->setStyleSheet( strMenuStyle );

    pMonitor->SetMenu( lstMenu );
    pLblTime = pMonitor->GetDateTimeCtrl( );

    connect( this, SIGNAL( OnPermission( bool, int ) ), pMonitor, SLOT( BtnPermission( bool, int ) ) );
}

void MainWindow::UpdateStatistics( int nNumber, int nIndex )
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->UpdateStatistics( nNumber, nIndex );
}

void MainWindow::SyncTime( QStringList& lstData )
{
    if ( 9 > lstData.count( ) ) {
        return;
    }

    SYSTEMTIME sysTime;
    sysTime.wYear = lstData[ 1 ].toUShort( );
    sysTime.wMonth = lstData[ 2 ].toUShort( );
    sysTime.wDay = lstData[ 3 ].toUShort( );
    sysTime.wDayOfWeek = lstData[ 4 ].toUShort( );
    sysTime.wHour = lstData[ 5 ].toUShort( );
    sysTime.wMinute = lstData[ 6 ].toUShort( );
    sysTime.wSecond = lstData[ 7 ].toUShort( );
    sysTime.wMilliseconds = lstData[ 8 ].toUShort( );

    BOOL bRet = SetLocalTime( &sysTime );
    qDebug( ) << "SyncTime( ) " << ( bRet ? "Success" : "Failed" ) << endl;
}

void MainWindow::SendTime( )
{
    SYSTEMTIME sysTime;
    GetLocalTime( &sysTime );

    QStringList lstData;

    lstData << QString::number( sysTime.wYear )
                << QString::number( sysTime.wMonth )
                << QString::number( sysTime.wDay )
                << QString::number( sysTime.wDayOfWeek )
                << QString::number( sysTime.wHour )
                << QString::number( sysTime.wMinute )
                << QString::number( sysTime.wSecond )
                << QString::number( sysTime.wMilliseconds );

    CNetwork::Singleton( ).BroadcastDatagram( CommonDataType::DGSyncTime, lstData );
}

void MainWindow::StartSycnTime( )
{
    bSyncServer   = pSettings->value( "Database/Server", false ).toBool( );
    double dInterval = pSettings->value( "Database/IntervalTime", 24 ).toDouble( );

    if ( !bSyncServer ) {
        return;
    }
    //CStartupProcess::GetFrame( )->UpdateInfo( "同步时间！" );

    static QTimer timer;

    int nInterval = int ( dInterval * 3600 * 1000 );
    timer.setInterval( nInterval );
    connect( &timer, SIGNAL( timeout( ) ), this, SLOT( SendTime( ) ) );
    timer.start( );

    SendTime( );
}

QString MainWindow::GetUserName( )
{
    return strUserName;
}

void MainWindow::CheckResolution( )
{
    QDesktopWidget* pDesktop = QApplication::desktop( );
    QRect rect = pDesktop->screenGeometry( );
    int nWidth  = rect.width( );
    int nHeight = rect.height( );

    int nW = 1440;
    int nH = 900;

    if ( nW != nWidth || nH != nHeight ) {
        QString strInfo = QString( "请设置屏幕分辨率为: %1 X %2" ).arg(
                QString::number( nW ), QString::number( nH ) );
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 strInfo, QMessageBox::Information );
    }
}

void MainWindow::Singleton( )
{
    QString strGUID = "{063F5B37-7AA6-4E90-B658-36AAFBA7B8BE}";
    WCHAR cGUID[ 256 ] = { 0 };
    strGUID.toWCharArray( cGUID );
    HANDLE hEvent = CreateEvent( NULL, TRUE, FALSE, cGUID );
    DWORD dwError = GetLastError( );

    if ( NULL != hEvent && ERROR_ALREADY_EXISTS == dwError ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 "系统已启动！", QMessageBox::Information );
        exit( 0 );
    }

    //CheckResolution( );
}

void MainWindow::RecognizePlate( QString strPlate, int nChannel, int nConfidence, bool bNocard, QByteArray byData )
{
    CProcessData* pProcessor = CProcessData::GetProcessor( pSerialPort, this );

    if ( NULL == pProcessor ) {
        return;
    }

    pProcessor->RecognizePlate( strPlate, nChannel, nConfidence, bNocard, byData );
}

void MainWindow::GetParkName( QString &strName, char cCan, int nIndex )
{
    // CAN / PARKINDEX / PARKNUM / PARKNAME
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->GetParkName( strName, cCan, nIndex );
}

void MainWindow::LoadCapturedImg( QString& strPath, int nChannel )
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->LoadCapturedImg( strPath, nChannel );
}

void MainWindow::GetInOutPixmap(QPixmap &bmpEnter, QPixmap &bmpLeave)
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->GetInOutPixmap( bmpEnter, bmpLeave );
}

void MainWindow::CaptureImage( QString &strFile, int nChannel, CommonDataType::CaptureImageType capType )
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->CaptureImage( strFile, nChannel, capType );
}

CMySqlDatabase* MainWindow::GetMysqlDb( )
{
    return pMysqlDb;
}

CWinSerialPort* MainWindow::GetSerialPort( )
{
    return pSerialPort;
}

bool MainWindow::SetCardNumber( QString& strNumber )
{
    bool bRet = ( NULL != edtCardNumner );
    if ( bRet ) {
        edtCardNumner->setText( strNumber );
    }

    return bRet;
}

void MainWindow::SetCardControl( QLineEdit *edtCtrl )
{
    edtCardNumner = edtCtrl;
}

void MainWindow::IconLoad( QWidget& frame )
{
    QString strInfo = strIconPath + "Icon.PNG";
    QIcon icon( strInfo );
    frame.setWindowIcon( icon );
}

QPixmap& MainWindow::GetPixmap( QString& strFile )
{
    static QPixmap pixmap;

    QString strTmp = strFile + ".JPG";
    if ( !pixmap.load(  strTmp, "JPG" ) ) {
        strTmp = strFile + ".PNG";
        pixmap.load( strTmp, "PNG" );
    }

    return pixmap;
}

void MainWindow::WriteLog( QString strType, QString& strContent, CommonDataType::SysLogType logType, QDateTime& dtDateTime, char cCan )
{
    QStringList lstRows;
    QString strText;
    CCommonFunction::DateTime2String( dtDateTime, strText );
    lstRows << strUserName << strType << strContent << strText;
    QString strWhere = "";
    GetLogicInterface( )->OperateSysLogInfo( lstRows, logType, CommonDataType::InsertData, strWhere );
}

void MainWindow::WriteShiftLog( bool bLogin )
{
    QString strContent = bLogin ? "登录系统成功" : "退出软件";
    QDateTime dtDateTime = QDateTime::currentDateTime( );
    WriteLog( "换班记录", strContent, CommonDataType::ShiftLog, dtDateTime );
}

void MainWindow::Permission( )
{
    QStringList lstRows;
    QString strWhere = QString( " Where operatorname = '%1' " ).arg( strUserName );
    CLogicInterface::GetInterface( )->OperateRightInfo( lstRows, CommonDataType::SelectData, strWhere );

    if ( 0 >= lstRows.count( ) ) {
        return;
    }

    QString strFalse = "0";
    // Right Mgm
    int nField = 4;
    bool bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actRightMgm->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actTariffSetting->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actDBMaintenance->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actSysLog->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actVideoService->setEnabled( bEnabled );
    ui->actRemoteMgmt->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actPlateService->setEnabled( bEnabled );
    ui->actIPC->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actConnectDb->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actSysExit->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actMonthlyCard->setEnabled( bEnabled );
    emit OnPermission( bEnabled, 0 );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actValueCard->setEnabled( bEnabled );
    emit OnPermission( bEnabled, 1 );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actTimeCard->setEnabled( bEnabled );
    emit OnPermission( bEnabled, 2 );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actPublishLEDInfo->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actDeviceConfig->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actSysSetting->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actBatchSetCardAccess->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actTollDiscountTypeSet->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actBlacklist->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actSerialPort->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actPlateRecognizationSet->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actSyncTime->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actAccess2Records->setEnabled( bEnabled );
    emit OnPermission( bEnabled, 3 );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actReewalRecords->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actDiscountSummaryReport->setEnabled( bEnabled );
    //ui->actSerialPort->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    ui->actPrintDaylyReport->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    //ui->actPrintDaylyReport->setEnabled( bEnabled );
    ui->actStay->setEnabled( bEnabled );

    bEnabled |= ( 0 != lstRows[ nField++ ].compare( strFalse ) );
    //ui->actPrintDaylyReport->setEnabled( bEnabled );

    bEnabled = ( 0 != lstRows[ 4 ].compare( strFalse ) );
    ui->mainTB->actions( )[ 2 ]->setEnabled( bEnabled );
    ui->mainTB->actions( )[ 3 ]->setEnabled( bEnabled );
    ui->mainTB->actions( )[ 4 ]->setEnabled( bEnabled );
    ui->mainTB->actions( )[ 5 ]->setEnabled( bEnabled );
}

void MainWindow::Login( bool bStart )
{
    if ( bStart ) {
        IconLoad( *pDlgLogin );
        connect( pDlgLogin, SIGNAL( ImportLicenseData( ) ), this, SLOT( on_actLicense_triggered( ) ) );
    }

    pDlgLogin->HideLicenseButton( bSyncServer );

    //pDlgLogin->HideCancelBtn( bStart );
    pDlgLogin->GetUsers( bStart );
    CCommonFunction::MySetWindowPos( pDlgLogin );

    if ( bStart ) {
        pDlgLogin->move( pDlgLogin->geometry( ).left( ),
                                          pDlgLogin->geometry( ).top( ) + 10 );
    }

    bool bStartupPlateDilivery = pSettings->value( "PlateDilivery/StartupDilivery", false ).toBool( );
    if ( bStartupPlateDilivery ) {
        if ( !pDlgLogin->AutoLogin( ) ) {
            if ( QDialog::Rejected == pDlgLogin->exec( ) ) {
                if ( bStart ) {
                    exit( 0 );
                } else {
                    return;
                }
            }
        } else {
            pDlgLogin->hide( );
        }
    } else {
        if ( QDialog::Rejected == pDlgLogin->exec( ) ) {
            if ( bStart ) {
                exit( 0 );
            } else {
                return;
            }
        }
    }

    if ( pDlgLogin->GetIsLicense( ) ) {
        GenerateLicense( strUserName, strUserPwd );
        pDlgLogin->SetIsLicense( false );
        exit( 0 );
    }

    QString strID;
    pDlgLogin->GetUserPwd( strUserName, strUserPwd, strID );

    emit OnUserChanged( strUserName, strID );
    WriteShiftLog( true );

    ReleaseCapture( );

    GetCardEntityInfo( );

    bool bDisplay = pSettings->value( "CommonCfg/SerialAnalog", false ).toBool( );
    frmSerial.setParent( NULL );
    frmSerial.setVisible( bDisplay );
}

CLogicInterface* MainWindow::GetLogicInterface( )
{
    return pLogicInterface;
}

void MainWindow::GetAppInfo( CommonDataType::AppInfoType appInfo, QString &strInfo )
{
    switch ( appInfo ) {
    case CommonDataType::AppDirPath :
        strInfo = QApplication::applicationDirPath( );
        break;

    case CommonDataType::AppFilePath :
        strInfo = QApplication::applicationFilePath( );
        break;

    case CommonDataType::AppTariffFile :
        strInfo = QApplication::applicationDirPath( );
        strInfo += "/TariffFile.ini";
        break;

    case CommonDataType::AppDBMaintaince :
        strInfo = QApplication::applicationDirPath( );
        strInfo += "/DBMaintainceFile.ini";
        break;
    }
}

void MainWindow::ReconnectDatabase( )
{
    bool bNeed = CLogicInterface::GetInterface( )->PingMysql( );

    if ( !bNeed ) {
        ControlDatabase( false );
        ControlDatabase( true );
    }
}

void MainWindow::ControlDatabase(bool bOpen)
{
    //DbConnect( QString( "192.168.1.5" ), QString( "test" ), QString( "test" ), QString("parkadmin"), 3306 );
    CCommonFunction::ShowSplashMessage( "连接数据库。" );
    pLogicInterface = CLogicInterface::GetInterface( );
    if ( bOpen ) {
#if false
        pSettings->sync( );
        QString strHost   = pSettings->value( "Database/Host", QVariant( "127.0.0.1" ) ).toString( );
        QString strUser   = pSettings->value( "Database/User", QVariant( "test" ) ).toString( );
        QString strPwd    = pSettings->value( "Database/Pwd", QVariant( "test" ) ).toString( );
        QString strSchema = pSettings->value( "Database/Schema", QVariant( "pms" ) ).toString( );
        QString strPort   = pSettings->value( "Database/Port", QVariant( "3306" ) ).toString( );
#endif
        QStringList lstParams;
        CCommonFunction::ConnectMySql( lstParams );

        QString localLoop = "127.0.0.1";
        QString strHost = CCommonFunction::GetHostIP( );
        if ( lstParams[ 0 ] == strHost ) {
            lstParams[ 0 ] = localLoop;
        }
        bool bRet = pLogicInterface->GetMysqlDb().DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );


        if ( false == bRet ) {
            CCommonFunction::ShowSplashMessage( "连接数据库失败。" );
            for ( int nIndex = 0; nIndex < 10000; nIndex++ ) {
                bRet = pLogicInterface->GetMysqlDb().DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );

                if ( bRet ) {
                    break;
                }
                Sleep( 1000 );
            }

            if ( false == bRet ) {
                CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                         "数据库连接失败！", QMessageBox::Warning );
            } else {
                CCommonFunction::ShowSplashMessage( "连接数据库成功。" );
            }
        } else {
            CCommonFunction::ShowSplashMessage( "连接数据库成功。" );
        }
    } else {
        pLogicInterface->GetMysqlDb().DbDisconnect( );
    }
}

void MainWindow::ControlSerial(bool bOpen)
{
    if ( NULL == pSerialPort ) {
        pSerialPort = new CWinSerialPort( "SerialPort", this );
    }

    CProcessData* pProcessor = CProcessData::GetProcessor( pSerialPort, this );
    if ( NULL == pProcessor ) {
        return;
    }

    bool bStartupPlateDilivery = pSettings->value( "PlateDilivery/StartupDilivery", false ).toBool( );
    if ( bStartupPlateDilivery ) {
        return;
    }

    if ( bOpen && !pProcessor->IsOpen( ) ) {
        if ( false == pProcessor->OpenPort( ) ) {
            CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                     "串口打开失败！\n请检查串口是否被占用！", QMessageBox::Information );
        }
    } else if ( !bOpen && pProcessor->IsOpen( ) ){
        pProcessor->ClosePort( );
    }
}

void MainWindow::ClearAllFiles( )
{
    QString strSnapshot;
    CCommonFunction::GetPath( strSnapshot, CommonDataType::PathSnapshot );
    CCommonFunction::ClearAllFiles( strSnapshot );
}

void MainWindow::HideCtrl( bool bVisible )
{
    ui->mainTB->setVisible( bVisible );
    ui->statusBar->setVisible( bVisible );
    ui->menuBar->setVisible( bVisible );
    ui->tbTime->setVisible( bVisible );
}

void MainWindow::SetMaxMinSize( )
{
    QRect rect;

#ifdef NewUI
    rect.setWidth( 1366 );
    rect.setHeight( 768 );
#else
    rect.setWidth( 1440 );
    rect.setHeight( 900 );
#endif

    setGeometry( rect );
    setMaximumSize( rect.width( ), rect.height( ) );
    setMinimumSize( rect.width( ), rect.height( ) );
}

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow( parent, flags ),
    ui(new Ui::MainWindow), pDlgLogin( 0 )
{
    //static CStartupThread startup( this );
    //startup.start( );
    //QEvent* pEvent = new QEvent( QEvent::User );
    //QApplication::postEvent( &startup, pEvent );
    SetMaxMinSize( );

    CCommonFunction::ShowSplashMessage( "初始化时间格式开始。" );
    SetDateTimeFormat( );
    CCommonFunction::ShowSplashMessage( "初始化时间格式结束。" );

    Singleton( );
    strIconPath = "";
    pSerialPort = NULL;
    netServer = NULL;

    ClearAllFiles( );

    CCommonFunction::ShowSplashMessage( "获取参数开始。" );
    CCommonFunction::GetPath( strIconPath, CommonDataType::PathUIImage );
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    strParkID = CCommonFunction::GetParkID( );
    nTransferRecord = pSettings->value( "CommonCfg/TransferRecord", 4 ).toInt( );
    bToInternet = pSettings->value( "CommonCfg/ToInternet", false ).toBool( );
    bAlert = pSettings->value( "CommonCfg/Alert", false ).toBool( );
    edtCardNumner = NULL;
    CCommonFunction::ShowSplashMessage( "获取参数结束。" );

    pDlgLogin = new CLoginDialog( NULL );
    connect( pDlgLogin, SIGNAL( OnReconnect( ) ), this, SLOT( ReconnectDatabase( ) ) );
    ControlDatabase( true );
    CNetwork::Singleton( this );
    ControlSerial( true );
    //GetCardEntityInfo( );
    setWindowFlags( Qt::FramelessWindowHint );

    CCommonFunction::ShowSplashMessage( "创建子窗体开始。" );
    ui->setupUi(this);
    CreateChildren( );
    CCommonFunction::ShowSplashMessage( "创建子窗体结束。" );

    //2014 Dongle
    //pCheckThread = &CCheckThread::GetInstance( this );

    CCommonFunction::ShowSplashMessage( "用户登录。" );
    StartSycnTime( );
    Login( true );

    StartupMgmt( );

    // License
    //2014 Dongle
    //connect( pCheckThread, SIGNAL( ExpirationSender( QString, bool, bool ) ), this, SLOT( Expiration( QString, bool, bool ) ) );
    //StartLicense( );

    CCommonFunction::ShowSplashMessage( "加载图片结束。" );
    IconLoad( *this );
    CCommonFunction::ShowSplashMessage( "加载图片结束。" );

    //QWidget::setWindowState( Qt::WindowMaximized );
    HideCtrl( false );
    //ControlSerial( true );
    ControlMonitor( true );
    ModiyToobar( );
    LoadUIImage( );
    move( 0, 0 );
    //Login( true );
    CCommonFunction::ShowSplashMessage( "授权开始。" );
    Permission( );
    CCommonFunction::ShowSplashMessage( "授权结束。" );

    //CCommonFunction::ShowSplashMessage( "同步时间开始。" );
   //CCommonFunction::ShowSplashMessage( "同步时间结束。" );

    ui->actPlateService->menuAction( )->setVisible( false );
    ui->actVideoService->menuAction( )->setVisible( false );

    QString strText = "%1%2端功能。";
    CCommonFunction::ShowSplashMessage( strText.arg( "启用", bSyncServer ? "服务器" : "客户" ) );

    ServerFunction( );
    ClientFunction( );

    RegisterAxCtrl( );

    qRegisterMetaType< QAbstractSocket::SocketError >( "QAbstractSocket::SocketError" );
    //pEvent = new QEvent( ( QEvent::Type ) ( QEvent::User + 1 ) );
    //QApplication::postEvent( &startup, pEvent );
    GatherData( );
}

void MainWindow::RegisterAxCtrl( )
{
    QLibrary libLoader;
    libLoader.setFileName( "SMSXControl.ocx" );
    bool bRet = libLoader.load( );
    if ( !bRet ) {
        CCommonFunction::MsgBox( NULL, "提示", libLoader.errorString( ), QMessageBox::Information );
        return;
    }

    typedef HRESULT __stdcall ( *DllRegisterServer ) (void);

    DllRegisterServer reg = ( DllRegisterServer ) libLoader.resolve( "DllRegisterServer" );
    if ( NULL != reg ) {
        reg( );
    }
}

void MainWindow::ProcessGateCommand( QStringList &lstData )
{
    CProcessData* pProcessor = CProcessData::GetProcessor( );
    if ( NULL == pProcessor ) {
        return;
    }

    if ( 3 > lstData.count( ) ) {
        return;
    }

    lstData.removeAt( 0 );

    quint8 nItems = lstData.count( ) ;
    nItems -= nItems % 2;
    if ( 2 > nItems ) {
        return;
    }

    for ( quint8 nIndex = 0; nIndex < nItems; nIndex += 2 ) {
        const QString& strOp = lstData.at( nIndex );
        char cCan = lstData.at( nIndex + 1 ).toShort( );
        pProcessor->ControlGate( "1" == strOp, cCan );
    }

    // Open(1)Close(0) CANAddr
}

void MainWindow::ProcessCpuidRequest( QStringList &lstData )
{
    return; //2014 Dongle
    if ( 3 > lstData.count( ) ) {
            return;
    }

    //QString strPSN;
    //CLicense::CreateSingleton( false ).GetPSN( strPSN );
    QStringList lstHids;
    CLicense::CreateSingleton( false ).GetPSN( lstHids );
    QString strIP = CCommonFunction::GetHostIP( );
    QString strAdminParkID = CCommonFunction::GetParkID( );

    foreach ( const QString& strPSN, lstHids ) {
        lstData.clear( );
        lstData << strPSN << strIP << strAdminParkID;

        CNetwork::Singleton( ).BroadcastDatagram( CommonDataType::DGCpuidResponse, lstData );
    }
}

bool MainWindow::GenerateLicense( QString &strSpecialUser, QString& strSpecialPwd )
{
    bool bExit = false;

    if ( "Future" != strSpecialUser || "951821*Future" != strSpecialPwd ) {
        ;//return bExit;
    }

    CDlgMakeLicense license( NULL );
    license.setStatusTip( strIconPath + "NewIcon/CommonMiddleBG-normal.jpg" );

    //CLicense::CreateSingleton( false ).GetDongle( )->SetVerifyDate( false );
    if ( !CLicense::CreateSingleton( false ).GetDongle( )->Administrator( ) ) {
        CCommonFunction::MsgBox( NULL, "错误", "请插入管理员加密狗！", QMessageBox::Critical );
        return bExit;
    }

    license.exec( );
    bExit = true;

    return bExit;
}

void MainWindow::StartLicense( )
{
    //2014 Dongle
    return;
    CLicense::CreateSingleton( false ).GetDongle( )->SetVerifyDate( true );
    QString strParkID = CCommonFunction::GetParkID( );
    pCheckThread->GetBlob( strParkID );
    pCheckThread->start( );
}

void MainWindow::Expiration( QString strMsg, bool bExpiration, bool bRetry )
{
    static int nCount = 0;

    if ( bRetry ) {
        QMessageBox msgBox;
        msgBox.setText( strMsg );
        msgBox.setWindowTitle( "软件异常" );
        QPushButton* pBtn = msgBox.addButton( QMessageBox::Ok );
        pBtn->setText( "重试" );
        pBtn = msgBox.addButton( QMessageBox::Cancel );
        pBtn->setText( "取消" );

        int nRet = msgBox.exec( );
        if ( QMessageBox::Ok == nRet && ( ++nCount < 5 ) ) {
            CLicense::CreateSingleton( false ).GetDongle( )->Reopen( );
            StartLicense( );
            return;
        }
    }

    nCount = 0;
    CLogicInterface::GetInterface( )->GetMysqlDb( ).SetExpiration( bExpiration );
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->setEnabled( !bExpiration );
    CCommonFunction::MsgBox( NULL, bExpiration ? "错误" : "提示", strMsg, bExpiration ? QMessageBox::Critical : QMessageBox::Information );
    qDebug( ) << "Expiration:" << strMsg << endl;

    if ( bExpiration ) {
        exit( 0 );
    }
}

void MainWindow::GatherData( )
{
    bool bGather = pSettings->value( "Mgmt/Gather", false ).toBool( );
    if ( !bGather ) {
        return;
    }

    CTimerThread::GetInstance( )->start( );
}

void MainWindow::ClientFunction( )
{
    if ( bSyncServer || !bToInternet ) {
        return;
    }

    QTextCodec* pCodec = CCommonFunction::GetTextCodec( );
    CNetClient::GetInstance( false, bSyncServer, pCodec, this ); // Communicate with MySQL server machine
    //CNetClient::GetInstance( true, bSyncServer, pCodec, this ); // Communicate with MySQL server machine

    static QTimer timer( this ); // Heartbeat
    connect( &timer, SIGNAL( timeout( ) ), this, SLOT( SendStateHB( ) ) );
    int nNetStateInterval = pSettings->value( "CenterServer/HeartbeatNetStateInterval",  600000 ).toInt( );
    timer.start( nNetStateInterval );
}

void MainWindow::ServerFunction( )
{
    if ( !bSyncServer ) {
        return;
    }

    ui->actLicense->setVisible( bSyncServer );
    ui->actLicense->setEnabled( bSyncServer );

    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->HideAlert( );

    ////////////////////////2014
    //CDbBackupThread::GetInstance( true, false, this ).start( );
    //CRdAutoDeleteThread::GetInstance( this ).start( );
    //return;
    ////////////////////////

    // Maintance Database
    CRdAutoDeleteThread::GetInstance( this ).start( );
    CDbBackupThread::GetInstance( true, false, this ).start( );

    //return;
    if ( !bToInternet ) {
        return;
    }

    CFtp::GetCommonParams( );
    g_pFtp = new CFtp( );
    g_pFtp->start( );
    //g_pFtp->moveToThread( g_pFtp );

    //QTextCodec* pCodec = CCommonFunction::GetTextCodec( );
    //CNetClient::GetInstance( false, bSyncServer, pCodec, this ); // Communicate with center server
    //CNetClient::GetInstance( true, bSyncServer, pCodec, this ); // Communicate with center server

    // Heartbeat
    g_pHeartbeatThread = &CHeartbeatThread::GetInstance( );
    g_pHeartbeatThread->start( );
    g_pHeartbeatThread->moveToThread( g_pHeartbeatThread );

    // Client Server
    netServer = CSvrThread::GetInstance( );
    netServer->start( );
    //netServer->moveToThread( netServer );
    //netServer->StartupTcpServer( false );
    netServer->StartupUdpServer( false );
}

void MainWindow::SetBallotSense( bool bSense, int nChannel, QByteArray& byData )
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->SetBallotSense( bSense, nChannel, byData );
}

void MainWindow::InitPMS( )
{
}

QString MainWindow::GetCurrentUserID( )
{
    if ( NULL == pDlgLogin ) {
        return "";
    }

    return pDlgLogin->GetCurrentUserID( );
}

void MainWindow::EmployeeCard( QString &strCardno )
{
    if ( NULL == pDlgLogin || !pDlgLogin->isVisible( ) ) {
        return;
    }

    pDlgLogin->EmployeeCard( strCardno );
}

void MainWindow::CreateChildren( )
{
     pChildMap = new Ui::childMap( );
     pMdiArea = new QMdiArea( );
     pMdiArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
     pMdiArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
     setCentralWidget( pMdiArea );
     CreateChildWnd( CommonDataType::MonitorWnd );
     return;
     //CreateChildWnd( CommonDataType::ShiftLogout );
     CreateChildWnd( CommonDataType::RightMgmWnd );
     //CreateChildWnd( CommonDataType::SysSettingWnd );
     CreateChildWnd( CommonDataType::ValueCardWnd );
     CreateChildWnd( CommonDataType::Access2RecordsWnd );
     CreateChildWnd( CommonDataType::BatchSetCardAccessWnd );
     CreateChildWnd( CommonDataType::DBMaintenanceWnd );
     CreateChildWnd( CommonDataType::TollDiscountTypeSetWnd );
     CreateChildWnd( CommonDataType::TimeCardWnd );
     CreateChildWnd( CommonDataType::TariffSettingWnd );
     CreateChildWnd( CommonDataType::SysLogWnd );
     CreateChildWnd( CommonDataType::RenewalRecordsWnd );
     //CreateChildWnd( CommonDataType::PwdModificationWnd );
     CreateChildWnd( CommonDataType::PublishLEDInfoWnd );
     CreateChildWnd( CommonDataType::PrintYearlyReportWnd );
     CreateChildWnd( CommonDataType::PrintMonthlyReportWnd );
     CreateChildWnd( CommonDataType::PrintDaylyReportWnd );
     CreateChildWnd( CommonDataType::MonthlyCardWnd );
     //CreateChildWnd( CommonDataType::HandheldICProcessWnd );
     CreateChildWnd( CommonDataType::DiscountSummaryReportWnd );
     CreateChildWnd( CommonDataType::DeviceConfigWnd );
     CreateChildWnd( CommonDataType::BlacklistWnd );
     //CreateChildWnd( CommonDataType::MonitorWnd );
     //CreateChildWnd( CommonDataType::RemoteMgmt );
}

void MainWindow::ModiyToobar()
{
    QToolBar* pMainTB = ui->mainTB;
    QString strInfo = strIconPath;

    QString strTmp = strInfo + "Shift";
    QIcon icon1( GetPixmap( strTmp ) );
    pMainTB->addAction( icon1, "交班注销", this, SLOT( on_actShiftLogout_triggered( ) ) );

    strTmp = strInfo + "MonthlyCard";
    QIcon icon2( GetPixmap( strTmp ) );
    pMainTB->addAction( icon2, "月租卡", this, SLOT( on_actMonthlyCard_triggered( ) ) );

    strTmp = strInfo + "SaveCard";
    QIcon icon3( GetPixmap( strTmp ) );
    pMainTB->addAction( icon3, "储值卡", this, SLOT( on_actValueCard_triggered( ) ) );

    strTmp = strInfo + "TimeCard";
    QIcon icon4( GetPixmap( strTmp ) );
    pMainTB->addAction( icon4, "计时卡", this, SLOT(on_actTimeCard_triggered( ) ) );

    strTmp = strInfo + "Inout";
    QIcon icon5( GetPixmap( strTmp ) );
    pMainTB->addAction( icon5, "出入记录", this, SLOT(on_actAccess2Records_triggered( ) ) );

    pMainTB->setMovable( false );

    pLblTime = new QLabel( ui->tbTime );
    pLblTime->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
    ui->tbTime->addWidget( pLblTime );
    pLblTime->setStyleSheet( "color: rgb(0, 143, 0);\nfont: 75 30pt \"黑体\";");
    //ui->tbTime->setStyleSheet( "background-color: rgb(0, 0, 0);" );
    pLblTime->setVisible( true );

    ui->tbTime->setMovable( false );

    pTimer = new QTimer( this );
    connect( pTimer, SIGNAL( timeout( ) ), SLOT( UpdateLableText(  ) ) );
    pTimer->start( 1000 );
}

void MainWindow::showEvent(QShowEvent *)
{
    InitPMS( );
    CheckCenterContronller( );
}

void MainWindow::CheckCenterContronller( )
{
    ControlSerial( true );
    CProcessData* pProcessor = CProcessData::GetProcessor( pSerialPort, this );
    if ( NULL == pProcessor ) {
        return;
    }
    QDateTime dtCurrent = QDateTime::currentDateTime( );
    pProcessor->CheckCenterContronller( true, dtCurrent );
    pProcessor->CheckCenterContronller( false, dtCurrent );
}

void MainWindow::ProcessDatagram( QStringList &lstData )
{
    if ( lstData.count( ) <= 1 ) {
        return;
    }

    int nField = 0;
    int nType = lstData[ nField++ ].toInt( );

    if( CommonDataType::DGSyncTime == nType ) {
        SyncTime( lstData );
    } else if ( CommonDataType::DGPublishLed == nType ) {
        CProcessData* pProcessor = CProcessData::GetProcessor( );
        if ( NULL != pProcessor ) {
            pProcessor->BroadcastLedInfo( lstData );
        }
    } else if ( CommonDataType::DGCpuidRequest == nType ) {
        ProcessCpuidRequest( lstData );
    } else if ( CommonDataType::DGGateCommand == nType ) {
        ProcessGateCommand( lstData );
    } else {
        ProcessMonitorMsg( ( CommonDataType::DatagramType ) nType, lstData );
    }
}

void MainWindow::SendInOutImg( QString &strFile, bool bEnter, QDateTime &dtCurrent, QString& strPlate, QString& strCardNo )
{
    if ( !bToInternet || !bAlert ) {
        return;
    }

    if ( strPlate.isEmpty( ) && strCardNo.isEmpty( ) ) {
        return;
    }

    QString strDateTime;
    CCommonFunction::DateTime2String( dtCurrent, strDateTime );
    bool bPlate = true;
    QString strBody = QString( "%1|%2|%3|%4|%5|0" ).arg( CCommonFunction::GetParkID( ), bPlate ? "1" : "0",
                                                      bPlate ? strPlate : strCardNo, bEnter ? "1" : "0", strDateTime );
    CNetClient::GetInstance( false, false ).SendSvrMsgData( NetTransport::SvrAlert, strBody );
    return;

    // Client
    QFile file( strFile );
    if ( !file.exists( ) ||  !file.open( QIODevice::ReadOnly ) ) {
        return;
    }

   QByteArray byData = file.readAll( );
   QStringList lstParams;
   lstParams << QString::number( bEnter ? NetTransport::ImgIn : NetTransport::ImgOut )
                  << strParkID
                  << strCardNo
                  << strPlate
                  << QString::number( dtCurrent.toMSecsSinceEpoch( ) );

   CNetClient::GetInstance( false, false ).SendCltMsgData( NetTransport::CltImg, lstParams, byData );
   file.close();
}

void MainWindow::SendStateHB( )
{
    // Client
    static QString strHostIP = CCommonFunction::GetHostIP( );
    static QTextCodec* pCodec =  CCommonFunction::GetTextCodec( );
    static QString strFormat = "%1,%2,%3";

    QString strBody = strFormat.arg( strParkID, strHostIP, QString::number( QDateTime::currentMSecsSinceEpoch( ) ) );
    QByteArray byBody = pCodec->fromUnicode( strBody );
    QStringList lstParams;
    lstParams << QString::number( NetTransport::HbNetState );
    CNetClient::GetInstance( false, false ).SendCltMsgData( NetTransport::CltHeartbeat, lstParams, byBody );
}

void MainWindow::ForwardPassRecord( QStringList &lstData )
{
    if ( !bSyncServer || !bToInternet ) {
        return;
    }

    int nCols = 12; // 总列数 包含报文类型
    int nTotalCols = lstData.count( );
    if ( nCols > nTotalCols ) {
        return;
    }

    nCols--;
    QString strColSeperator = "\n";
    QString strRowSeperator = "\r";
    QString strDateTime = "";
    int nTransferCols = 6;

    //////////
    // lstData << strPlate << strTime << strCardType << strChannel <<
    //        strCardNumber << ( bEnter ? "1" : "0" )
    //        << QString::number( cardType )
    //        << strDate << strCan << strCardNumber;
    ///////////
    for ( int nIndex = 1; nIndex < nTotalCols; nIndex += nCols ) {
        strPassRecord.append( strParkID ); // ParkID
        strPassRecord.append( strColSeperator );

        strPassRecord.append( lstData[ nIndex ] ); // Plate
        strPassRecord.append( strColSeperator );

        strPassRecord.append( lstData[ nIndex + 5 ] ); // InOut Flag
        strPassRecord.append( strColSeperator );

        strDateTime = lstData[ nIndex + 7 ] + " " + lstData[ nIndex + 1 ]; // Date + Time
        strPassRecord.append( strDateTime );
        strPassRecord.append( strColSeperator );

        strPassRecord.append( lstData[ nIndex + 8 ] ); // Can
        strPassRecord.append( strColSeperator );

        strPassRecord.append( lstData[ nIndex + 9 ] ); // CardNumber

        strPassRecord.append( strRowSeperator );
    }


    int nRows = strPassRecord.count( strRowSeperator );
    if ( nTransferRecord <= nRows ) {
        strPassRecord.remove( strPassRecord.count( ) - 1, strRowSeperator.count( ) );
        // Server to Hb Thread, then to Center Server
        //CNetClient::GetInstance( true, bSyncServer ).SendTableData( strPassRecord, nRows, nTransferCols, NetTransport::TabInOutRecord );

        CHbEvent::TableData table;
        table.strPass = strPassRecord;
        table.nRows = nRows;
        table.nCols = nTransferCols;
        table.tabType = NetTransport::TabInOutRecord;
        CHbEvent* pEvent = new CHbEvent( CHbEvent::HbPassRecord );
        pEvent->SetPassRecord( table );
        QApplication::postEvent( g_pHeartbeatThread, pEvent );
        strPassRecord.clear( );
    }
}

void MainWindow::ProcessMonitorMsg( CommonDataType::DatagramType nType, QStringList &lstData )
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );

    if ( CommonDataType::DGPassRecord == nType ) {
        ForwardPassRecord( lstData );
        pMonitor->FillDataGrid( lstData );
    } else if ( CommonDataType::DGSvrAlert == nType ) {
        pMonitor->DisplayAlert( lstData );
    }
}

void MainWindow::DisplayAlert(QStringList &lstData)
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->DisplayAlert( lstData );
}

void MainWindow::DataMayRead()
{
    //Sleep( 10 );
    CProcessData* pProcessor = CProcessData::GetProcessor( pSerialPort, this );
    if ( NULL == pProcessor ) {
        return;
    }

    Sleep( 4 );

    int nMinLen = 8;
    Win_QextSerialPort& winSerial = pProcessor->GetWinSerialPort( ).GetRawSerialPort( );
    int nValided = winSerial.bytesAvailable( );
    if ( nMinLen > nValided ) {
#ifndef QT_NO_DEBUG
        qDebug( ) << QString( " Data Length less than 8 ( %1 )") .arg( nValided )  << endl;
#endif
         return;
    }

#ifndef QT_NO_DEBUG
        qDebug( ) << "Time " << QDateTime::currentDateTime( ).toMSecsSinceEpoch( ) << endl;
#endif
        QByteArray byData = winSerial.readAll( );

#ifndef QT_NO_DEBUG
        QString strData( byData.toHex( ) );
        qDebug( ) << "Read Serial Port Cmd : " << strData << endl;
#endif

        if ( byData.count( ) < nMinLen ) {
            return;
        }

        char cEnd = 0x55;
        char cStart = 0xAA;
        int nIndex = -1;
        QByteArray bySingle;
        int nDataLen = 0;

        do {
            nIndex = byData.indexOf( cStart );
            if ( -1 == nIndex ) { // No 0xAA
                break;
            } else if ( 0 < nIndex ) { // First 0xAA
                byData.remove( 0, nIndex );
                if ( nMinLen > byData.count( ) ) {
                    break;
                }
            }

            nDataLen = ( BYTE ) byData[ 1 ] + ( ( ( BYTE ) byData[ 2 ]  ) << 8 );
            nDataLen += 4;

            if ( nDataLen >= byData.count( ) ) {
                break;
            }

            if ( cEnd != byData[ nDataLen ] ) {
                nDataLen += 1;
                byData.remove( 0, nDataLen );
                continue;
            }

            nDataLen += 1;
            bySingle = byData.left( nDataLen  );
            byData.remove( 0, nDataLen );

            pProcessor->ParseData( bySingle );
        } while ( nMinLen <= byData.count( ) );
}

void MainWindow::UpdateLableText(  )
{
#if false
    static const QString strMonth[ ] = { "1", "2", "3", "4", "5", "6" ,"7", "8", "9", "10", "11", "12" };
    static const QString strDay[ ] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
                                       "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
                                       "21", "22", "23", "24", "25", "26", "27", "28", "29", "30" };
    static const QString strFairly[ 12 ][ 2 ] = { { " 小寒", " 大寒" }, { " 立春", " 雨水" }, { " 惊蛰", " 春分" },
                                                { " 清明", " 谷雨" }, { " 立夏", " 小满" }, { " 芒种", " 夏至" },
                                                { " 小暑", " 大暑" }, { " 立秋", " 处暑" }, { " 白露", " 秋分" },
                                                { " 寒露", " 霜降" }, { " 立冬", " 小雪" }, { " 大雪", " 冬至" } };
    static const QString strZodiac[ ] = { "鼠年", "牛年", "虎年", "兔年", "龙年", "蛇年",
                                          "马年", "羊年", "猴年", "鸡年", "狗年", "猪年" };
#endif

    QDateTime dtNow = QDateTime::currentDateTime( );
    strTimeText = dtNow.toString( Qt::SystemLocaleLongDate );
    //QDate date = dtNow.date( );
    //int nDay = date.day( );
    //int nMonth = date.month( );
#if false
    //SolarDate solar( date.year( ), nMonth, nDay );
    //ChineseDate lunar;
    //solar.ToChineseDate( lunar );

    //int nlunarYear = lunar.GetYear( );
    //int nLunarMonth = lunar.GetMonth( );
    //int nLunarDay = lunar.GetDay( );
    //int nIndex = 2 * nLunarMonth;
    //int nFairlyIdx = -1;
    //bool bFairly = false;

    if ( 3 <= nDay && 9 >= nDay ) {
           bFairly = true;
           nIndex -= 1;
           nFairlyIdx = 0;
    } else if ( 18 <= nDay && 24 >= nDay ) {
        bFairly = true;
        nFairlyIdx = 1;
    }

    if ( bFairly ) {
        int nFairlyDay = ChineseCalendarDB::GetSolarTerm( nlunarYear, nIndex );
        bFairly = ( nDay == nFairlyDay );
    }

    QString strFairlyText = "";
    if ( bFairly ) {
        strFairlyText = strFairly[ nMonth - 1 ][ nFairlyIdx ];
    }

    int nZodiacIdx = ( ( nlunarYear - 4 ) % 60 ) % 12;
    QString strZodiacText = "农历";
    if ( 0 <= nZodiacIdx || 11 >= nZodiacIdx ) {
        strZodiacText = strZodiac[ nZodiacIdx ];
    }
#endif
   // strTimeText += QString( " %1 %2月%3%4" ).arg( strZodiacText, strMonth[ nLunarMonth - 1 ], strDay[ nLunarDay - 1 ], strFairlyText );
    pLblTime->setText( strTimeText );

    QTime time = dtNow.time( );
    ClearStatistics( time );
}

void MainWindow::ClearStatistics( QTime& time )
{
    static QString strTime = "23:59:59";

    if ( strTime != time.toString( ) ) {
        //qDebug( ) << time.toString( ) << endl;
        return;
    }

    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->ClearStatistics( );
}

void MainWindow::ControlMonitor(bool bShow)
{
    if ( bShow ) {
        CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
        //pMonitor->setWindowState( Qt::WindowMaximized );
        pMonitor->show( );
    }
}

void MainWindow::ControlChild( QCloseEvent *event, QWidget* child )
{
    event->ignore( );
    child->setVisible( false );

    ControlMonitor( true );
}

MainWindow::~MainWindow()
{
    ClearAllFiles( );

    if ( NULL != netServer && netServer->isRunning( ) ) {
        netServer->terminate( );
    }

    delete netServer;
    netServer = NULL;

    delete ui;
}

void MainWindow::ControlChargeInfo(QStringList &strInfo)
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->ControlChargeInfo( strInfo );
}

QWidget* MainWindow::CreateChildWnd( CommonDataType::ChildWndType childType )
{
    //quint64 nTime1 = QDateTime::currentMSecsSinceEpoch( );
#ifndef QT_NO_DEBUG
    //qDebug( ) << QString( "CreateChildWnd( %1 ) Begin" ).arg( QDateTime::currentMSecsSinceEpoch( ) ) << endl;
#endif
    QWidget* pFrame = NULL;
    QString strType = QString::number( childType );
    Ui::childMap::const_iterator ite = pChildMap->find( strType );
    bool bPictureContrast = false;
    QMdiArea* pMdiArea = NULL;
    bool bMiddle = false;
    bool bCommon = false;

    if ( pChildMap->end( ) != ite ) {
        pFrame = ite.value( );
    }
    else {
        switch ( childType ) {
        case CommonDataType::PictureContrast :
            pFrame = new CPictureContrast( NULL );
            bPictureContrast = true;
            break;

        case CommonDataType::ShiftLogoutWnd :
            pFrame = new CShiftLogout( pMdiArea );
            break;

        case CommonDataType::RightMgmWnd :
            pFrame = new CRightMgm( this, pMdiArea );
            break;

        case CommonDataType::TariffSettingWnd :
            pFrame = new CTariffSetting( this,  pMdiArea );
            bMiddle = true;
            break;

        case CommonDataType::DBMaintenanceWnd :
            pFrame = new CDBMaintenance( this,  pMdiArea );
            bMiddle = true;
            break;

        case CommonDataType::SysLogWnd :
            pFrame = new CSysLog( this,  pMdiArea );
            break;

        case CommonDataType::PwdModificationWnd :
            pFrame = new CPwdModification( this,  pMdiArea );
            break;

        case CommonDataType::MonthlyCardWnd :
            pFrame = new CMonthlyCard( this,  pMdiArea );
            break;

        case CommonDataType::ValueCardWnd :
            pFrame = new CValueCard( this,  pMdiArea );
            break;

        case CommonDataType::TimeCardWnd :
            pFrame = new CTimeCard( this,  pMdiArea );
            break;

        case CommonDataType::PublishLEDInfoWnd :
            pFrame = new CPublishLEDInfo( false, this,  pMdiArea );
            bMiddle = true;
            break;

        case CommonDataType::DeviceConfigWnd :
            pFrame = new CDeviceConfig( this,  pMdiArea );
            bCommon = true;
            break;

        case CommonDataType::BlacklistWnd :
            pFrame = new CBlacklist( this,  pMdiArea );
            break;

        case CommonDataType::SysSettingWnd :
            pFrame = new CSysSetting( this,  pMdiArea );
            break;

        case CommonDataType::BatchSetCardAccessWnd :
            pFrame = new CBatchSetCardAccess( this,  pMdiArea );
            break;

        case CommonDataType::TollDiscountTypeSetWnd :
            pFrame = new CTollDiscountTypeSet( this,  pMdiArea );
            bMiddle = true;
            break;

        case CommonDataType::Access2RecordsWnd :
            pFrame = new CAccess2Records( this, pMdiArea );
            break;

        case CommonDataType::RenewalRecordsWnd :
            pFrame = new CRenewalRecords( this,  pMdiArea );
            break;

        case CommonDataType::DiscountSummaryReportWnd :
            pFrame = new CDiscountSummaryReport( this,  pMdiArea );
            break;

        case CommonDataType::PrintDaylyReportWnd :
            pFrame = new CPrintDaylyReport( this,  pMdiArea );
            bMiddle = true;
            break;

        case CommonDataType::PrintMonthlyReportWnd :
            pFrame = new CPrintMonthlyReport( this,  pMdiArea );
            break;

        case CommonDataType::PrintYearlyReportWnd :
            pFrame = new CPrintYearlyReport( this,  pMdiArea );
            break;

        case CommonDataType::HandheldICProcessWnd :
            pFrame = new CHandheldICProcess( this,  pMdiArea );
            break;

        case CommonDataType::MonitorWnd :
            pFrame = new CMonitor( this,  this->pMdiArea );
            this->pMdiArea->addSubWindow( pFrame, Qt::FramelessWindowHint );
            break;

        case CommonDataType::RemoteMgmt :
            pFrame = new CIPCVideoFrame( false );
            bPictureContrast = true;
            break;

        default :
            break;
        }

        if ( !bPictureContrast ) {
            //pMdiArea->addSubWindow( pFrame, Qt::FramelessWindowHint );
            pFrame->setWindowFlags( Qt::FramelessWindowHint );
            pFrame->setWindowState( Qt::WindowNoState );

            if ( NULL == pFrame->parent( ) ) {
                QString strStyle = QString( "background-image:url(%1NewIcon/Common%2BG-normal%3.jpg)" ).arg(
                            strIconPath, bMiddle ? "Middle" : ( bCommon ? "" : "Big" ), GetPictureName( "%1" ) );
                pFrame->setStyleSheet( strStyle );
            }
        }

        pFrame->setVisible( false );
        pChildMap->insert( strType, pFrame );
    }

#ifndef QT_NO_DEBUG
    //qDebug( ) << QString( "CreateChildWnd( %1 ) End" ).arg( QDateTime::currentMSecsSinceEpoch( ) ) << endl;
#endif

    //quint64 nTime2 = QDateTime::currentMSecsSinceEpoch( );
    //CreateChildTime( nTime2 - nTime1, childType );

    return pFrame;
}

void MainWindow::CreateChildTime( quint64 nTime, CommonDataType::ChildWndType childType )
{
    QString strName = "";
    bool bFinished = false;

    switch ( childType ) {
    case CommonDataType::PictureContrast :
        strName = "CPictureContrast( NULL )";
        break;

    case CommonDataType::ShiftLogoutWnd :
        strName = "CShiftLogout( pMdiArea )";
        break;

    case CommonDataType::RightMgmWnd :
        strName = "CRightMgm( this, pMdiArea )";
        break;

    case CommonDataType::TariffSettingWnd :
        strName = "CTariffSetting( this,  pMdiArea )";
        break;

    case CommonDataType::DBMaintenanceWnd :
        strName = "CDBMaintenance( this,  pMdiArea )";
        break;

    case CommonDataType::SysLogWnd :
        strName = "CSysLog( this,  pMdiArea )";
        break;

    case CommonDataType::PwdModificationWnd :
        strName = "CPwdModification( this,  pMdiArea )";
        break;

    case CommonDataType::MonthlyCardWnd :
        strName = "CMonthlyCard( this,  pMdiArea )";
        break;

    case CommonDataType::ValueCardWnd :
        strName = "CValueCard( this,  pMdiArea )";
        break;

    case CommonDataType::TimeCardWnd :
        strName = "CTimeCard( this,  pMdiArea )";
        break;

    case CommonDataType::PublishLEDInfoWnd :
        strName = "CPublishLEDInfo( false, this,  pMdiArea )";
        break;

    case CommonDataType::DeviceConfigWnd :
        strName = "CDeviceConfig( this,  pMdiArea )";
        break;

    case CommonDataType::BlacklistWnd :
        strName = "CBlacklist( this,  pMdiArea )";
        break;

    case CommonDataType::SysSettingWnd :
        strName = "CSysSetting( this,  pMdiArea )";
        break;

    case CommonDataType::BatchSetCardAccessWnd :
        strName = "CBatchSetCardAccess( this,  pMdiArea )";
        break;

    case CommonDataType::TollDiscountTypeSetWnd :
        strName = "CTollDiscountTypeSet( this,  pMdiArea )";
        break;

    case CommonDataType::Access2RecordsWnd :
        strName = "CAccess2Records( this, pMdiArea )";
        break;

    case CommonDataType::RenewalRecordsWnd :
        strName = "CRenewalRecords( this,  pMdiArea )";
        break;

    case CommonDataType::DiscountSummaryReportWnd :
        strName = "CDiscountSummaryReport( this,  pMdiArea )";
        break;

    case CommonDataType::PrintDaylyReportWnd :
        strName = "CPrintDaylyReport( this,  pMdiArea )";
        break;

    case CommonDataType::PrintMonthlyReportWnd :
        strName = "CPrintMonthlyReport( this,  pMdiArea )";
        break;

    case CommonDataType::PrintYearlyReportWnd :
        strName = "CPrintYearlyReport( this,  pMdiArea )";
        break;

    case CommonDataType::HandheldICProcessWnd :
        strName = "CHandheldICProcess( this,  pMdiArea )";
        break;

    case CommonDataType::MonitorWnd :
        strName = "CMonitor( this,  this->pMdiArea )";
        bFinished = true;
        break;

    default :
        break;
    }

    strName = QString( "%1 CreateTime:%2\r\n" ).arg( strName, QString::number( nTime ) );
    static QFile file ( "c:/CreateTime.txt" );
    if ( !file.isOpen( ) ) {
        file.open( QIODevice::WriteOnly );
    }

    const QByteArray byData = strName.toAscii( );
    file.write( byData );

    if ( bFinished ) {
        file.close( );
    }
}

void MainWindow::ShowWnd( CommonDataType::ChildWndType childType )
{
    CreateChildWnd( childType );

    QString strType = QString::number( childType );
    Ui::childMap::const_iterator iteTarget = pChildMap->find( strType );

    Ui::childMap::const_iterator iteBigin = pChildMap->begin( );
    Ui::childMap::const_iterator iteEnd   = pChildMap->end( );

    for ( ; iteBigin != iteEnd; iteBigin++ ) {
        qDebug( ) << "iteTarget == iteBigin : " << ( iteTarget == iteBigin );
        iteBigin.value( )->setVisible( iteTarget == iteBigin );
    }

    QWidget* pFrame = iteTarget.value( );

    qDebug( ) << pFrame->objectName( ) << pFrame->isVisible( ) << endl;
    iteTarget.value( )->show( );
    qDebug( ) << pFrame->objectName( ) << pFrame->isVisible( ) << endl;

    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    if ( QString( pFrame->metaObject( )->className( ) ) != QString( pMonitor->metaObject( )->className( ) ) ) {
        pFrame->setParent( pMonitor );
        HWND hChildWnd = pFrame->winId( );
        ::BringWindowToTop( hChildWnd );
        pMonitor->show();
    }
}

void MainWindow::on_actDeviceConfig_triggered()
{
    ShowWnd( CommonDataType::DeviceConfigWnd );
}

void MainWindow::on_actSysSetting_triggered()
{
    //ShowWnd( CommonDataType::SysSettingWnd );
    CSysSettingDialog dlg;
    dlg.exec( );
}

void MainWindow::on_actBatchSetCardAccess_triggered()
{
    ShowWnd( CommonDataType::BatchSetCardAccessWnd );
}

void MainWindow::on_actTollDiscountTypeSet_triggered()
{
    ShowWnd( CommonDataType::TollDiscountTypeSetWnd );
}

void MainWindow::on_actShiftLogout_triggered()
{
    ControlMonitor( true );
    Login( false );
    //GetCardEntityInfo( );
    Permission( );
    //CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    //pMonitor->show( );
}

void MainWindow::on_actRightMgm_triggered()
{
    ShowWnd( CommonDataType::RightMgmWnd );
}

void MainWindow::on_actTariffSetting_triggered()
{
    ShowWnd( CommonDataType::TariffSettingWnd );
}

void MainWindow::on_actDBMaintenance_triggered()
{
    ShowWnd( CommonDataType::DBMaintenanceWnd );
}

void MainWindow::on_actSysLog_triggered()
{
    ShowWnd( CommonDataType::SysLogWnd );
}

void MainWindow::on_actPwdModification_triggered()
{
    //ShowWnd( CommonDataType::PwdModificationWnd );
    CPwdDialog dlg;
    dlg.OperateUserPwd( strUserName, strUserPwd, true );
    int nRet = dlg.exec( );

    if ( CPwdDialog::Accepted == nRet ) {
        dlg.OperateUserPwd( strUserName, strUserPwd, false );
        QString strSql = QString( "Update operator set operatorpassword = '%1' Where \
                                  operatorid = %2" ).arg( strUserPwd, pDlgLogin->GetOperatorID( ) );

        CLogicInterface::GetInterface( )->ExecuteSql( strSql );

        pDlgLogin->GetUsers( false );
    }
}

void MainWindow::on_actSysExit_triggered()
{
    if( QMessageBox::Cancel == CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                                        "确定要退出系统吗？", QMessageBox::Question ) ) {
        return;
    }

    //ShowWnd( CommonDataType::SysExitWnd );
    WriteShiftLog( false );

    CProcessData::ReleaseProcessor( );
    CLogicInterface::ReleaseInterface( );

    CCommonFunction::PlayMusic( "", true );
    exit( 0 );
}

void MainWindow::on_actMonthlyCard_triggered()
{
    ShowWnd( CommonDataType::MonthlyCardWnd );
}

void MainWindow::on_actValueCard_triggered()
{
    ShowWnd( CommonDataType::ValueCardWnd );
}

void MainWindow::on_actTimeCard_triggered()
{
    ShowWnd( CommonDataType::TimeCardWnd );
}

void MainWindow::on_actAccess2Records_triggered()
{
    ShowWnd( CommonDataType::Access2RecordsWnd );
}

void MainWindow::on_actReewalRecords_triggered()
{
    ShowWnd( CommonDataType::RenewalRecordsWnd );
}

void MainWindow::on_actDiscountSummaryReport_triggered()
{
    ShowWnd( CommonDataType::DiscountSummaryReportWnd );
}

void MainWindow::on_actPrintDaylyReport_triggered()
{
    ShowWnd( CommonDataType::PrintDaylyReportWnd );
}

void MainWindow::on_actPrintMonthlyReport_triggered()
{
    ShowWnd( CommonDataType::PrintMonthlyReportWnd );
}

void MainWindow::on_actPrintYearlyReport_triggered()
{
    ShowWnd( CommonDataType::PrintYearlyReportWnd );
}

void MainWindow::on_actHandheldICProcess_triggered()
{
    //ShowWnd( CommonDataType::HandheldICProcessWnd );
    CHandICDialog dlg;
    dlg.exec( );
}

void MainWindow::on_actAbout_triggered()
{
    //ShowWnd( CommonDataType::MonthlyCardWnd );
    //QStringList lstData;
    //lstData << "川A41093" << QTime::currentTime( ).toString( "hh:mm:ss" ) << "月租卡" << "南门入口";
    //CNetwork::Singleton( ).BroadcastDatagram( CommonDataType::DGPassRecord, lstData );

    CDlgAbout dlg;
    dlg.exec( );
}

void MainWindow::on_actDocment_triggered()
{
    //ShowWnd( CommonDataType::MonthlyCardWnd );
}

void MainWindow::closeEvent( QCloseEvent *event )
{
    //event->ingore( );
}

void MainWindow::on_actBlacklist_triggered()
{
    ShowWnd( CommonDataType::BlacklistWnd );
}

void MainWindow::on_actSerialPort_triggered()
{
    QStringList cfgStream;
    pSerialPort->GetCfg( cfgStream, true );
    CSerialPortDialog dlg( this );
    dlg.GetValue( cfgStream, true );

    int nRet = dlg.exec( );
    if ( CSerialPortDialog::Accepted == nRet ) {
        cfgStream.clear( );
        dlg.GetValue( cfgStream, false );
        pSerialPort->GetCfg( cfgStream, false );
        pSerialPort->ConfigPort( );

        ControlSerial( false );
        ControlSerial( true );
    }
}

void MainWindow::on_actPlateRecognizationSet_triggered()
{
    static CRecognizeParamDlg dlg( this );
    dlg.exec();
}

void MainWindow::on_actStartVideo_triggered()
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->StartAvSdk( );
}

void MainWindow::on_actStartPlate_triggered()
{
   CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
   pMonitor->StartPlateRecog( );
   Sleep( 10000 );
   pMonitor->ControlDetection( 0, true );
   pMonitor->ControlDetection( 1, true );
}

void MainWindow::on_actConnectDb_triggered()
{
    ControlDatabase( false );
    ControlDatabase( true );
    GetCardEntityInfo( );
}

void MainWindow::GetCardEntityInfo( )
{
    QString strWhere = "";

    CCommonFunction::ShowSplashMessage( "获取卡相关信息。" );
    CLogicInterface::GetInterface( )->GetEntityInfo( CCommonFunction::GetCardEntity( ), strWhere );

    strWhere = "";
    CCommonFunction::ShowSplashMessage( "获取车卡关联信息。" );
    CLogicInterface::GetInterface( )->GetPlateCardInfo( CCommonFunction::GetPlateCardHash( ), strWhere );

    CCommonFunction::ShowSplashMessage( "获取CAN地址信息。" );
    CLogicInterface::GetInterface( )->GetCanAddress( );

    CCommonFunction::ShowSplashMessage( "获取费率信息。" );
    CLogicInterface::GetInterface( )->GetAllTariff2File( );
}

void MainWindow::on_actStopVideo_triggered()
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->StopAvSdk( );
}

void MainWindow::on_actStopPlate_triggered()
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->ControlDetection( 0, false );
    pMonitor->ControlDetection( 1, false );
    Sleep( 10000 );
    pMonitor->StopPlateRecog( );
}
#if false
void MainWindow::on_actStartVideoOne_triggered()
{

}

void MainWindow::on_actStartVideoTwo_triggered()
{

}

void MainWindow::on_actStopVideoOne_triggered()
{

}

void MainWindow::on_actStopVideoTwo_triggered()
{

}

void MainWindow::on_actStartPlateOne_triggered()
{

}

void MainWindow::on_actStartPlateTwo_triggered()
{

}

void MainWindow::on_actStopPlateOne_triggered()
{

}

void MainWindow::on_actStopPlateTwo_triggered()
{

}
#endif

void MainWindow::on_actSyncTime_triggered()
{
    if ( bSyncServer ) {
        SendTime( );
    }
}

void MainWindow::on_actPublishLEDInfo_triggered()
{
    ShowWnd( CommonDataType::PublishLEDInfoWnd );
}

void MainWindow::on_actShiftLogout_hovered()
{

}

void MainWindow::on_actRestart_triggered()
{
    QProcess proc;
    QString strExe = QApplication::applicationFilePath( );
    proc.start( strExe );
    exit( 0 );
}

void MainWindow::on_actLicense_triggered()
{
    bool bRet = CCheckThread::GetInstance( this ).Import2Database( );

    if ( bRet ) {
        QDateTime dtDateTime = QDateTime::currentDateTime( );
        QString strContent = strUserName + " 导入了授权数据！";
        WriteLog( "导入授权数据", strContent, ( CommonDataType::SysLogType ) -1, dtDateTime );
    }

    //QString strMsg = "导入授权数据到数据库%1！" ;
    //CCommonFunction::MsgBox( NULL, "提示", strMsg.arg( bRet ? "成功" : "失败" ), QMessageBox::Information );
}

void MainWindow::on_actStay_triggered()
{
        CDlgStaying dlg;
        dlg.exec( );
}

void MainWindow::on_actRemoteMgmt_triggered()
{
    //ShowWnd( CommonDataType::RemoteMgmt );

    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->DisplayRemoteUI( );
}

void MainWindow::on_actIPC_triggered()
{
    CMonitor* pMonitor = dynamic_cast< CMonitor* >( CreateChildWnd( CommonDataType::MonitorWnd ) );
    pMonitor->ManualIPC( );
}
