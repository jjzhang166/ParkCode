#if PLATEDEMO_H
    #include "../Common/commonfunction.h"
    #include "../Common/logicinterface.h"
#elif VEHICLELICENSE_LIBRARY
    #include "../Common/commonfunction.h"
    #include "../Common/logicinterface.h"
#elif MULTIMEDIA_LIBRARY
    #include "../Common/commonfunction.h"
    #include "../Common/logicinterface.h"
#elif PARAM_CFG_H
    #include "../Common/commonfunction.h"
    #include "../Common/logicinterface.h"
#elif PARKDATARECEIVER_APP
    #include "../Common/commonfunction.h"
#elif PARKDATACLIENT_APP
    #include "../Common/commonfunction.h"
#elif PLATFORM_SERVER
    #include "../Common/commonfunction.h"
#elif PLATFORM_CLIENT
    #include "../Common/commonfunction.h"
#else
    #include "Common/commonfunction.h"
    #include "Common/logicinterface.h"
#endif

#include <QDebug>
#include <QApplication>
#include <QAbstractButton>
#include <QDir>
#include <windows.h>
#include <QMutex>
#include <QtNetwork>
#include <QHostInfo>
#include <QDesktopWidget>
#include <QLabel>
#include <QTimeEdit>
#include <QHeaderView>
#include <QPushButton>

QSettings* CCommonFunction::pSysSettings = NULL;
QSettings* CCommonFunction::pFeeSettings = NULL;
QSettings* CCommonFunction::pDevSettings = NULL;
QSettings* CCommonFunction::pDbmSettings = NULL;
QSettings* CCommonFunction::pSysSetSettings = NULL;
QSettings* CCommonFunction::pPlateSettings = NULL;
QMutex CCommonFunction::syncPass;
QByteArray CCommonFunction::byteInAddr;
QByteArray CCommonFunction::byteOutAddr;
CommonDataType::QEntityHash CCommonFunction::cardEntity;
CommonDataType::QPlateCardHash CCommonFunction::plateCardHash;
QSplashScreen* CCommonFunction::pSplash = NULL;
QHash< char, QString > CCommonFunction::hashCanParkIndex;
QHash< char, QString > CCommonFunction::hashCanParkNum;
QHash< char, QString > CCommonFunction::hashCanParkName;

void CCommonFunction::SetWindowIcon( QWidget *pWidget )
{
    QString strPath;
    GetPath( strPath, CommonDataType::PathUIImage );
    strPath += "Icon.JPG";
    QIcon icon( strPath );
    pWidget->setWindowIcon( icon );

    Qt::WindowFlags flags = pWidget->windowFlags( );
    flags &= ( ~Qt::WindowContextHelpButtonHint );
    pWidget->setWindowFlags( flags ); // Help
}

QString CCommonFunction::GetCarTypeString( QString &strIndex )
{
    QString strType = "小型车";
    if ( NULL != pFeeSettings ) {
        strType = pFeeSettings->value( QString( "CarType/Count%1" ).arg( strIndex ), strType ).toString( );
    }

    return strType;
}

void CCommonFunction::PlayMusic( QString strName, bool bStop )
{
    static Phonon::MediaObject* pMediaObj = NULL;

    if ( bStop ) {
        if ( NULL != pMediaObj ) {
            pMediaObj->clear( );
            delete pMediaObj;
        }

        return;
    }

    if ( NULL == pMediaObj ) {
        pMediaObj = Phonon::createPlayer( Phonon::MusicCategory );
    }

    pMediaObj->clear( );

    QString strPath;
    CCommonFunction::GetPath( strPath, CommonDataType::PathCfgData );

    strPath += strName + ".wav";
    Phonon::MediaSource mediaSrc( strPath );
    //pMediaObj->setCurrentSource( mediaSrc );
    pMediaObj->enqueue( mediaSrc );
    pMediaObj->play( );
}

void CCommonFunction::ConnectMySql( QStringList& lstParams, bool bHistory, int nIndex )
{
    QSettings* pSettings = GetSettings( CommonDataType::CfgSystem );
    QString strItem = QString( "%1/" ).arg( bHistory ?
                                                  QString( "HistoryServer%1" ).arg( nIndex ) : "Database" ) + "%1";
    lstParams.clear( );

    QString strIP = pSettings->value( strItem.arg( "Host" ), QVariant( "127.0.0.1" ) ).toString( );
    if ( strIP == GetHostIP( ) ) {
        strIP = "127.0.0.1";
    }

    lstParams<< strIP;
    lstParams<< pSettings->value( strItem.arg( "User" ), QVariant( "test" ) ).toString( );
    lstParams<< pSettings->value( strItem.arg( "Pwd" ), QVariant( "test" ) ).toString( );
    lstParams<< pSettings->value( strItem.arg( "Schema" ), QVariant( "pms" ) ).toString( );
    lstParams<< pSettings->value( strItem.arg( "Port" ), QVariant( "3306" ) ).toString( );
}

void CCommonFunction::ClearAllFiles( QString &strDir )
{
    QDir dir( strDir );
    if ( !dir.exists( ) ) {
        return;
    }

    QFileInfoList fileList = dir.entryInfoList( QDir::Files | QDir::NoDotAndDotDot );
    QFile file;

    foreach ( const QFileInfo& fileInfo, fileList ) {
        file.setFileName( fileInfo.absoluteFilePath( ) );
        file.remove( );
    }
}

QHash< char, QString >& CCommonFunction::GetCanParkIndexNum( int  nIndex )
{
    QHash< char, QString >* pHash = NULL;
    if ( 0 == nIndex ) {
        pHash = &hashCanParkIndex;
    } else if ( 1 == nIndex ) {
        pHash = &hashCanParkNum;
    } else if ( 2 == nIndex ) {
        pHash = &hashCanParkName;
    }

    if ( NULL == pHash ) {
        pHash = new QHash< char, QString >( );
    }

    return *pHash;
}

void CCommonFunction::StartupSplash( )
{
    if ( NULL != pSplash ) {
        return;
    }

    QString strFile = "";
    GetPath( strFile, CommonDataType::PathUIImage );
    strFile += "logo.jpg";
    QPixmap pixmap(strFile );

    pSplash = new QSplashScreen( pixmap );
    Qt::WindowFlags flags = pSplash->windowFlags( ) | Qt::WindowStaysOnBottomHint;
    pSplash->setWindowFlags( flags );
    pSplash->show( );

    ShowSplashMessage( "停车场系统开始启动。" );
}

void CCommonFunction::CleanupSplash( QWidget* pWidget )
{
    if ( NULL == pSplash ) {
        return;
    }

    ShowSplashMessage( "停车场系统启动完成。" );
    pSplash->finish( pWidget );

    delete pSplash;
    pSplash = NULL;
}

void CCommonFunction::ShowSplashMessage( QString strMsg )
{
    if ( NULL == pSplash ) {
        return;
    }

    pSplash->showMessage( strMsg, Qt::AlignLeft, Qt::white );
    qApp->processEvents( );
}

bool CCommonFunction::GetHistoryDb( )
{
    return GetSettings( CommonDataType::CfgSystem ) ->value( "CommonCfg/HistoryDb", false ).toBool( );
}

#ifdef COMMON_DB
void CCommonFunction::LoadFourImages( CommonDataType::BlobType blob, QString& strWhere, QLabel& lbl, bool bHistory )
{
    QString strFile = "";
    CCommonFunction::GetPath( strFile, CommonDataType::PathSnapshot );
    strFile += "tmp.jpg";

    CLogicInterface::GetInterface( )->OperateBlob( strFile, false, blob, strWhere, bHistory );
    if ( QFile::exists( strFile ) ) {
        QPixmap map( strFile );
         lbl.setPixmap( map );

        QFile::remove( strFile );
    }
}
#endif

