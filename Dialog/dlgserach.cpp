#include "dlgserach.h"
#include "ui_dlgserach.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"

#if false
select a.cardno, a.starttime, a.endtime, a.cardstate, a.cardkind, a.cardselfno, a.cardcomment, a.cardcreator,
b.username, b.usersex,b.userphone,
c.carcp, c.carmodel ,c.carhaoma from monthcard a
inner join userinfo b on a.cardno = b.cardindex
inner join carinfo c on a.cardno = c.cardindex

select a.cardno, a.cardfeebz, a.cardfee, a.cardstate, a.cardkind, a.cardselfno, a.cardcomment, a.cardcreator,
b.username, b.usersex,b.userphone,
c.carcp, c.carmodel ,c.carhaoma from savecard a
inner join userinfo b on a.cardno = b.cardindex
inner join carinfo c on a.cardno = c.cardindex;
#endif
CDlgSerach::CDlgSerach( CommonDataType::CardType nType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgSerach)
{
    ui->setupUi(this);

    CCommonFunction::ConnectCloseButton( ui->lblClose );
    QString strTmp = "";
    QString strTable= "";
    bTimeCard = false;
    CCommonFunction::GetTableName( nType, strTable );
    QHeaderView* pHeader = ui->tabResult->horizontalHeader( );

    switch ( nType ) {
    case CommonDataType::MonthlyCard :
        strTmp = "a.starttime, a.endtime, ";
        ui->tabResult->horizontalHeaderItem( 1 )->setText( "开始时间" );
        ui->tabResult->horizontalHeaderItem( 2 )->setText( "截止时间" );
        break;

    case CommonDataType::ValueCard :
        strTmp = "a.cardfeebz, a.cardfee, ";
        ui->tabResult->horizontalHeaderItem( 1 )->setText( "费用标准" );
        ui->tabResult->horizontalHeaderItem( 2 )->setText( "卡余额" );
        break;

    case CommonDataType::TimeCard :
        ui->tabResult->horizontalHeaderItem( 1 )->setText( "费用标准" );
        bTimeCard = true;
        ui->edtOwner->setEnabled( false );
        ui->edtPlate->setEnabled( false );
        for ( int nIndex = pHeader->count( ) - 1; nIndex >=0; nIndex-- ) {
            if ( ( 2 != nIndex ) &&  ( 0 <= nIndex && 5 >= nIndex  ) ) {
                continue;
            }

            QTableWidgetItem* pItem = ui->tabResult->takeHorizontalHeaderItem( nIndex );
            delete pItem;
            ui->tabResult->removeColumn( nIndex );
        }
        break;
    }

    if ( bTimeCard ) {
        strSql = QString ( "select a.cardno, a.cardfeebz, a.cardstate, a.cardkind, \
                           a.cardselfno from %1 a " ).arg( strTable );
    } else {
        strSql = QString( "select a.cardno, %1 a.cardstate, a.cardkind, a.cardselfno, \
                    a.cardcomment, a.cardcreator, \
                    b.username, b.usersex,b.userphone, \
                    c.carcp, c.carmodel ,c.carhaoma from %2 a \
                    inner join userinfo b on a.cardno = b.cardindex \
                    inner join carinfo c on a.cardno = c.cardindex " ).arg( strTmp, strTable );

                // '', '','', '', '' , '' from %2 a  " ).arg( strTmp, strTable );
        strCardSql = QString( "select a.cardno, %1 a.cardstate, a.cardkind, a.cardselfno, \
                              a.cardcomment, a.cardcreator, \
                              %2, %3 from %4 a  %5 %6" ).arg( strTmp, "%1", "%2", strTable, "%3", "%4" );
    }

    nCardType = nType;
    CCommonFunction::GetPath( strImagePath, CommonDataType::PathUIImage );
    strImagePath += "NewIcon/CommonMiddleBG-normal.jpg";
    QString strTitle[ ] = { "月租", "储值", "计时" };
    ui->lblTitle->setText( QString( "%1卡信息检索" ).arg( strTitle[ nCardType ] ) );

    setWindowFlags( Qt::FramelessWindowHint );

    setStyleSheet( QString( "background-image:url(%1);" ).arg( strImagePath ) );
}

