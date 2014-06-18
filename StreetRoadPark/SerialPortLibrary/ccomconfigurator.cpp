#include "ccomconfigurator.h"

#define CONFIG_NAME_SERIALPORT     "Config.ini"

CComConfigurator::CComConfigurator(QObject *parent) :
    QObject(parent)
{
    pSettings = new QSettings( CONFIG_NAME_SERIALPORT, QSettings::IniFormat );
}

CComConfigurator::~CComConfigurator( )
{
    if ( NULL != pSettings ) {
        delete pSettings;
        pSettings = NULL;
    }
}

CComConfigurator* CComConfigurator::GetConfigurator( )
{
    static CComConfigurator* pConfig = NULL;

    if ( NULL == pConfig ) {
        pConfig = new CComConfigurator( );
    }

    return pConfig;
}

bool CComConfigurator::GetDisplayDynamicLog( )
{
    pSettings->sync( );

    return pSettings->value( "ComM77R/DisplayDynamicLog", false ).toBool( );
}

QByteArray CComConfigurator::GetReceiverVerInfo( )
{
    return pSettings->value( "ComM77R/ReceiverVer", "M77R_ver1p5b" ).toByteArray( );
}

QString CComConfigurator::GetComParkID( QString &strComX )
{
    return pSettings->value( QString( "Park/%1ParkID" ).arg( strComX ), "5101070001" ).toString( );
}

QTextCodec* CComConfigurator::GetTextCodec( )
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