void CCommonFunction::ConnectCloseButton( QLabel *lblClose )
{
    QString strPath;
    GetPath( strPath, CommonDataType::PathUIImage);
    QString strBtnStyle = QString( "background-image:url(%1NewIcon/Close.JPG);\nborder: none; \nbackground-color: white;" ).arg( strPath );
    QCursor cursor( Qt::OpenHandCursor );
    lblClose->setVisible( false );
    QWidget* pWidget = ( QWidget* ) lblClose->parent( );
    QPushButton* pBtn = new QPushButton( pWidget );
    pBtn->setGeometry( lblClose->geometry( ) );
    pBtn->setStyleSheet( strBtnStyle );
    pBtn->setCursor( cursor );
    pWidget->connect( pBtn, SIGNAL( clicked( ) ), pWidget, SLOT( close( ) ) );
    return;
    static QString strLink = "<a href=\"/\" style = \"text-decoration:none;color: rgb(255, 255, 255);\">X</a>";
    lblClose->setStyleSheet( "background-image:url(none);" );
    lblClose->setAlignment( Qt::AlignHCenter );
    lblClose->setText( strLink );
}

void CCommonFunction::MySetWindowPos( QWidget* pWidget )
{
    if ( NULL == pWidget ) {
        return;
    }

    HWND hDesktop = GetDesktopWindow( );
    RECT recDesktop;
    BOOL bRet = GetWindowRect( hDesktop, &recDesktop );
    int nWidth = pWidget->width( );
    int nHeight = pWidget->height( );
    int nX = ( recDesktop.right - nWidth ) / 2;
    int nY = ( recDesktop.bottom - nHeight ) / 2;

    bRet = SetWindowPos( pWidget->winId( ), HWND_TOPMOST, nX, nY,
                              nWidth, nHeight, SWP_SHOWWINDOW );
}

QString CCommonFunction::GetFeeStd( QString &strFee )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgTariff );
    QString strKey = "CarType/Count%1";
    QString strTmp = strKey.arg( "" );
    QString strFeeStd = "-1";
    int nCount = pSet->value( strTmp, 0 ).toInt( );

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        strTmp = strKey.arg( nIndex );
        strTmp = pSet->value( strTmp, "" ).toString( );
        if ( strTmp == strFee ) {
            strFeeStd = QString::number( nIndex );
            break;
        }
    }

    return strFeeStd;
}

void CCommonFunction::DisplayPlateChar( QLabel**pLicenseRow, int nChannel, QString& strContent )
{
    qDebug( ) << "CCommonFunction::DisplayPlateChar " << strContent << endl;
    try {
    int nCount = strContent.count( ); //lblLicence11
    //static const QString strName( "lblLicence%1%2" );
    QLabel* pLabel = NULL;
    //static const QString strLink = "<a href=\"/\" style = \"text-decoration:none;color: rgb(255, 255, 255);\">%1</a>";

    for ( int nIndex = 0; nIndex < 8; nIndex ++ ) {
        pLabel = pLicenseRow[ nIndex ];

        if ( NULL != pLabel ) {
            //pLabel->setText( strLink.arg( ( nIndex > nCount - 1 ) ? " " : QString( strContent[ nIndex ] ) ) );
            //pLabel->setText( "" );
            if ( nIndex < nCount ) {
                QString strChar = QString( strContent[ nIndex ] );
                //HWND hWnd = pLabel->winId( );
                //QByteArray byText = GetTextCodec( )->fromUnicode( strChar );
                //LPCSTR pText = byText.data( );
                //HDC hDc = GetWindowDC( hWnd );
                //SetTextAlign( hDc, TA_CENTER );
                //BOOL bRet = TextOutA( hDc, 0, 0, pText, byText.length( ) );
                //ReleaseDC( hWnd, hDc );
                //if ( !bRet ) {
                    pLabel->setText( strChar );
                //}
            }
            //pLabel->setText( ( nIndex > nCount - 1 ) ? " " : QString( strContent[ nIndex ] ) );
            //if ( pLabel->updatesEnabled( ) ) {
            //    pLabel->update();
            //}
        }
    }
    } catch ( ... ) {
        qDebug( ) << "CCommonFunction::DisplayPlateChar Exception" << endl;
    }
}

void CCommonFunction::WindowCenter( QWidget &widget )
{
    QDesktopWidget* pDesktop = QApplication::desktop( );
    QRect rect = pDesktop->screenGeometry( );
    int nWidth  = rect.width( );
    int nHeight = rect.height( );

    QSize size = widget.size( );

    nWidth = ( nWidth - size.width( ) ) / 2;
    nHeight = ( nHeight - size.height( ) ) / 2;
    widget.move( nWidth, nHeight );
}

QString CCommonFunction::GetParkID( )
{
    QSettings* pSet = GetSettings( CommonDataType::CfgSystem );

    return pSet->value( "CommonCfg/ParkID", "127.0.0.1" ).toString( );
}

QString CCommonFunction::GetHostIP( )
{
#if false
    QHostInfo host = QHostInfo::fromName( QHostInfo::localHostName( ) );
    QList< QHostAddress > lstAddr = host.addresses( );

    for ( int nIndex = 0; nIndex < lstAddr.count( ); nIndex++ ) {
        QHostAddress addr = lstAddr.at( nIndex );
        qDebug( ) << addr.toString( ) << endl;
    }

    return lstAddr.count( ) > 0 ? lstAddr.first( ).toString( ) : "";
#endif
    QSettings* pSet = GetSettings( CommonDataType::CfgSystem );

    return pSet->value( "CommonCfg/Host", "127.0.0.1" ).toString( );
}

void CCommonFunction::GetChannelInfo( QString& strCardNo, bool bEnter, QStringList& lstInfo )
{
    //plateCardHash.value( strPlate );
    CommonDataType::PEntityInfo pInfo = cardEntity.value( strCardNo );
    if ( NULL == pInfo ) {
        return;
    }

    QList< QString > lstKeys = pInfo->cardRight.keys( );
    QString strIP = GetHostIP( );

    for ( int nItem = 0; nItem < lstKeys.count( ); nItem++ ) {
        QString& strKey = lstKeys[ nItem ];
        QStringList lstValue = pInfo->cardRight.value( strKey );

        if ( lstValue.contains( strIP ) ) {
            int nCAN = lstValue[ 2 ].toInt( ); // Odd / Enter
            // '东门入口', '00:00:00', '23:59:59', '2', '192.168.0.2'
            // ChannelName, StartTime, EndTime, CAN, IP
            if ( 0 != ( nCAN % 2 ) && bEnter ) {
                lstInfo << strKey << lstValue;
            } else if ( 0 == ( nCAN % 2 ) && !bEnter ) {
                lstInfo << strKey << lstValue;
            }
        }
    }

    if ( 0 == lstInfo.count( ) ) {
        qDebug( ) << "CCommonFunction::GetChannelInfo Failed" << endl;
        //lstInfo << "" << "00:00:00" << "23:59:59" << ( bEnter ? "2" : "1" ) << "127.0.0.1";
    }
}

CommonDataType::QPlateCardHash& CCommonFunction::GetPlateCardHash( )
{
    return plateCardHash;
}

CommonDataType::QEntityHash& CCommonFunction::GetCardEntity( )
{
    return cardEntity;
}

