#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Qt::WindowFlags nFlags = windowFlags( ) &
            ( ~Qt::WindowMaximizeButtonHint ) &
            ( ~Qt::WindowCloseButtonHint );
    setWindowFlags( nFlags );

    HideCtrl( );
    Initialize( );
    InitializeHash( );
    InitializeCmd( ui->cbM77Cmd );
    InitializeSignalSlot( );
}

MainWindow::~MainWindow()
{
    pPortController->ReleaseController( );
    pNetController->ReleaseController( );
    pDbController->ReleaseController( );

    delete ui;
}

void MainWindow::closeEvent( QCloseEvent *e )
{
    e->ignore( );
}

void MainWindow::Initialize( )
{
    pNetController = NetworkController::GetController( );
    //Sleep( 3000 );
    pDbController = DatabaseController::GetController( );
    DatabaseController::CreateDbThreadPool( );
    //Sleep( 2000 );
    pPortController = SerialPortController::GetController( );
    //Sleep( 1000 );

    pConfig = CMainConfigurator::GetConfigurator( );
    ui->btnHide->setVisible( false );

    connect( pPortController, SIGNAL( Log( QString, bool ) ),
             this, SLOT( DisplayPortLog( QString, bool ) ) );

    connect( pNetController, SIGNAL( Log( QString, bool ) ),
             this, SLOT( DisplayNetworkLog( QString, bool ) ) );

    connect( pDbController, SIGNAL( Log( QString, bool ) ),
             this, SLOT( DisplayDatabaseLog( QString, bool ) ) );

    pConfig->ReadComM77R( *ui->cbComM77R, lstCOMName );
    OpenPort( lstCOMName );

    if ( 0 < ui->cbComM77R->count( ) ) {
        ui->sbCmd0->setValue( GetItemData( ui->cbComM77R, 0 ) );
    }

    pConfig->ReadPortMaxConn( *ui->sbPort, *ui->sbMaxConn );
    pConfig->ReadIPPort( *ui->edtServerIP, *ui->sbServicePort );

    on_btnStartListen_clicked( );
}

void MainWindow::OpenPort( QStringList& lstCom )
{
    foreach ( const QString& strCom, lstCom ) {
        pPortController->OpenSerialPort( strCom );
    }
}

void MainWindow::ClosePort( QStringList& lstCom )
{
    foreach ( const QString& strCom, lstCom ) {
        pPortController->CloseSerialPort( strCom );
    }
}

void MainWindow::InitializeSignalSlot( )
{
    connect( ui->cbComM77R, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( ComM77RIndexChanged( int ) ) );
    connect( ui->cbM77Cmd, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( M77CmdIndexChanged( int ) ) );
}

void MainWindow::InitializeHash( )
{
    hashLabel.clear( );
    hashLabel.insert( 0, ui->lblCmd0 );
    hashLabel.insert( 1, ui->lblCmd1 );
    hashLabel.insert( 2, ui->lblCmd2 );

    hashSpinBox.insert( 0, ui->sbCmd0 );
    hashSpinBox.insert( 1, ui->sbCmd1 );
    hashSpinBox.insert( 2, ui->sbCmd2 );

    hashLabelText.clear( );

    hashLabelText.insert( SerialPortController::CmdDetectorThresholdModify,
                          "接受器ID@检测器ID@门限值" );
    hashLabelText.insert( SerialPortController::CmdDetectorDelayTimeModify,
                          "接受器ID@检测器ID@延时值" );
    hashLabelText.insert( SerialPortController::CmdDetectorReadData$,
                          "接受器ID@检测器ID" );
    hashLabelText.insert( SerialPortController::CmdDetectorReadDataR,
                          "接受器ID@检测器ID" );
    hashLabelText.insert( SerialPortController::CmdDetectorReadDataA,
                          "接受器ID@检测器ID" );
    hashLabelText.insert( SerialPortController::CmdDetectorForceReset,
                          "接受器ID@检测器ID" );
    hashLabelText.insert( SerialPortController::CmdDetectorModifyID,
                          "接受器ID@检测器原ID@检测器新ID" );
    hashLabelText.insert( SerialPortController::CmdDetectorModifyChannel,
                          "接受器ID@检测器ID@检测器信道号" );
    hashLabelText.insert( SerialPortController::CmdDetectorCommunicationTestOpen,
                          "接受器ID@检测器ID" );
    hashLabelText.insert( SerialPortController::CmdDetectorCommunicationTestClose,
                          "接受器ID@检测器ID" );
    hashLabelText.insert( SerialPortController::CmdReceiverModifyHostChannel,
                          "接受器ID@信道号" );
    hashLabelText.insert( SerialPortController::CmdReciverSetID,
                          "接受器原ID@接受器新ID" );
    hashLabelText.insert( SerialPortController::CmdReceiverHostSleep,
                          "接受器ID" );
}

