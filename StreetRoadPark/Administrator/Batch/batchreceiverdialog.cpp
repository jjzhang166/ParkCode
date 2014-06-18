#include "batchreceiverdialog.h"
#include "ui_batchreceiverdialog.h"
#include "ItemInfos/iteminforeceiver.h"
#include "ItemInfos/ItemType.h"
#include "Comm/commfunction.h"

#include <QMessageBox>

BatchReceiverDialog::BatchReceiverDialog(QString parkId, QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchReceiverDialog)
{
    ui->setupUi(this);
    currentItem = pItem;
    g_parkID = parkId;
}

BatchReceiverDialog::~BatchReceiverDialog()
{
    delete ui;
}

void BatchReceiverDialog::on_receiverTableWidget_cellClicked(int row, int column)
{
    ui->edtReceiverName->setText( ui->receiverTableWidget->item( row, 0 )->text() );
    ui->edtReceiverNo->setText( ui->receiverTableWidget->item( row, 1 )->text() );
    ui->edtChannelID->setText( ui->receiverTableWidget->item( row, 2 )->text() );
    ui->edtReceiverComments->setText( ui->receiverTableWidget->item( row, 3 )->text() );
}

void BatchReceiverDialog::on_ptnAdd_clicked()
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
        // 判断table表中是否存在。 判断strID
        for( int i = 0; i < ui->receiverTableWidget->rowCount(); ++i )
        {
            QString tmpID = ui->receiverTableWidget->item( i, 1 )->text(); // name id

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }

        QTableWidgetItem *pItem0 = new QTableWidgetItem( ui->edtReceiverName->text() );
        pItem0->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        pItem0->setData( Qt::UserRole, parkReceiverId );

        QTableWidgetItem *pItem1 = new QTableWidgetItem( ui->edtReceiverNo->text() );
        pItem1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem2 = new QTableWidgetItem(  ui->edtChannelID->text() );
        pItem2->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem3 = new QTableWidgetItem( ui->edtReceiverComments->text() );
        pItem3->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        int row = ui->receiverTableWidget->rowCount();
        ui->receiverTableWidget->setRowCount( row + 1 );

        ui->receiverTableWidget->setItem( row, 0, pItem0 );
        ui->receiverTableWidget->setItem( row, 1, pItem1 );
        ui->receiverTableWidget->setItem( row, 2, pItem2 );
        ui->receiverTableWidget->setItem( row, 3, pItem3 );
    }
}

void BatchReceiverDialog::on_ptnModify_clicked()
{
    if( ui->receiverTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要修改的行", "确定" );
        return;
    }
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
        // 判断table表中是否存在。 判断strID
        for( int i = 0; i < ui->receiverTableWidget->rowCount(); ++i )
        {
            if( i == ui->receiverTableWidget->currentRow() )
            {
                continue;
            }

            QString tmpID = ui->receiverTableWidget->item( i, 1 )->text(); // name id

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }

        int row = ui->receiverTableWidget->currentRow();
        ui->receiverTableWidget->item( row, 0 )->setText( ui->edtReceiverName->text() );
        ui->receiverTableWidget->item( row, 0 )->setData( Qt::UserRole, parkReceiverId );
        ui->receiverTableWidget->item( row, 1 )->setText( ui->edtReceiverNo->text() );
        ui->receiverTableWidget->item( row, 2 )->setText( ui->edtChannelID->text() );
        ui->receiverTableWidget->item( row, 3 )->setText( ui->edtReceiverComments->text() );
    }
}

void BatchReceiverDialog::on_ptnDelete_clicked()
{
    if( ui->receiverTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要删除的行", "确定" );
        return;
    }

    int row = ui->receiverTableWidget->currentRow();
    ui->receiverTableWidget->removeRow( row );
}

void BatchReceiverDialog::on_ptnSave_clicked()
{
    QString strBase = "( '%1', '%2', '%3', %4, '%5', '%6' ) ";
    QString strSql = "insert into tabreceiverinfo values";

    QList<QTreeWidgetItem *> lstChildren;

    int nRows = ui->receiverTableWidget->rowCount();

    if( 0 == nRows )
    {
        return;
    }

    for( int i = 0; i < nRows; ++i )
    {
        strSql += strBase.arg( g_parkID )
                .arg( ui->receiverTableWidget->item( i, 0 )->text() ) // name
                .arg( ui->receiverTableWidget->item( i, 1 )->text() ) // id
                .arg( ui->receiverTableWidget->item( i, 2 )->text().toUShort() )
                .arg( ui->receiverTableWidget->item( i, 3 )->text() )
                .arg( ui->receiverTableWidget->item( i, 0 )->data( Qt::UserRole ).toString() );

        if( i != nRows - 1 )
        {
            strSql += ","; // 使得最后一个没有,
        }

        QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( ui->receiverTableWidget->item( i, 0 )->text() ) );

        ItemInfoReceiver newItemInfo;
        newItemInfo.setId( ui->receiverTableWidget->item( i, 1 )->text() );
        newItemInfo.setName( ui->receiverTableWidget->item( i, 0 )->text() );
        newItemInfo.setChannelID( ui->receiverTableWidget->item( i, 2 )->text().toUShort() );
        newItemInfo.setComments( ui->receiverTableWidget->item( i, 3 )->text() );
        newItemInfo.setParkReceiverID( ui->receiverTableWidget->item( i, 0 )->data( Qt::UserRole ).toString() );
        newItemInfo.setPid( g_parkID ); // ParkID

        QVariant newValue;
        newValue.setValue( newItemInfo );
        childItem->setData( 0, Qt::WhatsThisRole, ReceiverItem );
        childItem->setData( 0, Qt::UserRole, newValue );

        lstChildren.append( childItem );
    }

    QString strError;
    QStringList lstRows;
    CommFunction::OperateSql( strSql, strError, lstRows );

    currentItem->addChildren( lstChildren );

    close();
    this->setResult( BatchReceiverDialog::Accepted );
}

void BatchReceiverDialog::on_ptnClose_clicked()
{
    close();
}
