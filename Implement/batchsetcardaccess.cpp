#include "Header/batchsetcardaccess.h"

#ifdef NewUI
    #include "ui_newbatchsetcardaccess.h"
#else
    #include "ui_batchsetcardaccess.h"
#endif

#include "Common/commonfunction.h"
#include "Common/logicinterface.h"
#include "Dialog/dlgreadcardid.h"

CBatchSetCardAccess::CBatchSetCardAccess(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(
        #ifdef NewUI
            new Ui::CONCAT_NEW_NAME( New , CBatchSetCardAccess )
        #else
            new Ui::CONCAT_NEW_NAME( , CBatchSetCardAccess )
        #endif
        )
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    ui->lblTitle->setText( windowTitle( ) );
    ui->tableBatchChannel->hideColumn( 1 );
    CCommonFunction::ConnectCloseButton( ui->lblClose );
}

CBatchSetCardAccess::~CBatchSetCardAccess()
{
    delete ui;
}

void CBatchSetCardAccess::SelectAllCards( QTableWidget* pTable, bool bAll )
{
    if ( false == pTable->isVisible( ) ) {
        return;
    }

    int nRows = pTable->rowCount( );
    int nCol = pTable->columnCount( ) - 1;

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        pTable->item( nRow, nCol )->setCheckState( bAll ? Qt::Checked : Qt::Unchecked );
    }
}

void CBatchSetCardAccess::SelectTable( bool bAll )
{
    SelectAllCards( ui->tableBatchMonth, bAll );
    SelectAllCards( ui->tableBatchTime, bAll );
    SelectAllCards( ui->tableBatchValue, bAll );
}

void CBatchSetCardAccess::SetTimeValue( bool bAllTime )
{
    ui->timeStart->setTime( QTime( 0, 0, 0 ) );
    ui->timeEnd->setTime( bAllTime ? QTime( 23, 59, 59 ) : QTime( 0, 0, 0 ) );
}

void CBatchSetCardAccess::on_btnAllSecleted_clicked( )
{
    SelectTable( true );
}

void CBatchSetCardAccess::on_btnAllUnselected_clicked( )
{
   SelectTable( false );
}

void CBatchSetCardAccess::FillTable( QTableWidget* table, QString& strSql, int nCols )
{
    CCommonFunction::FreeAllRows( table );

    QStringList lstData;
    int nRows = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData );

    table->setRowCount( nRows );

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        for ( int nCol = 0; nCol < nCols; nCol++ ) {
            QTableWidgetItem* pItem = new QTableWidgetItem( lstData[ nRow * nCols + nCol ]);
            table->setItem( nRow, nCol, pItem );
            pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
        }

        QTableWidgetItem* pItem = new QTableWidgetItem( );
        pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable );
        table->setItem( nRow, nCols, pItem );
        pItem->setCheckState( Qt::Unchecked );
    }
}

void CBatchSetCardAccess::GetData( QStringList &lstData, QTableWidget &table )
{
    QString strStartTime;
    QString strEndTime;
    QString strCardno;
    QTime tStart = ui->timeStart->time( );
    QTime tEnd = ui->timeEnd->time( );
    CCommonFunction::Time2String( tStart, strStartTime );
    CCommonFunction::Time2String( tEnd, strEndTime );
    QString strDelete = QString( "Delete From cardright Where cardno in ( %1 )" );
    QString strTmp;

    int nChannel = ui->tableBatchChannel->rowCount( );
    int nTable = table.rowCount( );
    int nInsert = 0;
    QStringList lstSql;
    QStringList lstSqlTotal;
    QStringList lstWhere;
    QString strSeperator = ",";
    QString strQuotation = "'";

    for ( int nIndex = 0; nIndex < nTable; nIndex++ ) {
        if ( Qt::Checked == table.item( nIndex, 3 )->checkState( ) ) { // ²Ù×÷ÓÐÐ§
            strCardno = table.item( nIndex, 0 )->text( );
            lstWhere << strQuotation + strCardno + strQuotation;

            for ( int nChan = 0; nChan < nChannel; nChan++ ) {
                if ( Qt::Checked == ui->tableBatchChannel->item( nChan, 2 )->checkState( ) ) {
                    lstData << strQuotation + strCardno + strQuotation
                            << strQuotation + ui->tableBatchChannel->item( nChan, 0 )->text( ) + strQuotation
                            << strQuotation + strStartTime + strQuotation
                            << strQuotation + strEndTime + strQuotation
                            << ui->tableBatchChannel->item( nChan, 1 )->text( );

                    lstSql << ( "(" + lstData.join( strSeperator ) + ")" );
                    lstData.clear( );

                    if ( 500 == ++nInsert ) {
                        nInsert = 0;
                        lstSqlTotal << lstSql.join( strSeperator );
                        lstSql.clear( );
                    }
                }
            }
        }
    }

    if ( 0 != lstSql.count( ) ) {
        lstSqlTotal << lstSql.join( strSeperator );
    }

    strTmp = strDelete.arg( lstWhere.join( strSeperator ) );
    CLogicInterface::GetInterface( )->ExecuteSql( strTmp );

    // Table Expression / Row Expression
    QString strSql = QString( "Insert Into cardright( cardno, shebeiname, starttime, endtime, roadconind ) Values %1" );

    int nTotal = lstSqlTotal.count( );
    for ( int nIndex = 0; nIndex < nTotal; nIndex++ ) {
        strTmp = strSql.arg( lstSqlTotal.at( nIndex ) );
        CLogicInterface::GetInterface( )->ExecuteSql( strTmp );
    }
}

