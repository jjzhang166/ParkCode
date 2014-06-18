#include "batchuserdialog.h"
#include "ui_batchuserdialog.h"
#include "ItemInfos/iteminfouser.h"
#include "ItemInfos/ItemType.h"
#include "Comm/commfunction.h"

#include <QMessageBox>

BatchUserDialog::BatchUserDialog( QString pid, QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchUserDialog)
{
    ui->setupUi(this);
    currentItem = pItem;
    g_pid = pid;
}

BatchUserDialog::~BatchUserDialog()
{
    delete ui;
}

void BatchUserDialog::on_userTableWidget_cellClicked(int row, int column)
{
    ui->edtUserNo->setText( ui->userTableWidget->item( row, 0 )->text() );
    ui->edtUserName->setText( ui->userTableWidget->item( row, 1 )->text() );
    ui->edtUserComments->setText( ui->userTableWidget->item( row, 2 )->text() );
    ui->edtUserPwd->setText( ui->userTableWidget->item( row, 3 )->text() );
}

void BatchUserDialog::on_ptnAdd_clicked()
{
    QString strID = ui->edtUserNo->text();
    QString strSql = "select * from tabuserinfo where UserID = '%1'";
    strSql = strSql.arg( strID );

    QString strName = ui->edtUserName->text();
    QString strSql2 = "select * from tabuserinfo where UserName = '%1'";
    strSql2 = strSql2.arg( strName );

    QString strError;
    QStringList lstRows;
    QString strName1 = "【%1】已经存在，请重新输入！";
    strName1 = strName1.arg( strID );
    QString strName2 = "【%1】已经存在，请重新输入！";
    strName2 = strName2.arg( strName );

    if( !CommFunction::VerifyIsEmpty( ui->edtUserNo->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtUserName->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtUserPwd->text() )
            && CommFunction::VerifyIsNumber( ui->edtUserNo->text() )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName1 )
            && CommFunction::VerifyIsUnique( strSql2, strError, lstRows, strName2 ) )
    {
       // 判断table表中是否存在。 判断strID
        for( int i = 0; i < ui->userTableWidget->rowCount(); ++i )
        {
            QString tmpID = ui->userTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }

        QTableWidgetItem *pItem0 = new QTableWidgetItem( ui->edtUserNo->text() );
        pItem0->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        //pItem0->setData( Qt::UserRole, g_ReceiverDetectorId );

        QTableWidgetItem *pItem1 = new QTableWidgetItem( ui->edtUserName->text() );
        pItem1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem2 = new QTableWidgetItem(  ui->edtUserComments->text() );
        pItem2->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem3 = new QTableWidgetItem( ui->edtUserPwd->text() );
        pItem3->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        int row = ui->userTableWidget->rowCount();
        ui->userTableWidget->setRowCount( row + 1 );

        ui->userTableWidget->setItem( row, 0, pItem0 );
        ui->userTableWidget->setItem( row, 1, pItem1 );
        ui->userTableWidget->setItem( row, 2, pItem2 );
        ui->userTableWidget->setItem( row, 3, pItem3 );
    }
}

void BatchUserDialog::on_ptnModify_clicked()
{
    if( ui->userTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要修改的行", "确定" );
        return;
    }

    QString strID = ui->edtUserNo->text();
    QString strSql = "select * from tabuserinfo where UserID = '%1'";
    strSql = strSql.arg( strID );

    QString strName = ui->edtUserName->text();
    QString strSql2 = "select * from tabuserinfo where UserName = '%1'";
    strSql2 = strSql2.arg( strName );

    QString strError;
    QStringList lstRows;
    QString strName1 = "【%1】已经存在，请重新输入！";
    strName1 = strName1.arg( strID );
    QString strName2 = "【%1】已经存在，请重新输入！";
    strName2 = strName2.arg( strName );

    if( !CommFunction::VerifyIsEmpty( ui->edtUserNo->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtUserName->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtUserPwd->text() )
            && CommFunction::VerifyIsNumber( ui->edtUserNo->text() )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName1 )
            && CommFunction::VerifyIsUnique( strSql2, strError, lstRows, strName2 ) )
    {
       // 判断table表中是否存在。 判断strID
        for( int i = 0; i < ui->userTableWidget->rowCount(); ++i )
        {
            if( i == ui->userTableWidget->currentRow() )
            {
                continue;
            }

            QString tmpID = ui->userTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpID ) )
            {
                QMessageBox::information( NULL, "提示", QString( "%1已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }

        int row = ui->userTableWidget->currentRow();
        ui->userTableWidget->item( row, 0 )->setText( ui->edtUserNo->text() );
        ui->userTableWidget->item( row, 1 )->setText( ui->edtUserName->text() );
        ui->userTableWidget->item( row, 2 )->setText( ui->edtUserComments->text() );
        ui->userTableWidget->item( row, 3 )->setText( ui->edtUserPwd->text() );
    }
}

void BatchUserDialog::on_ptnDelete_clicked()
{
    if( ui->userTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要删除的行", "确定" );
        return;
    }

    int row = ui->userTableWidget->currentRow();
    ui->userTableWidget->removeRow( row );
}

void BatchUserDialog::on_ptnSave_clicked()
{
    QString strBase = "( %1, '%2', '%3', %4, '%5' ) ";
    QString strSql = "insert into tabuserinfo values";

    QList<QTreeWidgetItem *> lstChildren;

    int nRows = ui->userTableWidget->rowCount();

    if( 0 == nRows )
    {
        return;
    }

    for( int i = 0; i < nRows; ++i )
    {
        strSql += strBase.arg( ui->userTableWidget->item( i, 0 )->text().toULongLong() )
                .arg( ui->userTableWidget->item( i, 1 )->text() )
                .arg( ui->userTableWidget->item( i, 2 )->text() )
                .arg( g_pid.toULongLong() ) // GroupId
                .arg( ui->userTableWidget->item( i, 3 )->text() );

        if( i != nRows - 1 )
        {
            strSql += ","; // 使得最后一个没有,
        }

        QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( ui->userTableWidget->item( i, 1 )->text() ) );

        ItemInfoUser newItemInfo;
        newItemInfo.setId( ui->userTableWidget->item( i, 0 )->text().toULongLong() );
        newItemInfo.setName( ui->userTableWidget->item( i, 1 )->text() );
        newItemInfo.setComments( ui->userTableWidget->item( i, 2 )->text() );
        newItemInfo.setPassword( ui->userTableWidget->item( i, 3 )->text() );
        newItemInfo.setPid( g_pid.toULongLong() ); // GroupId

        QVariant newValue;
        newValue.setValue( newItemInfo );
        childItem->setData( 0, Qt::WhatsThisRole, UserItem );
        childItem->setData( 0, Qt::UserRole, newValue );

        lstChildren.append( childItem );
    }

    QString strError;
    QStringList lstRows;
    CommFunction::OperateSql( strSql, strError, lstRows );

    currentItem->addChildren( lstChildren );

    close();
    this->setResult( BatchUserDialog::Accepted );
}

void BatchUserDialog::on_ptnClose_clicked()
{
    close();
}
