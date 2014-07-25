 #include "SerialPort/processdata.h"
#include <QDebug>
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"
#include <QThread>
#include <QTextCodec>
#include <Common/CommonType.h>
#include "Network/parkintranet.h"
#include "PmsLog/pmslog.h"
#include "writethread.h"
#include "PlateDilivery/cplatediliverythread.h"

#include <QtGui/QApplication>
#include "readthread.h"

CWriteThread g_serialThread;
CDbWriteThread g_dbThread;
CReadThread* g_pReadThread;

CProcessData* CProcessData::pCmdProcessor = NULL;
QUploadDataThread* CProcessData::pUploadDataThread = NULL;

bool CProcessData::NetProbe( )
{
    QString strIP = pSettings->value( "Database/Host", "127.0.0.1" ).toString( );
    bool bRet = ping.IcmpPing( strIP );

    if ( !bRet ) {
        CCommonFunction::MsgBox( NULL, "网络探测", QString( "网络不通。\r\n不能链接数据库【%1】。若是本机数据库，请把数据库IP配置为【127.0.0.1】。" ).arg( strIP ), QMessageBox::Critical );
    }

    return bRet;
}

void CProcessData::HandleReadThreadData( QByteArray byData )
{
    ParseData( byData );
}

CProcessData::CProcessData( CWinSerialPort* pWinPort, MainWindow* pWindow, QObject *parent ) :
    QObject(parent)
{
    g_pReadThread = CReadThread::CreateInstance( pWinPort );
    connect( g_pReadThread, SIGNAL( SerialData( QByteArray ) ),
             this, SLOT( HandleReadThreadData( QByteArray ) ) );

    g_serialThread.SetSerialPort( pWinPort );
    g_serialThread.start( );
    g_serialThread.moveToThread( &g_serialThread );

    GateIfHaveVehicle[ 0 ] = false;
    GateIfHaveVehicle[ 1 ] = false;

    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    bStartupPlateDilivery = pSettings->value( "PlateDilivery/StartupDilivery", false ).toBool( );
    bNocardwork = pSettings->value( "CommonCfg/NoCardWork", false ).toBool( );
    bNocardworkUnknown = pSettings->value( "CommonCfg/NoCardWorkUnknown", false ).toBool( );
    bBlacklistCheck = pSettings->value( "Blacklist/Start", false ).toBool( );
    bUploadData = pSettings->value( "UploadData/Upload", false ).toBool( );

    if ( !GetDirectDb( ) ) {
        g_dbThread.start( );
        g_dbThread.moveToThread( &g_dbThread );
    }

    CreateBufferTable( );

    pSerialPort = pWinPort;
    pMainWindow = pWindow;
    //cardType[ 0 ] = CardNone;
    //cardType[ 1 ] = CardNone;
    strCurrentPlate[ 0 ] = "";
    strCurrentPlate[ 1 ] = "";
    strCurrentPlate[ 2 ] = "";
    strCurrentPlate[ 3 ] = "";
    bPlateRecognize[ 0 ] = false;
    bPlateRecognize[ 1 ] = false;
    bPlateRecognize[ 2 ] = false;
    bPlateRecognize[ 3 ] = false;
    bParkspaceFull = false;

    pFeeDlg = new CPictureContrastDlg( NULL );
    connect( pFeeDlg, SIGNAL(SendTimeCardInfo(QByteArray&,QByteArray&,int,int,int,bool)),
             this, SLOT(SendTimeCardInfo(QByteArray&,QByteArray&,int,int,int,bool)));

    QString strKeyName = "CommonCfg/Name%1";
    QString strKey = "CommonCfg/Video%1";
    QString strCaptureKey = "CommonCfg/CatpureOpportunity%1" ;

    for ( int nIndex = 1; nIndex <= 4; nIndex++ ) {
        cCanVideo[ nIndex - 1 ] = ( char ) pSettings->value( strKey.arg( nIndex ), nIndex ).toInt( );
        strVideoChannelName[ nIndex - 1 ] = pSettings->value( strKeyName.arg( nIndex ), nIndex ).toString( );

        bCardCapture[ nIndex - 1 ] = pSettings->value( strCaptureKey.arg( nIndex ), 0 ).toInt( );
    }

    bTest = pSettings->value( "CommonCfg/Test", false ).toBool( );
    bSingleChannel = pSettings->value( "CommonCfg/SingleChannel", false ).toBool( );

    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgPlate );
    nSameInterval[ 0 ] = pSet->value( "WintonePlate/WintonePlate0/PlateInterval", 30 ).toInt( );
    nSameInterval[ 1 ] = pSet->value( "WintonePlate/WintonePlate1/PlateInterval", 30 ).toInt( );

    bPlateClear[ 0 ][ 0 ] = pSet->value( "WintonePlate/WintonePlate0/BallotClear", 1 ).toInt( );
    bPlateClear[ 0 ][ 1 ] = pSet->value( "WintonePlate/WintonePlate0/GateClear", 0 ).toInt( );
    bPlateClear[ 1 ][ 0 ] = pSet->value( "WintonePlate/WintonePlate1/BallotClear", 1 ).toInt( );
    bPlateClear[ 1 ][ 1 ] = pSet->value( "WintonePlate/WintonePlate1/GateClear", 0 ).toInt( );
    bPlateClear[ 2 ][ 0 ] = pSet->value( "WintonePlate/WintonePlate2/BallotClear", 1 ).toInt( );
    bPlateClear[ 2 ][ 1 ] = pSet->value( "WintonePlate/WintonePlate2/GateClear", 0 ).toInt( );
    bPlateClear[ 3 ][ 0 ] = pSet->value( "WintonePlate/WintonePlate3/BallotClear", 1 ).toInt( );
    bPlateClear[ 3 ][ 1 ] = pSet->value( "WintonePlate/WintonePlate3/GateClear", 0 ).toInt( );

    //nDiffInterval = nSameInterval;
    pSet = CCommonFunction::GetSettings( CommonDataType::CfgSysSet );
    nMonthWakeup = pSet->value( "CommonSet/MonthlyWakeup").toInt( );
    bCardConfirm = pSet->value( "CommonSet/CardConfirm", false ).toBool( );
    bHavePlateRecog = pSet->value( "CarLicence/AutoRecognize", false ).toBool( );
    cPrecision = ( char ) pSet->value( "CarLicence/Precision", 0 ).toInt( );

    bSendOnlyOnce = false;

    pConfirm[ 0 ] = new CDlgInconformity( NULL );
    pConfirm[ 1 ] = new CDlgInconformity( NULL );
    pConfirm[ 2 ] = new CDlgInconformity( NULL );
    pConfirm[ 3 ] = new CDlgInconformity( NULL );

    QString strPath;
    CCommonFunction::GetPath( strPath, CommonDataType::PathUIImage );
    strPath += "NewIcon/Inconformity.JPG";
    pConfirm[ 0 ]->setStatusTip( strPath );
    pConfirm[ 1 ]->setStatusTip( strPath );

    connect( pConfirm[ 0 ], SIGNAL( Pass( QString, char, QString ) ), this, SLOT( PlateCardComfirmPass( QString, char, QString ) ) );
    connect( pConfirm[ 1 ], SIGNAL( Pass( QString, char, QString ) ), this, SLOT( PlateCardComfirmPass( QString, char, QString ) ) );

    ReadCanForRestart( true );

    if ( bStartupPlateDilivery ) {
        CPlateDiliveryThread* pDilivery = CPlateDiliveryThread::GetSingleton( );
        connect( this, SIGNAL( PlateDelivery( int, QStringList, QString ) ), pDilivery, SLOT( HandlePlateDilivery( int, QStringList, QString ) ) );
        connect( pDilivery, SIGNAL( WeighingRequest( QStringList ) ), this, SLOT( HandleWeighing( QStringList ) ) );
        connect( pDilivery, SIGNAL( Capture( quint8 ) ), this, SLOT( HandleCapture( quint8 ) ) );
        connect( pDilivery, SIGNAL( SendFileCount( quint32 ) ), this, SLOT( HandleSendFileCount( quint32 ) ) );
    }
}

void CProcessData::HandleSendFileCount( quint32 nCount )
{
    pMainWindow->SetFileCount( nCount );
}

void CProcessData::CreateBufferTable( )
{
    QString strSql = QString( "Call StartTimer( %1 )" ).arg( QString::number( GetTimeCardBuffer( ) ) );
    CLogicInterface::GetInterface( )->ExecuteSql( strSql );
}

bool CProcessData::GetDirectDb( )
{
    return pSettings->value( "CommonCfg/DirectDb", true ).toBool( );
}

bool CProcessData::GetTimeCardBuffer( )
{
    return pSettings->value( "CommonCfg/TimeCardBuffer", false ).toBool( );
}

void CProcessData::SendDbWriteMessage( CDbEvent::UserEvent event, QString &strSql, bool bHistory, bool bTimerCard, bool bSelect )
{
    CDbEvent* pEvent = new CDbEvent( ( CDbEvent::Type ) event );
    pEvent->SetParameter( strSql, bHistory, bTimerCard, bSelect );
    QApplication::postEvent( &g_dbThread, pEvent );
}

void CProcessData::SendDbWriteMessage( CDbEvent::UserEvent event, QString &strSql, bool bHistory, bool bTimerCard, bool bSelect, CommonDataType::BlobType blob, QByteArray &byData )
{
    CDbEvent* pEvent = new CDbEvent( ( CDbEvent::Type ) event );
    pEvent->SetParameter( strSql, bHistory, bTimerCard, bSelect, blob, byData );
    QApplication::postEvent( &g_dbThread, pEvent );
}

void CProcessData::SendDbWriteMessage( CDbEvent::UserEvent event, QString &strCardno, bool bEnter, int nType, bool bGarage, QByteArray &byData )
{
    CDbEvent* pEvent = new CDbEvent( ( CDbEvent::Type ) event );
    pEvent->SetParameter( bEnter, nType, bGarage, strCardno, byData );
    QApplication::postEvent( &g_dbThread, pEvent );
}

short CProcessData::GetCmdDataSize( QByteArray &byCmd )
{
    short nSize = 0;

    if ( 8 > byCmd.size( ) ) {
        return nSize;
    }

    nSize = ( short ) byCmd[ 1 ] + ( byCmd[ 2 ] << 8 ); // -1

    return nSize;
}

void CProcessData::SetCmdDataSize( short nSize, QByteArray& byCmd )
{
    char* pSize = ( char* ) &nSize;
    byCmd[ 1 ] = pSize[ 0 ];
    byCmd[ 2 ] = pSize[ 1 ];
}

void CProcessData::SendMultiCmd( QList< QByteArray* > lstCmd, char cCan )
{
    const char cHeader[ ] = { 0xAA, 0x00, 0x00, 0x4D, 0x00, cCan };
    QByteArray byCmd( cHeader );
    char cCmdCount = 0;
    short nTotalSize = 0;
    short nCmdLen = 0;

    foreach( QByteArray* pCmd, lstCmd ) {
        nCmdLen = GetCmdDataSize( *pCmd );
        SetCmdDataSize( --nCmdLen,  *pCmd ); // Sub Can Address
        nTotalSize += nCmdLen;
        cCmdCount++;
        pCmd->remove( 5, 1 ); // Can
        byCmd.append( pCmd->mid( 1,  pCmd->size( ) - 3 ) );
    }

    nTotalSize += 3;
    SetCmdDataSize( nTotalSize,  byCmd );
    byCmd[ 4 ] = cCmdCount;
    const char cTailer[ ] = { 0x00, 0x55 };
    byCmd.append( cTailer );

    WriteData( byCmd );
}

void CProcessData::PublishLedInfo( QString &strInfo, char cCan, bool bIndependent )
{
    QByteArray byData;
    QByteArray vData;
    char cmdInfo[ ] = { 0xAA, 0x0B, 0x00, 0x44, 0x00, 0x00 };
    QTextCodec* pCodec = CCommonFunction::GetTextCodec( );

    vData.append( 0x1E );
    vData.append( 0x1F );
    vData.append( pCodec->fromUnicode( strInfo ) );
    byData.append( cmdInfo, sizeof ( cmdInfo ) );
    vData.append( bIndependent ? 0x02 : 0x01 );
    vData.append( 0x1C );
    vData.append( 0x1D );

    byData[ 5 ] = cCan;
    portCmd.ParseDownCmd( byData, CPortCmd::DownLED, vData );

    if ( bIndependent ) {
        byData[ 4 ] = 0x01;
    }

    WriteData( byData );
}

void CProcessData::BroadcastLedInfo( QStringList &lstData )
{
    QString strLocalIP = CCommonFunction::GetHostIP( );
    if ( !lstData.contains( strLocalIP ) ) {
        return;
    }

    int nFirst = lstData.indexOf( strLocalIP );
    int nCount = lstData.count( );

    while ( ( nFirst < nCount ) && ( strLocalIP == lstData[ nFirst++ ] ) ) {
        QString& strText = lstData[ nFirst++ ];
        QString& strCan = lstData[ nFirst++ ];
        char cCan = ( char ) strCan.toShort( );
        PublishLedInfo( strText, cCan );
    }
}

void CProcessData::ProcessUserRequest( CommonDataType::UserRequest request, char cCan, QStringList& lstData )
{
    QByteArray byData;
    QByteArray vData;
    int nMin = 0;
    int nHour = 0;
    int nAmount = 0;
    bool bEnter = false;
    int nMinor = 0;
    CPortCmd::PortDownCmd cmd = CPortCmd::DownFailed;

    switch ( request ) {
    case CommonDataType::UserCenterControler : // Test
        if ( 3 > lstData.count( ) ) {
            return;
        }

        nHour = lstData[ 0 ].toInt( );
        nMin = lstData[ 1 ].toInt( );
        nAmount = lstData[ 2 ].toInt( );

        byData[ 5 ] = cCan;
        CCDisplayInfo( byData, vData, nMin, nHour, nAmount, false );
        return;
        break;

    case CommonDataType::UserPheripheral :
        if ( 2 > lstData.count( ) ) {
            return;
        }

        bEnter = ( "1" == lstData[ 0 ] );
        byData[ 5 ] = cCan;
        nMinor = lstData[ 1 ].toInt( );

        switch ( nMinor ) {
        case 1:
            cmd = CPortCmd::DownQuerySense;
            break;
        case 2:
            cmd = CPortCmd::DownQueryGate;
            break;
        case 3:
            cmd = CPortCmd::DownQueryButton;
            break;
        case 4:
            cmd = CPortCmd::DownQueryControler;
            break;
        case 5:
            cmd = CPortCmd::DownDispenserQuery;
            break;
        case 6:
            cmd = CPortCmd::DownDispenserSend;
            break;
        case 7:
            cmd = CPortCmd::DownDispenserReceive;
            break;
        case 8:
            cmd = CPortCmd::DownDispenserReset;
            break;
        case 9:
            cmd = CPortCmd::DownPlayAudio;
            char cmdWelcome[ ] = { 0xAA, 0x04, 0x00, 0x45, 0x43, cCan };
            byData.append( cmdWelcome, sizeof ( cmdWelcome ) );
            PlayAudio( byData, vData, CPortCmd::AudioStartup );
            return;
            break;
        }

        break;

    case CommonDataType::UserPublishLed :
        if ( 2 > lstData.count( ) ) {
            return;
        }

        {
            QDate date = CCommonFunction::String2Date( lstData[ 0 ] );
            QTime time = CCommonFunction::String2Time( lstData[ 1 ] );
            DownloadTime( cCan, date, time );
            return;
        }
        break;

    case CommonDataType::UserSMS :
        return;
        break;
    }

    portCmd.ParseDownCmd( byData, cmd, vData );
    WriteData( byData );
}

CProcessData::CProcessData(QObject *parent) : QObject( parent )
{
}

CProcessData* CProcessData::GetProcessor()
{   // Only Picture Dialog
    return pCmdProcessor;
}

CProcessData::~CProcessData( )
{
    delete pFeeDlg;
    delete pConfirm[ 0 ];
    delete pConfirm[ 1 ];
    ReadCanForRestart( false );
}

void CProcessData::CheckCenterContronller( bool bEnter, QDateTime& dtDateTime )
{
    char cCan;
    //AA 0B 00 44 00 xx	最多40个字符对应编码 xx 55
    QDate date = dtDateTime.date( );
    QTime time = dtDateTime.time( );

    int nCount = CCommonFunction::GetAddressCount( bEnter );
    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        cCan = CCommonFunction::GetAddress( nIndex, bEnter );
        //DownloadWelcome( cCan );
        DownloadTime( cCan, date, time );
    }
}

void CProcessData::DownloadWelcome( char cCan )
{
    QByteArray byData;
    QByteArray vData;

    char cmdWelcome[ ] = { 0xAA, 0x04, 0x00, 0x45, 0x43, cCan };
    byData.append( cmdWelcome, sizeof ( cmdWelcome ) );
    PlayAudioDisplayInfo( byData, vData, CPortCmd::LedStartup, CPortCmd::AudioStartup );
}

void CProcessData::DownloadTime( char cCan, QDate& date, QTime& time )
{
    QByteArray byData;
    QByteArray vData;

    char cmdTime[ ] = { 0xAA, 0x0B, 0x00, 0x44, 0x00, cCan };
    byData.append( cmdTime, sizeof ( cmdTime ) );
    vData.append( 0x13 );
    QString strYear = QString::number( date.year( ) );

    if ( 4 == strYear.count( ) ) {
        strYear = strYear.right( 2 );
    }
    bool bOk = false;
    vData.append( ( char ) strYear.toUShort( &bOk, 16 ) );
    vData.append( ( char ) QString::number( date.month( ) ).toUShort( &bOk, 16 ) );
    vData.append( ( char ) QString::number( date.day( ) ).toUShort( &bOk, 16 ) );
    vData.append( ( char ) QString::number( time.hour( ) ).toUShort( &bOk, 16 ) );
    vData.append( ( char ) QString::number( time.minute( ) ).toUShort( &bOk, 16 ) );
    vData.append( ( char ) QString::number( time.second( ) ).toUShort( &bOk, 16 ) );
    vData.append( ( char ) date.dayOfWeek( ) );

    portCmd.ParseDownCmd( byData, CPortCmd::DownLED, vData );
    WriteData( byData );
}

CProcessData* CProcessData::GetProcessor( CWinSerialPort *pWinPort, MainWindow *pWindow )
{
    if ( NULL == pCmdProcessor ) {
        pCmdProcessor = new CProcessData( pWinPort, pWindow );
    }

    return pCmdProcessor;
}

