#include "dlgalert.h"
#include "ui_dlgalert.h"
#include "SMS/sms.h"

CDlgAlert::CDlgAlert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgAlert)
{
    ui->setupUi(this);

    CCommonFunction::ConnectCloseButton( ui->lblClose );
    ui->lblTitle->setText( windowTitle( ) );

    QHeaderView* pHeader = ui->tabAlert->horizontalHeader( );
    int nIndex = 2;
    pHeader->resizeSection( nIndex, pHeader->sectionSize( nIndex ) * 2 );

    nIndex = 3;
    pHeader->resizeSection( nIndex, pHeader->sectionSize( nIndex ) * 2 );

    nIndex = 4;
    pHeader->hideSection( nIndex );

    strTrue = "1";
    strSeprator = "|";
    CCommonFunction::GetPath( strSnapPath, CommonDataType::PathSnapshot );
    setWindowFlags( Qt::FramelessWindowHint );
    move( 123, 177 );

    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CDlgAlert::~CDlgAlert( )
{
    delete ui;
}

void CDlgAlert::resizeEvent( QResizeEvent *event )
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

void CDlgAlert::on_lblClose_linkActivated(QString)
{
    close( );
}

void CDlgAlert::on_tabAlert_cellDoubleClicked(int row, int column )
{
    if ( 3 != column ) {
        return;
    }

    QString strAlert = ui->tabAlert->item( row, 4 )->text( );
    GetImage( strAlert );
}

void CDlgAlert::DisplayImage( QLabel* pLbl, CommonDataType::BlobType blob, QString &strWhere )
{
    QString strFile = strSnapPath + "alert.JPG";
    CLogicInterface* pInterface = CLogicInterface::GetInterface( );
    pInterface->OperateBlob( strFile, false, blob, strWhere );
    QPixmap map( strFile );
    pLbl->setPixmap( map );
}

void CDlgAlert::GetImage( QString &strAlert )
{
    //// PARKID / bool( 1 : plate 0 : cardid)  / Plate | CardID / IOFlag / DateTime / Alert
    QStringList lstParams = strAlert.split( strSeprator );
    bool bPlate = ( strTrue == lstParams[ 1 ] );
    bool bEnter =  ( strTrue == lstParams[ 3 ] );
    QString& strPlate = lstParams[ 2 ];

    QString strWhere = QString( "Where %1 = '%2' and %3time = '%4'" ).arg( bPlate ? QString( "carcp%1" ).arg( bEnter ? "" : "out" ) : "cardno",
                                                strPlate, bEnter ? "in" : "out",  lstParams[ 4 ] );
    CommonDataType::BlobType blob = bEnter ? CommonDataType::BlobVehicleIn1: CommonDataType::BlobVehicleOut1;
    DisplayImage( ui->lblInOut, blob, strWhere );

    strWhere = QString( "Where %1='%2'" ).arg( bPlate ? "carcp" : "cardindex", strPlate );
    blob = CommonDataType::BlobVehicle;
    DisplayImage( ui->lblCar, blob, strWhere );

    QStringList lstRow;
    if ( bPlate ) {
        CLogicInterface* pInterface = CLogicInterface::GetInterface( );
        QString strSql = QString( "Select cardindex From carinfo Where carcp = '%1'" ).arg( strPlate );
        if ( 0 < pInterface->ExecuteSql( strSql, lstRow ) ) {
            strPlate = lstRow[ 0 ];
        }
    }

    strWhere = QString( "Where cardindex='%1'" ).arg( strPlate );
    blob = CommonDataType::BlobOwner;
    DisplayImage( ui->lblOwner, blob, strWhere );
}

void CDlgAlert::SendSms( QString &strInfo )
{
    QStringList lstData;
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    lstData = pSet->value( "SMS/TelNumber", "13980548766" ).toString( ).split( "@ ");
    //lstData << "18980070013" ;//"18982073890" <<
    CSms::GetSingleton( ).SendMsg( lstData, strInfo );

}

void CDlgAlert::PlayAudio( QString &strName )
{
    CCommonFunction::PlayMusic( strName );
}

void CDlgAlert::DisplayAlert( QStringList &lstData )
{
    static QString strAlert[ ] = { "套牌嫌疑车", "假牌车", "黑名单车", "" };

    QStringList lstDisplay;
    int nIndex = lstData[ 5 ].toInt( );
    if ( 0 > nIndex || 2 < nIndex ) {
        nIndex = 3;
    }

    int nType = nIndex;

    bool bPlate = ( strTrue == lstData[ 1 ] );
    bool bEnter = ( strTrue == lstData[ 3 ] );
    lstDisplay << lstData[ 0 ]
                    << QString( "%1:%2" ).arg( bPlate ? "车牌" : "卡号", lstData[ 2 ] )
                    << QString( "%1:%2" ).arg( bEnter ? "进入" : "离开",  lstData[ 4 ] )
                    << strAlert[ nIndex ]
                     << lstData.join( strSeprator );

    int  nRow = 0;
    ui->tabAlert->insertRow( nRow );

    QTableWidgetItem* pItem = NULL;

    for ( nIndex = 0; nIndex < lstDisplay.count( ); nIndex++ ) {
        pItem = new QTableWidgetItem( lstDisplay[ nIndex ] );
        pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
        ui->tabAlert->setItem( nRow, nIndex, pItem );
    }

    //QString strInfo = "停车场：" + lstData[ 0 ] + " 车牌号：" + lstData[ 2 ] +  " " + strAlert[ nType ];
    QString strInfo = "停车场：前途演示环境，车牌号：" + lstData[ 2 ] +  "，报警类型：" + strAlert[ nType ];
    SendSms( strInfo );
    PlayAudio( strAlert[ nType ] );
}
