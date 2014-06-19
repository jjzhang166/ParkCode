#include "Header/valuecard.h"

#ifdef NewUI
    #include "ui_newvaluecard.h"
#else
    #include "ui_valuecard.h"
#endif

#include "Dialog/valuecarddialog.h"
#include "Common/commonfunction.h"
#include "Common/CommonType.h"
#include "Common/logicinterface.h"
#include "Dialog/valuerechargedialog.h"
#include "Dialog/dlgserach.h"
#include "Dialog/dlgbulkregister.h"
#include "Dialog/dlgcardloss.h"

CValueCard::CValueCard(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(
        #ifdef NewUI
            new Ui::CONCAT_NEW_NAME( New , CValueCard )
        #else
            new Ui::CONCAT_NEW_NAME( , CValueCard )
        #endif
        )
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );

    //pParent->OperateTableWidget( ui->tableValue, CommonDataType::ValueTable, CommonDataType::InitializeType );
    //pParent->OperateTableWidget( ui->tableRecharge, CommonDataType::ValueRechargeTable, CommonDataType::InitializeType );
    //pParent->OperateTableWidget( ui->tableAccess, CommonDataType::ValueAccessTable, CommonDataType::InitializeType );
    //pParent->OperateTableWidget( ui->tableEntranceRight, CommonDataType::ValueEntranceRightTable, CommonDataType::InitializeType );

    FillPlateCtrl( );
    pMenu = NULL;
    CCommonFunction::GetCarType( ui->cbxCarType );

    GetDataFromDb( );
    ui->tableRecharge->horizontalHeader( )->hideSection( 1 );

    ui->lblCardNo->setVisible( false );
    ui->lblUserID->setVisible( false );
    ControlDataGrid( );
    ui->lblTitle->setText( windowTitle( ) );

    QHeaderView* pHeader = ui->tableAccess->horizontalHeader( );
    pHeader->hideSection( ui->tableAccess->columnCount( ) - 1 );
}

CValueCard::~CValueCard()
{
    delete ui;
}

void CValueCard::ControlDataGrid( )
{
    int nIndex = 0;

    QHeaderView* pHeader = ui->tableRecharge->horizontalHeader( );
    nIndex = 2;
    pHeader->resizeSection( nIndex, pHeader->sectionSize( nIndex ) * 2 );

    pHeader = ui->tableAccess->horizontalHeader( );
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

void CValueCard::GetDataFromDb( )
{
    QStringList lstRows;
    QString strWhere = "order by cardselfno";
    int nRows = CLogicInterface::GetInterface( )->OperateCardInfo( lstRows, CommonDataType::ValueCard,
                                                       CommonDataType::SelectData, strWhere );

    CCommonFunction::FreeAllRows( ui->tableValue );
    CCommonFunction::FillTable( ui->tableValue, nRows, lstRows );

    ///////////////////////////////
    QTableWidgetItem* pItem = NULL;
    nRows = ui->tableValue->rowCount( );
    QString strText;
    QString strFalse = "0";
    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        for ( int nCol = 1; nCol < 3; nCol++ ) {
            pItem = ui->tableValue->item( nIndex, nCol );
            strText = pItem->text( );
            pItem->setText( "" );
            pItem->setCheckState( strFalse == strText ? Qt::Unchecked : Qt::Checked );
            pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        }
    }
}

void CValueCard::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CValueCard::WriteCardLog(QString strCotent)
{
    QDateTime dtDateTime = QDateTime::currentDateTime( );
    pParent->WriteLog( "卡片管理", strCotent, CommonDataType::CardMgmLog, dtDateTime );
}

void CValueCard::OpenDialog( bool bNew )
{
    QString strUser = pParent->GetUserName( );
    CValueCardDialog dlg( bNew, strUser, ui->tableValue, this );
    dlg.InitDlg( );
    pParent->SetCardControl( dlg.GetCardNumCtrl( ) );
    dlg.exec( );

    if ( bNew ) {
        lstCarID.clear( );
    }
    pParent->SetCardControl( NULL );
}

void CValueCard::on_btnValueRecharge_clicked( )
{
    Recharge( );
}