void CProcessData::ReadCanForRestart( bool bRead )
{
    int nCount;
    QString strGroup = "CardCan";
    QString strCard = "%1Card%2";
    QString strCan= "%1Can%2";
    QString strCouple = "%1Count";
    QString strIndex;

    if ( bRead ) {
        strGroup += "/";
        nCount = pSettings->value( strCouple.arg( strGroup ), 0 ).toInt( );
        for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
            strIndex = QString::number( nIndex );
            cardCan.insert( pSettings->value( strCard.arg( strGroup, strIndex ) ).toString( ),
                            ( char ) pSettings->value( strCan.arg( strGroup, strIndex ) ).toInt( ) );
        }
    } else {
        pSettings->beginGroup( strGroup );
        pSettings->remove( "" );
        nCount = cardCan.count( );
        pSettings->setValue( strCouple.arg( "" ), nCount );

        QList< QString > lstKeys = cardCan.keys( );
        for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
            strIndex = QString::number( nIndex );
            pSettings->setValue( strCard.arg( "", strIndex ), lstKeys.at( nIndex ) );
            pSettings->setValue( strCan.arg( "", strIndex ), ( int ) cardCan[ lstKeys.at( nIndex ) ] );
        }

        pSettings->endGroup( );
        pSettings->sync( );
    }
}

void CProcessData::ReleaseProcessor( )
{
    if ( NULL !=pUploadDataThread ) {
        pUploadDataThread->CloseDB( );
    }

    if ( NULL != pCmdProcessor ) {
        delete pCmdProcessor;
    }
}

CWinSerialPort& CProcessData::GetWinSerialPort( )
{
    return *pSerialPort;
}

bool CProcessData::OpenPort( )
{
    pSerialPort->SetPortName( );
    pSerialPort->SetQueryMode( QextSerialBase::EventDriven );
    bool bRet = pSerialPort->OpenPort( false );
    pSerialPort->ConfigPort( );

    return bRet;
}

void CProcessData::ClosePort( )
{
    pSerialPort->ClosePort( );
}

bool CProcessData::IsOpen( )
{
    return pSerialPort->IsOpened( );
}

void CProcessData::ConfirmSuccess( )
{
    char cData[ ] = { 0xAA, 0x04, 0x00, 0x45, 0x43, 0x80, 0x00, 0xB6, 0x55 };
    int nLen = sizeof ( cData );
    QByteArray byData( cData, nLen );

    WriteData( byData );
}

int CProcessData::ParseData( QByteArray &byData )
{
    int nRet = 0;
    QByteArray vData;
    quint16 nDataLen = 0;
    quint8 nCanAddr = 0;
    quint8 nCheckSum = 0;
    CPortCmd::PortUpCmd cmdType =  portCmd.ParseUpCmd( byData, nDataLen, nCanAddr, nCheckSum, vData );

    QString strText = "";
    if ( CPortCmd::UpNone == cmdType ) {
        strText = "接收到未知命令！";
    } else if ( nCheckSum != portCmd.CheckSum( byData ) ) {
        strText = "校验和不正确！";
    } else if ( CPortCmd::UpSuccess == cmdType ) {
        strText = "与中心控制器通讯成功！";
    } else if ( CPortCmd::UpFailed == cmdType ) {
        strText = "与中心控制器通讯失败！";
    }

    if ( "" != strText ) {
        //CCommonFunction::MsgBox( pMainWindow, QString( "提示" ), strText, QMessageBox::Information );
        return nRet;
    }

    //ConfirmSuccess( );
    ProcessCmd( byData, cmdType );

    return nRet;
}

void CProcessData::GetCaptureFile( QString& strPath, QString& strCardNo, int nChannel, CommonDataType::CaptureImageType capType )
{
    QString strExt = "";
    if ( CommonDataType::CaptureBMP == capType ) {
        strExt = "BMP";
    } else if( CommonDataType::CaptureJPG == capType || CommonDataType::CaptureJPEG == capType ) {
        strExt = "JPG";
    }

    strPath = QString( "%1ch%2.%3" ).arg( strCardNo, QString::number( nChannel ), strExt );
    CCommonFunction::GetPath( strPath, CommonDataType::PathSnapshot );
}

void CProcessData::ClearSenseImage( QByteArray &byData )
{
    int nChannel = GetChannelByCan( ( char ) byData[ 5 ] );
    if ( bCardCapture[ nChannel ] ) {
        return;
    }

    pSettings->sync( );
    bool bQueue = pSettings->value( "CommonCfg/SenseGetImg", true ).toBool( );
    QString strFile = "";

    if ( bQueue ) {
        if ( !imgQueue[ nChannel ].isEmpty( ) ) {
            strFile = imgQueue[ nChannel ].dequeue( );

            imgQueue[ nChannel ].clear( ) ;
        }
    } else {
        if ( !imgStack[ nChannel ].isEmpty( ) ) {
            strFile = imgStack[ nChannel ].pop( );

            imgStack[ nChannel ].clear( );
        }
    }

    if ( !strFile.isEmpty( ) ) {
        QFile::remove( strFile );
    }
}

void CProcessData::CaptureSenseImage( QByteArray &byData, CommonDataType::CaptureImageType capType )
{
    int nChannel = GetChannelByCan( ( char ) byData[ 5 ] );
    if ( bCardCapture[ nChannel ] ) {
        return;
    }

    QString strFileName = "";
    QString strCardNo = "Sense" + QString::number( QDateTime::currentMSecsSinceEpoch( ) );
    GetCaptureFile( strFileName, strCardNo, nChannel, capType );
    pMainWindow->CaptureImage( strFileName, nChannel, capType  );

    LoadCapturedImg( strFileName, nChannel );

    if ( bHavePlateRecog ) {
        pMainWindow->PictureRegconize( strFileName, nChannel, byData );
#if false
        QString strTmp;
        CCommonFunction::GetPath( strTmp, CommonDataType::PathSnapshot );
        strTmp += "sense.jpg";

        if ( QFile::exists( strTmp ) ) {
            QFile::remove( strTmp );
        }

        if ( QFile::copy( strFileName, strTmp ) ) {
            pMainWindow->PictureRegconize( strTmp, nChannel );
        }
#endif
    }

    //imgQueue[ nChannel ].enqueue( strFileName );
    pSettings->sync( );
    bool bQueue = pSettings->value( "CommonCfg/SenseGetImg", true ).toBool( );
    bQueue ? imgQueue[ nChannel ].enqueue( strFileName ) :  imgStack[ nChannel ].push( strFileName );
}

void CProcessData::CaptureImage( QString& strCardNo, int nChannel, CommonDataType::CaptureImageType capType )
{
    QString strFileName = "";
    GetCaptureFile( strFileName, strCardNo, nChannel, capType );
    pSettings->sync( );
    bool bQueue = pSettings->value( "CommonCfg/SenseGetImg", true ).toBool( );
    bool bEmpty = bQueue ? imgQueue[ nChannel ].isEmpty( ) : imgStack[ nChannel ].isEmpty( );
    bool bFault = false;

    //if ( imgQueue[ nChannel ].isEmpty( ) ) {
    if ( bEmpty ) {
        pMainWindow->CaptureImage( strFileName, nChannel, capType );
        bFault = true;
    } else {
        //QString strTmpFile = imgQueue[ nChannel ].dequeue( );
        QString strTmpFile = bQueue ? imgQueue[ nChannel ].dequeue( ) : imgStack[ nChannel ].pop( );
        QFile file( strTmpFile );
        if ( !file.rename( strFileName ) ) {
            pMainWindow->CaptureImage( strFileName, nChannel, capType );
            bFault = true;
        }
    }

    if ( bCardCapture[ nChannel ] || bFault ) {
        LoadCapturedImg( strFileName, nChannel );
    }
}

void CProcessData::LoadEntranceImg( QString &strCardNo, CommonDataType::CaptureImageType capType )
{
    QString strFileName = "";
    int nChannel = 0;
    GetCaptureFile( strFileName, strCardNo, nChannel, capType );
    ControlVehicleImage( strCardNo, false, nChannel, 1 );
    LoadCapturedImg( strFileName, nChannel );
}

void CProcessData::LoadCapturedImg( QString& strPath, int nChannel )
{
    pMainWindow->LoadCapturedImg( strPath, nChannel );
}

void CProcessData::GetPlate( QString &strCardNo, QString &strPlate )
{
    CommonDataType::QEntityHash& entHash = CCommonFunction::GetCardEntity( );
    CommonDataType::PEntityInfo pInfo = entHash.value( strCardNo );

    if ( NULL == pInfo ){
        QString strWhere = QString( " Where cardindex ='%1'" ).arg( strCardNo );
        QStringList lstRows;
        CLogicInterface::GetInterface( )->OperateCarInfo( lstRows, CommonDataType::SelectData, strWhere );
        if ( 0 < lstRows.count( ) ) {
            strPlate = lstRows[ 0 ];
        }
        return;
    }

    QList<QString> lstKeys = pInfo->carInfo.keys( );
    if ( 0 == lstKeys.count( ) ) {
        return;
    }

    strPlate = lstKeys[ 0 ];
}

quint64 CProcessData::GetTimeSecond( QDateTime &time )
{
    return time.toMSecsSinceEpoch( ) / 1000;
}

bool CProcessData::GetTimeDiff( int nIntervalTime, quint64 nCurrentTime, QDateTime &tTarget )
{
    return nIntervalTime < ( int ) ( nCurrentTime - GetTimeSecond( tTarget ) );
}

bool CProcessData::SingleChannel( QString& strPlate, bool bEnter, bool bSame, quint64 nCurrentTime )
{
    bool bRet = false;

    if ( bEnter ) {
        if ( singleChannelHash.contains( strPlate ) ) {
            QVector< QDateTime > vec = singleChannelHash.value( strPlate );
            bRet = GetTimeDiff( nSameInterval[ bEnter ? 0 : 1 ], nCurrentTime, vec[ bSame ? 0 : 1 ] ); //摄像头照到同一通道
            //bRet = bRet || GetTimeDiff( nDiffInterval, nCurrentTime, vec[ 1 ] ); //摄像头照到不同通道
        } else { // 刚进
            bRet = true;
        }
    } else {
        if ( singleChannelHash.contains( strPlate ) ) {
            QVector< QDateTime > vec = singleChannelHash.value( strPlate );
            bRet = GetTimeDiff( nSameInterval[ bEnter ? 0 : 1 ], nCurrentTime, vec[ bSame ? 1 : 0 ] );
        } else { // 刚出
            bRet = true;
        }
    }

    return bRet;
}

char CProcessData::GetCanLevel( char cCan )
{
    char cLevel;
    cCan &= 0x3F;
    char cTmp = char( 0 );

    if ( cTmp == ( cCan & 0x20 ) ) { // 32
        cLevel = 1;
    } else if ( cTmp == ( cCan & 0x10 ) ) { // 16
        cLevel = 2;
    } else if ( cTmp == ( cCan & 0x08 ) ) { // 8
        cLevel = 3;
    } else { // 8
        cLevel = 4;
    }

    return cLevel;
}

void CProcessData::TestCaptureImage( QString &strPlate, int nChannel )
{
    if ( !bTest ) {
        return;
    }

    QString strFileName = "";
    CCommonFunction::GetPath( strFileName, CommonDataType::PathSnapshot );
    QString strTime;
    QTime time = QTime::currentTime( );
    CCommonFunction::Time2String( time, strTime );
    strTime.remove( ":" );
    strFileName += strPlate + "-" + strVideoChannelName[ nChannel ] + "-" + strTime + ".jpg";
    pMainWindow->CaptureImage( strFileName, nChannel, CommonDataType::CaptureJPG );
}

void CProcessData::MakeCardCmd(QString &strCardNo, QByteArray &byData, char cCan )
{
    qint32 nCardNo = strCardNo.toInt( );
    char* pInt = ( char* ) &nCardNo;

    //AA	06 00	4B 00	xx	3字节，16进制卡号	xx	55
    byData.append( char( 0xAA ) );
    byData.append( char( 0x06 ) );
    byData.append( char( 0x00 ) );
    byData.append( char( 0x4B ) );
    byData.append( char( 0x00 ) );
    byData.append( char( cCan ) ); // CAN
    byData.append( char( pInt[ 2 ] ) );
    byData.append( char( pInt[ 1 ] ) );
    byData.append( char( pInt[ 0 ] ) );
    byData.append( char( 0x00 ) ); // Checksum
    byData.append( char( 0x55 ) );
}

void CProcessData::HandleWeighing( QStringList lstData )
{

}

void CProcessData::HandleCapture( quint8 nChannel )
{
    QString strFileName = "";
    QString strCardNo = "Sense" + QString::number( QDateTime::currentMSecsSinceEpoch( ) );
    GetCaptureFile( strFileName, strCardNo, nChannel, CommonDataType::CaptureJPG );
    pMainWindow->CaptureImage( strFileName, nChannel, CommonDataType::CaptureJPG  );

    if ( true ) {
        //pMainWindow->PictureRegconize( strFileName, nChannel,  );
#if false
        QString strTmp;
        CCommonFunction::GetPath( strTmp, CommonDataType::PathSnapshot );
        strTmp += "sense.jpg";

        if ( QFile::copy( strFileName, strTmp ) ) {
            pMainWindow->PictureRegconize( strTmp, nChannel );
        }

        if ( QFile::exists( strTmp ) ) {
            QFile::remove( strTmp );
        }
#endif
    }
}

void CProcessData::SendPlate( QString strPlate, int nChannel, int nConfidence )
{
    QStringList lstData;
    QDateTime dt = QDateTime::currentDateTime( );

    QString strDateTime = dt.toString( "yyyyMMddhhmmss" );
    QString strName = dt.toString( "yyyyMMddhhmmsszzz" );

    QString strFileName = "";
    CCommonFunction::GetPath( strFileName, CommonDataType::PathSnapshot );
    strFileName += strPlate + "-" + QString::number( nChannel ) + "-" + strName + ".jpg";
    pMainWindow->CaptureImage( strFileName, nChannel, CommonDataType::CaptureJPG );

    if ( !QFile::exists( strFileName ) ) {
        int n = 0;
        n = 1;
        return;
    }

    lstData << strPlate << strDateTime << QString::number( nConfidence ) << strFileName;

    emit PlateDelivery( nChannel, lstData, strPlate );
}

int CProcessData::MatchNum( QString &strPlate, const QString &strTest )
{
    int counter = 0;
    int min = qMin( strPlate.size(), strTest.size() );
    for( int i = 0; i < min; ++i ) // length 超出范围引发崩溃。
    {
        if( strPlate.at( i ) == strTest.at( i ) )
        {
            ++counter;
            continue;
        }
    }

    return counter;
}

bool CProcessData::RecognizeFuzzyPlate( CommonDataType::QPlateCardHash &hash,
                                        QString &strCarNo,
                                        QString& strPlate )
{
    // typedef QHash< QString / Plate, QString / CardNo > QPlateCardHash;
    bool bRet = false;
    if ( 0 == cPrecision ) {
        return bRet;
    }

    QList< QString > lstPlates = hash.keys( );
    //lstPlates.removeAll( "未知" );

    // strCarNo

    QMultiHash< int, QString > matchHash;
    int nMatch = 0;

    foreach ( const QString& strValue, lstPlates ) {
        nMatch = MatchNum( strPlate, strValue );
        if( nMatch < strPlate.count( ) - cPrecision )
        {
            continue;
        }

        matchHash.insertMulti( nMatch,  strValue );
    }

    if( matchHash.isEmpty() )
    {
        return bRet;
    }

    QList< int > lstKeys =  matchHash.keys( );
    qSort( lstKeys );

    QString strTmpPlate = matchHash.value( lstKeys.at( lstKeys.count(  ) - 1 )  );
    strCarNo = hash.value( strTmpPlate );
    bRet = true;

    return bRet;
}

bool CProcessData::GetEntranceFlag( int nChannel )
{
    return ( 0 != ( nChannel % 2 ) );
}

int CProcessData::GetChannelIndex( int nChannel )
{
    // 1 2 3 4
    // 0 1 2 3
    // 5 6 7 8
    // 4 5 6 7
    // 9 10 11 12
    // 8 9 10 11
    // 33 34 35 36
    // 37 38 39 40

    int nIndex = ( nChannel - 1 ) % 4;

    return nIndex;
}

void CProcessData::CheckBlacklist( QStringList& lstData )
{
    if ( !bBlacklistCheck || 7 > lstData.count( ) ) {
        return;
    }

    const QString& strPlate = lstData.at( 3 );
    if ( strPlate.isEmpty( ) || "未知" == strPlate ) {
        return;
    }

    QString strSql = QString( "Select plate from blacklist where upper( plate ) = '%1'" ).arg( strPlate.toUpper( ) );
    QStringList lstRow;
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRow );

    if ( 0 == lstRow.count( ) ) {
        return;
    }

    pMainWindow->DisplayAlert( lstData );
}

