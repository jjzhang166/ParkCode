#include "qdlgdevice.h"
#include "ui_qdlgdevice.h"
#include <QDebug>

QDlgDevice::QDlgDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDlgDevice)
{
    ui->setupUi(this);
    nDeviceIndex= 0;
}

QDlgDevice::~QDlgDevice()
{
    delete ui;
}

int QDlgDevice::GetDeviceIndex( )
{
    return nDeviceIndex;
}

void QDlgDevice::AddDevice( QStringList &lstDevice )
{
    ui->listWidget->addItems( lstDevice );
}

void QDlgDevice::on_listWidget_doubleClicked(const QModelIndex &index)
{
    nDeviceIndex = index.row( );
    close( );

    setResult( QDlgDevice::Accepted );
}
