#ifndef QPLATFORMGLOBAL_H
#define QPLATFORMGLOBAL_H

#include "PlatformGlobal_global.h"
#include <QObject>
#include "../ThreadLibrary/qthreadgenerator.h"
#include "../CommonWidgetLibrary/commonwidgetlibrary.h"

class PLATFORMGLOBALSHARED_EXPORT QPlatformGlobal : public QObject {
    Q_OBJECT
public:
    static QPlatformGlobal* GetSingleton( );
    void ParseMainArgs( const MyEnums::ApplicationType type, const int nArgc, char **ppArgv );

    void ControlTimer( const QManipulateIniFile::IniFileName iniFile, const bool bStart );

    QCommonFunction& GetCommonFunctionObj( );
    QCommonWidgetLibrary& GetWidgetLibraryObj( );
    QManipulateIniFile& GetManipulateFileObj( );
    QThreadGenerator& GetThreadGenerator( );

    //
    // Client
    //
    MyDataStructs::QMyStringList& GetTcpClientIpPortList( );
    MyDataStructs::QStringThread& GetTcpClientThreadHash( );

    MyDataStructs::QMyStringList& GetUdpClientIpPortList( );
    MyDataStructs::QStringThread& GetUdpClientThreadHash( );

    MyDataStructs::QMyStringList& GetUdpBroadcastClientPortList( );
    MyDataStructs::QStringThread& GetUdpBroadcastClientThreadHash( );

    MyDataStructs::QMyStringList& GetUdpMulticastClientIpPortList( );
    MyDataStructs::QStringThread& GetUdpMulticastClientThreadHash( );

    //
    // Server end
    //
    MyDataStructs::QMyStringList& GetTcpListenerPortMaxConnectionList( );
    MyDataStructs::QStringThread& GetTcpListenerThreadHash( );

    MyDataStructs::QMyStringList& GetUdpListenerPortList( );
    MyDataStructs::QStringThread& GetUdpListenerThreadHash( );

    MyDataStructs::QMyStringList& GetUdpBroadcastListenerPortList( );
    MyDataStructs::QStringThread& GetUdpBroadcastListenerThreadHash( );

    MyDataStructs::QMyStringList& GetUdpMulticastListenerIpPortList( );
    MyDataStructs::QStringThread& GetUdpMulticastListenerThreadHash( );

    void BrowseLog( const QManipulateIniFile::LogFileNames type );
    void StartupThreadExit( QThread* pReceiver, const MyEnums::ThreadType type );
    void StartupLogWrite( QThread* pReceiver, const MyDataStructs::QEventMultiHash& hash );
    void GenerateLogHash( MyDataStructs::QEventMultiHash& hash, const QStringList& lstText, const QManipulateIniFile::LogTypes type );

    void InitializeApplication( const MyEnums::ApplicationType type );

    void CreateTcpClientThread( const QManipulateIniFile::IniFileName iniFile, const bool bConnect2Host = false );
    void TcpClientSendData( QThread* pReceiver, const QByteArray* pByteData );
    void TcpClientSendData2AllThreads( const QByteArray& byteData );
    void TcpClientDisconnect( QThread* pReceiver );
    void TcpClientConnect( QThread* pReceiver, const QString& strIP, const QString& strPort );
    void TcpClientAllConnectOrDisconnect( bool bConnect );

    void CreateUdpClientThread( const QManipulateIniFile::IniFileName iniFile, const bool bMultiThread = false );
    void UdpClientSendData( QThread* pReceiver, const QByteArray* pByteData, const QString& strIpPort, const MyEnums::UdpDatagramType dgType );
    void UdpClientSendData2AllThreads( const QByteArray& byteData, const MyEnums::UdpDatagramType dgType );

    void CreateTcpListenerThread( const QManipulateIniFile::IniFileName iniFile, const bool bStartupListener = true );
    void TcpListenerStartup( QThread* pReceiver, const QString& strPort, const QString& strMaxConnection );
    void TcpListenerAllStartup(  );

    void CreateUdpListenerThread( const QManipulateIniFile::IniFileName iniFile, const bool bServer, const bool bStartupListener = true );
    void UdpListenerStartup( QThread* pReceiver, const QString& strPort );
    void UdpListenerAllStartup(  );

    void CreateUdpBroadcastListenerThread( const QManipulateIniFile::IniFileName iniFile, const bool bServer, const bool bStartupListener = true );
    void UdpBroadcastListenerStartup( QThread* pReceiver, const QString& strPort );
    void UdpBroadcastListenerAllStartup(  );

    void CreateUdpMulticastListenerThread( const QManipulateIniFile::IniFileName iniFile, const bool bServer, const bool bStartupListener = true );
    void UdpMulticastListenerStartup( QThread* pReceiver, const QString& strPort );
    void UdpMulticastListenerAllStartup(  );

