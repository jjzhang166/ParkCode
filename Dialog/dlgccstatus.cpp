#include "dlgccstatus.h"
#include "ui_dlgccstatus.h"
#include "SerialPort/processdata.h"
#include "Common/commonfunction.h"

CDlgCCStatus::CDlgCCStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgCCStatus)
{
    ui->setupUi(this);
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    CCommonFunction::ConnectCloseButton( ui->lblClose );

    QString strKey = "UserRequest/CommunicationMode";
    ui->cbxMode->setCurrentIndex( pSettings->value( strKey, 0 ).toInt( ) );
    strKey = "UserRequest/IfDisplayFeeInfo";
    ui->chxDisplay->setChecked( pSettings->value( strKey, true ).toBool( ) );
    ui->lblTitle->setText( windowTitle( ) );
    setWindowFlags( Qt::FramelessWindowHint );

setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CDlgCCStatus::~CDlgCCStatus()
{
    delete ui;
}

void CDlgCCStatus::resizeEvent( QResizeEvent *event )
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

void CDlgCCStatus::on_btnTest_clicked()
{
    QStringList lstData;
    lstData << QString::number( ui->spHour->value( ) )
            << QString::number( ui->spMin->value( ) )
            << QString::number( ui->spAmount->value( ) );

    CProcessData::GetProcessor( )->ProcessUserRequest( CommonDataType::UserCenterControler, char( 0x80 ), lstData );
}

void CDlgCCStatus::on_btnSave_clicked()
{
    QString strKey = "UserRequest/CommunicationMode";
    pSettings->setValue( strKey, ui->cbxMode->currentIndex( ) );
    strKey = "UserRequest/IfDisplayFeeInfo";
    pSettings->setValue( strKey, ui->chxDisplay->isChecked( ) );

    pSettings->sync( );
}

void CDlgCCStatus::on_btnCancel_clicked()
{
    close( );
}

void CDlgCCStatus::on_lblClose_linkActivated(QString)
{
    close( );
}
