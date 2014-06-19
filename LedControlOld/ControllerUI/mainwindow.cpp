#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdlgconfig.h"
#include <QFileDialog>
#include <QDebug>

//
// Command request, Command response
//

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitializeCB( ui->cbLightSensitiveFlash );
    InitializeCB( ui->cbLightSensitiveFreq );
    InitializeSlot( );
    DlgConfig( );
    QControllerCommon::InitApp( );
    controller.ConrollSP( true );
    InitializeUI( );

    nTimerID = startTimer( 1000 * 10 ); //10
}

void MainWindow::SetQueryTemplate( )
{
    ui->edtState->clear( );

    strState = "频闪光敏控制 %1\n";
    strState += "闪光光敏控制 %2\n";
    strState += "温度 %3摄氏度\n";
    strState += "灯工作状态 %4\n";
    strState += "频闪触发方式 %5\n";
    strState += "闪光触发方式 %6\n";
    strState += "频闪时间（百分比显示）频闪时间 %7%\n";
    strState += "闪光时间（百分比显示）闪光时间 %8%\n";
    strState += "频闪亮度（百分比显示）频闪亮度 %9%\n";
    strState += "闪光亮度（百分比显示）闪光亮度 %10%\n";
    strState += "频闪光敏阀值 %11\n";
    strState += "闪光光敏阀值 %12\n";
    strState += "频闪频率 %13Hz\n";
    strState += "LED灯工作电压 %14伏\n";
    strState += "外部触发信号状态 %15";
    strState += "帧频 %16";
}

void MainWindow::InitializeUI( )
{
    ui->cbMode->setVisible( false );
    ui->btnQuery->setVisible( false );
    ui->chkQuery->setVisible( false );
    ui->tabWidgetDevice->setCurrentIndex( 0 );
    ui->tabWidget->setCurrentIndex( 1 );
    //ui->spLightSensitiveFlash->setVisible( false );
    //ui->spLightSensitiveFreq->setVisible( false );

    controllerCmd = QControllerCmd::GetSingleton( );
    GetQueryCmd( byQueryCmds );

    SetQueryTemplate( );
    //SetOldMaxSize( );

    LedControll::SSysConfig sConfig;
    QControllerCommon::GetSystemConfig( sConfig );
    //InitializeUI( sConfig, false );
    //InitializeUI( sConfig, true );

    connect( &controller, SIGNAL( Cmd( QByteArray, bool ) ), this, SLOT( HandleCmd( QByteArray, bool ) ) );
    connect( &controller, SIGNAL( Data( QByteArray ) ), this, SLOT( HandleData( QByteArray ) ) );
    connect( &controller, SIGNAL( Query( QString, qint8, QByteArray ) ), this, SLOT( HandleQuery( QString, qint8, QByteArray ) ) );

    on_btnQuery_clicked( );
    ui->chkQuery->setChecked( false );
}

void MainWindow::HandleCmd( QByteArray data, bool bSend )
{
    QString strText( data.toHex( ).toUpper( ) );
    strText += "\n";
    bSend ? ui->edtSendCmd->appendPlainText( strText ) :
            ui->edtReceiveCmd->appendPlainText( strText );
}

void MainWindow::HandleData( QByteArray data )
{
    QString strText( data.toHex( ).toUpper( ) );
    ui->edtDataStream->appendPlainText( strText );
}

void MainWindow::HandleQuery( QString strInfo, qint8 nIndex, QByteArray byData )
{
    if ( 0 == nIndex ) {
        QString strTitle = objectName( ) + " 与设备连接上。";
        setWindowTitle( strTitle );
    }

    if ( 1 > nIndex || QUERY_CMD_COUNT < nIndex ) {
        return;
    }

    ui->edtState->clear( );
    strStateValue[ nIndex - 1 ] = strInfo;

    QString strText = strState.arg( strStateValue[ 0 ], strStateValue[ 1 ], strStateValue[ 2 ],
                                                    strStateValue[ 3 ], strStateValue[ 4 ], strStateValue[ 5 ],
                                                    strStateValue[ 6 ], strStateValue[ 7 ], strStateValue[ 8 ] );
    strText = strText.arg( strStateValue[ 9 ], strStateValue[ 10 ], strStateValue[ 11 ],
                                      strStateValue[ 12 ], strStateValue[ 13 ], strStateValue[ 14 ], strStateValue[ 15 ] );
    ui->edtState->appendPlainText( strText );

    UpdateUI( nIndex - 1, byData );
}

