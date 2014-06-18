#include "addunitdialog.h"
#include "ui_addunitdialog.h"
#include "Comm/commfunction.h"

AddUnitDialog::AddUnitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUnitDialog)
{
    ui->setupUi(this);
    ui->edtUnitNo->setFocus();
}

AddUnitDialog::~AddUnitDialog()
{
    delete ui;
}

QStringList &AddUnitDialog::GetUnitItemInfo()
{
    return lstInfos;
}

bool AddUnitDialog::Verify()
{
    QString strID = ui->edtUnitNo->text();
    //QString strName = ui->edtUnitName->text();
    if( !IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql() )
    {
        return false;
    }

    QString strSql = "select * from tabunitinfo where UnitID = '%1'";
    strSql = strSql.arg( strID );
    QString strError;
    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    QStringList lstRows;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    if( !lstRows.isEmpty() )
    {
        QMessageBox::information( NULL, QString("提示"), QString("【%1】已存在， 请重新输入！").arg( strID ), "确定" );
        return false;
    }

    return true;
}

void AddUnitDialog::on_ptnAdd_clicked()
{
    QString strID = ui->edtUnitNo->text();
    QString strSql1 = "select * from tabunitinfo where UnitID = '%1'";
    strSql1 = strSql1.arg( strID );
    QString strError;
    QStringList lstRows;
    QString strName1 = "【%1】已经存在，请重新输入！";
    strName1 = strName1.arg( strID );

    QString strUnitName = ui->edtUnitName->text();
    QString strSql2 = "select * from tabunitinfo where UnitName = '%1'";
    strSql2 = strSql2.arg( strUnitName );
    QString strName2 = "【%1】已经存在，请重新输入！";
    strName2 = strName2.arg( strUnitName );

    if( !CommFunction::VerifyIsEmpty( ui->edtUnitNo->text() ) && !CommFunction::VerifyIsEmpty( ui->edtUnitName->text() ) && !CommFunction::VerifyIsEmpty( ui->edtUnitAddress->text() )
            && CommFunction::VerifyLength( ui->edtUnitNo->text(), 9 )
            && CommFunction::VerifyIsNumber( ui->edtUnitNo->text() )
            && CommFunction::VerifyIsUnique( strSql1, strError, lstRows, strName1 )
            && CommFunction::VerifyIsUnique( strSql2, strError, lstRows, strName2 ) )
    {
        lstInfos.clear();
        lstInfos << ui->edtUnitNo->text() << ui->edtUnitName->text()
                 << ui->edtUnitComments->text() << ui->edtUnitAddress->text();

        close();
        this->setResult( AddUnitDialog::Accepted );
    }
}

void AddUnitDialog::on_ptnCancel_clicked()
{
    close();
}
