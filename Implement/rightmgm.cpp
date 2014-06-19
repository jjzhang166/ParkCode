#include "Header/rightmgm.h"

#ifdef NewUI
    #include "ui_newrightmgm.h"
#else
    #include "ui_rightmgm.h"
#endif

#include <QGroupBox>
#include <QTableWidget>
#include <QString>
#include "Common/CommonType.h"
#include "Dialog/rigthmgmdatadlg.h"
#include "Common/commonfunction.h"
#include <Common/logicinterface.h>

#define ADMINISTRATOR QString( "系统管理员" )

CRightMgm::CRightMgm(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(
        #ifdef NewUI
            new Ui::CONCAT_NEW_NAME( New , CRightMgm )
        #else
            new Ui::CONCAT_NEW_NAME( , CRightMgm )
        #endif
        )
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );

    ui->tableRight->horizontalHeader( )->hideSection( ui->tableRight->columnCount( ) - 1 );
    ui->tableRight->horizontalHeader( )->hideSection( 29 );

    ui->lblTitle->setText( windowTitle( ) );
}

void CRightMgm::FillTable( QTableWidget* pTableWidget, QString& strWhere )
{
    CCommonFunction::FreeAllRows( ui->tableRight );

    qint32 nRows = 0;
    qint32 nCols = pTableWidget->columnCount( );
    qint32 nRowIndex = 0;
    qint32 nColIndex = 0;
    QString strValue;
    QTableWidgetItem* pItem = NULL;
    bool bCondition = false;
    QStringList lstRows;

    nRows = CLogicInterface::GetInterface( )->OperateRightInfo( lstRows, CommonDataType::SelectData, strWhere );
    pTableWidget->setRowCount( nRows ); // pTableWidet->setColumnCount( 20 )

    int nBase = 0;
    for ( nRowIndex = 0; nRowIndex < nRows; nRowIndex++ ) {
        for ( nColIndex = 0; nColIndex < nCols; nColIndex++ ) {
            bCondition = ( 4 > nColIndex || nColIndex >= nCols - 3 );
            strValue = lstRows[ nColIndex + nBase ];
            pItem = bCondition ? new QTableWidgetItem( strValue ) : new QTableWidgetItem( );
            pTableWidget->setItem( nRowIndex, nColIndex, pItem ); //[ Row, Column ] [ 0, 0 ]
            pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

            if ( false == bCondition) {
                pItem->setCheckState( ( 0 == strValue.compare( "0" ) ) ?  Qt::Unchecked : Qt::Checked );
            }
        }

        nBase += nCols;
    }
}

CRightMgm::~CRightMgm()
{
    delete ui;
}

bool CRightMgm::SameUser( QString &strUser )
{
    int nRows = ui->tableRight->rowCount( );
    bool bFound = false;

    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        if ( ( bFound = ( strUser == ui->tableRight->item( nIndex, 0 )->text( ) ) ) ) {
            break;
        }
    }

    return bFound;
}

void CRightMgm::ShowDialog( bool bNew )
{
    CRigthMgmDataDlg dlg( ui->tableRight, NULL );
    dlg.SetNewOrEdit( bNew );
    if ( false == bNew ) {
        if ( -1 == ui->tableRight->currentRow( ) ) {
            CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                     QString( "请选择要编辑的数据！" ), QMessageBox::Information );
            return;
        }

        if ( IsAdministrator( ) ) {
            return;
        }

        dlg.InitDlg( );
    }

    pParent->SetCardControl( dlg.GetCardIDCtrl( ) );
    int nRet = dlg.exec( );
    pParent->SetCardControl( NULL );

    if ( CRigthMgmDataDlg::Accepted == nRet ) {
        QString strUser = dlg.GetUser( );
        QString strWhere = "";

        if ( !bNew ) {
            GetWhere( strWhere, !bNew, strUser );
        }

        CLogicInterface::GetInterface( )->OperateRightInfo( dlg.GetData( ),
        bNew ? CommonDataType::InsertData : CommonDataType::UpdateData, strWhere );
    }
}

