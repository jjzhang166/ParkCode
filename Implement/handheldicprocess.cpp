#include "Header/handheldicprocess.h"
#include "ui_handheldicprocess.h"

CHandheldICProcess::CHandheldICProcess(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CHandheldICProcess)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
}

CHandheldICProcess::~CHandheldICProcess()
{
    delete ui;
}

void CHandheldICProcess::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}
