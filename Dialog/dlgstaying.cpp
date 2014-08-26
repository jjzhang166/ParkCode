#include "dlgstaying.h"
#include "ui_dlgstaying.h"
#include "Common/logicinterface.h"
#include "../Dialog/parkspacelotdialog.h"
#include "../mainwindow.h"

CDlgStaying::CDlgStaying(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgStaying)
{
    ui->setupUi(this);
    ConnectDb( );
    CreateContextMenu( );
    pPrintMonthlyReport = new CPrintMonthlyReport( NULL, false );
    QString strImagePath;
    CCommonFunction::GetPath( strImagePath, CommonDataType::PathUIImage );
    QString strStyle = QString( "background-image:url(%1NewIcon/VerifyPlate.JPG)" ).arg( strImagePath );
    pPrintMonthlyReport->setStyleSheet( strStyle );
    connect( pPrintMonthlyReport, SIGNAL( ManualRecogonization( int, QString ) ),
             this, SLOT( HandleManualRecogonization( int, QString ) ) );

    CCommonFunction::SetWindowIcon( this );
    bHistory = CCommonFunction::GetSettings( CommonDataType::CfgSystem )->value( "CommonCfg/HistoryDb", false ).toBool( );

    pSystem = CCommonFunction::GetSettings( CommonDataType::CfgSystem );

    SetChkClikedArray( false );

    pReportThread = QReportThread::CreateReportThread( );
    pFrmDisplayPic =  new CPrintYearlyReport( NULL, this );
    SetFrameVisble( false );

    pFrmDisplayPic->move( geometry( ).width( ) - pFrmDisplayPic->width( ),
                          geometry( ).height( ) - pFrmDisplayPic->height( ) );

    QHeaderView* pView = ui->tableWidgetMonth->horizontalHeader( );
    pView->hideSection( ui->tableWidgetMonth->columnCount( ) - 1 );

    pView = ui->tableWidgetTime->horizontalHeader( );
    pView->hideSection( ui->tableWidgetTime->columnCount( ) - 1 );

    pView = ui->tableWidgetNoCard->horizontalHeader( );
    pView->hideSection( ui->tableWidgetNoCard->columnCount( ) - 1 );

    bool bNocard = pSystem->value( "CommonCfg/NoCardWork", false ).toBool( );
    ui->tab_3->setVisible( bNocard );
    connect( pReportThread, SIGNAL( RefresehData( int ) ),
             this, SLOT( HandleRefreshData( int ) ) );
    connect( pReportThread, SIGNAL(ExecuteSQLData(int,QStringList,int)),
             this, SLOT(HandleExecuteSQLData(int,QStringList,int)));

    pProcessData = CProcessData::GetProcessor( );
    connect( pProcessData, SIGNAL( RefreshUI( QString ) ),
             this, SLOT( HandleRefreshUI( QString ) ) );

    nPage = 0;
    QString strLimit = " Limit 0, 100";
    GetData( 0, strLimit );
}

void CDlgStaying::DisableControl( )
{
    bool bDisable = false;
    ui->tab->setEnabled( bDisable );
    ui->tab_2->setEnabled( bDisable );

    QList< QAction* > lstAction = pMenuNoCard->actions( );
    if ( 2 > lstAction.size( ) ) {
        return;
    }

    lstAction.at( 0 )->setEnabled( bDisable );
    lstAction.at( 1 )->setEnabled( bDisable );

    ui->tabWidget->setCurrentIndex( 2 );
}

void CDlgStaying::ConnectDb( )
{
    QStringList lstParams;
    CCommonFunction::ConnectMySql( lstParams, false );
    dbInterface.GetMysqlDb( ).DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ],
                                                     lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );
}

void CDlgStaying::HandleRefreshUI( QString strRdid )
{
    //GetData( ui->tabWidget->currentIndex( ) + 1 );
    QTableWidget* pWidget = NULL;
    switch( ui->tabWidget->currentIndex( ) ) {
    case 0 :
        pWidget = ui->tableWidgetMonth;
        break;

    case 1 :
        pWidget = ui->tableWidgetTime;
        break;

    case 2 :
        pWidget = ui->tableWidgetNoCard;
        break;
    }

    pWidget->removeRow( pWidget->currentRow( ) );
}

