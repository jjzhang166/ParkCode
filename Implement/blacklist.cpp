#include "Header/blacklist.h"
#include "ui_blacklist.h"

#ifdef NewUI
    #include "ui_newblacklist.h"
#else
    #include "ui_blacklist.h"
#endif

#include "Common/commonfunction.h"
#include "Dialog/dlgblacklistlocation.h"

CBlacklist::CBlacklist(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(
        #ifdef NewUI
            new Ui::CONCAT_NEW_NAME( New , CBlacklist )
        #else
            new Ui::CONCAT_NEW_NAME( , CBlacklist )
        #endif
        )
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    //pParent->OperateTableWidget( ui->tableBlacklist, CommonDataType::BlacklistTable, CommonDataType::InitializeType );
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    EnableControl( false );
    ControlButton( true );
    ui->lblTitle->setText( windowTitle( ) );

    nOperate = -1;
    ui->tableBlacklist->hideColumn( 3 );
    ui->lblID->setVisible( false );
}

void CBlacklist::FillTable( )
{
    CCommonFunction::FreeAllRows( ui->tableBlacklist );

    QStringList lstData;
    QString strWhere = "";
    int nCols = 4;
    int nRows = CLogicInterface::GetInterface( )->OperateBlacklistInfo( lstData, CommonDataType::SelectData, strWhere );

    ui->tableBlacklist->setRowCount( nRows );

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        for ( int nCol = 0; nCol < nCols; nCol++ ) {
            QTableWidgetItem* pItem = new QTableWidgetItem( lstData[ nRow * nCols + nCol ]);
            ui->tableBlacklist->setItem( nRow, nCol, pItem );
            pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        }
    }
}

void CBlacklist::ControlButton( bool bEnabled )
{
    ui->btnAdd->setEnabled( bEnabled );
    ui->btnDelete->setEnabled( bEnabled );
    ui->btnModify->setEnabled( bEnabled );

    ui->btnOk->setEnabled( !bEnabled );
    ui->btnCancel->setEnabled( !bEnabled );
}

void CBlacklist::on_btnAdd_clicked( )
{
    nOperate = 0;
    ControlButton( false );
    EnableControl( true );
}

void CBlacklist::on_btnDelete_clicked( )
{
    int nRow = ui->tableBlacklist->currentRow( );

    if ( -1 == nRow || ui->lblID->text( ).isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请选择要删除的行！" ), QMessageBox::Information );
        return;
    }

    if ( QMessageBox::Cancel == CCommonFunction::MsgBox( NULL, "提示", "确定要删除记录吗？", QMessageBox::Question ) ) {
        return;
    }

    nOperate = 1;
    SaveData( 1 );

    CCommonFunction::FreeRow( ui->tableBlacklist, nRow, ui->tableBlacklist->columnCount( ) );

    /////////////////////////////////////////////////////////////////////////////////////////////z
    //第一次为选中点击删除会提示，第二次便不会，且删掉界面上的，而不是数据库中的。因为ui->lblID标签里有值，是旧的当前选项值，已失效。
    ui->lblID->setText( "" );// 最后应该置空。

}

void CBlacklist::on_btnModify_clicked( )
{
    int nRow = ui->tableBlacklist->currentRow( );

    if ( -1 == nRow || ui->lblID->text( ).isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请选择要修改的行！" ), QMessageBox::Information );
        return;
    }

    nOperate = 2;
    EnableControl( true );
    ControlButton( false );
}

void CBlacklist::EnableControl( bool bEnabled )
{
    ui->edtName->setEnabled( bEnabled );
    ui->edtType->setEnabled( bEnabled );
    ui->edtExplain->setEnabled( bEnabled );
}

void CBlacklist::AssignValue( bool bToTable, int nRowIndex )
{
    QTableWidgetItem* pItem = NULL;

    if ( bToTable ) {
        pItem = new QTableWidgetItem( ui->edtName->text( ) );
        ui->tableBlacklist->setItem( nRowIndex, 0, pItem );
        pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );

        pItem = new QTableWidgetItem( ui->edtType->text( ) );
        ui->tableBlacklist->setItem( nRowIndex, 1, pItem );
        pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );

        pItem = new QTableWidgetItem( ui->edtExplain->text( ) );
        ui->tableBlacklist->setItem( nRowIndex, 2, pItem );
        pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );

    } else {
        pItem = ui->tableBlacklist->item( nRowIndex, 0 );
        if ( NULL == pItem ) {
            return;
        }
        ui->edtName->setText( pItem->text( ) );

        pItem = ui->tableBlacklist->item( nRowIndex, 1 );
        if ( NULL == pItem ) {
            return;
        }
         ui->edtType->setText( pItem->text( ) );

        pItem = ui->tableBlacklist->item( nRowIndex, 2 );
        if ( NULL == pItem ) {
            return;
        }
        ui->edtExplain->setText( pItem->text( ) );
    }
}

