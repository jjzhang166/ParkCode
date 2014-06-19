#include "dlgbulkregister.h"
#include "ui_dlgbulkregister.h"
#include <QDateTimeEdit>
#include <QComboBox>

CDlgBulkRegister::CDlgBulkRegister( CommonDataType::CardType card, QTableWidget* table, QString strUser,  QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::CDlgBulkRegister)
{
    ui->setupUi(this);
    cardType = card;
    tabWidget = table;
    strCreator = strUser;
    ui->edtCardID->setVisible( false );

    AddColumn( );

    ui->frame->setEnabled( CommonDataType::MonthlyCard == card );

    QString strType [ ] = { "月租", "储值", "计时" };
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    ui->lblTitle->setText( statusTip( ).arg( strType[ cardType ] ) );
    setWindowFlags( Qt::FramelessWindowHint );

    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    nBulkEndMonth = 0;
    if ( NULL != pSet ) {
        nBulkEndMonth = pSet->value( "CommonCfg/CardBulkRegEndTime", 1 ).toInt( );
    }

    ui->spMonth->setValue( nBulkEndMonth );
    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CDlgBulkRegister::~CDlgBulkRegister()
{
    delete ui;
}

void CDlgBulkRegister::resizeEvent( QResizeEvent *event )
{
    QWidget::resizeEvent( event );

    QString strFile = statusTip( );
    QPixmap bgimage( strFile );
    QPalette pal( palette( ) );
    pal.setBrush( QPalette::Window, QBrush( bgimage.scaled( event->size( ),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation ) ) );
    setPalette(pal);
}

QLineEdit* CDlgBulkRegister::GetEditCntrl( )
{
    return ui->edtCardID;
}

void CDlgBulkRegister::on_edtCardID_textChanged(const QString &arg1)
{
    AddRecord( arg1 );
}

void CDlgBulkRegister::AddRecord( const QString &strCardID )
{
    QList< QTableWidgetItem* > lstItem = ui->tabRecord->findItems( strCardID, Qt::MatchFixedString );
    if ( 0 < lstItem.count( ) ) {
        QTableWidgetItem* pItem = lstItem.at( 0 );
        ui->tabRecord->setCurrentItem( pItem, QItemSelectionModel::ToggleCurrent );
        return;
    }

    switch ( cardType ) {
    case CommonDataType::MonthlyCard :
        AddMonthRow( strCardID );
        break;

    case CommonDataType::ValueCard :
        AddValueRow( strCardID );
        break;

    case CommonDataType::TimeCard :
        AddTimeRow( strCardID );
        break;
    }
}

void CDlgBulkRegister::OnBulkMonth( int nMonth )
{
    QDateTimeEdit* pDt = NULL;
    QDateTime dtStart;

    for ( int nRow = 0; nRow < ui->tabRecord->rowCount( ); nRow++ ) {
        pDt = ( QDateTimeEdit* ) ui->tabRecord->cellWidget( nRow, 5 );
        dtStart = pDt->dateTime( );

        pDt = ( QDateTimeEdit* ) ui->tabRecord->cellWidget( nRow, 6 );
        dtStart = dtStart.addMonths( nMonth );
        //qDebug( ) << dtStart.toString( ) << endl;
        pDt->setDateTime( dtStart );
    }
}

void CDlgBulkRegister::AddColumn( )
{
    int nCols = 0;
    QStringList lstColName;

    switch ( cardType ) {
    case CommonDataType::MonthlyCard :
        nCols = 11;
        lstColName << "卡号" << "入场必须刷卡" << "出场必须刷卡" << "多进多出" << "卡类型"  << "有效期开始时间"
                              << "有效期结束时间" << "卡状态" << "卡片自编号" << "备注" << "登记者";
        ui->spMonth->setEnabled( true );
        connect( ui->spMonth, SIGNAL( valueChanged( int ) ), this, SLOT( OnBulkMonth( int  ) ) );
        break;

    case CommonDataType::ValueCard :
        nCols = 10;
        lstColName << "卡号" << "入场必须刷卡" << "出场必须刷卡" << "卡类型"  << "卡状态"
                              << "卡余额" << "扣费标准" << "卡片自编号" << "备注" << "登记者";
        break;

    case CommonDataType::TimeCard :
        nCols = 5;
        lstColName << "卡号" << "卡类型" << "收费标准" << "卡片自编号"<< "卡状态";
        ui->cbxCarType->setEnabled( true );
        AddCbxValue( ui->cbxCarType );
        connect( ui->cbxCarType, SIGNAL( currentIndexChanged( int ) ), this, SLOT( OnBulkCarType( int ) ) );
        break;
    }

    ui->tabRecord->setColumnCount( nCols );

    QTableWidgetItem* pItem = NULL;
    for ( int nCol = 0; nCol < nCols; nCol++ ) {
        pItem = new QTableWidgetItem( lstColName[ nCol ] );
        ui->tabRecord->setHorizontalHeaderItem( nCol, pItem );
    }
}

void CDlgBulkRegister::OnBulkCarType( int nIndex )
{
    QComboBox* pCbx = NULL;

    for ( int nRow = 0; nRow < ui->tabRecord->rowCount( ); nRow++ ) {
        pCbx = ( QComboBox* ) ui->tabRecord->cellWidget( nRow, 2 );
        pCbx->setCurrentIndex( nIndex );
    }
}

void CDlgBulkRegister::GetSelfNumber( QString &strNumber )
{
    if ( Qt::Unchecked == ui->chkID->checkState( ) ) {
        strNumber = "未知";
        return;
    }

    char cValue[ 32 ] = { 0 };
    int nValue = ui->spValue->value(  );

    QString strDigit = "%." + ui->spDigit->text( ) + "d";
    QByteArray byData = strDigit.toAscii( );
    ::sprintf( cValue, byData.data( ), nValue );

    strNumber = cValue;
    ui->spValue->setValue( nValue + 1 );
}

void CDlgBulkRegister::AddItem( const QString &strText, int nRow, int nCol, QTableWidget* pTable )
{
    QTableWidgetItem* pItem = new QTableWidgetItem( strText );
    pItem->setFlags( Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    pTable->setItem( nRow, nCol, pItem );
}

void CDlgBulkRegister::AddCheckBoxItem( int nRow, int nCol, QTableWidget* pTable, bool bChecked )
{
    QTableWidgetItem* pItem = new QTableWidgetItem( );
    pItem->setFlags( Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable );
    pItem->setCheckState( bChecked ? Qt::Checked : Qt::Unchecked );
    pTable->setItem( nRow, nCol, pItem );
}

void CDlgBulkRegister::AddDateTimeItem( int nRow, int nCol, const QDateTime& dtDeafult, QTableWidget* pTable )
{
    QDateTimeEdit* pDateTime = new QDateTimeEdit( dtDeafult );
    pDateTime->setCalendarPopup( true );
    pTable->setCellWidget( nRow, nCol, pDateTime );
}

void CDlgBulkRegister::AddCbxValue( QComboBox *pCbx )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgTariff );
    QString strKey = "CarType/Count%1";
    int nCount = pSet->value( strKey.arg( "" ), 0 ).toInt( );

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        pCbx->addItem( pSet->value( strKey.arg( nIndex ), "" ).toString( ) );
    }
}

