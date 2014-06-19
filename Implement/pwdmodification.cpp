#include "Header/pwdmodification.h"
#include "ui_pwdmodification.h"

CPwdModification::CPwdModification(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CPwdModification)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
}

CPwdModification::~CPwdModification()
{
    delete ui;
}

void CPwdModification::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CPwdModification::resizeEvent( QResizeEvent* )
{
    CalculatePos( );
}

void CPwdModification::CalculatePos( )
{
    QRect rectWnd = this->geometry( );

    QString strName = "widget";
    QWidget* pWg = findChild< QWidget* >( strName );
    QRect rectWg = pWg->geometry( );
    pWg->setGeometry( ( rectWnd.width( ) - rectWg.width( ) -2 ) / 2,
                      ( rectWnd.height( )  - rectWg.height( ) -2 ) / 2,
                      rectWg.width( ), rectWg.height( ) );
}
