#include "Header/printmonthlyreport.h"
#include "ui_printmonthlyreport.h"

CPrintMonthlyReport::CPrintMonthlyReport(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CPrintMonthlyReport)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    setWindowFlags( Qt::FramelessWindowHint );
    nPlateChannel = 0;
    nPlateIndex = 0;

#ifdef NewUI
    move( 47, 430 );
#else
    move( 48, 546 );
#endif

    InitUI( );
}

CPrintMonthlyReport::~CPrintMonthlyReport()
{
    delete ui;
}

void CPrintMonthlyReport::showEvent(QShowEvent *)
{
    //ClearPlate( );
}

void CPrintMonthlyReport::ClearPlate( )
{
    QString strBtn = "btnRes%1";
    QPushButton* pBtn = NULL;

    for ( quint32 nIndex = 0; nIndex < 8; nIndex++ ) {
        pBtn = findChild< QPushButton* >( strBtn.arg( nIndex ) );
        pBtn->setText( "" );
    }
}

void CPrintMonthlyReport::closeEvent( QCloseEvent *event )
{
    //pParent->ControlChild( event, this );
}

void CPrintMonthlyReport::DisableChinese( )
{
    QString strBtn = "btn%1";
    QPushButton* pBtn = NULL;

    for ( int nIndex = 0; nIndex < nChineseCount; nIndex++ ) {
        pBtn = findChild< QPushButton* >( strBtn.arg( nIndex ) );
        pBtn->setEnabled( 1 == nPlateIndex );
    }
}

void CPrintMonthlyReport::InitUI( )
{
    nChineseCount = 0;
    strAbbreviation = "´¨¶õ¸Ê¸Ó¹ó¹ðºÚ»¦¼ª¼½½ò½ú¾©ÁÉÂ³ÃÉÃöÄþÇàÇíÉÂËÕÍîÏæÐÂÓåÔ¥ÔÁÔÆ²ØÕã";
    strAbbreviation += "ABCDEFGHIGKLMNOPQRSTUVWXYZ0123456789 ";
    strAbbreviation += "¼×ÒÒ±û¼º¸ýÐÁÈÉÒú³½ÊùÎçÎ´ÉêÏû±ßÍ¨É­½ð¾¯µç";

    int nCount = strAbbreviation.count( );
    QString strBtn = "btn%1";
    QPushButton* pBtn = NULL;

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        pBtn = findChild< QPushButton* >( strBtn.arg( nIndex ) );
        pBtn->setText( strAbbreviation.mid( nIndex, 1 ) );
        QObject::connect( pBtn, SIGNAL( clicked( ) ), this, SLOT( OnBtnClicked( ) ) );
    }

    strBtn = "btnRes%1";
    pBtn = NULL;

    for ( quint32 nIndex = 0; nIndex < 8; nIndex++ ) {
        pBtn = findChild< QPushButton* >( strBtn.arg( nIndex ) );
        QObject::connect( pBtn, SIGNAL( clicked( ) ), this, SLOT( OnBtnResClicked( ) ) );
    }
}

void CPrintMonthlyReport::InitResBtn( QString &strPlate )
{
    ClearPlate( );

    strPlates = strPlate;
    if ( strPlates.count( ) < 8 ) {
        strPlates.append( " " );
    }
    ConnectResBtn( strPlate.count( ), strPlate );
}

void CPrintMonthlyReport::ConnectResBtn( quint32 nCount, QString& strPlate )
{
    QString strBtn = "btnRes%1";
    QPushButton* pBtn = NULL;

    for ( quint32 nIndex = 0; nIndex < nCount; nIndex++ ) {
        pBtn = findChild< QPushButton* >( strBtn.arg( nIndex ) );
        pBtn->setText( QString( strPlate[ nIndex ] ) );
    }
}

void CPrintMonthlyReport::OnBtnResClicked( )
{
    nPlateIndex = sender( )->objectName( ).right( 1 ).toInt( );
}

void CPrintMonthlyReport::SetChannelIndex( int &nChannel, int &nIndex )
{
    nPlateChannel = nChannel;
    nPlateIndex = nIndex;

    //DisableChinese( );
}

void CPrintMonthlyReport::OnBtnClicked( )
{
    QPushButton* pBtn = qobject_cast< QPushButton* >( sender( ) );
    QString strValue = pBtn->text( );
    int nCount = strPlates.count( );
    for ( int nIndex = nCount; nIndex < 8; nIndex++ ) {
        strPlates.append( " " );
    }

    nCount = strPlates.count( );
    if ( nPlateIndex < nCount ) {
        strPlates.replace( nPlateIndex, 1, strValue );
        QString strBtn = "btnRes%1";
        QPushButton* pBtn = findChild< QPushButton* >( strBtn.arg( nPlateIndex ) );
        pBtn->setText( strValue );
    }

    if ( nPlateIndex < nCount - 1 ) {
        nPlateIndex++;
    }

    emit SendValue( strValue, nPlateChannel, nPlateIndex );
}

void CPrintMonthlyReport::on_btn99_clicked()
{
    strPlates.remove( " " );
    close( );
    //emit ManualRecogonization( nPlateChannel );
    emit ManualRecogonization( nPlateChannel, strPlates );
}

void CPrintMonthlyReport::on_btn96_clicked()
{
    close( );
}

void CPrintMonthlyReport::on_btnClear_clicked()
{
    close( );
    emit ClearMonitorPlate( nPlateChannel );
}