void CValueCard::SaveCarInfo( )
{
    // carid carpic carcp, carmodel, carhaoma, cardindex
   QString strCardID = "edtVechileID%1";
   QString strTmp;
   QStringList lstRows;
   QLineEdit* pEdit = NULL;
   QString strExistSql = "Select cardindex from carinfo where carcp ='%1' and cardindex <> '%2'";
   QString strInsertSql = "Insert IGNORE Into carinfo( carcp, carmodel, cardindex, carhaoma ) values( '%1','%2','%3', '%4' )";
   QString strUpdateSql = "Update IGNORE carinfo set carcp = '%1', carmodel = '%2', carhaoma = '%3' where carid = %4";
   QString strDeleteSql = "Delete IGNORE From carinfo where carid = %1";

   for ( int nIndex = 0; nIndex < 10; nIndex++ ) {

       lstRows.clear( );
       strTmp = strCardID.arg( nIndex );
       pEdit = ui->gbOwner->findChild< QLineEdit* >( strTmp );

       if ( pEdit->text( ).isEmpty( ) ) {
           if ( !pEdit->statusTip( ).isEmpty( ) ) {
               if ( 0 == nIndex ) {
                   strTmp = strUpdateSql.arg( "未知", ui->cbxCarType->currentText( ),
                                              ui->edtDriveID->text( ), pEdit->statusTip( ) );
                   CLogicInterface::GetInterface( )->ExecuteSql( strTmp, lstRows );
               } else {
                    strTmp = strDeleteSql.arg( pEdit->statusTip( ) );
                    CLogicInterface::GetInterface( )->ExecuteSql( strTmp, lstRows );
               }
           }
           continue;
       }

       strTmp = strExistSql.arg( pEdit->text( ), ui->lblCardNo->text( ) );
       if ( "未知" != pEdit->text( ) && 0 < CLogicInterface::GetInterface( )->ExecuteSql( strTmp, lstRows ) ) {
           strTmp = QString( "车牌【%1】已与卡号【%2】绑定。" ).arg( pEdit->text( ), lstRows.join( "," ) );
           CCommonFunction::MsgBox( NULL, QString( "提示" ), strTmp, QMessageBox::Information );
           return;
       }

       //strTmp = strExistSql.arg( pEdit->text( ), ui->lblCardNo->text( ) );
       //int nRows = CLogicInterface::GetInterface( )->ExecuteSql( strTmp, lstRows );

       if ( pEdit->statusTip( ).isEmpty( ) ) {
            strTmp = strInsertSql.arg( pEdit->text( ), ui->cbxCarType->currentText( ),
                                       ui->lblCardNo->text( ), ui->edtDriveID->text( ) );
       } else {
            strTmp = strUpdateSql.arg( pEdit->text( ), ui->cbxCarType->currentText( ),
                                       ui->edtDriveID->text( ), pEdit->statusTip( ) );
       }

       CLogicInterface::GetInterface( )->ExecuteSql( strTmp, lstRows );
   }

   on_tableValue_cellClicked( ui->tableValue->currentRow( ), 0 );
}

void CValueCard::on_btnValueSave_clicked( )
{
    //if ( ui->edtVechileID0->text( ).isEmpty( ) ) {
        //CCommonFunction::MsgBox( NULL, "提示", "请输入第一个车牌号！", QMessageBox::Information );
    //    return;
    //}
    ui->edtName->text( );
    ui->cbxSex->currentText( );
    ui->edtTel->text( );
    ui->edtUnit->text( );
    ui->edtID->text( );
    ui->edtAddr->text( );
    //ui->edtVechileID->text( );
    ui->edtDriveID->text( );
    //ui->edtVechileType->text( );
    //ui->gvOwner->
    //ui->gvVechile
    //strSql = "SELECT username, usersex, useradress, ";
    //strSql += "usercorp, userphone, userhaoma, "; //userpic
    //strSql += "userid FROM userinfo "; //cardindex
    QStringList lstRows;
    QString strID = ui->lblUserID->text( );
    QString strWhere = QString( " Where userid = %1" ).arg( strID );
    lstRows << ui->edtName->text( )
            << ui->cbxSex->currentText( )
            << ui->edtAddr->text( )
            << ui->edtUnit->text( )
            << ui->edtTel->text( )
            << ui->edtID->text( )
            << ui->lblCardNo->text( );

            CLogicInterface::GetInterface( )->OperateOwnerInfo( lstRows,
                                                                 ( "" == strID ) ? CommonDataType::InsertData :
                                                                 CommonDataType::UpdateData, strWhere );
    //"Select carcp,carmodel,cardindex,carhaoma FROM carinfo ";
     // carid carpic carcp, carmodel, carhaoma, cardindex
    SaveCarInfo( );
    CCommonFunction::OperationSuccess( );
}

