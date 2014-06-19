#include "dlgblacklistlocation.h"
#include "ui_dlgblacklistlocation.h"

CDlgBlacklistLocation::CDlgBlacklistLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgBlacklistLocation)
{
    ui->setupUi(this);
}

CDlgBlacklistLocation::~CDlgBlacklistLocation()
{
    delete ui;
}

void CDlgBlacklistLocation::on_btnOk_clicked()
{
    emit Location( ui->edtPlate->text( ) );
}

void CDlgBlacklistLocation::on_btnClose_clicked()
{
    close( );
}
