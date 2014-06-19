#include "Header/printyearlyreport.h"
#include "ui_printyearlyreport.h"

CPrintYearlyReport::CPrintYearlyReport(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CPrintYearlyReport)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    setWindowFlags( Qt::FramelessWindowHint );
}

CPrintYearlyReport::~CPrintYearlyReport()
{
    delete ui;
}

void CPrintYearlyReport::closeEvent( QCloseEvent *event )
{
    //pParent->ControlChild( event, this );
}

void CPrintYearlyReport::DisplayPicture( QString &strFile )
{
    QPixmap pixPic( strFile );
    ui->lblPicture->setPixmap( pixPic );
}
