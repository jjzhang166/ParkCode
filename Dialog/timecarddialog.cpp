#include "Dialog/timecarddialog.h"
#include "ui_timecarddialog.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"
#include "Header/timecard.h"

CTimeCard* pTimeParent;

CTimeCardDialog::CTimeCardDialog( bool bNew, QString strUser, QTableWidget *pTable, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CTimeCardDialog)
{
    ui->setupUi(this);

    pMonTable = pTable;
    strRecorder = strUser;
    m_bNew = bNew;
    CCommonFunction::GetCarType( ui->cbxStandard );
    pTimeParent = dynamic_cast< CTimeCard* >( this->parent( ) );
    setParent( NULL );

    CCommonFunction::ControlSysMenu( *this );
}

CTimeCardDialog::~CTimeCardDialog()
{
    delete ui;
}

void CTimeCardDialog::closeEvent( QCloseEvent *event )
{
    if ( event->spontaneous( ) ) {
        event->ignore( );
    }
}

QLineEdit* CTimeCardDialog::GetCardNumCtrl( )
{
    return m_bNew ? ui->edtCardNumber : NULL;
}

void CTimeCardDialog::SaveValue( )
{
    //Select cardno, cardkind, cardfeebz, cardselfno, cardstate, cardcreator
    QStringList lstRows;
    lstRows << ClearZero( ui->edtCardNumber )
            << ui->cbxCardType->currentText( )
            << ui->cbxStandard->currentText( )
            << ui->edtCardSelfNo->text( )
            << ui->cbxCardStatus->currentText( )
            << ui->edtRecorder->text( );
    QString strWhere = "";

    if ( !m_bNew ) {
        strWhere = QString( " Where cardno ='%1'" ).arg( ClearZero( ui->edtCardNumber ) );
    }

    CLogicInterface::GetInterface()->OperateCardInfo( lstRows,
                                                      CommonDataType::TimeCard,
                                                      m_bNew ? CommonDataType::InsertData :
                                                      CommonDataType::UpdateData, strWhere );

    //carcp, carmodel, carhaoma, cardindex
    lstRows.clear( );
    lstRows << "未知"
            << "未知"
            << "未知"
            << ClearZero( ui->edtCardNumber ); // Trigger
    CLogicInterface::GetInterface( )->OperateCarInfo( lstRows, CommonDataType::InsertData, strWhere );
}

void CTimeCardDialog::FillTable( bool bNew )
{
    int nRow = 0;
    QTableWidgetItem* pItem = NULL;
    //Select cardno, cardkind, cardfeebz, cardselfno, cardstate, cardcreator
    if ( bNew ) {
        nRow = pMonTable->rowCount( );
        pMonTable->insertRow( nRow );

        pItem = new QTableWidgetItem( ClearZero( ui->edtCardNumber ) );
        pMonTable->setItem( nRow, 0, pItem );

        pItem = new QTableWidgetItem( ui->cbxCardType->currentText( ) );
        pMonTable->setItem( nRow, 1, pItem );

        pItem = new QTableWidgetItem( ui->cbxStandard->currentText( ) );
        pMonTable->setItem( nRow, 2, pItem );

        pItem = new QTableWidgetItem( ui->edtCardSelfNo->text( ) );
        pMonTable->setItem( nRow, 3, pItem );

        pItem = new QTableWidgetItem( ui->cbxCardStatus->currentText( ) );
        pMonTable->setItem( nRow, 4, pItem );

    } else {
        nRow = pMonTable->currentRow( );

        pItem = pMonTable->item( nRow, 0 );
        pItem->setText( ClearZero( ui->edtCardNumber ) );

        pItem = pMonTable->item( nRow, 1 );
        pItem->setText( ui->cbxCardType->currentText( ) );

        pItem = pMonTable->item( nRow, 2 );
        pItem->setText( ui->cbxStandard->currentText( ) );

        pItem = pMonTable->item( nRow, 3 );
        pItem->setText( ui->edtCardSelfNo->text( ) );

        pItem = pMonTable->item( nRow, 4 );
        pItem->setText( ui->cbxCardStatus->currentText( ) );
    }
}

void CTimeCardDialog::InitDlg( )
{
    QTableWidget *pTable = pMonTable;
    // 重复卡号
    if ( !m_bNew ) {
        //Select cardno, cardkind, cardfeebz, cardselfno, cardstate, cardcreator
        ui->edtCardNumber->setEnabled( m_bNew );
        int nRow = pTable->currentRow( );
        if ( 0 >= pTable->rowCount( ) ) {
            return;
        }
        QTableWidgetItem* pItem = pTable->item( nRow, 0 );
        ui->edtCardNumber->setText( pItem->text( ) );

        pItem = pTable->item( nRow, 1 );
        int nIndex = CCommonFunction::FindComboBoxItem( ui->cbxCardType, pItem->text( ) );
        ui->cbxCardType->setCurrentIndex( nIndex );

        pItem = pTable->item( nRow, 2 );
        nIndex = CCommonFunction::FindComboBoxItem( ui->cbxStandard, pItem->text( ) );
        ui->cbxStandard->setCurrentIndex( nIndex );

        pItem = pTable->item( nRow, 3 );
        ui->edtCardSelfNo->setText( pItem->text( ) );

        pItem = pTable->item( nRow, 4 );
        nIndex = CCommonFunction::FindComboBoxItem( ui->cbxCardStatus, pItem->text( ) );
        ui->cbxCardStatus->setCurrentIndex( nIndex );

    } else {
        //spCardNumber
        //cbxCardType
        //cbxCardStatus
        //ui->edtCardNumber->setText( "0" );
        ui->edtRecorder->setText( strRecorder );
        //ui->cbxStandard->setCurrentIndex( 2 );
        //edtSelfNumber
    }

    ui->edtRecorder->setText( strRecorder );
}

void CTimeCardDialog::on_btnSave_clicked()
{
    QString strCardNo = ClearZero( ui->edtCardNumber );
    if ( !CCommonFunction::IsDigital( ClearZero( ui->edtCardNumber ) )) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 "请输入正确的卡号！", QMessageBox::Information );
        return;
    }

    if ( m_bNew ) {
        QString strTable;
        CCommonFunction::GetTableName( CommonDataType::TimeCard, strTable );
        //QString strSql = QString( "Select cardno From %1 Where cardno = \
        //                          '%2'" ).arg( strTable, ClearZero( ui->edtCardNumber ) );
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
    setResult( CTimeCardDialog::Accepted );

    QString strCotent = QString( "%1计时卡 卡号　：%2" ).arg( m_bNew ? "新增" : "修改", ClearZero( ui->edtCardNumber ) );
    pTimeParent->WriteCardLog( strCotent );
    CCommonFunction::OperationSuccess( );
}

void CTimeCardDialog::on_btnExit_clicked()
{
    if ( QMessageBox::Ok != CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                                     "确定要放弃吗？", QMessageBox::Question ) ) {
        return;
    }

    close( );
    setResult( CTimeCardDialog::Rejected );
}

void CTimeCardDialog::showEvent(QShowEvent *)
{
    ui->edtCardNumber->setFocus( );
}

void CTimeCardDialog::on_edtCardNumber_textChanged(QString strText)
{
    //QLineEdit* pEdit = qobject_cast< QLineEdit* >( sender( ) );
    //pEdit->setText( QString::number( strText.toUInt( ) ) );
    //ui->edtCardSelfNo->setFocus( );
}

QString CTimeCardDialog::ClearZero( QLineEdit *pEdit )
{
    return QString::number( pEdit->text( ).toUInt( ) );
}
