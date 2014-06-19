#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitList( );
    InitSettings( );
    ReadConfig( );
}

MainWindow::~MainWindow()
{
    delete pSettings;
    delete ui;
}

void MainWindow::InitList( )
{
    QString strSection = "Administrator";

    ui->sbAdminServerPort->setWhatsThis( strSection );
    lstSpinBox.append( ui->sbAdminServerPort );
    ui->edtAdminServerIP->setWhatsThis( strSection );
    lstLineEdit.append( ui->edtAdminServerIP );

    strSection = "ClientControl";
    ui->sbClientServerPort->setWhatsThis( strSection );
    lstSpinBox.append( ui->sbClientServerPort );
    ui->edtClientServerIP->setWhatsThis( strSection );
    lstLineEdit.append( ui->edtClientServerIP );

    strSection = "Server";
    ui->sbListenPort->setWhatsThis( strSection );
    lstSpinBox.append( ui->sbListenPort );
    ui->sbMaxPendingConnections->setWhatsThis( strSection );
    lstSpinBox.append( ui->sbMaxPendingConnections );
    ui->sbMaxSleepTimeEachServerThread->setWhatsThis( strSection );
    lstSpinBox.append( ui->sbMaxSleepTimeEachServerThread );
    ui->sbServerThreadCountEachDataParser->setWhatsThis( strSection );
    lstSpinBox.append( ui->sbServerThreadCountEachDataParser );
    ui->sbSocketCountEachServerThread->setWhatsThis( strSection );
    lstSpinBox.append( ui->sbSocketCountEachServerThread );
}

void MainWindow::InitSettings( )
{
    pCodec = QCommonLibrary::GetTextCodec( );
    QString& strFileName = QCommonLibrary::GetConfigFileName( );
    pSettings = new QSettings( strFileName, QSettings::IniFormat );
    pSettings->setIniCodec( pCodec );
}

void MainWindow::ReadConfig( )
{
    QString strServerKey = "Server/%1";

    QString strValue = pSettings->value( strServerKey.arg( "ListenPort" ), 6000 ).toString( );
    ui->sbListenPort->setValue( strValue.toInt( ) );

    QString strKey = "%1/%2";

    foreach ( QSpinBox* pWidget, lstSpinBox ) {
        pWidget->setValue( pSettings->value( strKey.arg(
                                 pWidget->whatsThis( ),
                                 pWidget->objectName( ) ),
                          "0" ).toInt( ) );
    }

    foreach ( QLineEdit* pWidget, lstLineEdit ) {
        pWidget->setText( pSettings->value( strKey.arg(
                                 pWidget->whatsThis( ),
                                 pWidget->objectName( ) ),
                                            "127.0.0.1" ).toString( ) );
    }
}

void MainWindow::WriteConfig( )
{
    QString strKey = "%1/%2";
    QString strKeyValue;

    foreach ( QSpinBox* pWidget, lstSpinBox ) {
        strKeyValue = strKey.arg( pWidget->whatsThis( ), pWidget->objectName( ) );
        pSettings->setValue( strKeyValue, pWidget->value( ) );

        strKeyValue += ":" + pWidget->text( );
        QCommonLibrary::PrintLog( strKeyValue );
    }

    foreach ( QLineEdit* pWidget, lstLineEdit ) {
        strKeyValue = strKey.arg( pWidget->whatsThis( ), pWidget->objectName( ) );
        pSettings->setValue( strKeyValue, pWidget->text( ) );

        strKeyValue += ":" + pWidget->text( );
        QCommonLibrary::PrintLog( strKeyValue );
    }
}

void MainWindow::on_btnOK_clicked()
{
    WriteConfig( );
}

void MainWindow::on_btnCancel_clicked()
{
    close( );
}
