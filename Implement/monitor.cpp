#include "Dialog/parkspacelotdialog.h"
#include "Dialog/parkspacelotdialog.h"
#include "SerialPort/processdata.h"
#include <QDebug>
#include "SerialPort/processdata.h"
#include "Common/CommonType.h"
#include <QMetaType>

#include "Dialog/dlgccstatus.h"
#include "Dialog/ledinfodialog.h"
#include "Dialog/dlgperipheralstatus.h"
#include "Dialog/dlgsmsnotification.h"
#include "Dialog/dlgpassdetail.h"
#include "Dialog/dlgqueryowner.h"
#include "Dialog/picturecontrastdlg.h"
#include "Common/commonfunction.h"
#include "Header/publishledinfo.h"
#include "Header/printmonthlyreport.h"
#include "windows.h"
#include "PmsLog/pmslog.h"
#include "ThirdParty/scu.h"

#include "Header/monitor.h"

#ifdef NewUI
#include "ui_newmonitor.h"
#else
#include "ui_monitor.h"
#endif

//quint8 CMonitor::imgData[ VIDEO_USEDWAY ][ VIDEO_BUF ] = { { 0 } };
TH_PlateResult CMonitor::recogResult[ VIDEO_USEDWAY ][ RECOG_RES ] = { { 0 } };
bool CMonitor::bStartRecognization[ VIDEO_USEDWAY ] = { false, false };
//bool CMonitor::bPlateFilter = false;
//bool CMonitor::bSuccession = false;
TH_PlateResult CMonitor::structPlates[ VIDEO_USEDWAY ] = { { 0 } };
CMonitor* pMainWnd = NULL;
QString CMonitor::strPlates[ VIDEO_USEDWAY ] = { "" };

#include "qmypushbutton.h"
#include "VZPlateDemo/qtransparentframe.h"

void CMonitor::GateButtonRightClicked( )
{
    QPushButton* pButton = ( QPushButton* ) sender( );

    if ( ui->btnEnterGateOpen == pButton ) {
        if ( ConfigDefaultCan( lstEnterCanOpen, true, true ) ) {
            ControlGate( true, true, NULL );
        }
    } else if ( ui->btnEnterGateClose == pButton ) {
        if ( ConfigDefaultCan( lstEnterCanClose, true, false ) ) {
            ControlGate( true, false, NULL );
        }
    } else if ( ui->btnLeaveGateOpen == pButton ) {
        if ( ConfigDefaultCan( lstLeaveCanOpen, false, true ) ) {
            ControlGate( false, true, NULL );
        }
    } else if ( ui->btnLeaveGateClose == pButton ) {
        if ( ConfigDefaultCan( lstLeaveCanClose, false, false ) ) {
            ControlGate( false, false, NULL );
        }
    }
}

void CMonitor::CreateGateButton( )
{
    ui->btnEnterGateOpen->setParent( NULL );
    ui->btnEnterGateOpen = new QMyPushButton(this);
    ui->btnEnterGateOpen->setObjectName(QString::fromUtf8("btnEnterGateOpen"));
    ui->btnEnterGateOpen->setGeometry(
            #ifdef NewUI
                QRect(963, 213, 83, 83)
            #else
                QRect(1015, 250, 88, 97)
            #endif
                );
    ui->btnEnterGateOpen->setStyleSheet(QString::fromUtf8("background-image:url( );\n"
"border-style: outset; "));
    connect( ui->btnEnterGateOpen, SIGNAL( RightClick( ) ), this, SLOT( GateButtonRightClicked( ) ) );

    ui->btnEnterGateClose->setParent( NULL );
    ui->btnEnterGateClose = new QMyPushButton(this);
    ui->btnEnterGateClose->setObjectName(QString::fromUtf8("btnEnterGateClose"));
    ui->btnEnterGateClose->setGeometry(
            #ifdef NewUI
                QRect(1046, 213, 83, 83)
            #else
                QRect(1103, 250, 87, 97)
            #endif
                );
    ui->btnEnterGateClose->setStyleSheet(QString::fromUtf8("background-image:url( );\n"
"border-style: outset; "));
    connect( ui->btnEnterGateClose, SIGNAL( RightClick( ) ), this, SLOT( GateButtonRightClicked( ) ) );

    ui->btnLeaveGateClose->setParent( NULL );
    ui->btnLeaveGateClose = new QMyPushButton(this);
    ui->btnLeaveGateClose->setObjectName(QString::fromUtf8("btnLeaveGateClose"));
    ui->btnLeaveGateClose->setGeometry(
            #ifdef NewUI
                QRect(1226, 213, 83, 83)
            #else
                QRect(1292, 250, 87, 97)
            #endif
                                       );
    ui->btnLeaveGateClose->setStyleSheet(QString::fromUtf8("background-image:url( );\n"
"border-style: outset; "));
    connect( ui->btnLeaveGateClose, SIGNAL( RightClick( ) ), this, SLOT( GateButtonRightClicked( ) ) );

    ui->btnLeaveGateOpen->setParent( NULL );
    ui->btnLeaveGateOpen = new QMyPushButton(this);
    ui->btnLeaveGateOpen->setObjectName(QString::fromUtf8("btnLeaveGateOpen"));
    ui->btnLeaveGateOpen->setGeometry(
            #ifdef NewUI
                QRect(1143, 213, 83, 83)
            #else
                QRect(1204, 250, 88, 97)
            #endif
                                      );
    ui->btnLeaveGateOpen->setStyleSheet(QString::fromUtf8("background-image:url( );\n"
"border-style: outset; "));
    connect( ui->btnLeaveGateOpen, SIGNAL( RightClick( ) ), this, SLOT( GateButtonRightClicked( ) ) );
}

void CMonitor::CaptureNewImage( QString& strFile, int nChannel, CommonDataType::CaptureImageType capType )
{
    if ( QFile::exists( strFile ) ) {
        QFile::remove( strFile );
    }

    if ( bNetworkCamera ) {
        HWND hPlayWnd = lblVideoWnd[ nChannel ]->winId( );
        QString strIP = lblVideoWnd[ nChannel ]->toolTip( );

        ipcVideoFrame->CaptureDeviceImage( strIP, strFile, hPlayWnd );
        return;
    }

    if ( "中维" == strCapture ) {
        capType = CommonDataType::CaptureBMP;
        strFile.remove( ".JPG" );
        strFile += ".BMP";
    }

    pNewAnalogVideo->CaptureStaticImage( strFile, nChannel );
}

void CMonitor::HandleDetectInfo( int nChannel, bool bMotion )
{
    static QString strStyle = "background-image: url( );background-color: rgb(255, 0, 0);";
    static QString strBackImage = "background-image: url( );";

    if ( 0 > nChannel || 4 <= nChannel ) {
        return;
    }

    QLabel* pLbl = lblMoving[ nChannel ];
    if ( NULL == pLbl ) {
        return;
    }

    pLbl->setStyleSheet(  bMotion ? strStyle : strBackImage );
}

void CMonitor::ReplacePlateChinese( QString &strPlate )
{
    if ( NULL == pSystem || 0 >= strPlate.length( ) ) {
        return;
    }

    BOOL bReplaceChinese = pSystem->value( "PlateControll/ReplaceChinese", false ).toBool( );
    if ( false == bReplaceChinese ) {
        return;
    }

    QString strDefault = "黑辽湘";
    QString strChineseString = pSystem->value( "PlateControll/ChineseString", strDefault ).toString( );
    if ( 0 >= strChineseString.length( ) ) {
        strChineseString = strDefault;
    }

    strDefault = "川";
    QString strResultChinese = pSystem->value( "PlateControll/ResultChinese", strDefault ).toString( );
    if ( 1 != strResultChinese.length( ) ) {
        strResultChinese = strDefault;
    }

    if ( strChineseString.contains( strPlate.left( 1 ) ) ) {
        strPlate[ 0 ]  = strResultChinese[ 0 ];
    }
}

void CMonitor::HandleUIPlateResult( QString strPlate, int nChannel,
                                    bool bSuccess, bool bVideo, int nWidth,
                                    int nHeight, int nConfidence,
                                    QString strDirection, QByteArray byData,
                                    QRect rectPlate, QRect rectVideo )
{
    if ( bVideo && bPlateBox ) {
        QTransparentFrame::CreateFrame( lblVideoWnd[ nChannel ]->winId( ), rectPlate, rectVideo );
    }

    if ( bVideo && ( !bSuccess || strPlate.isEmpty( ) ) ) {
        return;
    }

    //SetBallotSense( false, nChannel );
    ReplacePlateChinese( strPlate );

    QString strWindth = QString( "%1/%2 " ).arg( QString::number( nWidth ),
                                                QString::number( nHeight ) );
    lblDirection[ nChannel ]->setText( strWindth + strDirection );
    bool bSuccession = pSystem->value( "CommonCfg/Succession", false ).toBool( );
    if ( bSuccession && bPlateVideo && !bSenseGate && !bNocardwork ) {
        CCommonFunction::DisplayPlateChar( lblLicense[ nChannel ], nChannel, strPlate );
        emit OnRecognizePlate( strPlate, nChannel, nConfidence, bSenseGate || bNocardwork, byData ); //自动开闸
        return;
    }

    if ( !bVideo ) { // File
        CCommonFunction::DisplayPlateChar( lblLicense[ nChannel ], nChannel, strPlate );
        emit OnRecognizePlate( strPlate, nChannel, nConfidence, bSenseGate || bNocardwork, byData ); //自动开闸
    } else { // Video
        if ( bBallotSense[ nChannel ] ) { // 车压地感了
            return;
        }

        PlateSort( plateResult[ nChannel ], strPlate );
    }
}

void CMonitor::PlateSort( QHash< QString, int > hash[ ], QString &strPlate )
{
    QString strKey;

    for( int nIndex = 0; nIndex < strPlate.count( ); nIndex++ )  {
        strKey = QString( strPlate.at( nIndex ) );
        if ( !hash[ nIndex ].contains( strKey ) ) {
            hash[ nIndex ].insert( strKey, 0 );
        }

        hash[ nIndex ][ strKey ]++;
    }
}

void CMonitor::SetNewBallotSense( bool bSense, int nChannel, QByteArray& byData )
{
    bBallotSense[ nChannel ] = bSense;
    QLabel* pLabel = NULL;
    QString strPlate;

    if ( bSense && bPlateVideo ) {
        for ( int nIndex = 0; nIndex < 8; nIndex ++ ) {
            pLabel = lblLicense[ nChannel ][ nIndex ];
            QList<int > lstValue = plateResult[ nChannel ][ nIndex ].values( );
            if ( 0 == lstValue.count( ) ) {
                continue;
            }

            qSort( lstValue );
            const QString strKey = plateResult[ nChannel ][ nIndex ].key( lstValue.at( lstValue.count( ) - 1 ), " " );

            if ( NULL != pLabel ) {
                pLabel->setText( strKey );
            }

            strPlate.append( strKey );
        }

        emit OnRecognizePlate( strPlate, nChannel, 0, bSenseGate || bNocardwork, byData ); //自动开闸
    } else {
        for ( int nIndex = 0; nIndex < 8; nIndex++ ) {
            plateResult[ nChannel ][ nIndex ].clear( );
        }

        ClearPlate( nChannel );
    }
}

void CMonitor::PictureRegconize( QString &strFile, int nChannel, QByteArray& byData )
{
    if ( bPlateVideo ) {
        return;
    }

    pPlateThread->PostPlateFileRecognize( byData, strFile, nChannel, bMultiThread );
    SavePicture( strFile );

    //bool bNoCard = pSystem->value( "CommonCfg/NoCardWork", false ).toBool( );
    //Sleep( bNoCard ? 0 : 500 );
    return;

    int nPlateNumber = RECOG_RES;
    //strFile = "d:/1.jpg";
    ZeroMemory( &recogResult[ nChannel ], sizeof ( TH_PlateResult ) * RECOG_RES );
    bool bRet;// = pVehicle->RecognizeFile( strFile, recogResult[ nChannel ], nPlateNumber, nChannel );

    if ( bRet ) { // Display Plate
        DisplayPlate( nChannel );
    }

    SavePicture( strFile );
}

void CMonitor::SavePicture( QString &strFile )
{
    if ( !bSavePicture ) {
        return;
    }

    QString strNew = strRegPicPath + QString::number( QDateTime::currentMSecsSinceEpoch( ) ) + ".jpg";
    QFile::copy( strFile, strNew );
}

