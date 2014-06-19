#include "cdlgquerywhere.h"
#include "ui_cdlgquerywhere.h"
#include "Common/commonfunction.h"

CDlgQueryWhere::CDlgQueryWhere(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgQueryWhere)
{
    ui->setupUi(this);
    CCommonFunction::ControlSysMenu( *this );
}

CDlgQueryWhere::~CDlgQueryWhere()
{
    delete ui;
}

void CDlgQueryWhere::GetWhere( QStringList &lstWhere )
{
    if ( QDialog::Rejected == result( ) ) {
        return;
    }
    // QString strWhere1 = "and a.cardno = '%1'"; // "and b.carcp = '%1'" // ""
    //QString strWhere2 = "cardno='%1' and"; //cardno in ( select cardindex from carinfo where carcp = '%1' ) // ""

    QString strCard = ui->edtCard->text( );
    QString strPlate = ui->edtPlate->text( );

    if( ui->rb1->isChecked( ) ) {
        lstWhere << "" << "";
    } else if ( ui->rb2->isChecked( ) ) {
        lstWhere << QString( "and a.cardno = '%1'" ).arg( strCard ) << QString( "cardno='%1' and" ).arg( strCard );
    } else if ( ui->rb3->isChecked( ) ) {
        lstWhere << QString( "and b.carcp = '%1'" ).arg( strPlate ) << QString( "cardno in ( select cardindex from carinfo where carcp = '%1' ) and" ).arg( strPlate );
    }
}

void CDlgQueryWhere::on_rb2_clicked(bool checked)
{
    ui->edtCard->setEnabled( checked );
}

void CDlgQueryWhere::on_rb3_clicked(bool checked)
{
    ui->edtPlate->setEnabled( checked );
}

void CDlgQueryWhere::on_btnOK_clicked()
{
    if ( ui->rb2->isChecked( ) && ui->edtCard->text( ).isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, "提示", "请输入卡号。", QMessageBox::Information );
    } else if (ui->rb3->isChecked( ) && ui->edtPlate->text( ).isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, "提示", "请输入车牌号。", QMessageBox::Information );
    } else {
        close( );
    }

    setResult( QDialog::Accepted );
}

void CDlgQueryWhere::on_btnCancel_clicked()
{
    close( );
    setResult( QDialog::Rejected );
}
