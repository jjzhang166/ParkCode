#include "cdlgbulkcharge.h"
#include "ui_cdlgbulkcharge.h"
#include "Common/logicinterface.h"

CDlgBulkCharge::CDlgBulkCharge(bool bState, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgBulkCharge)
{
    ui->setupUi(this);
    bMonthState = bState;
    CCommonFunction::ControlSysMenu( *this );
    GetUnit( );
    InitUI( );
    setWindowTitle( bState ? "月租卡批量续期" : "月租卡批量进出标志修改" );
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

    ui->widgetState->setEnabled( bMonthState );
    ui->widgetDate->setEnabled( !bMonthState );
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
    QString strText = bMonthState ? "符合条件的所有月租卡进出标志都将被修改。" : QString( "符合条件的所有月租卡截至日期都将被修改为【%1】。" ).arg(
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
    QString strSQLState = "Update MonthCard set EnterMustCard = %1, LeaveMustCard = %2, MIMO = %3 Where %4";
    QString strWhere = "";
    bool bRet = false;

    QString strSelect = "select cardno from MonthCard Where %1";

    if ( ui->rdbSelfNo->isChecked( ) ) {
        if ( ui->edtSelfStart->text( ).isEmpty( ) ||
             ui->edtSelfEnd->text( ).isEmpty( ) ) {
            CCommonFunction::MsgBox( NULL, "提示", "请输入完整的起始自编号范围。", QMessageBox::Information );
            return bRet;
        }

        strWhere = QString( "CardSelfNo between '%1' and '%2'" ).arg(
                    ui->edtSelfStart->text( ),
                    ui->edtSelfEnd->text( ) );
        strSelect = strSelect.arg( strWhere );
    } else if ( ui->rdbEndDate->isChecked( ) ) {
        if ( ui->dtEndStart->date( ) > ui->dtEndEnd->date( ) ) {
            CCommonFunction::MsgBox( NULL, "提示", "请输入正确的截至时间范围。", QMessageBox::Information );
            return bRet;
        }

        strWhere = QString( "EndTime between '%1 00:00:00' and '%2 23:59:59'" ).arg(
                    ui->dtEndStart->text( ),
                    ui->dtEndEnd->text( ) );
        strSelect = strSelect.arg( strWhere );
    } else if ( ui->rdbUnit->isChecked( ) ) {
        if ( !ui->cbxUnit->itemData( ui->cbxUnit->currentIndex( ) ).toBool( ) ) {
            CCommonFunction::MsgBox( NULL, "提示", "无有效单位。", QMessageBox::Information );
            return bRet;
        }

        strWhere = QString( "CardNo in( Select Distinct CardIndex From UserInfo Where UserCorp = '%1' )" ).arg(
                    ui->cbxUnit->currentText( ) );

        strSelect = QString( "Select Distinct CardIndex From UserInfo Where UserCorp = '%1'" ).arg( ui->cbxUnit->currentText( ) );
    }

    if ( bMonthState ) {
        strSQLState = strSQLState.arg( QString::number( ui->chkEnterMustCard->isChecked( ) ),
                                       QString::number( ui->chkLeaveMustCard->isChecked( ) ),
                                       QString::number( ui->chkMIMO->isChecked( ) ), strWhere );
    } else {
        strSQL = strSQL.arg( ui->dtNewEnd->text( ), strWhere );
    }

    CLogicInterface::GetInterface( )->ExecuteSql( bMonthState ? strSQLState : strSQL );

    QStringList lstData;
    lstData << strSelect;
    emit BroadcastCardNo( lstData );

    return true;
}
