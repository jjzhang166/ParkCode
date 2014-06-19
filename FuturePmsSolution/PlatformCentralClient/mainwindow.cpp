#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QPlatformGlobal* g_pPlatformGlobal;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( g_pPlatformGlobal, SIGNAL( ParseTcpData( QString, QThread*, QTcpSocket*, void* ) ),
             this, SLOT( HandleParseTcpData( QString, QThread*, QTcpSocket*, void* ) ) );

    connect( g_pPlatformGlobal, SIGNAL( ParseUdpData( QString, quint16, QThread*, void*, MyEnums::UdpDatagramType ) ),
             this, SLOT( HandleParseUdpData( QString, quint16, QThread*, void*, MyEnums::UdpDatagramType ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayMainArgs( MyDataStructs::QMyStringList &lstParam )
{
    QStringList lstStr( lstParam );
    ui->listWidget->insertItems( 0, lstStr );
}

void MainWindow::on_pushButton_clicked()
{
    MyDataStructs::QEventMultiHash hash;
    QStringList lstTexts;

    lstTexts <<"Hello1°¡" << "Hello2\nTest" << "Hello3";
    g_pPlatformGlobal->GenerateLogHash( hash, lstTexts, QManipulateIniFile::LogDatabase );

    lstTexts.clear( );
    lstTexts <<"Hello11" << "Hello11" << "Hello33";
     g_pPlatformGlobal->GenerateLogHash( hash, lstTexts, QManipulateIniFile::LogNetwork );

    g_pPlatformGlobal->StartupLogWrite( g_pPlatformGlobal->GetThreadGenerator( ).GenerateLogThread( ), hash );
}

void MainWindow::on_pushButton_2_clicked()
{
    //g_pPlatformGlobal->StartupThreadExit(
    //            g_pPlatformGlobal->GetThreadGenerator( ).GenerateLogThread( ), MyEnums::ThreadLogger );

    g_pPlatformGlobal->StartupThreadExit(
                g_pPlatformGlobal->GetUdpClientThreadHash( ).values( ).at( 0 ), MyEnums::ThreadUdpClient );
}

void MainWindow::on_pushButton_3_clicked()
{
    g_pPlatformGlobal->BrowseLog( QManipulateIniFile::PlatformCentralLogClient );
}

void MainWindow::on_pushButton_4_clicked()
{
    g_pPlatformGlobal->TcpClientAllConnectOrDisconnect( true );
}

void MainWindow::on_pushButton_5_clicked()
{
   g_pPlatformGlobal->TcpClientAllConnectOrDisconnect( false );
}

void MainWindow::on_pushButton_6_clicked()
{
    QString strText = "Hello2\nTestÄãºÃÂð£¿";
    QByteArray byteData = g_pPlatformGlobal->GetCommonFunctionObj().GetTextCodec( )->fromUnicode( strText );

    g_pPlatformGlobal->TcpClientSendData2AllThreads( byteData );
}

void MainWindow::on_pushButton_7_clicked()
{
    g_pPlatformGlobal->CreateTcpClientThread( QManipulateIniFile::PlatformCentralClient );
}

void MainWindow::HandleParseTcpData( QString strServer, QThread* pSenderThread, QTcpSocket* pPeerSocket, void* pByteArray )
{
    QByteArray* pByteData = ( QByteArray* ) pByteArray;

    strServer += " : " + QString ( *pByteData ) + "\n";
    ui->textEdit->insertPlainText( strServer );

    //g_pPlatformGlobal->TcpClientSendData( );

    delete pByteData;
}

void MainWindow::HandleParseUdpData( QString strSenderIP, quint16 nSenderPort, QThread *pSenderThread, void *pByteArray, MyEnums::UdpDatagramType dgType )
{
    QByteArray* pByteData = ( QByteArray* ) pByteArray;
    QString strType;

    switch ( dgType ) {
    case MyEnums::UdpUnicast :
        strType = "UdpUnicast";
        break;

    case MyEnums::UdpBroadcast :
        strType = "UdpBroadcast";
        break;

    case MyEnums::UdpMulticast :
        strType = "UdpMulticast";
        break;
    }

    strSenderIP += ":" + QString::number( nSenderPort ) + " " + strType + " --> " + QString ( *pByteData ) + "\n";
    ui->textEdit->insertPlainText( strSenderIP );

    //g_pPlatformGlobal->TcpClientSendData( );

    delete pByteData;
}

void MainWindow::on_pushButton_8_clicked()
{
    g_pPlatformGlobal->CreateUdpClientThread( QManipulateIniFile::PlatformCentralClient, true );
}

void MainWindow::on_pushButton_9_clicked()
{
    g_pPlatformGlobal->CreateUdpListenerThread( QManipulateIniFile::PlatformCentralClient, false );
}

void MainWindow::on_pushButton_10_clicked()
{
    QString strText = "UDP Unicast Hello2\nTestÄãºÃÂð£¿";
    QByteArray byteData = g_pPlatformGlobal->GetCommonFunctionObj().GetTextCodec( )->fromUnicode( strText );

    g_pPlatformGlobal->UdpClientSendData2AllThreads( byteData, MyEnums::UdpUnicast );
}

void MainWindow::on_pushButton_11_clicked()
{
    QString strText = "UDP Broadcast Hello2\nTestÄãºÃÂð£¿";
    QByteArray byteData = g_pPlatformGlobal->GetCommonFunctionObj().GetTextCodec( )->fromUnicode( strText );

    g_pPlatformGlobal->UdpClientSendData2AllThreads( byteData, MyEnums::UdpBroadcast  );
}

void MainWindow::on_pushButton_12_clicked()
{
    QString strText = "UDP Multicast Hello2\nTestÄãºÃÂð£¿";
    QByteArray byteData = g_pPlatformGlobal->GetCommonFunctionObj().GetTextCodec( )->fromUnicode( strText );

    g_pPlatformGlobal->UdpClientSendData2AllThreads( byteData, MyEnums::UdpMulticast );
}

void MainWindow::on_pushButton_13_clicked()
{
    g_pPlatformGlobal->UdpOperateAllMulticastGroups( true );
}

void MainWindow::on_pushButton_14_clicked()
{
    g_pPlatformGlobal->UdpOperateAllMulticastGroups( false );
}

void MainWindow::on_pushButton_15_clicked()
{
    g_pPlatformGlobal->CreateUdpBroadcastListenerThread( QManipulateIniFile::PlatformCentralClient, false );
}

void MainWindow::on_pushButton_16_clicked()
{
    g_pPlatformGlobal->CreateUdpMulticastListenerThread( QManipulateIniFile::PlatformCentralClient, false );
}