void CBlacklist::SaveData( int nType )
{
    QString strWhere = QString( " Where id = %1" ).arg( ui->lblID->text( ) );
    QStringList lstData;

    if ( 1 == nType ) {
        CLogicInterface::GetInterface( )->OperateBlacklistInfo( lstData, CommonDataType::DeleteData, strWhere );
    } else {
        lstData << ui->edtName->text( )
                << ui->edtType->text( )
                << ui->edtExplain->text( );

        if ( 0 == nType ) {
            CLogicInterface::GetInterface( )->OperateBlacklistInfo( lstData, CommonDataType::InsertData, strWhere );
        } else if ( 2 == nType ) {
            CLogicInterface::GetInterface( )->OperateBlacklistInfo( lstData, CommonDataType::UpdateData, strWhere );
        }
    }
}

void CBlacklist::on_tableBlacklist_cellClicked ( int row, int column )
{
    ui->lblID->setText( ui->tableBlacklist->item( row, 3 )->text( ) );
    AssignValue( false, row );
}

bool CBlacklist::DataExist()
{
    bool bRet = false;

    if ( 1 == nOperate ) {
        return bRet;
    }

    QString strPlate = ui->edtName->text( );
    int nRow = ui->tableBlacklist->rowCount( );

    for ( int nIndex = 0; nIndex < nRow; nIndex++ ) {
        if ( ui->tableBlacklist->item( nIndex, 0 )->text( ) == strPlate ) {
            ui->tableBlacklist->selectRow( nIndex );
            CCommonFunction::MsgBox( NULL, QString( "提示" ), QString( "【%1】已存在！" ).arg( strPlate ), QMessageBox::Information );
            bRet = true;
            break;
        }
    }

    return bRet;
}

void CBlacklist::on_btnOk_clicked( )
{
    if ( -1 == nOperate ) {
        return;
    }

    if ( DataExist( ) ) {
        return;
    }

    int nRow = 1;

    if ( 0 == nOperate ) { // Add
        nRow = ui->tableBlacklist->rowCount( );
        ui->tableBlacklist->insertRow( nRow );
    } else if ( 1 == nOperate ) { // Delete
        return;
    } else if ( 2 == nOperate ) { // Modify
        nRow = ui->tableBlacklist->currentRow( );
    }

    SaveData( nOperate );
    FillTable( );

    AssignValue( true, nRow );
    ControlButton( true );
    EnableControl( false );
}

void CBlacklist::on_btnCancel_clicked( )
{
    ControlButton( true );
    EnableControl( false );
}

CBlacklist::~CBlacklist()
{
    delete ui;
}

void CBlacklist::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CBlacklist::resizeEvent( QResizeEvent* )
{
    FillTable( );
    CalculatePos( );
}

void CBlacklist::CalculatePos( )
{
    move( 23, 55 );
    return;
    QRect rectWnd = this->geometry( );

    QString strName = "widget";
    QWidget* pWg = findChild< QWidget* >( strName );
    QRect rectWg = pWg->geometry( );

    pWg->setGeometry( ( rectWnd.width( ) - rectWg.width( ) -2 ) / 2,
                      ( rectWnd.height( )  - rectWg.height( ) -2 ) / 2,
                      rectWg.width( ), rectWg.height( ) );
}

void CBlacklist::on_btnMinimalize_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CBlacklist::on_lblClose_linkActivated(QString)
{
    close( );
}

void CBlacklist::HandleLocation( QString strPlate )
{
    int nRow = ui->tableBlacklist->rowCount( );

    for ( int nIndex = 0; nIndex < nRow; nIndex++ ) {
        if ( ui->tableBlacklist->item( nIndex, 0 )->text( ) == strPlate ) {
            ui->tableBlacklist->selectRow( nIndex );
            break;
        }
    }
}

void CBlacklist::on_btnLocation_clicked()
{
    CDlgBlacklistLocation dlg;
    connect( &dlg, SIGNAL( Location( QString ) ),
             this, SLOT( HandleLocation( QString ) ) );
    dlg.exec( );
}

void CBlacklist::on_btnRefresh_clicked()
{
    FillTable( );
}
