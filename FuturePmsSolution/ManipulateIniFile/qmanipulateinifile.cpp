#include "qmanipulateinifile.h"
#include <QMetaEnum>
#include <QApplication>

QManipulateIniFile::QManipulateIniFile( QObject* parent ) : QObject( parent )
{
    pTextCodec = commonFunction.GetTextCodec( );
    OperateSettingsInis( true );
    OperateSettingsLogs( true );
}

QManipulateIniFile::~QManipulateIniFile( )
{
    OperateSettingsInis( false );
    OperateSettingsLogs( false );
}

void QManipulateIniFile::OperateSettingsInis( bool bInitialize )
{
    for ( int nIndex = 0; nIndex < PlatformCount; nIndex++ ) {
        if ( bInitialize ) {
            pSettingsInis[ nIndex ]= NULL;
        } else {
            if ( NULL != pSettingsInis[ nIndex ] ) {
                delete pSettingsInis[ nIndex ];
                pSettingsInis[ nIndex ] = NULL;
            }
        }
    }
}

void QManipulateIniFile::OperateSettingsLogs( bool bInitialize )
{
    for ( int nIndex = 0; nIndex < PlatformLogCount; nIndex++ ) {
        if ( bInitialize ) {
            pSettingsLogs[ nIndex ]= NULL;
        } else {
            if ( NULL != pSettingsLogs[ nIndex ] ) {
                delete pSettingsLogs[ nIndex ];
                pSettingsLogs[ nIndex ] = NULL;
            }
        }
    }
}

void QManipulateIniFile::GetCfgFullName( QString &strFullName, const IniFileNames enumType )
{
    commonFunction.GetPath( strFullName, QCommonFunction::PathConfigs );

    QString strName;
    CfgFileName( enumType, strName );
    strFullName += strName + ".ini";
}

void QManipulateIniFile::GetSettings( QSettings*& pSettings, const QString &strFile )
{
    if ( NULL == pSettings ) {
        pSettings = new QSettings( strFile, QSettings::IniFormat );
        goto CODEC;
    }

    if ( strFile.toUpper( ) == pSettings->fileName( ).toUpper( ) ) {
        goto CODEC;
    }

    delete pSettings;

    pSettings = new QSettings( strFile, QSettings::IniFormat );

    CODEC:
    if ( NULL == pSettings->iniCodec( ) ) {
        pSettings->setIniCodec( pTextCodec );
    }
}

void QManipulateIniFile::IniFileValue( const IniFileNames file, const IniFileSections section, const IniFileSectionItems item, const bool bWrite, QVariant &varValue )
{
    QString strFullName;
    GetCfgFullName( strFullName, file );
    GetSettings( pSettingsInis[ file ], strFullName );

    QSettings* pSettingsIni = pSettingsInis[ file ];

    QString strSection;
    CfgFileSectionName( section, strSection );

    QString strItem;
    CfgFileSectionItemName( item, strItem );

    QString strKey = strSection + "/" + strItem;

    if ( bWrite ) {
        pSettingsIni->setValue( strKey, varValue );
    } else {
        varValue = pSettingsIni->value( strKey );
    }
}

void QManipulateIniFile::WriteLogFile( const LogFileNames file, const LogTypes types, const QVariant &var )
{
    QString strFullName;
    GetLogFullName( strFullName, file );

    QDate date = QDate::currentDate( );
    QString strDate = commonFunction.GetDateString( date );
    strFullName += strDate;

    GetSettings( pSettingsLogs[ file ], strFullName );
    QSettings* pSettingsLog = pSettingsLogs[ file ];

    QString strName;
    LogTypeName( types, strName );

    QString strCount = "Count";
    QString strKey = QString( "%1/" ).arg( strName ) + "%1";
    int nCount = pSettingsLog->value( strKey.arg( strCount ), 0 ).toInt( ) + 1;

    pSettingsLog->setValue( strKey.arg( strCount ), nCount );
    pSettingsLog->setValue( strKey.arg( nCount ), var );
}

void QManipulateIniFile::ReadLogFile( const LogFileNames file, const QString& strDate, const LogTypes types, QStringList& lstLogs )
{
    QString strFullName;
    GetLogFullName( strFullName, file );
    strFullName += strDate;

    GetSettings( pSettingsLogs[ file ], strFullName );
    QSettings* pSettingsLog = pSettingsLogs[ file ];

    QString strName;
    LogTypeName( types, strName );

    QString strCount = "Count";
    QString strKey = QString( "%1/" ).arg( strName ) + "%1";
    int nCount = pSettingsLog->value( strKey.arg( strCount ), 0 ).toInt( );

    QString strText = "";

    for ( int nIndex = 1; nIndex <= nCount; nIndex++ ) {
        strText = pSettingsLog->value( strKey.arg( nIndex ), "" ).toString( );

        if ( !strText.isEmpty( ) ) {
            lstLogs << strText;
        }
    }
}

void QManipulateIniFile::GetLogFullName( QString &strFullName, const LogFileNames enumType )
{
    commonFunction.GetPath( strFullName, QCommonFunction::PathLogs );

    QString strName;
    QString strSeperator = "/";
    LogFileDirName( enumType, strName );
    strFullName += strName + strSeperator;
}

QManipulateIniFile::IniFileNames QManipulateIniFile::GetIniFileNameType(  )
{
    LogFileNames logType = GetLogFileNameType(  );
    IniFileNames type;

    switch ( logType ) {
    case PlatformCentralLogClient :
        type = PlatformCentralClient;
        break;

    case PlatformCentralLogServer :
        type = PlatformCentralServer;
        break;

    case PlatformCentralLogDataReceiver :
        type = PlatformCentralDataReceiver;
        break;

    case PlatformLogCount :
        type = PlatformCount;
        break;
    }

    return type;

}

QManipulateIniFile::LogFileNames QManipulateIniFile::GetLogFileNameType( )
{
    LogFileNames type;
    QString strName;

    QString strAppName = qApp->applicationName( );

    for ( qint32 nIndex = 0; nIndex < PlatformLogCount; nIndex++ ) {
        LogFileNames tmp = ( LogFileNames ) nIndex;
        LogFileDirName( tmp, strName );

        if ( strName == strAppName ) {
            type = tmp;
            break;
        }
    }

    return type;
}

void QManipulateIniFile::CfgFileName( const IniFileNames enumType, QString &strName )
{
    QMetaEnum metaEnum = metaObject( )->enumerator( 0 );
    strName = metaEnum.key( enumType );
}

void QManipulateIniFile::LogFileDirName( const LogFileNames enumType, QString &strName )
{
    QMetaEnum metaEnum = metaObject( )->enumerator( 1 );
    strName = metaEnum.key( enumType );
}

void QManipulateIniFile::CfgFileSectionName( const IniFileSections enumType, QString& strName )
{
    QMetaEnum metaEnum = metaObject( )->enumerator( 2 );
    strName = metaEnum.key( enumType );
}

void QManipulateIniFile::CfgFileSectionItemName( const IniFileSectionItems enumType, QString& strName )
{
    QMetaEnum metaEnum = metaObject( )->enumerator( 3 );
    strName = metaEnum.key( enumType );
}

void QManipulateIniFile::LogTypeName( const LogTypes enumType, QString& strName )
{
    QMetaEnum metaEnum = metaObject( )->enumerator( 4 );
    strName = metaEnum.key( enumType );
}
