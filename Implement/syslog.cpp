#include "Header/syslog.h"

#ifdef NewUI
    #include "ui_newsyslog.h"
#else
    #include "ui_syslog.h"
#endif

#include "Common/logicinterface.h"
#include "Common/commonfunction.h"

CSysLog::CSysLog(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(
        #ifdef NewUI
            new Ui::CONCAT_NEW_NAME( New , CSysLog )
        #else
            new Ui::CONCAT_NEW_NAME( , CSysLog )
        #endif
        )
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    //pParent->OperateTableWidget( ui->tableShift, CommonDataType::ShiftTable, CommonDataType::InitializeType );
    //pParent->OperateTableWidget( ui->tableCardMgm, CommonDataType::CardMgmTable, CommonDataType::InitializeType );
    //pParent->OperateTableWidget( ui->tablDeleteData, CommonDataType::DeleteDataTable, CommonDataType::InitializeType );
    //pParent->OperateTableWidget( ui->tableManualGate, CommonDataType::ManualGateTable, CommonDataType::InitializeType );
    //pParent->OperateTableWidget( ui->tableHardware, CommonDataType::HardwareTable, CommonDataType::InitializeType );

    hashScaleImage.insert( CommonDataType::BlobManualGate1, ui->lblImg0 );
    hashScaleImage.insert( CommonDataType::BlobManualGate2, ui->lblImg1 );
    hashScaleImage.insert( CommonDataType::BlobManualGate3, ui->lblImg2 );
    hashScaleImage.insert( CommonDataType::BlobManualGate4, ui->lblImg3 );

    QDateTime currentDt = QDateTime::currentDateTime( );
    ui->dtEnd->setDateTime( currentDt );
    currentDt = currentDt.addDays( - 7 );
    ui->dtStart->setDateTime( currentDt );

    ui->lblTitle->setText( windowTitle( ) );
    ControlDataGrid( );
    ui->tabWidget->setCurrentIndex( 1 );
    ui->tabWidget->setCurrentIndex( 0 );
}

CSysLog::~CSysLog()
{
    delete ui;
}

void CSysLog::ControlDataGrid( )
{
    QHeaderView* pHeader = ui->tableShift->horizontalHeader( );
    pHeader->resizeSection( 2, pHeader->sectionSize( 2 ) * 2 );

    pHeader = ui->tableCardMgm->horizontalHeader( );
    pHeader->resizeSection( 1, pHeader->sectionSize( 1 ) * 5 );
    pHeader->resizeSection( 2, pHeader->sectionSize( 2 ) * 2 );

    pHeader = ui->tableManualGate->horizontalHeader( );
    pHeader->resizeSection( 0, pHeader->sectionSize( 1 ) * 2 );
    pHeader->resizeSection( 1, pHeader->sectionSize( 1 ) * 5 );
    pHeader->resizeSection( 2, pHeader->sectionSize( 2 ) * 2 );
}

void CSysLog::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CSysLog::CalculatePos( )
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

void CSysLog::resizeEvent( QResizeEvent* )
{
    CalculatePos( );
}

void CSysLog::on_tabWidget_currentChanged(int index)
{
    QStringList lstRows;
    QString strWhere = "";
    CommonDataType::SysLogType logType = CommonDataType::ShiftLog;
    QTableWidget* pTable = NULL;
    strWhere = " Where infokind = ";

    switch ( index ) {
    case 0 :
        logType = CommonDataType::ShiftLog;
        strWhere += "'换班记录'";
        pTable = ui->tableShift;
        break;

    case 1 :
        logType = CommonDataType::CardMgmLog;
        pTable = ui->tableCardMgm;
        strWhere += "'卡片管理'";
        break;

    case 2 :
        logType = CommonDataType::DeleteDBLog;
        pTable = ui->tablDeleteData;
        strWhere += "'删除数据库'";
        break;

    case 3 :
        logType = CommonDataType::ManualGateLog;
        pTable = ui->tableManualGate;
        strWhere += "'手动开关闸'";
        break;

    case 4 :
        logType = CommonDataType::HardwareInfoLog;
        pTable = ui->tableHardware;
        strWhere += "'硬件信息警告信息'";
        break;
    }

    QString strEnd;
    QString strStart;

    QDateTime dateTime = ui->dtStart->dateTime( );
    CCommonFunction::DateTime2String( dateTime, strStart);

    dateTime = ui->dtEnd->dateTime( );
    CCommonFunction::DateTime2String( dateTime, strEnd );

    strWhere += " And infotime between '" + strStart + "' and '" + strEnd + "'";

    int nRet = CLogicInterface::GetInterface( )->OperateSysLogInfo( lstRows, logType, CommonDataType::SelectData, strWhere );
    //pTable->clearContents( );

    CCommonFunction::FreeAllRows( pTable );
    CCommonFunction::FillTable( pTable, nRet, lstRows );

    ClearImage( );
}

void CSysLog::on_btnMinimalize_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CSysLog::on_lblClose_linkActivated(QString )
{
    close( );
}

void CSysLog::GetImage( CommonDataType::BlobType blob, int nRow )
{

    QString strWhere = QString( " where infooperator = '%1' and infokind = '%2' and infotext = '%3' and infotime = '%4'" ).arg(
                                                        ui->tableManualGate->item( nRow, 0 )->text( ),
                                                        "手动开关闸",
                                                        ui->tableManualGate->item( nRow, 1 )->text( ),
                                                        ui->tableManualGate->item( nRow, 2 )->text( ) );
    QLabel* pLbl = hashScaleImage.value( blob );

    CCommonFunction::LoadFourImages( blob, strWhere, *pLbl );
}

void CSysLog::ClearImage( )
{
    QPixmap map;
    foreach( QLabel* pLbl, hashScaleImage.values( ) ) {
        pLbl->setPixmap( map );
    }
}

void CSysLog::on_tableManualGate_cellClicked(int row, int column)
{
    ClearImage( );

    for ( int nIndex = CommonDataType::BlobManualGate1; nIndex <= CommonDataType::BlobManualGate4; nIndex++ ) {
        GetImage( ( CommonDataType::BlobType ) nIndex, row );
    }
}

void CSysLog::on_btnQuery_clicked()
{
    on_tabWidget_currentChanged( ui->tabWidget->currentIndex( ) );
}
