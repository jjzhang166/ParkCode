#include "qcontrollercommon.h"
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <windows.h>


//
// Common data, function, class
//

int QControllerCommon::nSleepTime = 250;

QControllerCommon::QControllerCommon()
{
}

void QControllerCommon::GetPath( QString &strPath, const LedControll::EPath eType )
{
    switch ( eType ) {
    case LedControll::PathConfig :
        strPath = qApp->applicationDirPath( ) + QDir::separator( ) + "LedControl";
        break;
    }
}

void QControllerCommon::PrintDebugInfo( QString strInfo )
{
    qDebug( ) << Q_FUNC_INFO << strInfo << endl;
}

QTextCodec* QControllerCommon::GetTextCodec( )
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

void QControllerCommon::InitApp( )
{
    QString strConfigPath;
    bool bRet = false;
    QDir dir;

    GetPath( strConfigPath, LedControll::PathConfig );
    if ( !dir.exists( strConfigPath ) ) {
        bRet = dir.mkpath( strConfigPath );

        if ( !bRet ) {
            PrintDebugInfo( QString( "dir.mkpath( %1 ) failed." ).arg( strConfigPath ) );
        }
    }
}

QSettings& QControllerCommon::GetConfigSettings( )
{
    static QSettings* pSettings = NULL;

    if ( NULL != pSettings ) {
        return *pSettings;
    }

    QString strFile;
    GetPath( strFile, LedControll::PathConfig );
    strFile += QDir::separator( ) + QString( "Led.ini" );

    pSettings = new QSettings( strFile, QSettings::IniFormat );

    pSettings->setIniCodec( GetTextCodec( ) );

    return *pSettings;
}

int QControllerCommon::GetWaitTime( )
{
    QSettings &settings = GetConfigSettings( );
    nSleepTime = settings.value( "SerialPort/WaitTime", 0 ).toInt( );

    return nSleepTime;
}

void QControllerCommon::GetPorts( QStringList &lstPorts )
{
    HKEY hHandle;
    DWORD dwIndex = 0;
    wchar_t cName[ 512 ] = { 0 };
    DWORD dwLen = 512;
    BYTE byValue[ 512 ] = { 0 };

    LONG lRet = RegOpenKey( HKEY_LOCAL_MACHINE, L"HARDWARE\\DEVICEMAP\\SERIALCOMM", &hHandle );
    if ( ERROR_SUCCESS != lRet ) {
        return;
    }

    while ( ERROR_SUCCESS == RegEnumValue( hHandle, dwIndex++, cName, &dwLen, NULL, NULL, byValue, &dwLen ) ) {
        lstPorts << QString::fromUtf16( ( const ushort* ) byValue ).toUpper( );
    }

    lRet = RegCloseKey( hHandle );
}

void QControllerCommon::SaveSPConfig( const LedControll::SComConfig &sConfig )
{
    QSettings &settings = GetConfigSettings( );

    settings.setValue( "SerialPort/Com", sConfig.nComName );
    settings.setValue( "SerialPort/BaudRate", sConfig.nBaudRate );
    settings.setValue( "SerialPort/DataBit", sConfig.nDataBit );
    settings.setValue( "SerialPort/Parity", sConfig.nParity );
    settings.setValue( "SerialPort/StopBit", sConfig.nStopBit );
    settings.setValue( "SerialPort/FlowCtrl", sConfig.nFlowCtrl );

    settings.setValue( "SerialPort/WaitTime", nSleepTime );
}

void QControllerCommon::GetSPConfig( LedControll::SComConfig &sConfig )
{
    QSettings &settings = GetConfigSettings( );

    sConfig.nComName = settings.value( "SerialPort/Com", 0 ).toUInt( );
    sConfig.nBaudRate = settings.value( "SerialPort/BaudRate", 10 ).toUInt( );
    sConfig.nDataBit = settings.value( "SerialPort/DataBit", 3 ).toUInt( );
    sConfig.nParity = settings.value( "SerialPort/Parity", 2 ).toUInt( );
    sConfig.nStopBit = settings.value( "SerialPort/StopBit", 0 ).toUInt( );
    sConfig.nFlowCtrl = settings.value( "SerialPort/FlowCtrl", 0 ).toUInt( );
}

