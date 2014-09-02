#include "cdlgmodifycardno.h"
#include "ui_cdlgmodifycardno.h"
#include "Common/commonfunction.h"

CDlgModifyCardNo::CDlgModifyCardNo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgModifyCardNo)
{
    ui->setupUi(this);
    CCommonFunction::ControlSysMenu( *this );
}

CDlgModifyCardNo::~CDlgModifyCardNo()
{
    delete ui;
}

QString CDlgModifyCardNo::GetCardNo( )
{
    return ui->edtNewCardNo->text( );
}

QLineEdit* CDlgModifyCardNo::GetCardNumCtrl( )
{
    return ui->edtNewCardNo;
}

void CDlgModifyCardNo::SetCardNo(  QString& strCardNo )
{
    ui->edtRawCardNo->setText( strCardNo );
}

void CDlgModifyCardNo::on_btnOK_clicked()
{
    if ( ui->edtNewCardNo->text( ).isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, "Ã· æ", "«Î ‰»Îø®∫≈£°", QMessageBox::Information );
        return;
    }

    close( );
    setResult( QDialog::Accepted );
}

void CDlgModifyCardNo::on_btnCancel_clicked()
{
    close( );
    setResult( QDialog::Rejected );
}
