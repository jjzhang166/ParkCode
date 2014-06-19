#include "Header/tariffsetting.h"
#include "ui_tariffsetting.h"
#include "Common/CommonType.h"
#include <QTextCodec>
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"

CTariffSetting::CTariffSetting(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CTariffSetting)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );

    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgTariff );

    GetAllParking( );
    CCommonFunction::GetCarType( ui->cbxType );
    CCommonFunction::GetCarType( ui->cbxStandard );

    ui->lblTitle->setText( windowTitle( ) );
    ControlUI( false );
}

void CTariffSetting::on_cbxType_currentIndexChanged(int index)
{
    if ( -1 == index )  {
        return;
    }

    GetTariff( );
}

void CTariffSetting::on_btnDownload_clicked( )
{
    //GetValue( false );
}

void CTariffSetting::on_btnSave_clicked( )
{
    SaveData( );
    CCommonFunction::OperationSuccess( );
}

void CTariffSetting::on_btnSaveExit_clicked( )
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CTariffSetting::ControlRuleUI( bool bInner, int nIndex, bool bEnabled )
{
    int nItems = 6;
    if ( nIndex > nItems ) {
        return;
    }

    QString strNameRule;
    QString strNameFoot;
    QString strRule = QString( "rule%1Min%2" );
    QString strFoot = QString( "rule%1Foot%2" );
    QSpinBox* pSB;
    QGroupBox* pGB = bInner ? ui->gbInnerFirst : ui->gbOuterFirst;

    for ( int nItem = nIndex + 1; nItem <= nItems; nItem++ ) {
        strNameRule = strRule.arg( QString::number( nItem ), bInner ? "Inner" : "Outer" );
        strNameFoot = strFoot.arg( QString::number( nItem ), bInner ? "Inner" : "Outer" );

        pSB = pGB->findChild< QSpinBox* >( strNameRule );
        pSB->setEnabled( false );
        pSB->setValue( 0 );

        pSB = pGB->findChild< QSpinBox* >( strNameFoot );
        pSB->setEnabled( false );
        pSB->setValue( 0 );
    }

    strNameFoot = strFoot.arg( QString::number( nIndex ), bInner ? "Inner" : "Outer" );
    pSB = pGB->findChild< QSpinBox* >( strNameFoot );
    pSB->setEnabled( bEnabled );
    if ( !bEnabled ) {
        pSB->setValue( 0 );
    }

    if ( nItems > nIndex ) {
        strNameRule = strRule.arg( QString::number( nIndex + 1 ), bInner ? "Inner" : "Outer" );
        pSB = pGB->findChild< QSpinBox* >( strNameRule );
        pSB->setEnabled( bEnabled );
        if ( !bEnabled ) {
            pSB->setValue( 0 );
        }
    }
}



void CTariffSetting::on_btnCalculate_clicked( )
{
    GetTariff( );
    QDateTime dtStart = ui->dtStart->dateTime( );
    QDateTime dtEnd = ui->dtEnd->dateTime( );
    QString strParkID = ui->cbxName->itemData( ui->cbxName->currentIndex( ) ).toString( );
    QString strFeeModel = QString::number( ui->cbxType->currentIndex( ) );
    QStringList lstText;
    uint nFee = CCommonFunction::CalculateFee( *pSettings, strParkID, strFeeModel, dtStart,
                                               dtEnd, lstText, true, ui->rbtnSection->isChecked( ) );

    CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                             QString( "收费%1元" ).arg( QString::number( nFee ) ), QMessageBox::Information );
}

void CTariffSetting::GetWhere( QString &strWhere )
{
    QString strParkID = ui->cbxName->itemData( ui->cbxName->currentIndex( ) ).toString( );
    QString strFeeModel = QString::number( ui->cbxType->currentIndex( ) );
    strWhere = QString( " Where rparkid = %1 And rfeemodel = %2 " ).arg( strParkID, strFeeModel );
}

