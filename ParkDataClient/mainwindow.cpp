#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QtGui/QApplication>
#include "windows.h"
#include <QFile>

MainWindow::MainWindow( QTextCodec* pCodec, QWidget *parent) :
   QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    netClient = &CNetClient::GetInstance( true, true, pCodec, this );

    bool bRet = connect( netClient, SIGNAL( Notify( QString ) ), this, SLOT( NotifyMessage( QString ) ) );
    bRet = false;
}

void MainWindow::FtpCmdFinished(int nId, bool bError)
{
    //qDebug( ) << ftp.errorString( ) << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartupClient_clicked()
{
    QProcess proc;
    QString strExe = QApplication::applicationFilePath( );

    for ( int nIndex = 0; nIndex < ui->spinBox->value( ); nIndex++ ) {
        proc.startDetached( strExe );
    }
}

void MainWindow::NotifyMessage( QString strMsg )
{
    ui->textBrowser->append( strMsg );
}

void MainWindow::on_SendData_clicked()
{
#if true
    QString strData = "100\nÓåF12345\n1\n2011-11-28 10:12:45\n0\n6535698\r101\n´¨F12345\n0\n2011-11-28 11:26:23\n1\47892";
    netClient->SendTableData( strData, 2, 6, NetTransport::TabInOutRecord );
    //Sleep( 1000 );

    QString strPlate = "ÓåF12345";
    QDateTime dt = QDateTime::currentDateTime( );
    QFile file( "D:/WinParkUI/debug/Image/MainBG.jpg");
    file.open( QIODevice::ReadOnly );
    QByteArray byData = file.readAll( );
    netClient->SendImageData( byData.data( ), byData.count( ), NetTransport::ImgOut, 1232, strPlate, dt );
    //Sleep( 1000 );

    QString strHb = "1234,192.168.1.25,6001";
    netClient->SendHeartbeatData( strHb, NetTransport::HbClientIP );

    strHb = "1234,192.168.1.25,2011-11-28 12:02:14";
    netClient->SendHeartbeatData( strHb, NetTransport::HbNetState );
    //Sleep( 1000 );
#else
    QString strUrl = "http://www.ifeng.com";
    httpClient.HttpGet( strUrl );
#endif
}

void MainWindow::on_pushButton_clicked()
{
    netClient->PostHttpServerEvent( CHttpEvent::HttpStartup );
}

void MainWindow::on_pushButton_2_clicked()
{
    netClient->PostHttpServerEvent( CHttpEvent::HttpAddListenUrl );
}

void MainWindow::on_pushButton_3_clicked()
{
    netClient->PostHttpServerEvent( CHttpEvent::HttpRetrieveRequest );
}

void MainWindow::on_pushButton_4_clicked()
{
    netClient->PostHttpServerEvent( CHttpEvent::HttpAddDelistenUrl );
}

void MainWindow::on_pushButton_5_clicked()
{
    netClient->PostHttpServerEvent( CHttpEvent::HttpCleanup );
}

void MainWindow::on_pushButton_6_clicked()
{
}