void CDlgBulkRegister::AddComboBoxItem( int nRow, int nCol, int nDefault, int nItem, QTableWidget* pTable )
{
    QComboBox* pCB = new QComboBox(  );

    switch ( nItem ) {
    case 0 :
        pCB->addItem( "EMID卡" );
        pCB->addItem( "MIFARE卡" );
        break;

    case 1 :
        pCB->addItem( "启用" );
        pCB->addItem( "挂失" );
        break;

    case 2 :
        AddCbxValue( pCB );
        break;
    }

    pCB->setCurrentIndex( nDefault );
    pTable->setCellWidget( nRow, nCol, pCB );
}

void CDlgBulkRegister::AddMonthRow( const QString &strCardID )
{
    ui->tabRecord->insertRow( 0 );
    QDateTime dt = QDateTime::currentDateTime( );
    QString strText;

    for ( int nIndex = 0; nIndex  < ui->tabRecord->columnCount( ); nIndex++ ) {
        switch ( nIndex ) {
        case 0 :
            AddItem( strCardID, 0, nIndex, ui->tabRecord );
            break;

        case 1 :
        case 2 :
        case 3 :
            AddCheckBoxItem( 0, nIndex, ui->tabRecord );
            break;

        case 4 :
        case 7 :
            AddComboBoxItem( 0, nIndex, 0, ( 7 == nIndex ), ui->tabRecord );
            break;

        case 5 :
        case 6 :
            if ( 6 == nIndex ) {
                dt = dt.addMonths( nBulkEndMonth );
            }
            AddDateTimeItem( 0, nIndex, dt, ui->tabRecord );
            break;

        case 8 :
            GetSelfNumber( strText );
            AddItem( strText, 0, nIndex, ui->tabRecord );
            break;

        case 9 :
            strText = "未知";
            AddItem( strText, 0, nIndex, ui->tabRecord );
            break;

        case 10 :
            AddItem( strCreator, 0, nIndex, ui->tabRecord );
            break;
        }
    }
}