void CDlgStaying::HandleRefreshData(int nType)
{
    QString strLimit = " Limit 0, 100";
    GetData( ui->tabWidget->currentIndex( ) + 1, strLimit );
}

void CDlgStaying::DisplayMenu( QTableWidget* pTabWidget, QMenu *pMenu, const QPoint &pos )
{
    if ( 0 == pTabWidget->rowCount( ) ) {
        return;
    }

    //绝对坐标是屏幕坐标(0,0)--(Rx, Ry)
    //每个控件都有自己的坐标左上角(0,0)--右下角(width, height)
    //QPoint	mapFrom ( QWidget * parent, const QPoint & pos ) const
    //QPoint	mapFromGlobal ( const QPoint & pos ) const
    //QPoint	mapFromParent ( const QPoint & pos ) const
    //QPoint	mapTo ( QWidget * parent, const QPoint & pos ) const
    //QPoint	mapToGlobal ( const QPoint & pos ) const
    //QPoint	mapToParent ( const QPoint & pos ) const
    QPoint point = pTabWidget->mapToGlobal( QPoint( 0, 0 ) );
    int nHH = pTabWidget->horizontalHeader( )->height( );
    int nVW = pTabWidget->verticalHeader( )->width( );
    point = pTabWidget->mapToGlobal( pos );
    point += QPoint( nVW, nHH );
    pMenu->exec( point );
}

void CDlgStaying::CreateContextMenu( )
{
    pMenuMonth = new QMenu( ui->tableWidgetMonth );
    pMenuMonth->addAction( "批量进入记录处理", this, SLOT( BulkMonthInRecordProcess( ) ) );

    pMenuTime = new QMenu( ui->tableWidgetTime );
    pMenuTime->addAction( "批量进入记录处理", this, SLOT( BulkTimeInRecordProcess( ) ) );
    pMenuTime->addAction( "手动收费处理", this, SLOT( ManualTimeFeeProcess( ) ) );
    pMenuTime->addAction( "校正车牌", this, SLOT( ManualTimeVerifyPlateProcess( ) ) );

    pMenuNoCard = new QMenu( ui->tableWidgetNoCard );
    pMenuNoCard->addAction( "批量进入记录处理", this, SLOT( BulkNoCardInRecordProcess( ) ) );
    pMenuNoCard->addAction( "手动收费处理", this, SLOT( ManualNoCardFeeProcess( ) ) );
    pMenuNoCard->addAction( "校正车牌", this, SLOT( ManualNoCardVerifyPlateProcess( ) ) );
}

void CDlgStaying::BulkMonthInRecordProcess( )
{
    QTableWidget* pTabWidget = ( QTableWidget* ) pMenuMonth->parent( );
    BulkInRecordProcess( pTabWidget, 0 );
}

void CDlgStaying::BulkTimeInRecordProcess( )
{
    QTableWidget* pTabWidget = ( QTableWidget* ) pMenuTime->parent( );
    BulkInRecordProcess( pTabWidget, 1 );
}

void CDlgStaying::BulkNoCardInRecordProcess( )
{
    QTableWidget* pTabWidget = ( QTableWidget* ) pMenuNoCard->parent( );
    BulkInRecordProcess( pTabWidget, 2 );
}

void CDlgStaying::ManualTimeFeeProcess( )
{
    QTableWidget* pTabWidget = ( QTableWidget* ) pMenuTime->parent( );
    ManualFeeProcess( pTabWidget, 1 );
}

void CDlgStaying::ManualNoCardFeeProcess( )
{
    QTableWidget* pTabWidget = ( QTableWidget* ) pMenuNoCard->parent( );
    ManualFeeProcess( pTabWidget, 2 );
}

void CDlgStaying::ManualTimeVerifyPlateProcess( )
{
    QTableWidget* pTabWidget = ( QTableWidget* ) pMenuTime->parent( );
    ManualVerifyPlateProcess( pTabWidget, 1 );
}

void CDlgStaying::ManualNoCardVerifyPlateProcess( )
{
    QTableWidget* pTabWidget = ( QTableWidget* ) pMenuNoCard->parent( );
    ManualVerifyPlateProcess( pTabWidget, 2 );
}

void CDlgStaying::ManualVerifyPlateProcess( QTableWidget *pTabWidget, int nType )
{
    nVerifyPlateType = nType;
    pVerifyPlateTableWindget = pTabWidget;
    pPrintMonthlyReport->setParent( this );
    pPrintMonthlyReport->show( );
}