void MainWindow::UpdateUI( qint8 nIndex, QByteArray byData )
{
    if ( 0 >= byData.count( )  ) {
        return;
    }

    qint8 nValue = byData.at( 0 );

    switch ( nIndex ) {
    case 0 : // 频闪光敏控制
        ui->chkLightSensitiveFreq->setChecked( 0 !=nValue );
        break;

    case 1 : // 闪光光敏控制
        ui->chkLightSensitiveFlash->setChecked( 0 != nValue );
        break;

    case 4 : // 频闪触发方式
        ClearRadioboxValue( hashFreqSync, nValue + 1 );
        break;

    case 5 : // 闪光触发方式
        ClearRadioboxValue( hashFlashSync, nValue + 1 );
        break;

    case 6 : // 频闪时间
        ui->spFreqTimeNew->setValue( nValue );//
        break;

    case 7 : // 闪光时间
        ui->spFlashTimeNew->setValue( nValue );//
        break;

    case 8 : // 频闪亮度
        ui->spLightSensitiveFreq->setValue( nValue );
        break;

    case 9 : // 闪光亮度
        ui->spLightSensitiveFlash->setValue( nValue );
        break;

    case 10 : // 频闪光敏阀值
        SetComboxValue( ui->cbLightSensitiveFreq, nValue );
        break;

    case 11 : // 闪光光敏阀值
        SetComboxValue( ui->cbLightSensitiveFlash, nValue );
        break;

    case 15 : // 帧频控制
        SetComboxValue( ui->cbLightFrameFreq, nValue );
        break;
    }
}

void MainWindow::SetComboxValue( QComboBox *pCB, qint8 nValue )
{
    if ( pCB == ui->cbLightFrameFreq ) {
        pCB->setCurrentIndex( nValue - 1 );
        return;
    }

    for ( qint32 nIndex = 0; nIndex < pCB->count( ); nIndex++ ) {
        if ( ( qint8 ) pCB->itemData( nIndex ).toInt( ) == nValue )  {
            pCB->setCurrentIndex( nIndex );
            break;
        }
    }
}

void MainWindow::ClearRadioboxValue( QHash< char, QRadioButton* >& hash, qint8 nKey )
{
    QRadioButton* pRB = hash.value( nKey );
    if ( NULL == pRB ) {
        return;
    }

    for ( qint32 nIndex = 1; nIndex <= hash.count( ); nIndex++ ) {
        hash.value( nIndex )->setChecked( false );
    }

    pRB->setChecked( true );
}

void MainWindow::InitializeUI( const QString &strFile, const bool bNewDev )
{
    LedControll::SSysConfig sConfig;
    QControllerCommon::GetSystemConfig( sConfig, strFile );
    InitializeUI( sConfig, bNewDev );
}

void MainWindow::GetCheckBoxState( QHash<char, QRadioButton *> &hash, char c )
{
    QRadioButton* pButton = hash.value( c );
    if ( NULL != pButton ) {
        pButton->setChecked( true );
    }
}

void MainWindow::SetSpinBoxValue( const LedControll::SSysConfig &sConfig, const bool bNewDev )
{
    if ( !bNewDev ) {
        ui->spFlashLight->setValue( sConfig.nFlashRadiance );
        ui->spFlashTime->setValue( sConfig.nFlashTime );
        ui->spFreqLight->setValue( sConfig.nFrequencyRadiance );
        ui->spFreqTime->setValue( sConfig.nFrequencyTime );
    } else {
        ui->spFlashLightNew->setValue( sConfig.sNewConfig.nFlashRadiance );
        ui->spFlashTimeNew->setValue( sConfig.sNewConfig.nFlashTime );
        ui->spFreqLightNew->setValue( sConfig.sNewConfig.nFrequencyRadiance );
        ui->spFreqTimeNew->setValue( sConfig.sNewConfig.nFrequencyTime );
        ui->spLightSensitiveFreq->setValue( sConfig.sNewConfig.nFrequencyActivated );
        ui->spLightSensitiveFlash->setValue( sConfig.sNewConfig.nFlashActivated );
    }
}

void MainWindow::SetComboBoxValue( const LedControll::SSysConfig &sConfig )
{
    ui->spLightSensitiveFreq->setValue( sConfig.sNewConfig.nFrequencyActivated );
    ui->spLightSensitiveFlash->setValue( sConfig.sNewConfig.nFlashActivated );

    ui->cbLightSensitiveFreq->setCurrentIndex( sConfig.sNewConfig.nFrequencyActivated );
    ui->cbLightSensitiveFlash->setCurrentIndex( sConfig.sNewConfig.nFlashActivated );
    ui->cbLightFrameFreq->setCurrentIndex( sConfig.sNewConfig.nFrameFreqMode );
}

void MainWindow::SetCheckBoxValue( const LedControll::SSysConfig &sConfig, const bool bNewDev )
{
    if ( !bNewDev ) {
        ui->chkBaseLight->setChecked( 0 != sConfig.nBaseRadiance );
        ui->chkLightSensitive->setChecked( 0 != sConfig.nActivatedSwitch );
    } else {
        ui->chkLightSensitiveFlash->setChecked( 0 != sConfig.sNewConfig.nFlashSwitch );
        ui->chkLightSensitiveFreq->setChecked( 0 != sConfig.sNewConfig.nFrequencySwitch );
    }
}

