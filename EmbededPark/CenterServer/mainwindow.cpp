#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( &libThread, SIGNAL( DisplayLog( QString ) ),
             this, SLOT( HandleDisplayLog( QString ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandleDisplayLog( QString strText )
{
    ui->edtLog->appendPlainText( strText );
    ui->edtLog->appendPlainText( "\r\n" );
}

void MainWindow::on_pushButton_clicked()
{
    libThread.PostListenerThreadEvent( QCommonLibrary::EventStartListen );
}

void MainWindow::on_pushButton_2_clicked()
{
    libThread.PostListenerThreadEvent( QCommonLibrary::EventStopListen );
}