QString CCommonFunction::GetMsgTitle( QMessageBox::Icon nType )
{
    QString strTitle = "";

    if ( QMessageBox::Information == nType ) {
        strTitle = "提示";
    }

    return strTitle;
}

void CCommonFunction::ControlSysMenu( QWidget &wg )
{
    Qt::WindowFlags flags = wg.windowFlags( );
    flags &= ( ~Qt::WindowContextHelpButtonHint );
    wg.setWindowFlags( flags ); // Help

    wg.setMinimumSize( wg.width( ), wg.height( ) );
    wg.setMaximumSize( wg.width( ), wg.height( ) );

    HMENU hSysMenu = GetSystemMenu( wg.winId( ), FALSE );

    if ( NULL != hSysMenu ) {
        EnableMenuItem( hSysMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED ); // Close
    }
}

void CCommonFunction::AddAddress( char cAddr, bool bEnter )
{
    if ( bEnter && !byteInAddr.contains( cAddr ) ) {
        byteInAddr.append( cAddr );
    } else if ( !bEnter && !byteOutAddr.contains( cAddr ) ) {
        byteOutAddr.append( cAddr );
    }
}

int CCommonFunction::GetAddressCount( bool bEnter )
{
    return bEnter ? byteInAddr.count( ) : byteOutAddr.count( );
}

char CCommonFunction::GetAddress( int nIndex, bool bEnter )
{
    char cAddr = 0;
    if ( 0 > nIndex ) {
        return cAddr;
    }

    if ( bEnter && byteInAddr.count( ) > nIndex ) {
        cAddr = byteInAddr[ nIndex ];
    } else if ( !bEnter && byteOutAddr.count( ) > nIndex ) {
        cAddr = byteOutAddr[ nIndex ];
    }

    return cAddr;
}

bool CCommonFunction::ContainAddress( char cAddr, bool bEnter )
{
    return bEnter ? byteInAddr.contains( cAddr ) : byteOutAddr.contains( cAddr );
}

QSettings* CCommonFunction::CreateSetting( QSettings **pSet, QString& strFile )
{
    if ( NULL == *pSet ) {
        GetPath( strFile, CommonDataType::PathCfgData );
        *pSet = new QSettings( strFile, QSettings::IniFormat );
        ( *pSet )->setIniCodec( CCommonFunction::GetTextCodec( ) );
    }

    return *pSet;
}

QMutex& CCommonFunction::GetSyncPass( )
{
    return syncPass;
}

void CCommonFunction::GetCarType( QComboBox* pCB )
{
    pCB->clear( );
    QString strSection= "CarType/Count%1";
    int nIndex = 0;
    QString strName;
    QSettings* pSet = GetSettings( CommonDataType::CfgTariff );

    int nSection = pSet->value( strSection.arg( "" ), QVariant( 0 ) ).toInt( );
    for ( nIndex = 0; nIndex < nSection; nIndex++ ) {
        strName = pSet->value( strSection.arg( QString::number( nIndex ) ), QVariant( "" ) ).toString( );
        if ( !strName.isEmpty( ) ) {
            pCB->addItem( strName );
        }
    }

    pCB->setCurrentIndex( 2 );
}

QSettings* CCommonFunction::GetSettings(CommonDataType::CfgType type)
{
    QSettings* pSettings = NULL;
    QString strName;

    switch ( type ) {
    case CommonDataType::CfgSystem :
        strName = "SystemCfg.ini";
        pSettings = CreateSetting( &pSysSettings, strName );
        break;

    case CommonDataType::CfgTariff :
        strName = "TariffCfg.ini";
        pSettings = CreateSetting( &pFeeSettings, strName );
        break;

    case CommonDataType::CfgDbMaintain :
        strName = "DBMaintainceCfg.ini";
        pSettings = CreateSetting( &pDbmSettings, strName );
        break;

    case CommonDataType::CfgDevice :
        strName = "DeviceCfg.ini";
        pSettings = CreateSetting( &pDevSettings, strName );
        break;

    case CommonDataType::CfgSysSet :
        strName = "SysSetCfg.ini";
        pSettings = CreateSetting( &pSysSetSettings, strName );
        break;

    case CommonDataType::CfgPlate :
        strName = "PlateCfg.ini";
        pSettings = CreateSetting( &pPlateSettings, strName );
        break;

    default :
       pSettings = new QSettings( );
    break;
    }

    qDebug( ) << "QSettings Path : " << pSettings->fileName( ) << endl;

    return pSettings;
}

CCommonFunction::CCommonFunction(QObject *parent) :
    QObject(parent)
{
}

void CCommonFunction::DateTime2String( QDateTime &dtValue, QString& strText )
{
    strText = dtValue.toString( "yyyy-MM-dd HH:mm:ss" );
}

void CCommonFunction::Date2String( QDate &dtValue, QString& strText )
{
    strText = dtValue.toString( "yyyy-MM-dd" );
}

void CCommonFunction::Time2String( QTime &dtValue, QString& strText )
{
    strText = dtValue.toString( "HH:mm:ss" );
}

void CCommonFunction::GetTableName( CommonDataType::CardType type, QString& strTable )
{
    switch ( type ) {
    case CommonDataType::MonthlyCard :
        strTable = "monthcard";
        break;

    case CommonDataType::TimeCard :
        strTable = "tmpcard";
        break;

    case CommonDataType::ValueCard :
        strTable = "savecard";
        break;
    }
}

QTextCodec* CCommonFunction::GetTextCodec( )
{
    static QTextCodec* pCodec = NULL;

    if ( NULL != pCodec ) {
        return pCodec;
    }

    QList<QByteArray> lstCodec = pCodec->availableCodecs( );
    QString strText;
    bool bFound = false;

    for ( int nIndex = 0; nIndex < lstCodec.count( ); nIndex++ ) {
        QByteArray byData = lstCodec[ nIndex ];
        strText = QString( byData );
        qDebug( ) << strText << endl;

        if ( 0 == strText.toUpper().compare( "GB18030" ) ||
             0 == strText.toUpper().compare( "GBK" ) ||
             0 == strText.toUpper().compare( "GB2312" ) ) {
            bFound = true;
            break;
        }
    }

    if ( !bFound ) {
        strText = QString( "System" );
    }

    pCodec = QTextCodec::codecForName( strText.toAscii( ) );
    return pCodec;
}

QDateTime CCommonFunction::String2DateTime( QString& strText )
{
    return QDateTime::fromString( strText, QString( "yyyy-MM-dd HH:mm:ss" ) );
}

QDate CCommonFunction::String2Date( QString& strText )
{
    return QDate::fromString( strText, QString( "yyyy-MM-dd" ) );
}

QTime CCommonFunction::String2Time( QString& strText )
{
    return QTime::fromString( strText, QString( "HH:mm:ss" ) );
}

int CCommonFunction::GetDateTimeDiff( bool bDate, int nDiff, QDateTime &dtStart, QDateTime &dtEnd )
{
    if ( bDate ) {
        QTime time( 0, 0 );
        dtStart.setTime( time );
        dtEnd.setTime( time );
    }

    uint nSeconds = dtEnd.toTime_t( ) - dtStart.toTime_t( );
    int nDay = nSeconds / nDiff;

    return nDay;
}

void CCommonFunction::OperationSuccess( QString strInfo )
{
    MsgBox( NULL, "提示", "操作成功！", QMessageBox::Information );
}

