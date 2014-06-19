#include "dlgabout.h"
#include "ui_dlgabout.h"
#include "Common/commonfunction.h"

CDlgAbout::CDlgAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgAbout)
{
    ui->setupUi(this);
    //CCommonFunction::ControlSysMenu( *this );
    LoadInfo( );
}

CDlgAbout::~CDlgAbout()
{
    delete ui;
}

void CDlgAbout::LoadInfo( )
{
    QSettings* pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );

    ui->lblCompany->setText(pSettings->value( "About/Company", "" ).toString( ) );
    ui->lblVersion->setText(pSettings->value( "About/Version", "" ).toString( ) );
    ui->lblTel->setText(pSettings->value( "About/Tel", "" ).toString( ) );
    ui->lblFax->setText(pSettings->value( "About/Fax", "" ).toString( ) );
}