void CMonitor::keyPressEvent( QKeyEvent *event )
{

    if ( Qt::AltModifier == event->modifiers( ) ) {
        int key = event->key( );
        qDebug( ) << Q_FUNC_INFO << QString::number( key ) << endl;
        //if ( QMessageBox::Ok == CCommonFunction::MsgBox( NULL, "提示", "确定要推出系统吗？", QMessageBox::Question ) ) {
         //   exit( 0 );
        //}
    }

    QString str1 = "你好";
    QString str2 = "吗？";

    Q_UNUSED( str1 );
    Q_UNUSED( str2 );
    QFrame::keyPressEvent( event );

    bool bRet = pSystem->value( "CommonCfg/HotKeyGate", false ).toBool( );
    if ( !bRet ) {
        return;
    }

    switch ( event->key( ) ) {
    case Qt::Key_F9 :
        ControlGate( true, true, ui->btnEnterGateOpen );
        break;

    case Qt::Key_F10 :
        ControlGate( false, true, ui->btnEnterGateOpen );
        break;

    case Qt::Key_F11 :
        ControlGate( true, false, ui->btnLeaveGateOpen );
        break;

    case Qt::Key_F12 :
        ControlGate( false, false, ui->btnLeaveGateClose );
        break;
    }
}

void CMonitor::GetCanParkIndexNum( )
{
    int nCols = 4;
    int nField = 0;
    QString strCan;
    char cCan;

    CLogicInterface::GetInterface( )->GetCurrentPark( lstPark );
    if ( nCols <= lstPark.count( ) ) {
        strParkName = lstPark[ 1 ];
        nTotalParkSpace = lstPark[ 2 ].toInt( );
    }

    int nRows = lstPark.count( ) / nCols;

    // CAN / PARKINDEX / PARKNUM / PARKNAME

    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        nField = nIndex * nCols;
        strCan = lstPark[ nField ];
        short sCan = strCan.toShort( );
        cCan = ( char ) sCan;

        CCommonFunction::GetCanParkIndexNum( 0 ).insert( cCan, lstPark[ nField + 1 ] );
        CCommonFunction::GetCanParkIndexNum( 1 ).insert( cCan, lstPark[ nField + 2 ] );
        CCommonFunction::GetCanParkIndexNum( 2 ).insert( cCan, lstPark[ nField + 3 ] );
    }
}

void CMonitor::ControlGateButton( )
{
    bool bRet = pSystem->value( "CommonCfg/HotKeyGate", false ).toBool( );

    ui->btnEnterGateOpen->setEnabled( bRet ) ;
    ui->btnEnterGateClose->setEnabled( bRet ) ;
    ui->btnLeaveGateOpen->setEnabled( bRet ) ;
    ui->btnLeaveGateClose->setEnabled( bRet ) ;
}

CMonitor::CMonitor(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(
        #ifdef NewUI
            new Ui::CONCAT_NEW_NAME( New , CMonitor )
        #else
            new Ui::CONCAT_NEW_NAME( , CMonitor )
        #endif
        )
{
    ui->setupUi(this);
    CreateGateButton( );

    pSysSet = CCommonFunction::GetSettings( CommonDataType::CfgSysSet );
    pSystem= CCommonFunction::GetSettings( CommonDataType::CfgSystem );

    bMultiThread = pSystem->value( "CommonCfg/PlateMultiThread", false ).toBool( );
    bDongleOneWay = pSystem->value( "CommonCfg/DongleOneWay", false ).toBool( );
    pPlateThread = QPlateThread::GetInstance( );

    ui->pushButton_2->setVisible( false );
    ui->pushButton->setVisible( false );
    ui->spinBox->setVisible( false );
    ui->label_3->setVisible( false );
    ui->lblFileCount->setVisible( false );
    pMainWnd = this;
    GetCanParkIndexNum( );
    nRefreshParkspaceTime = 1000 * 60;

    ReadDefaultCan( lstEnterCanOpen, true, true );
    ReadDefaultCan( lstEnterCanClose, true, false );
    ReadDefaultCan( lstLeaveCanOpen, false, true );
    ReadDefaultCan( lstLeaveCanClose, false, false );

    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    //qobject_cast()

    bPlateBox = pSystem->value( "CommonCfg/PlateBox", false ).toBool( );
    nRealTimeRecord = pSystem->value( "CommonCfg/RealTimeRecord", 100 ).toInt( );
    bPlateVideo = pSystem->value( "CommonCfg/PlateVideo", true ).toBool( );
    bSavePicture = pSystem->value( "CommonCfg/SavePicture", false ).toBool( );
    bNetworkCamera = pSystem->value( "CommonCfg/NetworkCamera", false ).toBool( );
    pNewAnalogVideo = NULL;
    bNocardwork = pSystem->value( "CommonCfg/NoCardWork", false ).toBool( );
    bSenseGate = pSystem->value( "CommonCfg/SenseOpenGate", false ).toBool( );

    InitChannelHandle( );

    //QString strLink = "<a href=\"/\" style = \"text-decoration:none;color: rgb(244, 244, 0);\">校正</a>";
    //ui->lblLicence19->setText( strLink );
    //ui->lblLicence29->setText( strLink );
    CCommonFunction::ControlSysMenu( *this );
    //pVehicle = NULL;
    ControlDataGrid( *ui->tabRecord );
    bool bRet = connect( pParent, SIGNAL( OnUserChanged( QString&, QString& ) ), this, SLOT( ChangeUser( QString&, QString& ) ) );
    bRet = connect( this, SIGNAL( OnRecognizePlate( QString, int, int, bool, QByteArray )), pParent, SLOT( RecognizePlate( QString, int, int, bool, QByteArray ) ) );
    bRet = connect( this, SIGNAL( OnDirectionIndicator( int, bool ) ), this, SLOT( DirectionIndicator( int, bool ) ) );

    CCommonFunction::GetPath( strImagePath, CommonDataType::PathUIImage );
    strButtonStyle = "background-image:url(%1NewIcon/%2-%3.JPG);\nborder-style: outset; ";

    strRegPicPath = strImagePath + "PlatePicture/";
    QDir dir;
    if ( !dir.exists( strRegPicPath ) ) {
        dir.mkpath( strRegPicPath );
    }

    SpaceInfo( );
    InitVideoPlateUI( );
    StartSpaceTimer( );
    InitStatistics( );

    pDlgAlert = new CDlgAlert( );
    pDlgAlert->setStatusTip( strImagePath + "NewIcon/CommonMiddleBG-normal.jpg" );

    connect( &CLogicInterface::GetInterface( )->GetMysqlDb( ), SIGNAL( NotifyError( QString ) ), this, SLOT( DisplayDbError( QString ) ) );
    ControlGateButton( );

    ipcVideoFrame = new CIPCVideoFrame( bNetworkCamera );
    connect( ipcVideoFrame, SIGNAL( NotifyMessage( QString ) ),
             this, SLOT( HandleIPCMsg( QString ) ) );
}

void CMonitor::HandleIPCMsg( QString strMsg )
{
    //ui->lblAlert->setText( strMsg );
}

void CMonitor::SetFileCount( quint32 nCount )
{
    ui->lblFileCount->setVisible( true );
    QString strText = QString::number( nCount );
    ui->lblFileCount->setText( strText );
}

void CMonitor::DisplayDbError( QString strMsg )
{
    CCommonFunction::MsgBox( NULL, "提示", strMsg, QMessageBox::Information );
}

void CMonitor::HideAlert( )
{
    bool bHide = !pSystem->value( "CommonCfg/HideAlert", true ).toBool( );
    ui->lblAlert->setVisible( bHide );
}

void CMonitor::SetAlertMsg( const QString &strText )
{
    ui->lblAlert->setText( strText );
}

void CMonitor::InitVideoPlateUI( )
{
    nUsedWay = pSysSet->value( "VideoMode/Way", 2 ).toInt( );
    if ( VIDEO_USEDWAY < nUsedWay ) {
        nUsedWay = VIDEO_USEDWAY;
    }

    bool bAuto = pSysSet->value( "VideoMode/AutoVideo", false ).toBool( );

    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgPlate );
    //QSettings* pSystem= CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    bDisplayAlert = pSystem->value( "CommonCfg/DisplayAlert", false ).toBool( );
    nRefreshParkspaceTime = pSystem->value( "CommonCfg/RefreshParkspaceTime", 5 * 1000 * 60 ).toInt( );

    /////////////////////////////////////////////////////////////////////////////
    QString strVideo = "video%1";
    QString strDirection = "lblDir%1";
    QString strMoving = "lblMoving%1";
    QString strTitle = "lblTitle%1";
    QString strPlate = "WintonePlate/WintonePlate%1/PlateStart";
    QLabel* pTitle = NULL;
    QString strKey = "CommonCfg/Name%1";
    int nRealIndex = 0;

    //bPlateFilter = pSystem->value( "CommonCfg/PlateFilter", false ).toBool( );
    //bSuccession = pSystem->value( "CommonCfg/Succession", false ).toBool( );
    QRect rect;
    int nMode =  0;

    ui->video1->setVisible( false );
    ui->video2->setVisible( false );
    ui->video3->setVisible( false );
    ui->video4->setVisible( false );
    ui->video5->setVisible( false );

    for ( int nIndex = 0; nIndex < VIDEO_USEDWAY; nIndex++ ) {
        nRealIndex = nIndex + 1;
        if ( bAuto ) {
            nMode = nIndex % 2;
            rect.setX( nMode ?
               #ifdef NewUI
                       483
               #else
                       509
               #endif
                            :
               #ifdef NewUI
                       47
               #else
                       48
               #endif
                           );
            rect.setY( nIndex - nMode ?
               #ifdef NewUI
                       466
               #else
                       546
               #endif
                         :
               #ifdef NewUI
                       173
               #else
                       203
               #endif
                           );
            rect.setWidth(
                #ifdef NewUI
                        389
                #else
                        410
                #endif
                           );
            rect.setHeight(
                #ifdef NewUI
                        234
                #else
                        275
                #endif
                            );
            lblVideoWnd[ nIndex ] = new CMyLabel( nIndex, rect, bNetworkCamera, this );
            QString strKey = QString( "CommonCfg/Video%1" ).arg( nIndex + 1 );
            QString strCan = pSystem->value( strKey, "0" ).toString( );

            lblVideoWnd[ nIndex ]->setToolTip( strCan );
            if ( "0" != strCan && bNetworkCamera ) {
                QString strSQL = QString( "Select video2ip from roadconerinfo where \
                                          shebeiadr = %1 and video1ip = '%2'" ).arg(
                        strCan, CCommonFunction::GetHostIP( ) );
                QStringList lstRow;
                if ( 0 < CLogicInterface::GetInterface( )->ExecuteSql( strSQL, lstRow ) ) {
                    lblVideoWnd[ nIndex ]->setToolTip( lstRow.at( 0 ) );
                }
            }
        } else {
             lblVideoWnd[ nIndex ] = findChild< QLabel* >( strVideo.arg( nRealIndex ) );
        }

        connect( lblVideoWnd[ nIndex ], SIGNAL( HideCtrl( int, bool ) ), this, SLOT( HideCtrl( int, bool ) ) );
        bPlateStart[ nIndex ] = ( 1 == pSet->value( strPlate.arg( nIndex ), 0 ).toInt( ) );
        lblDirection[ nIndex ] = findChild< QLabel* >( strDirection.arg( nRealIndex ) );
        lblMoving[ nIndex ] = findChild< QLabel* >( strMoving.arg( nRealIndex ) );
        pTitle = findChild< QLabel* >( strTitle.arg( nRealIndex ) );
        pTitle->setText( pSystem->value( strKey.arg( nRealIndex ), nRealIndex ).toString( ) );

        bBallotSense[ nIndex ] = false;
    }

    QString strName = "lblNumber%1";
    for ( int nIndex = 0; nIndex < ( int ) ( sizeof ( lblStatistics ) / sizeof ( QLabel* ) ); nIndex++ ) {
        lblStatistics[ nIndex ] = findChild< QLabel* >( strName.arg( nIndex ) );
        nCurrentTotal[ nIndex ] = 0;
    }

    strName = "lblLicence%1%2";
    QLabel* pLabel = NULL;
    for ( int nChannel = 1; nChannel <= 4; nChannel++ ) {
        for ( int nIndex = 1; nIndex <= 8; nIndex++ ) {
            pLabel = findChild< QLabel* >( strName.arg( nChannel ).arg( nIndex ) );
            lblLicense[ nChannel - 1 ][ nIndex - 1 ] = pLabel;

            if ( NULL != pLabel ) {
                QObject::connect( pLabel, SIGNAL( linkActivated( QString ) ), this, SLOT( onLinkActivated( QString ) ) );
            }
        }
    }
}