int CCommonFunction::MsgBox(QWidget* pParent, QString strTitle, QString strText, QMessageBox::Icon nType, QString strStyle )
{
    int nRet = 0;
    QMessageBox msg( nType, strTitle, strText );
    msg.setAutoFillBackground( false );
    msg.setAttribute( Qt::WA_StyleSheet );
    msg.setAttribute( Qt::WA_SetStyle );
    msg.setStyleSheet( strStyle );
    msg.setParent( pParent );
    QPushButton* pOk = NULL;
    QPushButton* pCancel = NULL;

    switch ( nType ) {
    case QMessageBox::Question :
        //nRet = msg.question( pParent, strTitle, strText, QMessageBox::Ok | QMessageBox::Cancel );
        pOk = msg.addButton( "确定", QMessageBox::AcceptRole );
        pCancel = msg.addButton( "取消", QMessageBox::RejectRole );
        break;

    case QMessageBox::Information :
        //nRet = msg.information( pParent, strTitle, strText, QMessageBox::Ok );
        pOk = msg.addButton( "确定", QMessageBox::AcceptRole );
        break;

    case QMessageBox::Warning :
        //nRet = msg.warning( pParent, strTitle, strText, QMessageBox::Ok );
        pOk = msg.addButton( "确定", QMessageBox::AcceptRole );
        break;

    case QMessageBox::Critical :
        //nRet = msg.critical( pParent, strTitle, strText, QMessageBox::Ok );
        pOk = msg.addButton( "确定", QMessageBox::AcceptRole );
        break;

    case QMessageBox::NoIcon :
        break;

    }

    nRet = msg.exec( );
    QAbstractButton* pClicked = msg.clickedButton( );
    if (  pClicked == ( QAbstractButton* )pOk ) {
        nRet = QMessageBox::Ok;
    } else if ( pClicked == ( QAbstractButton* ) pCancel ){
        nRet = QMessageBox::Cancel;
    }

    return nRet;
}
int CCommonFunction::FindComboBoxItem( QComboBox* pCBX, QString strText )
{
    int nIndex = -1;

    int nItems = pCBX->count( );

    for ( int nItem = 0; nItem < nItems; nItem++ ) {
        if ( 0 == pCBX->itemText( nItem ).compare( strText ) ) {
            nIndex = nItem;
            break;
        }
    }

    return nIndex;
}

void CCommonFunction::FreeAllRows( QTableWidget* pTable )
{
    int nRows = pTable->rowCount( ) - 1;
    int nCols = pTable->columnCount( );
    for ( ; nRows >= 0 ; nRows-- ) {
        FreeRow( pTable, nRows, nCols );
    }
}

void CCommonFunction::FillTable( QTableWidget* pTable, int nRows, QStringList& lstRows )
{
    QString strValue;
    QTableWidgetItem* pItem = NULL;
    int nCols = pTable->columnCount( );

    int nBase = 0;
    pTable->setRowCount( nRows );

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        for ( int nCol = 0; nCol < nCols; nCol++ ) {
            strValue = lstRows[ nCol + nBase ];
            pItem = new QTableWidgetItem( strValue );
            pTable->setItem( nRow, nCol, pItem );
            pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        }

        nBase += nCols;
    }
}

void CCommonFunction::FillCardRightTable( QTableWidget* pTable, int nRows, QStringList& lstRows )
{
    QString strValue;
    QTableWidgetItem* pItem = NULL;
    int nCols = pTable->columnCount( );

    pTable->horizontalHeader( )->hideSection( 3 );

    int nBase = 0;
    pTable->setRowCount( nRows );
    QTimeEdit* pEdit = NULL;
    QTime time = QTime::currentTime( );

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        for ( int nCol = 0; nCol < nCols; nCol++ ) {
            strValue = lstRows[ nCol + nBase ];

            if ( 1 == nCol || 2 == nCol ) {
                time = String2Time( strValue );
                pEdit = new QTimeEdit( time );
                pEdit->setCalendarPopup( true );
                pTable->setCellWidget( nRow, nCol, pEdit );
            } else {
                pItem = new QTableWidgetItem( strValue );
                pTable->setItem( nRow, nCol, pItem );
                pItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
            }
        }

        nBase += nCols;
    }
}

void CCommonFunction::UpateCardRight( QStringList& lstRows, QTableWidget *pTable )
{
    if ( NULL == pTable ) {
        return;
    }

    QTimeEdit* pEdit = NULL;
    int nRows = pTable->rowCount( );
    int nCols = pTable->columnCount( );
    QTime time = QTime::currentTime( );
    QString strTime;

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        for ( int nCol = 1; nCol < nCols; nCol++ ) {
            if ( 3 != nCol ) {
                pEdit = ( QTimeEdit* )pTable->cellWidget( nRow, nCol );
                time = pEdit->time( );
                Time2String( time, strTime );
                lstRows << strTime;
            } else {
                lstRows << pTable->item( nRow, nCol )->text( );
            }
        }
    }
}

void CCommonFunction::CreateDiretory( QString& strPath, QString& strName )
{
    strPath = QApplication::applicationDirPath( ) + strName;
    QDir dir;

    if ( !dir.exists( strPath ) ) {
        dir.mkpath( strPath );
    }
}

void CCommonFunction::GetPath( QString &strFileName, CommonDataType::DataPath pathType )
{
    QString strName;
    switch ( pathType ) {
    case CommonDataType::PathCfgData :
        strName = "/Data/";
        break;

    case CommonDataType::PathSnapshot :
        strName = "/Snapshot/";
        break;

    case CommonDataType::PathUIImage :
        strName = "/Image/";
        break;

    case CommonDataType::PathPlate :
        strName = "/Plate/";
        break;

    case CommonDataType::PathExe :
        strName = "/";
        break;
    }

    QString strPath;
    CreateDiretory( strPath, strName );

    strFileName = strPath + strFileName;
}

void CCommonFunction::FreeRow( QTableWidget *pTable, int nRow, int nCols )
{
    if ( NULL == pTable ) {
        return;
    }

    for ( int nIndex = 0; nIndex < nCols; nIndex++ ) {
        delete pTable->item( nRow, nIndex );
    }

    pTable->removeRow( nRow );
}

bool CCommonFunction::IsDigital( QString strText )
{
    QString strDigiatl( "0123456789" );
    bool bRet = false;

    int nCount = strText.count( );

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        bRet = strDigiatl.contains( strText[ nIndex ] );
        if( false == bRet ) {
            break;
        }
    }

    return bRet;
}

int CCommonFunction::GetParkSection( QString &strName )
{
    QString strSection = "Section%1/%2";
    QSettings* pSet = GetSettings( CommonDataType::CfgDevice );
    int nSection = pSet->value( strSection.arg( "", "Count" ), QVariant( 0 ) ).toInt( );

    QString strPark;
    int nIndex = 0;
    int nTarget = -1;

    for ( nIndex = 0; nIndex < nSection; nIndex++ ) {
        strPark = pSet->value( strSection.arg( QString::number( nIndex ), "ParkName"  ), QVariant( "" ) ).toString( );
        if ( 0 == strName.compare( strName ) ) {
            nTarget = nIndex;
            break;
        }
    }

    return nTarget;
}

void CCommonFunction::GetAllChannels( QStringList &lstChannel, QString &strPark, bool bEnter )
{
    QSettings* pSet = GetSettings( CommonDataType::CfgDevice );
    QString strSection = "Section%1/%2";

    int nIndex = 0;
    int nTarget = GetParkSection( strPark );

    if ( -1 == nTarget ) {
        return;
    }

    int nItems = pSet->value( strSection.arg( QString::number( nTarget ), "DeviceCount" ), 0 ).toInt( );
    QString strItem = "%1%2";
    QString strChan;

    for ( nIndex = 0; nIndex < nItems; nIndex++ ) {
        int nDirection = pSet->value( strSection.arg( QString::number( nTarget ),
                                      strItem.arg( "Direction", QString::number( nIndex ) ) ), 0 ).toInt( );
        strChan = pSet->value( strSection.arg( QString::number( nTarget ),
                                               strItem.arg( "Device", QString::number( nIndex ) ) ), "" ).toString( );

        if ( strChan.isEmpty( ) ) {
            continue;
        }

        if ( 3 == nDirection && bEnter ) { // Enter
            lstChannel << strChan;
        } else if ( 4 == nDirection && !bEnter ) {
            lstChannel << strChan;
        }
    }
}

