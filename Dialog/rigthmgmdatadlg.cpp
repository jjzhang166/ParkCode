#include "Dialog/rigthmgmdatadlg.h"
#include "ui_rigthmgmdatadlg.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"

CRigthMgmDataDlg::CRigthMgmDataDlg(QTableWidget* pTableWG, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRigthMgmDataDlg)
{
    ui->setupUi(this);
    pTableWidget = pTableWG;
    pLstRow = new QStringList( );

    CCommonFunction::ControlSysMenu( *this );
}

CRigthMgmDataDlg::~CRigthMgmDataDlg()
{
    delete pLstRow;
    delete ui;
}
#if 0
chxRMgm
chxRate
chxData
chxSysLog
chxStartVideo
chxStartPlate
chxConnectDB
chxExit
chxMonthCard
chxValueCard
chxTimeCard
chxLedInfo
chxDeviceConfig
chxSystemSet
chxCardRight
chxDiscountSet
chxSerialPortSet
chxPlateSet
chxPassRecord
chxFeeRecord
chxDiscountReport
chxDailyReport
chxMonthlyReport
chxYearlyReport
#endif
QStringList& CRigthMgmDataDlg::GetData( )
{
    QString strTrue = "-1";
    QString strFalse = "0";
    *pLstRow << ui->edtName->text( ) <<
                ui->edtCardID->text( ) <<
                ui->cbxSex->currentText( ) <<
                ui->cbxRType->currentText( ) <<
                ( ui->chxRMgm->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxRate->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxData->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxSysLog->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxStartVideo->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxStartPlate->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxConnectDB->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxExit->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxMonthCard->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxValueCard->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxTimeCard->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxLedInfo->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxDeviceConfig->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxSystemSet->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxCardRight->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxDiscountSet->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chkBlacklist->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxSerialPortSet->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxPlateSet->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxSyncTime->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxPassRecord->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxFeeRecord->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxDiscountReport->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxDailyReport->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxMonthlyReport->isChecked( ) ? strTrue : strFalse ) <<
                ( ui->chxYearlyReport->isChecked( ) ? strTrue : strFalse ) <<
                ui->edtAddr->text( ) <<
                ui->edtTel->text( );

    return *pLstRow;
}

QString CRigthMgmDataDlg::GetUser( )
{
    return ui->edtName->text( );
}

void CRigthMgmDataDlg::SetNewOrEdit(bool bNew)
{
    bNewOrEdit = bNew;
    ui->edtName->setEnabled( bNew );
}

bool CRigthMgmDataDlg::ValidCardID( )
{
    quint32 nID = ui->edtCardID->text( ).toUInt( );
    bool bRet = false;

    if ( 1 <= nID && nID <= 0xFFFFFF ) {
        bRet = true;
    } else {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请输入1到16777215之间的卡号！" ), QMessageBox::Information );
    }

    return bRet;
}

QLineEdit* CRigthMgmDataDlg::GetCardIDCtrl( )
{
    return ui->edtCardID;
}

void CRigthMgmDataDlg::on_btnOk_clicked()
{
    //if ( !ValidCardID( ) ) {
    //    return;
    //}

    if ( bNewOrEdit ) {

        if ( ui->edtName->text( ).isEmpty( ) ) {
            CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                     QString( "用户已不能为空！" ), QMessageBox::Information );
            return;
        }
        QStringList lstRows;
        QString strSql= QString( "Select  operatorname From operator \
                                 Where operatorname = '%1'" ).arg( ui->edtName->text( ) );
        CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
        if ( 0 < lstRows.count( ) ) {
           CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                    QString( "用户已存在，请重新输入用户！" ), QMessageBox::Information );
           return;
        }
    }

    NewOrEditDlg( bNewOrEdit );

    close( );
    setResult( CRigthMgmDataDlg::Accepted );
}

void CRigthMgmDataDlg::on_btnCancel_clicked()
{
    int nRet = CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                        QString( "真要取消吗？" ), QMessageBox::Question );
    if ( QMessageBox::Cancel == nRet ) {
        return;
    }

    close( );
    setResult( CRigthMgmDataDlg::Rejected );
}

void CRigthMgmDataDlg::closeEvent(QCloseEvent *event)
{
    bool bRet = event->spontaneous( );

    if ( bRet ) {
        event->ignore( );
    } else {
        ;
    }
}