void CTariffSetting::GetTariff(  )
{
    QStringList lstRows;
    QString strWhere;
    GetWhere( strWhere );

    CLogicInterface::GetInterface( )->OperateTariffInfo( lstRows, CommonDataType::SelectData, strWhere );

    if ( 1 > lstRows.count( ) ) {
        return;
    }

    int nField = 2;
    ui->spLimitTime->setValue( lstRows[ nField++ ].toInt( ) );
    ui->spNoFullTime->setValue( lstRows[ nField++ ].toInt( ) );

    ui->tdtSection1->setTime( CCommonFunction::String2Time( lstRows[ nField++ ] ) );//QTime
    ui->tdtSection2->setTime( CCommonFunction::String2Time( lstRows[ nField++ ] ) );

    //ui->rbtnNoSection->setChecked( pSettings->value( strSection.arg( "NoSection" ), true ).toBool( ) );// bool
    //ui->rbtnSection->setChecked( pSettings->value( strSection.arg( "Section" ), false ).toBool( ) );
    //ControlUI( !ui->rbtnNoSection->isChecked( ) );

    ui->rule1MinInner->setValue( lstRows[ nField++ ].toInt( ) );//int
    ui->rule1FootInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule2MinInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule2FootInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule3MinInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule3FootInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule4MinInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule4FootInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule5MinInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule5FootInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule6MinInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule6FootInner->setValue( lstRows[ nField++ ].toInt( ) );

    ui->rule1MinOuter->setValue( lstRows[ nField++ ].toInt( ) );//int
    ui->rule1FootOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule2MinOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule2FootOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule3MinOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule3FootOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule4MinOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule4FootOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule5MinOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule5FootOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule6MinOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->rule6FootOuter->setValue( lstRows[ nField++ ].toInt( ) );

    ui->perMinInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->perMinFootInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->perMinOuter->setValue( lstRows[ nField++ ].toInt( ) );
    ui->perMinFootOuter->setValue( lstRows[ nField++ ].toInt( ) );

    ui->spLimitFootInner->setValue( lstRows[ nField++ ].toInt( ) );
    ui->spLimitFootOuter->setValue( lstRows[ nField++ ].toInt( ) );

    ui->perMinNoSectionLimit->setValue( lstRows[ nField++ ].toInt( ) );
    ui->perMinFootNoSection->setValue( lstRows[ nField++ ].toInt( ) );

    ui->perMinNoSectionFirst->setValue( lstRows[ nField++ ].toInt( ) );

    bool bSection = lstRows[ nField++ ].toInt( ) == 0 ? false : true;

    if ( bSection ) {
        ui->rbtnSection->setChecked( true );
    } else {
        ui->rbtnNoSection->setChecked( true );
    }

    ControlUI( !ui->rbtnNoSection->isChecked( ) );
}

void CTariffSetting::GetAllParking( )
{
    //parkname,parkindex, parknum,shebeiid
    QStringList lstRows;
    CLogicInterface::GetInterface( )->GetAllParks( lstRows );

    int nCount = lstRows.count( );
    int nRows = nCount / 4;
    int nField = 0;
    int nCols = 4;

    ui->cbxName->clear( );
    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        nField = nCols * nRow;
        QString& strName = lstRows[ nField++ ];
        QString& strID = lstRows[ nField++ ];
        ui->cbxName->addItem( strName, strID );
    }

    //ui->cbxType->setCurrentIndex( 0 );
    return;
    // Get All Park Name
    // Fill ui->cbxName

    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgDevice );
    QString strSection = "Section%1/%2";
    int nSection = pSet->value( strSection.arg( "", "Count" ), QVariant( 0 ) ).toInt( );
    QString strName;
    int nIndex = 0;

    ui->cbxName->clear( );

    for ( nIndex = 0; nIndex < nSection; nIndex++ ) {
        strName = pSet->value( strSection.arg( QString::number( nIndex ), "ParkName"  ), QVariant( "" ) ).toString( );
        if ( !strName.isEmpty( ) ) {
            ui->cbxName->addItem( strName );
        }
    }
}

void CTariffSetting::ControlUI(bool bSection )
{
    ui->gbTimeSection->setEnabled( bSection );
    ui->gbOuter->setEnabled( bSection );

    ui->spLimitFootInner->setEnabled( bSection );
    ui->spLimitFootOuter->setEnabled( bSection );

    ui->gbNoSecQuota1->setEnabled( !bSection );
    ui->gbNoSecQuota2->setEnabled( !bSection );
}

