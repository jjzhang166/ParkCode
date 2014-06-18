#include "monitor.h"
#include "ui_monitor.h"
#include <QMessageBox>
#include <QMenu>
#include "frame.h"

CMonitor::CMonitor(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CMonitor)
{
    ui->setupUi(this);
}

CMonitor::~CMonitor()
{
    delete ui;
}

void CMonitor::on_pushButton_clicked()
{
    QMessageBox a( this );
    a.addButton( QMessageBox::Ok );
    a.exec( );
}