bool CRigthMgmDataDlg::SameUser( QString &strUser )
{
    int nRows = pTableWidget->rowCount( );
    bool bFound = false;

    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        if ( ( bFound = ( strUser == pTableWidget->item( nIndex, 0 )->text( ) ) ) ) {
            break;
        }
    }

    return bFound;
}

void CRigthMgmDataDlg::NewOrEditDlg(bool bNew)
{
    QTableWidgetItem* pItem = NULL;
    int nCurRow = -1;
    int nField= 0;

    if ( bNew ) {
        nCurRow = pTableWidget->rowCount( );
        pTableWidget->insertRow( nCurRow );

        pItem = new QTableWidgetItem( ui->edtName->text( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem( ui->edtCardID->text( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem( ui->cbxSex->currentText( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem( ui->cbxRType->currentText( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxRMgm->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxRate->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxData->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxSysLog->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxStartVideo->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxStartPlate->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxConnectDB->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxExit->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxMonthCard->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxValueCard->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxTimeCard->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxLedInfo->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxDeviceConfig->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxSystemSet->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxCardRight->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxDiscountSet->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxSerialPortSet->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chkBlacklist->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxPlateSet->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxSyncTime->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxPassRecord->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxFeeRecord->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxDiscountReport->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxDailyReport->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxMonthlyReport->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem(  );
        pItem->setCheckState( ui->chxYearlyReport->checkState( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem( ui->edtAddr->text( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

        pItem = new QTableWidgetItem( ui->edtTel->text( ) );
        pTableWidget->setItem( nCurRow, nField++, pItem );
        pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
    } else {
        nCurRow = pTableWidget->currentRow( );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setText( ui->edtName->text( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setText( ui->edtCardID->text( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setText( ui->cbxSex->currentText( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setText( ui->cbxRType->currentText( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxRMgm->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxRate->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxData->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxSysLog->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxStartVideo->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxStartPlate->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxConnectDB->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxExit->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxMonthCard->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxValueCard->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxTimeCard->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxLedInfo->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxDeviceConfig->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxSystemSet->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxCardRight->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxDiscountSet->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chkBlacklist->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxSerialPortSet->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxPlateSet->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxSyncTime->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxPassRecord->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxFeeRecord->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxDiscountReport->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxDailyReport->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxMonthlyReport->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setCheckState( ui->chxYearlyReport->checkState( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setText( ui->edtAddr->text( ) );

        pItem = pTableWidget->item( nCurRow, nField++ );
        pItem->setText( ui->edtTel->text( ) );
    }
}

void CRigthMgmDataDlg::InitDlg( )
{
    QTableWidgetItem* pItem = NULL;
    int nCurRow = pTableWidget->currentRow( );
    if ( -1 == nCurRow ) {
        return;
    }

    int nField = 0;

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->edtName->setText( pItem->text( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->edtCardID->setText( pItem->text( ) );

    int nIndex = CCommonFunction::FindComboBoxItem( ui->cbxSex, ui->cbxSex->currentText( ) );
    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->cbxSex->setCurrentIndex( nIndex );/////////

    nIndex = CCommonFunction::FindComboBoxItem( ui->cbxRType, ui->cbxRType->currentText( ) );
    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->cbxRType->setCurrentIndex( nIndex );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxRMgm->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxRate->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxData->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxSysLog->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxStartVideo->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxStartPlate->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxConnectDB->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxExit->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxMonthCard->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxValueCard->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxTimeCard->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxLedInfo->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxDeviceConfig->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxSystemSet->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxCardRight->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxDiscountSet->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chkBlacklist->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxSerialPortSet->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxPlateSet->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxSyncTime->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxPassRecord->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxFeeRecord->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxDiscountReport->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxDailyReport->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxMonthlyReport->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->chxYearlyReport->setCheckState( pItem->checkState( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->edtAddr->setText( pItem->text( ) );

    pItem = pTableWidget->item( nCurRow, nField++ );
    ui->edtTel->setText( pItem->text( ) );
}

void CRigthMgmDataDlg::AllSelected(bool bSelected)
{
    QList< QCheckBox* > oList = this->findChildren< QCheckBox* >( );
    QCheckBox* pChk = NULL;

    foreach ( pChk, oList ) {
        pChk->setChecked( bSelected );
    }

}

void CRigthMgmDataDlg::on_btnAllOk_clicked()
{
    AllSelected( true );
}

void CRigthMgmDataDlg::on_btnAllCancel_clicked()
{
    AllSelected( false );
}
