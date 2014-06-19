#include "cdlgmonthquery.h"
#include "ui_cdlgmonthquery.h"
#include <QDate>
#include <QDebug>

CDlgMonthQuery::CDlgMonthQuery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgMonthQuery)
{
    ui->setupUi(this);
}

CDlgMonthQuery::~CDlgMonthQuery()
{
    delete ui;
}

void CDlgMonthQuery::on_btnOK_clicked()
{
    close( );
    setResult( QDialog::Accepted );
}

void CDlgMonthQuery::GetParams( QStringList &lstParams )
{
    lstParams.clear( );
    lstParams << QString::number( ui->cbxType->currentIndex( ) )
              << ui->dtStart->text( )
              << ui->dtEnd->text( );
}

void CDlgMonthQuery::SetParams( QStringList &lstParams )
{
    if ( 0 == lstParams.count( ) ) {
        ui->dtStart->setDate( QDate::currentDate( ) );
        ui->dtEnd->setDate( QDate::currentDate( ) );
    } else if ( 3 <= lstParams.count( ) ){
        int nIndex = lstParams.at( 0 ).toInt( );
        ui->cbxType->setCurrentIndex( nIndex );


        QDate date = QDate::fromString( lstParams.at( 1 ), "yyyy-MM-dd" );
        qDebug( ) << date.toString( "yyyy-MM-dd" ) << endl;
        ui->dtStart->setDate( date );

        date = QDate::fromString( lstParams.at( 2 ), "yyyy-MM-dd" );
        ui->dtEnd->setDate( date );
    }
}

void CDlgMonthQuery::on_btnCancel_clicked()
{
    close( );
    setResult( QDialog::Rejected );
}
