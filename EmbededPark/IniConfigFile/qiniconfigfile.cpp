#include "qiniconfigfile.h"

QSettings* QIniConfigFile::pSettings = NULL;

QIniConfigFile::QIniConfigFile( QObject* parent ) : QObject( parent )
{
}

void QIniConfigFile::CreateSettings( )
{
    if ( NULL == pSettings ) {
        pSettings = new QSettings( QCommonLibrary::GetConfigFileName( ),
                                   QSettings::IniFormat );
    }
}

quint16 QIniConfigFile::GetServerListenPort( )
{
    quint16 nPort = 6000;

    CreateSettings( );
    nPort = pSettings->value( "Server/sbListenPort", nPort ).toUInt( );

    return nPort;
}

qint32 QIniConfigFile::GetMaxPendingConnections( )
{
    qint32 nMaxConn = 100;

    CreateSettings( );
    nMaxConn = pSettings->value( "Server/sbMaxPendingConnections", nMaxConn ).toInt( );

    return nMaxConn;
}

qint32 QIniConfigFile::GetSocketCountEachServerThread( )
{
    qint32 nSocketCount = 3;

    CreateSettings( );
    nSocketCount = pSettings->value( "Server/sbSocketCountEachServerThread", nSocketCount ).toInt( );

    return nSocketCount;
}

qint32 QIniConfigFile::GetServerThreadCountEachDataParser( )
{
    qint32 nParserCount = 2;

    CreateSettings( );
    nParserCount = pSettings->value( "Server/sbServerThreadCountEachDataParser", nParserCount ).toInt( );

    return nParserCount;
}

qint32 QIniConfigFile::GetSocketThreadServerSleepTime( )
{
    qint32 nTime = 10; // Minute

    CreateSettings( );
    nTime = pSettings->value( "Server/sbMaxSleepTimeEachServerThread", nTime ).toInt( );

    return nTime;
}

qint32 QIniConfigFile::GetDbThreadPoolThreadCount( )
{
    qint32 nThreadCount = 10;

    return nThreadCount;
}

qint32 QIniConfigFile::GetDbMaxDbConnections( )
{
    qint32 nConnCount = 10;

    return nConnCount;
}

QString QIniConfigFile::GetClientServerIP( )
{
    QString strIP = "127.0.0.1";

    CreateSettings( );
    strIP = pSettings->value( "ClientControl/edtClientServerIP", strIP ).toString( );

    return strIP;
}

quint16 QIniConfigFile::GetClientServerPort( )
{
    quint16 nPort = 6000;

    CreateSettings( );
    nPort = pSettings->value( "ClientControl/sbClientServerPort", nPort ).toUInt( );

    return nPort;
}

QString QIniConfigFile::GetAdminServerIP( )
{
    QString strIP = "127.0.0.1";

    CreateSettings( );
    strIP = pSettings->value( "Administrator/edtAdminServerIP", strIP ).toString( );

    return strIP;
}

quint16 QIniConfigFile::GetAdminServerPort( )
{
    qint32 nPort = 6000;

    CreateSettings( );
    nPort = pSettings->value( "Administrator/sbAdminServerPort", nPort ).toUInt( );

    return nPort;
}

qint32 QIniConfigFile::GetTaskCount4DbConnection( )
{
    qint32 nTaskCount = 10;

    return nTaskCount;
}

quint8 QIniConfigFile::GetLogCount( )
{
    quint8 nCount = 100;

    return nCount;
}
