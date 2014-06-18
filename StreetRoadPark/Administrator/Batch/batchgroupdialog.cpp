#include "batchgroupdialog.h"
#include "ui_batchgroupdialog.h"
#include "ItemInfos/iteminfogroup.h"
#include "Comm/commfunction.h"
#include "ItemInfos/ItemType.h"

#include <QMessageBox>

BatchGroupDialog::BatchGroupDialog( QString groupParentId, QString pid, QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchGroupDialog)
{
    ui->setupUi(this);
    currentItem = pItem;
    g_groupParentId = groupParentId;
    g_pid = pid;
}

BatchGroupDialog::~BatchGroupDialog()
{
    delete ui;
}

void BatchGroupDialog::on_groupTableWidget_cellClicked(int row, int column)
{
    ui->edtGroupNo->setText( ui->groupTableWidget->item( row, 0 )->text() );
    ui->edtGroupName->setText( ui->groupTableWidget->item( row, 1 )->text() );
    ui->edtGroupComments->setText( ui->groupTableWidget->item( row, 2 )->text() );
    ui->spbGroupRight->setValue( ui->groupTableWidget->item( row, 3 )->text().toInt() );
}

void BatchGroupDialog::on_ptnAdd_clicked()
{
    QString strID = ui->edtGroupNo->text();
    QString strSql = "select * from tabgroupinfo where GroupID = %1";
    strSql = strSql.arg( strID.toULongLong() );
    QString strError;
    QStringList lstRows;

    QString strName = ui->edtGroupName->text();
    QString strSql2 = "select * from tabgroupinfo where GroupName = '%1'";
    strSql2 = strSql2.arg( strName );

    QString strName1 = "%1已经存在，请重新输入！";
    strName1 = strName1.arg( strID );
    QString strName2 = "%1已经存在，请重新输入！";
    strName2 = strName2.arg( strName );


    if( !CommFunction::VerifyIsEmpty( ui->edtGroupNo->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtGroupName->text() )
            && CommFunction::VerifyIsNumber( ui->edtGroupNo->text() )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName1 )
            && CommFunction::VerifyIsUnique( strSql2, strError, lstRows, strName2 ) )
    {

        // 判断table表中是否存在。 判断strID

        for( int i = 0; i < ui->groupTableWidget->rowCount(); ++i )
        {
            QString tmpID = ui->groupTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }

            QString tmpName = ui->groupTableWidget->item( i, 1 )->text();
            if( 0 == strName.compare( tmpName ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%2已经存在，请重新输入！" ).arg( strName ), "确定" );
                return;
            }
        }

        QTableWidgetItem *pItem0 = new QTableWidgetItem( ui->edtGroupNo->text() );
        pItem0->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        //pItem0->setData( Qt::UserRole, g_ReceiverDetectorId );

        QTableWidgetItem *pItem1 = new QTableWidgetItem( ui->edtGroupName->text() );
        pItem1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem2 = new QTableWidgetItem(  ui->edtGroupComments->text() );
        pItem2->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem3 = new QTableWidgetItem( QString::number( ui->spbGroupRight->value() ) );
        pItem3->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        int row = ui->groupTableWidget->rowCount();
        ui->groupTableWidget->setRowCount( row + 1 );

        ui->groupTableWidget->setItem( row, 0, pItem0 );
        ui->groupTableWidget->setItem( row, 1, pItem1 );
        ui->groupTableWidget->setItem( row, 2, pItem2 );
        ui->groupTableWidget->setItem( row, 3, pItem3 );
    }
}

