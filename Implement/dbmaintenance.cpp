#include "Header/dbmaintenance.h"
#include "ui_dbmaintenance.h"
#include "Common/commonfunction.h"
#include "Common/CommonType.h"
#include "Common/logicinterface.h"
#include "DbBackup/dbbackupthread.h"

CDBMaintenance::CDBMaintenance(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CDBMaintenance)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );

    fileDlg.setFileMode( QFileDialog::DirectoryOnly );
    fileDlg.setViewMode( QFileDialog::List );

    ui->lblTitle->setText( windowTitle( ) );
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgDbMaintain );

    connect( ui->btnClear1, SIGNAL( clicked( ) ), this, SLOT( ClearData( ) ) );
    connect( ui->btnClear2, SIGNAL( clicked( ) ), this, SLOT( ClearData( ) ) );
    connect( ui->btnClear3, SIGNAL( clicked( ) ), this, SLOT( ClearData( ) ) );
    connect( ui->btnClear4, SIGNAL( clicked( ) ), this, SLOT( ClearData( ) ) );

    QDate date = QDate::currentDate( ).addDays( -60 );
    ui->date1->setDate( date );
    ui->date2->setDate( date );
    ui->date3->setDate( date );
    ui->date4->setDate( date );
    ui->dtNext->setMinimumDate( QDate::currentDate( ).addDays( 1 ) );
}

void CDBMaintenance::ClearData( )
{
    if ( QMessageBox::Cancel == CCommonFunction::MsgBox( NULL, "提示", "确定要清楚数据吗？",
                                                         QMessageBox::Question ) ) {
        return;
    }

    QPushButton* pBtn = qobject_cast< QPushButton* >( sender( ) );
    int nIndex = pBtn->objectName( ).right( 1 ).toInt( );
    QString strGb = "gb%1";
    QString strDate = "date%1";
    QGroupBox* pGb = findChild< QGroupBox* >( strGb.arg( nIndex ) );
    QDate date = pGb->findChild< QDateEdit* >( strDate.arg( nIndex ) )->date( );
    CCommonFunction::Date2String( date, strDate );

    CLogicInterface::GetInterface( )->DbDeleteRd( nIndex, strDate );
    CCommonFunction::OperationSuccess( );
}

void CDBMaintenance::GetValue( bool bReadFile )
{
    bReadFile ? ReadIniFile( ) : WriteIniFile( );
}

void CDBMaintenance::ReadIniFile( )
{
    //dateRecharge
    //dateOutIn
    //dateSysLog
    //dateImg

    QString strSection = "Options/";
    int nValue = 0;
    bool bChecked = false;

    nValue = pSettings->value( strSection + "FeeRd" ).toInt( );
    ui->spDay1->setValue( nValue );
    bChecked = pSettings->value( strSection + "FeeRdAuto" ).toBool( );
    ui->chxDay1->setChecked( bChecked );

    nValue = pSettings->value( strSection + "StopRd" ).toInt( );
    ui->spDay2->setValue( nValue );
    bChecked = pSettings->value( strSection + "StopRdAuto" ).toBool( );
    ui->chxDay2->setChecked( bChecked );

    nValue = pSettings->value( strSection + "SysLog" ).toInt( );
    ui->spDay3->setValue( nValue );
    bChecked = pSettings->value( strSection + "SysLogAuto" ).toBool( );
    ui->chxDay3->setChecked( bChecked );

    nValue = pSettings->value( strSection + "ImgRd" ).toInt( );
    ui->spDay4->setValue( nValue );
    bChecked = pSettings->value( strSection + "ImgRdAuto" ).toBool( );
    ui->chxDay4->setChecked( bChecked );

    QTime time = pSettings->value( strSection + "AutoBackupTime", QTime::currentTime( ) ).toTime( );
    ui->timeAuto->setTime( time );
    bChecked = pSettings->value( strSection + "AutoBackupStartup" ).toBool( );
    ui->chxAuto1->setChecked( bChecked );
    bChecked = pSettings->value( strSection + "AutoBackupImg" ).toBool( );
    ui->chxAuto2->setChecked( bChecked );
    QDate nextDate = pSettings->value( strSection + "NextAutoTime", QDate::currentDate( ) ).toDate( );
    ui->dtNext->setDate( nextDate );

    time = pSettings->value( strSection + "AutoStart", QTime::currentTime( ) ).toTime( );
    ui->timeDelete->setTime( time );

    QString strPath = pSettings->value( strSection + "ManualBackupPath", "" ).toString( );
    ui->edtBackupPath->setText( strPath );
    bChecked = pSettings->value( strSection + "ManualBackupImg" ).toBool( );
    ui->chxBackup->setChecked( bChecked );

    strPath = pSettings->value( strSection + "ManualRestorePath", "" ).toString( );
    ui->edtRecoveryPath->setText( strPath );
    bChecked = pSettings->value( strSection + "ManualOverwiteData" ).toBool( );
    ui->chxOverwrite->setChecked( bChecked );
}

