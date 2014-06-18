#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include "Comm/commfunction.h"

AddUserDialog::AddUserDialog( QString pid, QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
    g_pid = pid;
    currentItem = pItem;
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::on_ptnAdd_clicked()
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
        strSql = "insert into tabuserinfo values( %1, '%2', '%3', %4, '%5' )";
        strSql = strSql.arg( ui->edtUserNo->text().toULongLong() ).arg( ui->edtUserName->text() ).arg( ui->edtUserComments->text() )
                .arg( g_pid.toULongLong() ).arg( ui->edtUserPwd->text() );

        CommFunction::OperateSql( strSql, strError, lstRows );

        QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( ui->edtUserName->text() ) );
        ItemInfoUser newItemInfo;
        newItemInfo.setId( ui->edtUserNo->text().toULongLong() );
        newItemInfo.setName( ui->edtUserName->text() );
        newItemInfo.setComments( ui->edtUserComments->text() );
        newItemInfo.setPassword( ui->edtUserPwd->text() );
        newItemInfo.setPid( g_pid.toULongLong() ); // UnitID

        QVariant newValue;
        newValue.setValue( newItemInfo );
        childItem->setData( 0, Qt::WhatsThisRole, UserItem );
        childItem->setData( 0, Qt::UserRole, newValue );
        currentItem->addChild( childItem );

        close();
        this->setResult( AddUserDialog::Accepted );
    }
}

void AddUserDialog::on_ptnCancel_clicked()
{
    close();
}
