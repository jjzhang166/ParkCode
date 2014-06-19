#include "dlgpassdetail.h"
#include "ui_dlgpassdetail.h"
#include "Common/commonfunction.h"

CDlgPassDetail::CDlgPassDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgPassDetail)
{
    ui->setupUi(this);
    ui->lblTitle->setText( windowTitle( ) );
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CDlgPassDetail::~CDlgPassDetail()
{
    delete ui;
}

void CDlgPassDetail::resizeEvent( QResizeEvent *event )
{
    QWidget::resizeEvent( event );

    QString strFile = statusTip( );
    QPixmap bgimage( strFile );
    QPalette pal( palette( ) );
    pal.setBrush( QPalette::Window, QBrush( bgimage.scaled( event->size( ),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation ) ) );
    setPalette(pal);
}

void CDlgPassDetail::on_btnQuery_clicked()
{

}

void CDlgPassDetail::on_lblClose_linkActivated(QString)
{
    close( );
}