void MainWindow::SetFlash( const bool bValue )
{
    bFlash = bValue;
}

bool MainWindow::GetFlash( )
{
    return bFlash;
}

void MainWindow::SetLocation( const LedControll::SSysConfig &sConfig, const bool bNewDev )
{
    QString strLocation;

    if ( !bNewDev ) {
        strLocation = QString::fromWCharArray( sConfig.cLocation );
        ui->edtLocation->setText( strLocation );
    } else {
        strLocation = QString::fromWCharArray( sConfig.sNewConfig.cLocation );
        ui->edtLocationNew->setText( strLocation );
    }
}

void MainWindow::InitializeUI( const LedControll::SSysConfig &sConfig, const bool bNewDev )
{
    if ( bNewDev ) {
        GetCheckBoxState( hashFlashSync, sConfig.sNewConfig.nFlashMode );
        GetCheckBoxState( hashFreqSync, sConfig.sNewConfig.nFrequencyMode );
    } else {
        GetCheckBoxState( hashMode, sConfig.nRunMode );
        GetCheckBoxState( hashSync, sConfig.nSyncMode );
    }

    SetSpinBoxValue( sConfig, bNewDev );
    SetCheckBoxValue( sConfig, bNewDev );
    SetComboBoxValue( sConfig );
    SetLocation( sConfig, bNewDev );

    SetFlash( 1 <= sConfig.nRunMode && 4 >= sConfig.nRunMode );
    SwitchModeUI( !GetFlash( ) );
}

void MainWindow::InitializeSlot( )
{
    SetFlash( false );
    nModeIndex = 0;

    hashMode.insert( 1, ui->rb01 );
    hashMode.insert( 2, ui->rb02 );
    hashMode.insert( 3, ui->rb03 );
    hashMode.insert( 4, ui->rb04 );
    hashMode.insert( 5, ui->rb05 );
    hashMode.insert( 6, ui->rb06 );
    hashMode.insert( 7, ui->rb07 );
    hashMode.insert( 8, ui->rb08 );

    hashSync.insert( 1, ui->rbSync01 );
    hashSync.insert( 2, ui->rbSync02 );
    hashSync.insert( 3, ui->rbSync03 );

    hashFlashSync.insert( 1, ui->rbSync08 );
    hashFlashSync.insert( 2, ui->rbSync09 );
    hashFlashSync.insert( 3, ui->rbSync10);
    hashFlashSync.insert( 4, ui->rbSync11 );

    hashFreqSync.insert( 1, ui->rbSync04 );
    hashFreqSync.insert( 2, ui->rbSync05 );
    hashFreqSync.insert( 3, ui->rbSync06 );
    hashFreqSync.insert( 4, ui->rbSync07 );

    lstFlashCtrl.append( ui->rbSync08 );
    lstFlashCtrl.append( ui->rbSync09 );
    lstFlashCtrl.append( ui->rbSync10 );
    lstFlashCtrl.append( ui->rbSync11 );
    lstFlashCtrl.append( ui->chkLightSensitiveFlash );
    lstFlashCtrl.append( ui->spLightSensitiveFlash );
    lstFlashCtrl.append( ui->spFlashTimeNew );
    lstFlashCtrl.append( ui->cbLightSensitiveFlash );

    connect( ui->rb01, SIGNAL( clicked( ) ), this, SLOT( OnRbModeXClicked( ) ) );
    connect( ui->rb02, SIGNAL( clicked( ) ), this, SLOT( OnRbModeXClicked( ) ) );
    connect( ui->rb03, SIGNAL( clicked( ) ), this, SLOT( OnRbModeXClicked( ) ) );
    connect( ui->rb04, SIGNAL( clicked( ) ), this, SLOT( OnRbModeXClicked( ) ) );
    connect( ui->rb05, SIGNAL( clicked( ) ), this, SLOT( OnRbModeXClicked( ) ) );
    connect( ui->rb06, SIGNAL( clicked( ) ), this, SLOT( OnRbModeXClicked( ) ) );
    connect( ui->rb07, SIGNAL( clicked( ) ), this, SLOT( OnRbModeXClicked( ) ) );
    connect( ui->rb08, SIGNAL( clicked( ) ), this, SLOT( OnRbModeXClicked( ) ) );

    connect( ui->rbSync01, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync02, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync03, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync04, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync05, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync06, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync07, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync08, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync09, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync10, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );
    connect( ui->rbSync11, SIGNAL( clicked( ) ), this, SLOT( OnRbSyncXClicked( ) ) );

    connect( ui->spFlashLight, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );
    connect( ui->spFlashTime, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );
    connect( ui->spFreqLight, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );
    connect( ui->spFreqTime, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );

    connect( ui->spFlashLightNew, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );
    connect( ui->spFlashTimeNew, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );
    connect( ui->spFreqLightNew, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );
    connect( ui->spFreqTimeNew, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );
    connect( ui->spLightSensitiveFlash, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );
    connect( ui->spLightSensitiveFreq, SIGNAL( valueChanged( int ) ), this, SLOT( OnSpXValueChanged( int ) ) );

    connect( ui->cbLightSensitiveFlash, SIGNAL( currentIndexChanged( int ) ), this, SLOT( CbCurrentIndexChanged( int ) ) );
    connect( ui->cbLightSensitiveFreq, SIGNAL( currentIndexChanged( int ) ), this, SLOT( CbCurrentIndexChanged( int ) ) );

    connect( ui->cbLightFrameFreq, SIGNAL( currentIndexChanged( int ) ), this, SLOT( CbCurrentIndexChanged( int ) ) );
}

