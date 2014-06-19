#include "Dialog/valuecarddialog.h"
#include "ui_valuecarddialog.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"
#include "Header/valuecard.h"
CValueCard* pValueParent;

CValueCardDialog::CValueCardDialog( bool bNew, QString strUser, QTableWidget *pTable, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CValueCardDialog)
{
    ui->setupUi(this);

    pMonTable = pTable;
    strRecorder = strUser;
    m_bNew = bNew;
    pValueParent = dynamic_cast< CValueCard* >( this->parent( ) );
    setParent( NULL );
    CCommonFunction::GetCarType( ui->cbxStandard );

    CCommonFunction::ControlSysMenu( *this );
}

CValueCardDialog::~CValueCardDialog()
{
    delete ui;
}

void CValueCardDialog::closeEvent( QCloseEvent *event )
{
    if ( event->spontaneous( ) ) {
        event->ignore( );
    }
}

QLineEdit* CValueCardDialog::GetCardNumCtrl( )
{
    return m_bNew ? ui->edtNumber : NULL;
}

void CValueCardDialog::SaveValue( )
{
    //cardno, cardkind, cardstate, cardfee, cardfeebz, cardselfno, cardcomment, cardcreator
    QString strTrue = "1";
    QString strFalse = "0";

    QStringList lstRows;
    lstRows << ClearZero( ui->edtNumber )
            << ui->cbxCardType->currentText( )
            << ui->cbxCardStatus->currentText( )
            << ui->edtRemainder->text( )
            << ui->cbxStandard->currentText( )
            << ui->edtSelfNumber->text( )
            << ui->edtComment->toPlainText( )
            << ui->edtRecorder->text( )
            << ( ui->chkEnter->isChecked( ) ? strTrue : strFalse )
            << ( ui->chkLeave->isChecked( ) ? strTrue : strFalse );
    QString strWhere = "";

    if ( !m_bNew ) {
        strWhere = QString( " Where cardno ='%1'" ).arg( ClearZero( ui->edtNumber ) );
    }

    CLogicInterface::GetInterface()->OperateCardInfo( lstRows,
                                                      CommonDataType::ValueCard,
                                                      m_bNew ? CommonDataType::InsertData :
                                                      CommonDataType::UpdateData, strWhere );
}

void CValueCardDialog::FillTable( bool bNew )
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

        pItem = new QTableWidgetItem( ui->cbxCardType->currentText( ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( ui->cbxCardStatus->currentText( ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( ui->edtRemainder->text( ) );
        pMonTable->setItem( nRow, nField++, pItem );

        pItem = new QTableWidgetItem( ui->cbxStandard->currentText( ) );
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
        pItem->setText( ui->cbxCardType->currentText( ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->cbxCardStatus->currentText( ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->edtRemainder->text( ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->cbxStandard->currentText( ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->edtSelfNumber->text( ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->edtComment->toPlainText( ) );

        pItem = pMonTable->item( nRow, nField++ );
        pItem->setText( ui->edtRecorder->text( ) );
    }
}

void CValueCardDialog::InitDlg( )
{
    QTableWidget *pTable = pMonTable;
    // 重复卡号
    if ( !m_bNew ) {
        int nField = 0;
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
        int nIndex = CCommonFunction::FindComboBoxItem( ui->cbxCardType, pItem->text( ) );
        ui->cbxCardType->setCurrentIndex( nIndex );

        pItem = pTable->item( nRow, nField++ );
        nIndex = CCommonFunction::FindComboBoxItem( ui->cbxCardStatus, pItem->text( ) );
        ui->cbxCardStatus->setCurrentIndex( nIndex );

        pItem = pTable->item( nRow, nField++ );
        ui->edtRemainder->setText( pItem->text( ) );

        pItem = pTable->item( nRow, nField++ );
        nIndex = CCommonFunction::FindComboBoxItem( ui->cbxStandard, pItem->text( ) );
        ui->cbxStandard->setCurrentIndex( nIndex );

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
        ui->edtRecorder->setText( strRecorder );
        //ui->cbxStandard->setCurrentIndex( 2 );
        //edtSelfNumber
        ui->edtComment->setPlainText ( "未知" );
    }

    ui->edtRecorder->setText( strRecorder );
}

void CValueCardDialog::on_btnSave_clicked()
{
    QString strCardNo = ClearZero( ui->edtNumber );
    if ( !CCommonFunction::IsDigital( ClearZero( ui->edtNumber ) )) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 "请输入正确的卡号！", QMessageBox::Information );
        return;
    }

    if ( m_bNew ) {
        QString strTable;
        CCommonFunction::GetTableName( CommonDataType::ValueCard, strTable );
        //QString strSql = QString( "Select cardno From %1 Where cardno = \
        //                          '%2'" ).arg( strTable, ui->edtNumber->text( ) );
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
    setResult( CValueCardDialog::Accepted );

    QString strCotent = QString( "%1储值卡 卡号　：%2" ).arg( m_bNew ? "新增" : "修改", ClearZero( ui->edtNumber ) );
    pValueParent->WriteCardLog( strCotent );

    CCommonFunction::OperationSuccess( );
}

void CValueCardDialog::on_btnExit_clicked()
{
    if ( QMessageBox::Ok != CCommonFunction::MsgBox( NULL, "提示", "确定要放弃吗？", QMessageBox::Question ) ) {
        return;
    }

    close( );
    setResult( CValueCardDialog::Rejected );
}

void CValueCardDialog::showEvent(QShowEvent *)
{
    ui->edtNumber->setFocus( );
}

void CValueCardDialog::on_edtNumber_textChanged(QString )
{
    //QLineEdit* pEdit = qobject_cast< QLineEdit* >( sender( ) );
    //pEdit->setText( QString::number( strText.toUInt( ) ) );
    //ui->edtSelfNumber->setFocus( );
}

QString CValueCardDialog::ClearZero( QLineEdit *pEdit )
{
    return QString::number( pEdit->text( ).toUInt( ) );
}