void CValueCard::on_btnEntranceSave_clicked( )
{
    //pParent->OperateTableWidget( ui->tableEntranceRight, CommonDataType::ValueEntranceRightTable, CommonDataType::SaveType );
}

void CValueCard::resizeEvent( QResizeEvent* )
{
    CalculatePos( );
}

void CValueCard::CalculatePos( )
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

void CValueCard::AddRecord( )
{
    OpenDialog( true );
}

void CValueCard::ModifyRecord( )
{
    qint32 nCurrentRow = ui->tableValue->currentRow( );
    if ( 0 > nCurrentRow ) {
        return;
    }

    OpenDialog( false );
}

void CValueCard::DeleteRecord( )
{
    int nRow = ui->tableValue->currentRow( );

    if ( -1 == nRow ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 "请选择要删除的数据！", QMessageBox::Information );
        return;
    } else if ( QMessageBox::Ok == CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                                            "确定要删除数据吗？", QMessageBox::Question ) ){
        QTableWidgetItem* pItem = ui->tableValue->item( nRow, 0 );
        QString strWhere = QString( " Where cardno = '%1'" ).arg( pItem->text( ) );
        QStringList lstRows;

        QString strCotent = QString( "删除储值卡 卡号　：%1" ).arg( pItem->text( ) );
        WriteCardLog( strCotent );

        CLogicInterface::GetInterface( )->OperateCardInfo( lstRows, CommonDataType::ValueCard,
                                                          CommonDataType::DeleteData, strWhere );
        CCommonFunction::FreeRow( ui->tableValue, nRow, ui->tableValue->columnCount( ) );
        lstCarID.clear( );
    }
}

void CValueCard::Recharge( )
{
    int nRow = ui->tableValue->currentRow( );
    if ( -1 == nRow ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请选择要充值的卡！" ), QMessageBox::Information );
        return;
    }

    CValueRechargeDialog dlg( NULL );
    QTableWidgetItem* pItem = ui->tableValue->item( nRow, 5 );

    if ( NULL != pItem ) {
        dlg.SetRemainder( pItem->text( ) );
    }

    int nRet = dlg.exec( );
    if ( QDialog::Accepted == nRet ) {
        QStringList lstRows;
        dlg.GetValue( lstRows );
        lstRows << pParent->GetUserName( )
                << ui->lblCardNo->text( );

        int nTotal = lstRows[ 0 ].toInt( ) + pItem->text( ).toInt( );
        pItem->setText( QString::number( nTotal ) );

        QString strWhere = "";
        CLogicInterface::GetInterface( )->OperateChargeRecord( lstRows,
                                                               CommonDataType::InsertData, strWhere );
        CLogicInterface::GetInterface( )->UpdateSaveCardRemainder( true, lstRows[ 0 ].toUInt( ), ui->lblCardNo->text( ) );
    }
}

void CValueCard::Serach( )
{
    CDlgSerach dlg( CommonDataType::ValueCard );
    connect( &dlg, SIGNAL( PositionRow( QString ) ), this, SLOT( PositionRow( QString ) ) );
    pParent->SetCardControl( dlg.GetEditCntrl(  ) );
    dlg.exec( );
    pParent->SetCardControl( NULL );
}

void CValueCard::PositionRow( QString strCardID )
{
    QList< QTableWidgetItem* > lstItem = ui->tableValue->findItems( strCardID, Qt::MatchFixedString );
    if ( 0 >= lstItem.count( ) ) {
        return;
    }

    QTableWidgetItem* pItem = lstItem.at( 0 );
    int nRow = ui->tableValue->row( pItem );
    //ui->tableValue->setCurrentItem( pItem, QItemSelectionModel::ToggleCurrent );
    on_tableValue_cellClicked( nRow, 0 );
    ui->tableValue->selectRow( nRow );
}

void CValueCard::ChangeCard( )
{

}

void CValueCard::Refresh( )
{
    GetDataFromDb( );
}

void CValueCard::PrintCardInfo( )
{

}

void CValueCard::Download2CC( )
{

}

void CValueCard::AddBulkRecord( )
{
    CDlgBulkRegister dlg( CommonDataType::ValueCard, ui->tableValue, pParent->GetUserName( ) );
    QString strPath;
    CCommonFunction::GetPath( strPath, CommonDataType::PathUIImage );
    strPath += "NewIcon/CommonMiddleBG-normal.jpg";
    dlg.setStatusTip( strPath );
    pParent->SetCardControl( dlg.GetEditCntrl(  ) );
    dlg.exec( );
    pParent->SetCardControl( NULL );
}