void MainWindow::InitializeCB( QComboBox *pCB )
{
    pCB->clear( );

    QString strText[ ] = { "1.5", "1.6", "1.8", "2.0","2.2","2.4","2.6","2.8","3.0" };
    quint8 nValues[ ] = { 15, 16, 18, 20, 22, 24, 26, 28, 30 };

    for ( quint8 nIndex = 0; nIndex < sizeof ( nValues ) / sizeof ( quint8 ); nIndex++ ) {
        pCB->addItem( strText[ nIndex ], nValues[ nIndex ] );
    }
}

quint8 MainWindow::GetCbBCDValue( const QComboBox *pCB )
{

    if ( pCB == ui->cbLightFrameFreq ) {
        return pCB->currentIndex( ) + 1;
    }

    quint8 nBCDValue = 0;
    quint8 nBase = 10;

    quint8 nTmp = pCB->itemData( pCB->currentIndex( ) ).toUInt( );
    quint8 nFourBit = 0;

    nFourBit = nTmp % nBase;
    nBCDValue |= nFourBit;

    nFourBit = ( ( nTmp / nBase ) << 4 );
    nBCDValue |= nFourBit;

    return nBCDValue;
}

void MainWindow::CbCurrentIndexChanged( int index )
{
    SetNewFlash( sender( ) );

    const QComboBox* pCB = ( QComboBox* ) sender( );
    LedControll::ECommand eCmd;
    bool bNewDevice = true;

    qint32 nValue = GetCbBCDValue( pCB );

    if ( pCB == ui->cbLightSensitiveFlash ) {
        eCmd = LedControll::CmdFlashRadianceChange;
        SendCmd( bNewDevice, eCmd, nValue );
    } else if ( pCB == ui->cbLightSensitiveFreq ) {
        eCmd = LedControll::CmdFrenquencyRadianceChange;
        SendCmd( bNewDevice, eCmd, nValue );
    } else if ( pCB == ui->cbLightFrameFreq ) {
        eCmd = LedControll::CmdFrameFrequency;
        SendCmd( bNewDevice, eCmd, nValue );
    }
}

void MainWindow::GetQueryCmd( QByteArray *pData )
{
    #if false
     //Query test cmd
    FEFEFEFE68AAAAAAAAAAAA68910533363337330016
    FEFEFEFE68AAAAAAAAAAAA68910541363337330016
    FEFEFEFE68AAAAAAAAAAAA689107343633374467890016
    FEFEFEFE68AAAAAAAAAAAA68910535363337340016
    FEFEFEFE68AAAAAAAAAAAA68910536363337350016
    FEFEFEFE68AAAAAAAAAAAA6891053E363337340016
    FEFEFEFE68AAAAAAAAAAAA68910537363337340016
    FEFEFEFE68AAAAAAAAAAAA68910538363337350016
    FEFEFEFE68AAAAAAAAAAAA68910539363337360016
    FEFEFEFE68AAAAAAAAAAAA6891053A363337370016
    FEFEFEFE68AAAAAAAAAAAA6891053F363337380016
    FEFEFEFE68AAAAAAAAAAAA68910540363337390016
    FEFEFEFE68AAAAAAAAAAAA6891053B363337580016
    FEFEFEFE68AAAAAAAAAAAA6891063C36333744560016
    FEFEFEFE68AAAAAAAAAAAA6891053D363337340016
    #endif

    QByteArray data;
    bool bQuery = true;
    bool bMode = true; // true Flash
    qint32 nParam = 0;

    //LedControll::CmdFlashFrenquencyGearWorkTimeSet
    //LedControll::CmdFlashFrenquencyGearWorkTimeSet bFlash true
    //LedControll::CmdFlashFrenquencyIntensityTune
    //LedControll::CmdFlashFrenquencyIntensityTune bFlash true


    controllerCmd->GetNewCmd( LedControll::CmdFlashFrenquencyLightSensitiveIfWork, data, nParam, bQuery, !bMode );
    pData[ 0 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdFlashFrenquencyLightSensitiveIfWork, data, nParam, bQuery, bMode );
    pData[ 1 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdLedTemperature, data, nParam, bQuery, bMode );
    pData[ 2 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdFlashGearSet, data, nParam, bQuery, bMode );
    pData[ 3 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdSyncModeDownTrigger, data, nParam, bQuery, bMode );
    pData[ 4 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdFlashFrenquencyGearWorkTimeSet, data, nParam, bQuery, !bMode );
    pData[ 5 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdFlashFrenquencyGearWorkTimeSet, data, nParam, bQuery, bMode );
    pData[ 6 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdFlashFrenquencyIntensityTune, data, nParam, bQuery, !bMode );
    pData[ 7 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdFlashFrenquencyIntensityTune, data, nParam, bQuery, bMode );
    pData[ 8 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdLedFrequency, data, nParam, bQuery, bMode );
    pData[ 9 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdLedWorkVoltage, data, nParam, bQuery, bMode );
    pData[ 10 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdLedExternalTriggerSignalState, data, nParam, bQuery, bMode );
    pData[ 11 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdSyncModeForFlash, data, nParam, bQuery, bMode );
    pData[ 12 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdFrenquencyRadianceChange, data, nParam, bQuery, !bMode );
    pData[ 13 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdFlashRadianceChange, data, nParam, bQuery, bMode );
    pData[ 14 ].append( data );

    controllerCmd->GetNewCmd( LedControll::CmdFrameFrequency, data, nParam, bQuery, bMode );
    pData[ 15 ].append( data );

    //qDebug( ) << byData.toHex( ).toUpper( ) << endl;
}

