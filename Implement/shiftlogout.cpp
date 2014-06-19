#include "Header/shiftlogout.h"
#include "ui_shiftlogout.h"

#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QDockWidget>

CShiftLogout::CShiftLogout(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CShiftLogout)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
}

CShiftLogout::~CShiftLogout()
{
    delete ui;
}

void CShiftLogout::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}