void CDlgBulkRegister::AddValueRow( const QString &strCardID )
{
    ui->tabRecord->insertRow( 0 );
    QString strText = "0";

    for ( int nIndex = 0; nIndex  < ui->tabRecord->columnCount( ); nIndex++ ) {
        switch ( nIndex ) {
        case 0 :
            AddItem( strCardID, 0, nIndex, ui->tabRecord );
            break;

        case 1 :
        case 2 :
            AddCheckBoxItem( 0, nIndex, ui->tabRecord );
            break;

        case 3 :
        case 4 :
            AddComboBoxItem( 0, nIndex, 0, ( 4 == nIndex ), ui->tabRecord );
            break;

        case 5 :
            AddItem( strText, 0, nIndex, ui->tabRecord );
            break;

        case 6 :
            AddComboBoxItem( 0, nIndex, 2, 2, ui->tabRecord );
            break;

        case 7 :
            strText = "未知";
            AddItem( strText, 0, nIndex, ui->tabRecord );
            break;

        case 8 :
            GetSelfNumber( strText );
            AddItem( strText, 0, nIndex, ui->tabRecord );
            break;

        case 9 :
            AddItem( strCreator, 0, nIndex, ui->tabRecord );
            break;
        }
    }
}

void CDlgBulkRegister::AddTimeRow( const QString &strCardID )
{
    ui->tabRecord->insertRow( 0 );
    QString strText;

    for ( int nIndex = 0; nIndex  < ui->tabRecord->columnCount( ); nIndex++ ) {
        switch ( nIndex ) {
        case 0 :
            AddItem( strCardID, 0, nIndex, ui->tabRecord );
            break;

        case 1 :
            AddComboBoxItem( 0, nIndex, 0, 0, ui->tabRecord );
            break;

        case 2 :
            AddComboBoxItem( 0, nIndex, 2, 2, ui->tabRecord );
            break;

        case 3 :
            GetSelfNumber( strText );
            AddItem( strText, 0, nIndex, ui->tabRecord );
            break;

        case 4 :
            AddComboBoxItem( 0, nIndex, 0, 1, ui->tabRecord );
            break;
        }
    }
}

void CDlgBulkRegister::SaveData( )
{
    QStringList lstDuplication;
    QStringList lstTotalSql;

    switch ( cardType ) {
    case CommonDataType::MonthlyCard :
        SaveMonthData( lstDuplication, lstTotalSql );
        break;

    case CommonDataType::ValueCard :
        SaveValueData( lstDuplication, lstTotalSql );
        break;

    case CommonDataType::TimeCard :
        SaveTimeData( lstDuplication, lstTotalSql );
        break;
    }

    if ( 0 < lstDuplication.count( ) ) {
        CCommonFunction::MsgBox( NULL, "提示", "下列卡号已存在：\r\n" + lstDuplication.join( "," ),
                                 QMessageBox::Information );
    }

    if ( 0 < lstTotalSql.count( ) ) {
        ExecuteSql( lstTotalSql );
    }
}

