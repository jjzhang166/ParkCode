#include "addreceiverdialog.h"
#include "ui_addreceiverdialog.h"
#include "Comm/commfunction.h"

AddReceiverDialog::AddReceiverDialog(QString parkId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddReceiverDialog)
{
    ui->setupUi(this);
    g_parkID.append( parkId );
    ui->edtReceiverNo->setFocus();
}

AddReceiverDialog::~AddReceiverDialog()
{
    delete ui;
}

QStringList &AddReceiverDialog::GetReceiverItemInfo()
{
    return lstInfos;
}

bool AddReceiverDialog::Verify()
{
    QString strID = ui->edtReceiverNo->text();
    parkReceiverId = g_parkID + strID;

    if( !IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql() )
    {
        return false;
    }

    QString strSql = "select * from tabreceiverinfo where ParkReceiverID = '%1'";
    strSql = strSql.arg( parkReceiverId );
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

void AddReceiverDialog::on_ptnAdd_clicked()
{
    QString strID = ui->edtReceiverNo->text();
    parkReceiverId = g_parkID + strID;
    QString strSql = "select * from tabreceiverinfo where ParkReceiverID = '%1'";
    strSql = strSql.arg( parkReceiverId );
    QString strError;
    QStringList lstRows;
    QString strName = "【%1】已经存在，请重新输入！";
    strName = strName.arg( strID );

    if( !CommFunction::VerifyIsEmpty( ui->edtReceiverNo->text() ) && !CommFunction::VerifyIsEmpty( ui->edtChannelID->text() ) && !CommFunction::VerifyIsEmpty( ui->edtReceiverName->text() )
            && CommFunction::VerifyLength( ui->edtReceiverNo->text(), 3 )
            && CommFunction::VerifyIsNumber( ui->edtReceiverNo->text() ) && CommFunction::VerifyIsNumber( ui->edtChannelID->text() )
            && CommFunction::VerifyMinMax( ui->edtChannelID->text(), 0, 255 )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
    {
        lstInfos.clear();
        lstInfos << ui->edtReceiverNo->text() << ui->edtReceiverName->text()
                 << ui->edtChannelID->text() << ui->edtReceiverComments->text()
                 << parkReceiverId;
        close();
        this->setResult( AddReceiverDialog::Accepted );
    }
}

void AddReceiverDialog::on_ptnCancel_clicked()
{
    close();
}