void CProcessData::RecognizePlate( QString strPlate, int nChannel, int nConfidence, bool bNocard, QByteArray bySerialData )
{
    if ( bNocard ) {
        strCurrentPlate[ nChannel ] = strPlate;

        if ( WriteInOutRecord( bySerialData ) ) {
            //SenseOpenGate( bySerialData );
        }

        return;
    }

    if ( bStartupPlateDilivery ) {
        SendPlate( strPlate, nChannel, nConfidence );
        return;
    }

    bool bEnter = ( 0 == nChannel % 2 );
    bPlateRecognize[ nChannel ] = true;

    if ( IfSenseOpenGate( ) ) {
        //plateQueue[ nChannel ].enqueue( strPlate );
        strCurrentPlate[ nChannel ] = strPlate;
        return;
    }

    TestCaptureImage( strPlate, nChannel );
    // nChannel 0 1 2 3
    strCurrentPlate[ nChannel ] = strPlate;
    CommonDataType::QPlateCardHash& hash = CCommonFunction::GetPlateCardHash( );
    if ( false == hash.contains( strPlate ) ) { // Don't exist to get
        QString strWhere = QString( " and carcp = '%1'" ).arg( strPlate );
        CLogicInterface::GetInterface( )->GetPlateCardInfo( hash, strWhere );
    }

    QString strCardNo = hash.value( strPlate );
    if ( strCardNo.isNull( ) || strCardNo.isEmpty( ) ) {
        //加入判断
        if ( !RecognizeFuzzyPlate( hash, strCardNo, strPlate ) ) {
            return;
        }
    }

    CommonDataType::QEntityHash& entHash = CCommonFunction::GetCardEntity( );
    if ( false == entHash.contains( strCardNo ) ) {
        QString strWhere = QString( " And a.cardno = '%1'" ).arg( strCardNo );
        CLogicInterface::GetInterface( )->GetEntityInfo( entHash, strWhere );
    }

    CommonDataType::PEntityInfo pInfo = entHash.value( strCardNo );
    if ( NULL == pInfo ) { // TmpCard
        return;
    }

    GetChannelInfo( strCardNo );
    //QStringList& channelInfo = bEnter ? inChannelInfo : outChannelInfo;
    //if ( 0 == channelInfo.count( ) ) {
    //    return;
   // }
    //QString& strCan = channelInfo[ 3 ];
    char cCan = cCanVideo[ nChannel ];//strCan.toShort( );
    QByteArray byData;
    MakeCardCmd( strCardNo, byData, cCan );

    //bPlateRecognize[ bEnter ] = true;

    //////////////////////////////
    QDateTime time = QDateTime::currentDateTime( );
    int nCurrentTime = GetTimeSecond( time );
    bool bDiffContinue =  bSingleChannel && SingleChannel( strPlate, bEnter, false, nCurrentTime );
    bool bSameContinue = SingleChannel( strPlate, bEnter, true, nCurrentTime );

    if ( bSingleChannel ) {
        bSameContinue &= bDiffContinue;
    }
    /////////////////////////////


    bool bMust = false;
    //if ( !bEnter && bCardConfirm ) { // Save Plate/Card
    if ( ( bMust = MustCard( bEnter, strCardNo ) ) ) {
        //confirmHash.insert( strCardNo, strPlate );
        confirmHash.insert( strPlate, strCardNo );
    }
    //////////////////////////////
    //if ( bSameContinue && ( bEnter || ( !bEnter && !bCardConfirm ) ) ) {

    if ( bSameContinue && !bMust ) { //不需要确认走车牌识别流程，否则走刷卡流程
        ProcessCardInfo( byData, true, strPlate );
        //strCurrentPlate[ bEnter ] = "";
    }

    if ( false && bMust ) {
        QByteArray vData;
        ShuaCard( byData, vData );
    }

    bPlateRecognize[ nChannel ] = bMust;
}

bool CProcessData::MustCard( bool bEnter, QString &strCardID )
{
    bool bRet = false;

    CommonDataType::PEntityInfo pInfo = CCommonFunction::GetCardEntity( ).value( strCardID );
    if ( NULL == pInfo ) {
        return bRet;
    }

    bRet = bEnter ? pInfo->MustCard.bEnterMustCard : pInfo->MustCard.bLeaveMustCard;

    return bRet;
}

void CProcessData::GetChannelInfo( QString &strCardNo )
{
    if ( inChannelInfo.isEmpty( ) || outChannelInfo.isEmpty( ) ) {
        inChannelInfo.clear( );
        outChannelInfo.clear( );

        CCommonFunction::GetChannelInfo( strCardNo, true, inChannelInfo );
        CCommonFunction::GetChannelInfo( strCardNo, false, outChannelInfo );
    }
}

bool CProcessData::PlateCardComfirmDlg( QByteArray& byData, QString& strCardNumber, QString strPlate /*识别到的*/, ParkCardType& cardKind)
{
    QByteArray vData;
    bool bEnter = ( 0 != byData[ 5 ] % 2 );
    int nChannel = GetChannelByCan( byData[ 5 ] );

    if ( pConfirm[ nChannel ]->isVisible( ) ) {
        PlayAudioDisplayInfo( byData, vData, CPortCmd::LedExitConfirm, CPortCmd::AudioExitConfirm );
        return false;
    }

    bool bRet = pConfirm[ nChannel ]->GetInfomation( bEnter, strPlate,  strCardNumber, byData[ 5 ] );

    if ( bRet && ( CardTime == cardKind ) ) {
        return bRet;
    }

    PlayAudioDisplayInfo( byData, vData, CPortCmd::LedExitConfirm, CPortCmd::AudioExitConfirm );
    bRet = ( CDlgInconformity::Accepted == pConfirm[ nChannel ]->exec( ) );

    return bRet;
}

bool CProcessData::PlateCardComfirm( QString &strCardNumber, QByteArray& byData, QString strPlate, ParkCardType& cardKind )
{
    bool bEnter = ( 0 != byData[ 5 ] % 2 );
    int nChannel = GetChannelByCan( byData[ 5 ] );
    bool bRet = ( cardKind != CardTime );

    if ( !bRet) {
        bRet = true;
        // TmpCard
        if ( bPlateRecognize[ nChannel ] ) {
            bRet = PlateCardComfirmDlg( byData, strCardNumber, strPlate, cardKind );
            //bPlateRecognize[ bEnter ] = false;
        }

        return bRet;
    }

    bRet = bHavePlateRecog;
    if ( !bRet) { // No Plate Recognization
        return true;
    }

    char cLevel = GetCanLevel( byData[ 5 ] );
    if ( 1 < cLevel ) { // GarageInGarage
        return true;
    }

    // confirmHash < Plate, CardID >
    QList< QString > lstMemPlates = confirmHash.keys( );
    CommonDataType::QPlateCardHash& hash = CCommonFunction::GetPlateCardHash( );
    QList< QString > lstRawPlates = hash.keys( strCardNumber );

    for ( int nIndex = 0; nIndex < lstRawPlates.count( ); nIndex++ ) {
        const QString& strPlate = lstRawPlates.at( nIndex );
        bRet = lstMemPlates.contains( strPlate );
        if ( bRet ) {
            confirmHash.remove( strPlate );
            //bPlateRecognize[ bEnter ] = false;
            return bRet;
        }
    }

    if ( !bPlateRecognize[ nChannel ] && !bRet ) { // No Plate Recognization
        return true;
    }

    bRet = MustCard( bEnter, strCardNumber );
    if ( bPlateRecognize[ nChannel ] && bRet ) {
        bRet = PlateCardComfirmDlg( byData, strCardNumber, strPlate, cardKind );
        //bPlateRecognize[ bEnter ] = false;
    } else {
        bRet = true;
    }

    return bRet;
}

bool CProcessData::ExitConfirm( QString& strCardno, QByteArray& byData )
{
    bool bRet = false;

    bRet = confirmHash.contains( strCardno );

    if ( bRet ) { // confirmHash 是根据车牌找到的卡号Hash
        confirmHash.remove( strCardno );
        return bRet;
    } else { // 车卡不符
        QByteArray vData;
        PlayAudioDisplayInfo( byData, vData, CPortCmd::LedExitConfirm, CPortCmd::AudioExitConfirm );
    }

    QStringList lstInit;
    int nAmount;
    bRet = PictureContrast( lstInit, nAmount, byData, strCardno );

    return bRet;
}

bool CProcessData::GetCCCardCanAddr( QString& strCardno, char& cCan, bool& bEnter )
{
    bool  bRet = false;

    //QString strSql = "select Inside from monthcard where cardno = '%1' union ";
    //strSql += "select Inside from savecard where cardno = '%2' union ";
    //strSql += "select Inside from tmpcard where cardno = '%3'";
    QString strSql = " select CenterController( '%1' ) ";

    strSql = strSql.arg( strCardno );//, strCardno, strCardno );
    QStringList lstRow;
    int nRet = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRow );
    if ( 0 == nRet ) {
        return bRet;
    }

    bEnter = ( "0" == lstRow[ 0 ] );

    static bool bIn = false;
    static bool bOut = false;
    static bool bGet = true;
    static char cIn, cOut;
    if ( bGet ) {
        QString strKey = "SpecialSet/CC/%1";
        QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSysSet );
        bIn = pSet->value( strKey.arg( "Enter" ), false ).toBool( );
        bOut = pSet->value( strKey.arg( "Leave" ), false ).toBool( );
        cIn = ( char ) pSet->value( strKey.arg( "EnterAddr" ), 1 ).toInt( );
        cOut = ( char ) pSet->value( strKey.arg( "LeaveAddr" ), 2 ).toInt( );
        bGet = false;
    }

    if ( ( bRet = ( bEnter && bIn ) ) ) {
        cCan = cIn;
    } else if ( ( bRet = ( !bEnter && bOut ) ) ) {
        cCan = cOut;
    }

    return bRet;
}

quint32 CProcessData::GetCardNoByCom( QByteArray& byData )
{
    quint8 byte6 = byData[ 6 ]; //LSB BE LE
    quint8 byte7 = byData[ 7 ];
    quint8 byte8 = byData[ 8 ];

    return byte8 + ( byte7 << 8 ) + ( byte6 << 16 );
}

void CProcessData::DefaultClicked( QByteArray &byData )
{
    quint32 nCardNumber = GetCardNoByCom( byData );
    QString strCardno = QString( "%1" ).arg( nCardNumber );
    bool bEmployee = ( strCardno == pMainWindow->GetCurrentUserID( ) );

    if ( !bEmployee ) {
        return;
    }

    //ParkCardType cardKind = CardNone;
    //QStringList lstRows;
    //GetCardType2( strCardno, lstRows, cardKind );

    if ( pConfirm[ 0 ]->isVisible( ) ) {
        pConfirm[ 0 ]->DefaultClicked(  );
    }

    if ( pConfirm[ 1 ]->isVisible( ) ) {
        pConfirm[ 1 ]->DefaultClicked(  );
    }

    //if ( CardTime != cardKind || !pFeeDlg->isVisible( ) ) {
    //    return;
    //}

    if ( pFeeDlg->isVisible( ) ) {
        pFeeDlg->DefaultClicked(  );
    }
}

void CProcessData::EmployeeCard( QByteArray &byData )
{
    quint32 nCardNumber = GetCardNoByCom( byData );
    QString strCardno = QString( "%1" ).arg( nCardNumber );
    pMainWindow->EmployeeCard( strCardno );
}

void CProcessData::PlateCardComfirmPass( QString strCardNo, char cCan, QString strPlate )
{
    QByteArray byData;
    MakeCardCmd( strCardNo, byData, cCan );

    bool bEnter = ( 0 != cCan % 2 );
    QByteArray vData;
    QStringList lstRows;
    ParkCardType cardKind = CardNone;
    GetCardType2( strCardNo, lstRows, cardKind );

    int nChannel = GetChannelByCan( cCan );
    bPlateRecognize[ nChannel ] = false;

    if ( !CheckCardRight( strCardNo, bEnter, byData, cardKind ) ) { // Check
        return;
    }

    AssertCard( byData, vData, lstRows, strPlate, cardKind );
}

void CProcessData::ProcessCardInfo( QByteArray &byData, bool bPlate, QString strCurPlate )
{
        quint8 byte4 = byData[ 4 ];
        quint8 byte5 = byData[ 5 ]; // 1 ( +2 ) Enetr Park / 2 ( +2 ) Leave Park / 80 Register Card
        //quint8 byte6 = byData[ 6 ]; //LSB BE LE
        //quint8 byte7 = byData[ 7 ];
        //quint8 byte8 = byData[ 8 ];

        quint32 nCardNumber = GetCardNoByCom( byData );
        QString strCardNumber = QString::number( nCardNumber );
        GetNewCardInfo( strCardNumber );
        GetChannelInfo( strCardNumber );

        //if ( bPlate && MustCard( bEnter, strCardNumber ) && ( cardType != CardTime ) ) {
        //    return;
        //}

        if ( !bPlate && 0x80 == byte5 && pMainWindow->SetCardNumber( strCardNumber ) ) { // Register Card
            //qDebug( ) << "Time " << QDateTime::currentDateTime( ).toMSecsSinceEpoch( ) << endl;
            //pMainWindow->SetCardNumber( strCardNumber );
            const QString strText = "卡注册" + strCardNumber;
            pMainWindow->SetAlertMsg( strText );
            return;
        }

        bool bEnter;
        if ( !bPlate && 0x80 == byte5 ) { // CC replaces the card reader
            char cCan;
            if ( !GetCCCardCanAddr( strCardNumber, cCan, bEnter ) ) {
                const QString strText = QString( "中心Can%1" ).arg( QString( cCan ));
                pMainWindow->SetAlertMsg( strText );
                return;
            }
            byData[ 5 ] = cCan;
            //byte5 = cCan;
        }

        int nChannel = GetChannelByCan( ( char ) byData[ 5 ] );

        bEnter = CCommonFunction::ContainAddress( char ( byData[ 5 ] ), true );
        if ( strCurPlate.isEmpty( ) ) {
            //QString strPlate = "";
            //GetPlate( strCardNumber, strPlate );
            //strCurPlate = strPlate;

            //if ( !strCurrentPlate[ bEnter ].isEmpty( ) &&
            //     ( strCurPlate.isEmpty( ) || "未知" == strCurPlate ) ) {
            //    strCurPlate = strCurrentPlate[ bEnter ];
           // }

            strCurPlate = strCurrentPlate[ nChannel ];//识别到的车牌
        }

        strCurrentPlate[ nChannel ].clear( );

        if ( !bPlate && ( 0x80 != byte5 ) && ( 0x00 == byte4 ) ) {//!bPlateRecognize[ bEnter ]
            QString strEnter = "UserRequest/NoCarCardValidedEntrance";
            QString strLeave = "UserRequest/NoCarCardValidedExit";
            bool bValided = pSettings->value( bEnter ? strEnter : strLeave, true ).toBool( );
            if ( false == bValided ) {
                QString strText = "无车刷卡";
                pMainWindow->SetAlertMsg( strText );
                return;
            }
        }

        QByteArray vData;
        QStringList lstRows;
        ParkCardType cardKind = CardNone;
        GetCardType2( strCardNumber, lstRows, cardKind );

        if ( !bEnter && !bPlate && CardTime == cardKind && pMainWindow->ShiftDlgISVisible( ) ) {
            QString strText = "交接班";
            pMainWindow->SetAlertMsg( strText );
            qDebug( ) << "Shift" << endl;
            return;
        }

        CaptureImage( strCardNumber, nChannel, CommonDataType::CaptureJPG );

        qDebug( ) << " Card No. : " << strCardNumber << endl;
        // Get Card Info From Database

        //if ( !bPlate && ExcludeRemoteCardDuplication( nCardNumber, bEnter ) ) { // Remote card interval
        //    return;
        //}

        if ( CardNone == cardKind ) {
            PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardInvalid, CPortCmd::AudioCardInvalid );
            QString strText = "未知卡";
            pMainWindow->SetAlertMsg( strText );
            return;
        }

        int nStateIndex = 4;
        if ( CardSave == cardKind ) {
            nStateIndex = 2;
        }

        if ( lstRows.count( ) - 1 < nStateIndex ) {
            QString strText = "状态索引";
            pMainWindow->SetAlertMsg( strText );
            return;
        }

        QString strState = lstRows[ nStateIndex ];
        if ( 0 == strState.compare( QString( "挂失" ) ) ) {
            PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardLoss, CPortCmd::AudioCardLoss );
            QString strText = "挂失卡";
            pMainWindow->SetAlertMsg( strText );
            return;
        }

        /////////////////////
        //if ( ( ( !bEnter ) & bCardConfirm ) &&
        //if ( MustCard( bEnter, strCardNumber ) &&
        //    ( cardType != CardTime ) &&
        //     !ExitConfirm( strCardNumber, byData ) ) { // Exit must read card.
        //    return;
        //}

        if ( !bPlate && !PlateCardComfirm( strCardNumber, byData, strCurPlate, cardKind ) ) {
            //bPlateRecognize[ bEnter ] = false;
            QString strText = "不符拒放";
            pMainWindow->SetAlertMsg( strText );
            return;
        }

        if ( !bPlate ) {
            bPlateRecognize[ nChannel ] = false;
        }

        if ( !CheckCardRight( strCardNumber, bEnter, byData, cardKind ) ) { // Check
            QString strText = "无权限";
            pMainWindow->SetAlertMsg( strText );
            return;
        }
        /////////////////////

        if ( pConfirm[ nChannel ]->isVisible( ) ) {
            pConfirm[ nChannel ]->close( );
        }

        const QString strText = "P:" + strCardNumber;
        pMainWindow->SetAlertMsg( strText );

        bool bRet = AssertCard( byData, vData, lstRows, strCurPlate, cardKind );
        bRet = vData.contains( 0x32 );
        if ( false == bRet ) {
            return;
        }
}

bool CProcessData::ExcludeRemoteCardDuplication( quint32 nCardID, ParkCardType& cardKind )
{
    bool bRet = true;

    if ( CardMonthly != cardKind ) {
        return false;
    }

    quint64 nInterval = pSettings->value( "CommonCfg/RemoteCardTime", 60 ).toUInt( ) * 1000;
    if ( 0 == nInterval ) {
        return bRet;
    }

    quint64 nTime2 = QDateTime::currentMSecsSinceEpoch( );
    if ( !hashCardTime.contains( nCardID ) ) {
        hashCardTime.insert( nCardID, nTime2 );
        return bRet;
    }

    quint64 nTime1 = hashCardTime.value( nCardID );
    //hashCardTime.insert( nCardID, nTime2 );
    quint64 nTime = nTime2 - nTime1;
    pSettings->sync( );
    //quint64 nInterval = pSettings->value( "CommonCfg/RemoteCardTime", 60 ).toUInt( ) * 1000; // Ms

    bRet = ( nTime >= nInterval );

    if ( bRet ) {
        hashCardTime.insert( nCardID, nTime2 );
    }

    return bRet;
}

bool CProcessData::CheckCardRight( QString& strCardID, bool bEnter, QByteArray& byData,ParkCardType& cardKind )
{
    bool bRet = true;
    if ( CardNone == cardKind ) {
        return bRet;
    }

    bRet = false;
    QStringList lstRight;
    QTime current;
    QTime start;
    QTime end;
    QString strStart;
    QString strEnd;
    int nField = 0;
    QString strChannel;
    char cCan = byData[ 5 ];
    GetChannelName( bEnter, cCan, strChannel );

    CommonDataType::PEntityInfo pInfo = CCommonFunction::GetCardEntity( ).value( strCardID );
    if ( NULL == pInfo ) {
        goto EXITPROCESS;
    }

    lstRight = pInfo->cardRight.value( strChannel );
    if ( 0 == lstRight.count( ) ) {
        goto EXITPROCESS;
    }

    current = QTime::currentTime( );

    strStart = lstRight[ nField++ ];
    strEnd = lstRight[ nField++ ];
    start = QTime::fromString( strStart );
    end = QTime::fromString( strEnd );
    bRet = ( start <= current && current <= end );

    EXITPROCESS:
    if ( !bRet ) { // No right
        QByteArray vData;
        if ( !ExcludeRemoteCardDuplication( strCardID.toUInt( ), cardKind ) ) {
            PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardNoRight, CPortCmd::AudioCardNoRight );
        }
    }

    return bRet;
}