CDlgSerach::~CDlgSerach()
{
    delete ui;
}

void CDlgSerach::resizeEvent( QResizeEvent *event )
{
    QWidget::resizeEvent( event );

    QPixmap bgimage( strImagePath );
    QPalette pal( palette( ) );
    pal.setBrush( QPalette::Window, QBrush( bgimage.scaled( event->size( ),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation ) ) );
    setPalette(pal);
}

void CDlgSerach::GetWhere( QString &strWhere, QString& strCard )
{
    strWhere.clear( );
    QString strAnd = " and ";
    QString strParams[ 4 ] = { "b.username, b.usersex,b.userphone",
                                                   "c.carcp, c.carmodel ,c.carhaoma",
                                                   "inner join userinfo b on a.cardno = b.cardindex",
                                                   "inner join carinfo c on a.cardno = c.cardindex" };

    //strCardSql = QString( "select a.cardno, %1 a.cardstate, a.cardkind, a.cardselfno, \
    //                      a.cardcomment, a.cardcreator, \
    //                      '', '','', '', '' , '' from %2 a  " ).arg( strTmp, strTable );

    QString strCardno = ui->edtCardno->text( );
    if ( !strCardno.isEmpty( ) ) {
        strWhere = QString( "a.cardno like '%%1%'" ).arg( strCardno );
    }

    QString strCardself = ui->edtCardselfno->text( );
    if ( !strCardself.isEmpty( ) ) {
        strWhere += QString( "%1a.cardselfno like '%%2%'" ).arg( strWhere.isEmpty( ) ? "" : strAnd, strCardself );
    }

    QString strOwner = ui->edtOwner->text( );
    if ( !strOwner.isEmpty( ) ) {
        strWhere += QString( "%1b.username like '%%2%'" ).arg( strWhere.isEmpty( ) ? "" : strAnd, strOwner );
    } else {
        strParams[ 0 ] = "'', '',''";
        strParams[ 2 ] = "";
    }

    QString strPlate = ui->edtPlate->text( );
    if ( !strPlate.isEmpty( ) ) {
        strWhere += QString( "%1c.carcp like '%%2%'" ).arg( strWhere.isEmpty( ) ? "" : strAnd, strPlate );
    } else {
        strParams[ 1 ] = "'', '' , ''";
        strParams[ 3 ] = "";
    }

    if ( !strWhere.isEmpty( ) ) {
        strWhere = " Where " + strWhere;
    }

    strCard = strCardSql.arg( strParams[ 0 ], strParams[ 1 ], strParams[ 2 ], strParams[ 3 ] );
}

void CDlgSerach::on_btnClose_clicked()
{
    QStringList lstRows;
    QString strWhere = "";
    QString strCard = "";

    GetWhere( strWhere, strCard );
    QString strTmp = strSql + strWhere;
    int nRows = 0;

    nRows = CLogicInterface::GetInterface( )->ExecuteSql( strTmp, lstRows );

    if ( !bTimeCard && 0 == nRows && !strWhere.isEmpty( ) ) {
        strTmp = strCard + strWhere;
        nRows = CLogicInterface::GetInterface( )->ExecuteSql( strTmp, lstRows );
    }

    CCommonFunction::FreeAllRows( ui->tabResult );
    CCommonFunction::FillTable( ui->tabResult, nRows, lstRows );
}

void CDlgSerach::on_lblClose_linkActivated(QString link)
{
    close( );
}

void CDlgSerach::on_tabResult_cellDoubleClicked(int row, int)
{
    emit PositionRow( ui->tabResult->item( row, 0 )->text( ) );
}

QLineEdit* CDlgSerach::GetEditCntrl( )
{
    return ui->edtCardno;
}
