#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Dialog/recognizeparamdlg.h"
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <qtconcurrentexception.h>
#include "mythread.h"


static quint8 imgData[2][ 1024 * 1024 * 2 ] = { 0  };
static TH_PlateResult result[2][ 6 ] = { 0 };
//static TH_PlateIDResult result[ 1 ] = { 0 };

static int nResult = 6;
QString strPlate = "";
bool bStartRecognization[2] = { false };
MainWindow* pMainWnd1 = NULL;

static bool bCard = false;

void FuncEncDataCallback(int nChannel, PUCHAR pData, UINT nBuffLen, int nFrameType, BOOL bMov)
{

}

void FuncRawDataCallback(int nChannel, PUCHAR pRawBuffer, DWORD dwVideo,DWORD dwHD1)
{

}

void MainWindow::ImageStreamCallback( UINT nChannel, PVOID pContent )
{
    if ( false == bStartRecognization[nChannel] ) {
        return;
    }

    MainWindow* pMainWnd = ( MainWindow* ) pContent;
    quint8* p = imgData[nChannel];
    nResult = 6;
    bool bRet = pMainWnd->GetPlateRecognization( )->RecognizeVideo( imgData[nChannel], 704, 576, result[nChannel], nResult );

    //QByteArray byData( ( const char* ) imgData );
    //QString strHex( byData.toHex( ) );

    if ( 0 < nResult ) {
        //qDebug( ) << "ImageStreamCallback " << bRet << " " << strHex << endl;
        //qDebug( ) << "Plate : " << result[ 0 ].nDirection;
        //qDebug( ) << " : " << result[ 0 ].license << endl;
        QString strFile = "";
        pMainWnd->InsertPlate( nChannel, bRet, strFile );
    }
}

void CALLBACK MyPrcCbMotionDetect( long lnCardID, BOOL bMove, LPVOID lpContext  )
{
    //bStartRecognization = bMove;
    qDebug( ) << "MyPrcCbMotionDetect " << endl;
}

void CALLBACK PrcPicMessage( long lnCardID, long pBuf, long lnWidth, long lnHeight )
{
    nResult = 6;
    //memcpy( imgData, ( const void* ) pBuf, lnWidth * lnHeight * lnBiCount );
    bool bRet;// = pMainWnd1->GetPlateRecognization( )->RecognizeVideo( ( quint8* ) pBuf, lnWidth, lnHeight, result, nResult );

    //QByteArray byData( ( const char* ) imgData );
    //QString strHex( byData.toHex( ) );

    if ( 0 < nResult ) {
        //qDebug( ) << "ImageStreamCallback " << bRet << " " << strHex << endl;
        //qDebug( ) << "Plate : " << result[ 0 ].nDirection;
        //qDebug( ) << " : " << result[ 0 ].license << endl;
        QString strFile = "";
        pMainWnd1->InsertPlate( 0, bRet, strFile );
    }
}


void CALLBACK PrcCapSourceStream( long lnCardID, long pBuf, long lnWidth, long lnHeight, long lnBiCount )
{
    if ( false == bStartRecognization ) {
        return;
    }

    qDebug( ) << "ImageStreamCallback " << endl;


    nResult = 6;
    //memcpy( imgData, ( const void* ) pBuf, lnWidth * lnHeight * lnBiCount );
    bool bRet;// = pMainWnd1->GetPlateRecognization( )->RecognizeVideo( ( quint8* ) pBuf, lnWidth, lnHeight, result, nResult );

    //QByteArray byData( ( const char* ) imgData );
    //QString strHex( byData.toHex( ) );

    if ( 0 < nResult ) {
        //qDebug( ) << "ImageStreamCallback " << bRet << " " << strHex << endl;
        //qDebug( ) << "Plate : " << result[ 0 ].nDirection;
        //qDebug( ) << " : " << result[ 0 ].license << endl;
        QString strFile = "";
        pMainWnd1->InsertPlate( 0,bRet, strFile );
    }
}

void MotionDetection( ULONG channelNumber, BOOL bMotionDetected, void *context )
{
    bStartRecognization[channelNumber] = bMotionDetected;
    //qDebug( ) << "MotionDetection : " << bMotionDetected << endl;
}