void CTariffSetting::ReadIniFile( )
{
    QString strSection = "%1/%2/";
    strSection = strSection.arg( ui->cbxName->currentText( ), ui->cbxType->currentText( ) );
    strSection += "%1";

    ui->spLimitTime->setValue( pSettings->value( strSection.arg( "LimitTime" ), QVariant( 0 ) ).toInt( ) );
    ui->spNoFullTime->setValue( pSettings->value( strSection.arg( "NoFullTime" ), QVariant( 0 ) ).toInt( ) );

    //QVariant v1 = pSettings->value( strSection.arg( "Section1" ), "00:00:00" );
    //QVariant v2 = pSettings->value( strSection.arg( "Section2" ), "23:59:59" );
    ui->tdtSection1->setTime( pSettings->value( strSection.arg( "Section1" ), "00:00:00" ).toTime( ) );//QTime
    ui->tdtSection2->setTime( pSettings->value( strSection.arg( "Section2" ), "23:59:59" ).toTime( ) );

    ui->rbtnNoSection->setChecked( pSettings->value( strSection.arg( "NoSection" ), true ).toBool( ) );// bool
    ui->rbtnSection->setChecked( pSettings->value( strSection.arg( "Section" ), false ).toBool( ) );
    ControlUI( !ui->rbtnNoSection->isChecked( ) );

    ui->rule1MinInner->setValue( pSettings->value( strSection.arg( "rule1MinInner" ), 0 ).toInt( ) );//int
    ui->rule1FootInner->setValue( pSettings->value( strSection.arg( "rule1FootInner" ), 0 ).toInt( ) );
    ui->rule2MinInner->setValue( pSettings->value( strSection.arg( "rule2MinInner" ), 0 ).toInt( ) );
    ui->rule2FootInner->setValue( pSettings->value( strSection.arg( "rule2FootInner" ), 0 ).toInt( ) );
    ui->rule3MinInner->setValue( pSettings->value( strSection.arg( "rule3MinInner" ), 0 ).toInt( ) );
    ui->rule3FootInner->setValue( pSettings->value( strSection.arg( "rule3FootInner" ), 0 ).toInt( ) );
    ui->rule4MinInner->setValue( pSettings->value( strSection.arg( "rule4MinInner" ), 0 ).toInt( ) );
    ui->rule4FootInner->setValue( pSettings->value( strSection.arg( "rule4FootInner" ), 0 ).toInt( ) );
    ui->rule5MinInner->setValue( pSettings->value( strSection.arg( "rule5MinInner" ), 0 ).toInt( ) );
    ui->rule5FootInner->setValue( pSettings->value( strSection.arg( "rule5FootInner" ), 0 ).toInt( ) );
    ui->rule6MinInner->setValue( pSettings->value( strSection.arg( "rule6MinInner" ), 0 ).toInt( ) );
    ui->rule6FootInner->setValue( pSettings->value( strSection.arg( "rule6FootInner" ), 0 ).toInt( ) );
    //ui->rule7MinInner->setValue( pSettings->value( strSection.arg( "rule7MinInner" ), 0 ).toInt( ) );
    //ui->rule7FootInner->setValue( pSettings->value( strSection.arg( "rule7FootInner" ), 0 ).toInt( ) );

    ui->rule1MinOuter->setValue( pSettings->value( strSection.arg( "rule1MinOuter" ), 0 ).toInt( ) );//int
    ui->rule1FootOuter->setValue( pSettings->value( strSection.arg( "rule1FootOuter" ), 0 ).toInt( ) );
    ui->rule2MinOuter->setValue( pSettings->value( strSection.arg( "rule2MinOuter" ), 0 ).toInt( ) );
    ui->rule2FootOuter->setValue( pSettings->value( strSection.arg( "rule2FootOuter" ), 0 ).toInt( ) );
    ui->rule3MinOuter->setValue( pSettings->value( strSection.arg( "rule3MinOuter" ), 0 ).toInt( ) );
    ui->rule3FootOuter->setValue( pSettings->value( strSection.arg( "rule3FootOuter" ), 0 ).toInt( ) );
    ui->rule4MinOuter->setValue( pSettings->value( strSection.arg( "rule4MinOuter" ), 0 ).toInt( ) );
    ui->rule4FootOuter->setValue( pSettings->value( strSection.arg( "rule4FootOuter" ), 0 ).toInt( ) );
    ui->rule5MinOuter->setValue( pSettings->value( strSection.arg( "rule5MinOuter" ), 0 ).toInt( ) );
    ui->rule5FootOuter->setValue( pSettings->value( strSection.arg( "rule5FootOuter" ), 0 ).toInt( ) );
    ui->rule6MinOuter->setValue( pSettings->value( strSection.arg( "rule6MinOuter" ), 0 ).toInt( ) );
    ui->rule6FootOuter->setValue( pSettings->value( strSection.arg( "rule6FootOuter" ), 0 ).toInt( ) );
    //ui->rule7MinOuter->setValue( pSettings->value( strSection.arg( "rule7MinOuter" ), 0 ).toInt( ) );
    //ui->rule7FootOuter->setValue( pSettings->value( strSection.arg( "rule7FootOuter" ), 0 ).toInt( ) );

    ui->perMinInner->setValue( pSettings->value( strSection.arg( "perMinInner" ), 0 ).toInt( ) );
    ui->perMinFootInner->setValue( pSettings->value( strSection.arg( "perMinFootInner" ),0  ).toInt( ) );
    ui->perMinOuter->setValue( pSettings->value( strSection.arg( "perMinOuter" ), 0 ).toInt( ) );
    ui->perMinFootOuter->setValue( pSettings->value( strSection.arg( "perMinFootOuter" ), 0 ).toInt( ) );

    ui->spLimitFootInner->setValue( pSettings->value( strSection.arg( "LimitFootInner" ), 0 ).toInt( ) );
    ui->spLimitFootOuter->setValue( pSettings->value( strSection.arg( "LimitFootOuter" ), 0 ).toInt( ) );

    ui->perMinNoSectionLimit->setValue( pSettings->value( strSection.arg( "perMinNoSectionLimit" ), 0 ).toInt( ) );
    ui->perMinFootNoSection->setValue( pSettings->value( strSection.arg( "perMinFootNoSection" ), 0 ).toInt( ) );

    ui->perMinNoSectionFirst->setValue( pSettings->value( strSection.arg( "perMinNoSectionFirst" ), 0 ).toInt( ) );

    bool bSection = pSettings->value( strSection.arg( "Section" ), 0 ).toInt( ) == 0 ? false : true;

    if ( bSection ) {
        ui->rbtnSection->setChecked( true );
    } else {
        ui->rbtnNoSection->setChecked( true );
    }
}