void CDlgStaying::EmitPlate(QTableWidget *pTabWidget)
{
    QStringList lstParams;
    int nRow = pTabWidget->currentRow( );
    if ( -1 == nRow ) {
        return;
    }

    QString strPlate = pTabWidget->item( nRow, 2 )->text( );
    if( "未知" == strPlate ) {
        return;
    }

    lstParams << pTabWidget->item( nRow, 0 )->text( )
              << strPlate
              << pTabWidget->item( nRow, 3 )->text( )
              << pTabWidget->item( nRow, 4 )->text( );

    emit EnterPlate( lstParams );
}

void CDlgStaying::HandleManualRecogonization( int nChannel, QString strPlate )
{
    Q_UNUSED( nChannel )
    if ( 0 < pVerifyPlateTableWindget->findItems( strPlate, Qt::MatchFixedString ).size( ) ) {
        CCommonFunction::MsgBox( NULL, "提示", QString( "车牌号【%1】已存在！" ).arg( strPlate ), QMessageBox::Information );
        return;
    }

    int nRowIndex = pVerifyPlateTableWindget->currentRow( );
    QTableWidgetItem* pItem = pVerifyPlateTableWindget->item( nRowIndex, 0 );
    QString strCardNo = pItem->text( );
    pItem = pVerifyPlateTableWindget->item( nRowIndex, 2 );
    pItem->setText( strPlate );

    if ( 2 == nVerifyPlateType ) {
        pItem = pVerifyPlateTableWindget->item( nRowIndex, 0 );
        pItem->setText( strPlate );

        EmitPlate( pVerifyPlateTableWindget );
    }

    pItem = pVerifyPlateTableWindget->item( nRowIndex,
                                            pVerifyPlateTableWindget->columnCount( ) - 1 );
    QString strStoprdid = pItem->text( );
    QString strSql = QString( "Call ManualVerifyPlate( '%1', '%2', '%3',%4 )" ).arg( strCardNo, strPlate, strStoprdid,
                                                                                QString::number( nVerifyPlateType ) );
    dbInterface.ExecuteSql( strSql );
}

void CDlgStaying::BulkInRecordProcess( QTableWidget* pTabWidget, int nType )
{
    if ( QMessageBox::Ok != CCommonFunction::MsgBox( NULL, "提示", "确定要批量处理选中的进入记录吗？", QMessageBox::Question ) ) {
        return;
    }

    QString strCardNo;
    QString strStoprdid;
    QTableWidgetItem* pItem = pTabWidget->item( pTabWidget->currentRow(), 1 == nType ? 4 : 2 );

    GetSpParams( strCardNo, strStoprdid, pTabWidget );
    QString strUser = ( ( MainWindow* ) parent( ) )->GetUserName( );
    QString strDateTime;
    QDateTime dt = QDateTime::currentDateTime( );
    CCommonFunction::DateTime2String( dt, strDateTime );
    QString strXml = QString( "<Data><User>%1</User><CardNo>%2</CardNo><Stoprdid>%3</Stoprdid><Plate>%4</Plate><Time>%5</Time></Data>" ).arg(
                strUser, strCardNo, strStoprdid, pItem->text( ), strDateTime );
    QString strSQL = QString( "CALL BulkStayingProcess( %1, \"%2\" )" ).arg( QString::number( nType ),
                                                                 strXml );
    pReportThread->PostReportEvent( strSQL, QMyReportEvent::ExecuteSQL, false );
}

