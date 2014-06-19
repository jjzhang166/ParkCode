#include "Header/timecard.h"

#ifdef NewUI
    #include "ui_newtimecard.h"
#else
    #include "ui_timecard.h"
#endif

#include "Common/commonfunction.h"
#include "Dialog/timecarddialog.h"
#include "Dialog/dlgserach.h"
#include "Dialog/dlgbulkregister.h"
#include "Dialog/dlgcardloss.h"

CTimeCard::CTimeCard(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(
        #ifdef NewUI
            new Ui::CONCAT_NEW_NAME( New , CTimeCard )
        #else
            new Ui::CONCAT_NEW_NAME( , CTimeCard )
        #endif
        )
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );

    //pParent->OperateTableWidget( ui->tableTime, CommonDataType::TimeTable, CommonDataType::InitializeType );
    //pParent->OperateTableWidget( ui->tableAccess, CommonDataType::TimeAccessTable, CommonDataType::InitializeType );
    //pParent->OperateTableWidget( ui->tableEntranceRight, CommonDataType::TimeEntranceRightTable, CommonDataType::InitializeType );
    GetDataFromDb( );
    pMenu = NULL;
    ControlDataGrid( );
    ui->lblTitle->setText( windowTitle( ) );
    ui->lblCardNo->setVisible( false );

    QHeaderView* pHeader = ui->tableAccess->horizontalHeader( );
    pHeader->hideSection( ui->tableAccess->columnCount( ) - 1 );
}

CTimeCard::~CTimeCard()
{
    delete ui;
}

void CTimeCard::ControlDataGrid( )
{
    int nIndex = 0;

    QHeaderView* pHeader = ui->tableAccess->horizontalHeader( );
    nIndex = 0;
    pHeader->resizeSection( nIndex, pHeader->sectionSize( nIndex ) * 2 );
    nIndex = 1;
    pHeader->resizeSection( nIndex, pHeader->sectionSize( nIndex ) * 2 );
    nIndex = 2;
    pHeader->resizeSection( nIndex, pHeader->sectionSize( nIndex ) * 2 );
    nIndex = 3;
    pHeader->resizeSection( nIndex, pHeader->sectionSize( nIndex ) * 2 );

    ui->tableEntranceRight->horizontalHeader( )->hideSection( 3 );
}

void CTimeCard::GetDataFromDb( )
{
    QStringList lstRows;
    QString strWhere = "order by cardselfno";
    int nRows = CLogicInterface::GetInterface( )->OperateCardInfo( lstRows, CommonDataType::TimeCard,
                                                       CommonDataType::SelectData, strWhere );

    CCommonFunction::FreeAllRows( ui->tableTime );
    CCommonFunction::FillTable( ui->tableTime, nRows, lstRows );
}

void CTimeCard::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CTimeCard::resizeEvent( QResizeEvent* )
{
    CalculatePos( );
}

void CTimeCard::CalculatePos( )
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

void CTimeCard::OpenDialog( bool bNew )
{
    QString strUser = pParent->GetUserName( );
    CTimeCardDialog dlg( bNew, strUser, ui->tableTime, this );
    dlg.InitDlg( );
    pParent->SetCardControl( dlg.GetCardNumCtrl( ) );
    dlg.exec( );
    pParent->SetCardControl( NULL );
}

void CTimeCard::AddRecord( )
{
    OpenDialog( true );
}

void CTimeCard::ModifyRecord( )
{
    qint32 nCurrentRow = ui->tableTime->currentRow( );
    if ( 0 > nCurrentRow ) {
        return;
    }

    OpenDialog( false );
}

void CTimeCard::WriteCardLog(QString strCotent)
{
    QDateTime dtDateTime = QDateTime::currentDateTime( );
    pParent->WriteLog( "卡片管理", strCotent, CommonDataType::CardMgmLog, dtDateTime );
}

void CTimeCard::DeleteRecord( )
{
    int nRow = ui->tableTime->currentRow( );

    if ( -1 == nRow ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 "请选择要删除的数据！", QMessageBox::Information );
        return;
    } else if ( QMessageBox::Ok == CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                                            "确定要删除数据吗？", QMessageBox::Question ) ){
        QTableWidgetItem* pItem = ui->tableTime->item( nRow, 0 );
        QString strWhere = QString( " Where cardno = '%1'" ).arg( pItem->text( ) );
        QStringList lstRows;

        QString strCotent = QString( "删除计时卡 卡号　：%1" ).arg( pItem->text( ) );
        WriteCardLog( strCotent );

        CLogicInterface::GetInterface( )->OperateCardInfo( lstRows, CommonDataType::TimeCard,
                                                          CommonDataType::DeleteData, strWhere );
        CCommonFunction::FreeRow( ui->tableTime, nRow, ui->tableTime->columnCount( ) );
    }
}

void CTimeCard::Refresh( )
{
    GetDataFromDb( );
}

void CTimeCard::Serach( )
{
    CDlgSerach dlg( CommonDataType::TimeCard );
    connect( &dlg, SIGNAL( PositionRow( QString ) ), this, SLOT( PositionRow( QString ) ) );
    pParent->SetCardControl( dlg.GetEditCntrl(  ) );
    dlg.exec( );
    pParent->SetCardControl( NULL );
}

