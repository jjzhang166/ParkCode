#include "dlgreadcardid.h"
#include "ui_dlgreadcardid.h"
#include "Common/commonfunction.h"

CDlgReadCardID::CDlgReadCardID(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgReadCardID)
{
    ui->setupUi(this);
    CCommonFunction::ControlSysMenu( *this );
}

CDlgReadCardID::~CDlgReadCardID()
{
    delete ui;
}

void CDlgReadCardID::on_btnDeleteAll_clicked()
{
    ui->lstCardID->clear();
}

void CDlgReadCardID::on_btnDeleteSingle_clicked()
{
    QListWidgetItem* pItem = ui->lstCardID->takeItem( ui->lstCardID->currentRow( ) );
    if ( NULL != pItem ) {
        delete pItem;
    }
}

QStringList& CDlgReadCardID::GetCardNoLst( )
{
    return lstCardNo;
}

void CDlgReadCardID::on_btnOK_clicked()
{
    for ( int nRow = 0; nRow < ui->lstCardID->count( ); nRow++ ) {
        lstCardNo << "'" + ui->lstCardID->item( nRow )->text( ) + "'";
    }

    close( );
    setResult( CDlgReadCardID::Accepted );
}

QLineEdit* CDlgReadCardID::GetEditCntrl( )
{
    return ui->edtCardID;
}

void CDlgReadCardID::on_btnCancel_clicked()
{
    close( );
    setResult( CDlgReadCardID::Rejected );
}

void CDlgReadCardID::on_edtCardID_textChanged(const QString &arg1)
{
    if ( 0 == ui->lstCardID->findItems( arg1, Qt::MatchFixedString ).count( ) ) {
        ui->lstCardID->addItem( arg1 );
    }
}
