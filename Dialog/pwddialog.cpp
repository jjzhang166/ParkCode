#include "Dialog/pwddialog.h"
#include "ui_pwddialog.h"
#include "Common/commonfunction.h"

CPwdDialog::CPwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPwdDialog)
{
    ui->setupUi(this);
    ui->edtName->setEnabled( false );
    CCommonFunction::ConnectCloseButton( ui->lblClose );

    CCommonFunction::ControlSysMenu( *this );
    setWindowFlags( Qt::FramelessWindowHint );
    QString strPath;
    CCommonFunction::GetPath( strPath, CommonDataType::PathUIImage );
    strPath += "NewIcon/CommonBG-normal.jpg";
    setStatusTip( strPath );

    ui->lblTitle->setText( windowTitle( ) );
    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CPwdDialog::~CPwdDialog()
{
    delete ui;
}

void CPwdDialog::resizeEvent( QResizeEvent *event )
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

void CPwdDialog::on_btnSave_clicked( )
{
    if ( strPwd != ui->edtOldPwd->text( ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "输入的旧密码，不正确！"), QMessageBox::Information );
        return;
    }

    if ( ui->edtNewPwd1->text( ) != ui->edtNewPwd2->text( ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "两次输入的新密码，不一致！"), QMessageBox::Information );
        return;
    }

    close( );
    setResult( CPwdDialog::Accepted );
}

void CPwdDialog::on_btnCancel_clicked( )
{
    close( );
    setResult( CPwdDialog::Rejected );
}

void CPwdDialog::OperateUserPwd( QString &strUserName, QString &strUserPwd, bool bSet )
{
    if ( bSet ) {
        strUser = strUserName;
        strPwd = strUserPwd;

        ui->edtName->setText( strUser );
    } else {
        strUserName = strUser;
        strUserPwd = ui->edtNewPwd1->text( );
    }
}

void CPwdDialog::on_lblClose_linkActivated(QString)
{
    close( );
}