void QControllerCommon::SaveModemConfig( const quint8 nDataFlowCtrl, const quint8 nAutoReply )
{
    QSettings &settings = GetConfigSettings( );

    settings.setValue( "Modem/DataFlowCtrl", nDataFlowCtrl );
    settings.setValue( "Modem/AutoReply", nAutoReply );
}

void QControllerCommon::GetModemConfig( quint8& nDataFlowCtrl, quint8& nAutoReply )
{
    QSettings &settings = GetConfigSettings( );

    nDataFlowCtrl = settings.value( "Modem/DataFlowCtrl", 0 ).toUInt( );
    nAutoReply = settings.value( "Modem/AutoReply", 0 ).toUInt( );
}

void QControllerCommon::SaveBufferConfig( const qint32 nInBuffer, const qint32 nOutBuffer )
{
    QSettings &settings = GetConfigSettings( );

    settings.setValue( "Buffer/InSize", nInBuffer );
    settings.setValue( "Buffer/OutSize", nOutBuffer );
}

void QControllerCommon::GetBufferConfig( qint32& nInBuffer, qint32& nOutBuffer )
{
    QSettings &settings = GetConfigSettings( );

    nInBuffer = settings.value( "Buffer/InSize", 8192 ).toInt( );
    nOutBuffer = settings.value( "Buffer/OutSize", 8192 ).toInt( );
}

void QControllerCommon::SaveSystemConfig( LedControll::SSysConfig &sConfig, const QString &strFile )
{
    QSettings settings( strFile, QSettings::IniFormat );
    settings.setIniCodec( GetTextCodec( ) );
    SaveSystemConfig( sConfig, settings );
}

void QControllerCommon::SaveSystemConfig( LedControll::SSysConfig &sConfig, QSettings &settings )
{
    settings.setValue( "System/RunMode", sConfig.nRunMode );
    settings.setValue( "System/SyncMode", sConfig.nSyncMode );
    settings.setValue( "System/BaseRadiance", sConfig.nBaseRadiance );
    settings.setValue( "System/ActivatedSwitch", sConfig.nActivatedSwitch );
    settings.setValue( "System/FrequencyTime", sConfig.nFrequencyTime );
    settings.setValue( "System/FrequencyRadiance", sConfig.nFrequencyRadiance );
    settings.setValue( "System/FlashTime", sConfig.nFlashTime );
    settings.setValue( "System/FlashRadiance", sConfig.nFlashRadiance );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    settings.setValue( "System/NewFlashTime", sConfig.sNewConfig.nFlashTime );
    settings.setValue( "System/NewFlashRadiance", sConfig.sNewConfig.nFlashRadiance );
    settings.setValue( "System/NewFlashActivated", sConfig.sNewConfig.nFlashActivated );
    settings.setValue( "System/NewFlashSwitch", sConfig.sNewConfig.nFlashSwitch );
    settings.setValue( "System/NewFlashMode", sConfig.sNewConfig.nFlashMode );

    settings.setValue( "System/NewFrequencyTime", sConfig.sNewConfig.nFrequencyTime );
    settings.setValue( "System/NewFrequencyRadiance", sConfig.sNewConfig.nFrequencyRadiance );
    settings.setValue( "System/NewFrequencyActivated", sConfig.sNewConfig.nFrequencyActivated );
    settings.setValue( "System/NewFrequencySwitch", sConfig.sNewConfig.nFrequencySwitch );
    settings.setValue( "System/NewFrequencyMode", sConfig.sNewConfig.nFrequencyMode );
    settings.setValue( "System/NewFrameFreqMode", sConfig.sNewConfig.nFrameFreqMode );
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SaveLocation( settings, sConfig.cLocation, false );
    SaveLocation( settings, sConfig.sNewConfig.cLocation, true );
}

void QControllerCommon::SaveLocation( QSettings& settings, wchar_t *pBuffer, const bool bNewDevice )
{
    pBuffer[ LedControll::nLOCATION_SIZE - 1 ] = 0;
    QString strLocation = QString::fromWCharArray( pBuffer );
    settings.setValue( QString( "System/Location%1" ).arg( bNewDevice ? "New" : "" ), strLocation );
}

void QControllerCommon::SaveSystemConfig( LedControll::SSysConfig &sConfig )
{
    QSettings &settings = GetConfigSettings( );
    SaveSystemConfig( sConfig, settings );
}

