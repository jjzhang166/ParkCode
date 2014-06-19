#include "Header/toolbardockwidget.h"
#include "ui_toolbardockwidget.h"

CToolbarDockWidget::CToolbarDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CToolbarDockWidget)
{
    ui->setupUi(this);
}

CToolbarDockWidget::~CToolbarDockWidget()
{
    delete ui;
}

void CToolbarDockWidget::closeEvent( QCloseEvent *event )
{
    event->ignore( );
}
