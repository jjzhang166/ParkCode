#include "Header/discountsummaryreport.h"
#include "ui_discountsummaryreport.h"

CDiscountSummaryReport::CDiscountSummaryReport(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CDiscountSummaryReport)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
}

CDiscountSummaryReport::~CDiscountSummaryReport()
{
    delete ui;
}

void CDiscountSummaryReport::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}
