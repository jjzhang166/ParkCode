#include "modgroupdialog.h"
#include "ui_modgroupdialog.h"
#include "Comm/commfunction.h"
#include "ItemInfos/iteminfogroup.h"
#include "ItemInfos/ItemType.h"

ModGroupDialog::ModGroupDialog(QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModGroupDialog)
{
    ui->setupUi(this);
    currentItem = pItem;

    QVariant varValue = pItem->data( 0, Qt::UserRole );
    ItemInfoGroup curInfo = varValue.value<ItemInfoGroup>();

    ui->edtGroupNo->setText( QString::number( curInfo.getId() ) );
    ui->edtGroupNo->setEnabled( false );
    ui->edtGroupName->setText( curInfo.getName() );
    ui->edtGroupComments->setText( curInfo.getComments() );
    ui->spbGroupRight->setValue( curInfo.getGroupRight() );
    g_groupParentId = curInfo.getParentID();
    g_pid = curInfo.getPid();
    strOldGroupName = curInfo.getName();
}

ModGroupDialog::~ModGroupDialog()
{
    delete ui;
}

void ModGroupDialog::on_ptnMod_clicked()
{
    QString strGroupName = ui->edtGroupName->text();
    QString strSql = "select * from tabgroupinfo where GroupName = '%1'";
    strSql = strSql.arg( strGroupName );

    QString strError;
    QStringList lstRows;
    QString strName = "【%1】已经存在，请重新输入！";
    strName = strName.arg( strGroupName );

    if( 0 != strOldGroupName.compare( strGroupName ) )
    {
        if( !CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
        {
            return;
        }
    }

    if( !CommFunction::VerifyIsEmpty( ui->edtGroupName->text() ) )
    {
        strSql = "update tabgroupinfo set GroupName = '%1', GroupComments = '%2', GroupRight = %3 where GroupID = %4";
        strSql = strSql.arg( ui->edtGroupName->text() ).arg( ui->edtGroupComments->text() )
                .arg( ui->spbGroupRight->text().toULongLong() ).arg( ui->edtGroupNo->text().toULongLong() );

        CommFunction::OperateSql( strSql, strError, lstRows );

        ItemInfoGroup newItemInfo;
        newItemInfo.setId( ui->edtGroupNo->text().toULongLong() );
        newItemInfo.setName( ui->edtGroupName->text() );
        newItemInfo.setComments( ui->edtGroupComments->text() );
        newItemInfo.setParentID( g_groupParentId );
        newItemInfo.setGroupRight( ui->spbGroupRight->text().toULongLong() );
        newItemInfo.setPid( g_pid ); // UnitID

        QVariant newValue;
        newValue.setValue( newItemInfo );
        currentItem->setText( 0, ui->edtGroupName->text() );
        currentItem->setData( 0, Qt::WhatsThisRole, GroupItem );
        currentItem->setData( 0, Qt::UserRole, newValue );

        close();
        this->setResult( ModGroupDialog::Accepted );
    }
}

void ModGroupDialog::on_ptnCancel_clicked()
{
    close();
}