void BatchGroupDialog::on_ptnModify_clicked()
{
    if( ui->groupTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要修改的行", "确定" );
        return;
    }

    QString strID = ui->edtGroupNo->text();
    QString strSql = "select * from tabgroupinfo where GroupID = %1";
    strSql = strSql.arg( strID.toULongLong() );
    QString strError;
    QStringList lstRows;

    QString strName = ui->edtGroupName->text();
    QString strSql2 = "select * from tabgroupinfo where GroupName = '%1'";
    strSql2 = strSql2.arg( strName );

    QString strName1 = "%1已经存在，请重新输入！";
    strName1 = strName1.arg( strID );
    QString strName2 = "%1已经存在，请重新输入！";
    strName2 = strName2.arg( strName );


    if( !CommFunction::VerifyIsEmpty( ui->edtGroupNo->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtGroupName->text() )
            && CommFunction::VerifyIsNumber( ui->edtGroupNo->text() )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName1 )
            && CommFunction::VerifyIsUnique( strSql2, strError, lstRows, strName2 ) )
    {
        // 判断table表中是否存在。 判断strID

        for( int i = 0; i < ui->groupTableWidget->rowCount(); ++i )
        {
            if( i == ui->groupTableWidget->currentRow() )
            {
                continue;
            }

            QString tmpID = ui->groupTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }

            QString tmpName = ui->groupTableWidget->item( i, 1 )->text();
            if( 0 == strName.compare( tmpName ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%2已经存在，请重新输入！" ).arg( strName ), "确定" );
                return;
            }
        }

        int row = ui->groupTableWidget->currentRow();
        ui->groupTableWidget->item( row, 0 )->setText( ui->edtGroupNo->text() );
        ui->groupTableWidget->item( row, 1 )->setText( ui->edtGroupName->text() );
        ui->groupTableWidget->item( row, 2 )->setText( ui->edtGroupComments->text() );
        ui->groupTableWidget->item( row, 3 )->setText( ui->spbGroupRight->text() );
    }
}

void BatchGroupDialog::on_ptnDelete_clicked()
{
    if( ui->groupTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要删除的行", "确定" );
        return;
    }

    int row = ui->groupTableWidget->currentRow();
    ui->groupTableWidget->removeRow( row );
}

void BatchGroupDialog::on_ptnSave_clicked()
{
    QString strBase = "( %1, '%2', '%3', %4, %5, '%6' ) ";
    QString strSql = "insert into tabgroupinfo values";

    QList<QTreeWidgetItem *> lstChildren;

    int nRows = ui->groupTableWidget->rowCount();
    //int nCols = ui->groupTableWidget->columnCount();

    if( 0 == nRows )
    {
        return;
    }

    for( int i = 0; i < nRows; ++i )
    {
        strSql += strBase.arg( ui->groupTableWidget->item( i, 0 )->text().toULongLong() )
                .arg( ui->groupTableWidget->item( i, 1 )->text() )
                .arg( ui->groupTableWidget->item( i, 2 )->text() )
                .arg( g_groupParentId.toULongLong() )
                .arg( ui->groupTableWidget->item( i, 3 )->text().toULongLong() )
                .arg( g_pid );

        if( i != nRows - 1 )
        {
            strSql += ","; // 使得最后一个没有,
        }

        QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( ui->groupTableWidget->item( i, 1 )->text() ) );
        ItemInfoGroup newItemInfo;
        newItemInfo.setId( ui->groupTableWidget->item( i, 0 )->text().toULongLong() );
        newItemInfo.setName( ui->groupTableWidget->item( i, 1 )->text() );
        newItemInfo.setComments( ui->groupTableWidget->item( i, 2 )->text() );
        newItemInfo.setParentID( g_groupParentId.toULongLong() ); // change
        newItemInfo.setGroupRight( ui->groupTableWidget->item( i, 3 )->text().toULongLong() );
        newItemInfo.setPid( g_pid ); // UnitID

        QVariant newValue;
        newValue.setValue( newItemInfo );
        childItem->setData( 0, Qt::WhatsThisRole, GroupItem );
        childItem->setData( 0, Qt::UserRole, newValue );

        lstChildren.append( childItem );
    }

    QString strError;
    QStringList lstRows;
    CommFunction::OperateSql( strSql, strError, lstRows );

    currentItem->addChildren( lstChildren );
    close();
    this->setResult( BatchGroupDialog::Accepted );
}

void BatchGroupDialog::on_ptnClose_clicked()
{
    close();
}
