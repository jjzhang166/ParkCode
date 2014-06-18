#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThreadPool>
#include "windows.h"
#include <QMessageBox>

CLocalCltCommunication* g_pLocalCltComm;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Singleton( );
    ui->setupUi(this);

    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    pTextCodec = CCommonFunction::GetTextCodec( );

    pLocalComm = CLocalSvrCommunication::GetInstance( pTextCodec );
    connect( pLocalComm, SIGNAL( NotifyMsg( QString ) ), this, SLOT( DisplayMessage( QString ) ) );
    pLocalComm->StartupServer( );

    g_pLocalCltComm = new CLocalCltCommunication( pTextCodec, this );
    g_pLocalCltComm->Connect2Server( );

    CNetProcessData::GetCommonParams( );

    netServer = CSvrThread::GetInstance( this );
    connect( netServer, SIGNAL( Notify( QString ) ), this, SLOT(DisplayMessage( QString ) ) );
    netServer->start( );
    netServer->StartupUdpServer( true );
    netServer->StartupTcpServer( true );

    qRegisterMetaType< QAbstractSocket::SocketError >( "QAbstractSocket::SocketError" );
    sysTrayIcon = NULL;
    NotifyIcon( );

    Qt::WindowFlags flags = windowFlags( );
    flags &= ( ~Qt::WindowMinimizeButtonHint );
    setWindowFlags( flags );

    //setWindowState( Qt::WindowMinimized );
    //close( );
}

MainWindow::~MainWindow()
{
    CNetProcessData::ReleaseResource( );
    CLocalSvrCommunication::ReleaseInstance( );

    if ( NULL != netServer && netServer->isRunning( ) ) {
        netServer->terminate( );
    }

    delete ui;
}

void MainWindow::DisplayMessage( QString strMsg )
{
    ui->textBrowser->append( strMsg ); // The Same format
    //ui->textBrowser->insertPlainText( strMsg ); // Insert at current cursor position
}

void MainWindow::Singleton( )
{
    QString strGUID = "{7D868E8B-612D-42E1-8AF6-B2F7F63CB8AD}";
    WCHAR cGUID[ 256 ] = { 0 };
    strGUID.toWCharArray( cGUID );
    HANDLE hEvent = CreateEvent( NULL, TRUE, FALSE, cGUID );
    DWORD dwError = GetLastError( );

    if ( NULL != hEvent && ERROR_ALREADY_EXISTS == dwError ) {
        QMessageBox::information( this, "提示", "数据接收服务器已启动！" );
        exit( 0 );
    }
}

void MainWindow::on_btnClear_clicked()
{
    ui->textBrowser->clear( );
}

void MainWindow::on_btnSave_clicked()
{

}

void MainWindow::closeEvent( QCloseEvent * e )
{
    e->ignore( );
    hide( );
}

void MainWindow::NotifyIcon( )
{
    if ( NULL != sysTrayIcon ) {
        return;
    }

    QString strFile = "";
    CCommonFunction::GetPath( strFile, CommonDataType::PathUIImage );
    strFile += "Icon.JPG";
    QIcon icon( strFile );
    sysTrayIcon = new QSystemTrayIcon( icon, this );

    connect(  sysTrayIcon, SIGNAL( activated( QSystemTrayIcon::ActivationReason ) ),
                     this, SLOT( SysTrayActivate( QSystemTrayIcon::ActivationReason ) ) );

    QString strTip = "中心数据接收程序。";
    sysTrayIcon->setToolTip( strTip );

    QMenu* pMenu = new QMenu( );

    QString strText = "显示";
    QVariant var( true ); // 1
    AddMenuItem( pMenu, var, strText );

    strText = "隐藏"; // 0
    var =  false;
    AddMenuItem( pMenu, var, strText );

    strText = "退出";
    var =  2;
    AddMenuItem( pMenu, var, strText );

    sysTrayIcon->setContextMenu( pMenu );
    sysTrayIcon->show( );
}

void MainWindow::AddMenuItem( QMenu *pMenu, QVariant &varData, QString &strText )
{
    QAction* act = new QAction( strText, pMenu );
    act->setData( varData );
    connect( act, SIGNAL( triggered( ) ), this, SLOT( SysTray( ) ) );
    pMenu->addAction( act );
}

void MainWindow::SysTray( )
{
    QAction* act = qobject_cast< QAction* > ( sender( ) ) ;
    QVariant var = act->data( );

    if ( 2 == var.toInt( ) ) {
        exit( 0 );
    } else {
        var.toBool( ) ? show( ) : hide( );
        //setVisible( var.toBool( ) );
    }
}

void MainWindow::SysTrayActivate( QSystemTrayIcon::ActivationReason reason )
{
    if ( QSystemTrayIcon::Context != reason ) {
        return;
    }

    QMenu* pMenu = sysTrayIcon->contextMenu( );
    QList< QAction* > lstAct  = pMenu->actions( );
    lstAct.at( 0 )->setEnabled( !isVisible( ) );
    lstAct.at( 1 )->setEnabled( isVisible( ) );
}