void CDlgBulkRegister::SaveMonthData( QStringList &lstDuplication, QStringList& lstTotalSql )
{
    int nRows = ui->tabRecord->rowCount( );
    QStringList lstSql;
    QString strTrue = "1";
    QString strFalse = "0";
    QString strDateTime = "";
    QDateTime dt;
    QString strQuotation = "'";
    bool bChecked = false;
    QComboBox* pCB = NULL;
    QDateTimeEdit* pDT = NULL;
    QString strText = "";
    QStringList lstExist;

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        lstSql.clear( );
        strText = ui->tabRecord->item( nRow, 0 )->text( );

        CLogicInterface::GetInterface( )->ExistCardNumber(strText, lstExist );
        if ( 0 < lstExist.count( ) ) {
            lstDuplication << lstExist;
            continue;
        }

        QList< QTableWidgetItem* > lstItems = tabWidget->findItems( strText, Qt::MatchFixedString );
        if ( 0 < lstItems.count( ) ) {
            lstDuplication << strText;
            continue;
        }

        tabWidget->insertRow( 0 );

        for ( int nCol = 0; nCol < ui->tabRecord->columnCount( ); nCol++ ) {
            switch ( nCol ) {
                case 0 :
                case 8 :
                case 9 :
                case 10 :
                    strText = ui->tabRecord->item( nRow, nCol )->text( );
                    lstSql  << ( strQuotation + strText + strQuotation );
                    AddItem( strText, 0, nCol, tabWidget );
                    break;

                case 1 :
                case 2 :
                case 3 :
                    bChecked = Qt::Checked == ui->tabRecord->item( nRow, nCol )->checkState( );
                    lstSql << ( bChecked ? strTrue : strFalse );
                    AddCheckBoxItem( 0, nCol, tabWidget, bChecked );
                    break;

                case 4 :
                case 7 :
                    pCB = ( QComboBox* ) ui->tabRecord->cellWidget( nRow, nCol );
                    strText = pCB->currentText( );
                    lstSql << ( strQuotation + strText + strQuotation );
                    AddItem( strText, 0, nCol, tabWidget );
                    break;

                case 5 :
                case 6 :
                    pDT = ( QDateTimeEdit* )  ui->tabRecord->cellWidget( nRow, nCol );
                    dt = pDT->dateTime( );
                    CCommonFunction::DateTime2String( dt, strDateTime );
                    lstSql << ( strQuotation + strDateTime + strQuotation );
                    AddItem( strDateTime, 0, nCol, tabWidget );
                    break;
            }
        }

        lstTotalSql << ( "(" + lstSql.join( "," ) + " )" );
    }
}

void CDlgBulkRegister::SaveValueData( QStringList &lstDuplication, QStringList& lstTotalSql )
{
    int nRows = ui->tabRecord->rowCount( );
    QStringList lstSql;
    QString strTrue = "1";
    QString strFalse = "0";
    QString strQuotation = "'";
    bool bChecked = false;
    QComboBox* pCB = NULL;
    QString strText = "";
    QStringList lstExist;

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        lstSql.clear( );
        strText = ui->tabRecord->item( nRow, 0 )->text( );

        CLogicInterface::GetInterface( )->ExistCardNumber(strText, lstExist );
        if ( 0 < lstExist.count( ) ) {
            lstDuplication << lstExist;
            continue;
        }

        QList< QTableWidgetItem* > lstItems = tabWidget->findItems( strText, Qt::MatchFixedString );
        if ( 0 < lstItems.count( ) ) {
            lstDuplication << strText;
            continue;
        }

        tabWidget->insertRow( 0 );

        for ( int nCol = 0; nCol < ui->tabRecord->columnCount( ); nCol++ ) {
            switch ( nCol ) {
                case 0 :
                case 5 :
                case 7 :
                case 8 :
                case 9 :
                    strText = ui->tabRecord->item( nRow, nCol )->text( );
                    lstSql  << ( strQuotation + strText + strQuotation );
                    AddItem( strText, 0, nCol, tabWidget );
                    break;

                case 3 :
                case 4 :
                case 6 :
                    pCB = ( QComboBox* ) ui->tabRecord->cellWidget( nRow, nCol );
                    strText = pCB->currentText( );
                    lstSql << ( strQuotation + strText + strQuotation );
                    AddItem( strText, 0, nCol, tabWidget );
                    break;

                case 1 :
                case 2 :
                    bChecked = Qt::Checked == ui->tabRecord->item( nRow, nCol )->checkState( );
                    lstSql << ( bChecked ? strTrue : strFalse );
                    AddCheckBoxItem( 0, nCol, tabWidget, bChecked );
                    break;
            }
        }

        lstTotalSql << ( "(" + lstSql.join( "," ) + " )" );
    }
}

