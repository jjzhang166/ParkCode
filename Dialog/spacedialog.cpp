#include "Dialog\spacedialog.h"
#include "ui_spacedialog.h"
#include "Common/commonfunction.h"

CSpaceDialog::CSpaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSpaceDialog)
{
    ui->setupUi(this);

    CCommonFunction::ControlSysMenu( *this );
    CCommonFunction::SetWindowIcon( this );
    ui->spNocardSpace->setEnabled( false );
}

CSpaceDialog::~CSpaceDialog()
{
    delete ui;
}

void CSpaceDialog::SpaceNumber( int &nSpace, bool bGet )
{
    if ( bGet ) {
        nSpace = ui->spSpace->value( );
    } else {
        ui->spSpace->setValue( nSpace );
    }
}

void CSpaceDialog::SpaceNocardNumber( int &nSpace, bool bGet )
{
    if ( bGet ) {
        nSpace = ui->spNocardSpace->value( );
    } else {
        ui->spNocardSpace->setEnabled( true );
        ui->spNocardSpace->setValue( nSpace );
    }
}

void CSpaceDialog::ParkName( QString &strName, bool bGet )
{
    if ( bGet ) {
        strName = ui->edtName->text( );
    } else {
        ui->edtName->setText( strName );
    }
}

void CSpaceDialog::on_btnOK_clicked()
{
    close( );
    setResult( CSpaceDialog::Accepted );
}

void CSpaceDialog::on_pushButton_2_clicked()
{
    close( );
}