void CTariffSetting::WriteIniFile( )
{
    int nCount = ui->cbxType->count( );
    QString strSection = "CarType/%1%2";

    pSettings->remove( strSection.arg( "", "" ) );
    pSettings->setValue( strSection.arg( "Count", "" ), QString::number( nCount ));
    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        pSettings->setValue( strSection.arg( "Count", QString::number( nIndex ) ), ui->cbxType->itemText( nIndex ) );
    }

    strSection = "%1";
    strSection = strSection.arg( ui->cbxName->currentText( ) );
    pSettings->beginGroup( strSection );

    strSection = QString( "%1/" ).arg( ui->cbxType->currentText( ) );
    strSection += "%1";

    pSettings->setValue( strSection.arg( "LimitTime" ), ui->spLimitTime->value( ) );
    pSettings->setValue( strSection.arg( "NoFullTime" ), ui->spNoFullTime->value( ) );

    pSettings->setValue( strSection.arg( "Section1" ), ui->tdtSection1->time( ).toString( "hh:mm:ss" ) );//QTime
    pSettings->setValue( strSection.arg( "Section2" ), ui->tdtSection2->time( ).toString( "hh:mm:ss" ) );

    //pSettings->setValue( strSection.arg( "NoSection" ), ui->rbtnNoSection->isChecked( ) );// bool
    pSettings->setValue( strSection.arg( "Section" ), ui->rbtnSection->isChecked( ) ? 1 : 0 );

    pSettings->setValue( strSection.arg( "rule1MinInner" ), ui->rule1MinInner->value( ) );//int
    pSettings->setValue( strSection.arg( "rule1FootInner" ), ui->rule1FootInner->value( ) );
    pSettings->setValue( strSection.arg( "rule2MinInner" ), ui->rule2MinInner->value( ) );
    pSettings->setValue( strSection.arg( "rule2FootInner" ), ui->rule2FootInner->value( ) );
    pSettings->setValue( strSection.arg( "rule3MinInner" ), ui->rule3MinInner->value( ) );
    pSettings->setValue( strSection.arg( "rule3FootInner" ), ui->rule3FootInner->value( ) );
    pSettings->setValue( strSection.arg( "rule4MinInner" ), ui->rule4MinInner->value( ) );
    pSettings->setValue( strSection.arg( "rule4FootInner" ), ui->rule4FootInner->value( ) );
    pSettings->setValue( strSection.arg( "rule5MinInner" ), ui->rule5MinInner->value( ) );
    pSettings->setValue( strSection.arg( "rule5FootInner" ), ui->rule5FootInner->value( ) );
    pSettings->setValue( strSection.arg( "rule6MinInner" ), ui->rule6MinInner->value( ) );
    pSettings->setValue( strSection.arg( "rule6FootInner" ), ui->rule6FootInner->value( ) );
    //pSettings->setValue( strSection.arg( "rule7MinInner" ), ui->rule7MinInner->value( ) );
    //pSettings->setValue( strSection.arg( "rule7FootInner" ), ui->rule7FootInner->value( ) );

    pSettings->setValue( strSection.arg( "rule1MinOuter" ), ui->rule1MinOuter->value( ) );//int
    pSettings->setValue( strSection.arg( "rule1FootOuter" ), ui->rule1FootOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule2MinOuter" ), ui->rule2MinOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule2FootOuter" ), ui->rule2FootOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule3MinOuter" ), ui->rule3MinOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule3FootOuter" ), ui->rule3FootOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule4MinOuter" ), ui->rule4MinOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule4FootOuter" ), ui->rule4FootOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule5MinOuter" ), ui->rule5MinOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule5FootOuter" ), ui->rule5FootOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule6MinOuter" ), ui->rule6MinOuter->value( ) );
    pSettings->setValue( strSection.arg( "rule6FootOuter" ), ui->rule6FootOuter->value( ) );
    //pSettings->setValue( strSection.arg( "rule7MinOuter" ), ui->rule7MinOuter->value( ) );
    //pSettings->setValue( strSection.arg( "rule7FootOuter" ), ui->rule7FootOuter->value( ) );

    pSettings->setValue( strSection.arg( "perMinInner" ), ui->perMinInner->value( ) );
    pSettings->setValue( strSection.arg( "perMinFootInner" ), ui->perMinFootInner->value( ) );
    pSettings->setValue( strSection.arg( "perMinOuter" ), ui->perMinOuter->value( ) );
    pSettings->setValue( strSection.arg( "perMinFootOuter" ), ui->perMinFootOuter->value( ) );

    pSettings->setValue( strSection.arg( "LimitFootInner" ), ui->spLimitFootInner->value( ) );
    pSettings->setValue( strSection.arg( "LimitFootOuter" ), ui->spLimitFootOuter->value( ) );

    pSettings->setValue( strSection.arg( "perMinNoSectionLimit" ), ui->perMinNoSectionLimit->value( ) );
    pSettings->setValue( strSection.arg( "perMinFootNoSection" ), ui->perMinFootNoSection->value( ) );

    pSettings->setValue( strSection.arg( "perMinNoSectionFirst" ), ui->perMinNoSectionFirst->value( ) );
    //pSettings->setValue( strSection.arg( "Section" ), ui->->value( ) );

    pSettings->endGroup( );

    pSettings->sync( );
}