bool CProcessData::AssertCard( QByteArray& byData, QByteArray& vData, QStringList& lstRows, QString strPlate, ParkCardType& cardKind )
{
    bool bRet = false;
    //bool bEnter = ( 0 != byData[ 5 ] % 2 );
    switch ( cardKind) {
    case CardNone :
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardInvalid, CPortCmd::AudioCardInvalid );
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedContactAdmin, CPortCmd::AudioContactAdmin );
        break;

    case CardMonthly :
        bRet = ProcessMonthlyCard( byData, vData, lstRows, strPlate, cardKind );
        break;

    case CardSave :
        bRet = ProcessSaveCard( byData, vData, lstRows, strPlate, cardKind );
        break;

    case CardTime :
        bRet = ProcessTimeCard( byData, vData, lstRows, strPlate, cardKind );
        break;

    case CardEmployee :
        break;
    }

    return bRet;
}

bool CProcessData::CarInsideOutside( bool bEnter, QString& strCardNumber, QString& strTable,
                                     QByteArray& byData, QByteArray& vData, char cCan, ParkCardType& cardKind )
{
    //inshebeiname, intime, outshebeiname, outtime
    bool bRet = true;

    char cLevel = GetCanLevel( cCan );
    if ( 1 != cLevel ) {
        return bRet;
    }
#if 1
    QStringList lstRows;
    //QString strSql = QString( " Select Inside From %1 Where cardno = '%2'" ).arg( strTable, strCardNumber );
    QString strSql = QString( " Select CarInSide( '%1', '%2' )" ).arg( strTable, strCardNumber );
    int nRet = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
    if ( 0 == nRet ) {
        return bRet;
    }
#endif
    QString strInside  = lstRows[ 0 ];
    QString strFlag = "0";
    QString strText = "";
    //CarInsideOutsideHash( strInside, strCardNumber, true );
    if ( bEnter && strFlag != strInside ) {
        bRet = false;
        strText = "已入场" ;

        if ( !ExcludeRemoteCardDuplication( strCardNumber.toUInt( ), cardKind ) ) {
            PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCarInside, CPortCmd::AudioCarInside );
        }
    } else if ( !bEnter && strFlag == strInside ) {
        bRet = false;
        strText = "未入场" ;
        if ( !ExcludeRemoteCardDuplication( strCardNumber.toUInt( ), cardKind ) ) {
            PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCarOutside, CPortCmd::AudioCarOutside );
        }
    }

    if ( !strText.isEmpty( ) ) {
        pMainWindow->SetAlertMsg( strText );
    }

    return bRet;
}

void CProcessData::CarInsideOutsideHash( QString &strInside, QString &strCardNo, bool bGet )
{
    CommonDataType::QEntityHash& entInfo = CCommonFunction::GetCardEntity( );
    CommonDataType::PEntityInfo pInfo = entInfo.value( strCardNo );

    if ( NULL == pInfo ) {
        return;
    }

    if ( bGet ) {
        strInside = QString::number( pInfo->nInside );
    } else if ( !strInside.isEmpty( ) ) {
        pInfo->nInside = strInside.toInt( );
    }
}

void CProcessData::GetNewCardInfo( QString &strCardNo )
{
    if ( NULL != CCommonFunction::GetCardEntity( ).value( strCardNo ) ) {
        return;
    }

    QString strWhere = QString( " and cardno = '%1'" ).arg( strCardNo );
    QString strTmpWhere = QString( " Where cardno = '%1'" ).arg( strCardNo );
    CLogicInterface::GetInterface( )->GetEntityInfo( CCommonFunction::GetCardEntity( ), strWhere, strTmpWhere );

    strWhere = QString( " and cardindex = '%1'" ).arg( strCardNo );
    CLogicInterface::GetInterface( )->GetPlateCardInfo( CCommonFunction::GetPlateCardHash( ), strWhere );

}

void CProcessData::CarInsideOutside( bool bEnter, QString& strTable, QString& strCardNumber, char cCan )
{
    char cLevel = GetCanLevel( cCan );
    QString strInside;
    if ( bEnter  ) {
        strInside = QString( "%1" ).arg( ( 1 << cLevel ) - 1 );
    } else if ( 1 == cLevel ) { // 最外层
        strInside = "0";
    }

    QString strSql = QString( "Update %1 set Inside = %2 Where cardno = '%3'" ).arg( strTable, strInside, strCardNumber );
    //CarInsideOutsideHash( strInside, strCardNumber, false );

    CLogicInterface::GetInterface( )->ExecuteSql( strSql );
}

void CProcessData::GetCardTypeData( QString &strType, QByteArray &vData )
{
    vData.clear( );
    QByteArray byTmp = CCommonFunction::GetTextCodec( )->fromUnicode( strType );
    vData.append(  byTmp.data( ), byTmp.count( ) );
}

bool CProcessData::GetMonthDeadline( QDateTime &dtEndTime, QString &strCardNo )
{
    bool bRet = false;
    CommonDataType::PEntityInfo pInfo = CCommonFunction::GetCardEntity( ).value( strCardNo );

    if ( NULL == pInfo ) {
        return bRet;
    }

    QString strSql = QString( "Select endtime from monthcard where cardno = '%1'" ).arg( strCardNo );
    QStringList lstRows;
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );

    if ( 0 == lstRows.count( ) ) {
        return bRet;
    }

    pInfo->MonthDateTime.dtEnd = CCommonFunction::String2DateTime( lstRows[ 0 ] );
    if ( pInfo->MonthDateTime.dtEnd.toTime_t( ) > dtEndTime.toTime_t( ) ) {
        dtEndTime = pInfo->MonthDateTime.dtEnd;
        bRet = true;
    }

    return bRet;
}

bool CProcessData::ProcessMonthlyCard( QByteArray& byData, QByteArray& vData, QStringList &lstRows, QString strPlate, ParkCardType& cardKind )
{
    // Select cardno, cardkind, starttime, endtime, cardstate, cardselfno, cardcomment, cardcreator
    // 该卡已挂失
    // 该卡有效期剩余xx天
    // 该卡已过有效期
    quint8 byte5 = byData[ 5 ]; // 3E Enetr Park 3F Leave Park
    int nChannel = GetChannelByCan( byte5 );
    bool bEnter = CCommonFunction::ContainAddress( char ( byte5 ), true );
    bool bLeave = !bEnter;
    bool bRet = false;
#if false
    QString strState = lstRows[ 4 ];
    if ( 0 == strState.compare( QString( "挂失" ) ) ) {
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardMonth, CPortCmd::AudioCardMonth );
        PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardLoss, CPortCmd::AudioCardLoss );
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedContactAdmin, CPortCmd::AudioContactAdmin );
        return bRet;
    }
#endif

    if ( !ExcludeRemoteCardDuplication( lstRows[ 0 ] .toUInt( ), cardKind ) ) {
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedMonthlyExceed, CPortCmd::AudioMonthlyExceed );
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedContactAdmin, CPortCmd::AudioContactAdmin );
        return bRet;
    }

    QDateTime dtCurrent = QDateTime::currentDateTime( );
    QDateTime dtEndTime = CCommonFunction::String2DateTime( lstRows[ 3 ] );
    QDateTime dtSartTime = CCommonFunction::String2DateTime( lstRows[ 2 ] );
    if ( dtEndTime.toTime_t( ) < dtCurrent.toTime_t( ) ||
         dtCurrent.toTime_t( ) < dtSartTime.toTime_t( ) ) {
        if ( !GetMonthDeadline( dtEndTime, lstRows[ 0 ] ) ) {
            //PlayAudio( byData, vData, CPortCmd::AudioMonthlyExceed );
            QString strText = "已过期";
            pMainWindow->SetAlertMsg( strText );

            //if ( !ExcludeRemoteCardDuplication( lstRows[ 0 ] .toUInt( ), cardKind ) ) {
                PlayAudioDisplayInfo( byData, vData, CPortCmd::LedMonthlyExceed, CPortCmd::AudioMonthlyExceed );
                //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedContactAdmin, CPortCmd::AudioContactAdmin );
            //}

            return bRet;
        }
    }

    QString strTable;
    CCommonFunction::GetTableName( CommonDataType::MonthlyCard, strTable );
    if ( !MonthCardWorkMode( lstRows[ 0 ] ) && !CarInsideOutside( bEnter, lstRows[ 0 ], strTable, byData, vData, byte5, cardKind ) ) {
        return bRet;
    }
    // Open Gate
    QString strCardType = "月租卡";
    ClearListContent( nChannel );
    ControlGate( bEnter, byData, vData, cardKind ); //第一次：通行

    int nDay = CCommonFunction::GetDateTimeDiff( true, 24 * 60 * 60, dtCurrent, dtEndTime );
    if ( nMonthWakeup >= nDay ) {
        int nMaxDay = 999;
        if ( nMaxDay < nDay ) {
            nDay = nMaxDay;
        }
        QString strDays = QString::number( nDay );
        // 第二次：余额
        CardRemainder( byData, vData, strDays, CPortCmd::LedMonthlyRemainder, CPortCmd::AudioMonthlyRemainder, bEnter );
    }

    ProcessPlayDisplayList(  nChannel );

    WriteInOutRecord( bEnter, lstRows[ 0 ], strTable, strCardType, strPlate, byte5, cardKind );

    if ( bLeave ) {
        ControlChargeInfo( lstRows[ 0 ], QDateTime::currentDateTime( ), "0", "0" );
    }

    return bRet;
}

void CProcessData::ClearListContent( int nChannel )
{
    audioList[ nChannel ].clear( );
    ledList[ nChannel ].clear( );
}

void CProcessData::TimeCardPass( int nAmount, int nHour, int nMin, QByteArray& byData )
{
    QByteArray vData;

    vData = QString::number( nAmount ).toAscii( );
    portCmd.GetLedInfo( CPortCmd::LedTimeCardPass, vData );
    portCmd.ParseDownCmd( byData,CPortCmd::DownLED, vData );
    WriteData( byData );

    QString strAmount = QString::number( nAmount );
    ComposeDigitalAudio( vData, strAmount );
    portCmd.GetAudioAddr( CPortCmd::AudioTimeCardPass, vData );
    portCmd.ParseDownCmd( byData, CPortCmd::DownPlayAudio, vData );
    WriteData( byData );

    CCDisplayInfo( byData, vData, nMin, nHour, nAmount, false );
}

bool CProcessData::PictureContrast( QStringList& lstRows, int& nAmount, QByteArray& byData, QString& strCardno )
{
    bool bRet = true;
    char cLevel = GetCanLevel( byData[ 5 ] );
    if ( 1 != cLevel ) {
        return bRet;
    }

    bRet = false;
    if ( pFeeDlg->isVisible( ) ) {
        return bRet;
    }
    //pMainWindow->PopupWindow( CommonDataType::WndPicturContrast );
    QPixmap bmpEnter;
    QPixmap bmpLeave;
    pMainWindow->GetInOutPixmap( bmpEnter, bmpLeave );
    //static CPictureContrastDlg dlg( NULL );
    QString strParkName;
    //pMainWindow->GetParkName( strParkName, cardCan[ strCardno ] );
    pMainWindow->GetParkName( strParkName, byData[ 5 ], 0 );
    pFeeDlg->SetParkID( strParkName );
    pFeeDlg->setModal( true );

    bool bBuffer = GetTimeCardBuffer( ) ;
    if ( bBuffer ) {
        lstRows.append( strCardno ); // tmpcardintime ID
    }
    pFeeDlg->InitDlg( lstRows,  bmpEnter, bmpLeave, byData, bBuffer );

    if ( CPictureContrastDlg::Accepted == pFeeDlg->exec( ) ) {
        pFeeDlg->hide( );
        bRet = true;
        nAmount = pFeeDlg->GetDisAmount( );
    }

    return bRet;
}

bool CProcessData::IfSenseOpenGate( )
{
    pSettings->sync( );
    bool bRet = pSettings->value( "CommonCfg/SenseOpenGate", false ).toBool( );

    return bRet;
}

bool CProcessData::NoCardWork( )
{
    pSettings->sync( );
    bool bRet = pSettings->value( "CommonCfg/NoCardWork", false ).toBool( );

    return bRet;
}

void CProcessData::SenseOpenGate( QByteArray &byRawData )
{
    if ( !IfSenseOpenGate( ) ) {
        return;
    }

    if ( NoCardWork( ) ) {
        QByteArray vData;
        portCmd.ParseDownCmd( byRawData, CPortCmd::DownOpenGate, vData );
    }

    ControlGate( true, byRawData[ 5 ] );
}

void CProcessData::ControlGate( bool bOpen, char cCan ) // Manual
{
    // Open	AA 03 00 4F 00 3E 00 55 // 3F Leave
    // Close	AA 03 00 43 00 3F 00 55

    QByteArray byData;
    byData.append( char( 0xAA ) );
    byData.append( char( 0x03 ) );
    byData.append( char( 0x00 ) );
    byData.append( char( bOpen ? 0x4F : 0x43 ) );
    byData.append( char( 0x00 ) );
    byData.append( cCan );
    byData.append( char( 0x00 ) ); // Checksum
    byData.append( char( 0x55 ) );

    WriteData( byData );

    ///////////////////////////////////////////////////////////////////////////
    int nChannel = GetChannelByCan( cCan );
    if ( bPlateClear[ nChannel ][ 1 ] ) {
        pMainWindow->SetBallotSense( false, nChannel, byData );
    }
    //////////////////////////////////////////////////////////////////////////
}

void CProcessData::ControlGate( bool bEnter, QByteArray &byData, QByteArray &vData, ParkCardType& cardKind ) // Auto
{
    if ( !NoCardWork( ) ) {
        if ( IfSenseOpenGate( ) ) {
            return;
        }
    }

    //while ( GateIfHaveVehicle[ bEnter ] ) {
    //    Sleep( 10 );
    //}

    WaitForSingleObject( g_pReadThread->GetEventObject( bEnter ), 60000 );
    qDebug( ) << "Wait Event" << endl;

    vData.clear( );
    //portCmd.ParseDownCmd( byData, bEnter ? CPortCmd::DownOpenGate : CPortCmd::DownCloseGate, vData );
    portCmd.ParseDownCmd( byData, CPortCmd::DownOpenGate, vData );
    WriteData( byData );

    ///////////////////////////////////////////////////////////////////////////
    int nChannel = GetChannelByCan( byData[ 5 ] );
    if ( bPlateClear[ nChannel ][ 1 ] ) {
        pMainWindow->SetBallotSense( false, nChannel, byData );
    }
    //////////////////////////////////////////////////////////////////////////

    QString strType = "";
    char cAudio[ 2 ] = { 0 };
    if ( CardMonthly == cardKind ) {
        strType = "月租卡";
        cAudio[ 0 ] = 0xFA;
    } else if ( CardSave == cardKind ) {
        strType = "储值卡";
        cAudio[ 0 ] = 0x27;
    } else if ( CardTime == cardKind ) {
        strType = "计时卡";
        cAudio[ 0 ] = 0x84;
        return;
    }

    GetCardTypeData( strType, vData );
    QByteArray vAudio( cAudio, 2 );

    //PlayAudioDisplayInfo( byData,  vData, vAudio, CPortCmd::LedPass, CPortCmd::AudioPass );
    GetPlayDisplayList( byData,  vData, vAudio, CPortCmd::LedPass, CPortCmd::AudioPass, nChannel );
}

void CProcessData::ShuaCard( QByteArray &byData, QByteArray &vData )
{
    portCmd.GetAudioAddr( CPortCmd::AudioShuaCard, vData );
    portCmd.ParseDownCmd( byData, CPortCmd::DownPlayAudio, vData );
    WriteData( byData );
}

void CProcessData::ComposeDigitalAudio( QByteArray &vData, QString &strDigital )
{
    vData.clear( );
    QByteArray tmpData;
    int nLen = strDigital.count( );

    int nTmp = strDigital.toInt( );
    bool bHundred = ( 0 == ( nTmp % 100 ) ); // 0 -- 999
    bool bTen = ( 0 == ( nTmp % 10 ) );
    bool bMiddle = false;

    if ( 3 == nLen && '0' == strDigital[ 1 ] ) {
        bMiddle = true;
    }

    quint8 nCounter= ( quint8 ) ( nLen - 1 );

    for ( int nIndex = 0; nIndex < nLen; nIndex++ ) {
        --nCounter;

        if ( ( nIndex == ( nLen - 1 ) ) && ( !bHundred && bTen ) ) {
            break;
        }

        quint8 cDigital = QString( strDigital[ nIndex ] ).toInt( );
        portCmd.GetAudioDigital( tmpData, cDigital );
        vData.append( tmpData );

        if ( bMiddle && ( 1 == nIndex ) ) {
            continue;
        }

        portCmd.GetAudioChineseChar( tmpData, nCounter );
        vData.append( tmpData );

        if ( bHundred ) {
            break;
        }
    }
}

void CProcessData::GetHourMin( int nMins, int& nHour, int& nMin )
{
    nHour = nMins / 60;
    nMin = ( nMins - nHour * 60 );
}

QString CProcessData::GetFeeStd( QString &strCardNo )
{
    CommonDataType::QEntityHash& ent = CCommonFunction::GetCardEntity( );
    QString strFeeStd = "2";

    if ( ent.contains( strCardNo ) ) {
        CommonDataType::PEntityInfo pInfo = ent[ strCardNo ];
        strFeeStd = pInfo->strFeeStd;
    }

    return strFeeStd;
}

int CProcessData::CalculateFee( QDateTime &dtStart, QDateTime &dtEnd, QString& strCardNumber, char cCan )
{
    int nFee = 0;

    QStringList lstText;
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgTariff );
    QString strName;
    //char cCardCan = cardCan[ strCardNumber ];
    //pMainWindow->GetParkName( strName, cCardCan );
    pMainWindow->GetParkName( strName, cCan, 0 );
    //lstText << ( QString( "PN:%1 CID:%2(%3)" ).arg( strName, strCardNumber, QString::number( cCardCan ) ) );
#if false
    if ( strName.isEmpty( ) ) {
        QStringList lstPark;
        short sCan = ( short ) cCan;
        QString strWhere = QString( "and shebeiadr = %1" ).arg( sCan );
        CLogicInterface::GetInterface( )->GetCurrentPark( lstPark, strWhere );
        if ( 0 < lstPark.count( ) ) {
            strName = lstPark[ 0 ];
        }

        lstText << ( QString( "PN:%1(Raw %2)" ).arg( strName, QString::number( cCan ) ) ) ;
    }
