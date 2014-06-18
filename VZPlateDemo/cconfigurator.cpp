#include "cconfigurator.h"

CConfigurator* CConfigurator::pConfigurator = NULL;

CConfigurator::CConfigurator(QObject *parent) :
    QObject(parent)
{
    pCodec = QCommon::GetTextCodec( );
    QString strConfig = qApp->applicationDirPath( ) + "/" + "config.ini";
    pSettings = new QSettings( strConfig, QSettings::IniFormat );
    pSettings->setIniCodec( pCodec );
}

CConfigurator* CConfigurator::CreateInstance( )
{
    if ( NULL == pConfigurator ) {
        pConfigurator = new CConfigurator( );
    }

    return pConfigurator;
}

void CConfigurator::ReadAppMainWindow( QString& strType )
{   // Blacklist Demo
    strType = pSettings->value( "AppMainWindow/Type", "Demo" ).toString( );
}

void CConfigurator::WriteAppMainWindow( QString& strType )
{   // Blacklist Demo
    pSettings->setValue( "AppMainWindow/Type", strType );
}

void CConfigurator::ReadVideoType( QString& strType )
{   // HkAnalog TmAnalog HkIPC JwsIPC OnvifIPC
    strType = pSettings->value( "VideoSource/Type", "OnvifIPC" ).toString( );
}

void CConfigurator::WriteVideoType( QString& strType )
{   // HkAnalog TmAnalog HkIPC JwsIPC OvnifIPC
    pSettings->setValue( "VideoSource/Type", strType );
}

void CConfigurator::ReadIpcIP( QString& strIP )
{
    strIP = pSettings->value( "IPC/IP", "127.0.0.1" ).toString( );
}

void CConfigurator::WriteIpcIP( QString& strIP )
{
    pSettings->setValue( "IPC/IP", strIP );
}

int CConfigurator::ReadPlateWay( )
{
    return pSettings->value( "Plate/Way", 1 ).toInt( );
}

void CConfigurator::WritePlateWay( int nWay )
{
     pSettings->setValue( "Plate/Way", nWay );
}

bool CConfigurator::ReadMainStream( )
{
    return pSettings->value( "IPC/MainStream", true ).toBool( );
}

void CConfigurator::WriteMainStream( bool bStream )
{
    pSettings->setValue( "IPC/MainStream", bStream );
}

bool CConfigurator::ReadRealStream( )
{
    return pSettings->value( "IPC/RealStream", false ).toBool( );
}

void CConfigurator::WriteRealStream( bool bReal )
{
    pSettings->setValue( "IPC/RealStream", bReal );
}

bool CConfigurator::ReadVideoCapture( )
{
    return pSettings->value( "Plate/Capture", false ).toBool( );
}

bool CConfigurator::ReadPlateMultiThread( )
{
    return pSettings->value( "Plate/MultiThread", false ).toBool( );
}

void CConfigurator::WritePlateMultiThread( bool bMulti )
{
    pSettings->setValue( "Plate/MultiThread", bMulti );
}

void CConfigurator::WriteVideoCapture( bool bCapture )
{
    pSettings->setValue( "Plate/Capture", bCapture );
}

void CConfigurator::ReadBlacklistPlate( QStringList& lstPlates )
{
    int nCount = pSettings->value( "Blacklist/PlateCount", 0 ).toInt( );
    QString strPlate = "";

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        strPlate = pSettings->value( QString( "Blacklist/Plate%1" ).arg( nIndex ), "" ).toString( );
        if ( strPlate.isEmpty( ) ) {
            continue;
        }

        lstPlates << strPlate;
    }
}

void CConfigurator::WriteBlacklistPlate( QStringList& lstPlates )
{
    int nCount = lstPlates.count( );
    if ( 0 == nCount ) {
        return;
    }

    QString strKey = "Blacklist/PlateCount";
    int nRawCount = pSettings->value( strKey, 0 ).toInt( );
    pSettings->setValue( strKey, nCount );
    nCount = 0;

    strKey = "Blacklist/Plate%1";
    foreach ( const QString& strPlate, lstPlates ) {
       pSettings->setValue( strKey.arg( nCount++ ), strPlate );
    }

    for ( int nIndex = nCount; nIndex < nRawCount; nIndex++ ) {
        pSettings->remove( strKey.arg( nIndex ) );
    }

    pSettings->sync( );
}

void CConfigurator::ReadPlateProvider( QString &strProvider )
{
    strProvider = pSettings->value( "Plate/Provider", "VZ" ).toString( );
}

bool CConfigurator::ReadPlateDongleWay( )
{
    return pSettings->value( "Plate/DongleOneWay", false ).toBool( );
}