void CValueCard::CardLossProcess( )
{
    qint32 nCurrentRow = ui->tableValue->currentRow( );
    if ( 0 > nCurrentRow ) {
        return;
    }

    QString strID = ui->tableValue->item( nCurrentRow, 0 )->text( );
    CDlgCardLoss dlg( strID, CommonDataType::ValueCard );
    dlg.exec( );
}


void CValueCard::CreateContextMenu( QTableWidget *parent )
{
    if ( NULL == pMenu ) {
        pMenu = new QMenu( parent );
        pMenu->addAction( "新增", this, SLOT( AddRecord( ) ) );
        pMenu->addAction( "批量新增", this, SLOT( AddBulkRecord( ) ) );
        pMenu->addAction( "编辑", this, SLOT( ModifyRecord( ) ) );
        pMenu->addAction( "删除", this, SLOT( DeleteRecord( ) ) );
        pMenu->addAction( "续费", this, SLOT( Recharge( ) ) );
        pMenu->addAction( "查找", this, SLOT( Serach( ) ) );
        //pMenu->addAction( "换卡", this, SLOT( ChangeCard( ) ) );
        pMenu->addAction( "车进场 卡遗失处理", this, SLOT( CardLossProcess( ) ) );
        pMenu->addSeparator( );
        pMenu->addAction( "刷新", this, SLOT( Refresh( ) ) );
        pMenu->addSeparator( );
        pMenu->addAction( "打印卡片资料", this, SLOT( PrintCardInfo( ) ) );
        pMenu->addAction( "下载到中心控制器", this, SLOT( Download12CC( ) ) );
    }

    pMenu->exec( parent->cursor().pos( ) );
}

void CValueCard::on_tableValue_customContextMenuRequested( QPoint )
{
    CreateContextMenu( ui->tableValue );
}

void CValueCard::on_tableValue_cellClicked(int row, int column)
{
    if ( -1 == row ) {
        return;
    }

    QTableWidgetItem* pItem = ui->tableValue->item( row, 0 );
    ui->lblCardNo->setText( pItem->text( ) );
    ui->lblUserID->setText( "" );
    ui->edtVechileID0->clear( );
    ui->edtVechileID0->setStatusTip( "" );
    ClearText( 1 );

    //////////////////////////////////////////////////////////////////////
    QString strWhere = QString( " Where cardindex = '%1'" ).arg( pItem->text( ) );
    QStringList lstRows;
    int nRows = CLogicInterface::GetInterface( )->OperateOwnerInfo( lstRows,
                                                         CommonDataType::SelectData, strWhere );

    if ( 0 < nRows ) {
        ui->edtName->setText( lstRows[ 0 ] );
        int nIndex = CCommonFunction::FindComboBoxItem( ui->cbxSex, lstRows[ 1 ] );
        if ( -1 == nIndex ) {
            nIndex = 0;
        }
        ui->cbxSex->setCurrentIndex( nIndex );
        ui->edtAddr->setText( lstRows[ 2 ] );
        ui->edtUnit->setText( lstRows[ 3 ] );
        ui->edtTel->setText( lstRows[ 4 ] );
        ui->edtID->setText( lstRows[ 5 ] );
        ui->lblUserID->setText( lstRows[ 6 ] );
    }

    ///////////////////////////////////////////////////////////////////////
    nRows = CLogicInterface::GetInterface( )->OperateCarInfo( lstRows,
                                                             CommonDataType::SelectData, strWhere );

    lstCarID.clear( );
    if ( 0 < nRows ) {
        //carcp, carmodel, carhaoma, carid
        QString strCarPlate = "edtVechileID%1";
        QLineEdit* pEdit = NULL;
        QString strTmp;
        int nField = 0;
        for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
            nField = nIndex * 4;
            strTmp = strCarPlate.arg( nIndex );
            pEdit = ui->gbOwner->findChild< QLineEdit* >( strTmp );
            pEdit->setText( lstRows[ nField ] );

            if ( 0 == nIndex ) {
                int nCarTypeIdx = CCommonFunction::FindComboBoxItem( ui->cbxCarType, lstRows[ 1 ] );
                if ( -1 == nCarTypeIdx ) {
                    nCarTypeIdx = 2;
                }
                ui->cbxCarType->setCurrentIndex( nCarTypeIdx );
                ui->edtDriveID->setText( lstRows[ 2 ] );
            }

            lstCarID.append( lstRows[ nField + 3 ] );
            pEdit->setStatusTip( lstRows[ nField + 3 ] );
        }

        for ( int nIndex = nRows; nIndex < 10; nIndex++ ) {
            strTmp = strCarPlate.arg( nIndex );
            pEdit = ui->gbOwner->findChild< QLineEdit* >( strTmp );
            pEdit->setStatusTip( "" );
        }
    }

    CCommonFunction::FreeAllRows( ui->tableAccess );
    CCommonFunction::FreeAllRows( ui->tableRecharge );
    CCommonFunction::FreeAllRows( ui->tableEntranceRight );

    /////////////////////////////////////////////////////////////////
    strWhere = QString( " Where cardno = '%1'" ).arg( pItem->text( ) );
    nRows = CLogicInterface::GetInterface( )->OperateChargeRecord( lstRows,
                                                       CommonDataType::SelectData, strWhere );
    CCommonFunction::FillTable( ui->tableRecharge, nRows, lstRows );

    ///////////////////////////////////////////////////////////////////
    QString strSql = QString ( "Select inshebeiname, intime, outshebeiname, outtime, stoprdid From stoprd %1" ).arg( strWhere );
    //nRows = CLogicInterface::GetInterface( )->OperateInOutRecord( lstRows,
    //                                                   CommonDataType::SelectData, strWhere );
    nRows = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows, CCommonFunction::GetHistoryDb( ) );
    CCommonFunction::FillTable( ui->tableAccess, nRows, lstRows );

    ///////////////////////////////////////////////////////////////////
    nRows = CLogicInterface::GetInterface( )->OperateInOutRight( lstRows,
                                                       CommonDataType::SelectData, strWhere );
    CCommonFunction::FillCardRightTable( ui->tableEntranceRight, nRows, lstRows );

    QString strCarID = ( 0 == lstCarID.count( ) ) ? "" : lstCarID[ 0 ];
    strWhere = QString( " where carid = %1" ).arg( strCarID );
    CCommonFunction::LoadFourImages( CommonDataType::BlobVehicle, strWhere, *ui->lblCar );
    strWhere = QString( " where userid = %1" ).arg( ui->lblUserID->text( ) );
    CCommonFunction::LoadFourImages( CommonDataType::BlobOwner, strWhere, *ui->lblOwner );
}