#endif

    QString strType = GetFeeStd( strCardNumber );
    lstText << ( "CarType:" + strType );
    if ( strType.isEmpty( ) ) {
        strType = "2";
        lstText << ( "DefaultType:" + strType );
    }
    //QStringList lstRows;
    //QString strSql = QString( " Select cardfeebz From %1 Where cardno = '%2'" ).arg( strTable, strCardNumber );
    //CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
    //strType = lstRows[ 0 ];

    nFee = CCommonFunction::CalculateFee( *pSet, strName, strType, dtStart, dtEnd, lstText );
    quint64 nTime = ( dtEnd.toMSecsSinceEpoch( ) - dtStart.toMSecsSinceEpoch( ) ) / ( 1000 * 60 );
    if ( ( 0 == nFee ) && ( nTime >= 15 ) ) {
        QString strStart;
        QString strEnd;
        CCommonFunction::DateTime2String( dtStart, strStart );
        CCommonFunction::DateTime2String( dtEnd, strEnd );

        lstText << ( "Start:" + strStart + " End:" + strEnd );
        QStringList lstLogs;
        lstLogs << "收费" << lstText.join( "," ) << strEnd;
        CPmsLog::GetInstance( )->WriteLog( lstLogs );
    }

    return nFee;
}

int CProcessData::CalculateFee( QDateTime &dtStart, QDateTime &dtEnd, QString& strType )
{
    int nFee = 0;

    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgTariff );
    QString strName;
    pMainWindow->GetParkName( strName, 0, 0 );
    if ( strName.isEmpty( ) ) {
        CCommonFunction::MsgBox( pMainWindow, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 "请先选择停车场！", QMessageBox::Information );
        return nFee;
    }

    QStringList lstText;
    nFee = CCommonFunction::CalculateFee( *pSet, strName, strType, dtStart, dtEnd, lstText );
    return nFee;
}

bool CProcessData::ProcessSaveCard( QByteArray& byData, QByteArray& vData, QStringList &lstRows, QString strPlate, ParkCardType& cardKind )
{
    // Select cardno, cardkind, cardstate, cardfee, cardfeebz, cardselfno, cardcomment, cardcreator
    // 该卡已挂失
    // 该卡剩余xx元
    // 该卡金额余额不足
    quint8 byte5 = byData[ 5 ]; // 3E Enetr Park 3F Leave Park
    int nChannel = GetChannelByCan( byte5 );
    bool bEnter = CCommonFunction::ContainAddress( char ( byte5 ), true );
    bool bLeave = !bEnter;

    bool bRet = false;
    int nAmount = 0;
#if false
    QString strState = lstRows[ 2 ];
    if ( 0 == strState.compare( QString( "挂失" ) ) ) {
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardSave, CPortCmd::AudioCardSave );
        PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardLoss, CPortCmd::AudioCardLoss );
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedContactAdmin, CPortCmd::AudioContactAdmin );
        return bRet;
    }
#endif

    QString strTable;
    CCommonFunction::GetTableName( CommonDataType::ValueCard, strTable );
    if ( !CarInsideOutside( bEnter, lstRows[ 0 ], strTable, byData, vData, byte5, cardKind ) ) {
        return bRet;
    }

    QString strFee = lstRows[ 3 ];
    ClearListContent( nChannel );

    if ( bEnter ) {
        // Open Gate
        ControlGate( bEnter, byData, vData, cardKind ); // 第一次
        // 第二次
        CardRemainder( byData, vData, strFee, CPortCmd::LedSaveRemainder, CPortCmd::AudioSaveRemainder, bEnter );
    } else if ( bLeave ) {

        int nRemainder = strFee.toInt( );
        QStringList lstInOut;
        //QString strWhere = QString( " Where cardno = '%1' And intime in \
        //                            ( Select intime From ( Select Max( intime ) As intime \
        //                                                   From stoprd \
        //                                                   Where cardno = '%2') tmp )" ).arg( lstRows[ 0 ], lstRows[ 0 ] );

        QString strWhere = QString( " Where stoprdid = ( Select stoprdid From cardstoprdid \
                                                           Where cardno = '%1' )" ).arg( lstRows[ 0 ] );
        CLogicInterface::GetInterface( )->OperateInOutRecord( lstInOut, CommonDataType::SelectData, strWhere );
        if ( 0 == lstInOut.count( ) ) {
            //qDebug << QString( "Not enter" ) << endl;
            return bRet;
        }
        QDateTime dtEnd = QDateTime::currentDateTime( );
        QDateTime dtStart = CCommonFunction::String2DateTime( lstInOut[ 1 ] );
        int nMins = CCommonFunction::GetDateTimeDiff( false, 60, dtStart, dtEnd );
        int nHour;
        int nMin;
        GetHourMin( nMins, nHour, nMin );
        QString strTable;
        CCommonFunction::GetTableName( CommonDataType::ValueCard, strTable );
        nAmount = CalculateFee( dtStart, dtEnd, lstRows[ 0 ], byte5 );
        nRemainder -= nAmount;
        if ( 0 > nRemainder ) {
            PlayAudioDisplayInfo( byData, vData, CPortCmd::LedSaveRemainderInsufficient, CPortCmd::AudioSaveRemainderInsufficient );
            //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedRenewal, CPortCmd::AudioRenewal );
            return bRet;
        }// else if ( 5 > nRemainder ) {
        //    PlayAudioDisplayInfo( byData, vData, CPortCmd::LedRecharge, CPortCmd::AudioRecharge );
        //}

        lstRows[ 3 ] = QString::number( nRemainder );
        strFee = lstRows[ 3 ];

        // Open Gate
        ControlGate( bEnter, byData, vData, cardKind );// 第一次
        //CardRemainder( byData, vData, strFee, CPortCmd::LedSaveRemainder, CPortCmd::AudioSaveRemainder );
        CardExitInfo( byData, vData, true, nMin, nHour, nAmount, nRemainder, bEnter ); // 第二次
        CCDisplayInfo( byData, vData, nMin, nHour, nAmount, bEnter );

        CLogicInterface::GetInterface( )->UpdateSaveCardRemainder( false, nAmount, lstRows[ 0 ] );
        strWhere = QString( " Where cardno = '%1' " ).arg( lstRows[ 0 ] );
        CLogicInterface::GetInterface( )->OperateCardInfo( lstRows, CommonDataType::ValueCard,
                                                           CommonDataType::UpdateData, strWhere );

        ControlChargeInfo( lstRows[ 0 ], QDateTime::currentDateTime( ), QString::number( nAmount ), "0" );
    }

    ProcessPlayDisplayList( nChannel );
    QString strCardType = "储值卡";
    WriteInOutRecord( bEnter, lstRows[ 0 ], strTable, strCardType, strPlate, byte5, cardKind, nAmount );

    return bRet;
}

void CProcessData::CardRemainder( QByteArray &byData, QByteArray &vData, QString& strFee,
                                  CPortCmd::LedInfo led, CPortCmd::AudioAddress audio, bool bEnter )
{
    QByteArray byDataLed = strFee.toAscii( );
    ComposeDigitalAudio( vData, strFee );
    //PlayAudioDisplayInfo( byData, byDataLed, vData, led, audio );
    int nChannel = GetChannelByCan( byData[ 5 ] );
    GetPlayDisplayList( byData, byDataLed, vData, led, audio, nChannel );
}

void CProcessData::CardExitInfo( QByteArray &byData, QByteArray &vData, bool bSave,
                                 int nMin, int nHour, int nAmount, int nRemainder, bool bEnter )
{
    char cLevel = GetCanLevel( byData[ 5 ] );
    int nChannel = GetChannelByCan( byData[ 5 ] );
    if ( 1 != cLevel ) {
        return;
    }
    QString strMin = QString::number( nMin );
    QString strHour = QString::number( nHour );
    QString strAmount = QString::number( nAmount );
    QString strRemainder = QString::number( nRemainder );
    //byData[ 5 ] = 0x3E;
    CPortCmd::LedInfo infoType = bSave ? CPortCmd::LedSaveCardExit : CPortCmd::LedTimeCardExit;

    portCmd.GetLedInfo2( infoType, vData, &strHour, &strMin,
                         &strAmount, bSave ? &strRemainder : NULL, NULL );
    portCmd.ParseDownCmd( byData, CPortCmd::DownLED, vData );
    if ( !bSave ) {
        WriteData( byData );
    } else {
        ledList[ nChannel ].append( byData );
    }

    QByteArray byAmount;
    ComposeDigitalAudio( byAmount, strAmount );

    QByteArray byRemainder;
    ComposeDigitalAudio( byRemainder, strRemainder );

    QByteArray* pRemainder = bSave ? &byRemainder : NULL;
    CPortCmd::AudioAddress audioType = bSave ? CPortCmd::AudioSaveCardExit : CPortCmd::AudioTimeCardExit;
    portCmd.GetAudioAddr2( audioType, &byAmount, pRemainder, NULL );
    portCmd.ParseDownCmd( byData, CPortCmd::DownPlayAudio, byAmount );

    if ( !bSave ) {
        WriteData( byData );
    } else {
        audioList[ nChannel ].append( byData );
    }
}

void CProcessData::CCDisplayInfo( QByteArray& byData, QByteArray& vData,
                                  int nMin, int nHour, int nAmount, bool bEnter )
{
    char cLevel = GetCanLevel( byData[ 5 ] );
    if ( 1 != cLevel ) {
        return;
    }
    //QString strMin = QString::number( nMin );
    //QString strHour = QString::number( nHour );
    //QString strAmount = QString::number( nAmount );
    QByteArray byteCC = byData;

    GetCCDisplayInfo( vData, nHour, nMin, nAmount );
    portCmd.ParseDownCmd( byteCC, CPortCmd::DownCCDisplay, vData );
    WriteData( byteCC );

#if false
    byData[ 5 ] = bEnter ? 0x3E : 0x3F;
    portCmd.GetLedInfo2( CPortCmd::LedCCDisplay, vData, &strHour, &strMin, &strAmount, NULL );
    portCmd.ParseDownCmd( byData, CPortCmd::DownLED, vData );
    WriteData( byData );

    QByteArray byMin;

    if ( 0 != nMin ) {
        ComposeDigitalAudio( byMin, strMin );
    }

    QByteArray byHour;
    if ( 0 != nHour ) {
        ComposeDigitalAudio( byHour, strHour );
    }

    QByteArray byAmount;
    ComposeDigitalAudio( byAmount, strAmount );

    portCmd.GetAudioAddr2( CPortCmd::AudioCCDisplay, &byHour, &byMin, &byAmount, NULL );
    portCmd.ParseDownCmd( byData, CPortCmd::DownPlayAudio, byHour );
    WriteData( byData );
#endif
}

void CProcessData::ControlChargeInfo(QString &strCardNumber, QDateTime dtLeave, QString strAmount, QString strRetention)
{
    return;
    //QString strSql = QString( "Select Max( intime ) From %1 Where cardno = '%2' " ).arg(
    //            GetTimeCardBuffer( ) ? "tmpcardintime" : "stoprd", strCardNumber );

    QString strSql = QString( "Select intime From %1 Where stoprdid = \
                              ( Select stoprdid from cardstoprdid where cardno = '%2')" ).arg(
                              GetTimeCardBuffer( ) ? "tmpcardintime" : "stoprd", strCardNumber );

    QStringList strInfo;
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, strInfo );
    if ( 0 >= strInfo.count( ) ) {
        return;
    }

    QDateTime dtEnter = QDateTime::fromString( strInfo[ 0 ], Qt::SystemLocaleDate );
    uint nSeconds = dtLeave.toTime_t( ) - dtEnter.toTime_t( );
    uint nOneHour = 60 * 60 ;
    uint nHour = nSeconds / nOneHour;
    uint nMinute = ( nSeconds - nHour * nOneHour ) / 60;

    QString strFormat = QString( "yyyy年M月d日 H时m分" );
    strInfo.clear( );
    strInfo << dtEnter.toString( strFormat )
            << dtLeave.toString( strFormat )
            << QString( "%1小时%2分" ).arg( QString::number( nHour ), QString::number( nMinute ) )
            << strAmount
            << strRetention;

    pMainWindow->ControlChargeInfo( strInfo );
}

void CProcessData::GetCCDisplayInfo( QByteArray &byData, int nHour, int nMin, int nAmout )
{
    byData.clear( );
    bool b1 = false;
    bool b2 = false;

    quint8 nData1 = nMin / 10;
    b1 = ( 0 == nData1 );
    quint8 nData2 = nMin - nData1 * 10;
    nData2 += ( 1 << 7);
    byData.append( nData2 );
    byData.append( b1 ? 0x0F : nData1 );

    nData1 = nHour / 100;
    b1 = ( 0 == nData1 );
    nData2 = ( nHour - nData1 * 100 ) / 10;
    b2 = ( 0 == nData2 );
    quint8 nData3 = nHour - nData1 * 100 - nData2 * 10;
    byData.append( nData3 );
    byData.append( ( b1 && b2 ) ? 0x0F : nData2 );
    byData.append( b1 ? 0x0F : nData1 );

    nData1 = nAmout / 100;
    b1 = ( 0 == nData1 );
    nData2 = ( nAmout - nData1 * 100 ) / 10;
    b2 = ( 0 == nData2 );
    nData3 = nAmout - nData1 * 100 - nData2 * 10;
    byData.append( nData3 );
    byData.append( ( b1 && b2 ) ? 0x0F : nData2 );
    byData.append( b1 ? 0x0F : nData1 );
}

void CProcessData::WriteFeeData( QString &strCardType, QString &strCardNo, int nAmount, QString &strDateTime )
{
    //feenumb, timelen, feetime, feekind, feeoperator, cardno
    QStringList lstData;
    lstData << QString::number( nAmount )
            << "0"
            << strDateTime
            << strCardType
            << pMainWindow->GetUserName( )
            << strCardNo;

    QString strWhere = "";

    CLogicInterface::GetInterface( )->OperateChargeRecord( lstData, CommonDataType::InsertData, strWhere );
}

void CProcessData::GetChannelName( bool bEnter, char cCan, QString& strChannel )
{
    QStringList& lstChannel = bEnter ? inChannelInfo : outChannelInfo;
    if ( 0 == lstChannel.count( ) ) {
        return;
    }

    int nCols = 5;
    int nRows = lstChannel.count( ) / nCols;

    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        QString& strCan = lstChannel[ nIndex * nCols  + 3 ];
        if ( cCan == ( char ) strCan.toShort( ) ) {
           strChannel =  lstChannel[ nIndex * nCols ];
           break;
        }
    }
}

void CProcessData::BroadcastRecord( QString& strCardNumber, QDateTime& dtCurrent, int nCardTypeID,
                                    QString strPlate, QString& strCardType, QString& strChannel, char cCan )
{
    QStringList lstData;
    QString strTime;
    QString strDate;
    QTime time = dtCurrent.time( );
    QDate date = dtCurrent.date( );
    CCommonFunction::Time2String( time, strTime );
    CCommonFunction::Date2String( date, strDate );
    QString strCan = QString::number( cCan );
    bool bEnter = ( 0 != ( cCan % 2 ) );

    QString strLoop = "127.0.0.1";
    QString strDbIP = pSettings->value( "Database/Host",  strLoop ).toString( );

    lstData << strPlate << strTime << strCardType << strChannel <<
            strCardNumber << ( bEnter ? "1" : "0" )
            << QString::number( nCardTypeID )
            << strDate << strCan << strCardNumber << strDbIP;
    CNetwork::Singleton( ).BroadcastDatagram( CommonDataType::DGPassRecord, lstData );
}

void CProcessData::SpaceChange( bool bEnter, char cCan )
{
    // CAN / PARKINDEX / PARKNUM / PARKNAME
    QString strName = "";
    pMainWindow->GetParkName( strName, cCan, 0 );
    QString strSql = QString( "call SurplusSpace( %1, %2 )" ).arg( QString::number( !bEnter ), strName );
    CLogicInterface::GetInterface( )->ExecuteSql( strSql );

    strSql = QString( "Select usedSpace from parkinfo where parkindex = %1" ).arg( strName );
    QStringList lstData;
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData );
    pMainWindow->GetParkName( strName, cCan, 1 );
    int nTotalParkSpace = strName.toInt( );
    int nFree = 0;
    if ( 0 < lstData.count( ) ) {
        int nUsed = lstData[ 0 ].toInt( );
        nFree = nTotalParkSpace - nUsed;
    }

    bool bFull = ( 0 >= nFree );
    QString strInfo = bFull ? "车位已满！" : QString( "空闲车位：%1" ).arg( QString::number( nFree ) );
    ParkspaceFull( bFull, strInfo, cCan );
}

bool CProcessData::MonthNoCardWorkMode( )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    bool bRet = pSet->value( "CommonCfg/NoCardWork", false ).toBool( );

    return bRet;
}

bool CProcessData::NoPlateOpenGate( )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSysSet );
    bool bRet = !pSet->value( "CarLicence/AutoRecognize", false ).toBool( );

    return bRet;
}

bool CProcessData::MonthCardWorkMode( QString& strCardNo )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSysSet );
    bool bRet = pSet->value( "CommonSet/MonthlyWorkMode", false ).toBool( );

    //if ( !bRet ) {
        CommonDataType::PEntityInfo pInfo = CCommonFunction::GetCardEntity( ).value( strCardNo );
        if ( NULL != pInfo ) {
            bRet &= pInfo->bMIMO;
        }
    //}

    return bRet;
}

int CProcessData::GetMinFee( char cCan )
{
    QString strName;
    pMainWindow->GetParkName( strName, cCan, 0 );

    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgTariff );
    int nMinFee = pSet->value( QString( "%1/2/rule1FootInner" ).arg( strName ), 0 ).toInt( );

    return nMinFee / 10;
}

