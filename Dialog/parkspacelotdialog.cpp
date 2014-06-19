#include "Dialog/parkspacelotdialog.h"
#include "ui_parkspacelotdialog.h"
#include <QRadioButton>
#include <QVBoxLayout>
#include "Common/commonfunction.h"

CParkSpaceLotDialog::CParkSpaceLotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CParkSpaceLotDialog)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader( )->hide( );
    ui->tableWidget->verticalHeader( )->hide( );

    ui->tableWidget->setColumnWidth( 0, ui->tableWidget->width( ) );

    strParkName = "";

    CCommonFunction::ControlSysMenu( *this );
    CCommonFunction::SetWindowIcon( this );
}

CParkSpaceLotDialog::~CParkSpaceLotDialog()
{
    delete ui;
}

void CParkSpaceLotDialog::GetParkName( QString& strName )
{
    strName = strParkName;
}

void CParkSpaceLotDialog::RadioClick( )
{
    QObject* pSender = sender( );

    if ( NULL != pSender && pSender->inherits( "QRadioButton" ) ) {
        QRadioButton* pRB = dynamic_cast< QRadioButton* >( pSender );
        strParkName = pRB->text( );
        if ( 1 == pRB->parent( )->children( ).count( ) ) {
            pRB->setChecked( true );
        }
    }
}

void CParkSpaceLotDialog::GetCanAddress( QVector< char >& vecCan )
{
    vecCan.clear( );

    int nRows = ui->tableWidget->rowCount( );

    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        if ( Qt::Checked == ui->tableWidget->item( nIndex, 0 )->checkState( ) ) {
            QString strCan = ui->tableWidget->item( nIndex, 0 )->text( ).split( "=" )[ 1 ];
            char cCan = ( char ) strCan.toShort( );
            vecCan.append( cCan );
        }
    }
}

void CParkSpaceLotDialog::GetCanAddress( QStringList& lstCan )
{
    lstCan.clear( );

    int nRows = ui->tableWidget->rowCount( );

    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        if ( Qt::Checked == ui->tableWidget->item( nIndex, 0 )->checkState( ) ) {
            QString strCan = ui->tableWidget->item( nIndex, 0 )->text( ).split( "=" )[ 1 ];
            lstCan << strCan;
        }
    }
}

void CParkSpaceLotDialog::InitDlg( bool bChannel, QStringList& lstRows, bool bEneter, QStringList& lstCan )
{
    int nIndex = 0;
    int nItems = lstRows.count( );
    QTableWidgetItem* pItem = NULL;

    if ( 0 == nItems ) {
        return;
    }

    if ( bChannel ) {
        ui->tableWidget->setRowCount( nItems / 2 );
        while ( nIndex < nItems ) {
            QString& strCan = lstRows[ nIndex + 1 ];
            bool bContain = lstCan.contains( strCan );
            pItem = new QTableWidgetItem( lstRows[ nIndex ]  + "=" + strCan );
            ui->tableWidget->setItem( nIndex / 2, 0, pItem );
            pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
            pItem->setCheckState( bContain ? Qt::Checked : Qt::Unchecked );
            nIndex += 2;
        }

        if ( 2 == nItems ) {
            ui->tableWidget->item( 0, 0 )->setCheckState( Qt::Checked );
        }
        setWindowTitle( QString( "所有%1口通道" ).arg( bEneter ? "入" : "出" ) );
    } else {
        setWindowTitle( QString( "所有停车场" ) );
        ui->tableWidget->setVisible( bChannel );
        QVBoxLayout *vbox = new QVBoxLayout();

        QRadioButton* prdx;
        while ( nIndex < nItems ) {
            prdx = new QRadioButton( lstRows[ nIndex ] );
            connect( prdx, SIGNAL( clicked( ) ), this, SLOT( RadioClick( ) ) );

            vbox->addWidget( prdx );
            vbox->addStretch( 1 );
            nIndex++;
        }

        ui->gb->setLayout( vbox );

        QObjectList oList = ui->gb->children( );
        prdx = dynamic_cast< QRadioButton* >( oList.at( 2 ) );
        prdx->setChecked( true );
    }
}

void CParkSpaceLotDialog::on_btnOk_clicked()
{
    close( );
    setResult( CParkSpaceLotDialog::Accepted );
}

void CParkSpaceLotDialog::on_btnCancel_clicked()
{
    close( );
    setResult( CParkSpaceLotDialog::Rejected );
}
