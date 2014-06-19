#include "dlginconformity.h"
#include "ui_dlginconformity.h"
#include "Common/logicinterface.h"

CDlgInconformity::CDlgInconformity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgInconformity)
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint );

    edtCntrl[ 0 ][ 0 ] = ui->edtInfo00;
    edtCntrl[ 0 ][ 1 ] = ui->edtInfo01;
    edtCntrl[ 0 ][ 2 ] = ui->edtInfo02;
    edtCntrl[ 0 ][ 3 ] = ui->edtInfo03;
    edtCntrl[ 0 ][ 4 ] = ui->edtInfo04;

    edtCntrl[ 1 ][ 0 ] = ui->edtInfo10;
    edtCntrl[ 1 ][ 1 ] = ui->edtInfo11;
    edtCntrl[ 1 ][ 2 ] = ui->edtInfo12;
    edtCntrl[ 1 ][ 3 ] = ui->edtInfo13;
    edtCntrl[ 1 ][ 4 ] = ui->edtInfo14;

    move( 980, 520 );

    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

void CDlgInconformity::closeEvent(QCloseEvent *)
{
    ClearData( );
}

void CDlgInconformity::ClearData( )
{
    for ( int nRow = 0; nRow < 2; nRow++ ) {
        for ( int nCol = 0; nCol < 5; nCol++ ) {
            edtCntrl[ nRow ][ nCol ]->clear( );
        }
    }
}

CDlgInconformity::~CDlgInconformity()
{
    delete ui;
}

void CDlgInconformity::resizeEvent( QResizeEvent * event )
{
    QWidget::resizeEvent( event );

    QString strFile = statusTip( );
    QPixmap bgimage( strFile );
    QPalette pal( palette( ) );
    pal.setBrush( QPalette::Window, QBrush( bgimage.scaled( event->size( ),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation ) ) );
    setPalette(pal);
}

void CDlgInconformity::FillCntrl( QStringList &lstRows, bool bCard )
{
    int nCount =  lstRows.count( );
    if ( 0 >= nCount ) {
        return;
    }

    if ( 5 < nCount ) {
        nCount -= ( ( nCount / 5 - 1 ) * 5 );
    }

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        edtCntrl[ bCard ][ nIndex ]->setText( lstRows[ nIndex ] );
    }
}

bool CDlgInconformity::GetInfomation( bool bEnter, QString &strPlate, QString &strCardID, char cCan )
{
    bool bNoRecord = false;

    ui->lblTitle->setText( ui->lblTitle->statusTip( ).arg( bEnter ? "入" : "出" ) );
    cCanAddr = cCan;
    // select cardno from monthcard where cardno in ( select cardindex from carinfo where carcp = strplate )
    // select cardno from monthcard where cardno in ( strCardID )
    QStringList lstRows;
    //QString strPlateSql = "Call InconformityInfo( '%1', '%2' );";
    QString strTable[ ] = { "monthcard", "savecard", "tmpcard" };
    QString strCardType [ ] = { "月租卡", "储值卡", "计时卡" };

    QString strSql[ ] = { "select a.cardindex, d.%1, b.username, b.userphone, a.carcp from carinfo a \
                     join userinfo b on a.carcp = '%2' and a.cardindex = b.cardindex \
                     join ( select '%3' from %4 where cardno in \
                            ( select cardindex from carinfo where carcp = '%5' ) ) d",
                     "select a.cardindex, d.%1, b.username, b.userphone, a.carcp from carinfo a \
                     join userinfo b on a.cardindex = '%2' and a.cardindex = b.cardindex  \
                     join ( select '%3' from %4 where cardno in ( '%5' ) ) d" };

    QString strTmpCard = QString( "select a.cardno, '%1' , '', '', '' from \
                                  tmpcard a where a.cardno = '%2'" ).arg( strCardType[ 2 ], strCardID );

    QString strTmp;

    bool bPlate = false;
    for ( int nRow = 0; nRow < 2; nRow ++ ) {
        bPlate = ( 0 == nRow );
        for ( int nIndex = 0; nIndex < 3; nIndex++ ) {
            if ( !bPlate && 2 == nIndex ) {
                strTmp = strTmpCard;
            } else {
                strTmp = strSql[ nRow ].arg( strCardType[ nIndex ], bPlate ? strPlate : strCardID, strCardType[ nIndex ],
                                                     strTable[ nIndex ], bPlate ? strPlate : strCardID );
            }

           if ( 0 < CLogicInterface::GetInterface( )->ExecuteSql( strTmp, lstRows ) ) {
                FillCntrl( lstRows, bPlate );
                break;
           } else if ( bPlate ) { // No Record
                ui->edtInfo14->setText( strPlate );
                bNoRecord = true;
           }
        }
    }

    return bNoRecord;
}

void CDlgInconformity::on_btn3_clicked()
{
    close( );
    setResult( CDlgInconformity::Rejected );
}

void CDlgInconformity::on_btn1_clicked()
{
    emit Pass( ui->edtInfo10->text( ), cCanAddr, ui->edtInfo14->text( ) );
    close( );
    setResult( CDlgInconformity::Rejected );
}

void CDlgInconformity::on_btn2_clicked()
{
    emit Pass( ui->edtInfo00->text( ), cCanAddr, ui->edtInfo14->text( ) );
    close( );
    setResult( CDlgInconformity::Rejected );
}

void CDlgInconformity::DefaultClicked( )
{
    on_btn2_clicked( );
}