bool CProcessData::GateNoCardWork( QByteArray& byData, QString& strPlate,
                                   char cCan, QString& strCardNo,
                                   QString& strType, QString& strChannel, int& nFee )
{
    bool bRet = MonthNoCardWorkMode( );

    if ( !bRet ) { // 纯地感开闸，不收费
        return true;
    }

    QString strSql = QString( "Select NoCardWork( '%1', %2 )" ).arg( strPlate, QString::number( cCan ) );
    QStringList lstRow;
    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRow );
    if ( 0 == lstRow.count( ) || lstRow.at( 0 ).isEmpty( ) ) {
        return false;
    }

    // month,expire,day,enter
    // time,enter,unknown,tmpid,stoprdid,intime,inchannel,outchannel
    lstRow = lstRow.at( 0 ).split( "," );
    const QString& strCardType= lstRow.at( 0 );

    QByteArray vData;
    strType = "无卡工作";
    bool bEnter = true;
    ParkCardType cardType = CardNone;
    int nChannel = GetChannelByCan( byData[ 5 ] );

    if ( "month" == strCardType ) {
        if ( "1" == lstRow.at( 1 ) ) {
            PlayAudioDisplayInfo( byData, vData, CPortCmd::LedMonthlyExceed, CPortCmd::AudioMonthlyExceed );
            return false;
        }

        cardType = CardMonthly;
        ClearListContent( nChannel );
        bEnter = ( "1" == lstRow.at( 3 ) );
        QString strDays = lstRow.at( 2 );
        int nDay = strDays.toInt( );
        if ( nMonthWakeup >= nDay ) {
            int nMaxDay = 999;
            if ( nMaxDay < nDay ) {
                nDay = nMaxDay;
            }

            CardRemainder( byData, vData, strDays, CPortCmd::LedMonthlyRemainder, CPortCmd::AudioMonthlyRemainder, bEnter );
        }

        //ProcessPlayDisplayList( nChannel );
    } else if ( "time" == strCardType ) {
        bEnter = ( "1" == lstRow.at( 1 ) );
        cardType = CardTime;

        if ( !bEnter ) { // leave
            bool bUnknown = false;
            if ( "1" == lstRow.at( 2 ) ) { // 未知
                //return false;
                bUnknown = true;
                lstRow << "0" << "0" << "" << "";
            }

            if ( pFeeDlg->isVisible( ) ) {
                //return false; // Only let one car pass
                pFeeDlg->DefaultClicked( );
                Sleep( 1000 );
            }

            QString strTmpID = lstRow[ 4 ];
            QDateTime dtEnd = QDateTime::currentDateTime( );
            QDateTime dtStart;// = CCommonFunction::String2DateTime( lstRow[ 5 ] );
            int nMins = 0;// = CCommonFunction::GetDateTimeDiff( false, 60, dtStart, dtEnd );

            if ( !bUnknown ) {
                dtStart = CCommonFunction::String2DateTime( lstRow[ 5 ] );
                nMins = CCommonFunction::GetDateTimeDiff( false, 60, dtStart, dtEnd );
            }

            if ( 0 > nMins ) {
                CCommonFunction::MsgBox( NULL, "提示", "进入时间大于离开时间", QMessageBox::Information );
                return false;
            }

            int nHour;
            int nMin;
            char byte5 = byData[ 5 ];
            GetHourMin( nMins, nHour, nMin );

            QString strTable;
            CCommonFunction::GetTableName( CommonDataType::TimeCard, strTable );

            int nAmount = 0;//CalculateFee( dtStart, dtEnd, strCardNo, byte5 );
            if ( !bUnknown ) {
                nAmount = CalculateFee( dtStart, dtEnd, strCardNo, byte5 );
            } else {
                nAmount = GetMinFee( byData[ 5 ] );
            }

            nFee = nAmount;

            pFeeDlg->SetParams( byData, vData, nMin, nHour, nAmount, false );

            //////////////////////////////////

            QStringList lstInit;
            QString strParkName = "";
            pMainWindow->GetParkName( strParkName, byData[ 5 ], 0 );
            //QString strChannel = "未知";
            //GetChannelName( false, byte5, strChannel );

            //CCommonFunction::GetAllChannels( lstChan, strParkName, bEnter );
            //cardno, intime, inshebeiname, idtmpcardintime
            QString strEnd = dtEnd.toString( "yyyy-MM-dd HH:mm:ss" );
            lstInit << strCardNo << strType;
            lstInit << lstRow[ 6 ] << lstRow[ 5 ];
            lstInit << strChannel << strEnd;
            lstInit << QString::number( nHour ) << QString::number( nMin);
            lstInit << QString::number( nAmount );
            lstInit << strTable << strParkName;
            lstInit << lstRow[ 5 ] << strEnd << strPlate;
            lstInit << GetFeeStd( strCardNo );

            bool bGate = PictureContrast( lstInit, nAmount, byData, strTmpID );
            if ( bGate ) {
                pMainWindow->UpdateStatistics( nAmount, 2 );
                pMainWindow->UpdateStatistics( pFeeDlg->GetAmount( ) - nAmount, 5 );

                //ControlGate( false, byData, vData, cardKind );
            } else {
                return bRet;
            }

            QString strDateTime;
            CCommonFunction::DateTime2String( dtEnd, strDateTime );
            WriteFeeData( strType, strCardNo, nAmount, strDateTime );
            // Confirm to pass
            //ControlChargeInfo( strCardNo, QDateTime::currentDateTime( ), QString::number( nAmount ), "1" );
        } else {
            //ControlGate( bEnter, byData, vData, cardKind );
            //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedTimeCardEnter, CPortCmd::AudioTimeCardEnter );
        }
    } else {
        bRet = false;
    }

    if ( bRet ) {
        ControlGate( bEnter, byData, vData, cardType );
    }

    if ( CardMonthly == cardType ) {
        ProcessPlayDisplayList(  nChannel );
    } else if ( CardTime == cardType && bEnter ) {
        PlayAudioDisplayInfo( byData, vData, CPortCmd::LedTimeCardEnter, CPortCmd::AudioTimeCardEnter );
    }

    return bRet;
}

bool CProcessData::WriteInOutRecord( QByteArray& byData ) // 地感开闸
{
    bool bRet = false;

    if ( !IfSenseOpenGate( ) ) {
        return bRet;
    }

    int nIndex = 5;
    if ( nIndex >= byData.count( ) ) {
        return bRet;
    }

    char cCan = byData[ nIndex ];
    bool bEnter = ( 0 != (  cCan % 2 ) );
    int nChannel = GetChannelByCan( cCan );
    QString strPlate = strCurrentPlate[ nChannel ];
    strCurrentPlate[ nChannel ].clear( );
    char cLevel = GetCanLevel( cCan );

    if ( !hashCanChannel.keys( ).contains( cCan ) ) {
        QString strWhere = QString( "And shebeiadr = %1" ).arg( ( short ) cCan );
        GetCan2Channel( strWhere );
    }

    QString strChannel = hashCanChannel.value( cCan );

    if ( strPlate.isEmpty( ) ) {
        strPlate = "未知";
    }

    QString strSql = "";
    QString strDateTime = "";
    QDateTime dtCurrent = QDateTime::currentDateTime( );
    CCommonFunction::DateTime2String( dtCurrent, strDateTime );
    bool bUnknown = ( "未知" == strPlate );
    QString strCardNumber = bUnknown ? QString::number( dtCurrent.toMSecsSinceEpoch( ) ) : strPlate;
    QString strCardType = "自由卡";

    bool bGarage = ( 1 < cLevel );

    if ( 1 == cLevel ) { //最外层车库
        QString strIn = bEnter ? "in" : "out";
        QString strOut = bEnter ? "": "out";
        strSql = QString( "Insert Into stoprd ( %1shebeiname, %2time, cardno, carcp%3, cardkind ) Values (  \
                          '%4', '%5', '%6', '%7', '%8' ) " );
        strSql = strSql.arg( strIn, strIn, strOut, strChannel, strDateTime, strCardNumber, strPlate, strCardType );

        if ( !bEnter && !bUnknown ) {
            strSql = QString( "update stoprd set outshebeiname = '%1', outtime = '%2', carcpout = '%3' where  stoprdid in ( select stoprdid from cardstoprdid where cardno = '%4' )" ).arg(
                        strChannel, strDateTime, strPlate, strCardNumber );
        }

        //SpaceChange( bEnter, cCan );
    } else { //库中库
        strSql = QString( "Insert Into GarageInGarage( CardID, ChannelName, Level, DateTime, \
                          InOutFlag, PlateID, CardKind ) VALUES( '%1', '%2', %3, '%4', %5, '%6', '%7' )" ).arg( strCardNumber,
                                                                                                                     strChannel, QString::number( cLevel ),
                                                                                                                     strDateTime, bEnter ? "1" : "0", strPlate, strCardType );
    }

    int nFee = 0;

    if ( !bGarage ) {
        bRet = GateNoCardWork( byData, strPlate, cCan, strCardNumber, strCardType, strChannel, nFee );
        if ( !bRet ) {
            return bRet;
        }

        SpaceChange( bEnter, cCan );
        BroadcastRecord( strCardNumber, dtCurrent, bUnknown ? 10 : 11, strPlate, strCardType, strChannel, cCan );
    }

    if ( !strSql.isEmpty( ) ) {
        QString strPath = "";
        GetCaptureFile( strPath, strCardNumber, nChannel, CommonDataType::CaptureJPG );
        CaptureImage( strCardNumber, nChannel, CommonDataType::CaptureJPG );
        QFile file( strPath );
        QByteArray byImage;
        if ( file.open( QFile::ReadWrite ) ) {
          byImage = file.readAll( );
          file.close( );
        }

        QString strHex( byImage.toBase64( ) );
        strSql = "Select InsertFreeCardData( '%1', '%2', '%3', '%4', %5, %6, '%7', %8, %9, '%10' )";
        strSql = strSql.arg( strCardNumber, strDateTime, strChannel,
                             strPlate, QString::number( cLevel ),
                             QString::number( bEnter ), strCardType,
                             QString::number( nFee ), QString::number( bNocardworkUnknown ) );
        strSql = strSql.arg( strHex );

        //CLogicInterface::GetInterface( )->ExecuteSql( strSql );
        SendDbWriteMessage( CDbEvent::SQLInternal, strSql, CCommonFunction::GetHistoryDb( ), false, true );
        /////////////////////////////
        //CLogicInterface::GetInterface( )->ExecuteSql( strSql );
        //CaptureImage( strCardNumber, nChannel, CommonDataType::CaptureJPG );
        //ControlVehicleImage( strCardNumber, true, nChannel,  cLevel, true, false, "", bGarage );
        DeleteCapturedFile( strCardNumber, nChannel, bEnter, dtCurrent, strPlate );
    }

    QStringList lstData;
    lstData << "" << CCommonFunction::GetParkID( ) << "1" << strPlate << ( bEnter ? "1" : "0" ) << strDateTime << "2";
    CheckBlacklist( lstData );

    return !bRet;
}

void CProcessData::GetCan2Channel( QString &strWhere )
{
    QString strSql = QString( "select shebeiadr, shebeiname from parkadmin.roadconerinfo where video1ip = '%1' %2" ).arg(
                                                   CCommonFunction::GetHostIP( ), strWhere );
    QStringList lstRows;
    int nRet = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
    if ( 0 >= nRet ) {
        return;
    }

    int nCols = 2;
    char cCan;

    for ( int nIndex = 0; nIndex < nRet; nIndex += nCols ) {
        const QString& strValue = lstRows[ nIndex++  ];
        cCan = ( char ) strValue.toShort( );
        hashCanChannel.insert( cCan, lstRows[ nIndex ] );
    }
}

void CProcessData::UploadData( QString &strPlate, QString &strCardID,
                               bool bEnter, QString &strDateTime,
                               QByteArray& byImageData )
{
    if ( !bUploadData ) {
        return;
    }

    if ( NULL == pUploadDataThread ) {
        pUploadDataThread = QUploadDataThread::CreateInstance( );
    }

    QStringList lstParams;

    lstParams << strPlate << ( bEnter ? "1" : "0" ) << strDateTime << strCardID;


    pUploadDataThread->PostUploadDataEvent( lstParams, byImageData );
}

void CProcessData::WriteInOutRecord( bool bEnter, QString& strCardNumber, QString& strTable,
                                     QString& strCardType, QString strPlate, char cCan, ParkCardType& cardKind, int nAmount )
{
    if ( bEnter ) {
        cardCan.insert( strCardNumber, cCan );
    }

    char cLevel = GetCanLevel( cCan );
    int nChannel = GetChannelByCan( cCan );
    QString strChannel = "未知";
    GetChannelName( bEnter, cCan, strChannel );
    QString strSql;
    QString strDateTime = "";
    QDateTime dtCurrent = QDateTime::currentDateTime( );
    CCommonFunction::DateTime2String( dtCurrent, strDateTime );

    bool bMonthCard = ( CardMonthly == cardKind );
    bool bMonthMultipleCard = bMonthCard && MonthCardWorkMode( strCardNumber );
    QString strMonthMultipleCardNo = "%1(%2)";
    int nType = 1;

    if ( bMonthMultipleCard ) {
        // 多进多出 自编卡号
        //strMonthMultipleCardNo = strMonthMultipleCardNo.arg( strCardNumber, QString::number( dtCurrent.toMSecsSinceEpoch( ) ) );
        strMonthMultipleCardNo = strCardNumber;
        nType = 0;
    }

    if ( 1 != cLevel ) {  
        strSql = QString( "Insert IGNORE Into GarageInGarage( CardID, ChannelName, Level, DateTime, \
                          InOutFlag, PlateID, CardKind ) VALUES( '%1', '%2', %3, '%4', %5, '%6', '%7' )" ).arg(
                bMonthMultipleCard ? strMonthMultipleCardNo : strCardNumber,
                 strChannel, QString::number( cLevel ),
                 strDateTime, bEnter ? "1" : "0", strPlate, strCardType );
        if ( GetDirectDb( ) ) {
            CLogicInterface::GetInterface( )->ExecuteSql( strSql );
        } else {
            SendDbWriteMessage( CDbEvent::SQLInternal, strSql, CCommonFunction::GetHistoryDb( ), false, false );
        }

        ControlVehicleImage( strCardNumber, true, nChannel, nType, cLevel, bMonthMultipleCard,
                             bMonthCard, strMonthMultipleCardNo, true );
        DeleteCapturedFile( strCardNumber, nChannel,bEnter,  dtCurrent, strPlate );
        return;
    }
    //inshebeiname, intime, outshebeiname, outtime, cardno

    //QTime myTime = dtCurrent.time( );
    if ( singleChannelHash.contains( strPlate ) ) {
        QVector< QDateTime >& vec = singleChannelHash[ strPlate ];
        if ( bEnter ) {
            vec[ 0 ] = dtCurrent;
            //vec[ 1 ] = QTime( );
        } else {
            //vec[ 0 ] = QTime( );
            vec[ 1 ] = dtCurrent;
        }
    } else {
        QVector< QDateTime > vec( 2 ); // InTime OutTime

        if ( bEnter ) {
            vec[ 0 ] = dtCurrent;
            vec[ 1 ] = QDateTime( );
        } else {
            vec[ 0 ] = QDateTime( );
            vec[ 1 ] = dtCurrent;
        }
        singleChannelHash.insert( strPlate, vec );
    }

#if false
    pMainWindow->GetParkName( strName );
    CCommonFunction::GetAllChannels( lstRows, strName, bEnter );
    if ( 0 < lstRows.count( ) ) {
        strChannel = lstRows[ 0 ];
    }
#endif

    int nRealAmount = 0;
    if ( !bMonthCard && !bEnter ) {
        QString strTmp = strCardType + "%1";

        if ( CardTime == cardKind ) {
            strTmp = strTmp.arg( "收费" );
            nRealAmount = pFeeDlg->GetAmount( );
        } else if ( CardSave == cardKind ) {
            strTmp = strTmp.arg( "扣费" );
        }

        WriteFeeData( strTmp, strCardNumber, nAmount, strDateTime );
    }

    //QString strPlate = strCurrentPlate[ bEnter ];

    if ( strPlate.isEmpty( ) ) {
        GetPlate( strCardNumber, strPlate );
    }

    if ( strPlate.isEmpty( ) ) {
        strPlate = "未知";
    }

    qDebug( ) << " WriteInOutRecord " << strChannel << endl;

    ////////////////////////Broadcast data
#if false
    QStringList lstData;
    QString strTime;
    QString strDate;
    QTime time = dtCurrent.time( );
    QDate date = dtCurrent.date( );
    CCommonFunction::Time2String( time, strTime );
    CCommonFunction::Date2String( date, strDate );
    QString strCan = QString::number( cCan );
    lstData << strPlate << strTime << strCardType << strChannel <<
            strCardNumber << ( bEnter ? "1" : "0" )
            << QString::number( cardType[ bEnter ] )
            << strDate << strCan << strCardNumber;
    CNetwork::Singleton( ).BroadcastDatagram( CommonDataType::DGPassRecord, lstData );
#endif

    if ( bMonthMultipleCard ) {
        BroadcastRecord( strMonthMultipleCardNo, dtCurrent, 10, strPlate, strCardType, strChannel, cCan );
        //BroadcastRecord( strCardNumber, dtCurrent, cardKind, strPlate, strCardType, strChannel, cCan );
    } else {
        BroadcastRecord( strCardNumber, dtCurrent, cardKind, strPlate, strCardType, strChannel, cCan );
    }
    /////////////////////////////////
    if ( bMonthMultipleCard ) {
        // MIMO 记录分开写
        QString strIn = bEnter ? "in" : "out";
        QString strOut = bEnter ? "": "out";
        strSql = QString( "Insert IGNORE Into stoprd ( %1shebeiname, %2time, cardno, carcp%3, cardkind, childrdindx ) Values (  \
                          '%4', '%5', '%6', '%7', '%8', 1 ) " );
        strSql = strSql.arg( strIn, strIn, strOut, strChannel, strDateTime, strMonthMultipleCardNo, strPlate, strCardType );
#if false // 合成一条
        if ( bEnter ) {
            strSql = QString( "select a.stoprdid from CardStoprdID a, stoprd b \
                              where a.cardno = '%1' and a.stoprdid = b.stoprdid \
                              and intime is not null and outtime is null and cardkind = '月租卡'" ).arg( strMonthMultipleCardNo );
            QStringList lstRow;
            CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRow );

            if ( 0 == lstRow.count( ) ) {
                strSql = QString( "Insert IGNORE Into stoprd ( inshebeiname, intime, cardno, carcp, cardkind ) Values ( '%1', '%2', '%3', '%4', '%5' ) " );
                strSql = strSql.arg( strChannel, strDateTime, strCardNumber, strPlate, strCardType );
            }
            else {
                strSql = QString( "UPDATE IGNORE stoprd set inshebeiname = '%1', intime = '%2', cardno = '%3', carcp = '%4', cardkind = '%5'\
                                  where stoprdid = %6" );
                strSql = strSql.arg( strChannel, strDateTime, strCardNumber, strPlate, strCardType, lstRow.at( 0 ) );
            }
        } else {
            strSql = QString( "select a.stoprdid from CardStoprdID a, stoprd b \
                              where a.cardno = '%1' and a.stoprdid = b.stoprdid AND \
                              cardkind = '月租卡'" ).arg( strMonthMultipleCardNo );
            QStringList lstRow;
            CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRow );

            if ( 0 == lstRow.count( ) ) {
                strSql = QString( "Insert IGNORE Into stoprd ( outshebeiname, outtime, cardno, carcpout, cardkind ) Values (  \
                              '%1', '%2', '%3', '%4', '%5' ) " );
                strSql = strSql.arg( strChannel, strDateTime, strMonthMultipleCardNo, strPlate, strCardType );
            } else {
                strSql = QString( "Update IGNORE stoprd Set outshebeiname = '%1', outtime = '%2', carcpout = '%3', cardkind = '%4', feefactnum = %5, \
                                  feenum = %6, feetime = '%7', feeoperator = '%8', feekind = '%9', feezkyy = '%10' \
                                  Where stoprdid = \
                        ( select stoprdid from CardStoprdID where cardno = '%11' ) " );
                strSql = strSql.arg( strChannel, strDateTime, strPlate, strCardType, QString::number( nAmount ),
                                                  QString::number( nRealAmount ), strDateTime, pMainWindow->GetUserName( ) );

                strSql = strSql.arg( bMonthCard ? "" : pFeeDlg->GetFeeRateType( ),
                                              bMonthCard ? "无优惠" : pFeeDlg->GetDiscountType( ),
                                              strCardNumber );
            }

        }
