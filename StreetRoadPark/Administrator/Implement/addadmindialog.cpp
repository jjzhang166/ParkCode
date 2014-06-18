#include "addadmindialog.h"
#include "ui_addadmindialog.h"
#include "Implement/iterfacetomysql.h"
#include "Comm/commfunction.h"

AddAdminDialog::AddAdminDialog( QTreeWidgetItem *pItem, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::AddAdminDialog)
{
    ui->setupUi(this);
    currentItem = pItem;

    QVariant varValue = pItem->data( 0, Qt::UserRole );
    ItemInfoAdmin adminInfo = varValue.value<ItemInfoAdmin>();
    QString pID = adminInfo.getId();

    QString strSql = "select * from tabchinainfo where AdministrativeParentID = '%1'";
    strSql = strSql.arg( pID );

    GetCmbItem( strSql );
}

AddAdminDialog::~AddAdminDialog()
{
    delete ui;
}

void AddAdminDialog::GetCmbItem( QString &strSql )
{
    QString strError;
    QStringList lstRows;

    CommFunction::OperateSql( strSql, strError, lstRows );
    int nRows = 0;
    int nCols = 5;
    nRows = lstRows.count() / nCols;

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

        ui->cmbAdmin->addItem( curValue.getName(), var );
    }
}

QStringList &AddAdminDialog::GetAdminItemInfo() // not use
{
    return lstInfos;
}

bool AddAdminDialog::Verify() // not use
{
    QString strID ;//= ui->edtAdminNo->text();
    if( !IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql() )
    {
        return false;
    }

    QString strSql = "select * from tabadministrativeinfo where AdministrativeID = '%1'";
    strSql = strSql.arg( strID );
    QString strError;
    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    QStringList lstRows;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    if( !lstRows.isEmpty() )
    {
        QMessageBox::information( NULL, QString("提示"), QString("【%1】已存在， 请重新输入！").arg( strID ), "确定" );
        return false;
    }

    return true;
}

void AddAdminDialog::on_ptnAdd_clicked()
{
    QVariant curValue = ui->cmbAdmin->itemData( ui->cmbAdmin->currentIndex(), Qt::UserRole );
    ItemInfoAdmin curCmbInfo = curValue.value<ItemInfoAdmin>();

    curCmbInfo.setComments( ui->edtAdminComments->text() );
    curValue.setValue( curCmbInfo ); // 更新

    QString strError = "";
    QStringList lstRows;
    // VerifyIsUnique 是否已经存在
    QString strSql = "select * from tabadministrativeinfo where AdministrativeID = '%1'";
    strSql = strSql.arg( curCmbInfo.getId() );
    QString strName = "【%1】已经存在，请重新选择！";
    strName = strName.arg( curCmbInfo.getName() );
    if( !CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
    {
        return;
    }

    QTreeWidgetItem *child = new QTreeWidgetItem( QStringList( curCmbInfo.getName() ) );
    child->setData( 0, Qt::UserRole, curValue );
    child->setData( 0, Qt::WhatsThisRole, AdminItem );
    currentItem->addChild( child );

    strSql = "insert into tabadministrativeinfo values( '%1', '%2', '%3', '%4', '%5' ) ";
    strSql = strSql.arg( curCmbInfo.getId() ).arg( curCmbInfo.getName() ).arg( curCmbInfo.getComments() )
            .arg(curCmbInfo.getPid() ).arg( curCmbInfo.getType() );

    strError.clear();
    lstRows.clear();
    CommFunction::OperateSql( strSql, strError, lstRows );

    if( strError.isEmpty() )
    {
        close();
        this->setResult( AddAdminDialog::Accepted );
    }
}

void AddAdminDialog::on_ptnCancel_clicked()
{
    close();
}
