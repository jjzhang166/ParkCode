#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QPlatformGlobal* g_pPlatformGlobal;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    g_pPlatformGlobal->BrowseLog( QManipulateIniFile::PlatformCentralLogServer );
}

void MainWindow::on_pushButton_2_clicked()
{
    g_pPlatformGlobal->CreateTcpListenerThread( QManipulateIniFile::PlatformCentralServer );
}

void MainWindow::on_pushButton_3_clicked()
{
    g_pPlatformGlobal->CreateUdpListenerThread( QManipulateIniFile::PlatformCentralServer, true );
}

void MainWindow::on_pushButton_4_clicked()
{
    g_pPlatformGlobal->CreateUdpBroadcastListenerThread( QManipulateIniFile::PlatformCentralServer, true );
}

void MainWindow::on_pushButton_5_clicked()
{
    g_pPlatformGlobal->CreateUdpMulticastListenerThread( QManipulateIniFile::PlatformCentralServer, true );
}

void MainWindow::on_pushButton_6_clicked()
{
    g_pPlatformGlobal->UdpOperateAllMulticastGroups( true );
}

void MainWindow::on_pushButton_7_clicked()
{
    g_pPlatformGlobal->UdpOperateAllMulticastGroups( false );
}
