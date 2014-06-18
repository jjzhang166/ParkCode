#include "addgroupdialog.h"
#include "ui_addgroupdialog.h"
#include "Comm/commfunction.h"

AddGroupDialog::AddGroupDialog(QString groupParentId, QString pid, QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGroupDialog)
{
    ui->setupUi(this);
    g_groupParentId = groupParentId;
    g_pid = pid;
    currentItem = pItem;
}

AddGroupDialog::~AddGroupDialog()
{
    delete ui;
}

void AddGroupDialog::on_ptnAdd_clicked()
{
    QString strID = ui->edtGroupNo->text();
    QString strSql = "select * from tabgroupinfo where GroupID = %1";
    strSql = strSql.arg( strID.toULongLong() );
    QString strError;
    QStringList lstRows;

    QString strName = ui->edtGroupName->text();
    QString strSql2 = "select * from tabgroupinfo where GroupName = '%1'";
    strSql2 = strSql2.arg( strName );

    QString strName1 = "【%1】已经存在，请重新输入！";
    strName1 = strName1.arg( strID );
    QString strName2 = "【%1】已经存在，请重新输入！";
    strName2 = strName2.arg( strName );


    if( !CommFunction::VerifyIsEmpty( ui->edtGroupNo->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtGroupName->text() )
            && CommFunction::VerifyIsNumber( ui->edtGroupNo->text() )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName1 )
            && CommFunction::VerifyIsUnique( strSql2, strError, lstRows, strName2 ) )
    {
        strSql = "insert into tabgroupinfo values( %1, '%2', '%3', %4, %5, '%6' )";
        strSql = strSql.arg( ui->edtGroupNo->text().toULongLong() ).arg( ui->edtGroupName->text() ).arg( ui->edtGroupComments->text() )
                .arg( g_groupParentId ).arg( ui->spbGroupRight->text().toULongLong() ).arg( g_pid );

        CommFunction::OperateSql( strSql, strError, lstRows );

        QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( ui->edtGroupName->text() ) );
        ItemInfoGroup newItemInfo;
        newItemInfo.setId( ui->edtGroupNo->text().toULongLong() );
        newItemInfo.setName( ui->edtGroupName->text() );
        newItemInfo.setComments( ui->edtGroupComments->text() );
        newItemInfo.setParentID( g_groupParentId.toULongLong() );
        newItemInfo.setGroupRight( ui->spbGroupRight->text().toULongLong() );
        newItemInfo.setPid( g_pid ); // UnitID

        QVariant newValue;
        newValue.setValue( newItemInfo );
        childItem->setData( 0, Qt::WhatsThisRole, GroupItem );
        childItem->setData( 0, Qt::UserRole, newValue );
        currentItem->addChild( childItem );

        close();
        this->setResult( AddGroupDialog::Accepted );
    }
}

void AddGroupDialog::on_ptnCancel_clicked()
{
    close();
}