void CMonitor::HideCtrl( int nIndex, bool bVisible )
{
    QString strMoving = "lblMoving%1";
    QLabel* pLbl = NULL;

    for ( int nItem = 0; nItem < 4; nItem++ ) {
        //pLbl = findChild< QLabel* >( strMoving.arg( nItem + 1 ) );
        pLbl = lblMoving[ nItem ];
        pLbl->setVisible( bVisible );

        if ( nIndex == nItem ) {
            continue;
        }

        lblVideoWnd[ nItem ]->setVisible( bVisible );
    }

    //ui->lblDateTime->setVisible( bVisible );
}

void CMonitor::UpdateStatistics( int nNumber, int nIndex, bool bInit )
{
    static QString strInfo[ ] = { "进%1辆", "出%1辆", "当班收费：%1元", "进%1辆", "出%1辆", "当班免费：%1元" };
    if ( bInit ) {
       nCurrentTotal[ nIndex ] = nNumber;
    } else {
       nCurrentTotal[ nIndex ] += nNumber;
    }

    lblStatistics[ nIndex ]->setText( strInfo[ nIndex ].arg( nCurrentTotal[ nIndex ] ) );
}

void CMonitor::ClearStatistics( )
{
    UpdateStatistics( 0, 0, true );
    UpdateStatistics( 0, 1, true );
    UpdateStatistics( 0, 3, true );
    UpdateStatistics( 0, 4, true );
}

void CMonitor::InitStatistics(  )
{
    // intime outtime  and ( %4 not is null )
    QString strTime1 = " 00:00:00";
    QString strTime2 = " 23:59:59";
    QString strField[ ] = { "in", "out", "", "in", "out" };
    QString strSql = QString( "Select count( * ) from stoprd where ( %1time between '%2' and '%3' ) \
                     and %4shebeiname in ( select shebeiname  from roadconerinfo where \
                     video1ip = '%5' and ( shebeiadr between 1 and 30 ) \
                     and shebeiadr % 2 %6= 0 ) %7" );
    QString strDate;
    QDate date = QDate::currentDate( );
    CCommonFunction::Date2String( date, strDate );
    QStringList lstData;
    QString strTmp;
    int nRows;

    for ( int nIndex = 0; nIndex < 6; nIndex++ ) {
        if ( 2 == nIndex || 5 == nIndex ) { // 0 1 2 3 4 5
            continue;
        }

        lstData.clear( );
        strTmp = strSql.arg( strField[ nIndex ], strDate + strTime1, strDate + strTime2, strField[ nIndex ],
                             CCommonFunction::GetHostIP( ),
                             ( ( ( 0 == nIndex ) || ( 3 == nIndex ) ) ? "!" : "" ),
                             ( ( 1 >= nIndex ) ? "" : "and cardkind = '计时卡'" ) );
        nRows = CLogicInterface::GetInterface( )->ExecuteSql( strTmp, lstData );
        if ( 0 < nRows ) {
            UpdateStatistics( lstData[ 0 ].toInt( ), nIndex, true );
        }
    }
}

void CMonitor::LoadDigital( int nGroup, int nDigital, char cColor )
{
    QString strTemplate = QString( "lbl%1" ).arg( nGroup ) + "%1";
    QString strDigital = QString::number( nDigital );
    int nCount = strDigital.count( );
    QChar color = cColor;
    QChar digital;

    for ( int nIndex = 1; nIndex <= 4; nIndex++ ) {
        QString strName = strTemplate.arg( nIndex );
        QLabel* pLbl = findChild< QLabel* >( strName );

        if ( nIndex > nCount ) {
            color = 'b';
            digital = '0';
        } else {
            digital = strDigital[ nIndex - 1 ];
        }

        QString strStyle = strButtonStyle.arg( strImagePath, digital, color );
        pLbl->setStyleSheet( strStyle );
    }
}

void CMonitor::DisplayAlert( QStringList &lstData )
{
    if ( 7 > lstData.count( ) ) {
        return;
    }

    lstData.removeAt( 0 );
    pDlgAlert->DisplayAlert( lstData );

    if ( !pDlgAlert->isVisible( ) && bDisplayAlert ) {
        pDlgAlert->show();
    }
}

void CMonitor::FillDataGrid( QStringList &lstData )
{
    int nField = 1;
    int nCols = 12;
    int nRows = lstData.count( ) / nCols;
    if ( 0 >= nRows ) {
        return;
    }

    if ( nRealTimeRecord < ui->tabRecord->rowCount( ) ) {
        for ( int nIndex = ui->tabRecord->rowCount( ) - 1; nIndex > nRealTimeRecord - 1; nIndex-- ) {
            ui->tabRecord->removeRow( nIndex );
        }
    }

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        ui->tabRecord->insertRow( 0 );
        nField = nRow * nCols + 1;

        for ( int nCol = 0; nCol < nCols - 1; nCol++ ) {
            QString& strText = lstData[ nField + nCol ];
            QTableWidgetItem* pItem = new QTableWidgetItem( strText );
            pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsEnabled );

            ui->tabRecord->setItem( 0, nCol, pItem );

            if ( ( nCol == nCols - 2 ) && CCommonFunction::GetHostIP( ) == strText ) {
               pItem->setText( "127.0.0.1" );
            }
        }
    }
}

void CMonitor::ChangeUser( QString &strUser, QString& strID )
{
   QString struser = "当前用户：" + strUser;
   ui->lblCurrentUser->setText( struser );

   if ( strID != strUserID ) {
       strUserID = strID;
       UpdateStatistics( 0, 2, true );
       UpdateStatistics( 0, 5, true );
   }
}

