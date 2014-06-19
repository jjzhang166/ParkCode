#include "Header/publishledinfo.h"
#include "ui_publishledinfo.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"
#include "Network/parkintranet.h"
#include "SerialPort/processdata.h"

CPublishLEDInfo::CPublishLEDInfo( bool bLocalhost, QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CPublishLEDInfo)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    bLocal = bLocalhost;
    CCommonFunction::ConnectCloseButton( ui->lblClose );
}

CPublishLEDInfo::~CPublishLEDInfo()
{
    delete ui;
}

void CPublishLEDInfo::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CPublishLEDInfo::resizeEvent( QResizeEvent* )
{
    //FillTable( );
    CalculatePos( );
}

void CPublishLEDInfo::FillTable( )
{
    CCommonFunction::FreeAllRows( ui->tableWidget );

    QStringList lstData;
    QString strWhere = QString( " Where video1ip = '%1' " ).arg( CCommonFunction::GetHostIP( ) );
    QString strSql = QString( "Select distinct shebeiname, shebeiadr, video1ip from \
                              roadconerinfo %1 order by video1ip, shebeiadr" ).arg(
                                      bLocal ? strWhere : "" );
    int nRows = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData );

    int nCols = 3;
    ui->tableWidget->setRowCount( nRows );

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        for ( int nCol = 0; nCol < nCols; nCol++ ) {
            QTableWidgetItem* pItem = new QTableWidgetItem( lstData[ nRow * nCols + nCol ]);
            ui->tableWidget->setItem( nRow, nCol, pItem );
            pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
        }

        QTableWidgetItem* pItem = new QTableWidgetItem( );
        pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable );
        ui->tableWidget->setItem( nRow, nCols, pItem );
        pItem->setCheckState( Qt::Checked );
    }
}

void CPublishLEDInfo::CalculatePos( )
{
#ifdef NewUI
    move( 123, 46 );
#else
    move( 123, 177 );
#endif
}

void CPublishLEDInfo::on_btnDownload_clicked( )
{
    QStringList lstData;


    for ( int nIndex = 0; nIndex < ui->tableWidget->rowCount( ); nIndex++ ) {
        if ( Qt::Checked == ui->tableWidget->item( nIndex, 3 )->checkState( ) ) {
            lstData << ui->tableWidget->item( nIndex, 2 )->text( )   // IP
                    << ui->edtLedInfo->toPlainText( )                // Info
                    << ui->tableWidget->item( nIndex, 1 )->text( );  // Can
        }
    }

    CNetwork::Singleton( ).BroadcastDatagram( CommonDataType::DGPublishLed, lstData );
}

void CPublishLEDInfo::on_btnClose_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CPublishLEDInfo::SelectAllCards( QTableWidget* pTable, bool bAll )
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

void CPublishLEDInfo::showEvent(QShowEvent *)
{
    FillTable( );
}

void CPublishLEDInfo::on_btnSelectAll_clicked()
{
    SelectAllCards( ui->tableWidget, true );
}

void CPublishLEDInfo::on_btnUnselectAll_clicked()
{
    SelectAllCards( ui->tableWidget, false );
}

void CPublishLEDInfo::on_btnDownloadTime_clicked()
{
    QStringList lstData;
    QDate date = QDate::currentDate( );
    QTime time = QTime::currentTime( );
    QString strInfo;

    CCommonFunction::Date2String( date, strInfo );
    lstData << strInfo;
    CCommonFunction::Time2String( time, strInfo );
    lstData << strInfo;

    for ( int nIndex = 0; nIndex < ui->tableWidget->rowCount( ); nIndex++ ) {
        if ( Qt::Checked == ui->tableWidget->item( nIndex, 3 )->checkState( ) ) {
            char cCan =  ( char ) ui->tableWidget->item( nIndex, 1 )->text( ).toShort( );  // Can
            CProcessData* pProcessor = CProcessData::GetProcessor( );
            if ( NULL != pProcessor ) {
                pProcessor->ProcessUserRequest( CommonDataType::UserPublishLed, cCan, lstData );
            }
        }
    }
}

void CPublishLEDInfo::on_lblClose_linkActivated(QString)
{
    close( );
}