void QControllerCommon::GetSystemConfig( LedControll::SSysConfig &sConfig, const QString &strFile )
{
    QSettings settings( strFile, QSettings::IniFormat );
    settings.setIniCodec( GetTextCodec( ) );
    GetSystemConfig( sConfig, settings );
}

void QControllerCommon::GetSystemConfig( LedControll::SSysConfig &sConfig, QSettings &settings )
{
    sConfig.nRunMode = settings.value( "System/RunMode", 1 ).toUInt( );
    sConfig.nSyncMode = settings.value( "System/SyncMode", 1 ).toUInt( );
    sConfig.nBaseRadiance = settings.value( "System/BaseRadiance", 0 ).toUInt( );
    sConfig.nActivatedSwitch = settings.value( "System/ActivatedSwitch", 0 ).toUInt( );
    sConfig.nFrequencyTime = settings.value( "System/FrequencyTime", 0 ).toUInt( );
    sConfig.nFrequencyRadiance = settings.value( "System/FrequencyRadiance", 0 ).toUInt( );
    sConfig.nFlashTime = settings.value( "System/FlashTime", 0 ).toUInt( );
    sConfig.nFlashRadiance = settings.value( "System/FlashRadiance", 0 ).toUInt( );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sConfig.sNewConfig.nFlashTime = settings.value( "System/NewFlashTime", 0 ).toUInt( );
    sConfig.sNewConfig.nFlashRadiance = settings.value( "System/NewFlashRadiance", 0 ).toUInt( );
    sConfig.sNewConfig.nFlashActivated = settings.value( "System/NewFlashActivated", 0 ).toUInt( );
    sConfig.sNewConfig.nFlashSwitch = settings.value( "System/NewFlashSwitch", 0 ).toUInt( );
    sConfig.sNewConfig.nFlashMode = settings.value( "System/NewFlashMode", 1 ).toUInt( );

    sConfig.sNewConfig.nFrequencyTime = settings.value( "System/NewFrequencyTime", 0 ).toUInt( );
    sConfig.sNewConfig.nFrequencyRadiance = settings.value( "System/NewFrequencyRadiance", 0 ).toUInt( );
    sConfig.sNewConfig.nFrequencyActivated = settings.value( "System/NewFrequencyActivated", 0 ).toUInt( );
    sConfig.sNewConfig.nFrequencySwitch = settings.value( "System/NewFrequencySwitch", 0 ).toUInt( );
    sConfig.sNewConfig.nFrequencyMode = settings.value( "System/NewFrequencyMode", 1 ).toUInt( );
    sConfig.sNewConfig.nFrameFreqMode = settings.value( "System/NewFrameFreqMode", 1 ).toUInt( );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    GetLocation( settings, sConfig.cLocation, false );
    GetLocation( settings, sConfig.sNewConfig.cLocation, true );
}

void QControllerCommon::GetLocation( QSettings &settings, wchar_t *pBuffer, const bool bNewDevice )
{
    QString strKey = QString( "System/Location%1" ).arg( bNewDevice ? "New" : "" );
    QString strDefault = QString( "%1设备未设置" ).arg( bNewDevice ? "新" : "老" );
    QString strLocation = settings.value( strKey, strDefault ).toString( );
    const wchar_t* pData = ( wchar_t* ) strLocation.utf16( );
    qint32 nLen = strLocation.length( );
    qint32 nRealLen = LedControll::nLOCATION_SIZE - 1;
    if ( nRealLen < nLen ) {
        strLocation.remove( nRealLen, nLen - nRealLen );
    }

    wcscpy( pBuffer, pData );
}

void QControllerCommon::GetSystemConfig( LedControll::SSysConfig &sConfig )
{
    QSettings &settings = GetConfigSettings( );
    GetSystemConfig( sConfig, settings );
}

void QControllerCommon::ControlSysMenu( QWidget &wg )
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

int QControllerCommon::MsgBox( QWidget* pParent, QString strTitle, QString strText, QMessageBox::Icon nType )
{
    int nRet = 0;
    QMessageBox msg( nType, strTitle, strText );
    msg.setAutoFillBackground( false );
    msg.setAttribute( Qt::WA_StyleSheet );
    msg.setAttribute( Qt::WA_SetStyle );
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