void CMonitor::SetMenu( QList<QMenu *> &lstMenu )
{
    if ( 5 > lstMenu.count( ) ) {
        return;
    }
    // Menu
    ui->btnSysMan->setMenu( lstMenu[ 0 ] );
    //connect( ui->btnSysMan, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    //connect( ui->btnSysMan, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    ui->btnCardMan->setMenu( lstMenu[ 1 ] );
    //connect( ui->btnCardMan, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    //connect( ui->btnCardMan, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    ui->btnAdvSet->setMenu( lstMenu[ 2 ] );
    //connect( ui->btnAdvSet, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    //connect( ui->btnAdvSet, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    ui->btnReport->setMenu( lstMenu[ 3 ] );
    //connect( ui->btnReport, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    //connect( ui->btnReport, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    ui->btnHelp->setMenu( lstMenu[ 4 ] );
    //connect( ui->btnHelp, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    //connect( ui->btnHelp, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    // Toolbar
    bool bRet = connect( ui->btnShift, SIGNAL( clicked( ) ), pParent, SLOT( on_actShiftLogout_triggered( ) ) );
    connect( ui->btnShift, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnShift, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    bRet = connect( ui->btnMonthCard, SIGNAL( clicked( ) ), pParent, SLOT( on_actMonthlyCard_triggered( ) ) );
    connect( ui->btnMonthCard, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnMonthCard, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    bRet = connect( ui->btnValueCard, SIGNAL( clicked( ) ), pParent, SLOT( on_actValueCard_triggered( ) ) );
    connect( ui->btnValueCard, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnValueCard, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    bRet = connect( ui->btnTimeCard, SIGNAL( clicked( ) ), pParent, SLOT( on_actTimeCard_triggered( ) ) );
    connect( ui->btnTimeCard, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnTimeCard, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    bRet = connect( ui->btnPassRecord, SIGNAL( clicked( ) ), pParent, SLOT( on_actAccess2Records_triggered( ) ) );
    connect( ui->btnPassRecord, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnPassRecord, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    // Gate
    bRet = connect( ui->btnEnterGateOpen, SIGNAL( clicked( ) ), this, SLOT( GateOpen1( ) ) );
    connect( ui->btnEnterGateOpen, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnEnterGateOpen, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    bRet = connect( ui->btnEnterGateClose, SIGNAL( clicked( ) ), this, SLOT( GateClose1( ) ) );
    connect( ui->btnEnterGateClose, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnEnterGateClose, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    bRet = connect( ui->btnLeaveGateOpen, SIGNAL( clicked( ) ), this, SLOT( GateOpen2( ) ) );
    connect( ui->btnLeaveGateOpen, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnLeaveGateOpen, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    bRet = connect( ui->btnLeaveGateClose, SIGNAL( clicked( ) ), this, SLOT( GateClose2( ) ) );
    connect( ui->btnLeaveGateClose, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnLeaveGateClose, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    // Verify
    connect( ui->btnVerifyIn0, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnVerifyIn1, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnVerifyOut0, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnVerifyOut1, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );

    connect( ui->btnVerifyIn0, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );
    connect( ui->btnVerifyIn1, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );
    connect( ui->btnVerifyOut0, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );
    connect( ui->btnVerifyOut1, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    connect( ui->btnVerifyIn0, SIGNAL( clicked( ) ), this, SLOT( onBtnVerifyInClicked( ) ) );
    connect( ui->btnVerifyIn1, SIGNAL( clicked( ) ), this, SLOT( onBtnVerifyInClicked( ) ) );
    connect( ui->btnVerifyOut0, SIGNAL( clicked( ) ), this, SLOT( onBtnVerifyOutClicked( ) ) );
    connect( ui->btnVerifyOut1, SIGNAL( clicked( ) ), this, SLOT( onBtnVerifyOutClicked( ) ) );

    // Status
    connect( ui->btnCenterControlerStatus, SIGNAL( clicked( ) ), this, SLOT( OnClickedDlgPopup( ) ) );
    connect( ui->btnCenterControlerStatus, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnCenterControlerStatus, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    connect( ui->btnPublishLedInfo, SIGNAL( clicked( ) ), this, SLOT( OnClickedDlgPopup( ) ) );
    connect( ui->btnPublishLedInfo, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnPublishLedInfo, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    connect( ui->btnEnterPeripheralStatus, SIGNAL( clicked( ) ), this, SLOT( OnClickedDlgPopup( ) ) );
    connect( ui->btnEnterPeripheralStatus, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnEnterPeripheralStatus, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    connect( ui->btnSmsNotification, SIGNAL( clicked( ) ), this, SLOT( OnClickedDlgPopup( ) ) );
    connect( ui->btnSmsNotification, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnSmsNotification, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    connect( ui->btnLeavePeripheralStatus, SIGNAL( clicked( ) ), this, SLOT( OnClickedDlgPopup( ) ) );
    connect( ui->btnLeavePeripheralStatus, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnLeavePeripheralStatus, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );

    connect( ui->btnCandinate, SIGNAL( clicked( ) ), this, SLOT( OnClickedDlgPopup( ) ) );
    connect( ui->btnCandinate, SIGNAL( pressed( ) ), this, SLOT( BtnPressed( ) ) );
    connect( ui->btnCandinate, SIGNAL( released( ) ), this, SLOT( BtnReleased( ) ) );
}

void CMonitor::OnClickedDlgPopup(  )
{
    QPushButton* pBtn = qobject_cast< QPushButton* >( sender( ) );
    QString strObjName = pBtn->objectName( );
    //static QString strStyle = strButtonStyle.arg( strImagePath, "CommonBG", "normal" );
    QDialog* pDlg = NULL;

    if ( strObjName == ui->btnCenterControlerStatus->objectName( ) ) {
        pDlg = new CDlgCCStatus( this );
    } else if ( strObjName == ui->btnPublishLedInfo->objectName( ) ) {
        //pDlg = new CLedInfoDialog( this );
        static CPublishLEDInfo dlg( true, pParent, this );
        QString strStyle = QString( "background-image:url(%1NewIcon/CommonMiddleBG-normal.jpg)" ).arg( strImagePath );
        dlg.setStyleSheet( strStyle );
        HWND hChildWnd = dlg.winId( );
        ::BringWindowToTop( hChildWnd );
        dlg.show( );
        return;
    } else if ( strObjName == ui->btnEnterPeripheralStatus->objectName( ) ) {
        pDlg = new CDlgPeripheralStatus( true, this );
        connect( ( CProcessData::GetProcessor( ) ), SIGNAL( OnResponseUserRequest( QByteArray& , int ) ),
                 pDlg, SLOT( ResponseUserRequest( QByteArray&, int ) ) );
    } if ( strObjName == ui->btnLeavePeripheralStatus->objectName( ) ) {
        pDlg = new CDlgPeripheralStatus( false, this );
        connect( ( CProcessData::GetProcessor( ) ), SIGNAL( OnResponseUserRequest( QByteArray& , int ) ),
                 pDlg, SLOT( ResponseUserRequest( QByteArray&, int ) ) );
    } else if ( strObjName == ui->btnSmsNotification->objectName( ) ) {
        pDlg = new CDlgSMSNotification( this );
    } else if ( strObjName == ui->btnCandinate->objectName( ) ) {
        pDlg = new CDlgQueryOwner( this );
    }

    //CCommonFunction::ControlSysMenu( *pDlg );
    SetDlgBackground( *pDlg );

    pDlg->exec( );

    delete pDlg;
    pDlg = NULL;
}

void CMonitor::SetDlgBackground( QDialog &dlg )
{
    QString strStyle = "background-image: url( );";
    dlg.setStyleSheet( strStyle );
    dlg.setWindowFlags( Qt::FramelessWindowHint );
    strStyle = strImagePath + "NewIcon/CommonBG-normal.jpg";
    dlg.setStatusTip( strStyle );
    dlg.setParent( NULL );
    return;

    QPalette pal;
    QPixmap map( strImagePath + "NewIcon/CommonBG-normal.jpg" );
    QPixmap tmp = map.scaled( dlg.size( ) );
    QBrush br( tmp );
    pal.setBrush( dlg.backgroundRole( ), br );
    dlg.setPalette( pal );
    dlg.setAutoFillBackground( true );
    dlg.setWindowFlags( Qt::FramelessWindowHint );
}

void CMonitor::BtnPermission( bool bNormal, int nIndex )
{
    QPushButton* pBtn = NULL;
    switch ( nIndex )
    {
    case 0 :
        pBtn = ui->btnMonthCard;
        break;

    case 1 :
        pBtn = ui->btnValueCard;
        break;

    case 2 :
        pBtn = ui->btnTimeCard;
        break;

    case 3 :
        pBtn = ui->btnPassRecord;
        break;
    }

    if ( NULL == pBtn ) {
        return;
    }

    pBtn->setEnabled( bNormal );
    qDebug( ) << "BtnPermission : " << pBtn->objectName( ) << " " << bNormal << endl;
    SwitchImage( pBtn, false, bNormal );
}

void CMonitor::BtnPressed( )
{
    QPushButton* pBtn = qobject_cast< QPushButton* >( sender( ) );
    SwitchImage( pBtn, true );
}

void CMonitor::BtnReleased( )
{
    QPushButton* pBnt = qobject_cast< QPushButton* >( sender( ) );
    SwitchImage( pBnt, false );
}

void CMonitor::SwitchImage( QPushButton *pBtn, bool bDown, bool bPermission )
{
    QString strStyle = strButtonStyle.arg( strImagePath, pBtn->objectName( ).remove( "2"), bPermission ? ( bDown ?
                                                                                                               pParent->GetPictureName( "clicked%1" ) :
                                                                                                               pParent->GetPictureName( "normal%1" ) ) :
                                                                                                         pParent->GetPictureName( "disabled%1" ) );
    //qDebug( ) << strStyle << endl << "Down" << bDown << endl;
    pBtn->setStyleSheet( strStyle );
    qDebug( ) << Q_FUNC_INFO << strStyle << endl;
}

QLabel* CMonitor::GetDateTimeCtrl( )
{
    return ui->lblDateTime;
}

void CMonitor::ControlDataGrid( QTableWidget& tw )
{
    QHeaderView* pHeader = tw.verticalHeader( );
    pHeader->setMinimumSize( 10, 4 );
    pHeader->setResizeMode( QHeaderView::Fixed );
    //QString strStyle = "color: rgb(73, 63, 107);";
    //pHeader->>setStyleSheet( strStyle );

    pHeader = tw.horizontalHeader( );
    pHeader->setResizeMode( QHeaderView::Fixed );
    pHeader->setShown( true );
    pHeader->resizeSection( 0, 80 );
    pHeader->resizeSection( 1, 80 );
    pHeader->resizeSection( 2, 80 );
    pHeader->resizeSection( 3, tw.width( ) - 250 - tw.autoScrollMargin( ) );

    pHeader->hideSection( 4 );
    pHeader->hideSection( 5 );
    pHeader->hideSection( 6 );
    pHeader->hideSection( 7 );
    pHeader->hideSection( 8 );
    pHeader->hideSection( 9 );
    pHeader->hideSection( 10 );
}

void CALLBACK PrcPicMessage( long lnCardID, long pBuf, long lnWidth, long lnHeight )
{

}

void CMonitor::PrcCapSourceStream(DWORD dwCard, BYTE *pbuff, DWORD dwSize)
{
    DWORD lnCardID = dwCard;
    bool bMoving = pMainWnd->bStartRecognization[ lnCardID ];
    emit pMainWnd->OnDirectionIndicator( lnCardID, bMoving );

    if ( false == bMoving ) {
        return;
    }

    int nResult = 0;
    //CVehicleLicense* pVehicle = pMainWnd->GetPlateRecognization( );
    //if ( NULL == pVehicle ) {
     //   return;
    //}

    //memcpy( imgData[ lnCardID ], ( void* ) pBuf, lnWidth * lnHeight * lnBiCount );

    qDebug( ) << "CardID : " << QString::number( lnCardID ) << endl;
    nResult = RECOG_RES;
    bool bRet;// = pVehicle->RecognizeVideo( ( quint8* ) pbuff, 352,
               //                           288, recogResult[ lnCardID ], nResult, lnCardID );

    if ( bRet ) { // Display Plate
        pMainWnd->DisplayPlate( lnCardID );
    }
}

//( DWORD dwCard, BOOL bMove, BYTE *pbuff, DWORD dwSize, LPVOID lpContext )
void CALLBACK MyPrcCbMotionDetect( DWORD dwCard, BOOL bMove, BYTE *pbuff, DWORD dwSize, LPVOID lpContext )
{
    DWORD lnCardID = dwCard;
    CMonitor::bStartRecognization[ lnCardID ] = bMove;
    qDebug( ) << "MyPrcCbMotionDetect " << endl;
}

void CMonitor::MotionDetection( ULONG nChannel, BOOL bMotionDetected, void *context )
{
    bStartRecognization[ nChannel ] = bMotionDetected;
    //qDebug( ) << "MotionDetection : " << bMotionDetected << endl;
}

void CMonitor::DirectionIndicator( int nChannel, bool bMoving )
{
    static QString strStyle = "background-image: url( );background-color: rgb(255, 0, 0);";
    static QString strBackImage = "background-image: url( );";

    if ( 0 > nChannel || 4 <= nChannel ) {
        return;
    }

    QLabel* pLbl = lblMoving[ nChannel ];
    if ( NULL == pLbl ) {
        return;
    }

    pLbl->setStyleSheet(  bMoving ? strStyle : strBackImage );
}

void CMonitor::ImageStreamCallback( UINT nChannel, PVOID pContent )
{
     static int nConter = 25;
     QString strInfo;
     QTime time;
     if ( nConter == 25 ) {
         time = QTime::currentTime( );
         strInfo = time.toString( "Begin hh:mm:ss.zzz" ) + "\r\n";
     }
     /////////////////
    bool bMoving = bStartRecognization[ nChannel ];
    CMonitor* pMainWnd = ( CMonitor* ) pContent;
    emit pMainWnd->OnDirectionIndicator( nChannel, bMoving );

    if ( false == bMoving ) {
        strInfo += "No Moving\r\n";
        return;
    }

    int nResult = 0;

    //CVehicleLicense* pVehicle = pMainWnd->GetPlateRecognization( );
    //if ( NULL == pVehicle ) {
    //    return;
    //}

    //qDebug( ) << "Time1 " << QDateTime::currentDateTime( ).toMSecsSinceEpoch( ) << endl;
    nResult = RECOG_RES;
    quint8* pData = new quint8[ VIDEO_BUF ];
    //memcpy( pData, imgData[ nChannel ], VIDEO_BUF );//imgData[ nChannel ]
    bool bRet;// = pVehicle->RecognizeVideo( pData, 704, 576, recogResult[ nChannel ], nResult, nChannel );
    strInfo += "RecognizeVideo\r\n";

    //qDebug( ) << "Time2 " << QDateTime::currentDateTime( ).toMSecsSinceEpoch( ) << endl;
    if ( bRet ) { // Display Plate
        bool bPlateFilter = GetPlateSuccession( true, nChannel + 1 );
        bPlateFilter ? pMainWnd->DisplayPlate( nChannel ) : pMainWnd->PlateFilter2( nChannel );
    }
    //qDebug( ) << "Time3 " << QDateTime::currentDateTime( ).toMSecsSinceEpoch( ) << endl;
    ///////
    if ( 0 == ( --nConter ) ) {
        time = QTime::currentTime( );
        strInfo += time.toString( "End hh:mm:ss.zzz" ) + "\r\n";
        nConter = 25;
    }

    pMainWnd->WriteFrameInfo( strInfo );
}

void CMonitor::WriteFrameInfo( QString &strInfo )
{
    return;
    static QFile file;

    if ( !file.isOpen( ) ) {
        file.setFileName( "c:/FrameCallback.txt" );
        file.open( QIODevice::WriteOnly | QIODevice::Append );
    }

    QByteArray byData = strInfo.toAscii( );
    file.write( byData );
    file.flush( );
}


void CMonitor::SetBallotSense( bool bSense, int nChannel, QByteArray& byData )
{
    SetNewBallotSense( bSense, nChannel, byData );
    return;

    bBallotSense[ nChannel ] = bSense;
    bool bPlateFilter = GetPlateSuccession( true, nChannel + 1 );

    if ( !bPlateVideo ) {
        bPlateFilter = false;
    }

    if ( !bSense ) {
        ZeroMemory( &structPlates[ nChannel ], sizeof ( TH_PlateResult ) );
        ZeroMemory( &recogResult[ nChannel ], sizeof ( TH_PlateResult ) * RECOG_RES );
        ClearPlate( nChannel );
    } else if ( !bPlateFilter ){ // PlateFilter2
        //DisplayPlate( nChannel );
    }
}

bool CMonitor::GetPlateSuccession( bool bFilter, int nIndex  )
{
    QSettings* pSys= CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    pSys->sync( );
    QString strKey = QString( "CommonCfg/%1%2").arg( bFilter ? "PlateFilter" : "Succession", QString::number( nIndex ) );
    bool bRet = pSys->value( strKey, false ).toBool( );

    return bRet;
}

bool CMonitor::PlateFilter( int nChannel, TH_PlateResult*& pResult )
{
    bool bRet = false;
    bool bSuccession = GetPlateSuccession( false, nChannel + 1 );

    int nCmp = strcmp( recogResult[ nChannel ] [ 0 ].license, structPlates[ nChannel ].license );
    if ( 0 == nCmp && !bSuccession ) { // The Same Plate
        return bRet;
    }

    bool bConfidence = ( recogResult[ nChannel ] [ 0 ].nConfidence > structPlates[ nChannel ].nConfidence );
    if ( !bConfidence && !bSuccession ) { // Lower Confidence
        return bRet;
    }

    structPlates[ nChannel ] = recogResult[ nChannel ] [ 0 ]; // Copy data
    pResult = &structPlates[ nChannel ];

    if ( !bBallotSense[ nChannel ] && !bSuccession ) {
        return bRet;
    }

    return true;
}

void CMonitor::PlateFilter2( int nChannel )
{
    bool bConfidence = ( recogResult[ nChannel ] [ 0 ].nConfidence >= structPlates[ nChannel ].nConfidence );
    if ( !bConfidence ) { // Lower Confidence
        return;
    }
    structPlates[ nChannel ] = recogResult[ nChannel ] [ 0 ]; // Copy data
}

void CMonitor::DisplayPlate( int nChannel )
{
    try {
        TH_PlateResult* pResult = &recogResult[ nChannel ][ 0 ];
    // Picture 关闭连续识别
        //if ( bPlateVideo ) {
            bool bPlateFilter = GetPlateSuccession( true, nChannel + 1 );
            if ( !bPlateVideo ) {
                bPlateFilter = false;
                structPlates[ nChannel ] = recogResult[ nChannel ][ 0 ];
            }
            pResult = bPlateFilter ? NULL : &structPlates[ nChannel ];
            if ( bPlateFilter && ( !PlateFilter( nChannel, pResult ) || ( NULL == pResult ) ) ) {
                return;
            }
        //}

    QString strPlate( pResult->license );
    if ( strPlate.isEmpty( ) ) {
        return;
    }

    if ( bPlateVideo ) {
        bool bSuccession = GetPlateSuccession( false, nChannel + 1 );
        if ( bSuccession ) {
            if ( strPlates[ nChannel ] == strPlate ) {
                return;
            } else {
                strPlates[ nChannel ] = strPlate;
            }
        }
    }
    //ui->lblTmp->setText( strPlate );
    QString strDirection;
    //pVehicle->GetPlateMoveDirection( strDirection, pResult->nDirection );

    int nWidth  = pResult->rcLocation.right - pResult->rcLocation.left;
    int nHeight  = pResult->rcLocation.bottom - pResult->rcLocation.top;

    int nConfidence = pResult->nConfidence;
    //ui->lblConfidence->setText( QString::number( nConfidence ) );
    QByteArray byData;
    SetBallotSense( false, nChannel, byData );

    QString strWindth = QString( "%1/%2 " ).arg( QString::number( nWidth ),
                                                QString::number( nHeight ) );
    lblDirection[ nChannel ]->setText( strWindth + strDirection );

    CCommonFunction::DisplayPlateChar( lblLicense[ nChannel ], nChannel, strPlate );
    //Sleep( 500 );

    emit OnRecognizePlate( strPlate, nChannel, nConfidence, false, QByteArray( ) );
    } catch ( ... ) {
        qDebug( ) << " Display Exception" << endl;
    }
}

//CVehicleLicense* CMonitor::GetPlateRecognization( )
//{
//    return pVehicle;
//}

void CMonitor::GetFileName( QString& strFileName, QString strExt )
{
    strFileName.clear( );
    QDateTime dtCurrent = QDateTime::currentDateTime();
    QString strDateTime = dtCurrent.toString( "yyyy-MM-dd HHmmss " );
    strDateTime += QString::number( dtCurrent.toMSecsSinceEpoch( ) );
    strFileName = QString( "%1/Data/%2.%3" ).arg( QApplication::applicationDirPath( ) ).arg( strDateTime ).arg( strExt );
}

void CMonitor::InitChannelHandle( )
{
    for ( int nIndex = 0; nIndex < ENCODECHANNEL; nIndex++ ) {
        hChannelHandle[ nIndex ] = INVALID_HANDLE;
    }

    pMultimedia = NULL;
    nEncode = 0;
}

CMonitor::~CMonitor()
{
    delete pDlgAlert;
    StopAvSdk( );
    StopIPC( );

    if ( NULL !=  ipcVideoFrame ) {
        delete ipcVideoFrame;
    }

    delete ui;
}

void CMonitor::CaptureImage( QString& strFile, int nChannel, CommonDataType::CaptureImageType capType )
{
    CaptureNewImage( strFile, nChannel, capType );
    return;

    if ( QFile::exists( strFile ) ) {
        QFile::remove( strFile );
    }

    if ( bNetworkCamera ) {
        HWND hPlayWnd = lblVideoWnd[ nChannel ]->winId( );
        QString strIP = lblVideoWnd[ nChannel ]->toolTip( );

        ipcVideoFrame->CaptureDeviceImage( strIP, strFile, hPlayWnd );
        return;
    }

    if ( "中维" == strCapture ) {
        capType = CommonDataType::CaptureBMP;
        strFile.remove( ".JPG" );
        strFile += ".BMP";
    }

    HANDLE hChan = hChannelHandle[ nChannel ];
    if ( NULL != pMultimedia && INVALID_HANDLE != hChan ) {
        if ( CommonDataType::CaptureBMP == capType ) {
            pMultimedia->CaptureBMP( hChan, strFile );
        } else if ( CommonDataType::CaptureJPG == capType || CommonDataType::CaptureJPEG == capType ) {
            pMultimedia->CaptureJpeg( hChan, strFile );
        }
    }
}

void CMonitor::ControlDetection( int nChannel, bool bStart )
{
    pMultimedia->MotionDetection( hChannelHandle[ nChannel ], bStart );
}

void CMonitor::StartNewPlateRecog( )
{
    QPlateThread* pThread = pPlateThread;
    pThread->SetPlateWay( nUsedWay );
    pThread->SetPlateMultiThread( bMultiThread );
    if ( !bMultiThread ) {
        pThread->SetDongleOneWay( bDongleOneWay );
    }

    bool bWtProvider = pSystem->value( "CommonCfg/PlateProvider", "VZ" ).toString( ).toUpper( ) == "WT";

    for ( int nIndex = 0; nIndex < nUsedWay; nIndex++ ) {
        if ( !bPlateStart[ nIndex ] ) {
            continue;
        }

        if ( bNetworkCamera ) {
           pThread->PostPlateInitEvent( bPlateVideo ? ImageFormatYUV420COMPASS : ImageFormatBGR, nIndex, bWtProvider ); // Format / Channel
        } else {
            switch ( nCapture ) {
            case CMultimedia::HikSdk :
                pThread->PostPlateInitEvent( bPlateVideo ? ImageFormatYUV420COMPASS : ImageFormatBGR, nIndex, bWtProvider ); // HK
               break;

            case CMultimedia::TmSDK :
               pThread->PostPlateInitEvent( ImageFormatRGB, nIndex, bWtProvider ); //TM
               break;
            }
        }
    }

    connect( pThread, SIGNAL( UIPlateResult( QString, int, bool, bool, int, int, int, QString, QByteArray, QRect, QRect ) ),
             this, SLOT( HandleUIPlateResult( QString, int, bool, bool, int, int, int, QString, QByteArray, QRect, QRect ) ) );
}

void CMonitor::StartPlateRecog( )
{
    QString strKey = "CarLicence/AutoRecognize";
    bool bAuto = pSysSet->value( strKey, 0 ).toBool( );
    if ( !bAuto ) {
        return;
    }

    StartNewPlateRecog( );
    return;

    //StopPlateRecog( );

    //pVehicle = CVehicleLicense::CreateInstance( CVehicleLicense::WinToneSdk );
    //if ( NULL == pVehicle ) {
    //    return;
    //}

    QStringList lstParam;
    for ( int nIndex = 0; nIndex < nUsedWay; nIndex++ ) {
        if ( !bPlateStart[ nIndex ] ) {
            continue;
        }

        lstParam.clear( );

        if ( bNetworkCamera ) {
           lstParam << QString::number( bPlateVideo ? ImageFormatYUV420COMPASS : ImageFormatBGR ) << QString::number( nIndex ); // Format / Channel
        } else {
            switch ( nCapture ) {
            case CMultimedia::HikSdk :
               lstParam << QString::number( bPlateVideo ? ImageFormatYUV420COMPASS : ImageFormatBGR ) << QString::number( nIndex );
               break;

            case CMultimedia::TmSDK :
               lstParam << QString::number( ImageFormatRGB ) << QString::number( nIndex );
               break;
            }
        }

        //lstParam << QString::number( bPlateVideo ? ImageFormatYUV420COMPASS : ImageFormatBGR ) << QString::number( nIndex ); // Format / Channel
        //pVehicle->RecognizedImageFormat( lstParam );
        bool bRet;// = pVehicle->Initialize( nIndex );
        if (  false == bRet ) {
            CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                     "请检查车牌识别加密狗是否插好！", QMessageBox::Information, "background-image: url( );" );
            //CVehicleLicense::DestroyInstance( pVehicle );
            //pVehicle =  NULL;
            break;
        }
    }

    //if ( NULL != pVehicle ) {
     //   pVehicle->SetStop( false );
    //}
}

void CMonitor::StopPlateRecog( )
{
    //if ( NULL == pVehicle ) {
     //   return;
    //}

    //pVehicle->SetStop( true );

    for ( int nIndex = 0; nIndex < nUsedWay ; nIndex++ ) {
        if ( !bPlateStart[ nIndex ] ) {
            continue;
        }

        //pVehicle->Uninitialize( nIndex );
    }

    //pVehicle->DestroyInstance( pVehicle );
    //pVehicle = NULL;
}

void CMonitor::StopAvSdk( )
{
    if ( bNetworkCamera ) {
        return;
    }

    if ( NULL == pMultimedia ) {
        return;
    }
    for ( int nIndex = 0; nIndex < nEncode; nIndex++ ) {
        StopVideo( nIndex );
    }

    nEncode = 0;
    int nRet = 0;

    if ( bPlateVideo ) {
        for ( int nIndex = 0; nIndex < nUsedWay; nIndex++ ) { // Detection
            nRet = pMultimedia->SetupDetection( hChannelHandle[ nIndex ], NULL, nIndex );
            nRet = pMultimedia->MotionDetection( hChannelHandle[ nIndex ], false );
            nRet = pMultimedia->GetStreamData( hChannelHandle[ nIndex ], FALSE, NULL, nIndex );
        }

        nRet = pMultimedia->RegisterStreamCB( NULL, NULL );
    }

    nRet = pMultimedia->SystemShutdown( );
    CMultimedia::DestroyInstance( pMultimedia );
    pMultimedia = NULL;

    InitChannelHandle( );
}

void CMonitor::DisplayRemoteUI( )
{
    ipcVideoFrame->show( );
}

void CMonitor::ManualIPC( )
{
    if ( !bNetworkCamera ) {
        return;
    }

    StopIPC( );
    ipcVideoFrame->LocalIPCLogin( );
    StartIPC( );
}

void CMonitor::StartIPC( )
{
    if ( !bNetworkCamera ) {
        return;
    }

    IPCVideo( true );
}

void CMonitor::StopIPC( )
{
    if ( !bNetworkCamera ) {
        return;
    }

    IPCVideo( false );
    ipcVideoFrame->LocalIPCLogout( );
}

void CMonitor::IPCVideo( bool bPlayVideo )
{
    HWND hPlayWnd;
    QString strIP;

    for ( int nIndex = 0; nIndex < nUsedWay; nIndex++ ) {
        //PlayVideo( nIndex, lblVideoWnd[ nIndex ] );
        hPlayWnd = lblVideoWnd[ nIndex ]->winId( );
        strIP = lblVideoWnd[ nIndex ]->toolTip( );

        if ( strIP.isEmpty( ) || "0" == strIP || "127.0.0.1" == strIP ) {
            LoadVideoWndBg( nIndex );
            continue;
        }

        if ( bPlayVideo ) {
            ipcVideoFrame->LocalIPCStartVideo( strIP, hPlayWnd );
        } else {
            ipcVideoFrame->LocalIPCStopVideo( hPlayWnd );
        }
    }
}

void CMonitor::StartNewAvSdk( )
{
    strCapture = pSystem->value( "CommonCfg/CaptureCard", "HK" ).toString( ).toUpper( );
    nCapture = -1;
    //for ( int nStart = CMultimedia::HikSdk; nStart <= CMultimedia::TmSDK; ++nStart ) {
    if ( "HK" == strCapture ) {
        nCapture = CMultimedia::HikSdk;
        pNewAnalogVideo = QHkCaptureCardThread::GetInstance( );
    } else if ( "ZW" == strCapture ) {
        nCapture = CMultimedia::JvsSDK;
    } else if ( "TM" == strCapture ) {
        nCapture = CMultimedia::TmSDK;
        pNewAnalogVideo = QTmCaptureCardThread::GetInstance( );
    }

    pNewAnalogVideo->PostInitCaptureSDKEvent( winId( ) );

    for ( int nChannel = 0; nChannel < nUsedWay; nChannel++ ) {
        pNewAnalogVideo->PostOpenChannelEvent( nChannel );
        pNewAnalogVideo->PostPlayVideoEvent( nChannel, lblVideoWnd[ nChannel ]->winId( ) );

        if ( bPlateVideo ) {
            pNewAnalogVideo->PostStartCaptureEvent( nChannel );
            pNewAnalogVideo->PostStartMotionDetectEvent( nChannel );
            pNewAnalogVideo->PostStartSourceStreamEvent( nChannel, 0 == nChannel );
        }

        CMyLabel* pLbl = qobject_cast< CMyLabel* >( lblVideoWnd[ nChannel ] );
        pLbl->SetParams( nChannel, pNewAnalogVideo );
    }

    connect( pNewAnalogVideo, SIGNAL( DetectInfo( int, bool ) ),
             this, SLOT( HandleDetectInfo( int, bool ) ) );
}

void CMonitor::StartAvSdk( )
{
    if ( bNetworkCamera ) {
        return;
    }

    pSysSet->sync( );
    QString strKey = "VideoMode/AutoVideo";
    bool bAuto = pSysSet->value( strKey, 0 ).toBool( );
    if ( !bAuto ) {
        return;
    }

    /////////////////////////////
    StartNewAvSdk( ); // new video
    return;
    /////////////////////////////

    StopAvSdk( );

    strCapture = pSystem->value( "CommonCfg/CaptureCard", "HK" ).toString( ).toUpper( );
    nCapture = -1;
    //for ( int nStart = CMultimedia::HikSdk; nStart <= CMultimedia::TmSDK; ++nStart ) {
    if ( "HK" == strCapture ) {
        nCapture = CMultimedia::HikSdk;
    } else if ( "ZW" == strCapture ) {
        nCapture = CMultimedia::JvsSDK;
    } else if ( "TM" == strCapture ) {
        nCapture = CMultimedia::TmSDK;
    }

    if ( -1 != nCapture ) {
        pMultimedia = CMultimedia::CreateInstance( ( CMultimedia::AvSdk ) nCapture );
        nEncode = pMultimedia->SystemStartup( winId( ) );
        if ( 0 >= nEncode ) {
            CMultimedia::DestroyInstance( pMultimedia );
            qDebug( ) << "SystemStartup Failed!( DSPs )" << endl;
            pMultimedia = NULL;
            //return;
        } else {
            ;//break;
        }
    }
    //}

    int nRet = 0;
    if ( bPlateVideo ) { // Plate Video Mode
        bool bRet = false;
        switch ( nCapture ) {
        case CMultimedia::HikSdk :
            bRet = pMultimedia->RegisterStreamCB( ImageStreamCallback, this ); // GetVideoData
            break;

        case CMultimedia::TmSDK :
            bRet = pMultimedia->RegisterStreamCB( ( HK_STREAM_CB ) PrcCapSourceStream, this ); // GetVideoData
            break;
        }

    }
    //int nRet = pMultimedia->RegisterStreamCB( ( HK_STREAM_CB ) PrcCapSourceStream, this ); // GetVideoData

    for ( int nIndex = 0; nIndex < nUsedWay; nIndex++ ) {
        PlayVideo( nIndex, lblVideoWnd[ nIndex ] );
    }

    if ( bPlateVideo ) {
        for ( int nIndex = 0; nIndex < nUsedWay; nIndex++ ) { // Detection
            switch ( nCapture ) {
            case CMultimedia::HikSdk :
                nRet = pMultimedia->SetupDetection( hChannelHandle[ nIndex ], MotionDetection, nIndex, this );
                break;

            case CMultimedia::TmSDK :
                nRet = pMultimedia->SetupDetection( hChannelHandle[ nIndex ], ( HK_MOTION_CB ) MyPrcCbMotionDetect, nIndex, this );
                break;
            }

            nRet = pMultimedia->MotionDetection( hChannelHandle[ nIndex ], true );
            nRet = pMultimedia->TmEnablePicMessage( ( int ) hChannelHandle[ nIndex ], TRUE, PrcPicMessage );

            //nRet = pMultimedia->GetStreamData( hChannelHandle[ nIndex ], TRUE, imgData[ nIndex ], 3 );
        }
    }
}

void CMonitor::PlayVideo( int nIndex, QFrame* pVideo )
{
    if ( nIndex > nEncode || 0 > nIndex || NULL == pMultimedia ) {
        return;
    }

    if ( pVideo->toolTip( ) == "0" ) {
        LoadVideoWndBg( nIndex );
        return;
    }

    if ( INVALID_HANDLE !=  hChannelHandle[ nIndex ] ) {
        pMultimedia->StopVideo(  hChannelHandle[ nIndex ] );
        pMultimedia->CloseChannel( hChannelHandle[ nIndex ] );
        hChannelHandle[ nIndex ] = INVALID_HANDLE;
    }

    hChannelHandle[ nIndex ] = pMultimedia->OpenChannel( nIndex );
    if ( INVALID_HANDLE == hChannelHandle[ nIndex ] ) {
        qDebug( ) << "OpenChannel( " << nIndex << " ) Failed" << endl;
        return;
    }

    bool bAuto = pSysSet->value( "VideoMode/AutoVideo", false ).toBool( );
    if ( bAuto ) {
        CMyLabel* pLbl = qobject_cast< CMyLabel* >( lblVideoWnd[ nIndex ] );
        pLbl->SetParams( hChannelHandle[ nIndex ], pMultimedia );
    }

    QRect rect = pVideo->rect( );
#if false
    rect.setX( rect.x( ) + pVideo->lineWidth( ) );
    rect.setY( rect.y( ) + pVideo->lineWidth( ) );
    rect.setWidth( rect.width( ) - 2 * pVideo->lineWidth( ) );
    rect.setHeight( rect.height( ) - 2 * pVideo->lineWidth( ) );
#endif
    pMultimedia->PlayVideo( hChannelHandle[ nIndex ], pVideo->winId( ), rect, nIndex );
}

void CMonitor::StopVideo( int nIndex )
{
    if ( nIndex > nEncode || 0 > nIndex || NULL == pMultimedia ) {
        return;
    }

    if ( INVALID_HANDLE != hChannelHandle[ nIndex ] ) {
        pMultimedia->StopVideo( hChannelHandle[ nIndex ] );
        pMultimedia->CloseChannel( hChannelHandle[ nIndex ] );
        hChannelHandle[ nIndex ] = INVALID_HANDLE;
    }
}

void CMonitor::ControlSelf( )
{
    this->geometry();
}

void CMonitor::closeEvent( QCloseEvent *event )
{
    QTransparentFrame::DestroyFrame( );
    event->ignore( );
}

void CMonitor::CalculatePos( )
{
    QRect rectParent = pParent->geometry( );
    this->setGeometry( rectParent );
    QRect rectWnd = this->geometry( );

    QString strName = "widget";
    QWidget* pWg = findChild< QWidget* >( strName );
    pWg->setGeometry( rectWnd );

#if 0
    QRect rectWg = pWg->geometry( );

    pWg->setGeometry( ( rectWnd.width( ) - rectWg.width( ) -2 ) / 2,
                      ( rectWnd.height( )  - rectWg.height( ) -2 ) / 2,
                      rectWg.width( ), rectWg.height( ) );
#endif
}

void CMonitor::GetParkName( QString& strName, char cCan, int nIndex )
{
    //strName = "";
    //if ( 0 < lstPark.count( ) ) {
    //    strName = lstPark[ 0 ];
    //}

    strName = CCommonFunction::GetCanParkIndexNum( nIndex ).value( cCan );

    if( strName.isEmpty( ) ) {
        //qDebug( ) << "CMonitor::GetParkName() failed" << endl;
        QStringList lstLogs;
        QDateTime dt = QDateTime::currentDateTime( );
        QString strText;
        CCommonFunction::DateTime2String( dt, strText );
        lstLogs << "停车场" << "失败" << strText;
        CPmsLog::GetInstance( )->WriteLog( lstLogs );
    }
}

void CMonitor::GetAllParkSpaceLot( bool bChannel, bool bEnter )
{
    QStringList lstRows;
    if ( bChannel ) {
        //strParkName = "天府名居";
        if ( strParkName.isEmpty( ) ) {
            CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                     "请先选择停车场！", QMessageBox::Information );
            return;
        }
        //CLogicInterface::GetInterface( )->GetAllChannels( lstRows, bEneter ? "1" : "0" );
        CCommonFunction::GetAllChannels( lstRows, strParkName, bEnter );
    } else {
        //CLogicInterface::GetInterface( )->GetAllParks( lstRows );
        CCommonFunction::GetAllParks( lstRows );
    }

    CParkSpaceLotDialog dlg( this );
    dlg.InitDlg( bChannel, lstRows, bEnter, lstEnterCanOpen );
    dlg.exec( );

    if ( !bChannel ) {
        dlg.GetParkName( strParkName );
        //GetSpaceInfo( strParkName );
    }
}

void CMonitor::showEvent(QShowEvent *)
{
    GetDefaultParkInfo( );
}

void CMonitor::GetDefaultParkInfo(  )
{
    if ( !strParkName.isEmpty( ) ) {
        return;
    }

    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgDevice );
    strParkName = pSet->value( "Default/ParkName", "" ).toString( );
    //GetSpaceInfo( strParkName );
}

int CMonitor::GetInsideCard( QStringList &lstRows )
{
    int nInside = 0;
    for ( int nIndex = 0; nIndex < lstRows.count( ); nIndex++ ) {
        if ( "0" != lstRows[ ++nIndex ] ) {
            nInside++;
        }
    }
    return nInside;
}

void CMonitor::StartSpaceTimer( )
{
    //return;
    static QTimer timer;
    connect( &timer,SIGNAL( timeout( ) ), this, SLOT( SpaceInfo( ) ) );

    //timer.start( 5 * 60 * 1000 );
    timer.start( nRefreshParkspaceTime );
}

void CMonitor::PublishSpaceInfo( int nTotal, int nUsed)
{
    static QStringList lstData;
    static CScu scu;

    lstData.clear( );
    lstData << QString::number( nTotal ) << QString::number( nUsed );

    scu.InteractWithScu( lstData );
}

void CMonitor::SpaceInfo(  ) //最外围
{
    if ( strParkName.isEmpty( ) ) {
        return;
    }

    QString strInfo;

    bool bFull;
    QString strSql;
    QStringList lstData;
    int nFree = 0;
    int nUsed = 0;
    int nM = 0;
    int nS = 0;
    int nT = 0;

    CProcessData* pProcessor = CProcessData::GetProcessor( );
    if ( NULL == pProcessor ) {
        return;
    }

    QSettings* pSystemSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    pSystemSet->sync( );
    bool bSenseOpenGate = pSystemSet->value( "CommonCfg/SenseOpenGate", false ).toBool( );
    if ( bSenseOpenGate ) {
        //QString strName;
        //GetParkName( strName, 0, 0 );
        strSql = QString( "Select sum( usedSpace ) from parkinfo" );
        CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData );
        if ( 0 < lstData.count( ) ) {
            nUsed = lstData[ 0 ].toInt( );
            nFree = nTotalParkSpace - nUsed;
            if ( nFree < 0 ) {
                nFree = 0;
            }

            LoadDigital( 2, nFree, 'r' );
            LoadDigital( 3, nUsed, 'g' );

            goto SPACEFULL;
        }

        return;
    }

    strSql = "Call Calculate(@M, @s, @t)";
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData );

    strSql = "Select @M, @s, @t";
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData );

    if ( 0 >= lstData.count( ) ) {
        return;
    }

    nM = lstData[ 0 ].toInt( );
    nS = lstData[ 1 ].toInt( );
    nT = lstData[ 2 ].toInt( );

    nFree = nTotalParkSpace - nM - nS - nT;
    nUsed = nM + nS + nT;
    if ( 0 <= nFree ) {
        LoadDigital( 2, nFree, 'r' );
        LoadDigital( 3, nUsed, 'g' );
        LoadDigital( 4, nT, 'g' );
    }

    SPACEFULL:
    bFull = ( 0 >= nFree );
    //QString strInfo = bFull ? "车位已满！" : QString( "总车位：%1 滞留车位：%2 临时车位：%3 空闲车位：%4" ).arg(
    //                                                                                      QString::number( nTotalParkSpace ),  QString::number( nUsed ),
    //                                                                                      QString::number( nT ), QString::number( nFree ) );

    strInfo = bFull ? "车位已满！" : QString( "空闲车位：%1" ).arg( QString::number( nFree ) );
    pProcessor->ParkspaceFull( bFull, strInfo, 0 );

    PublishSpaceInfo( nTotalParkSpace, nUsed );
}

void CMonitor::GetImgBasePath(QString &strPath)
{
    CCommonFunction::GetPath( strPath, CommonDataType::PathUIImage );
}

void CMonitor::LoadCapturedImg( QString& strPath, int nChannel )
{
    //if ( ( VIDEO_USEDWAY / 2 != nUsedWay ) || ( 1 < nChannel ) ) {
    //    return;
    //}

    QPixmap bmp = QPixmap( strPath );

    // nChannel 0 1 2 3
    lblVideoWnd[ nChannel % 2 + 2 ]->setPixmap( bmp );
}

void CMonitor::GetInOutPixmap(QPixmap &bmpEnter, QPixmap &bmpLeave)
{
    const QPixmap* pMap = lblVideoWnd[ 2 ] ->pixmap( );
    if ( NULL != pMap ) {
        bmpEnter = *pMap;
    }

    pMap = lblVideoWnd[ 3 ]->pixmap( );
    if ( NULL != pMap ) {
        bmpLeave = *pMap;
    }
}

void CMonitor::LoadVideoWndBg( qint32 nIndex )
{
    QString strInfo = "";
    GetImgBasePath( strInfo );

    QString strTmp = strInfo + "logo";
    lblVideoWnd[ nIndex ]->setPixmap( pParent->GetPixmap( strTmp ) );
}

void CMonitor::LoadImg( )
{
    QString strInfo = "";
    GetImgBasePath( strInfo );

    //QString strTmp = strInfo + "logo";
    for ( int nIndex = nUsedWay; nIndex < 4; nIndex++ ) {
        LoadVideoWndBg( nIndex );
    }

    // Enter
    //strTmp = strButtonStyle.arg( strInfo, ui->btnVerifyIn0->objectName( ), "normal" );
    //ui->btnVerifyIn0->setStyleSheet( strTmp );
    SwitchImage( ui->btnVerifyIn0, false );

    //strTmp = strButtonStyle.arg( strInfo, ui->btnVerifyIn1->objectName( ), "normal" );
    //ui->btnVerifyIn1->setStyleSheet( strTmp );
    SwitchImage( ui->btnVerifyIn1, false );

    //strTmp = strButtonStyle.arg( strInfo, ui->btnVerifyOut0->objectName( ), "normal" );
    //ui->btnVerifyOut0->setStyleSheet( strTmp );
    SwitchImage( ui->btnVerifyOut0, false );

    //strTmp = strButtonStyle.arg( strInfo, ui->btnVerifyOut1->objectName( ), "normal" );
    //ui->btnVerifyOut1->setStyleSheet( strTmp );
    SwitchImage( ui->btnVerifyOut1, false );

    ////
    //strTmp = strButtonStyle.arg( strInfo, ui->btnCenterControlerStatus->objectName( ), "normal" );
    //ui->btnCenterControlerStatus->setStyleSheet( strTmp );
    SwitchImage( ui->btnCenterControlerStatus, false );

    //strTmp = strButtonStyle.arg( strInfo, ui->btnPublishLedInfo->objectName( ), "normal" );
    //ui->btnPublishLedInfo->setStyleSheet( strTmp );
    SwitchImage( ui->btnPublishLedInfo, false );

    //strTmp = strButtonStyle.arg( strInfo, ui->btnEnterPeripheralStatus->objectName( ), "normal" );
    //ui->btnEnterPeripheralStatus->setStyleSheet( strTmp );
    SwitchImage( ui->btnEnterPeripheralStatus, false );

    //strTmp = strButtonStyle.arg( strInfo, ui->btnSmsNotification->objectName( ), "normal" );
    //ui->btnSmsNotification->setStyleSheet( strTmp );
    SwitchImage( ui->btnSmsNotification, false );

    //strTmp = strButtonStyle.arg( strInfo, ui->btnLeavePeripheralStatus->objectName( ), "normal" );
    //ui->btnLeavePeripheralStatus->setStyleSheet( strTmp );
    SwitchImage( ui->btnLeavePeripheralStatus, false );

    //strTmp = strButtonStyle.arg( strInfo, ui->btnCandinate->objectName( ), "normal" );
    //ui->btnCandinate->setStyleSheet( strTmp );
    SwitchImage( ui->btnCandinate, false );

    LoadDigital( 1, nTotalParkSpace, 'g' );

    //for ( int nIndex = 1; nIndex <= 4; nIndex++ ) {
    //    LoadDigital( nIndex, 1234, ( 2 == nIndex ) ? 'r' : 'g' );
    //}
#if false
    strTmp = strInfo + "Shift";
    ui->toolBox->setItemIcon( 0, pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "MonthlyCard";
    ui->toolBox->setItemIcon( 1, pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "SaveCard";
    ui->toolBox->setItemIcon( 2, pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "TimeCard";
    ui->toolBox->setItemIcon( 3, pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "Inout";
    ui->toolBox->setItemIcon( 4, pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "Open";
    ui->btnGateOpen1->setIcon( pParent->GetPixmap( strTmp ) );
    ui->btnGateOpen2->setIcon( pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "Close";
    ui->btnGateClose1->setIcon( pParent->GetPixmap( strTmp ) );
    ui->btnGateClose2->setIcon( pParent->GetPixmap( strTmp ) );
    /////////
    strTmp = strInfo + "HistoryLog";
    ui->btnHistoryLog->setIcon( pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "HistoryClear";
    ui->btnHistoryClear->setIcon( pParent->GetPixmap( strTmp ) );

    //strTmp = strInfo + "Pass";
    //ui->btnPass->setIcon( pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "Comfirm";
    ui->btnBarcode->setIcon( pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "DispatcherOpen";
    ui->btnDispatcherOpen->setIcon( pParent->GetPixmap( strTmp ) );

    strTmp = strInfo + "DispatcherClose";
    ui->btnDispatcherClose->setIcon( pParent->GetPixmap( strTmp ) );

    SetGateImg( false, true );
    SetGateImg( false, false );
#endif
}

void CMonitor::resizeEvent( QResizeEvent* )
{
    //CalculatePos( );
    LoadImg( );
    StartAvSdk( );
    StartIPC( );
    StartPlateRecog( );
}

void CMonitor::SetGateImg(bool bOpen, bool bEnter)
{
#if false
    QString strInfo = "";
    GetImgBasePath( strInfo );

    QString strTmp = strInfo + ( bOpen ? "GateOpened" : "GateClosed" );
    if ( bEnter ) {
        ui->lblGateImg1->setPixmap( pParent->GetPixmap( strTmp ) );
    } else {
        ui->lblGateImg2->setPixmap( pParent->GetPixmap( strTmp ) );
    }
#endif
}

void CMonitor::on_btnDispatcherInfo_clicked()
{
    GetAllParkSpaceLot( true );
}

void CMonitor::on_btnGateChannel1_clicked()
{
    GetAllParkSpaceLot( true );
}

void CMonitor::on_btnGateChannel2_clicked()
{
    GetAllParkSpaceLot( true, false );
}

void CMonitor::ReadDefaultCan( QStringList& lstCan, bool bEnter, bool bOpen )
{
    lstCan.clear( );
    QString strKey = QString( "CommonCfg/%1DefaultCan%2" ).arg( bEnter ? "Enter" : "Leave",
                                                                bOpen ? "Open" : "Close" );
    QString strValue = pSystem->value( strKey, "" ).toString( );
    if ( !strValue.isEmpty( ) ) {
        lstCan = strValue.split( "," );
    }
}

void CMonitor::WriteDefaultCan( QStringList& lstCan, bool bEnter, bool bOpen )
{
    QString strKey = QString( "CommonCfg/%1DefaultCan%2" ).arg( bEnter ? "Enter" : "Leave",
                                                                bOpen ? "Open" : "Close" );
    QString strValue = lstCan.join( "," );
    pSystem->setValue( strKey, strValue );
}

bool CMonitor::ConfigDefaultCan( QStringList& lstCan, bool bEnter, bool bOpen )
{
    CParkSpaceLotDialog dlg;
    QString strSql = QString ( "Select distinct shebeiname, shebeiadr From roadconerinfo \
                               where video1ip ='%1' and shebeiadr % 2 %2= 0" ).arg(
                                       CCommonFunction::GetHostIP( ), bEnter ? "!" : "" );
    QStringList lstRows;
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
    dlg.InitDlg( true, lstRows, bEnter, lstCan );
    dlg.setWindowTitle( dlg.windowTitle( ) + ( bOpen ? QString( "——开闸" ) : QString( "——关闸" ) ) );
    if ( CParkSpaceLotDialog::Rejected == dlg.exec( ) ) {
        return false;
    }

    dlg.GetCanAddress( lstCan );

    if ( 0 != lstCan.count( ) ) {
        WriteDefaultCan( lstCan, bEnter, bOpen );
    } else {
        ReadDefaultCan( lstCan, bEnter, bOpen );
    }

    return true;
}

QStringList& CMonitor::GetDefaultGateCan( bool bEnter, bool bOpen )
{
    if ( bEnter ) {
        return ( bOpen ? lstEnterCanOpen : lstEnterCanClose );
    } else {
        return ( bOpen ? lstLeaveCanOpen : lstLeaveCanClose );
    }
}

void CMonitor::ControlGate( bool bOpen, bool bEnter, QObject* sender )
{
    //QPushButton* pSender = qobject_cast< QPushButton* >( sender );
    //pSender->setEnabled( false );
    //bool bEnter = ( 0 != cCan % 2 ); // 1 2 3 4
    SetGateImg( bOpen, bEnter );

    int nCount = 0;
    CProcessData* pProcessor = CProcessData::GetProcessor( pParent->GetSerialPort( ), pParent );
    QString strWhere;
    QString strType = "手动开关闸";
    QString strText;
    QString strContent = QString( "%1口 %2闸" ).arg( bEnter ? "入" : "出", bOpen ? "开" : "关" );
    QDateTime dtDateTime = QDateTime::currentDateTime( );
    CCommonFunction::DateTime2String( dtDateTime, strText );

    QStringList& lstCan = GetDefaultGateCan( bEnter, bOpen );
    nCount = lstCan.count( );
    if ( 0 == nCount ) {
        ConfigDefaultCan( lstCan, bEnter, bOpen );
        nCount = lstCan.count( );
        if ( 0 == nCount ) {
            CCommonFunction::MsgBox( NULL, "提示", strContent + " 没配置CAN地址。", QMessageBox::Information );
            return;
        }
    }

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        char cCan = ( char ) lstCan.at( nIndex ).toShort( );
        pProcessor->ControlGate( bOpen, cCan );

        if ( 33 > cCan ) {
            pParent->WriteLog( strType, strContent, CommonDataType::ManualGateLog, dtDateTime, cCan );
        }

        strWhere = QString( " where infooperator = '%1' and infokind = '%2' and infotext = '%3' and infotime = '%4'" ).arg(
                    pParent->GetUserName( ), strType, strContent, strText );

        pProcessor->CaptureManualGateImage( cCan, strWhere );
    }

    //ENABLEBUTTON:
    //pSender->setEnabled( true );
}

void CMonitor::GateOpen1()
{
    ControlGate( true, true, sender( ) );
}

void CMonitor::GateClose1()
{
    ControlGate( false, true, sender( ) );
}

void CMonitor::GateOpen2()
{
    ControlGate( true, false, sender( ) );
}

void CMonitor::GateClose2()
{
    ControlGate( false, false, sender( ) );
}

void CMonitor::on_btnGate3Channel_clicked()
{
    GetAllParkSpaceLot( false );
}

void CMonitor::ControlChargeInfo(QStringList &strInfo)
{
#if false
    if ( 5 != strInfo.count( ) ) {
        return;
    }

    ui->lblInTime->setText( strInfo[ 0 ] );
    ui->lblOutTime->setText( strInfo[ 1 ] );
    ui->lblRetentionTime->setText( strInfo[ 2 ] );
    ui->lcdAmount->display( strInfo[ 3 ] );
    //ui->btnPass->setEnabled( 0 == strInfo[ 4 ].compare( "1" ) ); // [ 0 disabled, 1 enabled ]
#endif
}

void CMonitor::on_btnDispatcherOpen_clicked()
{
    return;
    QString strFile;
    GetFileName( strFile, "bmp" );

    pMultimedia->CaptureBMP( hChannelHandle[ 0 ], strFile );

    GetFileName( strFile, "jpg" );
    pMultimedia->CaptureJpeg( hChannelHandle[ 0 ], strFile );
    ///////////////////////////
    //AA 0E 00 44 00 3e 1A 1B C7 EB CB A2 BF A8 02 1C 1D 3c 55
    //char cData[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x42, 0x3f, 0x01, 0x00, 0x55};
    char cData[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x42, 0x3e, 0x01, 0x00, 0x55}; //UpBallotSenseVihcleEnter
    //char cData[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x43, 0x3E, 0x01, 0x00, 0x55 }; Send card
    //char cData[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x43, 0x3E, 0x00, 0x00, 0x55 };

    //char cData[ ] = { 0xAA, 0x05, 0x00, 0x50, 0x01, 0x3e, 0x00, 0x00, 0x00, 0x55};
    //char cData[ ] = { 0xAA, 0x05, 0x00, 0x50, 0x01, 0x3e, 0x00, 0x00, 0x00, 0x55};
    QByteArray byData( cData, sizeof ( cData) );
    CProcessData* pProcessor = CProcessData::GetProcessor( pParent->GetSerialPort( ), pParent );
    if ( !pProcessor->IsOpen( ) ) {
        pProcessor->OpenPort( );
    }

    pProcessor->ParseData( byData );
}

void CMonitor::on_btnBarcode_clicked()
{

}

void CMonitor::on_btnDispatcherClose_clicked()
{

}

void CMonitor::ManualRecogonization( int nChannel )
{
    DisplayPlate( nChannel );
}

void CMonitor::ManualRecogonization( int nChannel, QString strPlate )
{
    QByteArray byData = CCommonFunction::GetTextCodec( )->fromUnicode( strPlate );
    const char* pData = byData.data( );
    strcpy( structPlates[ nChannel ].license, pData );
    DisplayPlate( nChannel );
}

void CMonitor::PlateCheck( QString strChar, int nChannel, int nIndex )
{
    if ( 0 > nChannel || 0 > nIndex || strChar.isNull( ) || strChar.isEmpty( ) ) {
        return;
    }

    if ( 1 == nIndex ) {
        nIndex = 0;
    }

    char* pLicense = &structPlates[ nChannel ].license[ nIndex ];
    QByteArray byData = strChar.toUtf8( );
    int nBytes = byData.count( );

    if ( NULL == pLicense || 15 < nBytes ) {
        return;
    }

    for ( nIndex = 0; nIndex < nBytes; nIndex++ ) {
        *pLicense = byData.at( nIndex );
        pLicense++;
    }
}

void CMonitor::ClearPlate( int nPlateChannel )
{
    //return;
    QString strPlate = "        ";
    CCommonFunction::DisplayPlateChar( lblLicense[ nPlateChannel ], nPlateChannel, strPlate );
    strPlates[ nPlateChannel ].clear( );
}

void CMonitor::onLinkActivated(QString link)
{
    static CPrintMonthlyReport check( NULL );
    static bool bConnect = false;
    if ( !bConnect ) {
        QString strStyle = QString( "background-image:url(%1NewIcon/VerifyPlate.JPG)" ).arg( strImagePath );
        check.setStyleSheet( strStyle );
        bConnect = true;
        connect( &check, SIGNAL( SendValue( QString, int, int ) ), this, SLOT( PlateCheck( QString, int, int ) ) );
        connect( &check, SIGNAL( ManualRecogonization( int ) ), this, SLOT( ManualRecogonization( int ) ) );
        connect( &check, SIGNAL( ClearMonitorPlate( int ) ), this, SLOT( ClearPlate( int ) ) );
    }

    QLabel* pLbl = qobject_cast< QLabel* >( sender( ) );
    QString strNumber = pLbl->text( ).right( 2 );
    int nChannel = strNumber.left( 1 ).toInt( );
    int nIndex = strNumber.right( 1 ).toInt( );
    check.SetChannelIndex( nChannel, nIndex );
    check.InitResBtn( link );

    check.show( );
}

void CMonitor::on_btnPass_clicked()
{
    //this->ControlGate( true, false );
    //CCommonFunction::GetSyncPass( ).unlock( );
}

void CMonitor::onBtnVerifyInClicked()
{
    int nChannel = sender( )->objectName( ).right( 1 ).toInt( );
    if ( 1 == nChannel ) {
        nChannel += 1;
    }

    VerifyClecked( nChannel );
}

void CMonitor::onBtnVerifyOutClicked()
{
    int nChannel = sender( )->objectName( ).right( 1 ).toInt( );
    if ( 0 == nChannel ) {
        nChannel += 1;
    } else {
        nChannel += 2;
    }

    VerifyClecked( nChannel );
}

void CMonitor::VerifyClecked( int nChannel )
{
    QString strPlate = QString( structPlates[ nChannel ].license );
    static CPrintMonthlyReport check( NULL, this );
    static bool bConnect = false;

    if ( !bConnect ) {
        bConnect = true;
        QString strStyle = QString( "background-image:url(%1NewIcon/VerifyPlate.JPG)" ).arg( strImagePath );
        check.setStyleSheet( strStyle );
        connect( &check, SIGNAL( ManualRecogonization( int, QString ) ), this, SLOT( ManualRecogonization( int, QString ) ) );
        connect( &check, SIGNAL( ClearMonitorPlate( int ) ), this, SLOT( ClearPlate( int ) ) );
    }

    int nIndex = 0;
    check.SetChannelIndex( nChannel, nIndex );
    check.InitResBtn( strPlate );
    check.show( );
}

void CMonitor::on_tabRecord_cellDoubleClicked(int row, int column)
{
#if false
    M:select a.cardno, a.cardselfno, a.endtime, b.username, b.userpic, b.Comments, c.carcp, c.carmodel,
    c.carpic, d.inshebeiname, d.intime, d.outshebeiname, d.outtime, d.cardkind
    from parkadmin.monthcard a
    inner join parkadmin.userinfo b on a.cardno = '17338' and a.cardno = b.cardindex
    inner join parkadmin.carinfo c on a.cardno = c.cardindex
    inner join parkadmin.stoprd d on a.cardno = d.cardno and ( inshebeiname = '南门入口' or outshebeiname = '南门入口')
    and ( intime = '2011-08-11 07:26:49' or outtime = '2011-08-11 07:26:49' );
    0,1,2 M /S /T Card

    S:select a.cardno, a.cardselfno, a.cardfee, b.username, b.userpic, b.Comments, c.carcp, c.carmodel,
    T:select a.cardno, a.cardselfno, b.username, b.userpic, b.Comments, c.carcp, c.carmodel,
      pWG->item( row, 1 )->text( );//Plate
      pWG->item( row, 1 )->text( );//Time
      pWG->item( row, 2 )->text( );//卡类型
      pWG->item( row, 3 )->text( );//Channel
      pWG->item( row, 4 )->text( );//CardNo
      pWG->item( row, 5 )->text( );//Eneter?
      pWG->item( row, 6 )->text( );//CardType
      pWG->item( row, 7 )->text( );// Date
#endif
    try {
        CPictureContrastDlg dlg( this );
        SetDlgBackground( dlg );

        QStringList  lstData;
        QTableWidget* pWG = qobject_cast< QTableWidget* >( sender( ) );
        QString strField[ ] = { "a.endtime, b.username, a.cardcomment, ", "a.cardfee, b.username, a.cardcomment,d.feefactnum,", "d.feefactnum," };
        QString strTable = "";
        bool bEnter = ( pWG->item( row, 5 )->text( ) == "1" );
        int nType = pWG->item( row, 6 )->text( ).toInt( ); // 0M 1S 2T 10F
        QString strDateTime = pWG->item( row, 7 )->text( ) + " " + pWG->item( row, 1 )->text( );
        CCommonFunction::GetTableName( ( CommonDataType::CardType ) nType, strTable );

        QString strChannelField = bEnter ? "inshebeiname" : "outshebeiname";
        QString strTimeField = bEnter ? "intime" : "outtime";
        QString strChannel = pWG->item( row, 3 )->text( );
        QString strCardNo = pWG->item( row, 4 )->text( );
        QString strUser = ( 2 != nType ) ? QString( "inner join userinfo b on a.cardno = '%1' and a.cardno = b.cardindex" ).arg( strCardNo ) : "";


        QString strSql;
        bool bFreeCard = ( 10 == nType || 11 == nType  );
        QString strWhere = QString( " Where stoprdid = ( select stoprdid from stoprd Where cardno = '%1' and %2 = '%3' and %4 = '%5' )" ).arg(
                                    strCardNo, strChannelField, strChannel, strTimeField, strDateTime );

        CLogicInterface logInterf;
        CMySqlDatabase& mySql = logInterf.GetMysqlDb( );
        QStringList lstParams;
        CCommonFunction::ConnectMySql( lstParams );
        lstParams[ 0 ] = pWG->item( row, 10 )->text( ); //IP
        bool bRet = mySql.DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );
        if ( !bRet ) {
            return;
        }

        if ( 2 == nType ) {
            strSql  = QString( "select a.cardno, a.cardselfno, %1 '%2', '', \
                      d.inshebeiname, d.intime, d.outshebeiname, d.outtime, d.cardkind, d.carcp, d.carcpout, d.feekind \
                      from %3 a \
                      %4 \
                      inner join stoprd d on a.cardno = d.cardno and %5 = '%6' and %7 = '%8'" ).arg(
                      strField[ nType ], ui->tabRecord->item( row, 0 )->text( ), strTable, strUser,
                      strChannelField, strChannel,
                      strTimeField, strDateTime );
        } else if ( bFreeCard ) {
            strSql = "Select cardkind from stoprd " + strWhere;
            logInterf.ExecuteSql( strSql, lstData );
            if ( lstData.length( ) > 0 && lstData.at( 0 ) == "月租卡" ) {
                strTable = "monthcard";
                int nIndex =  strCardNo.indexOf( "(" );
                strUser = QString( "inner join userinfo b on a.cardno = '%1' and a.cardno = b.cardindex" ).arg(
                            nIndex > 0 ? strCardNo.mid( 0, nIndex ) : strCardNo );
                nType = 0;
                strSql  = QString( "select a.cardno, a.cardselfno, %1 c.carcp, c.carmodel, \
                d.inshebeiname, d.intime, d.outshebeiname, d.outtime, d.cardkind \
                from %2 a \
                %3 \
                inner join carinfo c on a.cardno = c.cardindex \
                inner join stoprd d on d.cardno = '%4' and %5 = '%6' and %7 = '%8'" ).arg(
                strField[ nType ], strTable, strUser, strCardNo,
                strChannelField, strChannel,
                strTimeField, strDateTime );
            } else {
                strSql = QString( "Select cardno, cardselfno, feefactnum, '%1', '', inshebeiname, intime,outshebeiname,\
                                  outtime,cardkind, carcp, carcpout, feekind from stoprd " ).arg( ui->tabRecord->item( row, 0 )->text( ) );
                strSql += strWhere;
                nType = 2;
            }
        } else if ( 0 == nType || 1 == nType ) {
            strSql  = QString( "select a.cardno, a.cardselfno, %1 c.carcp, c.carmodel, \
                          d.inshebeiname, d.intime, d.outshebeiname, d.outtime, d.cardkind \
                          from %2 a \
                          %3 \
                          inner join carinfo c on a.cardno = c.cardindex \
                          inner join stoprd d on a.cardno = d.cardno and %4 = '%5' and %6 = '%7'" ).arg(
                          strField[ nType ], strTable, strUser,
                          strChannelField, strChannel,
                          strTimeField, strDateTime );
        }
        qDebug( ) << strSql << endl;

        //   CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData, CCommonFunction::GetHistoryDb( ) );

        logInterf.ExecuteSql( strSql, lstData );

        if ( 0 == lstData.count( ) ) { // InOut Record empty
            QStringList lstLog;
            QDateTime dt = QDateTime::currentDateTime( );
            QString strDt;
            CCommonFunction::DateTime2String( dt, strDt );
            strSql.remove( "'" );
            lstLog << "查看进出记录" << strSql << strDt;
            CPmsLog::GetInstance( )->WriteLog( lstLog );
        }

        dlg.SetDbInterf( &logInterf );
        dlg.InitDlg( lstData, strWhere, strCardNo, nType, bEnter );
        mySql.DbDisconnect( );
        dlg.exec( );
      } catch ( ... ) {
          ;
      }
}

void CMonitor::on_pushButton_clicked()
{
    QFile file( qApp->applicationDirPath( ) + "/logo.jpg" );
    bool bRet = file.open( QIODevice::ReadOnly );
    qDebug( ) << file.errorString( ) << " : " << file.fileName( ) << endl;
    if ( !bRet ) {
        return;
    }
    QByteArray byData = file.readAll( );
    file.close( );

    QStringList lstValue;
    QStringList lstCardno;
    QDateTime dt;
    QString strDt;
    QString strCardno;

    //QString strSql = "insert into stoprd ( cardno, inshebeiname, outshebeiname, intime, outtime, feetime,  feeoperator, cardkind ) values %1";
    //QString strValue = "( %1, '南门入口', '南门出口', '%2', '%3', '%4', '系统管理员', '月租卡' )";
    QString strSql = "insert into stoprd ( cardno, inshebeiname, intime, cardkind ) values %1";
    QString strValue = "( %1, '南门入口', '%2',  '计时卡' )";
    QDate date = QDate::currentDate( );

    for ( int nIndex = 1; nIndex <= ui->spinBox->value( ) * 10000; nIndex++ ) {
        dt = QDateTime( date, QTime::currentTime( ) );
        CCommonFunction::DateTime2String( dt, strDt );
        strCardno = QString::number( dt.toMSecsSinceEpoch( ) );

        //lstValue << strValue.arg( strCardno, strDt, strDt, strDt );
        lstValue << strValue.arg( strCardno, strDt );
        lstCardno << strCardno;

        if ( 0 == nIndex % 3000 ) {
            QString strTmp = strSql.arg( lstValue.join( "," ) );
            CProcessData::GetProcessor( )->SendDbWriteMessage( CDbEvent::SQLExternal, strTmp, false, true, false );
            lstValue.clear( );

            Sleep( 10 );
            foreach ( const QString str, lstCardno ) {
                strTmp =  QString( " where cardno = '%1'" ).arg( str );
                CProcessData::GetProcessor( )->SendDbWriteMessage( CDbEvent::ImgExternal, strTmp, false, false, false,
                                                                   CommonDataType::BlobVehicleIn1, byData );

                //CProcessData::GetProcessor( )->SendDbWriteMessage( CDbEvent::ImgExternal, strTmp, false, false,
                //                                                   CommonDataType::BlobVehicleOut1, byData );
            }

            return;
            lstCardno.clear( );
            Sleep( 60000 );
        }

        Sleep( 20 );

        if ( 0 == nIndex % 20000 ) {
            date = date.addDays( 1 );
            Sleep( 60000 * 3 );
        }
    }

}

#include "../Network/http.h"
CHttp http;

void CMonitor::on_pushButton_2_clicked()
{
    QString strUrl = "http://localhost:1692/ASPWebsite/WebService.asmx/HelloWorld";
    QByteArray byData = strUrl.toAscii( );

    static QFile file( "d:/vid1.avi" );//( "d://1.jpg" );
    bool bRet = file.open( QIODevice::ReadOnly );
    http.HttpPost( strUrl, &file );
}
