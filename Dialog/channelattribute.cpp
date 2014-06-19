#include "channelattribute.h"
#include "ui_channelattribute.h"
#include "Common/commonfunction.h"

CChannelAttribute::CChannelAttribute(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CChannelAttribute)
{
    ui->setupUi(this);

    CCommonFunction::ControlSysMenu( *this );
    CCommonFunction::SetWindowIcon( this );
}

CChannelAttribute::~CChannelAttribute()
{
    delete ui;
}

void CChannelAttribute::on_btnOk_clicked()
{
    close( );
    setResult( CChannelAttribute::Accepted );
}

void CChannelAttribute::on_btnCancel_clicked()
{
    close( );
}

void CChannelAttribute::CANAddr( int &nAddr, bool bGet )
{
    if ( bGet ) {
        nAddr = ui->spAddr->value( );
    } else {
        ui->spAddr->setValue( nAddr );
    }
}

void CChannelAttribute::ChannelName( QString &strName, bool bGet )
{
    if ( bGet ) {
        strName = ui->edtName->text( );
    } else {
        ui->edtName->setText( strName );
    }
}

void CChannelAttribute::HostIP( QString &strIP, bool bGet )
{
    if ( bGet ) {
        strIP = ui->edtIP->text( );
    } else {
        ui->edtIP->setText( strIP );
    }
}

void CChannelAttribute::IPCIP( QString &strIP, bool bGet )
{
    if ( bGet ) {
        strIP = ui->edtIPCIP->text( );
    } else {
        ui->edtIPCIP->setText( strIP );
    }
}