CVehicleLicense* MainWindow::GetPlateRecognization( )
{
    return pVehicle;
}

void MainWindow::Recognize( quint8* pData, ULONG& lSize )
{
    nResult = 6;
    //memcpy( imgData, ( const void* ) pBuf, lnWidth * lnHeight * lnBiCount );
    pMultimedia->GetYuv422Data( 0, pData, lSize );
    bool bRet;// = pVehicle->RecognizeVideo( ( quint8* ) pData, 352, 288, result, nResult );

    //QByteArray byData( ( const char* ) imgData );
    //QString strHex( byData.toHex( ) );

    if ( 0 < nResult ) {
        //qDebug( ) << "ImageStreamCallback " << bRet << " " << strHex << endl;
        //qDebug( ) << "Plate : " << result[ 0 ].nDirection;
        //qDebug( ) << " : " << result[ 0 ].license << endl;
        QString strFile = "";
        InsertPlate(0,bRet, strFile );
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pMainWnd1 = this;

    pMultimedia = CMultimedia::CreateInstance( CMultimedia::JvsSDK );//bCard ? CMultimedia::TmSDK : CMultimedia::HikSdk );
    pVehicle = CVehicleLicense::CreateInstance( CVehicleLicense::WinToneSdk );
    hChannel[ 0 ] = INVALID_HANDLE;

    pMultimedia->SystemStartup( winId( ) );
    //on_btnOpenVideo_clicked( );

    bStartVideo = false;
    pMultimedia->RegisterStreamCB( bCard ? ( HK_STREAM_CB ) PrcCapSourceStream : ImageStreamCallback, this );

    //static CMyThread th( this );
    //th.start( );
}

bool MainWindow::Init(int nFormat)
{
    if ( bStartVideo ) {
        //CCommonFunction::MsgBox( this, "提示", "请停止视频！", QMessageBox::Information );
        return false;
    }

    QStringList lstParam;
    lstParam << QString::number( nFormat ) << "0";
    pVehicle->RecognizedImageFormat( lstParam );
    bool bRet = pVehicle->Initialize( 0 );
    //bRet = pVehicle->Initialize( 1 );

    lstParam.clear( );
    lstParam << QString::number( nFormat ) << "1";
    pVehicle->RecognizedImageFormat( lstParam );
    bRet = pVehicle->Initialize( 1 );

    if ( false == bRet ) {
        //CCommonFunction::MsgBox( this, "提示", "请检查车牌识别加密狗是否插好！", QMessageBox::Information );
    }

    return true;
}

MainWindow::~MainWindow()
{
    if ( NULL != pMultimedia ) {
        pMultimedia->SystemShutdown( );
        pMultimedia->DestroyInstance( pMultimedia );
    }

    if ( NULL != pVehicle ) {
        pVehicle->Uninitialize( 0 );
        pVehicle->Uninitialize( 1 );
        pVehicle->DestroyInstance( pVehicle );
    }

    delete ui;
}

void MainWindow::on_btnParam_clicked()
{
    //CRecognizeParamDlg dlg( this );
    //dlg.exec( );
}

void MainWindow::RecognizeFile( QString& strName )
{

}

void MainWindow::ClearTable( )
{
    ui->tableWidget->setRowCount( 0 );
    ui->tableWidget->clearContents( );
}

void MainWindow::InsertPlate( UINT nChannel, bool bRet, QString& strFile )
{
    QString strTmp( result[ nChannel][ 0 ].license );
    if ( strTmp != strPlate ) {
        strPlate = strTmp;
    } else {
        return;
    }

    int nRow = ui->tableWidget->rowCount( );
    ui->tableWidget->setRowCount( nRow + 1 );
    QTableWidgetItem* pItem = new QTableWidgetItem( "1" );
    ui->tableWidget->setItem( nRow, 0, pItem );

    //for ( int nIndex = 0; nIndex < nPlateNumber; nIndex++ ) {
    if ( bRet ) {
            qDebug ( ) << "License : " << result[ nChannel][ 0 ].license << endl;
            //ui->tableWidget->setRowCount( ui->tableWidget->rowCount( ) + 1 );

            pItem = new QTableWidgetItem( strTmp );
            ui->tableWidget->setItem( nRow, 1, pItem );

            pItem = new QTableWidgetItem( result[ nChannel][ 0 ].color );
            ui->tableWidget->setItem( nRow, 2, pItem );

            pItem = new QTableWidgetItem( QString::number( result[ nChannel][ 0 ].nTime ) + "毫秒" );
            ui->tableWidget->setItem( nRow, 3, pItem );

            pItem = new QTableWidgetItem( QString::number( result[ nChannel][ 0 ].nConfidence ) );
            ui->tableWidget->setItem( nRow, 4, pItem );

            int nWidth = result[ nChannel][ 0 ].rcLocation.right - result[ nChannel][ 0 ].rcLocation.left;
            int nHeight = result[ nChannel][ 0 ].rcLocation.bottom - result[ nChannel][ 0 ].rcLocation.top;
            QString str = QString( "%1,%2,D:%3" ).arg( QString::number( nWidth ),QString::number( nHeight),
                                                                     QString::number( result[ nChannel][ 0 ].nDirection ) );

            QString str1 = QString( "(%1, %2)(%3, %4):D%5" ).arg( QString::number( result[ nChannel][ 0 ].rcLocation.left ),
                                                                  QString::number( result[ nChannel][ 0 ].rcLocation.top ),
                                                                  QString::number( result[ nChannel][ 0 ].rcLocation.right ),
                                                                  QString::number( result[ nChannel][ 0 ].rcLocation.bottom ),
                                                                  QString::number( result[ nChannel][ 0 ].nDirection ) );
            pItem = new QTableWidgetItem( str1 );
            ui->tableWidget->setItem( nRow, 5, pItem );

        } else {
#if 0
            pItem = new QTableWidgetItem( "拒识" );
            ui->tableWidget->setItem( nRow, 1, pItem );

            pItem = new QTableWidgetItem( "" );
            ui->tableWidget->setItem( nRow, 2, pItem );

            pItem = new QTableWidgetItem( "0毫秒" );
            ui->tableWidget->setItem( nRow, 3, pItem );

            pItem = new QTableWidgetItem( "0" );
            ui->tableWidget->setItem( nRow, 4, pItem );
#endif

        }
        pItem = new QTableWidgetItem( strFile );
        ui->tableWidget->setItem( nRow, 6, pItem );
    //}
}

void MainWindow::on_btnImagePath_clicked()
{
    strFile = QFileDialog::getOpenFileName( this, "选择图像文件", QString(""), "Images (*.BMP *.TIF *.JPG *.JPEG )" );

    QDir dir ( strFile );
    dir.cdUp( );
    dir.setFilter( QDir::Files );
    ClearTable( );
    lstFileInfo = dir.entryInfoList( );
    if ( false == Init( 1 ) ) {
        return;
    }

    for (int i = 0; i < lstFileInfo.size( ); ++i) {
         QFileInfo fileInfo = lstFileInfo.at( i );
         QString strTmp = fileInfo.absoluteFilePath( );
         //::Sleep( 1000 );
         bool bRet = pVehicle->RecognizeFile( strTmp, result[ 0], nResult, 0 );

         InsertPlate( 0,bRet, strTmp );
     }

    pVehicle->Uninitialize( 0 );

}

void MainWindow::on_btnOpenVideo_clicked()
{
    if ( NULL == pMultimedia ) {
        return;
    }

    ClearTable( );

    //if ( false == Init( bCard ? ImageFormatBGR : ImageFormatYUV420 ) ) {//ImageFormatBGR
    //    return;
    //}

    bStartVideo = true;

    hChannel[0] = pMultimedia->OpenChannel( 0 );
    hChannel[1] = pMultimedia->OpenChannel( 1 );
    int nRet = 0;

    //if ( INVALID_HANDLE != hChannel ) {
        QRect rect = ui->lblVideo1->rect( );
        nRet = pMultimedia->PlayVideo(hChannel[0], ui->lblVideo1->winId( ), rect, 0 );

        rect = ui->lblVideo2->rect( );
        nRet = pMultimedia->PlayVideo( hChannel[1], ui->lblVideo2->winId( ), rect, 0 );

        //nRet = pMultimedia->PlayVideo( ( HANDLE )1, ui->lblVideo2->winId( ), rect, 0 );
        //nRet = pMultimedia->PlayVideo( ( HANDLE )2, ui->lblVideo3->winId( ), rect, 0 );
        //nRet = pMultimedia->PlayVideo( ( HANDLE )3, ui->lblVideo4->winId( ), rect, 0 );

        //nRet = pMultimedia->StopVideo( ( HANDLE )0 );
        //nRet = pMultimedia->PlayVideo( ( HANDLE )0, ui->lblVideo1->winId( ), rect, 0 );

        nRet = pMultimedia->SetupDetection(hChannel[0], ( HK_MOTION_CB ) FuncEncDataCallback, 0, ( PVOID) FuncRawDataCallback );
        nRet = pMultimedia->MotionDetection(  hChannel[0], true );

        nRet = pMultimedia->SetupDetection(  hChannel[1], ( HK_MOTION_CB ) FuncEncDataCallback, 0, ( PVOID) FuncRawDataCallback );
        nRet = pMultimedia->MotionDetection( hChannel[1], true );

        //nRet = pMultimedia->SetupDetection( ( HANDLE )1, ( HK_MOTION_CB ) MyPrcCbMotionDetect, 0 );
       // nRet = pMultimedia->MotionDetection( ( HANDLE )1, true );
    //}

    //nRet = pMultimedia->GetStreamData( bCard ? ( HANDLE )0 : hChannel[ 0 ], TRUE, imgData[ 0 ], bCard ? 3 : 0 );
    //nRet = pMultimedia->GetStreamData( bCard ? ( HANDLE )0 : hChannel[1], TRUE, imgData[ 1 ], bCard ? 3 : 0 );
    //nRet = pMultimedia->GetStreamData( ( HANDLE )1, TRUE, imgData, 3 );
    //nRet = pMultimedia->GetStreamData( ( HANDLE )2, TRUE, imgData, 3 );
    //nRet = pMultimedia->GetStreamData( ( HANDLE )3, TRUE, imgData, 3 );
   // pMultimedia->TmEnablePicMessage( 0, TRUE, PrcPicMessage );
}

void MainWindow::on_btnCloseVideo_clicked()
{
    if ( NULL == pMultimedia || false == bStartVideo ) {
        return;
    }

    try {
        pVehicle->Uninitialize( 0 );
        pVehicle->Uninitialize( 1 );

        int nRet = pMultimedia->GetStreamData( hChannel, FALSE, NULL, 0 );
        nRet = pMultimedia->MotionDetection( hChannel, false );
        nRet = pMultimedia->StopVideo( hChannel );
        nRet = pMultimedia->CloseChannel( hChannel );

        QString strStyle = "background-color: rgb(0, 0, 0);";
        ui->lblVideo1->setStyleSheet( strStyle );
        bStartVideo = false;
        hChannel[ 0] = INVALID_HANDLE;
    } catch (  QtConcurrent::Exception& e ) {
       //CCommonFunction::MsgBox( this, "Error", e.what( ), QMessageBox::Critical );
    } catch ( ... ) {
       //CCommonFunction::MsgBox( this, "Error", "出错了", QMessageBox::Critical );
    }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{

    QString strFile = ui->tableWidget->item( row, 5 )->text( );

    ui->lblPlate->setText( ui->tableWidget->item( row, 1 )->text( ) );

    if ( "" == strFile ) {
        return;
    }

    QPixmap map( strFile );
    ui->lblVideo1->setPixmap( map );
}

void MainWindow::on_btnClear_clicked()
{
    ClearTable( );
}

void MainWindow::on_btnCapture_clicked()
{
    QString strFile = "c:/" + QString::number( QDateTime::currentDateTime( ).toTime_t( ) ) + ".jpg";
    pMultimedia->CaptureJpeg( hChannel, strFile );
}


void MainWindow::on_pushButton_clicked()
{
    QString strFile = "d:/" + QString::number( QDateTime::currentDateTime( ).toTime_t( ) ) + ".bmp";
    pMultimedia->CaptureBMP( 0, strFile );
}