void CDlgStaying::ManualFeeProcess( QTableWidget* pTabWidget, int nType )
{
    QStringList lstCan;
    CParkSpaceLotDialog dlg;
    QString strSql = QString ( "Select distinct shebeiname, shebeiadr From roadconerinfo \
                               where video1ip ='%1' and shebeiadr % 2 = 0" ).arg(
                                       CCommonFunction::GetHostIP( ) );
    QStringList lstRows;
    dbInterface.ExecuteSql( strSql, lstRows );
    dlg.InitDlg( true, lstRows, false, lstCan );
    dlg.setWindowTitle( dlg.windowTitle( ) + QString( "——开闸" ) );
    if ( CParkSpaceLotDialog::Rejected == dlg.exec( ) ) {
        return;
    }

    QString strCahnnel;
    char cCan = 0;
    dlg.GetCanAddress( cCan, strCahnnel );
    if ( 0 == cCan ) {
        return;
    }

    // 卡号 车牌号 In通道 进入时间 记录ID Out通道 lstParams Stoprdid
    QStringList lstParams;
    int nIndex = pTabWidget->currentRow( );
    lstParams << pTabWidget->item( nIndex, 0 )->text( )
              << pTabWidget->item( nIndex, 2 )->text( )
              << pTabWidget->item( nIndex, 3 )->text( )
              << pTabWidget->item( nIndex, 4 )->text( )
              << pTabWidget->item( nIndex, pTabWidget->columnCount( ) - 1 )->text( )
              << strCahnnel;

    pProcessData->ManualFee( lstParams, nType, cCan );

    //GetData( nType + 1 );
}

void CDlgStaying::GetSpParams( QString& strCardNo, QString& strStoprdid, QTableWidget* pTabWidget )
{
    int nColCount = pTabWidget->columnCount( );
    QModelIndexList selRopws = pTabWidget->selectionModel( )->selectedRows( );
    QTableWidgetItem* pItem = NULL;
    QStringList lstCardNo;
    QStringList lstStoprdid;

    foreach( const QModelIndex& index, selRopws ) {
        pItem = pTabWidget->item( index.row( ), 0 );
        lstCardNo << QString( "'%1'" ).arg( pItem->text( ) );

        pItem = pTabWidget->item( index.row( ), nColCount - 1 );
        lstStoprdid << pItem->text( );
    }

    strCardNo = lstCardNo.join( "," );
    strStoprdid = lstStoprdid.join( "," );
}

void CDlgStaying::SetFrameVisble( bool bVisible )
{
    pFrmDisplayPic->setVisible(  bVisible );
}

void CDlgStaying::closeEvent(QCloseEvent *)
{
    pSystem->setValue( "Staying/ASC", ui->cbSort->currentIndex( ) );

    for ( int n = 0; n < 7; n++ ) {
        if ( bChkCliked[ n ] ) {
            //if ( 2 == n || 3 == n ) {
            //    n = 0;
            //}

            pSystem->setValue( "Staying/Column", n );
            break;
        }
    }
}

CDlgStaying::~CDlgStaying()
{
    delete pFrmDisplayPic;
    delete pPrintMonthlyReport;
    delete ui;
}

void CDlgStaying::HandleExecuteSQLData(int nType, QStringList lstData, int nRows)
{
    QTableWidget* pWidget = NULL;
    switch ( nType ) {
    case QMyReportEvent::StayingMonth :
        pWidget = ui->tableWidgetMonth;
        break;

    case QMyReportEvent::StayingTime :
        pWidget = ui->tableWidgetTime;
        break;

    case QMyReportEvent::StayingNoCard :
        pWidget = ui->tableWidgetNoCard;
        break;
    }

    if ( NULL == pWidget ) {
        return;
    }

    CCommonFunction::FreeAllRows( pWidget );
    if ( 0 < nRows ) {
       FillTable( lstData, pWidget, nRows );
    }
}

void CDlgStaying::GetMonthData( QString &strOrder, QString& strLimit )
{
    QString strSql = "SELECT d.cardno,d.cardselfno, b.username, b.userphone, c.carcp, a.inshebeiname, a.intime, a.stoprdid \
            FROM stoprd a, userinfo b, carinfo c, monthcard d \
            where a.stoprdid = ( select stoprdid from cardstoprdid c \
                                 where d.cardno = c.cardno and d.Inside = 1 ) and a.outtime is null \
                and d.cardno = b.cardindex and d.cardno = c.cardindex " + strOrder;
    strSql += strLimit;

    QueryData( strSql, QMyReportEvent::StayingMonth );
    return;

    QStringList lstRows;
    int nRows = dbInterface.ExecuteSql( strSql, lstRows, bHistory );
    CCommonFunction::FreeAllRows( ui->tableWidgetMonth );
    if ( 0 < nRows ) {
       FillTable( lstRows, ui->tableWidgetMonth, nRows );
    }
}

