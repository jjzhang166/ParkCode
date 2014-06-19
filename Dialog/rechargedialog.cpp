#include "Dialog/rechargedialog.h"
#include "ui_rechargedialog.h"
#include "Common/logicinterface.h"

CRechargeDialog::CRechargeDialog( QDateTime& dtEnd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRechargeDialog)
{
    ui->setupUi(this);
    //QDateTime dtCurrent = QDateTime::currentDateTime( );
    ui->dtStart->setDateTime( dtEnd );

    dtEnd = dtEnd.addMonths( 1 );
    ui->dtEnd->setDateTime( dtEnd );

    CCommonFunction::ControlSysMenu( *this );
}

CRechargeDialog::~CRechargeDialog()
{
    delete ui;
}

void CRechargeDialog::GetCarModel( QString &strCardID )
{
    QString strSql = QString( "Select distinct carmodel from carinfo where cardindex = '%1'" ).arg( strCardID );
    QStringList lstRows;
    int nRows = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );

    if ( 0 < nRows ) {
        ui->cbxCarModel->insertItems( 0, lstRows );
    }
}

void CRechargeDialog::on_btnOk_clicked()
{
    close( );
    setResult( QDialog::Accepted );
}

void CRechargeDialog::GetValue( QStringList& lstRows )
{
    QDateTime dtStart = ui->dtStart->dateTime( );
    QString strText;
    CCommonFunction::DateTime2String( dtStart, strText );
    lstRows << QVariant( ui->spAmount->value( ) ).toString( )
            << ui->edtDays->text( )
            << strText
            << "ÔÂ×â¿¨Ðø·Ñ";
}

void CRechargeDialog::on_btnCancel_clicked()
{
    close( );
    setResult( QDialog::Rejected );
}

QDateTime CRechargeDialog::GetEndDateTime( )
{
    return ui->dtEnd->dateTime( );
}

void CRechargeDialog::CalculateDays( QDateTime dtStart, QDateTime dtEnd )
{
    dtEnd.setTime( QTime( 0, 0 ) );
    dtStart.setTime( QTime( 0, 0 ) );

    uint nSeconds = dtEnd.toTime_t( ) - dtStart.toTime_t( );
    uint nDay = 24 * 60 * 60;
    nDay = nSeconds / nDay;

    ui->edtDays->setText( QString( "%1" ).arg( nDay ) );
}

void CRechargeDialog::on_dtStart_dateTimeChanged(QDateTime date)
{
    CalculateDays( date, ui->dtEnd->dateTime( ) );
}

void CRechargeDialog::on_dtEnd_dateTimeChanged(QDateTime date)
{
    CalculateDays( ui->dtStart->dateTime( ), date );
}