void MainWindow::SendCmd( const bool bNewDevice, const LedControll::ECommand eCmd, qint32 nParam )
{
    QByteArray byData;

    if ( bNewDevice ) {
        controllerCmd->GetNewCmd( eCmd, byData, nParam, ui->chkQuery->isChecked( ), GetFlash( ) );
    } else {
        controllerCmd->GetOldCmd( eCmd, byData, nParam );
    }

    controller.WriteData( byData, QControllerCommon::GetWaitTime( ), true );
}

qint32 MainWindow::GetRbIndex( QObject *pSender )
{
    QString strName = pSender->objectName( );
    int nLen = 2;

    if ( nLen > strName.length( ) ) {
        return 0;
    }

    qint32 nIndex = strName.right( 2 ).toInt( );
    if ( 11 < nIndex || 0 >= nIndex ) { // 1-- 11
        return 0;
    }

    return nIndex;
}

void MainWindow::ChangMode( qint32 nMode, const bool bNeedChange )
{
    bool bNewDevice = IsNewDevice( );

    if ( bNewDevice ) {
        nMode = ( GetFlash( ) ? 0x00000001 : 0x00000000 );
    } else if ( bNeedChange ) {
        nMode |= 0xFF03D800;
    }

    SendCmd( bNewDevice, GetFlash( ) ? LedControll::CmdFlashGearSet : LedControll::CmdFrenquencyGearSet, nMode );

    QString strTxt = QString( "目前处于:%1" ).arg( GetFlash( ) ? ui->lblFlash->text( ) : ui->lblFreq->text( ) );
    ui->lblMode->setText( strTxt );
}

void MainWindow::OnRbModeXClicked( )
{
    qint32 nIndex = GetRbIndex( sender( ) );

    if ( 0 >= nIndex || 8 < nIndex ) {
        return;
    }

    nModeIndex = nIndex;

    SetFlash( 5 > nIndex );
    SwitchModeUI( !GetFlash( ) );
    ChangMode( nIndex, true );
}

void MainWindow::OnRbSyncXClicked( )
{
    QObject* pSender = sender( );
    qint32 nIndex = GetRbIndex( pSender );

    if ( 0 >= nIndex || 11 < nIndex ) {
        return;
    }

    LedControll::ECommand eCmd;

    switch ( nIndex ) {
    case 2 :
    case 4 :
    case 7 :
        eCmd = LedControll::CmdSyncModeDownTrigger;
        break;

    case 1 :
    case 5 :
    case 8 :
        eCmd = LedControll::CmdSyncModeUpTrigger;
        break;

    case 3 :
    case 6 :
    case 9 :
    case 10 :
        eCmd = LedControll::CmdSyncModeFollowTrigger;
        break;

    case 11 :
        eCmd = LedControll::CmdSyncModeFollowDownTrigger;
        break;
    }

    bool bNewDevice = IsNewDevice( );
    if ( bNewDevice ) {
        SetNewFlash(  pSender );
    }

    if ( bNewDevice ) {
        //1 == ui->cbMode->currentIndex( )

        if ( bFlash ) {
            eCmd = LedControll::CmdSyncModeForFlash;
            nIndex -= 8;
        } else {
            nIndex -= 4;
        }
    } else {
        nIndex |= 0xFF03D800;
    }

    SendCmd( bNewDevice, eCmd, nIndex );
}

