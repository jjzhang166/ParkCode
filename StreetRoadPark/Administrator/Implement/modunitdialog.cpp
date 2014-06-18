#include "modunitdialog.h"
#include "ui_modunitdialog.h"
#include "Comm/commfunction.h"

ModUnitDialog::ModUnitDialog( QTreeWidgetItem * pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModUnitDialog)
{
    ui->setupUi(this);
    currentItem = pItem;

    QVariant varValue = pItem->data( 0, Qt::UserRole );
    ItemInfoUnit curInfo = varValue.value<ItemInfoUnit>();

    ui->edtUnitNo->setText( curInfo.getId() );
    ui->edtUnitName->setText( curInfo.getName() );
    ui->edtUnitComments->setText( curInfo.getComments() );
    ui->edtUnitAddress->setText( curInfo.getAddress() );

    newUnitInfo.setPid( curInfo.getPid() );
    oldUnitID = curInfo.getId();
}

ModUnitDialog::~ModUnitDialog()
{
    delete ui;
}

void ModUnitDialog::on_ptnMod_clicked()
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


    if( !CommFunction::VerifyIsEmpty( ui->edtUnitNo->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtUnitName->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtUnitAddress->text() )
            && CommFunction::VerifyLength( ui->edtUnitNo->text(), 9 )
            && CommFunction::VerifyIsNumber( ui->edtUnitNo->text() )
            && CommFunction::VerifyIsUnique( strSql1, strError, lstRows, strName1 )
            && CommFunction::VerifyIsUnique( strSql2, strError, lstRows, strName2 ) )
    {
        QString strSql = "update tabunitinfo set UnitName = '%1', UnitComments = '%2', UnitAddress = '%3', UnitID = '%4' "
                " where UnitID = '%5'";
        strSql = strSql.arg( ui->edtUnitName->text() ).arg( ui->edtUnitComments->text() )
                .arg( ui->edtUnitAddress->text() ).arg( ui->edtUnitNo->text() ).arg( oldUnitID );

        CommFunction::OperateModQuery( strSql );
/*                     // 数据库自动更新外键。
        // update foreign keys
        strSql = "select ParkID from tabparkinfo where UnitID = '%1'";
        strSql = strSql.arg( oldUnitID );
        QStringList lstRows;
        QString strWhere = "";

        if( CommFunction::OperateSql( strSql, strError, lstRows ) )
        {
            strWhere += QString( "ParkID = '%2'" );
            for( int i = 1; i < lstRows.size() - 1; ++i )
            {
                strWhere += QString( " and ParkID = '%%1" ).arg( i + 2 ) + "', ";
            }
            strWhere += QString( " and ParkID = '%%1" ).arg( lstRows.size() + 1 ) + "' ";

            strSql = "update tabparkinfo set UnitID = '%1' where ";
            strSql += strWhere;

            strSql = strSql.arg( ui->edtUnitNo->text() );
            for( int i = 0; i < lstRows.size(); ++i )
            {
                strSql = strSql.arg( lstRows[i] );
            }

            CommFunction::OperateModQuery( strSql );
        }
*/
        newUnitInfo.setId( ui->edtUnitNo->text() );
        newUnitInfo.setName( ui->edtUnitName->text() );
        newUnitInfo.setComments( ui->edtUnitComments->text() );
        newUnitInfo.setAddress( ui->edtUnitAddress->text() );

        currentItem->setText( 0, ui->edtUnitName->text() );
        QVariant var;
        var.setValue( newUnitInfo );
        currentItem->setData( 0, Qt::UserRole, var );

        close();
        this->setResult( ModUnitDialog::Accepted );
    }
}

void ModUnitDialog::on_ptnCancel_clicked()
{
    close();
}
