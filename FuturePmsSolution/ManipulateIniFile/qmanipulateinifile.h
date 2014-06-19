#ifndef QMANIPULATEINIFILE_H
#define QMANIPULATEINIFILE_H

#include "ManipulateIniFile_global.h"
#include <QSettings>
#include <QFile>
#include "../CommonLibrary/qcommonfunction.h"
#include <QDir>

class MANIPULATEINIFILESHARED_EXPORT QManipulateIniFile : public QObject
{
    Q_OBJECT

public:
    explicit QManipulateIniFile( QObject* parent = 0 );
    virtual ~QManipulateIniFile( );

public:

    enum IniFileName {
        PlatformCentralClient,
        PlatformCentralServer,
        PlatformCentralDataReceiver,
        PlatformCount
    }; // Index 0

    Q_DECLARE_FLAGS( IniFileNames, IniFileName )
    Q_FLAGS( IniFileName )

    enum LogFileName {
        PlatformCentralLogClient,
        PlatformCentralLogServer,
        PlatformCentralLogDataReceiver,
        PlatformLogCount
    }; // Index 1

    Q_DECLARE_FLAGS( LogFileNames, LogFileName )
    Q_FLAGS( LogFileName )

    enum IniFileSection {
        IniDatabase,
        IniNetwork,
        IniThread
    }; // Index 2

    Q_DECLARE_FLAGS( IniFileSections, IniFileSection )
    Q_FLAGS( IniFileSection )

    enum IniFileSectionItem {
        /////////////////////////////////////// Database
        DatabaseType,
        DatabaseHost,
        DatabasePort,
        DatabaseUser,
        DatabasePwd,
        DatabaseSchema,
        DatabaseThreadpoolMaxThreads,
        DatabaseThreadpoolThreadExpire,
        DatabaseObjectLifeTime,
        DatabaseObjectReleaseInterval,
        ////////////////////////////////////////// Network
        NetworkTcpMaxConnection,
        NetworkTcpServerPort,
        NetworkTcpServerIP,
        NetworkUdpServerPort,
        NetworkUdpServerIP,
        NetworkUdpBroadcastPort,
        NetworkMulticastPort,
        NetworkMulticastIP,
        ///////////////////////////////////////// Thread
        ThreadPeerSocketCount, // Per peer thread manages X PeerSockets.
        ThreadPeerStackSize, // 512K
        ThreadPeerReleaseInterval,
        ThreadPool
    }; // Index 3

    Q_DECLARE_FLAGS( IniFileSectionItems, IniFileSectionItem )
    Q_FLAGS( IniFileSectionItem )

    enum LogType {
        LogDatabase,
        LogNetwork,
        LogThread,
        LogCfgParam,
        LogOther,
        LogItems
    }; // Index 4

    Q_DECLARE_FLAGS( LogTypes, LogType )
    Q_FLAGS( LogType )

public:
    void IniFileValue( const IniFileNames file, const IniFileSections section, const IniFileSectionItems item, const bool bWrite, QVariant& varValue );
    void WriteLogFile( const LogFileNames file, const LogTypes types, const QVariant& var );
    void ReadLogFile( const LogFileNames file, const QString& strDate, const LogTypes types, QStringList& lstLogs );
    void CfgFileName( const IniFileNames enumType, QString& strName );
    void CfgFileSectionName( const IniFileSections enumType, QString& strName );
    void CfgFileSectionItemName( const IniFileSectionItems enumType, QString& strName );
    void LogTypeName( const LogTypes enumType, QString& strName );
    void LogFileDirName( const LogFileNames enumType, QString& strName );

    IniFileNames GetIniFileNameType( );
    LogFileNames GetLogFileNameType( );

private:
    void GetSettings( QSettings*& pSettings, const QString& strFile );
    void GetCfgFullName( QString& strFullName, const IniFileNames enumType );
    void GetLogFullName( QString& strFullName, const LogFileNames enumType );
    void OperateSettingsInis( bool bInitialize );
    void OperateSettingsLogs( bool bInitialize );

private:
    QFile objFile;
    QCommonFunction commonFunction;
    QTextCodec* pTextCodec;
    QSettings* pSettingsLogs[ PlatformLogCount ];
    QSettings* pSettingsInis[ PlatformCount ];

signals:

public slots:

};

#endif // QMANIPULATEINIFILE_H
