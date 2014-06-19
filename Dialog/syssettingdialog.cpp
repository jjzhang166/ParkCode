#include "Dialog/syssettingdialog.h"
#include "ui_syssettingdialog.h"
#include "Common/commonfunction.h"
#include <QFile>
#include "license/checkthread.h"

CSysSettingDialog::CSysSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSysSettingDialog)
{
    ui->setupUi(this);

    ui->lsResolution->setVisible( false );

    CCommonFunction::ConnectCloseButton( ui->lblClose );
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSysSet );
    ReadFile( );

    CCommonFunction::ControlSysMenu( *this );
    setWindowFlags( Qt::FramelessWindowHint );

    CCommonFunction::GetPath( strPath, CommonDataType::PathUIImage );
    QString strPlateSet = strPath + "NewIcon/SysSet.JPG";
    setStatusTip( strPlateSet );

    strPlateSet = strPath + "NewIcon/SysMiddleSet.JPG";
    QString strStyle = QString( "background-image:url(%1);" ).arg( strPlateSet );
    ui->tabWidget->setStyleSheet( strStyle );

    ui->lblTilte->setText( windowTitle( ) );
    move( 123, 177 );
    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CSysSettingDialog::~CSysSettingDialog()
{
    delete ui;
}

void CSysSettingDialog::resizeEvent( QResizeEvent *event )
{
    QWidget::resizeEvent( event );

    QString strFile = statusTip( );
    QPixmap bgimage( strFile );
    QPalette pal( palette( ) );
    pal.setBrush( QPalette::Window, QBrush( bgimage.scaled( event->size( ),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation ) ) );
    setPalette(pal);
}

void CSysSettingDialog::on_btnCommonSave_clicked()
{
    ui->rdxCostSelfDef->isChecked( );
    ui->rdxCostDll->isChecked( );

    ui->rdxWorkMaster->isChecked( );
    ui->rdxWorkSlave->isChecked( );

    ui->spMonthlyDay->value( );
    ui->spValueSurplus->value( );
    ui->chxMonthlyMode->checkState( );

    ui->chxEntranceMonth->checkState( );// Qt::CheckSate
    ui->chxEntranceValue->checkState( );
    ui->chxEntranceTime->checkState( );
    ui->chxLeaveMonth->checkState( );
    ui->chxLeaveValue->checkState( );
    ui->chxLeaveTime->checkState( );
    ui->chxForceOpenGate->checkState( );
}

void CSysSettingDialog::on_btnCancel_clicked()
{
    close( );
}

void CSysSettingDialog::on_btnCommonFormat_clicked()
{

}

void CSysSettingDialog::on_btnOK_clicked()
{
    ui->dateValid->date( );//QDate
}

void CSysSettingDialog::on_btnVideoModeSave_clicked()
{
    ui->rdxVideoWay2->isChecked( );
    ui->rdxVideoWay3->isChecked( );
    ui->rdxVideoWay4->isChecked( );
    ui->lsResolution->currentItem( )->text( );
}

void CSysSettingDialog::on_btnVichle_clicked()
{
    ui->chxStartAuto->checkState( );
    ui->chxStartBlacklist->checkState( );

    ui->rdxPrecision0->isChecked( );
    ui->rdxPrecision1->isChecked( );
    ui->rdxPrecision2->isChecked( );
    ui->rdxPrecision3->isChecked( );
    ui->rdxPrecision4->isChecked( );
    ui->rdxPrecision5->isChecked( );
    ui->rdxPrecision6->isChecked( );
    ui->rdxPrecision7->isChecked( );
    ui->rdxPrecision8->isChecked( );
}

void CSysSettingDialog::on_btnSpecialSave_clicked()
{
    ui->chxSpaceMonth->checkState( );
    ui->chxSpaceValue->checkState( );
    ui->chxCCEnter->checkState( );
    ui->chxCCLeave->checkState( );
    ui->spCCEnterAddr->value( );
    ui->spCCLeaveAddr->value( );
    ui->chxDataSync->checkState( );
    ui->chxValueCharging->checkState( );

    WriteFile( );
}

