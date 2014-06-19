#include "dlgsmsnotification.h"
#include "ui_dlgsmsnotification.h"
#include "SerialPort/processdata.h"
#include "Common/commonfunction.h"
#include "SMS/sms.h"
#include "Dialog/dlgsmsphone.h"

CDlgSMSNotification::CDlgSMSNotification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgSMSNotification)
{
    ui->setupUi(this);
    ui->lblTitle->setText( windowTitle( ) );
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CDlgSMSNotification::~CDlgSMSNotification()
{
    delete ui;
}

void CDlgSMSNotification::on_btnSave_clicked()
{
    QString strText = ui->edtInfo->toPlainText( );
    int nCount = strText.count( );

    if ( 20 < nCount || 0 >= nCount ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "信息内容太长或为空！" ), QMessageBox::Information, "background-image: url( );" );
        return;
    }

    QStringList lstData;
    lstData << "18982073890" << "13308058766";

    CDlgSmsPhone dlg;
    dlg.exec( );
    dlg.GetPhoneList( lstData );

    if ( 0 == lstData.size( ) ) {
        return;
    }

    CSms::GetSingleton( ).SendMsg( lstData, strText ); // Thread
    return;

    lstData << strText;
    CProcessData* pProcessor = CProcessData::GetProcessor( );
    if ( NULL == pProcessor ) {
        return;
    }
    pProcessor->ProcessUserRequest( CommonDataType::UserSMS, 0, lstData );
}

void CDlgSMSNotification::on_btnCancel_clicked()
{
    close( );
}

void CDlgSMSNotification::resizeEvent( QResizeEvent *event )
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

void CDlgSMSNotification::on_lblClose_linkActivated(QString)
{
    close( );
}
