#include "cnetconfigurator.h"
#include <QDateTime>

#define CONFIG_NAME_NETWORK     "Config.ini"

CNetConfigurator::CNetConfigurator(QObject *parent) :
    QObject(parent)
{
    pSettings = new QSettings( CONFIG_NAME_NETWORK, QSettings::IniFormat );
}

CNetConfigurator::~CNetConfigurator( )
{
    delete pSettings;
}

CNetConfigurator* CNetConfigurator::GetConfigurator( )
{
    static CNetConfigurator* pConfig = NULL;

    if ( NULL == pConfig ) {
        pConfig = new CNetConfigurator( );
    }

    return pConfig;
}

qint32 CNetConfigurator::GetThreadSocketCount( )
{
    QString strKey = "Network/ThreadSocketCount";

    return pSettings->value( strKey, 10 ).toInt( );
}

qint32 CNetConfigurator::GetPaserPeerCount( )
{
    QString strKey = "Network/PaserPeerCount";

    return pSettings->value( strKey, 2 ).toInt( );
}

qint32 CNetConfigurator::GetPeerThreadSleep( )
{
    QString strKey = "Network/PeerThreadSleep";

    return pSettings->value( strKey, 10 ).toInt( );
}

qint32 CNetConfigurator::GetDataDispatcherParserCount( )
{
    QString strKey = "Network/DataDispatcherParserCount";

    return pSettings->value( strKey, 2 ).toInt( );
}

QString CNetConfigurator::GetMulticastIP( )
{
    QString strKey = "Network/MulticastIP";

    return pSettings->value( strKey, "239.255.43.21" ).toString( );
}

quint16 CNetConfigurator::GetMulticastPort( )
{
    QString strKey = "Network/MulticastPort";

    return pSettings->value( strKey, 60000 ).toInt( );
}

bool CNetConfigurator::GetDisplayDynamicLog( )
{
    pSettings->sync( );

    return pSettings->value( "Network/DisplayDynamicLog", false ).toBool( );
}

qint32 CNetConfigurator::GetTimeSyncInterval( )
{
    return pSettings->value( "Common/TimeSyncInterval", 60 * 60 ).toInt( );
}

QString CNetConfigurator::GetDateTime( )
{
    return QDateTime::currentDateTime( ).toString( "yyyy-MM-dd hh:mm:ss" );
}

QTextCodec* CNetConfigurator::GetTextCodec( )
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
