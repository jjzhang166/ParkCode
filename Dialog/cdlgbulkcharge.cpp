#include "cdlgbulkcharge.h"
#include "ui_cdlgbulkcharge.h"
#include "Common/logicinterface.h"

CDlgBulkCharge::CDlgBulkCharge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgBulkCharge)
{
    ui->setupUi(this);
    CCommonFunction::ControlSysMenu( *this );
    GetUnit( );
    InitUI( );
}

CDlgBulkCharge::~CDlgBulkCharge()
{
    delete ui;
}

void CDlgBulkCharge::InitUI( )
{
    QDate dDate = QDate::currentDate( );

    ui->dtEndStart->setDate( dDate );

    dDate = dDate.addMonths( 1 );
    ui->dtEndEnd->setDate( dDate );
    ui->dtNewEnd->setDate( dDate );
}

void CDlgBulkCharge::on_btnCancel_clicked()
{
    close( );
    setResult( QDialog::Rejected );
}

void CDlgBulkCharge::GetUnit( )
{
    ui->cbxUnit->clear( );

    QString strSQL = "Select distinct UserCorp From UserInfo";
    QStringList lstRows;
    int nRows = CLogicInterface::GetInterface( )->ExecuteSql( strSQL, lstRows );

    lstRows.removeAll( "未知" );
    nRows = lstRows.size( );

    if ( 0 >= nRows ) {
        ui->cbxUnit->addItem( "无有效单位", false );
    } else {
        foreach ( const QString& str, lstRows ) {
            ui->cbxUnit->addItem( str, true );
        }
    }
}

void CDlgBulkCharge::on_btnOk_clicked()
{
    QString strText = QString( "符合条件的所有月租卡截至日期都将被修改为【%1】" ).arg(
                ui->dtNewEnd->text( ) );
    if ( QMessageBox::Cancel ==
         CCommonFunction::MsgBox( NULL, "提示", strText, QMessageBox::Question ) ) {
        return;
    }

    if ( !SaveData( ) ) {
        return;
    }

    close( );
    setResult( QDialog::Accepted );
}

bool CDlgBulkCharge::SaveData( )
{
    QString strSQL = "Update MonthCard set EndTime = '%1 23:59:59' Where %2";
    QString strWhere = "";
    bool bRet = false;

    if ( ui->rdbSelfNo->isChecked( ) ) {
        if ( ui->edtSelfStart->text( ).isEmpty( ) ||
             ui->edtSelfEnd->text( ).isEmpty( ) ) {
            CCommonFunction::MsgBox( NULL, "提示", "请输入完整的起始自编号范围。", QMessageBox::Information );
            return bRet;
        }

        strWhere = QString( "CardSelfNo between '%1' and '%2'" ).arg(
                    ui->edtSelfStart->text( ),
                    ui->edtSelfEnd->text( ) );
    } else if ( ui->rdbEndDate->isChecked( ) ) {
        if ( ui->dtEndStart->date( ) > ui->dtEndEnd->date( ) ) {
            CCommonFunction::MsgBox( NULL, "提示", "请输入正确的截至时间范围。", QMessageBox::Information );
            return bRet;
        }

        strWhere = QString( "EndTime between '%1 00:00:00' and '%2 23:59:59'" ).arg(
                    ui->dtEndStart->text( ),
                    ui->dtEndEnd->text( ) );
    } else if ( ui->rdbUnit->isChecked( ) ) {
        if ( !ui->cbxUnit->itemData( ui->cbxUnit->currentIndex( ) ).toBool( ) ) {
            CCommonFunction::MsgBox( NULL, "提示", "无有效单位。", QMessageBox::Information );
            return bRet;
        }

        strWhere = QString( "CardNo in( Select Distinct CardIndex From UserInfo Where UserCorp = '%1' )" ).arg(
                    ui->cbxUnit->currentText( ) );
    }

    strSQL = strSQL.arg( ui->dtNewEnd->text( ), strWhere );
    CLogicInterface::GetInterface( )->ExecuteSql( strSQL );
    return true;
}
