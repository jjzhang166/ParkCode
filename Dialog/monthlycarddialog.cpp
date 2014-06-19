#include "Dialog/monthlycarddialog.h"
#include "ui_monthlycarddialog.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"
#include "Header/monthlycard.h"

CMonthlyCard* pMonthParent;

CMonthlyCardDialog::CMonthlyCardDialog( bool bNew, QString strUser, QTableWidget *pTable, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMonthlyCardDialog)
{
    ui->setupUi(this);
    //QDateTime dtCurrent = QDateTime::currentDateTime( );
    //ui->dtStart->setDateTime( dtCurrent );

    //dtCurrent = dtCurrent.addMonths( 1 );
    //ui->dtEnd->setDateTime( dtCurrent );

    pMonTable = pTable;
    strRecorder = strUser;
    m_bNew = bNew;
    pMonthParent = dynamic_cast< CMonthlyCard* >( this->parent( ) );
    setParent( NULL );

    ui->lblStart->setVisible( false );

    CCommonFunction::ControlSysMenu( *this );
}

CMonthlyCardDialog::~CMonthlyCardDialog()
{
    delete ui;
}

void CMonthlyCardDialog::closeEvent( QCloseEvent *event )
{
    if ( event->spontaneous( ) ) {
        event->ignore( );
    }
}

QLineEdit* CMonthlyCardDialog::GetCardNumCtrl( )
{
    return m_bNew ? ui->edtNumber : NULL;
}

void CMonthlyCardDialog::SaveValue( )
{
    QStringList lstRows;
    QString strTrue = "1";
    QString strFalse = "0";

    lstRows << ClearZero( ui->edtNumber )
            << ui->cbxCardType->currentText( )
            //<< ( m_bNew ? ui->dtStart->text( ) : ui->lblStart->text( ) )
            << ui->dtStart->text( )
            << ui->dtEnd->text( )
            << ui->cbxCardStatus->currentText( )
            << ui->edtSelfNumber->text( )
            << ui->edtComment->toPlainText( )
            << ui->edtRecorder->text( )
            << ( ui->chkEnter->isChecked( ) ? strTrue : strFalse )
            << ( ui->chkLeave->isChecked( ) ? strTrue : strFalse )
            << ( ui->chkMIMO->isChecked( ) ? strTrue : strFalse );
    QString strWhere = "";

    if ( !m_bNew ) {
        strWhere = QString( " Where cardno ='%1'" ).arg( ClearZero( ui->edtNumber ) );
    }

    CLogicInterface::GetInterface()->OperateCardInfo( lstRows,
                                                      CommonDataType::MonthlyCard,
                                                      m_bNew ? CommonDataType::InsertData :
                                                      CommonDataType::UpdateData, strWhere );
}