#endif
    } else {
        if ( bEnter ) {
            strSql = QString( "Insert IGNORE Into stoprd ( inshebeiname, intime, cardno, carcp, cardkind ) Values ( '%1', '%2', '%3', '%4', '%5' ) " );
            //cardCan.insert( strCardNumber, cCan );

        } else {
            if ( CardTime == cardKind && GetTimeCardBuffer( ) ) {
                //strSql = QString( "Update IGNORE stoprd Set outshebeiname = '%1', outtime = '%2', carcpout = '%3', cardkind = '%4', feefactnum = %5, \
                //                  feenum = %6, feetime = '%7', feeoperator = '%8', feekind = '%9', feezkyy = '%10' \
               //                   where stoprdid in ( select stoprdid from CardStoprdID where \
               //                   cardno = '%11' ) " );

                strSql = QString( "Update IGNORE stoprd \
                        Set outshebeiname = '%1', outtime = '%2', carcpout = '%3', \
                        cardkind = '%4', feefactnum = %5, feenum = %6, \
                        feetime = '%7', feeoperator = '%8', \
                        feekind = '%9', feezkyy = '%10'  where stoprdid = \
                        ( select stoprdid from CardStoprdID where cardno = '%11' )" );
            } else {
            strSql = QString( "Update IGNORE stoprd Set outshebeiname = '%1', outtime = '%2', carcpout = '%3', cardkind = '%4', feefactnum = %5, \
                              feenum = %6, feetime = '%7', feeoperator = '%8', feekind = '%9', feezkyy = '%10' \
                              Where stoprdid = \
                    ( select stoprdid from CardStoprdID where cardno = '%11' ) " );
            }
        }

        if ( bEnter ) {
            strSql = strSql.arg( strChannel, strDateTime, strCardNumber, strPlate, strCardType );
        } else {
            if ( CardTime == cardKind && GetTimeCardBuffer( ) ) {
                strSql = strSql.arg( strChannel, strDateTime, strPlate, strCardType, QString::number( nAmount ),
                                                  QString::number( nRealAmount ), strDateTime, pMainWindow->GetUserName( ) );
                strSql = strSql.arg( bMonthCard ? "" : pFeeDlg->GetFeeRateType( ),
                                                  bMonthCard ? "无优惠" : pFeeDlg->GetDiscountType( ), strCardNumber );
            } else {
                strSql = strSql.arg( strChannel, strDateTime, strPlate, strCardType, QString::number( nAmount ),
                                                  QString::number( nRealAmount ), strDateTime, pMainWindow->GetUserName( ) );

            strSql = strSql.arg( bMonthCard ? "" : pFeeDlg->GetFeeRateType( ),
                                              bMonthCard ? "无优惠" : pFeeDlg->GetDiscountType( ),
                                              strCardNumber );
            }
        }
    }

    if ( GetDirectDb( ) ) {
        CLogicInterface::GetInterface( )->ExecuteSql( strSql );
    } else {
        bool bTimeCard = ( CardTime == cardKind );
        if ( bTimeCard && !bEnter && CCommonFunction::GetHistoryDb( ) ) {
            //QString strSql = QString( "Update IGNORE stoprd Set MayDelete = 1\
            //                          Where cardno = '%1' And intime in ( select * from ( Select Max( intime ) \
            //                           From stoprd Where cardno = '%2' ) tmp ) " ).arg( strCardNumber, strCardNumber );

            QString strSql = QString( "Update IGNORE stoprd Set MayDelete = 1\
                                      Where stoprdid = ( select stoprdid from cardstoprdid where cardno = '%1' ) " ).arg( strCardNumber );
            SendDbWriteMessage( CDbEvent::SQLExternal, strSql, false, false, false );
        }

        SendDbWriteMessage( CDbEvent::SQLExternal, strSql, CCommonFunction::GetHistoryDb( ), bTimeCard && bEnter, false );
    }

    //if ( !bMonthCard || !MonthCardWorkMode( ) ) {
        CarInsideOutside( bEnter, strTable, strCardNumber, cCan );
    //}

    //int nChannel = GetChannelByCan( cCan );

    QByteArray byImageData;

    if ( bMonthMultipleCard ) {
        byImageData = ControlVehicleImage( strCardNumber, true, nChannel, nType, cLevel, bMonthMultipleCard,
                             bMonthMultipleCard, strMonthMultipleCardNo );
        //ControlVehicleImage( strCardNumber, true, nChannel );
    } else {
        byImageData = ControlVehicleImage( strCardNumber, true, nChannel, nType );
    }

    UploadData( strPlate, strCardNumber, bEnter, strDateTime, byImageData );

    DeleteCapturedFile( strCardNumber, nChannel,bEnter,  dtCurrent, strPlate );

    pMainWindow->UpdateStatistics( 1, bEnter ? 0 : 1 );

    if ( "计时卡" == strCardType ) {
        pMainWindow->UpdateStatistics( 1, bEnter ? 3 : 4 );
    }

    if ( !bEnter ) {
        cardCan.remove( strCardNumber );
    }

    SpaceChange( bEnter, cCan );

    QStringList lstData;
    lstData << "" << CCommonFunction::GetParkID( ) << "1" << strPlate << ( bEnter ? "1" : "0" ) << strDateTime << "2";
    CheckBlacklist( lstData );
}

int CProcessData::GetChannelByCan( char cCan )
{
    int nChannel = 0;

    for ( int nIndex = 0; nIndex < 4; nIndex++ ) {
        if ( cCan == cCanVideo[ nIndex ] ) {
            nChannel = nIndex;
            break;
        }
    }

    return nChannel;
}

void CProcessData::DeleteCapturedFile( QString &strCardNo, int nChannel, bool bEnter, QDateTime& dtCurrent, QString strPlate )
{
    QString strPath = "";
    GetCaptureFile( strPath, strCardNo, nChannel, CommonDataType::CaptureJPG );

    if ( QFile::exists( strPath ) ) {
        pMainWindow->SendInOutImg( strPath, bEnter, dtCurrent, strPlate, strCardNo );
        QFile::remove( strPath );
    }
}

void CProcessData::CaptureManualGateImage( char cCan, QString &strWhere )
{
    int nChannel = GetChannelByCan( cCan );
    QString strFileName = "";
    QString strCardNo = QString( "Gate%1" ).arg( QDateTime::currentMSecsSinceEpoch( ) );
    GetCaptureFile( strFileName, strCardNo, nChannel, CommonDataType::CaptureJPG );
    pMainWindow->CaptureImage( strFileName, nChannel, CommonDataType::CaptureJPG );
    CLogicInterface::GetInterface( )->OperateBlob( strFileName, true,
                                                   ( CommonDataType::BlobType ) ( CommonDataType::BlobManualGate1 + nChannel ), strWhere );
}

QByteArray CProcessData::ControlVehicleImage( QString &strCardNo, bool bSave2Db, int nChannel, int nType,
                                        char cLevel, bool bFreeCard, bool bMonth, QString strMonth, bool bGarage )
{
    QByteArray byData;
    QString strPath = "";
    GetCaptureFile( strPath, strCardNo, nChannel, CommonDataType::CaptureJPG );
    bool bEnter = ( 0 == nChannel % 2 );

    CommonDataType::BlobType blob = CommonDataType::BlobOwner;

    if ( !bGarage ) {
        switch ( cLevel ) {
        case 1 :
            blob = bEnter ? CommonDataType::BlobVehicleIn1 : CommonDataType::BlobVehicleOut1;
            break;

        case 2 :
            blob = bEnter ? CommonDataType::BlobVehicleIn2 : CommonDataType::BlobVehicleOut2;
            break;

        case 3 :
            blob = bEnter ? CommonDataType::BlobVehicleIn3 : CommonDataType::BlobVehicleOut3;
            break;

        case 4 :
            blob = bEnter ? CommonDataType::BlobVehicleIn4 : CommonDataType::BlobVehicleOut4;
            break;
        }
    } else {
        blob = CommonDataType::BlobGarageImg;
    }

    QString strWhere;
    if ( bFreeCard ) { // 无卡号
        if ( bGarage ) {
            strWhere = QString( bMonth ? " Where id = ( select stoprdid from Garagestoprdid where cardno = '%1' )" : " Where id = '%1'" ).arg( strCardNo );
        } else {
            strWhere = QString(  " Where stoprdid = ( select stoprdid from cardstoprdid where cardno = '%1' )" ).arg( bMonth ? strMonth : strCardNo );
        }
    } else { // 有卡号
        //strWhere = QString( " Where cardno = '%1' And intime in ( Select intime From \
        //                          ( Select Max( intime ) As intime \
        //                            From stoprd \
        //                            Where cardno = '%2') tmp ) " ).arg( strCardNo, strCardNo );

        if ( bGarage ) {
            strWhere = QString( " Where id = ( select stoprdid from Garagestoprdid where cardno = '%1' )" ).arg( strCardNo );
        } else {
            strWhere = QString( " Where stoprdid = ( select stoprdid from cardstoprdid where cardno = '%1' )" ).arg( strCardNo );
        }
    }

    if ( bSave2Db && !GetDirectDb( ) ) {
        QFile file( strPath );
        if ( !file.exists( ) || !file.open( QIODevice::ReadWrite ) ) {
            return byData;
        }

        byData = file.readAll( );
        file.close( );
        //CLogicInterface::GetInterface( )->OperateBlob( byData, bSave2Db, blob, strWhere );
        ParkCardType cardKind = CardNone;
        QStringList lstRows;
        GetCardType2( strCardNo, lstRows, cardKind );

        if ( bGarage ) {
            SendDbWriteMessage( CDbEvent::ImgExternal, strWhere, CCommonFunction::GetHistoryDb( ),
                                bEnter && ( CardTime == cardKind ), false, blob, byData );
        } else {
            SendDbWriteMessage( CDbEvent::ImgExternal, strCardNo, bEnter, nType, bGarage, byData );
        }
    } else {
        CLogicInterface::GetInterface( )->OperateBlob( strPath, bSave2Db, blob, strWhere );
    }

    return byData;
}

bool CProcessData::ProcessTimeCard( QByteArray& byData, QByteArray& vData, QStringList &lstRows, QString strPlate, ParkCardType& cardKind )
{
    // Select cardno, cardkind, cardfeebz, cardselfno, cardstate
    // 该卡已挂失
    // 该卡剩余xx时间
    quint8 byte5 = byData[ 5 ]; // 3E Enetr Park 3F Leave Park
    bool bEnter = CCommonFunction::ContainAddress( char ( byte5 ), true );
    bool bLeave = !bEnter;
    bool bRet = false;
    int nAmount = 0;

    //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardTime, CPortCmd::AudioCardTime );
#if false
    QString strState = lstRows[ 4 ];
    if ( 0 == strState.compare( QString( "挂失" ) ) ) {
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardTime, CPortCmd::AudioCardTime );
        PlayAudioDisplayInfo( byData, vData, CPortCmd::LedCardLoss, CPortCmd::AudioCardLoss );
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedContactAdmin, CPortCmd::AudioContactAdmin );
        return bRet;
    }
#endif

    QString strTable;
    QString strCardType = "计时卡";
    CCommonFunction::GetTableName( CommonDataType::TimeCard, strTable );
    if ( !CarInsideOutside( bEnter, lstRows[ 0 ], strTable, byData, vData, byte5, cardKind ) ) {
        return bRet;
    }

    if ( bEnter ) {
        // lstInOut[ 1 ] 数据 已入场
        ControlGate( bEnter, byData, vData, cardKind );
        PlayAudioDisplayInfo( byData, vData, CPortCmd::LedTimeCardEnter, CPortCmd::AudioTimeCardEnter );
    } else if ( bLeave ) {
        if ( pFeeDlg->isVisible( ) ) {
            return false; // Only let one car pass
        }

        bool bBuffer = GetTimeCardBuffer( );
        QString strBufferTable = bBuffer ? "tmpcardintime" : "stoprd";
        QStringList lstInOut;
        QString strSql = QString( "select cardno, intime, inshebeiname %1 from %2" ).arg( bBuffer ? ",stoprdid" : "", strBufferTable );
        //QString strWhere = QString( " Where cardno = '%1' And intime in \
        //                            ( Select intime From ( Select Max( intime ) As intime \
        //                                                   From %2 \
        //                                                   Where cardno = '%3' ) tmp )" ).arg( lstRows[ 0 ], strBufferTable, lstRows[ 0 ] );

        QString strWhere = QString( " Where stoprdid = ( Select stoprdid From cardstoprdid \
                                                           Where cardno = '%1' )" ).arg( lstRows[ 0 ] );

        //CLogicInterface::GetInterface( )->OperateInOutRecord( lstInOut, CommonDataType::SelectData, strWhere );
        strSql += strWhere;
        CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstInOut );
        if ( 0 == lstInOut.count( ) ) {
            //qDebug << QString( "Not enter" ) << endl;
            return bRet;
        }

        QString strTmpID = "";
        if ( bBuffer ) {
            strTmpID = lstInOut[ 3 ];
        }

        QDateTime dtEnd = QDateTime::currentDateTime( );
        // lstInOut[ 1 ] 无数据 未入场
        QDateTime dtStart = CCommonFunction::String2DateTime( lstInOut[ 1 ] );
        int nMins = CCommonFunction::GetDateTimeDiff( false, 60, dtStart, dtEnd );

        if ( 0 > nMins ) {
            CCommonFunction::MsgBox( NULL, "提示", "进入时间大于离开时间", QMessageBox::Information );
            return false;
        }
        int nHour;
        int nMin;
        GetHourMin( nMins, nHour, nMin );

        QString strTable;
        CCommonFunction::GetTableName( CommonDataType::TimeCard, strTable );
        nAmount = CalculateFee( dtStart, dtEnd, lstRows[ 0 ], byte5 );
        //CardExitInfo( byData, vData, false, nMin, nHour, nAmount ); // 2011 12 18
        //CCDisplayInfo( byData, vData, nMin, nHour, nAmount, bEnter ); // 2011 12 18

        pFeeDlg->SetParams( byData, vData, nMin, nHour, nAmount, bEnter );

        //////////////////////////////////
        QStringList lstInit;
        QString strParkName = "";
        pMainWindow->GetParkName( strParkName, byData[ 5 ], 0 );
        QString strChannel = "未知";
        GetChannelName( bEnter, byte5, strChannel );

        //CCommonFunction::GetAllChannels( lstChan, strParkName, bEnter );
        QString strEnd = dtEnd.toString( "yyyy-MM-dd HH:mm:ss" );
        lstInit << lstRows[ 0 ] << strCardType;
        lstInit << lstInOut[ 2 ] << lstInOut[ 1 ];
        lstInit << strChannel << strEnd;
        lstInit << QString::number( nHour ) << QString::number( nMin);
        lstInit << QString::number( nAmount );
        lstInit << strTable << strParkName;
        lstInit << lstInOut[ 1 ] << strEnd << strPlate;
        lstInit << GetFeeStd( lstRows[ 0 ] );

        bool bGate = PictureContrast( lstInit, nAmount, byData, strTmpID );
        if ( bGate ) {
            pMainWindow->UpdateStatistics( nAmount, 2 );
            pMainWindow->UpdateStatistics( pFeeDlg->GetAmount( ) - nAmount, 5 );
            ControlGate( bEnter, byData, vData, cardKind );
        } else {
            return bRet;
        }
        //////////////////////////////////

        //CardExitInfo( byData, vData, false, nMin, nHour, nAmount );
        //CCDisplayInfo( byData, vData, nMin, nHour, nAmount, bEnter );

        // Confirm to pass
        ControlChargeInfo( lstRows[ 0 ], QDateTime::currentDateTime( ), QString::number( nAmount ), "1" );

        //CCommonFunction::GetSyncPass( ).lock( );
        //ControlGate( true, byData, vData );
    }

    WriteInOutRecord( bEnter, lstRows[ 0 ], strTable, strCardType, strPlate, byte5, cardKind, nAmount );

    return bRet;
}

 void CProcessData::SendTimeCardInfo( QByteArray &byData, QByteArray &vData, int nMin, int nHour, int nAmount, bool bEnter )
 {
     pSettings->sync( );

     //if ( pSettings->value( "CommonCfg/NoCardWork", false ).toBool( ) ) {
     //   Sleep( 1500 );
     //}

     if ( pSettings->value( "UserRequest/IfDisplayFeeInfo", false ).toBool( ) ) {
         CardExitInfo( byData, vData, false, nMin, nHour, nAmount ); // 2011 12 18
         CCDisplayInfo( byData, vData, nMin, nHour, nAmount, bEnter ); // 2011 12 18
     }
 }

#if false
bool CProcessData::ExitConfirmDlg( bool bEnter,)
{
    QStringList lstInit;
    QString strParkName = "";
    pMainWindow->GetParkName( strParkName );
    QStringList lstChan;
    CCommonFunction::GetAllChannels( lstChan, strParkName, bEnter );
    QString strEnd = dtEnd.toString( "yyyy-MM-dd HH:mm:ss" );
    lstInit << lstRows[ 0 ] << strCardType;
    lstInit << lstInOut[ 0 ] << lstInOut[ 1 ];
    lstInit << ( 0 < lstChan.count( ) ? lstChan[ 0 ] : "" ) << strEnd;
    lstInit << QString::number( nHour ) << QString::number( nMin);
    lstInit << QString::number( nAmount );
    lstInit << strTable << strParkName;
    lstInit << lstInOut[ 1 ] << strEnd << strCurrentPlate[ bEnter ];

    bool bGate = PictureContrast( lstInit, nAmount, byData );

    return bGate;
}
#endif

