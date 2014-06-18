#include "cmainconfigurator.h"
#include <windows.h>

#define CONFIG_NAME_SERVER     "Config.ini"

CMainConfigurator::CMainConfigurator(QObject *parent) :
    QObject(parent)
{
    pSettings = new QSettings( CONFIG_NAME_SERVER, QSettings::IniFormat );
}

CMainConfigurator::~CMainConfigurator( )
{
    if ( NULL != pSettings ) {
        delete pSettings;
        pSettings = NULL;
    }
}

CMainConfigurator* CMainConfigurator::GetConfigurator( )
{
    static CMainConfigurator* pConfig = NULL;

    if ( NULL == pConfig ) {
        pConfig = new CMainConfigurator( );
    }

    return pConfig;
}

void CMainConfigurator::ReadIPPort( QLineEdit& edtIP, QSpinBox& sbPort )
{
    QString strKey = "Database/ServerIP";
    edtIP.setText( pSettings->value( strKey, "127.0.0.1" ).toString( ) );

    strKey = "Database/Port";
    sbPort.setValue( pSettings->value( strKey, 3306 ).toUInt( ) );
}

void CMainConfigurator::WriteIPPort( QString& strIP, quint16 nPort )
{
    QString strKey = "Database/ServerIP";
    pSettings->setValue( strKey, strIP );

    strKey = "Database/Port";
    pSettings->setValue( strKey, nPort );
}

void CMainConfigurator::ReadPortMaxConn( QSpinBox& sbPort, QSpinBox& sbMaxConn )
{
    QString strKey = "Network/ListenPort";
    sbPort.setValue( pSettings->value( strKey, 6000 ).toUInt( ) );

    strKey = "Network/MaxPendingConn";
    sbMaxConn.setValue( pSettings->value( strKey, 100 ).toUInt( ) );
}

void CMainConfigurator::WritePortMaxConn( quint16 nPort, qint32 nMaxConn )
{
    QString strKey = "Network/ListenPort";
    pSettings->setValue( strKey, nPort );

    strKey = "Network/MaxPendingConn";
    pSettings->setValue( strKey, nMaxConn );
}

void CMainConfigurator::WriteComM77R( qint32 nIndex, qint32 nReceiverID )
{
    QString strKey = "ComM77R/ComM77R%1";
    QString strValue = "COM%1@%2";

    QString strReceiverID;
    strReceiverID.sprintf( "%03d", nReceiverID );

    pSettings->setValue( strKey.arg( nIndex ), strValue.arg( QString::number( nIndex ),
                                                             strReceiverID ) );
}

void CMainConfigurator::GetPorts( QStringList &lstPorts )
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

void CMainConfigurator::ReadComM77R( QComboBox &comboBox, QStringList& lstCom )
{
    comboBox.clear( );

    QString strValue;
    QStringList lstValue;
    QString strSperator = "@";
    QString strKey = "ComM77R/ComM77R%1";
    qint32 nCount = pSettings->value( strKey.arg( "Count" ), 0 ).toInt( );

    QStringList lstPorts;
    GetPorts( lstPorts );
    int nItem = 0;

    for ( qint32 nIndex = 1; nIndex <= nCount; nIndex++ ) {
        strValue = pSettings->value( strKey.arg( nIndex ), "" ).toString( );
        lstValue = strValue.split( strSperator );

        if ( 2 != lstValue.length( ) ) {
            continue;
        }

        strValue = lstValue.at( 0 ).toUpper( );
        lstCom << strValue;
        comboBox.addItem( strValue, lstValue.at( 1 ) );

        comboBox.setItemIcon( nItem++,
                              QIcon( lstPorts.contains( strValue ) ?
                                         ":/Images/Enable.png" : ":/Images/Disable.png" ) );
    }
}

QTextCodec* CMainConfigurator::GetTextCodec( )
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

    pCodec = QTextCodec::codecForName( strText.toLatin1( ) );
    return pCodec;
}
