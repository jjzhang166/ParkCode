#include "batchadmindialog.h"
#include "ui_batchadmindialog.h"
#include "ItemInfos/iteminfoadmin.h"
#include "Comm/commfunction.h"
#include "ItemInfos/ItemType.h"

#include <QMessageBox>

BatchAdminDialog::BatchAdminDialog( QTreeWidgetItem *pItem, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::BatchAdminDialog)
{
    ui->setupUi(this);
    currentItem = pItem;

    InitAdminCmb();

}

BatchAdminDialog::~BatchAdminDialog()
{
    delete ui;
}

void BatchAdminDialog::InitAdminCmb()
{
    QVariant varValue = currentItem->data( 0, Qt::UserRole );
    ItemInfoAdmin adminInfo = varValue.value<ItemInfoAdmin>();
    QString pID = adminInfo.getId();

    QString strSql = "select * from tabchinainfo where AdministrativeParentID = '%1'";
    strSql = strSql.arg( pID );
    QString strError;
    QStringList lstRows;

    CommFunction::OperateSql( strSql, strError, lstRows );
    int nRows = 0;
    int nCols = 5;
    nRows = lstRows.count() / nCols;
    QList<ItemInfoAdmin> AdminList;

    for( int i = 0; i < lstRows.count(); ++i )
    {
        ItemInfoAdmin tmpItem;
        tmpItem.setId( lstRows[i] );
        tmpItem.setName( lstRows[++i] );
        tmpItem.setComments( lstRows[++i] );
        tmpItem.setPid( lstRows[++i] );
        tmpItem.setType( lstRows[++i] );
        AdminList.push_back( tmpItem );
    }

    // init cmb items
    for( int i = 0; i < AdminList.size(); ++i )
    {
        const ItemInfoAdmin curValue = AdminList[i];
        QVariant var;
        var.setValue( curValue );

        ui->cbxAdmin->addItem( curValue.getName(), var );
    }
}

void BatchAdminDialog::on_ptnAdd_clicked()
{
    QVariant varValue = ui->cbxAdmin->itemData( ui->cbxAdmin->currentIndex(), Qt::UserRole );
    ItemInfoAdmin curInfo = varValue.value<ItemInfoAdmin>();

    // // 判断是否已经添加，数据库中是否存在。
    QString strSql = "select * from tabadministrativeinfo where AdministrativeID = '%1'";
    strSql = strSql.arg( curInfo.getId() );
    QString strError;
    QStringList lstRows;
    QString strName = "【%1】已经存在，请重新选择！";
    strName = strName.arg( curInfo.getName() );
    if( !CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
    {
        return;
    }

    // 判断table表中是否存在。
    QString strID = curInfo.getId();
    for( int i = 0; i < ui->adminTableWidget->rowCount(); ++i )
    {
        QVariant tmpValue = ui->adminTableWidget->item( i, 0 )->data( Qt::UserRole );
        ItemInfoAdmin tmpInfo = tmpValue.value<ItemInfoAdmin>();

        if( 0 == strID.compare( tmpInfo.getId() ) )
        {
            QMessageBox::information( NULL, "提示", QString( "【%1】已经存在，请重新选择！" ).arg( tmpInfo.getName() ), "确定" );
            return;
        }
    }

    curInfo.setComments( ui->edtComments->text() ); // Info 更新
    varValue.setValue( curInfo ); // variant 更新

    QTableWidgetItem *pItem0 = new QTableWidgetItem( ui->cbxAdmin->currentText() );
    pItem0->setData( Qt::UserRole, varValue );
    /*
Qt::NoItemFlags	0	It does not have any properties set.
Qt::ItemIsSelectable	1	It can be selected.
Qt::ItemIsEditable	2	It can be edited.
Qt::ItemIsDragEnabled	4	It can be dragged.
Qt::ItemIsDropEnabled	8	It can be used as a drop target.
Qt::ItemIsUserCheckable	16	It can be checked or unchecked by the user.
Qt::ItemIsEnabled	32	The user can interact with the item.
Qt::ItemIsTristate

*/
    pItem0->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled ); // Qt::ItemIsSelectable

    QTableWidgetItem *pItem1 = new QTableWidgetItem( ui->edtComments->text() );
    pItem1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    int row = ui->adminTableWidget->rowCount();
    ui->adminTableWidget->setRowCount( row + 1 );

    ui->adminTableWidget->setItem( row, 0, pItem0 );
    ui->adminTableWidget->setItem( row, 1, pItem1 );
}