QString CProcessData::GetCardStatus( QString &strCardNo, ParkCardType cardType )
{
    QString strTable;
    CCommonFunction::GetTableName( ( CommonDataType::CardType ) cardType, strTable );

    QStringList lstRows;
    QString strSql = QString( "select cardstate from %1 where cardno = '%2'" ).arg( strTable, strCardNo );
    if ( 0 < CLogicInterface::GetInterface()->ExecuteSql(  strSql, lstRows ) ) {
        return lstRows.at( 0 );
    } else {
        return "挂失";
    }
}

void CProcessData::GetCardType2( QString &strCardNo, QStringList &lstRows, ParkCardType& cardKind )
{
    cardKind = CardNone;
    CommonDataType::QEntityHash& entInfo = CCommonFunction::GetCardEntity( );
    CommonDataType::PEntityInfo pInfo = entInfo.value( strCardNo );
    lstRows.clear( );
    if ( NULL == pInfo ) {
        GetCardType1( strCardNo, lstRows, cardKind ); // Read DB to get new card
        return;
    }

    QString strDateTime;

    cardKind = ( ParkCardType )pInfo->cardType;

    lstRows.clear( );
    lstRows << pInfo->strCardNumber;
    lstRows << "";

    QList<QString> lstKey = pInfo->carInfo.keys( );
    if ( 0 == lstKey.count( ) ) {
        lstRows << "";
        lstRows << "";
        lstRows << pInfo->cardStatus;
        return;
    }

    //if ( "挂失" == pInfo->cardStatus ) {
        pInfo->cardStatus = GetCardStatus( strCardNo, cardKind );
    //}

    QString& strKey = lstKey.first( );

    if ( CardMonthly == cardKind ) {
        CCommonFunction::DateTime2String( pInfo->MonthDateTime.dtStart, strDateTime );
        lstRows << strDateTime;
        CCommonFunction::DateTime2String( pInfo->MonthDateTime.dtEnd, strDateTime );
        lstRows << strDateTime;
        lstRows << pInfo->cardStatus;
    } else if ( CardSave == cardKind ) {
        lstRows << pInfo->cardStatus;
        QString strSql = "Select cardfee from SaveCard where cardno = '%1' ";
        strSql = strSql.arg( pInfo->strCardNumber );
        QStringList lstFee;
        CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstFee );

        lstRows << ( ( lstFee.length( ) > 0 ) ? lstFee.at( 0 ) : "0" );
        lstRows << pInfo->carInfo.value( strKey );
    } else if ( CardTime == cardKind ) {
        lstRows << pInfo->carInfo.value( strKey );
        lstRows << "";
        lstRows << pInfo->cardStatus;
        lstRows << pInfo->strFeeStd;
    }
}

void CProcessData::GetCardType1( QString &strCardNo, QStringList& lstRows, ParkCardType& cardKind )
{
    CommonDataType::CardType card = CommonDataType::MonthlyCard;
    CommonDataType::DatabaseOperation dbOperation = CommonDataType::SelectData;
    QString strWhere = QString( " Where cardno = '%1' " ).arg( strCardNo );
    cardKind = CardNone;

    int nRows = CLogicInterface::GetInterface( )->OperateCardInfo( lstRows, card, dbOperation, strWhere );
    if ( 0 < nRows ) {
        cardKind = CardMonthly;
        return;
    }

    if ( CardNone == cardKind ) {
        card = CommonDataType::ValueCard;
        nRows = CLogicInterface::GetInterface( )->OperateCardInfo( lstRows, card, dbOperation, strWhere );
        if ( 0 < nRows ) {
            cardKind = CardSave;
            return;
        }
    }

    if ( CardNone == cardKind ) {
        card = CommonDataType::TimeCard;
        nRows = CLogicInterface::GetInterface( )->OperateCardInfo( lstRows, card, dbOperation, strWhere );
        if ( 0 < nRows ) {
            cardKind = CardTime;
            return;
        }
    }

    if ( CardNone == cardKind ) {
        //card = CommonDataType::TimeCard;
#if true
        QString strSql = QString( "Select EmployeeID from operator where EmployeeID ='%1'" ).arg( strCardNo );
        nRows = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );
        if ( 0 < nRows ) {
            //cardType[ bEnter ] = CardEmployee;
            cardKind = CardTime;
        }
#endif
    }
}

void CProcessData::PlayAudioDisplayInfo( QByteArray &byData, QByteArray& vDataLed, QByteArray& vDataAudio,
                                        CPortCmd::LedInfo led, CPortCmd::AudioAddress audio )
{
    //char cLevel = GetCanLevel( byData[ 5 ] );
    //if ( 1 != cLevel ) {
    //    return;
    //}

    DisplayInfo( byData, vDataLed, led );
    PlayAudio( byData, vDataAudio, audio );
}

void CProcessData::GetPlayDisplayList( QByteArray &byData, QByteArray &vDataLed, QByteArray &vDataAudio,
                                       CPortCmd::LedInfo led, CPortCmd::AudioAddress audio, int nChannel )
{
        portCmd.GetLedInfo( led, vDataLed );
        portCmd.ParseDownCmd( byData, CPortCmd::DownLED, vDataLed );
        ledList[ nChannel ].append( byData );

        portCmd.GetAudioAddr( audio, vDataAudio );
        portCmd.ParseDownCmd( byData, CPortCmd::DownPlayAudio, vDataAudio );
        audioList[ nChannel ].append( byData );
}

void CProcessData::ComposePlayDisplayData( QList<QByteArray> &listData, int nHeader, int nTail, bool bAudio )
{
    QByteArray byData;
    int nCount = listData.count( );
    int nIndex = 0;
    int nDataLen = 0;
    int nTmpLen = 0;
    char cAudioLen = 0;

    for ( nIndex = 0; nIndex < nCount; nIndex++ ) {
        const QByteArray& data = listData.at( nIndex );

        if ( 0 == nIndex ) {
            byData.append( data.left( nHeader ) );
        }

        if ( bAudio ) {
            cAudioLen += data[ 4 ];
        }

        nTmpLen = data.count( ) - nHeader - nTail;
        byData.append( data.mid( nHeader, nTmpLen ) );
        nDataLen += nTmpLen;

        if ( nIndex + 1 == nCount ) {
            byData.append( data.right( nTail ) );
        }
    }

    if ( 0 >= byData.count( ) ) {
        return;
    }

    nDataLen += nHeader + nTail - 5;
    qint16 nLen = ( qint16 ) nDataLen;
    qint8* pLen = ( qint8* ) &nLen;
    byData[ 1 ] = *pLen;
    byData[ 2 ] = *( pLen + 1 );
    if ( bAudio ) {
        byData[ 4 ] = cAudioLen;
    }

    WriteData( byData );
}

void CProcessData::ProcessPlayDisplayList( int nChannel )
{
    //"aa 14 00 44 00 05 1a 1b  header
    // d4 c2 d7 e2 bf a8 c7 eb cd a8 d0 d0  data
    // 01 1c 1d 01 55"  tail
    //if ( NoCardWork( ) ) {
    //    Sleep( 1000 );
    //}

    ComposePlayDisplayData( ledList[ nChannel ], 8, 5, false );

    //"aa 0900 50 03 05
    // 4c00 1f01 1401
    // 01 55"

    ComposePlayDisplayData( audioList[ nChannel ], 6, 2, true );
}

void CProcessData::PlayAudio( QByteArray &byData, QByteArray &vData, CPortCmd::AudioAddress audio )
{
    ////char cLevel = GetCanLevel( byData[ 5 ] );
    //if ( 1 != cLevel ) {
    //    return;
    //}

    portCmd.GetAudioAddr( audio, vData );
    portCmd.ParseDownCmd( byData, CPortCmd::DownPlayAudio, vData );
    WriteData( byData );
}

void CProcessData::DisplayInfo( QByteArray &byData, QByteArray &vData, CPortCmd::LedInfo led )
{
    //char cLevel = GetCanLevel( byData[ 5 ] );
    //if ( 1 != cLevel ) {
    //    return;
    //}

    portCmd.GetLedInfo( led, vData );
    portCmd.ParseDownCmd( byData, CPortCmd::DownLED, vData );
    WriteData( byData );
}

void CProcessData::ParkspaceFull( bool bFull, QString& strInfo, char cCan )
{
    bParkspaceFull = bFull;

    if ( !strInfo.isEmpty( ) ) {
        SendIndependentLedInfo( strInfo, cCan );
    }
}

void CProcessData::SendIndependentLedInfo( QString &strInfo, char cCan )
{
    pSettings->sync( ); // File <-- > Memory
    QString strCans = pSettings->value( "CommonCfg/IndependentLedCan", "" ).toString( );
    if ( strCans.isEmpty( ) ) {
        return;
    }

    //PublishLedInfo( strInfo, cCan, true );
    QStringList lstCans = strCans.split( "," );

    for ( int nIndex = 0; nIndex < lstCans.count( ); nIndex++ ) {
        if ( 0 != nIndex ) {
            const QString& strCan = lstCans.at( nIndex );
            if ( strCan.isNull() || strCan.isEmpty( ) ) {
                continue;
            }

            PublishLedInfo( strInfo, ( char ) strCan.toInt( ), true );
        } else if ( 0 == cCan ) {
            PublishLedInfo( strInfo, ( char ) lstCans.at( 0 ).toInt( ), true );
            break;
        }
    }
}

void CProcessData::DisableSendCardHint( QByteArray &byData, QByteArray &vData )
{
    QByteArray ledData;
    PlayAudioDisplayInfo( byData, ledData, vData, CPortCmd::LedParksFull, CPortCmd::AudioParksFull  );
}

void CProcessData::PlayAudioDisplayInfo( QByteArray &byData, QByteArray &vData,
                                        CPortCmd::LedInfo led, CPortCmd::AudioAddress audio )
{
    //char cLevel = GetCanLevel( byData[ 5 ] );
    //if ( 1 != cLevel ) {
    //    return;
    //}

    //if ( NoCardWork( ) ) {
    //    Sleep( 1500 );
    //}

    DisplayInfo( byData, vData, led );
    PlayAudio( byData, vData, audio );
}

void CProcessData::ProcessCmd( QByteArray &byData, CPortCmd::PortUpCmd cmdType )
{
    bool bEnter = ( 0x01 == byData[ 6 ]  ); // Enter Gate / Sense
    //bool bLeave = ( 0x00 == byData[ 6 ] ); // Leave Gate / Sense
    QByteArray vData;
    bool bForbidden;

    switch ( cmdType ) {
    case CPortCmd::UpNone :
        ;
        break;
    case CPortCmd::UpSuccess :
        ;
        break;
    case CPortCmd::UpFailed :
        ;
        break;
    case CPortCmd::UpCCExist :
        break;
    case CPortCmd::UpInGateExist :
    case CPortCmd::UpOutGateExist :
        {
            QDateTime dt = QDateTime::currentDateTime( );
            CheckCenterContronller( true, dt );
            CheckCenterContronller( false, dt );
        }
        break;
    case CPortCmd::UpCardInfo : // Shua Card
        EmployeeCard( byData );
        DefaultClicked( byData );
        ProcessCardInfo( byData );
        break;
    case CPortCmd::UpDispenserReply : // 发卡机状态
        //vData = byData.mid( 6,byData.count( ) - 8 );
        emit OnResponseUserRequest( byData, 5 );
        //Dispenser( byData, vData );
        break;
    case CPortCmd::UpAudioEnd :
        break;
    case CPortCmd::UpInBallotSenseVehcleEnter : // Vehcle Enter
        bSendOnlyOnce = true;
        BallotSense( byData, vData, bEnter, true );
        CaptureSenseImage( byData, CommonDataType::CaptureJPG );
        //Sleep( 1000 );
        if ( NoPlateOpenGate( ) && WriteInOutRecord( byData ) ) {
            SenseOpenGate( byData );
        }
        break;
    case CPortCmd::UpInBallotSenseVehcleLeave :
        bSendOnlyOnce = false;
        BallotSense( byData, vData, bEnter, false );
        ClearSenseImage( byData );
        break;
    case CPortCmd::UpOutBallotSenseVehcleEnter : // Vehcle Enter
        BallotSense( byData, vData, bEnter, true );
        CaptureSenseImage( byData, CommonDataType::CaptureJPG );
        //Sleep( 1000 );
        if ( NoPlateOpenGate( ) && WriteInOutRecord( byData ) ) {
            SenseOpenGate( byData );
        }
        break;
    case CPortCmd::UpOutBallotSenseVehcleLeave :
        BallotSense( byData, vData, bEnter, false );
        ClearSenseImage( byData );
        break;
    case CPortCmd::UpButtonDownCar : //
    case CPortCmd::UpButtonDownNoCar :
        bForbidden = pSettings->value( "UserRequest/EntranceForbidden", false ).toBool( );
        if ( !bForbidden && !bParkspaceFull ) { // false
            if ( bSendOnlyOnce ) {
                BallotButton( byData, vData, true );
                bSendOnlyOnce = false;
            }
        }

        if ( bForbidden || bParkspaceFull ) {
            DisableSendCardHint( byData, vData );
        }
        break;
    case CPortCmd::UpButtonUpCar :
        ;//BallotButton( byData, vData, false );
        break;
    //case CPortCmd::UpButtonDownNoCar :
    //    ;
    //    break;
    case CPortCmd::UpButtonUpNoCar :
        ;//BallotButton( byData, vData, false );
        break;
    case CPortCmd::UpInGateSenseVehcleEnter :// 道闸地感车辆进入
        GateSense( byData, vData, bEnter, false );
        break;
    case CPortCmd::UpInGateSenseVehcleLeave :
        GateSense( byData, vData, bEnter, false );
        break;
    case CPortCmd::UpOutGateSenseVehcleEnter :// 道闸地感车辆进入
        GateSense( byData, vData, bEnter, true );
        break;
    case CPortCmd::UpOutGateSenseVehcleLeave :
        GateSense( byData, vData, bEnter, true );
        break;
    case CPortCmd::UpQuerySenseCar : // 票箱地感状态
        emit OnResponseUserRequest( byData, 1 );
        break;
    case CPortCmd::UpQuerySenseNoCar :
        emit OnResponseUserRequest( byData, 1 );
        break;
    case CPortCmd::UpQueryButtonOpen : // 取卡按钮状态
        emit OnResponseUserRequest( byData, 3 );
        break;
    case CPortCmd::UpQueryButtonClose :
        emit OnResponseUserRequest( byData, 3 );
        break;
    case CPortCmd::UpQueryGateCar : // 道闸地感状态
        emit OnResponseUserRequest( byData, 2 );
        break;
    case CPortCmd::UpQueryGateNoCar :
        emit OnResponseUserRequest( byData, 2 );
        break;
    case CPortCmd::UpQueryControler : // 道闸控制器状态
        //GateControllerState( byData, vData );
        emit OnResponseUserRequest( byData, 4 );
        break;
    }
}

void CProcessData::QueryGateControllerState( char cAddr )
{
    QByteArray byData;
    //QByteArray vData;

    char cmd[ ] = { 0xAA, 0x03, 0x00, 0x51, 0x41, cAddr, 0x01, 0x55 };
    byData.append( cmd, sizeof ( cmd ) );

    //while ( true ) {
        if ( false == bQueryGateControllerState ) {
            //break;
        }

        //portCmd.ParseDownCmd( byData, CPortCmd::DownQueryControler, vData );
        WriteData( byData );
    //}
}

void CProcessData::QueryState( QueryStateType stateType )
{
    switch ( stateType ) {
    case GateController :
        QueryGateControllerState( char( 0x3E ) );
        QueryGateControllerState( char( 0x3F ) );
        break;
    }
}

void CProcessData::GateControllerState( QByteArray &byData, QByteArray &vData )
{
    qDebug( ) << "GateControllerState" << endl;
    bQueryGateControllerState = true;
}

void CProcessData::BallotButton( QByteArray &byData, QByteArray &vData, bool bDown )
{
    portCmd.ParseDownCmd( byData, bDown ? CPortCmd::DownDispenserSend : CPortCmd::DownDispenserReceive, vData );
    WriteData( byData );
}

void CProcessData::Dispenser( QByteArray &byData, QByteArray &vData )
{

}

void CProcessData::BallotSense( QByteArray &byData, QByteArray &vData, bool bEnterBallot, bool bEneterPark )
{
    int nChannel = GetChannelByCan( byData[ 5 ] );

    if ( !bEnterBallot ) {
        //bool bEnter = ( 0 == nChannel % 2 );
        bPlateRecognize[ nChannel ] = false;
        strCurrentPlate[ nChannel ].clear( );
    }

    if ( !bEnterBallot && !bPlateClear[ nChannel ][ 0 ] ) {
        return;
    }

    pMainWindow->SetBallotSense( bEnterBallot, nChannel, byData );

    //bool bEnter = ( 0 != byData[ 5 ] % 2 );

    if ( bEneterPark ) {
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedWelcome, CPortCmd::AudioWelcome );
    }

    if ( bEnterBallot ) {
        //PlayAudioDisplayInfo( byData, vData, CPortCmd::LedShuaCard, CPortCmd::AudioShuaCard );
    }
}

void CProcessData::GateSense( QByteArray &byData, QByteArray &vData, bool bEnterGate, bool bLeavePark )
{
    //GateIfHaveVehicle[ !bLeavePark ] = bEnterGate;
    //emit VehicleGateInOut( bEnterGate, bLeavePark );
    return;
    portCmd.ParseDownCmd( byData, bEnterGate ? CPortCmd::DownOpenGate : CPortCmd::DownCloseGate, vData );
    WriteData( byData );

    if ( bEnterGate ) {
        PlayAudioDisplayInfo( byData, vData, CPortCmd::LedPass, CPortCmd::AudioPass );
    }

    if ( bLeavePark ) {
        PlayAudioDisplayInfo( byData, vData, CPortCmd::LedGoodLuck, CPortCmd::AudioGoodLuck );
    }
}

bool CProcessData::WriteData( QByteArray &byData )
{
    CSerialEvent* pEvent = new CSerialEvent( QEvent::User );
    pEvent->SetSerialData( byData );
    QApplication::postEvent( &g_serialThread, pEvent );
    bool bRet = true;

#if false
    int nCount = byData.count( );
    Win_QextSerialPort& rawSerial = pSerialPort->GetRawSerialPort( );

    if ( rawSerial.isWritable( ) ) {
        bRet = ( nCount == rawSerial.write( byData ) );
        rawSerial.flush( );
#ifndef QT_NO_DEBUG
        QString strData( byData.toHex( ) );
        qDebug( ) << "Write Serial Port Cmd : " << strData << endl;
#endif
       Sleep( 500 );
    }
#endif

    return bRet;
}
