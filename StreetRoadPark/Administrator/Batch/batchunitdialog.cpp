#include "batchunitdialog.h"
#include "ui_batchunitdialog.h"
#include "ItemInfos/iteminfounit.h"
#include "ItemInfos/ItemType.h"
#include "Comm/commfunction.h"

#include <QMessageBox>

BatchUnitDialog::BatchUnitDialog( QString strAdminId, QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchUnitDialog)
{
    ui->setupUi(this);
    currentItem = pItem;
    g_Pid = strAdminId;
}

BatchUnitDialog::~BatchUnitDialog()
{
    delete ui;
}

void BatchUnitDialog::on_unitTableWidget_cellClicked(int row, int column)
{
    ui->edtUnitNo->setText( ui->unitTableWidget->item( row, 0 )->text() );
    ui->edtUnitName->setText( ui->unitTableWidget->item( row, 1 )->text() );
    ui->edtUnitComments->setText( ui->unitTableWidget->item( row, 2 )->text() );
    ui->edtUnitAddress->setText( ui->unitTableWidget->item( row, 3 )->text() );
}

void BatchUnitDialog::on_ptnAdd_clicked()
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
        // 判断table表中是否存在。 判断strID
        for( int i = 0; i < ui->unitTableWidget->rowCount(); ++i )
        {
            QString tmpID = ui->unitTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }

        QTableWidgetItem *pItem0 = new QTableWidgetItem( ui->edtUnitNo->text() );
        pItem0->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        //pItem0->setData( Qt::UserRole, g_ReceiverDetectorId );

        QTableWidgetItem *pItem1 = new QTableWidgetItem( ui->edtUnitName->text() );
        pItem1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem2 = new QTableWidgetItem(  ui->edtUnitComments->text() );
        pItem2->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem3 = new QTableWidgetItem( ui->edtUnitAddress->text() );
        pItem3->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        int row = ui->unitTableWidget->rowCount();
        ui->unitTableWidget->setRowCount( row + 1 );

        ui->unitTableWidget->setItem( row, 0, pItem0 );
        ui->unitTableWidget->setItem( row, 1, pItem1 );
        ui->unitTableWidget->setItem( row, 2, pItem2 );
        ui->unitTableWidget->setItem( row, 3, pItem3 );
    }
}

void BatchUnitDialog::on_ptnModify_clicked()
{
    if( ui->unitTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要修改的行", "确定" );
        return;
    }

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
        // 判断table表中是否存在。 判断strID
        for( int i = 0; i < ui->unitTableWidget->rowCount(); ++i )
        {
            if( i == ui->unitTableWidget->currentRow() )
            {
                continue;
            }

            QString tmpID = ui->unitTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }

        int row = ui->unitTableWidget->currentRow();
        ui->unitTableWidget->item( row, 0 )->setText( ui->edtUnitNo->text() );
        ui->unitTableWidget->item( row, 1 )->setText( ui->edtUnitName->text() );
        ui->unitTableWidget->item( row, 2 )->setText( ui->edtUnitComments->text() );
        ui->unitTableWidget->item( row, 3 )->setText( ui->edtUnitAddress->text() );
    }
}

void BatchUnitDialog::on_ptnDelete_clicked()
{
    if( ui->unitTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要删除的行", "确定" );
        return;
    }

    int row = ui->unitTableWidget->currentRow();
    ui->unitTableWidget->removeRow( row );
}

void BatchUnitDialog::on_ptnSave_clicked()
{
    QString strBase = "( '%1', '%2', '%3', '%4', '%5' ) ";
    QString strSql = "insert into tabunitinfo values";

    QList<QTreeWidgetItem *> lstChildren;

    int nRows = ui->unitTableWidget->rowCount();

    if( 0 == nRows )
    {
        return;
    }

    for( int i = 0; i < nRows; ++i )
    {
        strSql += strBase.arg( ui->unitTableWidget->item( i, 0 )->text() )
                .arg( ui->unitTableWidget->item( i, 1 )->text() )
                .arg( ui->unitTableWidget->item( i, 2 )->text() )
                .arg( g_Pid )
                .arg( ui->unitTableWidget->item( i, 3 )->text() );

        if( i != nRows - 1 )
        {
            strSql += ","; // 使得最后一个没有,
        }

        QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( ui->unitTableWidget->item( i, 1 )->text() ) );

        ItemInfoUnit newItemInfo;
        newItemInfo.setId( ui->unitTableWidget->item( i, 0 )->text() );
        newItemInfo.setName( ui->unitTableWidget->item( i, 1 )->text() );
        newItemInfo.setComments( ui->unitTableWidget->item( i, 2 )->text() );
        newItemInfo.setAddress( ui->unitTableWidget->item( i, 3 )->text() );
        newItemInfo.setPid( g_Pid ); // AdminstrativeID

        QVariant newValue;
        newValue.setValue( newItemInfo );
        childItem->setData( 0, Qt::WhatsThisRole, UnitItem );
        childItem->setData( 0, Qt::UserRole, newValue );

        lstChildren.append( childItem );
    }

    QString strError;
    QStringList lstRows;
    CommFunction::OperateSql( strSql, strError, lstRows );

    currentItem->addChildren( lstChildren );

    close();
    this->setResult( BatchUnitDialog::Accepted );
}

void BatchUnitDialog::on_ptnClose_clicked()
{
    close();
}
