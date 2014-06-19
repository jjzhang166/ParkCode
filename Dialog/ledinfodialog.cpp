#include "Dialog/ledinfodialog.h"
#include "ui_ledinfodialog.h"
#include "Common/commonfunction.h"
#include "SerialPort/processdata.h"
#include <QCheckBox>

CLedInfoDialog::CLedInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLedInfoDialog)
{
    ui->setupUi(this);
    ui->lblTitle->setText( windowTitle( ) );
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CLedInfoDialog::~CLedInfoDialog()
{
    delete ui;
}

bool CLedInfoDialog::SelectTarget( )
{
    QString strChk = "chk%1";
    bool bRet = false;

    for ( int nIndex = 1; nIndex <= 4; nIndex++ ) {
        QCheckBox* pChk = findChild< QCheckBox* >( strChk.arg( nIndex ) );
        bRet = pChk->isChecked( );

        if ( bRet ) {
            break;
        }
    }

    if ( !bRet ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请选择信息发布目标！" ), QMessageBox::Information, "background-image: url( );" );
    }

    return bRet;
}

void CLedInfoDialog::on_btnDownload_clicked()
{
    if ( !SelectTarget( ) ) {
        return;
    }
    QString strText = ui->edtInfo->toPlainText( );
    int nCount = strText.count( );

    if ( 20 < nCount || 0 >= nCount ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "信息内容太长或为空！" ), QMessageBox::Information, "background-image: url( );" );
        return;
    }

    DownloadData( strText );
}

void CLedInfoDialog::DownloadData( QString& strText )
{
    if ( !SelectTarget( ) ) {
        return;
    }
    QStringList lstData;
    lstData << strText;
    lstData << ( ui->chk1->isChecked( ) ? "1" : "" );
    lstData << ( ui->chk2->isChecked( ) ? "2" : "" );
    lstData << ( ui->chk3->isChecked( ) ? "3" : "" );
    lstData << ( ui->chk4->isChecked( ) ? "4" : "" );

    CProcessData* pProcessor = CProcessData::GetProcessor( );
    if ( NULL == pProcessor ) {
        return;
    }

    pProcessor->ProcessUserRequest( CommonDataType::UserPublishLed, 0, lstData );
}

void CLedInfoDialog::on_btnClose_clicked()
{
    close( );
}

void CLedInfoDialog::resizeEvent( QResizeEvent *event )
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

void CLedInfoDialog::on_btnDownloadTime_clicked()
{
    QString strText = "";
    DownloadData( strText );
}

void CLedInfoDialog::on_lblClose_linkActivated(QString)
{
    close( );
}