void CMonthlyCardDialog::FillTable( bool bNew )
{
    int nRow = 0;
    QTableWidgetItem* pItem = NULL;
    int nField = 0;

    if ( bNew ) {
        nRow = pMonTable->rowCount( );
        pMonTable->insertRow( nRow );

        pItem = new QTableWidgetItem( ClearZero( ui->edtNumber ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( );
        pMonTable->setItem( nRow, nField++, pItem );
        pItem->setCheckState( !ui->chkEnter->isChecked( ) ? Qt::Unchecked : Qt::Checked );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem( );
        pMonTable->setItem( nRow, nField++, pItem );
        pItem->setCheckState( !ui->chkLeave->isChecked( ) ? Qt::Unchecked : Qt::Checked );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem( );
        pMonTable->setItem( nRow, nField++, pItem );
        pItem->setCheckState( !ui->chkMIMO->isChecked( ) ? Qt::Unchecked : Qt::Checked );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem( ui->cbxCardType->currentText( ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( ui->dtStart->text( ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( ui->dtEnd->text( ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( ui->cbxCardStatus->currentText( ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( ui->edtSelfNumber->text( ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( ui->edtComment->toPlainText( ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( ui->edtRecorder->text( ) );
        pMonTable->setItem( nRow, nField++, pItem );
    } else {
        nRow = pMonTable->currentRow( );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ClearZero( ui->edtNumber ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setCheckState( ui->chkEnter->isChecked( ) ? Qt::Checked : Qt::Unchecked );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setCheckState( ui->chkLeave->isChecked( ) ? Qt::Checked : Qt::Unchecked );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setCheckState( ui->chkMIMO->isChecked( ) ? Qt::Checked : Qt::Unchecked );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->cbxCardType->currentText( ) );

        pItem = pMonTable->item( nRow, nField++ );
        QString strDt;
        QDateTime dt =  ui->dtStart->dateTime( );
        CCommonFunction::DateTime2String( dt, strDt );
        pItem->setText( strDt );

        dt =  ui->dtEnd->dateTime( );
        CCommonFunction::DateTime2String( dt, strDt );
        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( strDt );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->cbxCardStatus->currentText( ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->edtSelfNumber->text( ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->edtComment->toPlainText( ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->edtRecorder->text( ) );
    }
}

void CMonthlyCardDialog::InitDlg( )
{
    QTableWidget *pTable = pMonTable;
    // 重复卡号
    if ( !m_bNew ) {
        int nField  = 0;
        ui->edtNumber->setEnabled( m_bNew );
        int nRow = pTable->currentRow( );
        if ( 0 >= pTable->rowCount( ) ) {
            return;
        }
        QTableWidgetItem* pItem = pTable->item( nRow, nField++ );
        ui->edtNumber->setText( pItem->text( ) );

        pItem = pTable->item( nRow, nField++ );
        ui->chkEnter->setChecked( pItem->checkState( ) == Qt::Checked );

        pItem = pTable->item( nRow, nField++ );
        ui->chkLeave->setChecked( pItem->checkState( ) == Qt::Checked );

        pItem = pTable->item( nRow, nField++ );
        ui->chkMIMO->setChecked( pItem->checkState( ) == Qt::Checked );

        pItem = pTable->item( nRow, nField++ );
        int nIndex = CCommonFunction::FindComboBoxItem( ui->cbxCardType, pItem->text( ) );
        ui->cbxCardType->setCurrentIndex( nIndex );

        pItem = pTable->item( nRow, nField++ );
        QString strDateTime = pItem->text( );
        QDateTime dtDateTime = CCommonFunction::String2DateTime( strDateTime );
        ui->dtStart->setDateTime( dtDateTime );

        pItem = pTable->item( nRow, nField++ );
        strDateTime = pItem->text( );
        dtDateTime = CCommonFunction::String2DateTime( strDateTime );
        ui->dtEnd->setDateTime( dtDateTime );

        pItem = pTable->item( nRow, nField++ );
        nIndex = CCommonFunction::FindComboBoxItem( ui->cbxCardStatus, pItem->text( ) );
        ui->cbxCardStatus->setCurrentIndex( nIndex );

        pItem = pTable->item( nRow, nField++ );
        ui->edtSelfNumber->setText( pItem->text( ) );

        pItem = pTable->item( nRow, nField++ );
        ui->edtComment->setText( pItem->text( ) );

        pItem = pTable->item( nRow, nField++ );
        ui->edtRecorder->setText( pItem->text( ) );

    } else {
        //spCardNumber
        //cbxCardType
        //cbxCardStatus
        //ui->edtNumber->setText( "0" );
        QDateTime dtCurrent = QDateTime::currentDateTime( );
        ui->dtStart->setDateTime( dtCurrent );
        dtCurrent = dtCurrent.addMonths( 1 );
        ui->dtEnd->setDateTime( dtCurrent );
        ui->edtRecorder->setText( strRecorder );
        //edtSelfNumber
        ui->edtComment->setPlainText ( "未知" );
    }

    ui->edtRecorder->setText( strRecorder );
}

void CMonthlyCardDialog::on_btnSave_clicked( )
{
    QString strCardNo = ClearZero( ui->edtNumber );
    if ( !CCommonFunction::IsDigital( ClearZero( ui->edtNumber ) )) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 "请输入正确的卡号！", QMessageBox::Information );
        return;
    }

    if ( m_bNew ) {
        QString strTable;
        CCommonFunction::GetTableName( CommonDataType::MonthlyCard, strTable );
        //QString strSql = QString( "Select cardno From %1 Where cardno = \
        //                          '%2'" ).arg( strTable, ClearZero( ui->edtNumber ) );
        QStringList lstRow;
        //CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRow );
        CLogicInterface::GetInterface( )->ExistCardNumber( strCardNo, lstRow );
        if ( 0 < lstRow.count( ) ) {
            CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                     lstRow.at( 0 ), QMessageBox::Information );
            return;
        }
    }

    FillTable( m_bNew );
    SaveValue( );
    setResult( CMonthlyCardDialog::Accepted );

    QString strCotent = QString( "%1月租卡 卡号　：%2" ).arg( m_bNew ? "新增" : "修改", ClearZero( ui->edtNumber ) );
    pMonthParent->WriteCardLog( strCotent );
    CCommonFunction::OperationSuccess( );
}

void CMonthlyCardDialog::showEvent(QShowEvent *)
{
    ui->edtNumber->setFocus();
}

void CMonthlyCardDialog::on_btnExit_clicked( )
{
    if ( QMessageBox::Ok != CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                                     "确定要放弃吗？", QMessageBox::Question ) ) {
        return;
    }

    close( );
    setResult( CMonthlyCardDialog::Rejected );
}

QString CMonthlyCardDialog::ClearZero( QLineEdit *pEdit )
{
    return QString::number( pEdit->text( ).toUInt( ) );
}

void CMonthlyCardDialog::on_edtNumber_textChanged(QString strText)
{
    //QLineEdit* pEdit = qobject_cast< QLineEdit* >( sender( ) );
    //pEdit->setText( QString::number( strText.toUInt( ) ) );
    //ui->edtSelfNumber->setFocus( );
}
