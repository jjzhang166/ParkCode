#include "batchparkdialog.h"
#include "ui_batchparkdialog.h"
#include "ItemInfos/iteminfopark.h"
#include "ItemInfos/ItemType.h"
#include "Comm/commfunction.h"

#include <QMessageBox>

BatchParkDialog::BatchParkDialog(QString strAdminId, QString strParkParentId, QString strPid,  QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchParkDialog)
{
    ui->setupUi(this);
    currentItem = pItem;
    g_AdminID = strAdminId;
    g_ParkParentId = strParkParentId;
    g_Pid = strPid;
}

BatchParkDialog::~BatchParkDialog()
{
    delete ui;
}

void BatchParkDialog::on_parkTableWidget_cellClicked(int row, int column)
{
    ui->edtParkNo->setText( ui->parkTableWidget->item( row, 0 )->text() );
    ui->edtParkName->setText( ui->parkTableWidget->item( row, 1 )->text() );
    ui->edtParkSpace->setText( ui->parkTableWidget->item( row, 2 )->text() );
    ui->edtUsedSpace->setText( ui->parkTableWidget->item( row, 3 )->text() );
    ui->edtParkSelfNum->setText( ui->parkTableWidget->item( row, 4 )->text() );
    ui->edtParkComments->setText( ui->parkTableWidget->item( row, 5 )->text() );
}

void BatchParkDialog::on_ptnAdd_clicked()
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
        // 判断table表中是否存在。 判断strID
        for( int i = 0; i < ui->parkTableWidget->rowCount(); ++i )
        {
            QString tmpID = ui->parkTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }


        QTableWidgetItem *pItem0 = new QTableWidgetItem( ui->edtParkNo->text() );
        pItem0->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        pItem0->setData( Qt::UserRole, parkId );

        QTableWidgetItem *pItem1 = new QTableWidgetItem( ui->edtParkName->text() );
        pItem1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem2 = new QTableWidgetItem(  ui->edtParkSpace->text() );
        pItem2->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem3 = new QTableWidgetItem( ui->edtUsedSpace->text() );
        pItem3->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem4 = new QTableWidgetItem( ui->edtParkSelfNum->text() );
        pItem4->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem5 = new QTableWidgetItem( ui->edtParkComments->text() );
        pItem5->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        int row = ui->parkTableWidget->rowCount();
        ui->parkTableWidget->setRowCount( row + 1 );

        ui->parkTableWidget->setItem( row, 0, pItem0 );
        ui->parkTableWidget->setItem( row, 1, pItem1 );
        ui->parkTableWidget->setItem( row, 2, pItem2 );
        ui->parkTableWidget->setItem( row, 3, pItem3 );
        ui->parkTableWidget->setItem( row, 4, pItem4 );
        ui->parkTableWidget->setItem( row, 5, pItem5 );
    }
}

void BatchParkDialog::on_ptnModify_clicked()
{
    if( ui->parkTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要修改的行", "确定" );
        return;
    }

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
        // 判断table表中是否存在。 判断strID
        for( int i = 0; i < ui->parkTableWidget->rowCount(); ++i )
        {
            if( i == ui->parkTableWidget->currentRow() )
            {
                continue;
            }

            QString tmpID = ui->parkTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }

        int row = ui->parkTableWidget->currentRow();
        ui->parkTableWidget->item( row, 0 )->setText( ui->edtParkNo->text() );
        ui->parkTableWidget->item( row, 0 )->setData( Qt::UserRole, parkId );
        ui->parkTableWidget->item( row, 1 )->setText( ui->edtParkName->text() );
        ui->parkTableWidget->item( row, 2 )->setText( ui->edtParkSpace->text() );
        ui->parkTableWidget->item( row, 3 )->setText( ui->edtUsedSpace->text() );
        ui->parkTableWidget->item( row, 4 )->setText( ui->edtParkSelfNum->text() );
        ui->parkTableWidget->item( row, 5 )->setText( ui->edtParkComments->text() );
    }
}

void BatchParkDialog::on_ptnDelete_clicked()
{
    if( ui->parkTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要删除的行", "确定" );
        return;
    }

    int row = ui->parkTableWidget->currentRow();
    ui->parkTableWidget->removeRow( row );
}

void BatchParkDialog::on_ptnSave_clicked()
{
    QString strBase = "( '%1', '%2', %3, %4, '%5', '%6', '%7', '%8') ";
    QString strSql = "insert into tabparkinfo values";

    QList<QTreeWidgetItem *> lstChildren;

    int nRows = ui->parkTableWidget->rowCount();

    if( 0 == nRows )
    {
        return;
    }

    for( int i = 0; i < nRows; ++i )
    {
        strSql += strBase.arg( ui->parkTableWidget->item( i, 0 )->data( Qt::UserRole ).toString() )
                .arg( ui->parkTableWidget->item( i, 1 )->text() )
                .arg( ui->parkTableWidget->item( i, 2 )->text().toUShort() )
                .arg( ui->parkTableWidget->item( i, 3 )->text().toUShort() )
                .arg( ui->parkTableWidget->item( i, 4 )->text() )
                .arg( ui->parkTableWidget->item( i, 5 )->text() )
                .arg( g_ParkParentId )
                .arg( g_Pid ); // UnitId

        if( i != nRows - 1 )
        {
            strSql += ","; // 使得最后一个没有,
        }

        QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( ui->parkTableWidget->item( i, 1 )->text() ) );

        ItemInfoPark newItemInfo;
        newItemInfo.setId( parkId );
        newItemInfo.setName( ui->parkTableWidget->item( i, 1 )->text() );
        newItemInfo.setSpace( ui->parkTableWidget->item( i, 2 )->text().toUShort() );
        newItemInfo.setUsedSpace( ui->parkTableWidget->item( i, 3 )->text().toUShort() );
        newItemInfo.setSelfNumber( ui->parkTableWidget->item( i, 4 )->text() );
        newItemInfo.setComments( ui->parkTableWidget->item( i, 5 )->text() );
        newItemInfo.setPid( g_Pid ); // UnitID
        newItemInfo.setParkParentID( g_ParkParentId );

        QVariant newValue;
        newValue.setValue( newItemInfo );
        childItem->setData( 0, Qt::WhatsThisRole, ParkItem );
        childItem->setData( 0, Qt::UserRole, newValue );

        lstChildren.append( childItem );
    }

    QString strError;
    QStringList lstRows;
    CommFunction::OperateSql( strSql, strError, lstRows );

    currentItem->addChildren( lstChildren );

    close();
    this->setResult( BatchParkDialog::Accepted );
}

void BatchParkDialog::on_ptnClose_clicked()
{
    close();
}
