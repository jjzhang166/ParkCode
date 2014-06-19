#include "recognizeparamdlg.h"
#include "ui_recognizeparamdlg.h"

#ifdef PLATEDEMO_H
    #include "../Common/commonfunction.h"
#else
    #include "Common/commonfunction.h"
#endif

#define CHILD_COUNT ( int ) ( 41 )

CRecognizeParamDlg::CRecognizeParamDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRecognizeParamDlg)
{
    ui->setupUi(this);

    CCommonFunction::ConnectCloseButton( ui->lblClose );
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgPlate );
    CCommonFunction::ControlSysMenu( *this );
    SetKeyName( lstKeys );
    SetDefault( defaultData );
    GetValue( true );

    setWindowFlags( Qt::FramelessWindowHint );

    CCommonFunction::GetPath( strPath, CommonDataType::PathUIImage );
    QString strSysSet = strPath + "NewIcon/PlateSet.JPG";
    QString strStyle = QString( "background-image:url(%1);" ).arg( strSysSet );
    setStyleSheet( strStyle );
    //setStatusTip( strSysSet );
    strSysSet = strPath + "NewIcon/PlateMiddleSet.JPG";

    strStyle = QString( "background-image:url(%1);" ).arg( strSysSet );
    ui->tabParam->setStyleSheet( strStyle );

    ui->lblTitle->setText( windowTitle( ) );

    bRestart = false;

    ui->val139->setVisible( false );
    ui->val239->setVisible( false );
    ui->val339->setVisible( false );
    ui->val439->setVisible( false );
}

CRecognizeParamDlg::~CRecognizeParamDlg()
{
    delete ui;
}

void CRecognizeParamDlg::resizeEvent( QResizeEvent *event )
{
    QWidget::resizeEvent( event );

    //QString strFile = statusTip( );
    //QPixmap bgimage( strFile );
    //QPalette pal( palette( ) );
    //pal.setBrush( QPalette::Window, QBrush( bgimage.scaled( event->size( ),
    //                                                        Qt::IgnoreAspectRatio,
    //                                                        Qt::SmoothTransformation ) ) );
    //setPalette(pal);
}

void CRecognizeParamDlg::on_btnExit_clicked()
{
    if ( bRestart ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 whatsThis( ), QMessageBox::Information );
    }

    close( );
}

void CRecognizeParamDlg::on_btnSave_clicked()
{
    GetValue( false );
    bRestart = true;
    CCommonFunction::OperationSuccess( );
}

void CRecognizeParamDlg::on_btnDefault_clicked()
{
    int nIndex = ui->tabParam->currentIndex( );
    ControlValue( false, defaultData, nIndex );
    //bRestart = true;
}

void CRecognizeParamDlg::SetKeyName(QStringList &lstKey)
{
    lstKey << "PlateMin"
           << "PlateMax"
           << "PlateProvince"
           << "PlateMaxOutput"
           << "PlateVideoPosThreshold"
           << "PlateVideoRegThreshold"
           << "PlateImagePosThreshold"
           << "PlateImageRegThreshold"
           << "PlateOnlyOnceOutput"
           << "PlateInterleaveSample"
           << "PlateInputEntranceImage"
           << "PlateRegDualYellowCard"
           << "PlateRegIndividuationCard"
           << "PlateRegMilitaryCard"
           << "PlateRegDualMilitaryCard"
           << "PlateRegFarmCard"
           << "PlateNightMode"
           << "PlateAreaLeft"
           << "PlateAreaRight"
           << "PlateAreaUp"
           << "PlateAreaDown"
           << "PlateDetectionDelay"
           << "PlateFrameRate"
           << "PlateGrade"
           << "PlateConfidence"
           << "PlateRecognizationTime"
           << "PlateDetectionLeft"
           << "PlateDetectionRight"
           << "PlateDetectionUp"
           << "PlateDetectionDown"
           << "PlateStart"
           << "PlateBlacklist"
           << "PlatePrecision"
           << "PlateLeft"
           << "PlateRight"
           << "PlateUp"
           << "PlateDown"
           << "PlateInterval"
           << "PlateClear"
           << "BallotClear"
           << "GateClear";
}

void CRecognizeParamDlg::GetValue( bool bRead )
{
    bRead ? ReadFile( ) : WriteFile( );
}

void CRecognizeParamDlg::SetDefault( QStringList& lstData )
{
    lstData << "80"
            << "400"
            << "´¨"
            << "1"
            << "7"
            << "5"
            << "5"
            << "1"
            << "1"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "704"
            << "0"
            << "576"
            << "0"
            << "25"
            << "6"
            << "80"
            << "500"
            << "0"
            << "703"
            << "0"
            << "575"
            << "1"
            << "0"
            << "0"
            << "1"
            << "1"
            << "1"
            << "1"
            << "30"
            << "0"
            << "1"
            << "0";
}

void CRecognizeParamDlg::ReadFile( )
{
    QStringList lstData;
    QString strSection = "WintonePlate/WintonePlate%1";
    QString strKey;
    int nChild = ui->tabParam->count( );

    for ( int nIndex = 0; nIndex < nChild; nIndex++ ) {
        lstData.clear( );
        strKey = strSection.arg( QString::number( nIndex ) ) + QString( "/%1" );

        for ( int nItem = 0; nItem < lstKeys.count( ); nItem ++ ) {
            lstData << pSettings->value( strKey.arg( lstKeys[ nItem ] ), defaultData[ nItem ] ).toString( );
        }

        ControlValue( false, lstData, nIndex );
    }
#if 0
    strSection = "CaptureCard/%1%2";
    strKey = "²É¼¯¿¨1";
    WriteCB( strSection, ui->cbCaptureCard, strKey );
    strSection = "Algorithm/%1%2";
    strKey = "Ëã·¨1";
    WriteCB( strSection, ui->cbAlgorithm, strKey );
    strSection = "RecognizeMode/%1%2";
    strKey = "Í¼Ïñ";
    WriteCB( strSection, ui->cbRegMode, strKey );
#endif
}