void CCommonFunction::GetAllParks( QStringList &lstPark )
{
    QSettings* pSet = GetSettings( CommonDataType::CfgDevice );
    QString strSection = "Section%1/%2";
    int nSection = pSet->value( strSection.arg( "", "Count" ), QVariant( 0 ) ).toInt( );
    QString strName;
    int nIndex = 0;

    for ( nIndex = 0; nIndex < nSection; nIndex++ ) {
        strName = pSet->value( strSection.arg( QString::number( nIndex ), "ParkName"  ), QVariant( "" ) ).toString( );
        if ( !strName.isEmpty( ) ) {
            lstPark << strName;
        }
    }
}

// 每X规则收费
bool CCommonFunction::AddFee1( QString& strMin, QString& strFoot,
                             int &nFee, int& nMinDiff, QSettings &pSet, QStringList& lstText )
{
    bool bContinueRead = false;

    int nValue = pSet.value( strMin, 0 ).toInt( );
    bContinueRead = ( 0 < nValue );

    if ( bContinueRead ) {
        nMinDiff -= nValue;
        nFee += pSet.value( strFoot, 0 ).toInt( );
        lstText << "Fee:" + QString::number( nFee );
        bContinueRead = ( 0 < nMinDiff );
    }

    return bContinueRead;
}

// 每X分钟 收Y角
void CCommonFunction::AddFee2( QString& strMin, QString& strFoot,
                              int &nFee, int& nMinDiff, QSettings &pSet, QStringList& lstText )
{
    int nFactor = 0;
    int nValue = pSet.value( strMin, 0 ).toInt( );
    bool bContinueRead = ( 0 < nValue );

    if ( bContinueRead ) {
        if ( nMinDiff <= nValue ) {
            nFactor = 1;
        } else {
            nFactor =  nMinDiff / nValue;
            if ( 0 != nMinDiff % nValue ) {
                nFactor++;
            }
        }

        nValue = pSet.value( strFoot, 0 ).toUInt( );

        if ( 0 == nValue ) {
            lstText << "规则有零项";
        }

        nFee += ( nValue * nFactor );
    }
}

// 规则1-6 收费 // 加 每X分钟 收Y角
void CCommonFunction::AddFee3( QString& strSection, QString& strMinute, QString& strFootSufix,
                              int &nFee, int& nMinDiff, QSettings &pSet, QStringList& lstText )
{
    if ( 0 >= nMinDiff ) {
        lstText << "时间差不大于零";
        return;
    }

    int nDiff = nMinDiff;

    bool bContinueRead = false;
    QString strMin;
    QString strFoot;
    QString strIndex = "%1rule%2%3";

    for ( int nIndex = 1; nIndex <= 6; nIndex++ ) { // Rule1 - Rule6
        strMin = strIndex.arg( strSection, QString::number( nIndex ), strMinute );
        strFoot = strIndex.arg( strSection, QString::number( nIndex ), strFootSufix );
        bContinueRead = AddFee1( strMin, strFoot, nFee, nMinDiff, pSet, lstText );
        if ( false == bContinueRead ) {
            break;
        }
    }

    // 加 每X分钟 收Y角
    if ( nMinDiff > 0 ) { // Per minute / foot
        strIndex = "%1per%2";
        strMin = strIndex.arg( strSection, strMinute );
        strFoot = strIndex.arg( strSection, "Min" + strFootSufix );
        AddFee2( strMin, strFoot, nFee, nMinDiff, pSet, lstText );
    }

    nMinDiff = nDiff;
}

void CCommonFunction::AddFee4( QString& strSection, QString& strMinute, QString& strFootSufix,
                               int &nFee, int& nMinDiff, QSettings &pSet, QStringList& lstText )
{
    if ( 0 >= nMinDiff ) {
        lstText << "时间差不大于零";
        return;
    }

    int nLimitMin = pSet.value( strSection.arg( "perMinNoSectionLimit" ), 0 ).toInt( );
    int nLimitMinFoot = pSet.value( strSection.arg( "perMinFootNoSection" ), 0 ).toInt( );
    int nPeriodMin = pSet.value( strSection.arg( "perMinNoSectionFirst" ), 0 ).toInt( );
    strSection = strSection.arg( "" );

    bool bLimit = ( 0 != nLimitMin );
    int nLimitMulti = 0;
    int nRemainder = 0;
    int nQuota = 0;

    if ( bLimit ) {
        nLimitMulti = nMinDiff / nLimitMin;
        nQuota = nLimitMulti * nLimitMinFoot;
        nRemainder = nMinDiff % nLimitMin;

        if ( ( 0 == nLimitMulti ) || ( 1 <= nLimitMulti && 1 <= nPeriodMin ) ) {
            AddFee3( strSection, strMinute, strFootSufix, nFee, nRemainder, pSet, lstText );
        } else if ( 1 <= nLimitMulti && 0 == nPeriodMin && 0 < nRemainder ) {
            // Per minute / foot
            QString strIndex = "%1per%2";
            QString strMin = strIndex.arg( strSection, strMinute );
            QString strFoot = strIndex.arg( strSection, "Min" + strFootSufix );
            AddFee2( strMin, strFoot, nFee, nRemainder, pSet, lstText );
        }

        if ( nFee > nLimitMinFoot ) {
            nFee = nLimitMinFoot;
        }

        nFee += nQuota;
    } else {
        AddFee3( strSection, strMinute, strFootSufix, nFee, nMinDiff, pSet, lstText );
    }
}

int CCommonFunction::GetDateTimeDiff( QDateTime &dt1, QDateTime &dt2, int nT )
{
    return ( dt2.toTime_t( ) - dt1.toTime_t( ) ) / 60 - nT * 24 * 60;
}

int CCommonFunction::GetTimeDiff( QTime time1, QTime time2 )
{
    int nDiff = ( time2.hour( ) - time1.hour( ) ) * 3600 +
                ( time2.minute( ) - time1.minute( ) ) * 60 +
                ( time2.second( ) - time1.second( ) );
    nDiff /= 60;

    return nDiff;
}

int CCommonFunction::GetQuotaValue(int nQuota, int nFee)
{
    if ( 0 >= nQuota ) {
        return nFee;
    }

    return ( nQuota <= nFee ) ? nQuota : nFee;
}

bool CCommonFunction::GetSectionAround( QTime& tSectionBegin, QTime& tSectionEnd, QDateTime& dtStart, QDateTime& dtEnd )
{
    bool bRet = false;
    bool bReverse = ( tSectionBegin > tSectionEnd );

    if ( false == bReverse ) {
        if ( dtStart.time( ) >= tSectionBegin && dtEnd.time( ) <= tSectionEnd ) { // 段内

        }
    } else {
        if ( dtStart.time( ) >= tSectionBegin && dtEnd.time( ) <= tSectionEnd ) { // 段内

        }
    }

    return bRet;
}

