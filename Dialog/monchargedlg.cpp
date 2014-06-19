#include "Dialog/monchargedlg.h"
#include "ui_monchargedlg.h"
#include "Common/commonfunction.h"

CMonChargeDlg::CMonChargeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMonChargeDlg)
{
    ui->setupUi(this);
    CCommonFunction::ControlSysMenu( *this );
}

CMonChargeDlg::~CMonChargeDlg()
{
    delete ui;
}

void CMonChargeDlg::on_btnSave_clicked()
{

}

void CMonChargeDlg::on_btnCancel_clicked()
{

}
