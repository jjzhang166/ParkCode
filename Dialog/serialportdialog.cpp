#include "Dialog/serialportdialog.h"
#include "ui_serialportdialog.h"
#include "Common/commonfunction.h"

CSerialPortDialog::CSerialPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSerialPortDialog)
{
    ui->setupUi(this);

    ui->cbxPort->setCurrentIndex( 0 );
    ui->cbxBaud->setCurrentIndex( 19 ); // 115200
    ui->cbxData->setCurrentIndex( 3 );
    ui->cbxParity->setCurrentIndex( 0 );
    ui->cbxStop->setCurrentIndex( 0 );
    ui->cbxFlow->setCurrentIndex( 0 );

    CCommonFunction::ControlSysMenu( *this );
}

CSerialPortDialog::~CSerialPortDialog()
{
    delete ui;
}

void CSerialPortDialog::GetValue( QStringList &cfgStream, bool bInit )
{
    if ( !bInit ) {
    cfgStream << QVariant( ui->cbxPort->currentIndex( ) ).toString( )
              << QVariant( ui->cbxBaud->currentIndex( ) ).toString( )
              << QVariant( ui->cbxData->currentIndex( ) ).toString( )
              << QVariant( ui->cbxParity->currentIndex( ) ).toString( )
              << QVariant( ui->cbxStop->currentIndex( ) ).toString( )
              << QVariant( ui->cbxFlow->currentIndex( ) ).toString( );
    } else {
        ui->cbxPort->setCurrentIndex( cfgStream[ 0 ].toInt( ) );
        ui->cbxBaud->setCurrentIndex( cfgStream[ 1 ].toInt( ) );
        ui->cbxData->setCurrentIndex( cfgStream[ 2 ].toInt( ) );
        ui->cbxParity->setCurrentIndex( cfgStream[ 3 ].toInt( ) );
        ui->cbxStop->setCurrentIndex( cfgStream[ 4 ].toInt( ) );
        ui->cbxFlow->setCurrentIndex( cfgStream[ 5 ].toInt( ) );
    }
}

void CSerialPortDialog::on_btnOk_clicked()
{
    close( );
    accept( );
}

void CSerialPortDialog::on_btnCancel_clicked()
{
    close( );
    reject( );
}