void MainWindow::InitializeCmd( QComboBox *pCB )
{
    pCB->clear( );

    QString strText[ ] = { "检测器门限值修改",
                           "检测器延时修改",
                           "检测器读数据$",
                           "检测器读数据R",
                           "检测器读数据A",
                           "检测器强制复位",
                           "检测器修改ID",
                           "检测器修改信道",
                           "检测器通信测试建立",
                           "检测器通信测试关闭",
                           "接收器修改主机信道",
                           "接收器ID设置" };

    for ( qint32 nIndex = 0; nIndex < SerialPortController::CmdCount - 1; nIndex++ ) {
        pCB->addItem( strText[ nIndex ], nIndex );
    }

    ShowCtrl( ui->cbM77Cmd, 0 );
}

void MainWindow::DisplayPortLog( QString strLog, bool bStatic )
{
    QPlainTextEdit* pCtrl = bStatic ? ui->txtPortStaticLog : ui->txtPortDynamicLog;

    if ( !bStatic && 100 <= pCtrl->blockCount() ) {
        pCtrl->clear( );
    }
    pCtrl->appendPlainText( strLog );
}

void MainWindow::DisplayNetworkLog( QString strLog, bool bStatic )
{
    QPlainTextEdit* pCtrl = bStatic ? ui->txtNetworkStaticLog : ui->txtNetworkDynamicLog;

    if ( !bStatic && 100 <= pCtrl->blockCount() ) {
        pCtrl->clear( );
    }
    pCtrl->appendPlainText( strLog );
}

void MainWindow::DisplayDatabaseLog( QString strLog, bool bStatic )
{
    QPlainTextEdit* pCtrl = bStatic ? ui->txtDatabaseStaticLog : ui->txtDatabaseDynamicLog;

    if ( !bStatic && 100 <= pCtrl->blockCount() ) {
        pCtrl->clear( );
    }
    pCtrl->appendPlainText( strLog );
}

void MainWindow::on_btnPortCmd_clicked()
{
    qint32 nData = GetItemData( ui->cbM77Cmd, ui->cbM77Cmd->currentIndex( ) );
    SerialPortController::CmdPort eCmd = ( SerialPortController::CmdPort ) nData;
    QString strCOMx = ui->cbComM77R->currentText( );
    pPortController->SendCmd( strCOMx, eCmd,
                            ui->sbCmd0->value( ),
                            ui->sbCmd1->value( ),
                            ui->sbCmd2->value( ) );

    if ( SerialPortController::CmdReciverSetID == eCmd ) {
        qint32 nIndex = ui->cbComM77R->currentIndex( );
        ui->cbComM77R->setItemData( nIndex,
                                    ui->sbCmd1->value( ) );
        pConfig->WriteComM77R( nIndex, ui->sbCmd1->value( ) );
    }
}

void MainWindow::M77CmdIndexChanged(int index)
{
    HideCtrl( );
    QComboBox* pCB = ( QComboBox* ) sender( );
    ShowCtrl( pCB, index );
}

void MainWindow::ShowCtrl( QComboBox* pCB, qint32 nIndex )
{
    qint32 nData = GetItemData( pCB, nIndex );

    const QString strValue = hashLabelText.value( nData );
    QString strSeperator = "@";
    QStringList lstValue = strValue.split( strSeperator );

    QLabel* pLabel = NULL;
    QSpinBox* pSpinBox = NULL;

    for ( qint32 nItem = 0; nItem < lstValue.length( ); nItem++ ) {
        pLabel = hashLabel.value( nItem, NULL );
        if ( NULL != pLabel ) {
            pLabel->setVisible( true );
            pLabel->setText( lstValue.at( nItem ) );
        }

        pSpinBox = hashSpinBox.value( nItem, NULL );
        if ( NULL != pSpinBox ) {
            pSpinBox->setVisible( true );
        }
    }
}

void MainWindow::HideCtrl( )
{
    ui->lblCmd0->setVisible( false );
    ui->lblCmd1->setVisible( false );
    ui->lblCmd2->setVisible( false );

    ui->sbCmd0->setVisible( false );
    ui->sbCmd1->setVisible( false );
    ui->sbCmd2->setVisible( false );
}

qint32 MainWindow::GetItemData( QComboBox *pCB, qint32 nIndex )
{
    QString strReceiverID = pCB->itemData( nIndex ).toString( );
    return strReceiverID.toInt( );
}

void MainWindow::ComM77RIndexChanged(int index)
{
    QComboBox* pCB = ( QComboBox* ) sender( );
    ui->sbCmd0->setValue( GetItemData( pCB, index ) );
}

void MainWindow::on_btnStartListen_clicked()
{
    quint16 nPort = ui->sbPort->value( );
    qint32 nMaxConn = ui->sbMaxConn->value( );

    pNetController->StartListen( nPort, nMaxConn );
    pConfig->WritePortMaxConn( nPort, nMaxConn );

    pNetController->StartMultiCastListen( );
}

void MainWindow::on_btnStopListen_clicked()
{
    pNetController->StopListen( );
    pNetController->StopMultiCastListen( );
}

void MainWindow::on_btnConnectDb_clicked()
{
    QString strIP = ui->edtServerIP->text( );
    quint16 nPort = ui->sbServicePort->value( );

    pConfig->WriteIPPort( strIP, nPort );

    //pDbController->PostConnectDbEvent( );
}