void CSysSettingDialog::ReadFile( )
{
    if ( !QFile::exists( pSettings->fileName( ) ) ) {
        return;
    }

    QString strGroup = "CommonSet";
    pSettings->beginGroup( strGroup );
    bool bDll = pSettings->value( "FeeCalculateSet", false ).toBool( );
    ui->rdxCostSelfDef->setChecked( bDll );
    ui->rdxCostDll->setChecked( !bDll );

    bool bMode = pSettings->value( "WorkMode", false ).toBool( );
    ui->rdxWorkMaster->setChecked( bMode );
    ui->rdxWorkSlave->setChecked( !bMode );

    ui->spMonthlyDay->setValue( pSettings->value( "MonthlyWakeup", 0 ).toInt( ) );
    ui->spValueSurplus->setValue( pSettings->value( "SaveWakeup", 0 ).toInt( ) );
    ui->chxEntranceMonth->setChecked( pSettings->value( "EnterComfirm/Monhtly", false ).toBool( ) );
    ui->chxEntranceValue->setChecked( pSettings->value( "EnterComfirm/Save", false ).toBool( ) );
    ui->chxEntranceTime->setChecked( pSettings->value( "EnterComfirm/Time", false ).toBool( ) );
    ui->chxLeaveMonth->setChecked( pSettings->value( "LeaveComfirm/Monhtly", false ).toBool( ) );
    ui->chxLeaveValue->setChecked( pSettings->value( "LeaveComfirm/Save", false ).toBool( ) );
    ui->chxLeaveTime->setChecked( pSettings->value( "LeaveComfirm/Time", false ).toBool( ) );
    ui->chxMonthlyMode->setChecked( pSettings->value( "MonthlyWorkMode", false ).toBool( ) );
    ui->chxForceOpenGate->setChecked( pSettings->value( "ForceOpenGate", false ).toBool( ) );
    ui->chkConfirm->setChecked( pSettings->value( "CardConfirm", false ).toBool( ) );
    pSettings->endGroup( );

    strGroup = "TimeLimit";
    pSettings->beginGroup( strGroup );
    //ui->dateValid->setDate( pSettings->value( "Expiration", QDate::currentDate( ) ).toDate( ) );
    QDate dtDate;
    CCheckThread::GetInstance( NULL ).GetEndDate( dtDate );
    ui->dateValid->setDate( dtDate );
    pSettings->endGroup( );

    strGroup = "VideoMode";
    pSettings->beginGroup( strGroup );
    int nWay = 2;
    nWay = pSettings->value( "Way", 2 ).toInt( );
    VideoMode( nWay, false );
    ui->lsResolution->setCurrentRow( pSettings->value( "Resolution", 0 ).toInt( ) );
    pSettings->endGroup( );

    strGroup = "CarLicence";
    pSettings->beginGroup( strGroup );
    ui->chxStartAuto->setChecked( pSettings->value( "AutoRecognize", false ).toBool( ) );
    ui->chxStartBlacklist->setChecked( pSettings->value( "Blacklist", false ).toBool( ) );
    int nPrecision = 0;
    nPrecision = pSettings->value( "Precision", 0 ).toInt( );
    Precision( nPrecision, false );
    pSettings->endGroup( );

    strGroup = "SpecialSet";
    pSettings->beginGroup( strGroup );
    ui->chxSpaceMonth->setChecked( pSettings->value( "Space/Monthly", false ).toBool( ) );
    ui->chxSpaceValue->setChecked( pSettings->value( "Space/Save", false ).toBool( ) );
    ui->chxCCEnter->setChecked( pSettings->value( "CC/Enter", false ).toBool( ) );
    ui->spCCEnterAddr->setValue( pSettings->value( "CC/EnterAddr", 1 ).toInt( ) );
    ui->chxCCLeave->setChecked( pSettings->value( "CC/Leave", false ).toBool( ) );
    ui->spCCLeaveAddr->setValue( pSettings->value( "CC/LeaveAddr", 1 ).toInt( ) );
    ui->chxDataSync->setChecked( pSettings->value( "SyncOffline", false ).toBool( ) );
    ui->chxValueCharging->setChecked( pSettings->value( "SaveFee", false ).toBool( ) );
    pSettings->endGroup( );
}

void CSysSettingDialog::VideoMode( int &nMode, bool bGet )
{
    QString strName = "rdxVideoWay%1";
    QRadioButton* pRB;

    if ( 2 > nMode ) {
        return;
    }

    if ( bGet ) {
        for ( int nIndex = 2; nIndex < 5; nIndex++ ) {
            pRB = ui->gbVideo->findChild< QRadioButton* >( strName.arg( QString::number( nIndex ) ) );
            if ( pRB->isChecked( ) ) {
                nMode = nIndex;
                break;
            }
        }
    } else {
        pRB = ui->gbVideo->findChild< QRadioButton* >( strName.arg( QString::number( nMode ) ) );
        pRB->setChecked( true );
    }
}

