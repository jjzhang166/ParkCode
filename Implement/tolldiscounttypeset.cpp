#include "Header/tolldiscounttypeset.h"
#include "ui_tolldiscounttypeset.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"

CTollDiscountTypeSet::CTollDiscountTypeSet(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CTollDiscountTypeSet)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    //pParent->OperateTableWidget( ui->tableTollDiscount, CommonDataType::TollDiscountTable, CommonDataType::InitializeType );

    EnableControl( false );
    ControlButton( true );
    ui->lblTitle->setText( windowTitle( ) );

    nOperate = -1;
    ui->tableTollDiscount->hideColumn( 4 );
    ui->lblID->setVisible( false );
}

void CTollDiscountTypeSet::FillTable( )
{
    CCommonFunction::FreeAllRows( ui->tableTollDiscount );

    QStringList lstData;
    QString strWhere = "";
    int nCols = 5;
    int nRows = CLogicInterface::GetInterface( )->OperateTollDiscountInfo( lstData, CommonDataType::SelectData, strWhere );

    ui->tableTollDiscount->setRowCount( nRows );

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        for ( int nCol = 0; nCol < nCols; nCol++ ) {
            QString& strValue = lstData[ nRow * nCols + nCol ];
            QTableWidgetItem* pItem = new QTableWidgetItem( strValue );
            ui->tableTollDiscount->setItem( nRow, nCol, pItem );

            if ( 1 == nCol ) {
                int nIndex = strValue.toInt( );
                //ui->cbxMethod->itemText( nIndex );
                pItem->setText( ui->cbxMethod->itemText( nIndex ) );
            }

            pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        }
    }
}

void CTollDiscountTypeSet::ControlButton( bool bEnabled )
{
    ui->btnAdd->setEnabled( bEnabled );
    ui->btnDelete->setEnabled( bEnabled );
    ui->btnModify->setEnabled( bEnabled );

    ui->btnOk->setEnabled( !bEnabled );
    ui->btnCancel->setEnabled( !bEnabled );
}

void CTollDiscountTypeSet::on_btnAdd_clicked( )
{
    nOperate = 0;
    ControlButton( false );
    EnableControl( true );
}

void CTollDiscountTypeSet::on_btnDelete_clicked( )
{
    int nRow = ui->tableTollDiscount->currentRow( );

    if ( -1 == nRow || ui->lblID->text( ).isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请选择要删除的行！" ), QMessageBox::Information );
        return;
    }

    nOperate = 1;
    SaveData( 1 );
    CCommonFunction::FreeRow( ui->tableTollDiscount, nRow, ui->tableTollDiscount->columnCount( ) );
}

void CTollDiscountTypeSet::on_btnModify_clicked( )
{
    int nRow = ui->tableTollDiscount->currentRow( );

    if ( -1 == nRow || ui->lblID->text( ).isEmpty( ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 QString( "请选择要修改的行！" ), QMessageBox::Information );
        return;
    }

    AssignValue( false, nRow );
    nOperate = 2;
    EnableControl( true );
    ControlButton( false );
}

void CTollDiscountTypeSet::EnableControl( bool bEnabled )
{
    ui->edtName->setEnabled( bEnabled );
    ui->cbxMethod->setEnabled( bEnabled );
    ui->spValue->setEnabled( bEnabled );
    ui->edtExplain->setEnabled( bEnabled );
}

void CTollDiscountTypeSet::AssignValue( bool bToTable, int nRowIndex )
{
    QTableWidgetItem* pItem = NULL;

    if ( bToTable ) {
        pItem = new QTableWidgetItem( ui->edtName->text( ) );
        ui->tableTollDiscount->setItem( nRowIndex, 0, pItem );

        pItem = new QTableWidgetItem( ui->cbxMethod->currentText( ) );
        ui->tableTollDiscount->setItem( nRowIndex, 1, pItem );


        pItem = new QTableWidgetItem( QString( "%1" ).arg( ui->spValue->value( ) ) );
        ui->tableTollDiscount->setItem( nRowIndex, 2, pItem );

        pItem = new QTableWidgetItem( ui->edtExplain->text( ) );
        ui->tableTollDiscount->setItem( nRowIndex, 3, pItem );

    } else {
        pItem = ui->tableTollDiscount->item( nRowIndex, 0 );
        if ( NULL == pItem ) {
            return;
        }
        ui->edtName->setText( pItem->text( ) );

        pItem = ui->tableTollDiscount->item( nRowIndex, 1 );
        if ( NULL == pItem ) {
            return;
        }
        QString strText = pItem->text( );
        int nIndex = CCommonFunction::FindComboBoxItem( ui->cbxMethod, strText );
        ui->cbxMethod->setCurrentIndex( nIndex );

        pItem = ui->tableTollDiscount->item( nRowIndex, 2 );
        if ( NULL == pItem ) {
            return;
        }
        ui->spValue->setValue( pItem->text( ).toInt( ) );

        pItem = ui->tableTollDiscount->item( nRowIndex, 3 );
        if ( NULL == pItem ) {
            return;
        }
        ui->edtExplain->setText( pItem->text( ) );
    }
}

