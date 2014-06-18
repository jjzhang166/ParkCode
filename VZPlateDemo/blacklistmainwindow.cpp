#include "blacklistmainwindow.h"
#include "ui_blacklistmainwindow.h"
#include <QDir>
#include <QFileDialog>
#include "cdlgblacklist.h"
#include "cdlgconfig.h"

BlacklistMainWindow::BlacklistMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BlacklistMainWindow)
{
    ui->setupUi(this);
    Initialize( );
}

void BlacklistMainWindow::Initialize( )
{
    connect( QPlateThread::GetInstance( ), SIGNAL( PlateResult( QStringList, int, bool, bool ) ),
             this, SLOT( HandlePlateResult( QStringList, int, bool, bool ) ) );

    QPlateThread::GetInstance( )->PostPlateInitEvent( ImageFormatBGR, 0 );
    LoadLogoTitle( );

    CConfigurator::CreateInstance( )->ReadBlacklistPlate( lstBlacklistPlates );

    QHeaderView* pView = ui->tableAlert->horizontalHeader( );

    int nIndex = 1;
    pView->resizeSection( nIndex, pView->sectionSize( nIndex ) * 2 );

    nIndex = 3;
    pView->hideSection( nIndex);
}

BlacklistMainWindow::~BlacklistMainWindow()
{
    delete ui;
}

void BlacklistMainWindow::HandlePlateResult( QStringList lstResult, int nChannel, bool bSuccess, bool bVideo )
{
    int nCount = lstResult.count( );
    if ( 8 != nCount ) {
        return;
    }

    const QString& strPlate = lstResult.at( 0 );
    const QString& strFile = lstResult.at( nCount -1 );
    CheckBlacklistPlate( strPlate, strFile );
}

void BlacklistMainWindow::AddItem( QTableWidget* pTable, int nRow, int nCol, const QString &strText )
{
    QTableWidgetItem* pItem = new QTableWidgetItem( strText );
    pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    pTable->setItem( nRow, nCol, pItem );
}

void BlacklistMainWindow::CheckBlacklistPlate( const QString &strPlate, const QString& strFile )
{
    bool bContained = lstBlacklistPlates.contains( strPlate );
    if ( !bContained ) {
        return;
    }

    int nRow = 0;
    QString strDateTime;
    QCommon::GetCurrentDateTime( strDateTime );
    QString strReason = "黑名单车";

    ui->tableAlert->insertRow( nRow );

    AddItem( ui->tableAlert, nRow, 0, strPlate );
    AddItem( ui->tableAlert, nRow, 1, strDateTime );
    AddItem( ui->tableAlert, nRow, 2, strReason );
    AddItem( ui->tableAlert, nRow, 3, strFile );

    QCommon::PlayMusic( strReason, false );
}

void BlacklistMainWindow::LoadLogoTitle( )
{
    QString strPath;
    QString strNameFilter = "logo_*.*";
    QDir dir( strPath, strNameFilter, QDir::Unsorted, QDir::NoDotAndDotDot | QDir::Files );

    QFileInfoList lstFiles = dir.entryInfoList( );

    if ( 0 == lstFiles.count( ) ) {
        return;
    }

    const QFileInfo& fileInfo = lstFiles.at( 0 );
    QString strFile = fileInfo.absoluteFilePath( );

    QIcon winIcon( strFile );
    setWindowIcon( winIcon );

    //QPixmap lblPic( strFile );
    //ui->lblPicture->setPixmap( lblPic );

    QString strSuffix = "." + fileInfo.suffix( ).toLower( );
    strSuffix = fileInfo.baseName( ).toLower( ).remove( "logo_" ).remove( strSuffix );
    setWindowTitle( strSuffix );
}

QString BlacklistMainWindow::GetSelectedFile( )
{
    return QFileDialog::getOpenFileName( this, "选择要识别的文件", qApp->applicationDirPath( ),
                                                    "Image Files (*.BMP *.JPG *.JPEG *.PNG *.TIF);;All Files(*.*)" );
}

void BlacklistMainWindow::ButtonEnable( bool bPreEnable, bool bNextEnable )
{
    ui->btnPreFile->setEnabled( bPreEnable );
    ui->btnNextFile->setEnabled( bNextEnable );
}

void BlacklistMainWindow::LoadPicture( const QString &strImage )
{
    QPixmap objPixmap( strImage );
    ui->lblVideo->setPixmap( objPixmap );
}

void BlacklistMainWindow::on_btnSingleFile_clicked()
{
    QString strFile = GetSelectedFile( );

    if ( strFile.isEmpty( ) ) {
        return;
    }

    ButtonEnable( false, false );
    nFileIndex = 0;

    QDir dir( strFile );
    dir.cdUp( );

    QStringList lstFilter;
    lstFilter << "*.BMP" << "*.JPG" << "*.JPEG" << "*.PNG" << "*.TIF";
    dir.setNameFilters( lstFilter );

    lstFiles = dir.entryInfoList( );
    int nCount = lstFiles.count( );
    if ( 0 == nCount ) {
        return;
    } else if ( 1 < nCount ) {
        ButtonEnable( false, true );
    }

    QPlateThread::GetInstance( )->PostPlateFileRecognize( strFile, 0 );
    LoadPicture( strFile );
}

void BlacklistMainWindow::SingleFileRecognize( bool bPreFile )
{
    int nCount = lstFiles.count( ) - 1;

    if ( bPreFile ) {
        if ( 0 < nFileIndex ) {
            nFileIndex--;
        }

        ButtonEnable( 0 != nFileIndex, true );
    } else {
        if ( nCount > nFileIndex ) {
            nFileIndex++;
        }

        ButtonEnable( true, nCount != nFileIndex );
    }

    QString strFile = lstFiles.at( nFileIndex ).absoluteFilePath( );
    QPlateThread::GetInstance( )->PostPlateFileRecognize( strFile, 0 );
    LoadPicture( strFile );
}

void BlacklistMainWindow::on_btnPreFile_clicked()
{
    SingleFileRecognize( true );
}

void BlacklistMainWindow::on_btnNextFile_clicked()
{
    SingleFileRecognize( false );
}

void BlacklistMainWindow::on_actBlacklist_triggered()
{
    CDlgBlacklist dlg( this );
    dlg.exec( );
}

void BlacklistMainWindow::on_tableAlert_cellClicked(int row, int column)
{
    if ( 0 != column ) {
        return;
    }

    QString strFile = ui->tableAlert->item( row, ui->tableAlert->columnCount( ) - 1 )->text( );
    LoadPicture( strFile );
}

void BlacklistMainWindow::on_actParameter_triggered()
{
    CDlgConfig dlg( this );
    dlg.exec( );
}
