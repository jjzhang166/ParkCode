#include "moddetectordialog.h"
#include "ui_moddetectordialog.h"
#include "Comm/commfunction.h"

ModDetectorDialog::ModDetectorDialog( QTreeWidgetItem * pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModDetectorDialog)
{
    ui->setupUi(this);
    currentItem = pItem;

    QVariant varValue = pItem->data( 0, Qt::UserRole );
    ItemInfoDetector curInfo = varValue.value<ItemInfoDetector>();

    ui->edtDetectorNo->setText( curInfo.getId() );
    ui->edtDetectorNo->setEnabled( false );
    ui->edtDetectorChannelID->setText( QString::number( curInfo.getChannelID() ) );
    ui->edtDetectorComments->setText( curInfo.getComments() );

    ui->cmbReset->setCurrentIndex( (int)curInfo.getDetectorReset() );
    ui->sbxDelayTime->setValue( curInfo.getDelayTime() );
    ui->sbxThreshold->setValue( curInfo.getThreshold() );

    receiverDetectorID = curInfo.getReceiverDetectorID();

    newDetectorInfo.setPid( curInfo.getPid() );
    newDetectorInfo.setReceiverDetectorID( curInfo.getReceiverDetectorID() );
}

ModDetectorDialog::~ModDetectorDialog()
{
    delete ui;
}

void ModDetectorDialog::on_ptnMod_clicked()
{
    if( !CommFunction::VerifyIsEmpty( ui->cmbReset->currentText() )
            && CommFunction::VerifyIsNumber( ui->edtDetectorChannelID->text() )
            && CommFunction::VerifyMinMax( ui->edtDetectorChannelID->text(), 0, 255 ) )
    {
        QString strSql = "update tabdetectorinfo set DetectorID = '%1', DetectorChannelID = %2, DetectorComments = '%3', Threshold = %4, DelayTime = %5, DetectorReset = %6 "
                " where ReceiverDetectorID = '%7'";
        strSql = strSql.arg( ui->edtDetectorNo->text() ).arg( ui->edtDetectorChannelID->text().toUShort() )
                .arg( ui->edtDetectorComments->text() ).arg( ui->sbxThreshold->text().toUShort() ).arg( ui->sbxDelayTime->text().toUShort() )
                .arg( ui->cmbReset->itemData( ui->cmbReset->currentIndex(), Qt::UserRole ).toInt() ).arg( receiverDetectorID );

        CommFunction::OperateModQuery( strSql );

        newDetectorInfo.setId( ui->edtDetectorNo->text() );
        newDetectorInfo.setDelayTime( ui->sbxDelayTime->text().toUShort() );
        newDetectorInfo.setThreshold( ui->sbxThreshold->text().toUShort() );
        newDetectorInfo.setComments( ui->edtDetectorComments->text() );
        newDetectorInfo.setChannelID( ui->edtDetectorChannelID->text().toUShort() );
        newDetectorInfo.setDetectorReset( ui->cmbReset->itemData( ui->cmbReset->currentIndex(), Qt::UserRole ).toInt() );

        currentItem->setText( 0, ui->edtDetectorNo->text() );
        QVariant var;
        var.setValue( newDetectorInfo );
        currentItem->setData( 0, Qt::UserRole, var );

        close();
        this->setResult( ModDetectorDialog::Accepted );
    }
}

void ModDetectorDialog::on_ptnCancel_clicked()
{
    close();
}
