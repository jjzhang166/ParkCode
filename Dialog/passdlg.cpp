#include "Dialog/passdlg.h"
#include "ui_passdlg.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"

CPassDlg::CPassDlg(bool bEnter, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPassDlg)
{
    ui->setupUi(this);
    bDirection =  bEnter;
    CCommonFunction::ControlSysMenu( *this );


    int nIndex = 0;
    QString strSql = QString ( "Select distinct shebeiname, shebeiadr From roadconerinfo \
                               where video1ip ='%1' and shebeiadr % 2 %2= 0" ).arg(
                                       CCommonFunction::GetHostIP( ), bEnter ? "!" : "" );
    QStringList lstRows;
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
    int nItems = lstRows.count( );

    if ( 0 == nItems ) {
        return;
    }

    while ( nIndex < nItems ) {
        ui->cbxCan->insertItem( nIndex, lstRows[ nIndex ], lstRows[ nIndex + 1 ] );
        nIndex += 2;
    }
}

CPassDlg::~CPassDlg()
{
    delete ui;
}

bool CPassDlg::IsShow( )
{
    return 1 < ui->cbxCan->count( );
}

char CPassDlg::GetCanAddress( )
{
    char cCan = 0;
    if ( -1 != ui->cbxCan->currentIndex( ) ) {
        cCan = ( char ) ui->cbxCan->itemData( ui->cbxCan->currentIndex( ) ).toInt( );
    }

    return cCan;
}

void CPassDlg::closeEvent(QCloseEvent *e)
{
    if ( e->spontaneous( ) ) {
        e->ignore( );
    }
}

void CPassDlg::on_btnOk_clicked( )
{
    close( );
    setResult( CPassDlg::Accepted );
}

void CPassDlg::on_btnCancel_clicked()
{
    close( );
    setResult( CPassDlg::Rejected );
}