void MainWindow::OnSpXValueChanged( int nValue )
{
    QSpinBox* pSB = ( QSpinBox* ) sender( );
    LedControll::ECommand eCmd;
    bool bNewDevice = IsNewDevice( );

    if ( bNewDevice ) {
        SetNewFlash( pSB );
    }

    if ( pSB == ui->spFlashTime || pSB == ui->spFlashTimeNew ) { // 闪光灯
        eCmd = LedControll::CmdFlashFrenquencyGearWorkTimeSet;
        int iTrack = nValue;

        if ( bNewDevice ) {

        } else {
            float fValue = nValue / 25.0f;
            if ( fValue > 0 && fValue <= 1 ) {
                iTrack = 1;
            } else if ( fValue > 1 && fValue <= 2 )  {
                iTrack = 2;
            } else if ( fValue > 2 && fValue <= 3 ) {
                iTrack = 3;
            } else if ( fValue > 3 && fValue <= 4 ) {
                iTrack = 4;
            }

            iTrack *= 8;
            iTrack <<= 8;
            iTrack |= 0xffff0000;
            nValue = iTrack;
        }

        if ( GetFlash( ) ) {
            SendCmd( bNewDevice, eCmd, iTrack );

            if ( !bNewDevice ) {
                nValue &= 0xFFFFFF00;
                nValue |= nModeIndex;
                ChangMode( nValue, false );
            }
        }
    } else if ( pSB == ui->spFlashLight  || pSB == ui->spFlashLightNew ) {
        eCmd = LedControll::CmdFlashFrenquencyIntensityTune;

        if( bNewDevice ) {
            ;
        } else {
            float fValue = nValue / 25.0f;
            nValue = ( fValue * 0.25 ) * 1023;
            nValue &= 0x0000ffff;
        }

        if ( GetFlash( ) ) {
            SendCmd( bNewDevice, eCmd, nValue );

            if ( !bNewDevice ) {
                qint32 nLow = ( nValue >> 8 );
                qint32 nHigh = ( ( nValue & 0x000000FF ) << 8 );
                nValue = ( nLow | nHigh );
                nValue <<= 16;
                nValue |= 0x0000D800;
                nValue |= nModeIndex;
                //nValue |= 0x
                ChangMode( nValue, false );
            }
        }
    } else if ( pSB == ui->spFreqTime || pSB == ui->spFreqTimeNew ) { // 频闪
        eCmd = LedControll::CmdFlashFrenquencyGearWorkTimeSet;

        if ( bNewDevice ) {
            ;
        } else {
            nValue &= 0x000000FF;
            nValue <<= 16;
            nValue |= 0xff000000;
        }

        if ( !GetFlash( ) ) {
            SendCmd( bNewDevice, eCmd, nValue );
        }

        if ( !bNewDevice ) {
            nValue &= 0xFFFFFF00;
            nValue |= nModeIndex;
            ChangMode( nValue, false );
        }
    } else if ( pSB == ui->spFreqLight || pSB == ui->spFreqLightNew ) {
        eCmd = LedControll::CmdFlashFrenquencyIntensityTune;

        if( bNewDevice ) {
            ;
        } else {
            nValue = ( nValue / 32.0f ) * 1023;
            nValue &= 0x0000ffff;
        }

        if ( !GetFlash( ) ) {
            SendCmd( bNewDevice, eCmd, nValue );
        }

        if ( !bNewDevice ) {
            qint32 nLow = ( nValue >> 8 );
            qint32 nHigh = ( ( nValue & 0x000000FF ) << 8 );
            nValue = ( nLow | nHigh );
            nValue <<= 16;
            nValue |= 0x0000D800;
            nValue |= nModeIndex;
            //nValue |= 0x
            ChangMode( nValue, false );
        }
    } else if ( pSB == ui->spLightSensitiveFlash ) {
        //eCmd = LedControll::CmdFlashRadianceChange; // CmdFlashFrenquencyIntensityTune
        eCmd = LedControll::CmdFlashFrenquencyIntensityTune;
        SendCmd( bNewDevice, eCmd, nValue );
    } else if ( pSB == ui->spLightSensitiveFreq ) {
        //eCmd = LedControll::CmdFrenquencyRadianceChange;
        eCmd = LedControll::CmdFlashFrenquencyIntensityTune;
        SendCmd( bNewDevice, eCmd, nValue );
    }
}

void MainWindow::DlgConfig( )
{
    QDlgConfig dlg;
    if ( QDialog::Accepted == dlg.exec( ) ) {
        controller.ConrollSP( false );
        controller.ConrollSP( true );
    }

    QString strTitle = QString( "智能补光灯系统-串口:COM%1" ).arg( ( qint32 ) dlg.GetComName( ) );
    setWindowTitle( strTitle );
    setObjectName( strTitle );
}

void MainWindow::timerEvent( QTimerEvent *e )
{
    if ( nTimerID != e->timerId( ) ) {
        return;
    }

    setWindowTitle( objectName( ) );

    QByteArray byData;
    controllerCmd->GetNewCmd( LedControll::CmdTestConnect, byData, 0, true, GetFlash( ) );
    controller.WriteData( byData, QControllerCommon::GetWaitTime( ), true );
}