void CBatchSetCardAccess::on_btnOk_clicked( )
{
    QStringList lstData;
    //QString strWhereDelete = "";

    switch  ( ui->tableWidget->currentIndex( ) ) {
    case 0 :
        GetData( lstData, *ui->tableBatchMonth );
        break;

    case 1 :
        GetData( lstData, *ui->tableBatchTime );
        break;

    case 2 :
        GetData( lstData, *ui->tableBatchValue );
        break;
    }

    //CLogicInterface::GetInterface( )->OperateBatchCardInfo( lstData, CommonDataType::InsertData, strWhereDelete );

    CCommonFunction::OperationSuccess( );
}

void CBatchSetCardAccess::on_btnAllTime_clicked( )
{
    SetTimeValue( true );
}

void CBatchSetCardAccess::on_btnForbidden_clicked( )
{
    SetTimeValue( false );
}

void CBatchSetCardAccess::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CBatchSetCardAccess::DisplayData( int nIndex, QString& strWhere )
{
#if false
    QString strSql = "select a.cardno, a.cardselfno, b.username, \
                     c.carcp from %1 a, userinfo b, carinfo c \
                     where a.cardno = b.cardindex and a.cardno = c.cardindex";
#endif
    QString strSql = "select a.cardno, a.cardselfno, b.username \
                     from %1 a, userinfo b\
                     where a.cardno = b.cardindex";

    int nCols = 3;

    QString strTmp;

    switch ( nIndex ) {
    case 0 :
        strTmp = strSql.arg( "monthcard" ) + strWhere;
        FillTable( ui->tableBatchMonth, strTmp, nCols );
        break;

    case 1:
        strTmp = "Select cardno, cardselfno,'' from tmpcard " + strWhere;
        FillTable( ui->tableBatchTime, strTmp, nCols );
        break;

    case 2 :
        strTmp = strSql.arg( "savecard" ) + strWhere;
        FillTable( ui->tableBatchValue, strTmp, nCols );
        break;
    }

    strTmp = "SELECT distinct shebeiname, shebeiid from roadconerinfo";
    nCols = 2;
    FillTable( ui->tableBatchChannel, strTmp, nCols );
}

void CBatchSetCardAccess::resizeEvent( QResizeEvent* )
{
    //DisplayData( 0 );
    CalculatePos( );
}

void CBatchSetCardAccess::showEvent(QShowEvent *)
{
    //DisplayData( 0 );
}

void CBatchSetCardAccess::CalculatePos( )
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

void CBatchSetCardAccess::on_btnMinimalize_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CBatchSetCardAccess::on_tableWidget_currentChanged(int index)
{
    //DisplayData( index );
}

void CBatchSetCardAccess::on_lblClose_linkActivated(QString)
{
    close( );
}

void CBatchSetCardAccess::on_btnAllSecleted_2_clicked()
{
    SelectAllCards( ui->tableBatchChannel, true );
}

void CBatchSetCardAccess::on_btnAllUnselected_2_clicked()
{
    SelectAllCards( ui->tableBatchChannel, false );
}

void CBatchSetCardAccess::on_btnSerach_clicked()
{
    CDlgReadCardID dlg;
    pParent->SetCardControl( dlg.GetEditCntrl(  ) );
    int nRet = dlg.exec( );
    pParent->SetCardControl( NULL );

    if ( QDialog::Accepted == nRet ) {
        QStringList& lstCardNo = dlg.GetCardNoLst( );
        QString strWhere = "";

        int nIndex = ui->tableWidget->currentIndex( );

        if ( 0 < lstCardNo.count( ) ) {
            strWhere = ( ( 1== nIndex ) ? QString( " where " ) : QString( " and " ) )  + " cardno in ( " + lstCardNo.join( "," ) + " ) ";
        }

        DisplayData( nIndex, strWhere );
    }
}
