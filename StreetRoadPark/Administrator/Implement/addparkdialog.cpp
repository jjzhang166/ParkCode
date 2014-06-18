#include "addparkdialog.h"
#include "ui_addparkdialog.h"
#include "Comm/commfunction.h"

AddParkDialog::AddParkDialog( QString strPid, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::AddParkDialog)
{
    ui->setupUi(this);
    g_AdminID.append( strPid );
    ui->edtParkNo->setFocus();
}

AddParkDialog::~AddParkDialog()
{
    delete ui;
}

QStringList &AddParkDialog::GetParkItemInfo()
{
    return lstInfos;
}

bool AddParkDialog::Verify()
{
    QString strID = ui->edtParkNo->text();
    parkId = g_AdminID + strID;

    if( !IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql() )
    {
        return false;
    }

    QString strSql = "select * from tabparkinfo where ParkID = '%1'";
    strSql = strSql.arg( parkId );
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

void AddParkDialog::on_ptnAdd_clicked()
{
    QString strID = ui->edtParkNo->text();
    parkId = g_AdminID + strID;
    QString strSql = "select * from tabparkinfo where ParkID = '%1'";
    strSql = strSql.arg( parkId );
    QString strError;
    QStringList lstRows;
    QString strName = "【%1】已经存在，请重新输入！";
    strName = strName.arg( strID );

    if( !CommFunction::VerifyIsEmpty( ui->edtParkNo->text() ) && !CommFunction::VerifyIsEmpty( ui->edtParkName->text() ) && !CommFunction::VerifyIsEmpty( ui->edtParkSpace->text() )
            && CommFunction::VerifyLength( ui->edtParkNo->text(), 4 )
            && CommFunction::VerifyIsNumber( ui->edtParkNo->text() ) && CommFunction::VerifyIsNumber( ui->edtParkSpace->text() )
            && CommFunction::VerifyIsNumber( ui->edtUsedSpace->text() ) && CommFunction::VerifyIsNumber( ui->edtParkSelfNum->text() )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
    {
        lstInfos.clear();
        lstInfos << parkId << ui->edtParkName->text() << ui->edtParkSpace->text()
                 << ui->edtUsedSpace->text() << ui->edtParkSelfNum->text() << ui->edtParkComments->text();
        close();
        this->setResult( AddParkDialog::Accepted );
    }
}

void AddParkDialog::on_ptnCancel_clicked()
{
    close();
}