void CDlgStaying::GetTimeData( QString &strOrder, QString& strLimit )
{
    QStringList lstRows;
    QString strSql = "SELECT b.cardno,b.cardselfno, a.carcp, a.inshebeiname, a.intime, a.stoprdid\
            FROM stoprd a, tmpcard b \
            where a.stoprdid = ( select stoprdid from cardstoprdid c \
                                 where b.cardno = c.cardno and b.Inside = 1 ) and a.outtime is null" + strOrder;

    QueryData( strSql, QMyReportEvent::StayingTime );
    return;

    lstRows.clear( );
    int nRows = dbInterface.ExecuteSql( strSql, lstRows, bHistory );
    CCommonFunction::FreeAllRows( ui->tableWidgetTime );
    if ( 0 < nRows ) {
      FillTable( lstRows, ui->tableWidgetTime, nRows );
    }
}

void CDlgStaying::QueryData( QString& strSql, QMyReportEvent::MyReportEvent eEvent )
{
    pReportThread->PostReportEvent( strSql, eEvent );
}

void CDlgStaying::GetNocardData( QString &strOrder, QString& strLimit )
{
    QStringList lstRows;
    QString strSql = "SELECT cardno, '', IF ( 2 = type, '未知', cardno ), inshebeiname, intime, stoprdid\
            FROM tmpcardintime where type in( 1, 2 ) " + strOrder + strLimit;

    QueryData( strSql, QMyReportEvent::StayingNoCard );
    return;

    lstRows.clear( );
    int nRows = dbInterface.ExecuteSql( strSql, lstRows, bHistory );
    CCommonFunction::FreeAllRows( ui->tableWidgetNoCard );
    if ( 0 < nRows ) {
      FillTable( lstRows, ui->tableWidgetNoCard, nRows );
    }
}

void CDlgStaying::GetData( int nType /*0 all 1 2 3*/, QString& strLimit  )
{
    int nIndex = ui->tableWidgetMonth->columnCount( ) - 1;
    QHeaderView* pView = ui->tableWidgetMonth->horizontalHeader( );
    pView->resizeSection( nIndex, pView->sectionSize( nIndex ) * 2 );

    nIndex = ui->tableWidgetTime->columnCount( ) - 1;
    pView = ui->tableWidgetTime->horizontalHeader( );
    pView->resizeSection( nIndex, pView->sectionSize( nIndex ) * 2 );

    QString strOrder = " Order by cardno asc ";
    int nCb = pSystem->value( "Staying/ASC", 0 ).toInt( );
    int nChk = pSystem->value( "Staying/Column", 0 ).toInt( );

    ui->cbSort->setCurrentIndex( nCb );
    QRadioButton* pBtn = findChild< QRadioButton* >( QString( "chk%1" ).arg( nChk ) );
    if ( NULL != pBtn ) {
        pBtn->setChecked( true );
    }

    switch ( nType ) {
    case 0 :
        GetOrderByClause( strOrder, nChk, nCb, 0 );
        GetMonthData( strOrder, strLimit );

        GetOrderByClause( strOrder, nChk, nCb, 1 );
        GetTimeData( strOrder, strLimit );

        GetOrderByClause( strOrder, nChk, nCb, 2 );
        GetNocardData( strOrder, strLimit );
        break;

    case 1 :
        GetOrderByClause( strOrder, nChk, nCb, 0 );
        GetMonthData( strOrder, strLimit );
        break;

    case 2 :
        GetOrderByClause( strOrder, nChk, nCb, 1 );
        GetTimeData( strOrder, strLimit );
        break;

    case 3 :
        GetOrderByClause( strOrder, nChk, nCb, 2 );
        GetNocardData( strOrder, strLimit );
        break;
    }
}

void CDlgStaying::FillTable( QStringList &lstData, QTableWidget *pTable, int nRows )
{
    //int nIndex = pTable->columnCount( ) - 1;
    //QHeaderView* pView = pTable->horizontalHeader( );
    //pView->resizeSection( nIndex, pView->sectionSize( nIndex ) * 2 );

    CCommonFunction::FillTable( pTable, nRows, lstData );
}

void CDlgStaying::on_tableWidgetMonth_cellClicked(int row, int column)
{
    DisplayPic( ( QTableWidget* ) sender( ), row, column );
}

void CDlgStaying::on_tableWidgetTime_cellClicked(int row, int column)
{
    DisplayPic( ( QTableWidget* ) sender( ), row, column );
}