void CTariffSetting::SaveData( )
{
    QStringList lstRows;
    QString strWhere;
    GetWhere( strWhere );
    GetValue( lstRows );

    CLogicInterface::GetInterface( )->OperateTariffInfo( lstRows, CommonDataType::UpdateData, strWhere );

    WriteIniFile( );
}

void CTariffSetting::GetValue( QStringList& lstValues )
{
    lstValues << QString::number( ui->spLimitTime->value( ) );
    lstValues << QString::number( ui->spNoFullTime->value( ) );

    QString strTime;
    QTime time = ui->tdtSection1->time( );
    CCommonFunction::Time2String( time, strTime );
    lstValues << strTime;//QTime
    time = ui->tdtSection2->time( );
    CCommonFunction::Time2String( time, strTime );
    lstValues << strTime;

    lstValues << QString::number( ui->rule1MinInner->value( ) );//int
    lstValues << QString::number( ui->rule1FootInner->value( ) );
    lstValues << QString::number( ui->rule2MinInner->value( ) );
    lstValues << QString::number( ui->rule2FootInner->value( ) );
    lstValues << QString::number( ui->rule3MinInner->value( ) );
    lstValues << QString::number( ui->rule3FootInner->value( ) );
    lstValues << QString::number( ui->rule4MinInner->value( ) );
    lstValues << QString::number( ui->rule4FootInner->value( ) );
    lstValues << QString::number( ui->rule5MinInner->value( ) );
    lstValues << QString::number( ui->rule5FootInner->value( ) );
    lstValues << QString::number( ui->rule6MinInner->value( ) );
    lstValues << QString::number( ui->rule6FootInner->value( ) );

    lstValues << QString::number( ui->rule1MinOuter->value( ) );//int
    lstValues << QString::number( ui->rule1FootOuter->value( ) );
    lstValues << QString::number( ui->rule2MinOuter->value( ) );
    lstValues << QString::number( ui->rule2FootOuter->value( ) );
    lstValues << QString::number( ui->rule3MinOuter->value( ) );
    lstValues << QString::number( ui->rule3FootOuter->value( ) );
    lstValues << QString::number( ui->rule4MinOuter->value( ) );
    lstValues << QString::number( ui->rule4FootOuter->value( ) );
    lstValues << QString::number( ui->rule5MinOuter->value( ) );
    lstValues << QString::number( ui->rule5FootOuter->value( ) );
    lstValues << QString::number( ui->rule6MinOuter->value( ) );
    lstValues << QString::number( ui->rule6FootOuter->value( ) );

    lstValues << QString::number( ui->perMinInner->value( ) );
    lstValues << QString::number( ui->perMinFootInner->value( ) );
    lstValues << QString::number( ui->perMinOuter->value( ) );
    lstValues << QString::number( ui->perMinFootOuter->value( ) );

    lstValues << QString::number( ui->spLimitFootInner->value( ) );
    lstValues << QString::number( ui->spLimitFootOuter->value( ) );

    lstValues << QString::number( ui->perMinNoSectionLimit->value( ) );
    lstValues << QString::number( ui->perMinFootNoSection->value( ) );

    lstValues << QString::number( ui->perMinNoSectionFirst->value( ) );
    lstValues << QString::number( ui->rbtnSection->isChecked( ) ? 1 : 0 );
}

