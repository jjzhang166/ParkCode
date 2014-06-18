#include "dlgstartupprocess.h"
#include "ui_dlgstartupprocess.h"

#include "Common/commonfunction.h"

#include <windows.h>

CDlgStartupprocess* CDlgStartupprocess::pFrame = NULL;

CDlgStartupprocess::CDlgStartupprocess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgStartupprocess)
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint );
}

CDlgStartupprocess::~CDlgStartupprocess()
{
    delete ui;
}

CDlgStartupprocess* CDlgStartupprocess::GetFrame( QWidget* parent )
{
    if ( NULL == pFrame ) {
        pFrame = new CDlgStartupprocess( parent );
        //CCommonFunction::MySetWindowPos( pFrame );
    }

    return pFrame;
}

void CDlgStartupprocess::FreeFrame( )
{
    if ( NULL != pFrame ) {
        delete pFrame;
        pFrame = NULL;
    }
}

void CDlgStartupprocess::UpdateInfo( QString strInfo )
{
    ui->lblInfo->setText( strInfo );
}
