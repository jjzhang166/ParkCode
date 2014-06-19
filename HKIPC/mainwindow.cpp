#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pVideoThread = QIPCThread::GetInstance( );
    connect( pVideoThread, SIGNAL( NotifyMessage( QString ) ),
                                   this, SLOT( HandleNotifyMessage( QString ) ) );

    connect( pVideoThread, SIGNAL( CapturedJPGImage( quint32, QString ) ) ,
                                   this, SLOT( HandleCapturedJPGImage( quint32, QString ) ) );


    pFrame[ 0 ] = ui->frame0;
    pFrame[ 1 ] = ui->frame1;
    pFrame[ 2 ] = ui->frame2;
    pFrame[ 3 ] = ui->frame3;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandleCapturedJPGImage( quint32 nChannel, QString strFileName )
{

}

void MainWindow::HandleNotifyMessage( QString strMsg )
{
    strMsg += "\r\n";
    ui->plainTextEdit->appendPlainText( strMsg );
}

void MainWindow::on_pushButton_clicked()
{
    QIPCEvent::EventParam uParam;

    pVideoThread->PostIPCStartupEvent( );

    uParam.EventConnectTimeout.dwWaitTime = 2000;
    uParam.EventConnectTimeout.dwTryTimes = 1;
    pVideoThread->PostIPCSetConnectTimeoutEvent( uParam );

    uParam.EventReconnectTimeout.dwInterval = 10000;
    uParam.EventReconnectTimeout.bEnableRecon = TRUE;
    pVideoThread->PostIPCSetReconnectTimeEvent( uParam );

    strcpy( uParam.EventLogin.cIP, "192.168.1.64" );
    uParam.EventLogin.wPort = 8000;
    strcpy( uParam.EventLogin.cUser, "admin" );
    strcpy( uParam.EventLogin.cPwd, "12345" );
    pVideoThread->PostIPCLoginEvent( uParam );

    for ( int nIndex = 0; nIndex< 4; nIndex++ ) {
        strcpy( uParam.EventStartRealPlay.cIP, "192.168.1.64" );
        uParam.EventStartRealPlay.hPlayWnd = pFrame[ nIndex ]->winId( );
        pVideoThread->PostIPCStartRealPlayEvent( uParam );
    }
}

void MainWindow::closeEvent( QCloseEvent *event )
{
}

void MainWindow::on_pushButton_2_clicked()
{
    QIPCEvent::EventParam uParam;
    QString strPath = qApp->applicationDirPath( );

    strcpy( uParam.EventCaptureJPG.cIP, "192.168.1.64" );

    for ( int nIndex =0; nIndex < 4; nIndex++ ) {
        uParam.EventCaptureJPG.nChannel = nIndex;
        QString strTmp = strPath + "/Channel" +
                QString::number( nIndex ) + "_" +
                QString::number( QDateTime::currentMSecsSinceEpoch( ) ) +
                ".JPG";
        strcpy( uParam.EventCaptureJPG.cFile,
                strTmp.toAscii( ).data( ) );

        pVideoThread->PostIPCCaptureJPGEvent( uParam );
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QIPCEvent::EventParam uParam;
    char* pIP = "192.168.1.64";

    for ( int nIndex =0; nIndex < 4; nIndex++ ) {
        uParam.EventStopRealPlay.hPlayWnd = pFrame[ nIndex ]->winId( );
        pVideoThread->PostIPCStopRealPlayEvent( uParam );
    }

    strcpy( uParam.EventLogout.cIP, pIP );
    pVideoThread->PostIPCLogoutEvent( uParam );
    pVideoThread->PostIPCCleanupEvent( );
}