void BatchAdminDialog::on_ptnModify_clicked()
{
    if( ui->adminTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要修改的行", "确定" );
        return;
    }

    QVariant varValue = ui->cbxAdmin->itemData( ui->cbxAdmin->currentIndex(), Qt::UserRole );
    ItemInfoAdmin curInfo = varValue.value<ItemInfoAdmin>();

    // // 判断是否已经添加，数据库中是否存在。
    QString strSql = "select * from tabadministrativeinfo where AdministrativeID = '%1'";
    strSql = strSql.arg( curInfo.getId() );
    QString strError;
    QStringList lstRows;
    QString strName = "【%1】已经存在，请重新选择！";
    strName = strName.arg( curInfo.getName() );
    if( !CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
    {
        return;
    }


    // 判断table表中是否存在。
    QString strID = curInfo.getId();
    for( int i = 0; i < ui->adminTableWidget->rowCount(); ++i )
    {
        if( i == ui->adminTableWidget->currentRow() )
        {
            continue;
        }

        QVariant tmpValue = ui->adminTableWidget->item( i, 0 )->data( Qt::UserRole );
        ItemInfoAdmin tmpInfo = tmpValue.value<ItemInfoAdmin>();

        if( 0 == strID.compare( tmpInfo.getId() ) )
        {
            QMessageBox::information( NULL, "提示", QString( "【%1】已经存在，请重新选择！" ).arg( tmpInfo.getName() ), "确定" );
            return;
        }
    }

    int row = ui->adminTableWidget->currentRow();
    ui->adminTableWidget->item( row, 0 )->setText( ui->cbxAdmin->currentText() );

   // QVariant varValue = ui->cbxAdmin->itemData( ui->cbxAdmin->currentIndex(), Qt::UserRole );
    //ItemInfoAdmin curInfo = varValue.value<ItemInfoAdmin>();

    curInfo.setComments( ui->edtComments->text() ); // Info 更新
    varValue.setValue( curInfo ); // variant 更新

    ui->adminTableWidget->item( row, 0 )->setData( Qt::UserRole, varValue );

    ui->adminTableWidget->item( row, 1 )->setText( ui->edtComments->text() );
}

void BatchAdminDialog::on_ptnDelete_clicked()
{
    if( ui->adminTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要删除的行", "确定" );
        return;
    }

    int row = ui->adminTableWidget->currentRow();
    ui->adminTableWidget->removeRow( row );
}

void BatchAdminDialog::on_ptnSave_clicked()
{
    QString strBase = "( '%1', '%2', '%3', '%4', '%5' ) ";
    QString strSql = "replace into tabadministrativeinfo values";
    QStringList lstValues;

    QList<QTreeWidgetItem *> lstChildren;

    int nRows = ui->adminTableWidget->rowCount();
    int nCols = ui->adminTableWidget->columnCount();
    if( 0 == nRows )
    {
        return;
    }

    for( int i = 0; i < nRows; ++i )
    {
        for( int j = 0; j < nCols; ++j )
        {
            if( 0 == j )
            {
                QVariant varValue = ui->adminTableWidget->item( i, j )->data( Qt::UserRole );
                ItemInfoAdmin curInfo = varValue.value<ItemInfoAdmin>();
                lstValues << curInfo.getId() << curInfo.getName() << curInfo.getComments()
                          << curInfo.getPid() << curInfo.getType();

                QTreeWidgetItem *child = new QTreeWidgetItem( QStringList( curInfo.getName() ) );
                child->setData( 0, Qt::UserRole, varValue );
                child->setData( 0, Qt::WhatsThisRole, AdminItem );

                lstChildren.append( child );
            }
            else
            {
                break;
            }
        }
    }

    for( int i = 0; i < lstValues.size() / 5 - 1; ++i ) // == i < nRows
    {
        strSql += strBase.arg( lstValues[ i * 5 + 0 ] ).arg( lstValues[ i * 5 + 1 ] ).arg( lstValues[ i * 5 + 2 ] )
                .arg( lstValues[ i * 5 + 3 ] ).arg( lstValues[ i * 5 + 4 ] );
        strSql += ",";
    }

    strSql += strBase.arg( lstValues[ (nRows - 1) * 5 + 0 ] ).arg( lstValues[ (nRows - 1) * 5 + 1 ] )
            .arg( lstValues[ (nRows - 1) * 5 + 2 ] ).arg( lstValues[ (nRows - 1) * 5 + 3 ] )
            .arg( lstValues[ (nRows - 1) * 5 + 4 ] );

    QString strError;
    QStringList lstRows;
    CommFunction::OperateSql( strSql, strError, lstRows );

    currentItem->addChildren( lstChildren );

    close();
    this->setResult( BatchAdminDialog::Accepted );
}

void BatchAdminDialog::on_ptnClose_clicked()
{
    close();
}

void BatchAdminDialog::on_adminTableWidget_cellClicked(int row, int column)
{
    QString strAdmin = ui->adminTableWidget->item( row, 0 )->text();
    QString strComments = ui->adminTableWidget->item( row, 1 )->text();

    ui->cbxAdmin->setCurrentText( strAdmin );
    ui->edtComments->setText( strComments );

    ui->adminTableWidget->item( row, column )->setSelected( true );

}