void CRecognizeParamDlg::WriteFile( )
{
    QStringList lstData;
    QString strSection = "WintonePlate%1";
    QString strKey;
    int nChild = ui->tabParam->count( );

    pSettings->beginGroup( strSection.arg( "" ) );

    for ( int nIndex = 0; nIndex < nChild; nIndex++ ) {
        ControlValue( true, lstData, nIndex );
        strKey = strSection.arg( nIndex ) +  "/%1";

        for ( int nItem = 0; nItem < lstKeys.count( ); nItem ++ ) {
            pSettings->setValue( strKey.arg( lstKeys[ nItem ] ), lstData[ nItem ] );
        }
    }

    pSettings->endGroup( );
#if 0
    strSection = "CaptureCard";
    ReadCB( strSection, ui->cbCaptureCard );
    strSection = "Algorithm";
    ReadCB( strSection, ui->cbAlgorithm );
    strSection = "RecognizeMode";
    ReadCB( strSection, ui->cbRegMode );
#endif
}

void CRecognizeParamDlg::ReadCB( QString& strSection, QComboBox* pCB )
{
    int nCount = pCB->count( );
    if ( 0 >= nCount ) {
        return;
    }

    pSettings->beginGroup( strSection );
    QString strItem = "Count%1";

    pSettings->setValue( strItem.arg( "" ), nCount );
    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        pSettings->setValue( strItem.arg( nIndex ), pCB->itemText( nIndex ) );
    }
    pSettings->setValue( "Current", pCB->currentIndex( ) );

    pSettings->endGroup( );
}

void CRecognizeParamDlg::WriteCB( QString& strSection, QComboBox* pCB, QString& strDefault )
{

    QString strKey = "Count%1";
    int nCount = pSettings->value( strSection.arg( strKey, "" ), 0 ).toInt( );

    if ( 0 >= nCount ) {
        return;
    }

    pCB->clear( );

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        pCB->addItem( pSettings->value( strSection.arg( strKey, nIndex ), strDefault ).toString( ) );
    }
}

void CRecognizeParamDlg::ControlValue( bool bRead, QStringList &lstData, int nTabIndex )
{
    int nIndex = nTabIndex + 1;
    QString strTabWG = QString( "tab%1" ).arg( nIndex );
    QWidget* wg = ui->tabParam->findChild< QWidget* > ( strTabWG );

    if ( NULL == wg ) {
        return;
    }

    QString strCtrl = QString( "val%1" ).arg( nIndex ) + "%1";

    int nChild = CHILD_COUNT;

    QLineEdit* pLE = NULL;
    QCheckBox* pCB = NULL;
    QSpinBox* pSB = NULL;
    QComboBox* pCBX = NULL;
    QString strName;
    QString strReadVal;

    if ( bRead ) {
        lstData.clear( );
    }


    for ( nIndex = 0; nIndex < nChild; nIndex++ ) {
        strName = strCtrl.arg( nIndex + 1 );
        pSB = NULL;
        pLE = NULL;
        pCB = NULL;
        pCBX =NULL;

        if ( 2 == nIndex ) { // QLineEdit
            pLE = wg->findChild< QLineEdit* >( strName );
        } else if ( 38 == nIndex) { // QComboBox
            pCBX = wg->findChild< QComboBox* >( strName );
        } else if ( ( 8 <= nIndex && nIndex <= 16 ) ||
                    ( 30 <= nIndex && nIndex <= 31 ) ||
                    ( 33 <= nIndex && nIndex <= 36 ) ||
                    ( 39 <= nIndex && nIndex <= 40 ) ) { // QCheckBox
            pCB = wg->findChild< QCheckBox* >( strName );

            if ( 33 <= nIndex && nIndex <= 36 ) {
                pCB->setVisible( false );
            }
        } else { // QSpinBox
            pSB = wg->findChild< QSpinBox* >( strName );
        }

        if ( bRead ) {
            if ( NULL != pLE ) {
                strReadVal = pLE->text( );
            } else if ( NULL != pCB ) {
                strReadVal = pCB->isChecked( ) ? "1" : "0";
            } else if ( NULL != pSB ) {
                strReadVal = QString::number( pSB->value( ) );
            } else if ( NULL != pCBX ) {
                strReadVal = QString::number( pCBX->currentIndex( ) );
            }

            lstData << strReadVal;
        } else {
            QString& strVal = lstData[ nIndex ];

            if ( NULL != pLE ) {
                pLE->setText( strVal );
            } else if ( NULL != pCB ) {
                pCB->setChecked( "0" != strVal );
            } else if ( NULL != pSB ) {
                pSB->setValue( strVal.toInt( ) );
            } else if ( NULL != pCBX ) {
                int nItem = strVal.toInt( );
                if ( 0 > nItem || nItem >=pCBX->count( ) ) {
                    nItem = 0;
                }

                pCBX->setCurrentIndex( nItem );
            }
        }
    }
}

void CRecognizeParamDlg::on_lblClose_linkActivated(QString)
{
    close( );
}