bool CCommonFunction::GetSectionAround( QTime& tSectionBegin, QTime& tSectionEnd, QDateTime& dtStart )
{
    bool bRet = false;
    bool bReverse = ( tSectionBegin > tSectionEnd );

    if ( false == bReverse ) {
        if ( tSectionBegin <= dtStart.time( ) && dtStart.time( ) <= tSectionEnd ) { // 段内
            bRet = true;
        }
    } else {
        if ( tSectionBegin <= dtStart.time( ) || dtStart.time( ) <= tSectionEnd ) { // 段内
            bRet = true;
        }
    }

    return bRet;
}

int CCommonFunction::CalculateFee( QSettings& pSet, QString &strParkName, QString &strCarType,
                                   QDateTime& dtStart, QDateTime& dtEnd, QStringList& lstText, bool bManual, bool bSect )
{
    int nFee = 0;

    if ( dtStart >= dtEnd ) {
        lstText << "入时间不小于离时间";
        return nFee;
    }

    int nMinDiff = ( dtEnd.toTime_t( ) - dtStart.toTime_t( ) ) / 60;

    QString strSection = QString( "%1/%2/" ).arg( strParkName, strCarType );

    strSection += "%1";
    int nLimit = 0;
    int nValue = pSet.value( strSection.arg( "LimitTime" ), 0 ).toInt( );
    nLimit = nValue;
    if ( nValue >= nMinDiff ) { // 宽限
        lstText << "在宽限时间内";
        return nFee;
    } else {
       nMinDiff -= nValue;
    }

    nValue = pSet.value( strSection.arg( "NoFullTime" ), 0 ).toInt( );
    if ( nValue > nMinDiff ) { // 不足
        lstText << "在不足时间内";
        return nFee;
    }

    // //////////////2013.3.25/////把dtStart修改了，后面就不需要再修改。开始时间加上宽限时间，往后推迟了xx分钟。
    dtStart = dtStart.addSecs( nLimit * 60 );

    QString strMinInner = "MinInner";
    QString strMinOut = "MinOuter";

    QString strFootInner = "FootInner";
    QString strFootOut = "FootOuter";

    pSet.sync( );

    bool bSection = bManual ? bSect : pSet.value( strSection.arg( "Section" ), false ).toBool( ); // 是否分段

    if ( bSection ) { // 分段
        QTime tStart = pSet.value( strSection.arg( "Section1" ), QTime::currentTime( ) ).toTime( );
        QTime tEnd = pSet.value( strSection.arg( "Section2" ), QTime::currentTime( ) ).toTime( );

        int nFeeInner = 0;
        int nFeeOuter = 0;

        int nLimitFootInner = pSet.value( strSection.arg( "LimitFootInner" ), 0 ).toInt( );
        int nLimitFootOuter = pSet.value( strSection.arg( "LimitFootOuter" ), 0 ).toInt( );

        strSection = strSection.arg( "" );
        int nTerm = ( dtStart.secsTo( dtEnd ) ) / ( 60 * 24 * 60);

        QTime tTmpStart = dtStart.time( ); // 周期开头部分
       // tTmpStart = tTmpStart.addSecs( nLimit *60 ); // 宽限时间，所以起始时间就延后了。修改了dtStart时间。
        QTime tTmpEnd = dtEnd.time( ); // 周期结尾部分
        QTime t24Hour( 23, 59, 59 );
        QTime t0Hour( 0, 0, 0 );
        //bool bTimeEqual = false ;

        if ( 0 != nTerm ) { //  跨完整的一天
            // 段内
            nMinDiff = tStart.msecsTo( tEnd ) / 1000;
            if ( t24Hour == tEnd ) { // 无法设置24：0：0就用23：59：59来代替。
                nMinDiff++;
            }

            nMinDiff /= 60;
            AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
            nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

             // 段外
            nMinDiff = 24 * 60 - nMinDiff;
            AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
            nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

            nFee *= nTerm;

            // Precision Minute 乘以-1把秒减掉。
            tTmpStart.addSecs( tTmpStart.second( ) * -1 );
            tTmpEnd.addSecs( tTmpEnd.second( ) * -1 );
            tStart.addSecs( tStart.second( ) * -1 );
            tEnd.addSecs( tEnd.second( ) * -1 );

          //  if ( tTmpStart == tTmpEnd && ( tTmpStart != tEnd || tTmpStart != tStart ) ) { // 后部分永远为TRUE
          //      bTimeEqual = true;
         //   }
        }

        int nDayDiff = dtStart.date( ).daysTo( dtEnd.date( ) );

        if ( 0 != nDayDiff && tTmpStart >= tTmpEnd ) { //不完整跨天
            if ( tTmpStart > tTmpEnd ) {
                if ( tStart <= tTmpStart && tTmpStart <= tEnd ) { //1
                    if ( tTmpEnd < tStart ) { //13
                        nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = 24 * 60 - GetTimeDiff( tTmpEnd, tStart ) -
                                          GetTimeDiff( tStart, tEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else { //14ok
                        nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                        //////////////////////2013.3.27////
                         if( tEnd == t24Hour )
                         {
                             nMinDiff++;
                         }
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        /////////////////////////2013.3.22
                        int nFeeInnerSum = nFeeInner;

                        nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );

                        nFeeInnerSum += nFeeInner;
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInnerSum );

                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd );
                        //////////////////////2013.3.27////
                         if( tEnd == t24Hour )
                         {
                             nMinDiff--;
                         }
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                } else {
                    if ( tEnd < tTmpStart && tTmpStart <= t24Hour ) { // 2
                        if ( tTmpEnd < tStart ) { // 22ok
                            nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tTmpEnd, tStart ) -
                                              GetTimeDiff( tEnd, tTmpStart );
                            nFeeOuter = 0;
                            AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        } else if ( tStart <= tTmpEnd && tTmpEnd <= tEnd ) {//23ok
                            nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                            nFeeInner = 0;
                            AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                            nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tEnd, tTmpStart );
                            nFeeOuter = 0;
                            AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        } else if ( tEnd < tTmpEnd ) {//24
                            nMinDiff = GetTimeDiff( tStart, tEnd );
                            nFeeInner = 0;
                            AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                            //////////////////////////2013.3.27
                            nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tTmpEnd, tTmpStart ); //直接求
                            nFeeOuter = 0;
                            AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                        }
                    } else { // tTmpStart > t24Hour && tTmpStart < tStart //34
                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        /////////////////////////////2013.3.27 把后面的合并了，就不必麻烦分两次计算段外。
                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tTmpEnd, tTmpStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                }
            }
            ///////////////////2013.3.28因为此种情况无操作，可以不要。时间点重合说明它至少跨了一个完整天。在那部分就计算了。
           // else if ( tTmpStart == tTmpEnd ) { // 时间点重合，但不与分段时间点重合
           //     qDebug() << "时间点重合" << endl;
                ////////////////////2013.3.22不论时间点在哪儿重合，都是计算0-24这一整圈的，其实就是没有零散时间，只有整天，此时nFee的值就是。
           // }
         } else { //  tTmpStart < tTmpEnd
            if ( tStart <= tTmpStart && tTmpStart <= tEnd )  { // 1
                if ( tTmpEnd <=tEnd  ) { //11 ok
                    nMinDiff = GetDateTimeDiff( dtStart, dtEnd, nTerm ); // 求取的是除去整天后的零散时间
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );
                } else if ( tTmpEnd <= t24Hour ) { //12 ok
                    nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = GetTimeDiff( tEnd, tTmpEnd );
                    nFeeOuter = 0;
                    AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                }
                /////////////////////2013.3.27根本不会走到这儿来，在tTmpStart >= tTmpEnd的情况下包含了一下情况。
                //此时tTmpStart < tTmpEnd且tStart <= tTmpStart  <= tEnd反正不会进入下面情况。所以删除了。
            }

            else { // 大前提：tTmpStart < tTmpEnd
                if ( tEnd < tTmpStart && tTmpStart <= t24Hour ) { // 2
                    if ( tTmpEnd <= t24Hour ) { //21 ok
                        nMinDiff = GetDateTimeDiff( dtStart, dtEnd, nTerm );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                }
                else if ( t0Hour  <= tTmpStart && tTmpStart < tStart ) {  // 大前提：tTmpStart < tTmpEnd
                    if ( tTmpEnd <= tStart ) { //31ok
                        nMinDiff = GetDateTimeDiff( dtStart, dtEnd, nTerm );//
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if (tStart <= tTmpEnd && tTmpEnd <= tEnd  ) { //32
                        nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff =GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if (  tTmpEnd > tEnd && tTmpEnd <= t24Hour  ) { //33 34 ;34不会到此来。所以直接判断33情况。
                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        int nFeeOuterSum = nFeeOuter;

                        nMinDiff = GetTimeDiff( tEnd, tTmpEnd ); // 不能使用+=
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFeeOuterSum += nFeeOuter;
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuterSum );
                    }
                }
            }
        }
    } else { // 不分段
        AddFee4( strSection, strMinInner, strFootInner, nFee, nMinDiff, pSet, lstText );
    }

    return nFee / 10;
}