void CDBMaintenance::WriteIniFile( )
{
    //dateRecharge
    //dateOutIn
    //dateSysLog
    //dateImg

    QString strSection = "Options/";

    pSettings->setValue( strSection + "FeeRd", ui->spDay1->value( ) );
    pSettings->setValue( strSection + "FeeRdAuto", ui->chxDay1->isChecked( ) );

    pSettings->setValue( strSection + "StopRd", ui->spDay2->value( ) );
    pSettings->setValue( strSection + "StopRdAuto", ui->chxDay2->isChecked( ) );

    pSettings->setValue( strSection + "SysLog", ui->spDay3->value( ) );
    pSettings->setValue( strSection + "SysLogAuto", ui->chxDay3->isChecked( ) );

    pSettings->setValue( strSection + "ImgRd", ui->spDay4->value( ) );
    pSettings->setValue( strSection + "ImgRdAuto", ui->chxDay4->isChecked( ) );

    QTime time = ui->timeAuto->time( );
    QString strText;
    CCommonFunction::Time2String( time, strText );
    pSettings->setValue( strSection + "AutoBackupTime", strText );
    pSettings->setValue( strSection + "AutoBackupStartup", ui->chxAuto1->isChecked( ) );
    pSettings->setValue( strSection + "AutoBackupImg", ui->chxAuto2->isChecked( ) );
    QDate date = ui->dtNext->date( );
    CCommonFunction::Date2String( date, strText );
    pSettings->setValue( strSection + "NextAutoTime", strText );

    time = ui->timeDelete->time( );
    CCommonFunction::Time2String( time, strText );
    pSettings->setValue( strSection + "AutoStart", strText );

    pSettings->setValue( strSection + "ManualBackupPath", ui->edtBackupPath->text( ) );
    pSettings->setValue( strSection + "ManualBackupImg", ui->chxBackup->isChecked( ) );

    pSettings->setValue( strSection + "ManualRestorePath", ui->edtRecoveryPath->text( ) );
    pSettings->setValue( strSection + "ManualOverwiteData", ui->chxOverwrite->isChecked( ) );

    pSettings->sync( );
}

void CDBMaintenance::OpenDialog( bool bBackup )
{
    int nRet = fileDlg.exec( );

    if ( QFileDialog::Rejected == nRet ) {
        return;
    }

    QDir dir = fileDlg.directory( );

    if ( bBackup ) {
        ui->edtBackupPath->setText( dir.absolutePath( ) );
    } else {
        ui->edtRecoveryPath->setText( dir.absolutePath( ) );
    }
}

void CDBMaintenance::on_btnBackup_clicked( )
{
    QString strPath = ui->edtBackupPath->text( );
    if ( strPath.isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请选择文件路径！" ), QMessageBox::Information );
    } else {
        StartThread( false, false );
    }
}

void CDBMaintenance::on_btnRecovery_clicked( )
{
    QString strPath = ui->edtRecoveryPath->text( );
    if ( strPath.isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请选择文件路径！" ), QMessageBox::Information );
    } else {
        StartThread( false, true );
    }
}

void CDBMaintenance::StartThread( bool bAutoBackup, bool bRestore )
{
    GetValue( false );
    CDbBackupThread::GetInstance( bAutoBackup, bRestore, this ).start( );
}

void CDBMaintenance::on_btnSave_clicked( )
{
    GetValue( false );
}

void CDBMaintenance::on_btnBackupPath_clicked( )
{
    OpenDialog( true );
}

void CDBMaintenance::on_btnRecoveyPath_clicked( )
{
    OpenDialog( false );
}

CDBMaintenance::~CDBMaintenance()
{
    delete ui;
}

void CDBMaintenance::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CDBMaintenance::CalculatePos( )
{
#ifdef NewUI
    move( 123, 46 );
#else
    move( 123, 177 );
#endif
    return;
    QRect rectWnd = this->geometry( );

    QString strName = "widget";
    QWidget* pWg = findChild< QWidget* >( strName );
    QRect rectWg = pWg->geometry( );

    pWg->setGeometry( ( rectWnd.width( ) - rectWg.width( ) -2 ) / 2,
                      ( rectWnd.height( )  - rectWg.height( ) -2 ) / 2 - 40,
                      rectWg.width( ), rectWg.height( ) );
}

void CDBMaintenance::resizeEvent( QResizeEvent* )
{
    CalculatePos( );
}

void CDBMaintenance::showEvent(QShowEvent *)
{
    GetValue( true );
}

void CDBMaintenance::on_btnClose_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CDBMaintenance::on_lblClose_linkActivated(QString)
{
    close( );
}
