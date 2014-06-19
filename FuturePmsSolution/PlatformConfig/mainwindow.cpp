#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetDbType( );
    ReadData( );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetItemValue( const QManipulateIniFile::IniFileNames iniFile,
                               const QManipulateIniFile::IniFileSections iniSection,
                               const QManipulateIniFile::IniFileSectionItems iniItem,
                               QLineEdit *pEdit )
{
    QVariant varValue;

    manipulateIniFile.IniFileValue( iniFile, iniSection, iniItem, false, varValue );
    pEdit->setText( varValue.toString( ) );
}

void MainWindow::GetItemValue( const QManipulateIniFile::IniFileNames iniFile,
                               const QManipulateIniFile::IniFileSections iniSection,
                               const QManipulateIniFile::IniFileSectionItems iniItem,
                               QComboBox *pComboBox )
{
    QVariant varValue;

    manipulateIniFile.IniFileValue( iniFile, iniSection, iniItem, false, varValue );
    pComboBox->setCurrentIndex( varValue.toInt( ) );
}

void MainWindow::SetItemValue( const QManipulateIniFile::IniFileNames iniFile,
                               const QManipulateIniFile::IniFileSections iniSection,
                               const QManipulateIniFile::IniFileSectionItems iniItem,
                               QLineEdit *pEdit )
{
    QVariant varValue = pEdit->text( );

    manipulateIniFile.IniFileValue( iniFile, iniSection, iniItem, true, varValue );
}

void MainWindow::SetItemValue( const QManipulateIniFile::IniFileNames iniFile,
                               const QManipulateIniFile::IniFileSections iniSection,
                               const QManipulateIniFile::IniFileSectionItems iniItem,
                               QComboBox *pComboBox)
{
    QVariant varValue = pComboBox->currentIndex( );

    manipulateIniFile.IniFileValue( iniFile, iniSection, iniItem, true, varValue );
}

void MainWindow::ReadPClientConfig( )
{
    QManipulateIniFile::IniFileNames iniFile = QManipulateIniFile::PlatformCentralClient;
    QManipulateIniFile::IniFileSections iniSection = QManipulateIniFile::IniNetwork;

    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpServerIP, ui->edtPClientTcpIP );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpServerPort, ui->edtPClientTcpPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpServerIP, ui->edtPClientUdpIP );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpServerPort, ui->edtPClientUdpPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastIP, ui->edtPClientUdpMulticastIP );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastPort, ui->edtPClientUdpMulticastPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpBroadcastPort, ui->edtPClientUdpBroadcastPort );
}

void MainWindow::ReadPServerConfig( )
{
    QManipulateIniFile::IniFileNames iniFile = QManipulateIniFile::PlatformCentralServer;
    QManipulateIniFile::IniFileSections iniSection = QManipulateIniFile::IniNetwork;

    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpServerPort, ui->edtPServerTcpPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpMaxConnection, ui->edtPServerTcpPendingConnections );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpServerPort, ui->edtPServerUdpPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpBroadcastPort, ui->edtPServerUdpBroadcastPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastIP, ui->edtPServerUdpMulticastIP );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastPort, ui->edtPServerUdpMulticastPort );

    iniSection = QManipulateIniFile::IniThread;

    GetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerSocketCount, ui->edtPServerPeerThreadSocketCount );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerStackSize, ui->edtPServerPeerThreadStackSize );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerReleaseInterval, ui->edtPServerPeerThreadReleaseInterval );

    iniSection = QManipulateIniFile::IniDatabase;

    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseType, ui->cbPServerDbType );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseHost, ui->edtPServerDbIP );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabasePort, ui->edtPServerDbPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseUser, ui->edtPServerDbUser );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabasePwd, ui->edtPServerDbPwd );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseSchema, ui->edtPServerDbName );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseThreadpoolMaxThreads, ui->edtPServerThreadpoolMaxThreads );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseThreadpoolThreadExpire, ui->edtPServerThreadpoolThreadsExpire );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseObjectReleaseInterval, ui->edtPServerDbObjReleaseInterval );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseObjectLifeTime, ui->edtPServerDbObjLifeTime );
}

void MainWindow::ReadPDataServerConfig( )
{
    QManipulateIniFile::IniFileNames iniFile = QManipulateIniFile::PlatformCentralDataReceiver;
    QManipulateIniFile::IniFileSections iniSection = QManipulateIniFile::IniNetwork;

    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpServerPort, ui->edtPDataServerTcpPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpMaxConnection, ui->edtPDataServerTcpPendingConnections );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpServerPort, ui->edtPDataServerUdpPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpBroadcastPort, ui->edtPDataServerUdpBroadcastPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastIP, ui->edtPDataServerUdpMulticastIP );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastPort, ui->edtPDataServerUdpMulticastPort );

    iniSection = QManipulateIniFile::IniThread;

    GetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerSocketCount, ui->edtPDataServerPeerThreadSocketCount );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerStackSize, ui->edtPDataServerPeerThreadStackSize );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerReleaseInterval, ui->edtPDataServerPeerThreadReleaseInterval );

    iniSection = QManipulateIniFile::IniDatabase;

    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseType, ui->cbPDataServerDbType );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseHost, ui->edtPDataServerDbIP );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabasePort, ui->edtPDataServerDbPort );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseUser, ui->edtPDataServerDbUser );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabasePwd, ui->edtPDataServerDbPwd );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseSchema, ui->edtPDataServerDbName );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseThreadpoolMaxThreads, ui->edtPDataServerThreadpoolMaxThreads );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseThreadpoolThreadExpire, ui->edtPDataServerThreadpoolThreadsExpire );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseObjectReleaseInterval, ui->edtPDataServerDbObjReleaseInterval );
    GetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseObjectLifeTime, ui->edtPDataServerDbObjLifeTime );
}

