#include "dlgparkdongleinfo.h"
#include "ui_dlgparkdongleinfo.h"

CDlgParkDongleInfo::CDlgParkDongleInfo(CProcessCpuid* pProcessor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgParkDongleInfo),
    pProcess( pProcessor )
{
    ui->setupUi(this);

    QHeaderView* pView = ui->tableWidget->horizontalHeader( );
    pView->hideSection( 2 );
    pView->resizeSection( 0, pView->sectionSize( 0 ) + 20 );
    pView->resizeSection( 1, pView->sectionSize( 1 ) + 80 );

    FillTableWidget( );
}

CDlgParkDongleInfo::~CDlgParkDongleInfo()
{
    delete ui;
}

void CDlgParkDongleInfo::FillTableWidget( )
{
    QStringList lstRows;
    QString strSql = QString( "select distinct AdministrativeID, BriefName, AES_DECRYPT( DongleHID, '%1' ) from ParkDongleInfo" ).arg( KEY_GUID );

    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
    int nField = 0;
    int nCols = 3;

    for ( int nIndex = 0; nIndex < lstRows.count( ) / nCols; nIndex++ ) {
        nField = nIndex * nCols;
        AddRow( lstRows[ nField ], lstRows[ nField + 1 ], lstRows[ nField + 2 ]  );
    }
}

void CDlgParkDongleInfo::on_btnAdd_clicked()
{
    int nRow = ui->tableWidget->currentRow( );
    if ( -1 == nRow ) {
        CCommonFunction::MsgBox( NULL, "提示", "请选择要增加加密狗的停车场！", QMessageBox::Information );
        return;
    }

    QStringList lstHids;
    pProcess->GetAllHIDs( lstHids );

    foreach ( const QString& strHid, lstHids ) {
        //QList<QTableWidgetItem* > lstItems = ui->tableWidget->findItems( strHid, Qt::MatchContains );

        //if ( lstItems.count( ) > 0 ) {
        //    int nRow = ui->tableWidget->row( lstItems.at( 0 ) );
        //    QString strInfo = QString( "加密狗【%1】已被停车场【%2】使用了！" ).arg( strHid, ui->tableWidget->item( nRow, 1 )->text( ) );
        //    CCommonFunction::MsgBox( NULL, "提示", strInfo, QMessageBox::Information );
        //    continue;
        //}

        QTableWidgetItem* pItem = ui->tableWidget->item( nRow, 2 );
        QString strHids = pItem->text( );
        if ( strHids.isEmpty( ) ) {
            strHids = strHid;
        } else {
            if ( strHids.contains( strHid ) ) {
                continue;
            }

            strHids += "," + strHid;
        }
        pItem->setText( strHids );

        ui->listWidget->addItem( strHid );
    }
}

void CDlgParkDongleInfo::AddColumn( QString &strValue, int nRow, int nCol )
{
    QTableWidgetItem* pItem = new QTableWidgetItem( strValue );
    ui->tableWidget->setItem( nRow, nCol, pItem );
    pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
}

void CDlgParkDongleInfo::AddRow( QString& strParkID, QString& strBrief, QString& strHids )
{
    int nRow = 0;
    ui->tableWidget->insertRow( nRow );

    AddColumn( strParkID, nRow, 0 );
    AddColumn( strBrief, nRow, 1 );
    AddColumn( strHids, nRow, 2 );
}

void CDlgParkDongleInfo::on_btnAddParkID_clicked()
{
    QString strParkID = ui->edtID->text( );
    QString strParkBrief = ui->edtBrief->text( );
    QString strHids = "";

    if ( strParkID.isEmpty( ) || strParkBrief.isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, "提示",  "请输入停车场相关信息！", QMessageBox::Information );
        return;
    }

    if ( ui->tableWidget->findItems( strParkID, Qt::MatchFixedString ).count( ) > 0 ) {
        CCommonFunction::MsgBox( NULL, "提示", "该停车场已存在！", QMessageBox::Information );
        return;
    }

    AddRow( strParkID, strParkBrief, strHids );

    QString strSql = QString( "Insert Into ParkDongleInfo( AdministrativeID, BriefName ) Values( '%1', '%2'  )" ).arg( strParkID, strParkBrief );
    CLogicInterface::GetInterface( )->ExecuteSql( strSql );
    CCommonFunction::OperationSuccess( );
}

void CDlgParkDongleInfo::on_btnDeleteParkID_clicked()
{
     int nRow = ui->tableWidget->currentRow( );

     if ( -1 == nRow ) {
         CCommonFunction::MsgBox( NULL, "提示",  "请输选择要删除的停车场！", QMessageBox::Information );
         return;
     }

     QString strSql = QString( "Delete  From ParkDongleInfo Where  AdministrativeID = '%1' " ).arg(
                 ui->tableWidget->item( nRow, 0 )->text( ) );
     CLogicInterface::GetInterface( )->ExecuteSql( strSql );
     ui->tableWidget->removeRow( nRow );
     ui->listWidget->clear( );
     CCommonFunction::OperationSuccess( );
}

void CDlgParkDongleInfo::on_tableWidget_cellClicked(int row, int column )
{
    if ( 0 != column ) {
        return;
    }

    ui->edtID->setText( ui->tableWidget->item( row, 0 )->text( ) );
    ui->edtBrief->setText( ui->tableWidget->item( row, 1 )->text( ) );
    ui->listWidget->clear( );

    QString strHids = ui->tableWidget->item( row, 2 )->text( );
    if ( !strHids.isEmpty( ) ) {
        QStringList lstData = strHids.split( "," );
        ui->listWidget->addItems( lstData );
    }
}

void CDlgParkDongleInfo::on_btnDelete_clicked()
{
    int nRow = ui->tableWidget->currentRow( );
    if ( -1 == nRow ) {
        CCommonFunction::MsgBox( NULL, "提示", "请选择要删除加密狗的停车场！", QMessageBox::Information );
        return;
    }

    int nIndex = ui->listWidget->currentRow( );

    if ( -1 == nIndex ) {
        CCommonFunction::MsgBox( NULL, "提示", "请选择要删除的加密狗！", QMessageBox::Information );
        return;
    }

    QListWidgetItem* pLstItem = ui->listWidget->takeItem( nIndex );

    QTableWidgetItem* pItem = ui->tableWidget->item( nRow, 2 );
    QString strHids = pItem->text( );
    QStringList  lstHids = strHids.split( "," );
    lstHids.removeOne(pLstItem->text( ) );
    pItem->setText( lstHids.join( "," ) );

    delete pLstItem;
}

void CDlgParkDongleInfo::on_btnClose_clicked()
{
    close( );
}

void CDlgParkDongleInfo::on_btnSave_clicked()
{
    int  nRow = ui->tableWidget->currentRow( );
    if ( -1 == nRow ) {
        return;
    }

    QString strSql = QString( "update ParkDongleInfo set DongleHID = AES_ENCRYPT( '%1', '%2' ) where AdministrativeID = '%3'" ).arg(
                ui->tableWidget->item( nRow, 2 )->text( ), KEY_GUID, ui->tableWidget->item( nRow, 0 )->text( ) );
    CLogicInterface::GetInterface( )->ExecuteSql( strSql );
    CCommonFunction::OperationSuccess( );
}
