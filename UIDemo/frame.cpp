#include "frame.h"
#include "ui_frame.h"
#include <windows.h>

Frame::Frame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Frame)
{
    ui->setupUi(this);

    BOOL bRet = FALSE;
    HRGN hBtnRgn = CreateEllipticRgn( 50, 50, 200, 200);
    bRet = SetWindowRgn( winId( ), hBtnRgn, true );
}

Frame::~Frame()
{
    delete ui;
}