MainWindow::~MainWindow()
{
    if ( 0 != nTimerID ) {
        killTimer( nTimerID );
    }

    controller.ConrollSP( false );
    delete ui;
}

void MainWindow::on_btnSet_clicked()
{
    DlgConfig( );
}

void MainWindow::SwitchModeUI( const bool bFreqMode )
{
    int nIndex = bFreqMode ? 1 : 5;
    int nEnd = bFreqMode ? 4 : 8;
    QRadioButton* pButton = NULL;

    for ( ; nIndex <= nEnd; nIndex++ ) {
        pButton = hashMode.value( nIndex );

        if ( NULL != pButton && pButton->isChecked( ) ) {
            pButton->setCheckable( false );
            pButton->setChecked( false );
            pButton->setCheckable( true );
            pButton->setFocus( );
        }
    }
}

char MainWindow::GetSelectedRbIndex( QHash<char, QRadioButton *> &hash )
{
    char cRet = ( char ) 1;

    char cCounter = hash.size( );
    for ( char c = 1; c <= cCounter; c++ ) {
        if ( hash.value( c )->isChecked( ) ) {
            cRet = c;
            break;
        }
    }

    return cRet;
}

void MainWindow::SaveOldDevConfig ( LedControll::SSysConfig &sConfig )
{
    sConfig.nRunMode = GetSelectedRbIndex( hashMode );
    sConfig.nSyncMode = GetSelectedRbIndex( hashSync );
    sConfig.nFlashRadiance = ui->spFlashLight->value( );
    sConfig.nFlashTime = ui->spFlashTime->value( );
    sConfig.nFrequencyRadiance = ui->spFreqLight->value( );
    sConfig.nFrequencyTime = ui->spFreqTime->value( );
    sConfig.nActivatedSwitch = ui->chkLightSensitive->isChecked( ) ? 1 : 0;
    sConfig.nBaseRadiance = ui->chkBaseLight->isChecked( ) ? 1 : 0;
}

void MainWindow::GetLocationDefault( QString &strLocation, const bool bNewDev )
{
    if ( strLocation.isEmpty( ) ) {
        strLocation = QString( "%1设备未设置" ).arg( bNewDev ? "新" : "老" );
    }
}

void MainWindow::SaveLocationConfig( QString &strLocation, wchar_t *pBuffer )
{
    const wchar_t* pData = ( wchar_t* ) strLocation.utf16( );
    qint32 nLen = strLocation.length( );
    qint32 nRealLen = LedControll::nLOCATION_SIZE - 1;
    if ( nRealLen < nLen ) {
        strLocation.remove( nRealLen, nLen - nRealLen );
    }

    wcscpy( pBuffer, pData );
}

void MainWindow::SaveNewDevConfig( LedControll::SNewSysConfig &sConfig )
{
    sConfig.nFlashTime = ui->spFlashTimeNew->value( );
    sConfig.nFlashRadiance = ui->spFlashLightNew->value( );
    sConfig.nFlashActivated = ui->cbLightSensitiveFlash->currentIndex( );//ui->spLightSensitiveFlash->value( );
    sConfig.nFlashSwitch = ui->chkLightSensitiveFlash->isChecked( ) ? 1 : 0;
    sConfig.nFlashMode = GetSelectedRbIndex( hashFlashSync ) ;

    sConfig.nFrequencyTime = ui->spFreqTimeNew->value( );
    sConfig.nFrequencyRadiance = ui->spFreqLightNew->value( );
    sConfig.nFrequencyActivated = ui->cbLightSensitiveFreq->currentIndex( );//ui->spLightSensitiveFreq->value( );
    sConfig.nFrequencySwitch = ui->chkLightSensitiveFreq->isChecked( ) ? 1 : 0;
    sConfig.nFrequencyMode = GetSelectedRbIndex( hashFreqSync );
    sConfig.nFrameFreqMode = ui->cbLightFrameFreq->currentIndex( );
}

void MainWindow::on_btnSaveSet_clicked()
{
    LedControll::SSysConfig sConfig;
    ZeroMemory( &sConfig, sizeof ( sConfig ) );

    bool bNewDevice = IsNewDevice( );
    QString strLocation;

    if ( bNewDevice ) {
        strLocation = ui->edtLocationNew->text( );
        GetLocationDefault( strLocation, bNewDevice );
        SaveNewDevConfig( sConfig.sNewConfig );
        SaveLocationConfig( strLocation, sConfig.sNewConfig.cLocation );
    } else {
        strLocation = ui->edtLocation->text( );
        GetLocationDefault( strLocation, bNewDevice );
        SaveOldDevConfig( sConfig );
        SaveLocationConfig( strLocation, sConfig.cLocation );
    }

    QControllerCommon::SaveSystemConfig( sConfig );

    QString strPath;
    QControllerCommon::GetPath( strPath, LedControll::PathConfig );
    strPath += QDir::separator( ) + strLocation + ".ini";
    QControllerCommon::SaveSystemConfig( sConfig, strPath );

    QControllerCommon::MsgBox( NULL, "提示" , QString( "配置成功保存到\r\n【%1】" ).arg( strPath ), QMessageBox::Information );
}