void CValueCard::FillPlateCtrl( )
{
    QString strCarPlate = "edtVechileID%1";
    QLineEdit* pEdit = NULL;
    QString strTmp;

    for ( int nIndex = 0; nIndex < 10; nIndex++ ) {
        strTmp = strCarPlate.arg( nIndex );
        pEdit = ui->gbOwner->findChild< QLineEdit* >( strTmp );
        edtPlates[ nIndex ] = pEdit;
        QObject::connect( pEdit, SIGNAL( textChanged( QString ) ), this, SLOT( textChanged( QString ) ) );
    }
}

void CValueCard::ClearText( int nStart )
{
    for ( int nIndex = nStart; nIndex  < 10; nIndex++ ) {
        edtPlates[ nIndex ]->clear( );
        edtPlates[ nIndex ]->setEnabled( false );
    }
}

void CValueCard::textChanged( QString text )
{
    QLineEdit* pEdit = qobject_cast< QLineEdit* >( sender( ) );
    QString strName = "edtVechileID";
    int nStartIndex = pEdit->objectName( ).remove( strName ).toInt( ); // 0 to 9
    int nTotal = 10;

    if ( nStartIndex == ( nTotal - 1 ) ) { // 9
        return;
    }

    bool bEnable = text.isEmpty( );

    if ( bEnable ) {
        ClearText( ++nStartIndex );
    } else {
        edtPlates[ ++nStartIndex ]->setEnabled( !bEnable );
    }
}

void CValueCard::on_btnMinimalize_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CValueCard::on_tableAccess_cellClicked(int row, int column)
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

void CValueCard::on_lblClose_linkActivated(QString)
{
    close( );
}

void CValueCard::on_btnSaveRight_clicked()
{
    QStringList lstRows;
    QString strWhere = "";
    CCommonFunction::UpateCardRight( lstRows, ui->tableEntranceRight );
    CLogicInterface::GetInterface( )->OperateInOutRight( lstRows, CommonDataType::UpdateData, strWhere );
    CCommonFunction::OperationSuccess( );
}
