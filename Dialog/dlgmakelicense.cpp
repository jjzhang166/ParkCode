#include "dlgmakelicense.h"
#include "ui_dlgmakelicense.h"
#include <QFileDialog>
#include "dlgparkdongleinfo.h"

CDlgMakeLicense::CDlgMakeLicense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgMakeLicense)
{
    ui->setupUi(this);
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    ui->lblTitle->setText( windowTitle( ) );
    setWindowFlags( Qt::FramelessWindowHint );

    pProcess = new CProcessCpuid( ui->tableWidget, this );
    FillParkID( );
    connect( pProcess, SIGNAL( ParkIDChanged( QString& ) ), this, SLOT( ParkIDChanged( QString& ) ) );

    QHeaderView* pHeader = ui->tableWidget->horizontalHeader( );
    pHeader->resizeSection( 0, pHeader->sectionSize( 0 ) + 80 );
    pHeader->resizeSection( 1, pHeader->sectionSize( 1 ) + 20 );
    pHeader->resizeSection( 2, pHeader->sectionSize( 2 ) + 20 );
    pHeader->resizeSection( 3, pHeader->sectionSize( 3 ) + 20 );
    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CDlgMakeLicense::~CDlgMakeLicense()
{
    delete pProcess;
    delete ui;
}

void CDlgMakeLicense::ControlCBXEvent( bool bConnect )
{
    bConnect ? connect( ui->cbxCode, SIGNAL( currentIndexChanged( int ) ), this, SLOT( CbxIndexChanged( int ) ) ) :
               disconnect( ui->cbxCode, SIGNAL( currentIndexChanged( int ) ), this, SLOT( CbxIndexChanged( int ) ) );
}

void CDlgMakeLicense::ParkIDChanged( QString &strParkID )
{
    ControlCBXEvent( false );
    int nIndex = ui->cbxCode->findData( strParkID );
    ui->cbxCode->setCurrentIndex( nIndex );
    ControlCBXEvent( true );
}

void CDlgMakeLicense::resizeEvent( QResizeEvent * event )
{
    QWidget::resizeEvent( event );

    QString strFile = statusTip( );
    QPixmap bgimage( strFile );
    QPalette pal( palette( ) );
    pal.setBrush( QPalette::Window, QBrush( bgimage.scaled( event->size( ),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation ) ) );
    setPalette( pal );
}

void CDlgMakeLicense::on_btnPSN_clicked()
{
    pProcess->CpuidRequest( );
}

void CDlgMakeLicense::FillParkID( )
{
    ControlCBXEvent( false );

    ui->cbxCode->clear( );

    QString strSql = QString( "select distinct AdministrativeID, BriefName, AES_DECRYPT( DongleHID, '%1' ) from ParkDongleInfo" ).arg( KEY_GUID );
    QStringList lstRow;

    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRow );
    int nField = 0;
    int nCols = 3;

    for ( int nIndex = 0; nIndex < lstRow.count( ) / nCols; nIndex++ ) {
        nField = nIndex * nCols;
        ui->cbxCode->insertItem( nIndex, lstRow[ nField + 1 ], lstRow[ nField ] );
        ui->cbxCode->setItemData( nIndex, lstRow[ nField + 2 ], Qt::ToolTipRole );
    }

    ControlCBXEvent( true );

    if ( 0 < lstRow.count( ) ) {
        ui->cbxCode->setCurrentIndex( -1 );
        ui->cbxCode->setCurrentIndex( 0 );
    }
}

bool CDlgMakeLicense::GetCode( QString &strCode )
{
    bool bRet = true;
    strCode = ui->cbxCode->itemData( ui->cbxCode->currentIndex( ) ).toString( );

    if ( strCode.isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, "提示", "请输入停车场编码！", QMessageBox::Information );
        bRet = false;
    }

    return bRet;
}

void CDlgMakeLicense::on_btnSave_clicked()
{
    QString strCode;
    if ( !GetCode( strCode ) ) {
        return;
    }

    pProcess->SaveData( strCode );
}

void CDlgMakeLicense::on_btnClose_clicked()
{
    close( );
}

void CDlgMakeLicense::on_btnData_clicked()
{
    QString strCode;
    if ( !GetCode( strCode ) ) {
        return;
    }

    pProcess->GetData( strCode );
}

void CDlgMakeLicense::CbxIndexChanged( int nIndex )
{
    if ( -1 == nIndex ) {
        return;
    }
    on_btnData_clicked( );
}

void CDlgMakeLicense::on_btnAdd_clicked()
{
    QStringList lstRow;
    QDate curDate = QDate::currentDate( );
    QDate nxtDate = curDate.addYears( 1 );
    QString strStart;
    QString strEnd;

    CCommonFunction::Date2String( curDate, strStart);
    CCommonFunction::Date2String( nxtDate, strEnd );
    QString strParkID;
    GetCode( strParkID );

    lstRow << "" << "" << strStart << strEnd << strParkID;

    pProcess->AddRow( lstRow );
}

void CDlgMakeLicense::on_btnDelete_clicked()
{
    int nRow = ui->tableWidget->currentRow( );

    if ( -1 == nRow ) {
        CCommonFunction::MsgBox( NULL, "提示", "请选择行。", QMessageBox::Information );
        return;
    }

    ui->tableWidget->removeRow( nRow );

    if ( ui->tableWidget->rowCount( ) > 0 ) {
        ui->tableWidget->selectRow( 0 );
    }
}

void CDlgMakeLicense::ExpImpData( bool bImport )
{
    QString strFile = bImport ? QFileDialog::getOpenFileName( this ) : QFileDialog::getSaveFileName( this );

    if ( strFile.isEmpty( ) ) {
        return;
    }

    QString strParkID;
    GetCode( strParkID );

    bool bRet = bImport ? pProcess->ImportData( strFile ) : pProcess->ExportData( strFile, strParkID );
    QString strMsg = QString( "%1授权数据%2！" ).arg( bImport ? "导入" : "导出", bRet ? "成功" : "失败" );
    CCommonFunction::MsgBox( NULL, "提示", strMsg, QMessageBox::Information );
}

void CDlgMakeLicense::on_btnExport_clicked()
{
    ExpImpData( false );
}

void CDlgMakeLicense::on_btnImport_clicked()
{
    ExpImpData( true );
}

void CDlgMakeLicense::on_btnBatch_clicked()
{
    int nCurIndex = ui->cbxCode->currentIndex( );
    CDlgParkDongleInfo dlg( pProcess );
    dlg.exec( );
    FillParkID( );
    ui->cbxCode->setCurrentIndex( nCurIndex );
}

void CDlgMakeLicense::on_lblClose_linkActivated(const QString &)
{
    close( );
}
