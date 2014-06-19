#include "Header/picturecontrast.h"
#include "ui_picturecontrast.h"

CPictureContrast::CPictureContrast( QWidget* mainWnd, QWidget *parent ) :
    QFrame(parent),
    ui(new Ui::CPictureContrast)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
}

CPictureContrast::~CPictureContrast()
{
    delete ui;
}

void CPictureContrast::closeEvent( QCloseEvent *event )
{
    event->ignore( );
    //setVisible( false );
}

void CPictureContrast::showEvent(QShowEvent *)
{
}

void CPictureContrast::on_btnImg1_clicked()
{

}

void CPictureContrast::on_btnImg2_clicked()
{

}

void CPictureContrast::on_btnImg3_clicked()
{

}

void CPictureContrast::on_btnImg4_clicked()
{

}

void CPictureContrast::on_btnPass_clicked()
{
#if false
    edtCardID
    edtOwner
    edtEnterChannel
    edtStayTime
    edtCardNumber
    edtRemainder
    edtEnterTime
    spCharge
    edtCardType
    edtExpiration
    edtLeaveChannel
    edtVechileType
    edtLeaveTime
    edtVechileID
    edtComment

    btnPass
#endif
}