void CDlgStaying::DisplayPic( QTableWidget* pWidget, int nRow, int nCol )
{
    bool bZeroCol = ( 0 == nCol );
    bool bExist = false;
    bool bNocard = ( ui->tab_3 == pWidget );

    if ( bZeroCol ) {
        QString strFile;
        QString strWhere = QString( " Where stoprdid =%1 " ).arg(
                    pWidget->item( nRow, pWidget->columnCount( ) - 1 )->text( ) );
        CCommonFunction::GetPath( strFile, CommonDataType::PathSnapshot );
        strFile += "Staying.jpg";
        dbInterface.OperateBlob( strFile, false,
                                                       bNocard ? CommonDataType::BlobTimeInImg : CommonDataType::BlobVehicleIn1, strWhere, bHistory );

        bExist = QFile::exists( strFile );
        if ( bExist ) {
            pFrmDisplayPic->DisplayPicture( strFile );
            QFile::remove( strFile );
        }
    }

    bExist = bExist &&  bZeroCol;
    SetFrameVisble( bExist );
}

void CDlgStaying::on_tabWidget_currentChanged(int index)
{
    SetChkClikedArray( false );
    SetFrameVisble( false );

    bool bMonth = ( 0 == index );
    ui->chk2->setEnabled( bMonth );
    ui->chk3->setEnabled( bMonth );

    bool bNocard = ( 2 == index );
    ui->chk1->setEnabled( !bNocard );
    ui->chk4->setEnabled( !bNocard );
}

void CDlgStaying::SetChkClikedArray( bool bInit )
{
    for ( int n = 0; n < 7; n++ ) {
        bChkCliked[ n ] = bInit;
    }
}

void CDlgStaying::SortData( int nChk, int nCb, bool bCb )
{
    if ( !bCb && GetClicked( nChk ) ) {
        return;
    }

    if ( ui->sbStart->value( )> ui->sbEnd->value( ) ) {
        CCommonFunction::MsgBox( NULL, "提示", "记录范围不正确", QMessageBox::Information );
        return;
    }

    QString strLimit = QString( " Limit %1, %2" ).arg(  QString::number( ui->sbStart->value( ) - 1 ),
                                                        QString::number( ui->sbEnd->value( ) ) );

    QString strOrder;
    GetOrderByClause( strOrder, nChk, nCb, ui->tabWidget->currentIndex( ) );

    GetMonthData( strOrder, strLimit );

    if ( 2 != nChk && 3 != nChk ) {
        GetTimeData( strOrder, strLimit );
    }

    if ( 1 != nChk && 2 != nChk && 3 != nChk && 4 != nChk) {
        GetNocardData( strOrder, strLimit );
    }

    return;

    switch ( ui->tabWidget->currentIndex( ) ) {
    case 0 :
        GetMonthData( strOrder, strLimit );
        break;

    case 1 :
        GetTimeData( strOrder, strLimit );
        break;

    case 2 :
        GetNocardData( strOrder, strLimit );
        break;
    }
}

int CDlgStaying::GetChkIndex( )
{
    int nIndex = 0;

    if ( ui->chk0->isChecked( ) ) {
       nIndex = 0;
    } else if ( ui->chk1->isChecked( ) ) {
       nIndex = 1;
    } else if ( ui->chk2->isChecked( ) ) {
       nIndex = 2;
    } else if ( ui->chk3->isChecked( ) ) {
       nIndex = 3;
    } else if ( ui->chk4->isChecked( ) ) {
      nIndex = 4;
    } else if ( ui->chk5->isChecked( ) ) {
      nIndex = 5;
    } else if ( ui->chk6->isChecked( ) ) {
      nIndex = 6;
    }

    return nIndex;
}

void CDlgStaying::GetOrderByClause( QString& strOrder, int nChk, int nCb, int nCardType )
{
    QString strAsc = ( 0 == nCb ) ? " ASC " : " DESC ";
    strOrder = " Order by %1 ";

    switch ( nChk ) {
    case 0 :
        strOrder = strOrder.arg( "cardno" );
        break;

    case 1 :
        strOrder = strOrder.arg( "cardselfno" );

        if ( 2 == nCardType ) {
            strOrder.clear( );
        }
        break;

    case 2 :
        strOrder = strOrder.arg( "username" );

        if ( 1 == nCardType || 2 == nCardType ) {
            strOrder.clear( );
        }
        break;

    case 3 :
        strOrder = strOrder.arg( "b.userphone" );

        if ( 1 == nCardType || 2 == nCardType ) {
            strOrder.clear( );
        }
        break;

    case 4 :
        strOrder = strOrder.arg( "carcp" );

        if ( 2 == nCardType ) {
            strOrder.clear( );
        }
        break;

    case 5 :
        strOrder = strOrder.arg( "inshebeiname" );
        break;

    case 6 :
        strOrder = strOrder.arg( "intime" );
        break;

    default :
        break;
    }

    if ( !strOrder.isEmpty( ) ) {
        strOrder += strAsc;
    }
}

