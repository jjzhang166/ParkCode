#include "batchdetectordialog.h"
#include "ui_batchdetectordialog.h"
#include "ItemInfos/iteminfodetector.h"
#include "Comm/commfunction.h"
#include "ItemInfos/ItemType.h"

#include <QMessageBox>

BatchDetectorDialog::BatchDetectorDialog(QTreeWidgetItem *pItem, QString parkReceiverId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchDetectorDialog)
{
    ui->setupUi(this);
    currentItem = pItem;
    g_parkReceiverId.append( parkReceiverId );
    ui->cmbReset->setItemData( 0, "1", Qt::UserRole ); // 是
    ui->cmbReset->setItemData( 1, "0", Qt::UserRole ); // 否
    ui->edtDetectorNo->setFocus();
}

BatchDetectorDialog::~BatchDetectorDialog()
{
    delete ui;
}

void BatchDetectorDialog::on_detectorTableWidget_cellClicked(int row, int column)
{
    ui->edtDetectorNo->setText( ui->detectorTableWidget->item( row, 0 )->text() );
    ui->edtDetectorChannelID->setText( ui->detectorTableWidget->item( row, 1 )->text() );
    ui->edtDetectorComments->setText( ui->detectorTableWidget->item( row, 2 )->text() );
    ui->sbxThreshold->setValue( ui->detectorTableWidget->item( row, 3 )->text().toUShort() );
    ui->sbxDelayTime->setValue( ui->detectorTableWidget->item( row, 4 )->text().toUShort() );
    ui->cmbReset->setCurrentText( ui->detectorTableWidget->item( row, 5 )->text() );
}

