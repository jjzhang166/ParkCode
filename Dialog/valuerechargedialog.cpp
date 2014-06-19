#include "Dialog/valuerechargedialog.h"
#include "ui_valuerechargedialog.h"
#include "Common/commonfunction.h"

CValueRechargeDialog::CValueRechargeDialog( QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::CValueRechargeDialog)
{
    ui->setupUi(this);

    CCommonFunction::ControlSysMenu( *this );
}

CValueRechargeDialog::~CValueRechargeDialog()
{
    delete ui;
}

void CValueRechargeDialog::on_btnOk_clicked()
{
    ui->spRemainder->value( );
    ui->spAmount->value( );
    close( );
    setResult( QDialog::Accepted );
}

void CValueRechargeDialog::SetRemainder(QString strAmount)
{
    ui->spRemainder->setValue( strAmount.toInt( ) );
}

void CValueRechargeDialog::GetValue( QStringList& lstRows )
{
    QDateTime dtStart = QDateTime::currentDateTime( );
    QString strText;
    CCommonFunction::DateTime2String( dtStart, strText );
    lstRows << QVariant( ui->spAmount->value( ) ).toString( )
            << "0"
            << strText
            << "´¢Öµ¿¨³äÖµ";
}

void CValueRechargeDialog::on_btnCancel_clicked()
{
    close( );
    setResult( QDialog::Rejected );
}
