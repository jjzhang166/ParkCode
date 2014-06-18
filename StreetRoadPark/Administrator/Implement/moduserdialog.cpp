#include "moduserdialog.h"
#include "ui_moduserdialog.h"
#include "Comm/commfunction.h"
#include "ItemInfos/iteminfouser.h"
#include "ItemInfos/ItemType.h"

ModUserDialog::ModUserDialog( QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModUserDialog)
{
    ui->setupUi(this);
    currentItem = pItem;

    QVariant varValue = pItem->data( 0, Qt::UserRole );
    ItemInfoUser curInfo = varValue.value<ItemInfoUser>();

    ui->edtUserNo->setText( QString::number( curInfo.getId() ) );
    ui->edtUserNo->setEnabled( false );
    ui->edtUserName->setText( curInfo.getName() );
    ui->edtUserComments->setText( curInfo.getComments() );
    ui->edtUserPwd->setText( curInfo.getPassword() );
    g_pid = curInfo.getPid();
    strOldName = curInfo.getName();
}

ModUserDialog::~ModUserDialog()
{
    delete ui;
}

void ModUserDialog::on_ptnMod_clicked()
{
    QString strUserName = ui->edtUserName->text();
    QString strSql = "select * from tabuserinfo where UserName = '%1'";
    strSql = strSql.arg( strUserName );
    QString strError;
    QStringList lstRows;
    QString strName = "【%1】已经存在，请重新输入！";
    strName = strName.arg( strUserName );

    if( 0 != strOldName.compare( strUserName ) )
    {
        if( !CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
        {
            return;
        }
    }

    if( !CommFunction::VerifyIsEmpty( ui->edtUserName->text() ) )
    {
        strSql = "update tabuserinfo set UserName = '%1', UserComments = '%2', UserPwd = '%3' where UserID = %4 ";
        strSql = strSql.arg( ui->edtUserName->text() ).arg( ui->edtUserComments->text() )
                .arg( ui->edtUserPwd->text() ).arg( ui->edtUserNo->text().toULongLong() );       

        CommFunction::OperateSql( strSql, strError, lstRows );

        ItemInfoUser newItemInfo;
        newItemInfo.setId( ui->edtUserNo->text().toULongLong() );
        newItemInfo.setName( ui->edtUserName->text() );
        newItemInfo.setComments( ui->edtUserComments->text() );
        newItemInfo.setPassword( ui->edtUserPwd->text() );
        newItemInfo.setPid( g_pid ); // GroupID

        QVariant newValue;
        newValue.setValue( newItemInfo );
        currentItem->setData( 0, Qt::WhatsThisRole, UserItem );
        currentItem->setData( 0, Qt::UserRole, newValue );

        close();
        this->setResult( ModUserDialog::Accepted );
    }
}

void ModUserDialog::on_ptnCancel_clicked()
{
    close();
}