void CRightMgm::on_tableRight_cellDoubleClicked(int, int)
{
    ShowDialog( false );
}

void CRightMgm::showEvent(QShowEvent *)
{
    QString strWhere = "";
    FillTable( ui->tableRight, strWhere );
}

void CRightMgm::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CRightMgm::resizeEvent ( QResizeEvent *  )
{
    CalculatePos( );
}

void CRightMgm::CalculatePos( )
{
    move( 23, 55 );
    return;
    QRect rectWnd = geometry( );

    QString strName = "gbRight";
    QGroupBox* pGB = findChild< QGroupBox* >( strName );

    strName.clear( );
    strName.append( "tableRight" );
    QTableWidget* pTW = findChild< QTableWidget* >( strName );

    strName.clear( );
    strName.append( "wgButton" );
    QWidget* pWg = findChild< QWidget* >( strName );
    QRect rectWg = pWg->geometry( );

    pGB->setGeometry( rectWnd.x( ) + 1, rectWnd.y( ) + 1, rectWnd.width( ) - 2, rectWnd.height( ) - 1 - rectWg.height( ) - 5 );
    QRect rectGB = pGB->geometry( );

    pTW->setGeometry( rectGB.x( ) + 5, rectGB.y( ) + 15, rectGB.width( ) - 10, rectGB.height( ) - 10 );

    pWg->setGeometry( ( rectGB.width( ) - rectWg.width( ) ) / 2,
                      rectWnd.height( ) - rectWg.height( ), rectWg.width( ), rectWg.height( ) );
}

void CRightMgm::on_btnNew_clicked( )
{
    ShowDialog( true );
}

bool CRightMgm::IsAdministrator( )
{
    int nRow = ui->tableRight->currentRow( );
    bool  bRet = ADMINISTRATOR == ui->tableRight->item( nRow, 0 )->text( );

    if ( bRet ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "该用户是【%1】，不能修改或删除！" ).arg( ADMINISTRATOR ), QMessageBox::Information );
    }

    return bRet;
}

void CRightMgm::on_btnDelete_clicked( )
{
    int nRow = ui->tableRight->currentRow( );

    if ( -1 == nRow ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请选择要删除的数据！" ), QMessageBox::Information );
        return;
    }

    ui->tableRight->selectRow( ui->tableRight->currentRow( ) );

    if ( IsAdministrator( ) ) {
        return;
    }

    if ( QMessageBox::Ok == CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                                     QString( "确定要删除此数据！" ), QMessageBox::Question )) {

        QStringList lstRows;
        QString strWhere;
        GetWhere( strWhere );
        CLogicInterface::GetInterface( )->OperateRightInfo( lstRows,CommonDataType::DeleteData, strWhere );

        CCommonFunction::FreeRow( ui->tableRight, nRow, ui->tableRight->columnCount( ) );
    }
}

void CRightMgm::GetWhere( QString &strWhere, bool bUpdate, QString strUser )
{
    int nRow = ui->tableRight->currentRow( );
    //int nCol = ui->tableRight->columnCount( ) - 1;
    QTableWidgetItem* pItem = ui->tableRight->item( nRow, 0 );
    if ( NULL == pItem && !bUpdate) {
        return;
    }

    strWhere = QString( " Where  operator%1 = '%2'" ).arg(
            bUpdate ? "name" : "name" ,
            bUpdate ? strUser : pItem->text( ) );
    //strWhere = strWhere.arg( bUpdate ? strUser : pItem->text( ) );
}

void CRightMgm::on_btnExit_clicked( )
{
    this->setVisible( false );
    pParent->ControlMonitor( true );
}

void CRightMgm::on_btnEdit_clicked( )
{
    ShowDialog( false );
}

void CRightMgm::on_lblClose_linkActivated(QString)
{
    close( );
}