void CDlgBulkRegister::SaveTimeData( QStringList &lstDuplication, QStringList& lstTotalSql )
{
    int nRows = ui->tabRecord->rowCount( );
    QStringList lstSql;
    QString strQuotation = "'";
    QComboBox* pCB = NULL;
    QString strText = "";
    QStringList lstExist;

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        lstSql.clear( );
        strText = ui->tabRecord->item( nRow, 0 )->text( );

        CLogicInterface::GetInterface( )->ExistCardNumber(strText, lstExist );
        if ( 0 < lstExist.count( ) ) {
            lstDuplication << lstExist;
            continue;
        }

        QList< QTableWidgetItem* > lstItems = tabWidget->findItems( strText, Qt::MatchFixedString );
        if ( 0 < lstItems.count( ) ) {
            lstDuplication << strText;
            continue;
        }

        tabWidget->insertRow( 0 );

        for ( int nCol = 0; nCol < ui->tabRecord->columnCount( ); nCol++ ) {
            switch ( nCol ) {
                case 0 :
                case 3 :
                    strText = ui->tabRecord->item( nRow, nCol )->text( );
                    lstSql  << ( strQuotation + strText + strQuotation );
                    AddItem( strText, 0, nCol, tabWidget );
                    break;

                case 1 :
                case 2 :
                case 4 :
                    pCB = ( QComboBox* ) ui->tabRecord->cellWidget( nRow, nCol );
                    strText = pCB->currentText( );
                    lstSql << ( strQuotation +strText + strQuotation );
                    AddItem( strText, 0, nCol, tabWidget );
                    break;
            }
        }

        lstTotalSql << ( "(" + lstSql.join( "," ) + " )" );
    }
}

void CDlgBulkRegister::ExecuteSql( QStringList &lstTotalSql )
{
    QString strSql = "";

    switch ( cardType ) {
    case CommonDataType::MonthlyCard :
        strSql = "REPLACE Into monthcard ( cardno, EnterMustCard, LeaveMustCard, MIMO, cardkind, starttime, endtime,cardstate, cardselfno, cardcomment, cardcreator ) Values ";
        break;

    case CommonDataType::ValueCard :
        strSql = "REPLACE Into savecard ( cardno, EnterMustCard, LeaveMustCard, cardkind, cardstate, cardfee, cardfeebz, cardselfno, cardcomment, cardcreator ) Values ";
        break;

    case CommonDataType::TimeCard :
        strSql = "REPLACE Into tmpcard ( cardno, cardkind, cardfeebz, cardselfno, cardstate ) Values ";
        break;
    }

    if ( !strSql.isEmpty( ) ) {
        strSql += lstTotalSql.join( "," );
        CLogicInterface::GetInterface( )->ExecuteSql( strSql );
        CCommonFunction::OperationSuccess( );
    }
}

void CDlgBulkRegister::on_lblClose_linkActivated(const QString &)
{
    close( );
}

void CDlgBulkRegister::on_btnSave_clicked()
{
    SaveData( );
    close( );
}

void CDlgBulkRegister::on_btnClose_clicked()
{
    if ( QMessageBox::Ok == CCommonFunction::MsgBox( NULL, "提示", "确定要放弃吗？", QMessageBox::Information ) ) {
        close( );
    }
}

void CDlgBulkRegister::on_chkID_clicked(bool checked)
{
    ui->spValue->setEnabled( checked );
    ui->spDigit->setEnabled( checked );
}

void CDlgBulkRegister::on_chkEnterCard_clicked()
{
    ChangeCheckBoxStatus( ( QCheckBox* ) sender( ) );
}

void CDlgBulkRegister::on_chkLeaveCard_clicked()
{
    ChangeCheckBoxStatus( ( QCheckBox* ) sender( ) );
}

void CDlgBulkRegister::on_chkMIO_clicked()
{
    ChangeCheckBoxStatus( ( QCheckBox* ) sender( ) );
}

void CDlgBulkRegister::ChangeCheckBoxStatus(QCheckBox *pChk)
{
    int nIndex = pChk->whatsThis( ).toInt( );

    for ( int nRow = 0; nRow < ui->tabRecord->rowCount( ); nRow++ ) {
        QTableWidgetItem* pItem = ui->tabRecord->item( nRow, nIndex );

        switch( pItem->checkState( ) )
        {
        case Qt::Checked :
            pItem->setCheckState( Qt::Unchecked );
            break;

        case Qt::Unchecked :
            pItem->setCheckState( Qt::Checked );
            break;
        }
    }
}
