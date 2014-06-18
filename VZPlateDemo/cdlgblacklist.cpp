#include "cdlgblacklist.h"
#include "ui_cdlgblacklist.h"

CDlgBlacklist::CDlgBlacklist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgBlacklist)
{
    ui->setupUi(this);
    ReadPlate( );
}

CDlgBlacklist::~CDlgBlacklist()
{
    delete ui;
}

void CDlgBlacklist::on_btnAdd_clicked()
{
    QString strPlate = ui->edtPlate->text( );
    if ( strPlate.isEmpty( ) ) {
        QMessageBox::information( this, "提示", "请选输入车牌。" );
        return;
    }

    AddRow( strPlate );
    ui->edtPlate->clear( );
    SelectRow( 0 );
}

void CDlgBlacklist::AddRow( const QString &strPlate )
{
    if ( 0 < ui->tableWidget->findItems( strPlate, Qt::MatchFixedString ).count( ) ) {
        QMessageBox::information( this, "提示", QString( "车牌【%1】已存在。" ).arg( strPlate ) );
        return;
    }

    QTableWidgetItem* pItem = new QTableWidgetItem( strPlate );
    pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );

    ui->tableWidget->insertRow( 0 );
    ui->tableWidget->setItem( 0, 0, pItem );
}

void CDlgBlacklist::SelectRow( int nIndex )
{
    int nCount = ui->tableWidget->rowCount( );
    if ( 0 == nCount || nIndex >= nCount || 0 > nIndex ) {
        return;
    }

    ui->tableWidget->selectRow( nIndex );
}

void CDlgBlacklist::ReadPlate( )
{
    CConfigurator* pConfig = CConfigurator::CreateInstance( );
    QStringList lstPlates;
    pConfig->ReadBlacklistPlate( lstPlates );

    foreach ( const QString& strPlate, lstPlates ) {
        AddRow( strPlate );
    }

    SelectRow( 0 );
}

void CDlgBlacklist::SavePlate( )
{
    int nRows = ui->tableWidget->rowCount( );

    if ( 0 == nRows ) {
        return;
    }

    QStringList lstPlates;

    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        lstPlates << ui->tableWidget->item( nIndex, 0 )->text( );
    }

    CConfigurator* pConfig = CConfigurator::CreateInstance( );
    pConfig->WriteBlacklistPlate( lstPlates );
}

void CDlgBlacklist::on_btnDelete_clicked()
{
    int nRow = ui->tableWidget->currentRow( );

    if ( -1 == nRow ) {
        QMessageBox::information( this, "提示", "请选择要删除行。" );
        return;
    }

    QTableWidgetItem* pItem = ui->tableWidget->item( nRow, 0 );

    if ( QMessageBox::No == QMessageBox::question( this, "提示", QString( "确定要删除车牌【%1】吗？" ).arg( pItem->text( ) ), QMessageBox::Yes | QMessageBox::No ) ) {
        return;
    }

    ui->tableWidget->removeRow( nRow );
    SelectRow( 0 );
}

void CDlgBlacklist::on_btnSave_clicked()
{
    SavePlate( );
}