CTariffSetting::~CTariffSetting()
{
    delete ui;
}

void CTariffSetting::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CTariffSetting::CalculatePos( )
{
#ifdef NewUI
    move( 123, 43 );
#else
    move( 123, 177 );
#endif
#if 0
    QRect rectWnd = this->geometry( );

    QString strName = "widget";
    QWidget* pWg = findChild< QWidget* >( strName );
    QRect rectWg = pWg->geometry( );
    pWg->setGeometry( ( rectWnd.width( ) - rectWg.width( ) - 2 ) / 2,
                      ( rectWnd.height( )  - rectWg.height( ) - 2 ) / 2,
                      rectWg.width( ), rectWg.height( ) );

    ///////////////////////////////////////////////////////////
    QRect rectTabWidget = ui->tabWidget->geometry( );

    strName.clear( );
    strName.append( "wgTime" );
    QWidget* pWgTime = findChild< QWidget* >( strName );
    QRect rectWgTime = pWgTime->geometry( );
    pWgTime->setGeometry( ( rectTabWidget.width( ) - 2 - rectWgTime.width( ) ) / 2,
                          ( rectTabWidget.height( )  - 26 - rectWgTime.height( ) ) / 2,
                          rectWgTime.width( ), rectWgTime.height( ) );

    strName.clear( );
    strName.append( "wgRate" );
    QWidget* pWgRate = findChild< QWidget* >( strName );
    QRect rectWgRate = pWgRate->geometry( );
    pWgRate->setGeometry( ( rectTabWidget.width( ) - 2 - rectWgRate.width( ) ) / 2,
                          ( rectTabWidget.height( )  - 26 - rectWgRate.height( ) ) / 2,
                          rectWgRate.width( ), rectWgRate.height( ) );
#endif
}

void CTariffSetting::resizeEvent( QResizeEvent* )
{
    CalculatePos( );
}

void CTariffSetting::on_rbtnNoSection_clicked()
{
    ControlUI( false );
}

void CTariffSetting::on_rbtnSection_clicked()
{
    ControlUI( true );
}

void CTariffSetting::on_rule1MinInner_valueChanged( int nValue )
{
    ControlRuleUI( true, 1, nValue != 0 );
}