void CDlgStaying::on_cbSort_currentIndexChanged(int index)
{
    SortData( GetChkIndex( ), index, true );
}

bool CDlgStaying::GetClicked( int nChk )
{
    bool bRet = bChkCliked[ nChk ];

    for ( int n = 0; n < 7; n++ ) {
        bChkCliked[ n ] = false;
    }

    bChkCliked[ nChk ] = true;

    return bRet;
}

void CDlgStaying::on_chk0_clicked(bool checked)
{
    SortData( 0, ui->cbSort->currentIndex( ) );
}

void CDlgStaying::on_chk1_clicked(bool checked)
{
    SortData( 1, ui->cbSort->currentIndex( ) );
}

void CDlgStaying::on_chk2_clicked(bool checked)
{
    SortData( 2, ui->cbSort->currentIndex( ) );
}

void CDlgStaying::on_chk3_clicked(bool checked)
{
    SortData( 3, ui->cbSort->currentIndex( ) );
}

void CDlgStaying::on_chk4_clicked(bool checked)
{
    SortData( 4, ui->cbSort->currentIndex( ) );
}

void CDlgStaying::on_chk5_clicked(bool checked)
{
    SortData( 5, ui->cbSort->currentIndex( ) );
}

void CDlgStaying::on_chk6_clicked(bool checked)
{
    SortData( 6, ui->cbSort->currentIndex( ) );
}

void CDlgStaying::on_chk0_toggled(bool checked)
{

}

void CDlgStaying::on_tableWidgetNoCard_cellClicked(int row, int column)
{
    DisplayPic( ( QTableWidget* ) sender( ), row, column );

    EmitPlate( ui->tableWidgetNoCard );
}

void CDlgStaying::on_tableWidgetMonth_customContextMenuRequested(const QPoint &pos)
{
    DisplayMenu( ui->tableWidgetMonth, pMenuMonth, pos );
}

void CDlgStaying::on_tableWidgetTime_customContextMenuRequested(const QPoint &pos)
{
    DisplayMenu( ui->tableWidgetTime, pMenuTime, pos );
}

void CDlgStaying::on_tableWidgetNoCard_customContextMenuRequested(const QPoint &pos)
{
    DisplayMenu( ui->tableWidgetNoCard, pMenuNoCard, pos );
}

void CDlgStaying::on_btnRange_clicked()
{
    if ( ui->sbStart->value( ) > ui->sbEnd->value( ) ) {
        CCommonFunction::MsgBox( NULL, "提示", "记录范围不正确", QMessageBox::Information );
        return;
    }

    QString strLimit = QString( " Limit %1, %2" ).arg(  QString::number( ui->sbStart->value( ) - 1 ),
                                                        QString::number( ui->sbEnd->value( ) ) );

    GetData( ui->tabWidget->currentIndex( ) + 1, strLimit );
}

void CDlgStaying::on_btnPrePage_clicked()
{
    if ( 0 == nPage ) {
        return;
    }

    int nStart = ( nPage - 1 ) * 100;
    if ( 0 < nStart ) {
        nStart-= 1;
    }

    QString strLimit = QString( " Limit %1, %2" ).arg( QString::number( nStart ), QString::number( 100 ) );
    GetData( ui->tabWidget->currentIndex( ) + 1, strLimit );
    nPage--;
}

void CDlgStaying::on_btnNextPage_clicked()
{
    nPage++;
    int nStart = nPage* 100;
    if ( 0 < nStart ) {
        nStart-= 1;
    }

    QString strLimit = QString( " Limit %1, %2" ).arg( QString::number( nStart ), QString::number( 100 ) );

    GetData( ui->tabWidget->currentIndex( ) + 1, strLimit );
}