bool MainWindow::IsNewDevice( )
{
    return ui->chkDevType->isChecked( );
}

void MainWindow::SetNewFlash( QObject *pBox )
{
    qDebug( ) << pBox->objectName( ) << endl;
    bool bValue = lstFlashCtrl.contains( pBox );
    SetFlash( bValue );

    ui->cbMode->setCurrentIndex( bValue ? 1 : 0 );
}

void MainWindow::on_tbnReadSet_clicked()
{
    QFileDialog dlg( 0 );

    dlg.setNameFilter( tr( "Ini File (*.ini)" ) );
    dlg.setViewMode( QFileDialog::Detail );

    if ( QDialog::Rejected == dlg.exec( ) ) {
        return;
    }

   QStringList lstFiles = dlg.selectedFiles( );
   if ( 0 == lstFiles.length( ) ) {
       return;
   }

    InitializeUI( lstFiles.at( 0 ), IsNewDevice( ) );
}

void MainWindow::on_btnTestFlash_clicked()
{
    // AA 55 0A 03 D8 01 FF FF FF Open
    // AA 55 0A 03 D8 03 FF FF FF Close
    static bool bOpen = false;

    qint32 nParam = bOpen ? 0x00000003 : 0x00000001;
    SendCmd( IsNewDevice( ),
             bOpen ? LedControll::CmdTestFlashOpen : LedControll::CmdTestFlashClose, nParam );
    bOpen = !bOpen;

    QString strTxt = bOpen ? "试闪开" : "试闪关";
    ui->btnTestFlash->setText( strTxt );


}

void MainWindow::on_chkDevType_clicked(bool checked)
{
    ui->spFreqTime->setMaximum( checked ? 100 : 32 );
    ui->spFreqLight->setMaximum( checked ? 100 : 32 );

    ui->cbMode->setVisible( checked );
    ui->btnQuery->setVisible( checked );

    foreach ( QRadioButton* pButton, hashMode.values( ) ) {
        pButton->setEnabled( !checked );
    }

    ui->chkBaseLight->setEnabled( !checked );
    qint32 nIndex = ui->cbMode->currentIndex( );
    on_cbMode_currentIndexChanged( nIndex );

    checked ? SetNewMaxSize( ) : SetOldMaxSize( );
}

void MainWindow::SetOldMaxSize( )
{
    SetSize( 551, 415 );
}

void MainWindow::SetSize( qint32 nWidth, qint32 nHeight )
{
    setMaximumSize( nWidth, nHeight );
    QSize size( nWidth, nHeight );
    resize( size );
}

void MainWindow::SetNewMaxSize( )
{
    SetSize( 551, 653 );
}

void MainWindow::on_chkLightSensitive_clicked(bool checked)
{
    bool bNewDevice = IsNewDevice( );
    qint32 nParam = 0;
    if ( bNewDevice ) {
        nParam = checked ? 0x00000005 : 0x00000000;
    } else {
        nParam = checked ? 0xFF03D801 : 0xFF03D802;
    }

    SendCmd( bNewDevice, LedControll::CmdFlashFrenquencyLightSensitiveIfWork, nParam );
}

void MainWindow::on_chkBaseLight_clicked(bool checked)
{
    qint32 nParam = checked ? 0xFF03D801 : 0xFF03D800;
    SendCmd( IsNewDevice( ), LedControll::CmdFlashGearAlwaysRadianceClose, nParam );
}

void MainWindow::on_cbMode_currentIndexChanged(int index)
{
    SetFlash( 0 != index );
    ChangMode( index, false );
}

void MainWindow::on_btnQuery_clicked()
{
    //controller.WriteData( byQueryCmds[ 12 ], true );
    //return;
    // QUERY_CMD_COUNT
    for ( qint8 c = 0; c < QUERY_CMD_COUNT; c++ ) {
        controller.WriteData( byQueryCmds[ c ], QControllerCommon::GetWaitTime( ), true );
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->chkDevType->setChecked( 0 != index );
}

void MainWindow::on_chkLightSensitiveFreq_clicked(bool checked)
{
    SetNewFlash( sender( ) );
    on_chkLightSensitive_clicked( checked );
}

void MainWindow::on_chkLightSensitiveFlash_clicked(bool checked)
{
    SetNewFlash( sender( ) );
    on_chkLightSensitive_clicked( checked );
}

void MainWindow::on_tabWidgetDevice_currentChanged(int index)
{
    if ( 0 == index && IsNewDevice( ) ) {
        on_btnQuery_clicked( );
    }
}