void CTariffSetting::on_rule2MinInner_valueChanged( int nValue )
{
    ControlRuleUI( true, 2, nValue != 0 );
}

void CTariffSetting::on_rule3MinInner_valueChanged( int nValue )
{
    ControlRuleUI( true, 3, nValue != 0 );
}

void CTariffSetting::on_rule4MinInner_valueChanged( int nValue )
{
    ControlRuleUI( true, 4, nValue != 0 );
}

void CTariffSetting::on_rule5MinInner_valueChanged( int nValue )
{
    ControlRuleUI( true, 5, nValue != 0 );
}

void CTariffSetting::on_rule6MinInner_valueChanged( int nValue )
{
    ControlRuleUI( true, 6, nValue != 0 );
}

void CTariffSetting::on_rule7MinInner_valueChanged( int nValue )
{
    ControlRuleUI( true, 7, nValue != 0 );
}

void CTariffSetting::on_rule1MinOuter_valueChanged( int nValue )
{
    ControlRuleUI( false, 1, nValue != 0 );
}

void CTariffSetting::on_rule2MinOuter_valueChanged( int nValue )
{
    ControlRuleUI( false, 2, nValue != 0 );
}

void CTariffSetting::on_rule3MinOuter_valueChanged( int nValue )
{
    ControlRuleUI( false, 3, nValue != 0 );
}

void CTariffSetting::on_rule4MinOuter_valueChanged( int nValue )
{
    ControlRuleUI( false, 4, nValue != 0 );
}

void CTariffSetting::on_rule5MinOuter_valueChanged( int nValue )
{
    ControlRuleUI( false, 5, nValue != 0 );
}

void CTariffSetting::on_rule6MinOuter_valueChanged( int nValue )
{
    ControlRuleUI( false, 6, nValue != 0 );
}

void CTariffSetting::on_rule7MinOuter_valueChanged( int nValue )
{
    ControlRuleUI( false, 7, nValue != 0 );
}

void CTariffSetting::CompareTime( QTimeEdit &edtTime, QTime &time, bool bSequence )
{
    if ( !edtTime.isVisible( ) ) {
        return;
    }

    bool bDisplay = bSequence ? ( time > edtTime.time( ) ) : ( time < edtTime.time( ) );
    QString strStyle = bDisplay ? "background-color: rgb(255, 0, 0);" :
                       "background-color: rgb(255, 255, 255);";

    if ( bDisplay ) {
        edtTime.setFocus( );
        QString strInfo = QString( "%1时间不能%2于%3时间" ).arg( bSequence ? "截止" : "起始",
                                                          bSequence ? "小" : "大",
                                                          bSequence ? "起始" : "截止" );
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 strInfo, QMessageBox::Information );
    }

    QString strWhite = "background-color: rgb(255, 255, 255);";

    ui->tdtSection1->setStyleSheet( strWhite );
    ui->tdtSection2->setStyleSheet( strWhite );

    edtTime.setStyleSheet( strStyle );
}

void CTariffSetting::on_tdtSection1_timeChanged(QTime date)
{
    //CompareTime( *ui->tdtSection2, date, true );
}

void CTariffSetting::on_tdtSection2_timeChanged(QTime date)
{
    //CompareTime( *ui->tdtSection1, date, false );
}

void CTariffSetting::on_tabWidget_currentChanged(int index)
{
    if ( 1 == index ) {
        ;//GetValue( false );
    }
}

void CTariffSetting::ControlPerMinUI( bool bInner, bool bEnabled )
{
    QString strPerOuter = "perMinFoot%1";

    QGroupBox* pGB = bInner ? ui->gbInner : ui->gbOuter;

    QSpinBox* pSB = pGB->findChild< QSpinBox* >( strPerOuter.arg( bInner ? "Inner" : "Outer" ) );
    pSB->setEnabled( bEnabled );

    if( !bEnabled ) {
        pSB->setValue( 0 );
    }
}

void CTariffSetting::on_perMinInner_valueChanged(int nValue )
{
    ControlPerMinUI( true, nValue != 0 );
}

void CTariffSetting::on_perMinOuter_valueChanged(int nValue )
{
    ControlPerMinUI( false, nValue != 0 );
}

void CTariffSetting::on_cbxName_currentIndexChanged(int index)
{
    if ( -1 == index )  {
        return;
    }

    GetTariff( );
}

void CTariffSetting::on_lblClose_linkActivated(QString)
{
    close( );
}