void CTollDiscountTypeSet::on_tableTollDiscount_cellClicked ( int row, int column )
{
    ui->lblID->setText( ui->tableTollDiscount->item( row, 4 )->text( ) );
    AssignValue( false, row );
}

void CTollDiscountTypeSet::SaveData( int nType )
{
    QString strWhere = QString( " Where zkindex = %1" ).arg( ui->lblID->text( ) );
    QStringList lstData;

    if ( 1 == nType ) {
        CLogicInterface::GetInterface( )->OperateTollDiscountInfo( lstData, CommonDataType::DeleteData, strWhere );
    } else {
        lstData << ui->edtName->text( )
                << QString::number( ui->cbxMethod->currentIndex( ) )
                << QString::number( ui->spValue->value( ) )
                << ui->edtExplain->text( );

        if ( 0 == nType ) {
            CLogicInterface::GetInterface( )->OperateTollDiscountInfo( lstData, CommonDataType::InsertData, strWhere );
        } else if ( 2 == nType ) {
            CLogicInterface::GetInterface( )->OperateTollDiscountInfo( lstData, CommonDataType::UpdateData, strWhere );
        }
    }
}

void CTollDiscountTypeSet::on_btnOk_clicked( )
{
    if ( -1 == nOperate ) {
        return;
    }

    int nRow = 1;

    if ( 0 == nOperate ) { // Add
        QString strText = ui->edtName->text( );
        if ( strText.isEmpty( ) ) {
            CCommonFunction::MsgBox( NULL, "提示", QString( "请输入折扣名称！" ).arg( strText ),
                                     QMessageBox::Information );
            return;
        }

        QString strSql = QString( "select zkname from zkset where zkname = '%1'" ).arg( strText );
        QStringList lstRows;
        int nRows = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
        if ( 0 != nRows  ) {
            CCommonFunction::MsgBox( NULL, "提示", QString( "折扣名【%1】已存在！" ).arg( strText ),
                                     QMessageBox::Information );
            return;
        }

        nRow = ui->tableTollDiscount->rowCount( );
        ui->tableTollDiscount->insertRow( nRow );
    } else if ( 1 == nOperate ) { // Delete
        return;
    } else if ( 2 == nOperate ) { // Modify
        nRow = ui->tableTollDiscount->currentRow( );
    }

    SaveData( nOperate );

    AssignValue( true, nRow );
    ControlButton( true );
    EnableControl( false );

    FillTable( );
}

void CTollDiscountTypeSet::on_btnCancel_clicked( )
{
    ControlButton( true );
    EnableControl( false );
}

CTollDiscountTypeSet::~CTollDiscountTypeSet()
{
    delete ui;
}

void CTollDiscountTypeSet::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CTollDiscountTypeSet::resizeEvent( QResizeEvent* )
{
    FillTable( );
    CalculatePos( );
}

void CTollDiscountTypeSet::CalculatePos( )
{
#ifdef NewUI
    move( 123, 46 );
#else
    move( 123, 177 );
#endif
    return;
    QRect rectWnd = this->geometry( );

    QString strName = "widget";
    QWidget* pWg = findChild< QWidget* >( strName );
    QRect rectWg = pWg->geometry( );
    pWg->setGeometry( ( rectWnd.width( ) - rectWg.width( ) -2 ) / 2,
                      ( rectWnd.height( )  - rectWg.height( ) -2 ) / 2,
                      rectWg.width( ), rectWg.height( ) );
}

void CTollDiscountTypeSet::on_btnMinimalize_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CTollDiscountTypeSet::on_lblClose_linkActivated(QString)
{
    close( );
}
