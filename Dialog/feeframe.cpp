#include "feeframe.h"
#include "ui_feeframe.h"

CFeeFrame::CFeeFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CFeeFrame)
{
    ui->setupUi(this);
}

CFeeFrame::~CFeeFrame()
{
    delete ui;
}
