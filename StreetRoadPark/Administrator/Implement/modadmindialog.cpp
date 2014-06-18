#include "modadmindialog.h"
#include "ui_modadmindialog.h"
#include "Comm/commfunction.h"

ModAdminDialog::ModAdminDialog( QTreeWidgetItem *pItem, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::ModAdminDialog)
{
    ui->setupUi(this);

    currentItem = pItem;

    ui->cmbAdminType->setItemData( 0, QString( "Province" ), Qt::UserRole );
    ui->cmbAdminType->setItemData( 1, QString( "City" ), Qt::UserRole  );
    ui->cmbAdminType->setItemData( 2, QString( "District" ), Qt::UserRole  );

    QVariant varValue = pItem->data( 0, Qt::UserRole );
    ItemInfoAdmin curInfo = varValue.value<ItemInfoAdmin>();

    ui->edtAdminNo->setText( curInfo.getId() );
    ui->edtAdminName->setText( curInfo.getName() );
    ui->edtAdminComments->setText( curInfo.getComments() );

    ui->edtAdminNo->setEnabled( false );
    ui->edtAdminName->setEnabled( false );
    ui->cmbAdminType->setEnabled( false );

    if( 0 == curInfo.getType().compare( "Province" ) )
    {
        ui->cmbAdminType->setCurrentIndex( 0 );
    }
    else if( 0 == curInfo.getType().compare( "City" ) )
    {
        ui->cmbAdminType->setCurrentIndex( 1 );
    }
    else
    {
        ui->cmbAdminType->setCurrentIndex( 2 );
    }

    newAdminInfo.setPid( curInfo.getPid() );

    oldAdminId = curInfo.getId();
}

ModAdminDialog::~ModAdminDialog()
{
    delete ui;
}

void ModAdminDialog::on_ptnMod_clicked()
{
   // if( !CommFunction::VerifyIsEmpty( ui->edtAdminNo->text() )&&!CommFunction::VerifyIsEmpty( ui->edtAdminName->text() ) && CommFunction::VerifyIsNumber( ui->edtAdminNo->text() ) )
    {
        /*
        QString strSql = "update tabadministrativeinfo set AdministrativeName = '%1', AdministrativeComments = '%2', AdministrativeType = '%3', AdministrativeID = '%4'"
                " where AdministrativeID = '%5'";
        strSql = strSql.arg( ui->edtAdminName->text() ).arg( ui->edtAdminComments->text() )
                .arg( ui->cmbAdminType->itemData( ui->cmbAdminType->currentIndex(), Qt::UserRole ).toString() )
                .arg( ui->edtAdminNo->text() ).arg( oldAdminId );
*/
        QString strSql = "update tabadministrativeinfo set AdministrativeComments = '%1'"
                " where AdministrativeID = '%2'";
        strSql = strSql.arg( ui->edtAdminComments->text() ).arg( oldAdminId );
        CommFunction::OperateModQuery( strSql );

        newAdminInfo.setId( ui->edtAdminNo->text() );
        newAdminInfo.setName( ui->edtAdminName->text() );
        newAdminInfo.setComments( ui->edtAdminComments->text() );
        newAdminInfo.setType( ui->cmbAdminType->itemData( ui->cmbAdminType->currentIndex(), Qt::UserRole ).toString() );

        currentItem->setText( 0, ui->edtAdminName->text() );
        QVariant var;
        var.setValue( newAdminInfo );
        currentItem->setData( 0, Qt::UserRole, var );

        close();
        this->setResult( ModAdminDialog::Accepted );
    }
}

void ModAdminDialog::on_ptnCancel_clicked()
{
    close();
}
