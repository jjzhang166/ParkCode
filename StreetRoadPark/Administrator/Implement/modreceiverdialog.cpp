#include "modreceiverdialog.h"
#include "ui_modreceiverdialog.h"
#include "Comm/commfunction.h"

ModReceiverDialog::ModReceiverDialog(QTreeWidgetItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModReceiverDialog)
{
    ui->setupUi(this);
    currentItem = pItem;

    QVariant varValue = pItem->data( 0, Qt::UserRole );
    ItemInfoReceiver curInfo = varValue.value<ItemInfoReceiver>();

    ui->edtReceiverNo->setText( curInfo.getId() );
    ui->edtReceiverNo->setEnabled( false );
    ui->edtReceiverName->setText( curInfo.getName() );
    ui->edtReceiverComments->setText( curInfo.getComments() );
    ui->edtChannelID->setText( QString::number( curInfo.getChannelID() ) );
    parkReceiverID = curInfo.getParkReceiverID();

    newReceiverInfo.setParkReceiverID( curInfo.getParkReceiverID() );
    newReceiverInfo.setPid( curInfo.getPid() );
}

ModReceiverDialog::~ModReceiverDialog()
{
    delete ui;
}

void ModReceiverDialog::on_ptnMod_clicked()
{
    if( !CommFunction::VerifyIsEmpty( ui->edtChannelID->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtReceiverName->text() )
            && CommFunction::VerifyIsNumber( ui->edtChannelID->text() )
            && CommFunction::VerifyMinMax( ui->edtChannelID->text(), 0, 255 ) )
    {
        QString strSql = "update tabreceiverinfo set ReceiverName = '%1', ReceiverChannelID = %2, ReceiverComments = '%3' "
                " where ParkReceiverID = '%4'";
        strSql = strSql.arg( ui->edtReceiverName->text() ).arg( ui->edtChannelID->text().toInt() )
                .arg( ui->edtReceiverComments->text() ).arg( parkReceiverID );

        CommFunction::OperateModQuery( strSql );

        // not change also need set
        newReceiverInfo.setId( ui->edtReceiverNo->text() );
        newReceiverInfo.setName( ui->edtReceiverName->text() );
        newReceiverInfo.setComments( ui->edtReceiverComments->text() );
        newReceiverInfo.setChannelID( ui->edtChannelID->text().toUShort() );

        currentItem->setText( 0, ui->edtReceiverName->text() );
        QVariant var;
        var.setValue( newReceiverInfo );
        currentItem->setData( 0, Qt::UserRole, var );

        close();
        this->setResult( ModReceiverDialog::Accepted );
    }
}

void ModReceiverDialog::on_ptnCancel_clicked()
{
    close();
}