void CSysSettingDialog::Precision( int &nPrecision, bool bGet )
{
    QString strName = "rdxPrecision%1";
    QRadioButton* pRB;

    if ( bGet ) {
        for ( int nIndex = 0; nIndex < 9; nIndex++ ) {
            pRB = ui->gbPrecision->findChild< QRadioButton* >( strName.arg( QString::number( nIndex ) ) );
            if ( pRB->isChecked( ) ) {
                nPrecision = nIndex;
                break;
            }
        }
    } else {
        pRB = ui->gbPrecision->findChild< QRadioButton* >( strName.arg( QString::number( nPrecision ) ) );
        pRB->setChecked( true );
    }
}

void CSysSettingDialog::WriteFile( )
{
    QString strGroup = "CommonSet";
    pSettings->beginGroup( strGroup );
    pSettings->setValue( "FeeCalculateSet", ui->rdxCostSelfDef->isChecked( ) );
    pSettings->setValue( "WorkMode", ui->rdxWorkMaster->isChecked( ) );
    pSettings->setValue( "MonthlyWakeup", ui->spMonthlyDay->value( ) );
    pSettings->setValue( "SaveWakeup", ui->spValueSurplus->value( ) );
    pSettings->setValue( "EnterComfirm/Monhtly", ui->chxEntranceMonth->isChecked( ) );
    pSettings->setValue( "EnterComfirm/Save", ui->chxEntranceValue->isChecked( ) );
    pSettings->setValue( "EnterComfirm/Time", ui->chxEntranceTime->isChecked( ) );
    pSettings->setValue( "LeaveComfirm/Monhtly", ui->chxLeaveMonth->isChecked( ) );
    pSettings->setValue( "LeaveComfirm/Save", ui->chxLeaveValue->isChecked( ) );
    pSettings->setValue( "LeaveComfirm/Time", ui->chxLeaveTime->isChecked( ) );
    pSettings->setValue( "MonthlyWorkMode", ui->chxMonthlyMode->isChecked( ) );
    pSettings->setValue( "ForceOpenGate", ui->chxForceOpenGate->isChecked( ) );
    pSettings->setValue( "CardConfirm", ui->chkConfirm->isChecked( ) );
    pSettings->endGroup( );

    strGroup = "TimeLimit";
    pSettings->beginGroup( strGroup );
    pSettings->setValue( "Expiration", ui->dateValid->date( ).toString( "yyyy-MM-dd" ) );
    pSettings->endGroup( );

    strGroup = "VideoMode";
    pSettings->beginGroup( strGroup );
    int nWay = 2;
    VideoMode( nWay, true );
    pSettings->setValue( "Way", nWay );
    pSettings->setValue( "Resolution", ui->lsResolution->currentRow( ) );
    pSettings->endGroup( );

    strGroup = "CarLicence";
    pSettings->beginGroup( strGroup );
    pSettings->setValue( "AutoRecognize", ui->chxStartAuto->isChecked( ) );
    pSettings->setValue( "Blacklist", ui->chxStartBlacklist->isChecked( ) );
    int nPrecision = 0;
    Precision( nPrecision, true );
    pSettings->setValue( "Precision", nPrecision );
    pSettings->endGroup( );

    strGroup = "SpecialSet";
    pSettings->beginGroup( strGroup );
    pSettings->setValue( "Space/Monthly", ui->chxSpaceMonth->isChecked( ) );
    pSettings->setValue( "Space/Save", ui->chxSpaceValue->isChecked( ) );
    pSettings->setValue( "CC/Enter", ui->chxCCEnter->isChecked( ) );
    pSettings->setValue( "CC/EnterAddr", ui->spCCEnterAddr->value( ) );
    pSettings->setValue( "CC/Leave", ui->chxCCLeave->isChecked( ) );
    pSettings->setValue( "CC/LeaveAddr", ui->spCCLeaveAddr->value( ) );
    pSettings->setValue( "SyncOffline", ui->chxDataSync->isChecked( ) );
    pSettings->setValue( "SaveFee", ui->chxValueCharging->isChecked( ) );
    pSettings->endGroup( );

    pSettings->sync( );
}

void CSysSettingDialog::on_lblClose_linkActivated(QString)
{
    close( );
}