// Delete content in TariffCfg.ini except [ CarType ]
// alter table parkadmin.feerate1 add column Section tinyint( 1 ) default 0;
#if false
int CCommonFunction::CalculateFee( QSettings& pSet, QString &strParkName, QString &strCarType,
                                   QDateTime& dtStart, QDateTime& dtEnd, QStringList& lstText, bool bManual, bool bSect )
{
    int nFee = 0;

    if ( dtStart >= dtEnd ) {
        lstText << "入时间不小于离时间";
        return nFee;
    }

    int nMinDiff = ( dtEnd.toTime_t( ) - dtStart.toTime_t( ) ) / 60;

    QString strSection = QString( "%1/%2/" ).arg( strParkName, strCarType );

    strSection += "%1";
    int nLimit = 0;
    int nValue = pSet.value( strSection.arg( "LimitTime" ), 0 ).toInt( );
    nLimit = nValue;
    if ( nValue >= nMinDiff ) { // 宽限
        lstText << "在宽限时间内";
        return nFee;
    } else {
       nMinDiff -= nValue;
    }

    nValue = pSet.value( strSection.arg( "NoFullTime" ), 0 ).toInt( );
    if ( nValue > nMinDiff ) { // 不足
        lstText << "在不足时间内";
        return nFee;
    }// else {
    //   nMinDiff -= nValue;
    //}

    //////////////////////////////
    //
    //////////////////////////////
    QString strMinInner = "MinInner";
    QString strMinOut = "MinOuter";

    QString strFootInner = "FootInner";
    QString strFootOut = "FootOuter";

    pSet.sync( );

    bool bSection = bManual ? bSect : pSet.value( strSection.arg( "Section" ), false ).toBool( ); // 是否分段

    if ( bSection ) { // 分段
        QTime tStart = pSet.value( strSection.arg( "Section1" ), QTime::currentTime( ) ).toTime( );
        QTime tEnd = pSet.value( strSection.arg( "Section2" ), QTime::currentTime( ) ).toTime( );

        //int nDiffOuter = 0;
        //int nDiffInner = 0;
        int nFeeInner = 0;
        int nFeeOuter = 0;

        int nLimitFootInner = pSet.value( strSection.arg( "LimitFootInner" ), 0 ).toInt( );
        int nLimitFootOuter = pSet.value( strSection.arg( "LimitFootOuter" ), 0 ).toInt( );
        //bool bInside = GetSectionAround( tStart, tEnd, dtStart );

        strSection = strSection.arg( "" );
        int nTerm = dtStart.secsTo( dtEnd ) / ( 60 * 24 * 60);
        QTime tTmpStart = dtStart.time( ); // 周期开头部分
        QTime tTmpEnd = dtEnd.time( ); // 周期结尾部分
        QTime t24Hour( 23, 59, 59 );
        QTime t0Hour( 0, 0, 0 );
        bool bTimeEqual = false ;

        if ( 0 != nTerm ) { //  跨完整的一天
            // 段内
            nMinDiff = tStart.msecsTo( tEnd ) / 1000;
            if ( t24Hour == tEnd ) {
                nMinDiff++;
            }

            nMinDiff /= 60;
            AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
            nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

             // 段外
            nMinDiff = 24 * 60 - nMinDiff;
            AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
            nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

            nFee *= nTerm;

#if false
            //QTime& tTmpStart = dtStart.time( ); // 周期开头部分
            if ( tStart <= tTmpStart && tTmpStart <= tEnd )  { //
                if ( tTmpEnd <=tEnd  ) {
                    nMinDiff = GetTimeDiff( tTmpStart, tTmpEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );
                } else if ( tTmpEnd <= t24Hour ) {
                    nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = GetTimeDiff( tEnd, tTmpEnd );
                    nFeeOuter = 0;
                    AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                } else if ( tTmpEnd < tStart ) {
                    nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = 24 * 60 - GetTimeDiff( tTmpStart, tStart ) - GetTimeDiff( tStart, tEnd );
                    nFeeOuter = 0;
                    AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                } else if (  tTmpEnd >= tStart ) {
                    nMinDiff = GetTimeDiff( tTmpStart, tEnd ) + GetTimeDiff( tStart, tTmpEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd );
                    nFeeOuter = 0;
                    AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                }
            } else {
                if ( tEnd < tTmpStart && tTmpStart <= t24Hour ) {
                    if ( tTmpEnd <= t24Hour ) {
                        nMinDiff = GetTimeDiff( tTmpStart, tTmpEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if ( tTmpEnd < tStart ) {
                        nMinDiff = 24 * 60 - GetTimeDiff( tTmpEnd, tStart ) -
                                          GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tEnd, tTmpStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if ( tStart <= tTmpEnd && tTmpEnd <= tEnd  ) {
                        nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tEnd, tTmpStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if ( tEnd < tTmpEnd ) {
                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) -
                                         GetTimeDiff( tEnd, sTmpStart) + GetTimeDiff( tEnd, tTmpEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                } else if ( t0Hour  <= tTmpStart && tTmpStart < tStart ) {
                    if ( tTmpEnd <= tStart ) {
                        nMinDiff = GetTimeDiff( tTmpStart, tTmpEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if (tStart <= tTmpEnd && tTmpEnd <= tEnd  ) {
                        nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff =GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if (  tTmpEnd > tEnd  ) {
                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = GetTimeDiff( tTmpStart, tStart );
                        if ( tTmpEnd <= t24Hour ) {
                            nMinDiff += GetTimeDiff( tEnd, tTmpEnd );
                        } else if ( tTmpEnd < tStart ) {
                            nMinDiff += 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tTmpEnd, tStart );
                        }
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                }
            }

#if false
            if ( bInside ) { // 段内
                AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                nFee += GetQuotaValue( nLimitFootInner, nFeeInner );
            } else { // 段外
                AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
            }
#endif
#endif

            // Precision Minute
            tTmpStart.addSecs( tTmpStart.second( ) * -1 );
            tTmpEnd.addSecs( tTmpEnd.second( ) * -1 );
            tStart.addSecs( tStart.second( ) * -1 );
            tEnd.addSecs( tEnd.second( ) * -1 );

            if ( tTmpStart == tTmpEnd && ( tTmpStart != tEnd || tTmpStart != tStart ) ) {
                bTimeEqual = true;
            }
        }

        //QTime& tTmpStart = dtStart.time( ); // 周期开头部分
        int nDayDiff = dtStart.date( ).daysTo( dtEnd.date( ) );
        if ( 0 != nDayDiff && tTmpStart >= tTmpEnd ) { //不完整跨天
            if ( tTmpStart > tTmpEnd ) {
                if ( tStart <= tTmpStart && tTmpStart <= tEnd ) {
                    if ( tTmpEnd < tStart ) {
                        nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = 24 * 60 - GetTimeDiff( tTmpEnd, tStart ) -
                                          GetTimeDiff( tStart, tEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else {
                        nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                } else {
                    if ( tEnd < tTmpStart && tTmpStart <= t24Hour ) {
                        if ( tTmpEnd < tStart ) {
                            nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tTmpEnd, tStart ) -
                                              GetTimeDiff( tEnd, tTmpStart );
                            nFeeOuter = 0;
                            AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        } else if ( tStart <= tTmpEnd && tTmpEnd <= tEnd ) {
                            nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                            nFeeInner = 0;
                            AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                            nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tEnd, tTmpStart );
                            nFeeOuter = 0;
                            AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        } else if ( tEnd < tTmpEnd ) {
                            nMinDiff = GetTimeDiff( tStart, tEnd );
                            nFeeInner = 0;
                            AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                            nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tEnd, tTmpStart );
                            nFeeOuter = 0;
                            AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                            nMinDiff = GetTimeDiff( tEnd, tTmpEnd );
                            nFeeOuter = 0;
                            AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                            nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                        }
                    } else {
                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tTmpStart, tStart ) -
                                          GetTimeDiff( tTmpEnd, tTmpStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                }
            } else if ( bTimeEqual ) { // 时间点重合，但不与分段时间点重合
                nFee -= nFee / nTerm;

                if ( tStart < tTmpStart && tTmpStart < tEnd ) {
                    nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd );
                    nFeeOuter = 0;
                    AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                } else {
                    if ( tEnd < tTmpStart && tTmpStart <= t24Hour ) {
                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tEnd, tTmpEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        nMinDiff = GetTimeDiff( tEnd, tTmpEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if ( t0Hour <= tTmpStart && tTmpStart < tStart ) {
                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        //nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter ); // 郑敏
                        int nFeeOuterSum = nFeeOuter;  // 郑敏


                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFeeOuterSum += nFeeOuter;  // 郑敏

                        //nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );  // 郑敏
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuterSum );  // 郑敏

                    }
                }
            }
        } else {
            if ( tStart <= tTmpStart && tTmpStart <= tEnd )  { //
                if ( tTmpEnd <=tEnd  ) {
                    nMinDiff = GetDateTimeDiff( dtStart, dtEnd, nTerm );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );
                } else if ( tTmpEnd <= t24Hour ) {
                    nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = GetTimeDiff( tEnd, tTmpEnd );
                    nFeeOuter = 0;
                    AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                } else if ( tTmpEnd < tStart ) {
                    nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = 24 * 60 - GetTimeDiff( tTmpEnd, tStart ) - GetTimeDiff( tStart, tEnd );
                    nFeeOuter = 0;
                    AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                } else if (  tTmpEnd >= tStart ) {
                    nMinDiff = GetTimeDiff( tTmpStart, tEnd );// + GetTimeDiff( tStart, tTmpEnd )
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                    nFeeInner = 0;
                    AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                    nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd );
                    nFeeOuter = 0;
                    AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                }
            } else {
                if ( tEnd < tTmpStart && tTmpStart <= t24Hour ) {
                    if ( tTmpEnd <= t24Hour ) {
                        nMinDiff = GetDateTimeDiff( dtStart, dtEnd, nTerm );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if ( tTmpEnd < tStart ) {
                        nMinDiff = 24 * 60 - GetTimeDiff( tTmpEnd, tStart ) -
                                          GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tEnd, tTmpStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if ( tStart <= tTmpEnd && tTmpEnd <= tEnd  ) {
                        nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tEnd, tTmpStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if ( tEnd < tTmpEnd ) {
                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = 24 * 60 - GetTimeDiff( tStart, tEnd ) -
                                         GetTimeDiff( tEnd, tTmpStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        nMinDiff = GetTimeDiff( tEnd, tTmpEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                } else if ( t0Hour  <= tTmpStart && tTmpStart < tStart ) {
                    if ( tTmpEnd <= tStart ) {
                        nMinDiff = GetDateTimeDiff( dtStart, dtEnd, nTerm );//
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if (tStart <= tTmpEnd && tTmpEnd <= tEnd  ) {
                        nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff =GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if (  tTmpEnd > tEnd  ) {
                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        if ( tTmpEnd <= t24Hour ) {
                            nMinDiff += GetTimeDiff( tEnd, tTmpEnd );
                        } else if ( tTmpEnd < tStart ) {
                            nMinDiff += 24 * 60 - GetTimeDiff( tStart, tEnd ) - GetTimeDiff( tTmpEnd, tStart );
                        }

                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                }
            }
        }

#if false
        else {

        // y = 24t + DeltaT1 + DeltaT2; ( t = 0,1,2,.....n )
        // t = ( Dt2 - Dt1 ) / ( 24 * 60 )
        // In one day

        // t == 0 // d1 = d2 // d1 != d2

        // d1 == d2
            int nDayDiff = dtStart.date( ).daysTo( dtEnd.date( ) );
            if ( 0 != nDayDiff ) {
            } else  {
                if ( tTmpStart < tStart ) { // 段外
                    if ( tTmpEnd < tStart ) {
                        nMinDiff = GetTimeDiff( tTmpStart, tTmpEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    } else if ( tStart <= tTmpEnd && tTmpEnd <= tEnd ) {
                        nMinDiff = GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        nMinDiff = GetTimeDiff( tStart, tTmpEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );
                    } else if ( tEnd < tTmpEnd && tTmpEnd <= t24Hour ) {
                        nMinDiff = GetTimeDiff( tTmpStart, tStart );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );

                        nMinDiff = GetTimeDiff( tStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = GetTimeDiff( tEnd, tTmpEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                } else if ( tStart <= tTmpStart && tTmpStart <= tEnd ) { // 部分段内外
                    if ( tTmpEnd <= tEnd ) {
                        nMinDiff = GetTimeDiff( tTmpStart, tTmpEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );
                    } else if ( tEnd < tTmpEnd && tTmpEnd <= t24Hour ) {
                        nMinDiff = GetTimeDiff( tTmpStart, tEnd );
                        nFeeInner = 0;
                        AddFee3( strSection, strMinInner, strFootInner, nFeeInner, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootInner, nFeeInner );

                        nMinDiff = GetTimeDiff( tEnd, tTmpEnd );
                        nFeeOuter = 0;
                        AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                        nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                    }
                } else if ( tEnd < tTmpStart && tTmpStart <= t24Hour ) {
                    nMinDiff = GetTimeDiff( tTmpStart, tTmpEnd );
                    nFeeOuter = 0;
                    AddFee3( strSection, strMinOut, strFootOut, nFeeOuter, nMinDiff, pSet, lstText );
                    nFee += GetQuotaValue( nLimitFootOuter, nFeeOuter );
                }
            }
        }
#endif
    } else { // 不分段
        //strSection = strSection.arg( "" );
        AddFee4( strSection, strMinInner, strFootInner, nFee, nMinDiff, pSet, lstText );
    }

    return nFee / 10;
}
#endif
