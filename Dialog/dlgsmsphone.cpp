#include "dlgsmsphone.h"
#include "ui_dlgsmsphone.h"
#include "Common/logicinterface.h"

CDlgSmsPhone::CDlgSmsPhone(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgSmsPhone)
{
    ui->setupUi(this);

    CCommonFunction::ControlSysMenu( *this );
    FillData( );
}

CDlgSmsPhone::~CDlgSmsPhone()
{
    delete ui;
}

void CDlgSmsPhone::GetPhoneList( QStringList &lstData )
{
    lstData.clear( );

    int nCount = ui->tableWidget->rowCount( );
    if ( 0 == nCount ) {
        return;
    }

    int nColumn = ui->tableWidget->columnCount( );
    QTableWidgetItem* pItem = NULL;

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        pItem = ui->tableWidget->item( nIndex, nColumn - 1 );
        if ( pItem->checkState( ) == Qt::Unchecked ) {
            continue;
        }

        pItem = ui->tableWidget->item( nIndex, nColumn - 2 );
        lstData << pItem->text( );
    }
}

void CDlgSmsPhone::FillData( )
{
    QString strSql = "select a.cardno, b.carcp, c.username, c.userphone from \
            monthcard as a, carinfo as b, userinfo as c \
            where a.cardno = b.cardindex and a.cardno = c.cardindex and \
            c.userphone <> 'δ֪' and '1' = LEFT( c.userphone, 1 ) \
            and 11 = CHAR_LENGTH( c.userphone )";

    QStringList lstRows;
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
    QTableWidgetItem* pItem = NULL;

    for ( int nIndex = 0; nIndex < lstRows.size( ); nIndex += 4 ) {
       ui->tableWidget->insertRow( 0 );

        for ( int nCol = 0; nCol < 5; nCol++ ) {
            if ( 4 != nCol ) {
                pItem = new QTableWidgetItem( lstRows[ nIndex + nCol ] );
            } else {
                pItem = new QTableWidgetItem(  );
                pItem->setCheckState( Qt::Unchecked );
            }

            ui->tableWidget->setItem( 0, nCol, pItem );
            pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        }
    }
}

void CDlgSmsPhone::Select( bool bAll )
{
    int nCount = ui->tableWidget->rowCount( );
    if ( 0 == nCount ) {
        return;
    }

    int nColumn = ui->tableWidget->columnCount( );
    QTableWidgetItem* pItem = NULL;

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        pItem = ui->tableWidget->item( nIndex, nColumn - 1 );
        pItem->setCheckState( bAll ? Qt::Checked : Qt::Unchecked );
    }
}

void CDlgSmsPhone::on_btnAllSelect_clicked()
{
    Select( true );
}

void CDlgSmsPhone::on_btnAllUnselect_clicked()
{
    Select( false );
}

void CDlgSmsPhone::on_btnOK_clicked()
{
    close( );
}

void CDlgSmsPhone::on_tableWidget_cellClicked(int row, int column)
{
    if ( 4 != column ) { // 4 - column
        return;
    }

    QTableWidgetItem* pItem = ui->tableWidget->item( row, column );
    if ( NULL == pItem ) {
        return;
    }

    Qt::CheckState state = pItem->checkState( );

    if ( Qt::Unchecked == state ) {
        state =  Qt::Checked;
    } else if ( Qt::Checked == state ) {
        state = Qt::Unchecked;
    }

    pItem->setCheckState( state );
}
