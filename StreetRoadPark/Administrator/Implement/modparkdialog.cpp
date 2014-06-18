#include "modparkdialog.h"
#include "ui_modparkdialog.h"
#include "Comm/commfunction.h"

ModParkDialog::ModParkDialog(QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModParkDialog)
{
    ui->setupUi(this);
    currentItem = pItem;

    QVariant varValue = pItem->data( 0, Qt::UserRole );
    ItemInfoPark curInfo = varValue.value<ItemInfoPark>();

    ui->edtParkNo->setText( curInfo.getId() );
    ui->edtParkNo->setEnabled( false );
    ui->edtParkName->setText( curInfo.getName() );
    ui->edtParkComments->setText( curInfo.getComments() );
    ui->edtParkSpace->setText( QString::number( curInfo.getSpace() ) );
    ui->edtUsedSpace->setText( QString::number( curInfo.getUsedSpace() ) );
    ui->edtParkSelfNum->setText( curInfo.getSelfNumber() );

    newParkInfo.setParkParentID( curInfo.getParkParentID() );
    newParkInfo.setPid( curInfo.getPid() );
}

ModParkDialog::~ModParkDialog()
{
    delete ui;
}

void ModParkDialog::on_ptnMod_clicked()
{
    if( !CommFunction::VerifyIsEmpty( ui->edtParkName->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtParkSpace->text() )
            && CommFunction::VerifyIsNumber( ui->edtParkSpace->text() )
            && CommFunction::VerifyIsNumber( ui->edtUsedSpace->text() )
            && CommFunction::VerifyIsNumber( ui->edtParkSelfNum->text() ) )
    {
        QString strSql = "update tabparkinfo set ParkName = '%1', ParkSpace = %2, UsedSpace = %3, ParkSelfNumber = '%4', ParkComments = '%5' "
                " where ParkID = '%6'";
        strSql = strSql.arg( ui->edtParkName->text() ).arg( ui->edtParkSpace->text().toInt() )
                .arg( ui->edtUsedSpace->text().toInt() ).arg( ui->edtParkSelfNum->text() )
                .arg( ui->edtParkComments->text() ).arg( ui->edtParkNo->text() );

        CommFunction::OperateModQuery( strSql );

        newParkInfo.setId( ui->edtParkNo->text() );
        newParkInfo.setName( ui->edtParkName->text() );
        newParkInfo.setComments( ui->edtParkComments->text() );
        newParkInfo.setSpace( ui->edtParkSpace->text().toUShort() );
        newParkInfo.setUsedSpace( ui->edtUsedSpace->text().toUShort() );
        newParkInfo.setSelfNumber( ui->edtParkSelfNum->text() );

        currentItem->setText( 0, ui->edtParkName->text() );
        QVariant var;
        var.setValue( newParkInfo );
        currentItem->setData( 0, Qt::UserRole, var );

        close();
        this->setResult( ModParkDialog::Accepted );
    }
}

void ModParkDialog::on_ptnCancel_clicked()
{
    close();
}