void MainWindow::ReadData( )
{
    ReadPClientConfig( );
    ReadPServerConfig( );
    ReadPDataServerConfig( );
}

void MainWindow::SavePClientConfig( )
{
    QManipulateIniFile::IniFileNames iniFile = QManipulateIniFile::PlatformCentralClient;
    QManipulateIniFile::IniFileSections iniSection = QManipulateIniFile::IniNetwork;

    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpServerIP, ui->edtPClientTcpIP );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpServerPort, ui->edtPClientTcpPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpServerIP, ui->edtPClientUdpIP );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpServerPort, ui->edtPClientUdpPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastIP, ui->edtPClientUdpMulticastIP );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastPort, ui->edtPClientUdpMulticastPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpBroadcastPort, ui->edtPClientUdpBroadcastPort );
}

void MainWindow::SavePServerConfig( )
{
    QManipulateIniFile::IniFileNames iniFile = QManipulateIniFile::PlatformCentralServer;
    QManipulateIniFile::IniFileSections iniSection = QManipulateIniFile::IniNetwork;

    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpServerPort, ui->edtPServerTcpPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpMaxConnection, ui->edtPServerTcpPendingConnections );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpServerPort, ui->edtPServerUdpPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpBroadcastPort, ui->edtPServerUdpBroadcastPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastIP, ui->edtPServerUdpMulticastIP );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastPort, ui->edtPServerUdpMulticastPort );

    iniSection = QManipulateIniFile::IniThread;

    SetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerSocketCount, ui->edtPServerPeerThreadSocketCount );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerStackSize, ui->edtPServerPeerThreadStackSize );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerReleaseInterval, ui->edtPServerPeerThreadReleaseInterval );

    iniSection = QManipulateIniFile::IniDatabase;

    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseType, ui->cbPServerDbType );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseHost, ui->edtPServerDbIP );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabasePort, ui->edtPServerDbPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseUser, ui->edtPServerDbUser );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabasePwd, ui->edtPServerDbPwd );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseSchema, ui->edtPServerDbName );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseThreadpoolMaxThreads, ui->edtPServerThreadpoolMaxThreads );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseThreadpoolThreadExpire, ui->edtPServerThreadpoolThreadsExpire );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseObjectReleaseInterval, ui->edtPServerDbObjReleaseInterval );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseObjectLifeTime, ui->edtPServerDbObjLifeTime );
}

void MainWindow::SavePDataServerConfig( )
{
    QManipulateIniFile::IniFileNames iniFile = QManipulateIniFile::PlatformCentralDataReceiver;
    QManipulateIniFile::IniFileSections iniSection = QManipulateIniFile::IniNetwork;

    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpServerPort, ui->edtPDataServerTcpPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkTcpMaxConnection, ui->edtPDataServerTcpPendingConnections );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpServerPort, ui->edtPDataServerUdpPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkUdpBroadcastPort, ui->edtPDataServerUdpBroadcastPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastIP, ui->edtPDataServerUdpMulticastIP );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::NetworkMulticastPort, ui->edtPDataServerUdpMulticastPort );

    iniSection = QManipulateIniFile::IniThread;

    SetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerSocketCount, ui->edtPDataServerPeerThreadSocketCount );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerStackSize, ui->edtPDataServerPeerThreadStackSize );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::ThreadPeerReleaseInterval, ui->edtPDataServerPeerThreadReleaseInterval );

    iniSection = QManipulateIniFile::IniDatabase;

    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseType, ui->cbPDataServerDbType );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseHost, ui->edtPDataServerDbIP );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabasePort, ui->edtPDataServerDbPort );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseUser, ui->edtPDataServerDbUser );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabasePwd, ui->edtPDataServerDbPwd );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseSchema, ui->edtPDataServerDbName );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseThreadpoolMaxThreads, ui->edtPDataServerThreadpoolMaxThreads );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseThreadpoolThreadExpire, ui->edtPDataServerThreadpoolThreadsExpire );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseObjectReleaseInterval, ui->edtPDataServerDbObjReleaseInterval );
    SetItemValue( iniFile, iniSection, QManipulateIniFile::DatabaseObjectLifeTime, ui->edtPDataServerDbObjLifeTime );
}

void MainWindow::SaveData( )
{
    SavePClientConfig( );
    SavePServerConfig( );
    SavePDataServerConfig( );
}

void MainWindow::SetDbType( )
{
    QStringList lstDbType;

    lstDbType << "DbMySQL" <<
                             "DbSQLServer" <<
                             "DbSybase" <<
                             "DbOracle" <<
                             "DbDB2" <<
                             "DbSQLlite" <<
                             "DbBDB" <<
                             "DbAccess" <<
                             "DbPostgreSQL";

    ui->cbPServerDbType->insertItems( 0, lstDbType );
    ui->cbPDataServerDbType->insertItems( 0, lstDbType );
}

void MainWindow::on_btnSave_clicked()
{
    SaveData( ); // Save All data
}

void MainWindow::on_btnClose_clicked()
{
    close( );
}
