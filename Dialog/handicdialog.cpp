#include "Dialog/handicdialog.h"
#include "ui_handicdialog.h"
#include "Common/commonfunction.h"

CHandICDialog::CHandICDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CHandICDialog)
{
    ui->setupUi(this);
    CCommonFunction::ControlSysMenu( *this );
}

CHandICDialog::~CHandICDialog()
{
    delete ui;
}

void CHandICDialog::on_btnConnect_clicked()
{

}

void CHandICDialog::on_btnDiscount_clicked()
{
    close( );
}