    void UdpOperateMulticastGroup( const bool bJoin, const QString& strIpPort );
    void UdpOperateAllMulticastGroups( const bool bJoin );

protected:
    explicit QPlatformGlobal( );

private:
    void SetApplicationName( const QManipulateIniFile::LogFileNames type );
    void GetNetworkParams(  const QManipulateIniFile::IniFileName iniFile, const QManipulateIniFile::IniFileSectionItems item, QVariant& var );

    void InitializePlatformClient( );
    void InitializePlatformServer( );
    void InitializePlatformDataReceiver( );

    void ParseTcpArgs( const MyEnums::ApplicationType type, const QStringList& lstParams );
    void ParseUdpArgs( const MyEnums::ApplicationType type, const QStringList& lstParams );
    void ParseBroadcastArgs( const MyEnums::ApplicationType type, const QStringList& lstParams );
    void ParseMulticastArgs( const MyEnums::ApplicationType type, const QStringList& lstParams );
    void ParseDatabaseArgs( const MyEnums::ApplicationType type, const QStringList& lstParams );

    void ParsePlatformClientArgs( MyDataStructs::QMyStringList& lstTarget, const QStringList& lstParams );
    void ParsePlatformServerArgs( MyDataStructs::QMyStringList& lstTarget, const QStringList& lstParams );
    void ParsePlatformDataReceiverArgs( MyDataStructs::QMyStringList& lstTarget, const QStringList& lstParams );

    void Convert2StringList( const int nArgc, char **ppArgv, QStringList& lstParams );

    void ParseNetworkParams( QVariant& varParam1, QVariant& varParam2, MyDataStructs::QMyStringList& lstParams );
    void ParseNetworkParams( QVariant& varParam1, MyDataStructs::QMyStringList& lstParams );

    void CreateUdpClientThread( const QManipulateIniFile::IniFileName iniFile,
                                MyDataStructs::QMyStringList& listParams,
                                MyDataStructs::QStringThread& hashThread,
                                const MyEnums::UdpDatagramType dgType,
                                QUdpSenderThread* pThread );

    inline void ConnectUdpClientSignalSlot( QThread* pReceiver );

    void GetUdpListHashParam( const MyEnums::UdpDatagramType dgType,
                              MyDataStructs::QMyStringList*& pListParam,
                              MyDataStructs::QStringThread*& pHashThread );

    void CreateUdpListenerThread( MyDataStructs::QMyStringList& listParams,
                                  MyDataStructs::QStringThread& hashThread,
                                  const QManipulateIniFile::IniFileName iniFile,
                                  const QManipulateIniFile::IniFileSectionItems item,
                                  const bool bServer, const bool bStartupListener,
                                  const MyEnums::UdpDatagramType dgType );
    void UdpListenerAllStartup( MyDataStructs::QMyStringList& listParams,
                                MyDataStructs::QStringThread& hashThread );

private:
    static QPlatformGlobal* pPlatformGlobal;
    QCommonFunction commonFunction;
    QCommonWidgetLibrary widgetLibrary;
    QManipulateIniFile manipulateFile;
    QThreadGenerator* pGenerator;

    QString strColonSeperator;
    QString strAtSeperator;

    //
    // Client
    //
    MyDataStructs::QStringThread hashTcpClientThread;
    MyDataStructs::QMyStringList listTcpClientIpPort;

    MyDataStructs::QStringThread hashUdpClientThread;
    MyDataStructs::QMyStringList listUdpClientIpPort;

    MyDataStructs::QStringThread hashUdpBroadcastClientThread;
    MyDataStructs::QMyStringList listUdpBroadcastClientPort;

    MyDataStructs::QStringThread hashUdpMulticastClientThread;
    MyDataStructs::QMyStringList listUdpMulticastClientIpPort;


    //
    // Server end
    //
    MyDataStructs::QStringThread hashTcpListenerThread;
    MyDataStructs::QMyStringList listTcpListenerPortMaxConnection;

    MyDataStructs::QStringThread hashUdpListenerThread;
    MyDataStructs::QMyStringList listUdpListenerPort;

    MyDataStructs::QStringThread hashUdpBroadcastListenerThread;
    MyDataStructs::QMyStringList listUdpBroadcastListenerPort;

    MyDataStructs::QStringThread hashUdpMulticastListenerThread;
    MyDataStructs::QMyStringList listUdpMulticastListenerIpPort;

signals:
    // Z socket of Y thread of X Server
    void ParseTcpData( QString strServer, QThread* pSenderThread, QTcpSocket* pPeerSocket, void* pByteArray );
    void ParseUdpData( QString strSenderIP, quint16 nSenderPort, QThread* pSenderThread, void* pByteArray, MyEnums::UdpDatagramType dgType );

public slots:

private slots:
    void HandleGetWholeTcpStreamDataFromServer( QTcpSocket* pPeerSocket,void* pByteArray );
    void HandleGetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort, MyEnums::UdpDatagramType dgType );
};

#endif // QPLATFORMGLOBAL_H
