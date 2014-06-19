#include "Header/reewalrecords.h"

#ifdef NewUI
    #include "ui_newreewalrecords.h"
#else
    #include "ui_reewalrecords.h"
#endif

#include "Common/commonfunction.h"
#include "Common/logicinterface.h"

CRenewalRecords::CRenewalRecords(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(
        #ifdef NewUI
            new Ui::CONCAT_NEW_NAME( New , CRenewalRecords )
        #else
            new Ui::CONCAT_NEW_NAME( , CRenewalRecords )
        #endif
        )
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );

    //pParent->OperateTableWidget( ui->tableRenewalRecord, CommonDataType::RenewalRecordTable, CommonDataType::InitializeType );
    ui->lblTitle->setText( windowTitle( ) );
    ControlDataGrid( );
}

CRenewalRecords::~CRenewalRecords()
{
    delete ui;
}

void CRenewalRecords::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CRenewalRecords::ControlDataGrid( )
{
    int nIndex = 0;
    QHeaderView* pHeader = ui->tableRenewalRecord->horizontalHeader( );
    nIndex = 0;
    pHeader->resizeSection( nIndex, pHeader->sectionSize( nIndex ) * 2 );
}

void CRenewalRecords::CalculatePos( )
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

void CRenewalRecords::FillTable( )
{
    CCommonFunction::FreeAllRows( ui->tableRenewalRecord );

    QStringList lstData;
    QString strWhere = "";
    int nCols = 11;
    int nRows = CLogicInterface::GetInterface( )->OperateRechargeInfo( lstData, CommonDataType::SelectData, strWhere );

    ui->tableRenewalRecord->setRowCount( nRows );

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        for ( int nCol = 0; nCol < nCols; nCol++ ) {
            QTableWidgetItem* pItem = new QTableWidgetItem( lstData[ nRow * nCols + nCol ]);
            ui->tableRenewalRecord->setItem( nRow, nCol, pItem );
            pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
        }
    }
}

void CRenewalRecords::showEvent(QShowEvent *)
{
    FillTable( );
}

void CRenewalRecords::resizeEvent( QResizeEvent* )
{
    //FillTable( );
    CalculatePos( );
}

void CRenewalRecords::on_btnMinimalize_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CRenewalRecords::on_lblClose_linkActivated(QString)
{
    close( );
}
