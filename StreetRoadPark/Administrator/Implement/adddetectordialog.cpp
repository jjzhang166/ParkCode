#include "adddetectordialog.h"
#include "ui_adddetectordialog.h"
#include "Implement/iterfacetomysql.h"
#include "Comm/commfunction.h"

AddDetectorDialog::AddDetectorDialog( QString parkReceiverId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDetectorDialog)
{
    ui->setupUi(this);
    g_parkReceiverId.append( parkReceiverId );
    ui->cmbReset->setItemData( 0, "1", Qt::UserRole );
    ui->cmbReset->setItemData( 1, "0", Qt::UserRole );
    ui->edtDetectorNo->setFocus();
}

AddDetectorDialog::~AddDetectorDialog()
{
    delete ui;
}

QStringList &AddDetectorDialog::GetDetectorItemInfo()
{
    return lstInfos;
}

bool AddDetectorDialog::Verify()
{
    QString strID = ui->edtDetectorNo->text();
    g_ReceiverDetectorId = g_parkReceiverId + strID;
    if( !IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql() )
    {
        return false;
    }

    QString strSql = "select * from tabdetectorinfo where ReceiverDetectorID = '%1'";
    strSql = strSql.arg( g_ReceiverDetectorId );
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

void AddDetectorDialog::on_ptnAdd_clicked()
{
    QString strID = ui->edtDetectorNo->text();
    g_ReceiverDetectorId = g_parkReceiverId + strID;
    QString strSql = "select * from tabdetectorinfo where ReceiverDetectorID = '%1'";
    strSql = strSql.arg( g_ReceiverDetectorId );
    QString strError;
    QStringList lstRows;
    QString strName = "【%1】已经存在，请重新输入！";
    strName = strName.arg( strID );

    if( !CommFunction::VerifyIsEmpty( ui->edtDetectorNo->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtDetectorChannelID->text() )
            && CommFunction::VerifyLength( ui->edtDetectorNo->text(), 3 )
            && CommFunction::VerifyIsNumber( ui->edtDetectorNo->text() )
            && CommFunction::VerifyIsNumber( ui->edtDetectorChannelID->text() )
            && CommFunction::VerifyMinMax( ui->edtDetectorChannelID->text(), 0, 255 )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
    {
        lstInfos.clear();
        lstInfos << ui->edtDetectorNo->text() << ui->edtDetectorChannelID->text() << ui->sbxThreshold->text()
                 << ui->sbxDelayTime->text() << ui->cmbReset->itemData( ui->cmbReset->currentIndex(), Qt::UserRole ).toString() << ui->edtDetectorComments->text()
                 << g_ReceiverDetectorId;
        close();
        this->setResult( AddDetectorDialog::Accepted );      
    }
}

void AddDetectorDialog::on_ptnCancel_clicked()
{
    close();
}