void CTimeCard::PositionRow( QString strCardID )
{
    QList< QTableWidgetItem* > lstItem = ui->tableTime->findItems( strCardID, Qt::MatchFixedString );
    if ( 0 >= lstItem.count( ) ) {
        return;
    }

    QTableWidgetItem* pItem = lstItem.at( 0 );
    int nRow = ui->tableTime->row( pItem );
    //ui->tableTime->setCurrentItem( pItem, QItemSelectionModel::ToggleCurrent );
    on_tableTime_cellClicked( nRow, 0 );
    ui->tableTime->selectRow( nRow );
}

void CTimeCard::PrintCardInfo( )
{

}

void CTimeCard::Download2CC( )
{

}

void CTimeCard::AddBulkRecord( )
{
    CDlgBulkRegister dlg( CommonDataType::TimeCard, ui->tableTime, pParent->GetUserName( ) );
    QString strPath;
    CCommonFunction::GetPath( strPath, CommonDataType::PathUIImage );
    strPath += "NewIcon/CommonMiddleBG-normal.jpg";
    dlg.setStatusTip( strPath );
    pParent->SetCardControl( dlg.GetEditCntrl(  ) );
    dlg.exec( );
    pParent->SetCardControl( NULL );
}

void CTimeCard::CardLossProcess( )
{
    qint32 nCurrentRow = ui->tableTime->currentRow( );
    if ( 0 > nCurrentRow ) {
        return;
    }

    QString strID = ui->tableTime->item( nCurrentRow, 0 )->text( );
    CDlgCardLoss dlg( strID, CommonDataType::TimeCard );
    dlg.exec( );
}

void CTimeCard::CreateContextMenu( QTableWidget *parent )
{
    if ( NULL == pMenu ) {
        pMenu = new QMenu( parent );
        pMenu->addAction( "新增", this, SLOT( AddRecord( ) ) );
        pMenu->addAction( "批量新增", this, SLOT( AddBulkRecord( ) ) );
        pMenu->addAction( "编辑", this, SLOT( ModifyRecord( ) ) );
        pMenu->addAction( "删除", this, SLOT( DeleteRecord( ) ) );
        pMenu->addAction( "查找", this, SLOT( Serach( ) ) );
        pMenu->addAction( "车进场 卡遗失处理", this, SLOT( CardLossProcess( ) ) );
        pMenu->addSeparator( );
        pMenu->addAction( "刷新", this, SLOT( Refresh( ) ) );
        pMenu->addSeparator( );
        pMenu->addAction( "打印卡片资料", this, SLOT( PrintCardInfo( ) ) );
        pMenu->addAction( "下载到中心控制器", this, SLOT( Download12CC( ) ) );
    }

    pMenu->exec( parent->cursor().pos( ) );
}

void CTimeCard::on_tableTime_customContextMenuRequested( QPoint )
{
    CreateContextMenu( ui->tableTime );
}

void CTimeCard::on_tableTime_cellClicked(int row, int column)
{
    QTableWidgetItem* pItem = ui->tableTime->item( row, 0 );
    QString strCardNo = pItem->text( );
    QStringList lstRows;

    CCommonFunction::FreeAllRows( ui->tableAccess );
    CCommonFunction::FreeAllRows( ui->tableEntranceRight );

    ///////////////////////////////
    QString strWhere = QString( " Where cardno = '%1'" ).arg( strCardNo );
    QString strSql = QString ( "Select inshebeiname, intime, outshebeiname, outtime, stoprdid From stoprd %1" ).arg( strWhere );
    int nRows;//nRows = CLogicInterface::GetInterface( )->OperateInOutRecord( lstRows,
            //                                           CommonDataType::SelectData, strWhere );
    nRows = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows, CCommonFunction::GetHistoryDb( ) );
    CCommonFunction::FillTable( ui->tableAccess, nRows, lstRows );

    ///////////////////////////////////////////////////////////////////
    nRows = CLogicInterface::GetInterface( )->OperateInOutRight( lstRows,
                                                       CommonDataType::SelectData, strWhere );
    CCommonFunction::FillCardRightTable( ui->tableEntranceRight, nRows, lstRows );

    ui->lblCardNo->setText( strCardNo );
}

void CTimeCard::on_btnMinimalize_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CTimeCard::on_tableAccess_cellClicked(int row, int column)
{
    bool bFirst = ( 0 == column );
    if ( 1 == column || 3 == column ) {
        return;
    }

    QString strWhere = QString( " Where stoprdid = '%1'" ).arg(
                                ui->tableAccess->item( row, ui->tableAccess->columnCount( ) - 1 )->text( ) );

    QLabel* lblImg[ ] = { ui->lblImg1, ui->lblImg2, ui->lblImg3, ui->lblImg4 };
    for ( int nIndex = 0; nIndex < 4; nIndex++ ) {
        CCommonFunction::LoadFourImages( ( CommonDataType::BlobType ) ( nIndex + ( bFirst ? 0 : 4 ) ),
                                         strWhere, *lblImg[ nIndex ], CCommonFunction::GetHistoryDb( ) );
    }
}

void CTimeCard::on_lblClose_linkActivated(QString)
{
    close( );
}

void CTimeCard::on_pushButton_8_clicked()
{
    QStringList lstRows;
    QString strWhere = "";
    CCommonFunction::UpateCardRight( lstRows, ui->tableEntranceRight );
    CLogicInterface::GetInterface( )->OperateInOutRight( lstRows, CommonDataType::UpdateData, strWhere );
    CCommonFunction::OperationSuccess( );
}