void BatchDetectorDialog::on_ptnAdd_clicked()
{
    QString strID = ui->edtDetectorNo->text();
    g_ReceiverDetectorId = g_parkReceiverId + strID;
    QString strSql = "select * from tabdetectorinfo where ReceiverDetectorID = '%1'";
    strSql = strSql.arg( g_ReceiverDetectorId );
    QString strError;
    QStringList lstRows;
    QString strName = "该编号【%1】已经存在，请重新输入！";
    strName = strName.arg( strID );

    if( !CommFunction::VerifyIsEmpty( ui->edtDetectorNo->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtDetectorChannelID->text() )
            && CommFunction::VerifyLength( ui->edtDetectorNo->text(), 3 )
            && CommFunction::VerifyIsNumber( ui->edtDetectorNo->text() )
            && CommFunction::VerifyIsNumber( ui->edtDetectorChannelID->text() )
            && CommFunction::VerifyMinMax( ui->edtDetectorChannelID->text(), 0, 255 )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
    {
        // 判断table表中是否存在。 判断strID

        for( int i = 0; i < ui->detectorTableWidget->rowCount(); ++i )
        {
            QString tmpValue = ui->detectorTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpValue ) )
            {
                QMessageBox::information( NULL, "提示", QString( "该编号【%1】已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }

        QTableWidgetItem *pItem0 = new QTableWidgetItem( ui->edtDetectorNo->text() );
        pItem0->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        pItem0->setData( Qt::UserRole, g_ReceiverDetectorId );

        QTableWidgetItem *pItem1 = new QTableWidgetItem( ui->edtDetectorChannelID->text() );
        pItem1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem2 = new QTableWidgetItem( ui->edtDetectorComments->text() );
        pItem2->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem3 = new QTableWidgetItem( ui->sbxThreshold->text() );
        pItem3->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem4 = new QTableWidgetItem( ui->sbxDelayTime->text() );
        pItem4->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        QTableWidgetItem *pItem5 = new QTableWidgetItem( ui->cmbReset->currentText() );
        pItem5->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        int row = ui->detectorTableWidget->rowCount();
        ui->detectorTableWidget->setRowCount( row + 1 );

        ui->detectorTableWidget->setItem( row, 0, pItem0 );
        ui->detectorTableWidget->setItem( row, 1, pItem1 );
        ui->detectorTableWidget->setItem( row, 2, pItem2 );
        ui->detectorTableWidget->setItem( row, 3, pItem3 );
        ui->detectorTableWidget->setItem( row, 4, pItem4 );
        ui->detectorTableWidget->setItem( row, 5, pItem5 );
    }
}

void BatchDetectorDialog::on_ptnModify_clicked()
{
    if( ui->detectorTableWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选中要修改的行", "确定" );
        return;
    }

    QString strID = ui->edtDetectorNo->text();
    g_ReceiverDetectorId = g_parkReceiverId + strID;
    QString strSql = "select * from tabdetectorinfo where ReceiverDetectorID = '%1'";
    strSql = strSql.arg( g_ReceiverDetectorId );
    QString strError;
    QStringList lstRows;
    QString strName = "该编号【%1】已经存在，请重新输入！";
    strName = strName.arg( strID );

    if( !CommFunction::VerifyIsEmpty( ui->edtDetectorNo->text() )
            && !CommFunction::VerifyIsEmpty( ui->edtDetectorChannelID->text() )
            && CommFunction::VerifyLength( ui->edtDetectorNo->text(), 3 )
            && CommFunction::VerifyIsNumber( ui->edtDetectorNo->text() )
            && CommFunction::VerifyIsNumber( ui->edtDetectorChannelID->text() )
            && CommFunction::VerifyMinMax( ui->edtDetectorChannelID->text(), 0, 255 )
            && CommFunction::VerifyIsUnique( strSql, strError, lstRows, strName ) )
    {
        // 判断table表中是否存在。 判断strID

        for( int i = 0; i < ui->detectorTableWidget->rowCount(); ++i )
        {
            if( i == ui->detectorTableWidget->currentRow() )
            {
                continue;
            }

            QString tmpValue = ui->detectorTableWidget->item( i, 0 )->text();

            if( 0 == strID.compare( tmpValue ) )
            {
                QMessageBox::information( NULL, "提示", QString( "该编号【%1】已经存在，请重新输入！" ).arg( strID ), "确定" );
                return;
            }
        }

        int row = ui->detectorTableWidget->currentRow();
        ui->detectorTableWidget->item( row, 0 )->setText( strID );
        ui->detectorTableWidget->item( row, 0 )->setData( Qt::UserRole, g_ReceiverDetectorId );
        ui->detectorTableWidget->item( row, 1 )->setText( ui->edtDetectorChannelID->text() );
        ui->detectorTableWidget->item( row, 2 )->setText( ui->edtDetectorComments->text() );
        ui->detectorTableWidget->item( row, 3 )->setText( ui->sbxThreshold->text() );
        ui->detectorTableWidget->item( row, 4 )->setText( ui->sbxDelayTime->text() );
        ui->detectorTableWidget->item( row, 5 )->setText( ui->cmbReset->currentText() );
    }
}

void BatchDetectorDialog::on_ptnDelete_clicked()
{
if( ui->detectorTableWidget->currentItem() == NULL )
{
    QMessageBox::information( NULL, "提示", "请选中要删除的行", "确定" );
    return;
}

int row = ui->detectorTableWidget->currentRow();
ui->detectorTableWidget->removeRow( row );
}

void BatchDetectorDialog::on_ptnSave_clicked()
{
    QString strBase = "( '%1', '%2', %3, '%4', %5, %6, %7, '%8' ) ";
    QString strSql = "insert into tabdetectorinfo values";

    QList<QTreeWidgetItem *> lstChildren;

    int nRows = ui->detectorTableWidget->rowCount();

    if( 0 == nRows )
    {
        return;
    }

    for( int i = 0; i < nRows; ++i )
    {
        int reset;
        if( ui->detectorTableWidget->item( i, 5 )->text().compare( "是" ) )
        {
            reset = 1;
        }
        else
        {
            reset = 0;
        }

        strSql += strBase.arg( g_parkReceiverId ).arg( ui->detectorTableWidget->item( i, 0 )->text() )
                .arg( ui->detectorTableWidget->item( i, 1 )->text().toUShort() ).arg( ui->detectorTableWidget->item( i, 2 )->text() )
                .arg( ui->detectorTableWidget->item( i, 3 )->text().toUShort() ).arg( ui->detectorTableWidget->item( i, 4 )->text().toUShort() )
                .arg( reset ).arg( ui->detectorTableWidget->item( i, 0 )->data( Qt::UserRole ).toString() );
        if( i != nRows - 1 )
        {
            strSql += ","; // 使得最后一个没有,
        }

        ItemInfoDetector curInfo;
        curInfo.setPid( g_parkReceiverId );
        curInfo.setId( ui->detectorTableWidget->item( i, 0 )->text() );
        curInfo.setChannelID( ui->detectorTableWidget->item( i, 1 )->text().toUShort() );
        curInfo.setComments( ui->detectorTableWidget->item( i, 2 )->text() );
        curInfo.setThreshold( ui->detectorTableWidget->item( i, 3 )->text().toUShort() );
        curInfo.setDelayTime( ui->detectorTableWidget->item( i, 4 )->text().toUShort() );
        curInfo.setDetectorReset( reset );
        curInfo.setReceiverDetectorID( ui->detectorTableWidget->item( i, 0 )->data( Qt::UserRole ).toString() );

        QVariant varValue;
        varValue.setValue( curInfo );

        QTreeWidgetItem *child = new QTreeWidgetItem( QStringList( curInfo.getId() ) );
        child->setData( 0, Qt::UserRole, varValue );
        child->setData( 0, Qt::WhatsThisRole, DetectorItem );

        lstChildren.append( child );
    }

    QString strError;
    QStringList lstRows;
    CommFunction::OperateSql( strSql, strError, lstRows );

    currentItem->addChildren( lstChildren );

    close();
    this->setResult( BatchDetectorDialog::Accepted );
}

void BatchDetectorDialog::on_ptnClose_clicked()
{
    close();
}
