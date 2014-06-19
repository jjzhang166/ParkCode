#include "qplatformglobal.h"

QPlatformGlobal* QPlatformGlobal::pPlatformGlobal = NULL;

QPlatformGlobal::QPlatformGlobal( )
{
    strColonSeperator = ":";
    strAtSeperator = "@";

    pGenerator = QThreadGenerator::GetSingleton( );
}

QPlatformGlobal* QPlatformGlobal::GetSingleton( )
{
    if ( NULL == pPlatformGlobal ) {
        pPlatformGlobal = new QPlatformGlobal( );
    }

    return pPlatformGlobal;
}

QCommonFunction& QPlatformGlobal::GetCommonFunctionObj( )
{
    return commonFunction;
}

QCommonWidgetLibrary& QPlatformGlobal::GetWidgetLibraryObj( )
{
    return widgetLibrary;
}

QManipulateIniFile& QPlatformGlobal::GetManipulateFileObj( )
{
    return manipulateFile;
}

QThreadGenerator& QPlatformGlobal::GetThreadGenerator( )
{
    return *pGenerator;
}

void QPlatformGlobal::Convert2StringList( const int nArgc, char **ppArgv, QStringList &lstParams )
{
    for ( int nIndex = 1; nIndex < nArgc; nIndex++ ) {
        lstParams << ppArgv[ nIndex ];
    }
}

void QPlatformGlobal::ParseMainArgs( const MyEnums::ApplicationType type, const int nArgc, char **ppArgv )
{
    //
    // nIndex = 0 Application Execute Path
    //

    if ( 1 >= nArgc ) {
        return;
    }

    QStringList lstParams;
    Convert2StringList( nArgc, ppArgv, lstParams );

    QStringList lstParam;

    foreach ( const QString& strParam, lstParams ) {
        lstParam = strParam.split( strColonSeperator );

        if ( 2 > lstParam.count( ) ) {
            continue;
        }

        const QString& strCmd = lstParam.at( 0 );
        if ( strCmd.isEmpty( ) || 1 != strCmd.length( ) ) {
            continue;
        }

        QChar qcCmd = strCmd.at( 0 ).toUpper( );
        char cCmd = qcCmd.toAscii( );

        switch ( cCmd ) {
        case 'T' : // TCP
            ParseTcpArgs( type, lstParam );
            break;

        case 'U' : // UDP
            ParseUdpArgs( type, lstParam );
            break;

        case 'B' : // Broadcast
            ParseBroadcastArgs( type, lstParam );
            break;

        case 'M' : // Multicast
            ParseMulticastArgs( type, lstParam );
            break;

        case 'D' : // Database
            ParseDatabaseArgs( type, lstParam );
            break;
        }
    }
}

void QPlatformGlobal::ParseTcpArgs( const MyEnums::ApplicationType type, const QStringList& lstParams )
{
    switch ( type ) {
    case MyEnums::PlatformCentralClient :
        ParsePlatformClientArgs( listTcpClientIpPort, lstParams );
        break;

    case MyEnums::PlatformCentralServer :
        ParsePlatformServerArgs( listTcpListenerPortMaxConnection, lstParams );
        break;

    case MyEnums::PlatformCentralDataReceiver :
        ParsePlatformDataReceiverArgs( listTcpListenerPortMaxConnection, lstParams );
        break;
    }
}

void QPlatformGlobal::ParseUdpArgs( const MyEnums::ApplicationType type, const QStringList& lstParams )
{
    switch ( type ) {
    case MyEnums::PlatformCentralClient :
        ParsePlatformClientArgs( listUdpClientIpPort, lstParams );
        break;

    case MyEnums::PlatformCentralServer :
        ParsePlatformServerArgs( listUdpListenerPort, lstParams );
        break;

    case MyEnums::PlatformCentralDataReceiver :
        ParsePlatformDataReceiverArgs( listUdpListenerPort, lstParams );
        break;
    }
}

void QPlatformGlobal::ParseBroadcastArgs( const MyEnums::ApplicationType type, const QStringList& lstParams )
{
    switch ( type ) {
    case MyEnums::PlatformCentralClient :
        ParsePlatformClientArgs( listUdpBroadcastClientPort, lstParams );
        break;

    case MyEnums::PlatformCentralServer :
        ParsePlatformServerArgs( listUdpBroadcastListenerPort, lstParams );
        break;

    case MyEnums::PlatformCentralDataReceiver :
        ParsePlatformDataReceiverArgs( listUdpBroadcastListenerPort, lstParams );
        break;
    }
}

void QPlatformGlobal::ParseMulticastArgs( const MyEnums::ApplicationType type, const QStringList& lstParams )
{
    switch ( type ) {
    case MyEnums::PlatformCentralClient :
        ParsePlatformClientArgs( listUdpMulticastClientIpPort, lstParams );
        break;

    case MyEnums::PlatformCentralServer :
        ParsePlatformServerArgs( listUdpMulticastListenerIpPort, lstParams );
        break;

    case MyEnums::PlatformCentralDataReceiver :
        ParsePlatformDataReceiverArgs( listUdpMulticastListenerIpPort, lstParams );
        break;
    }
}

void QPlatformGlobal::ParseDatabaseArgs( const MyEnums::ApplicationType type, const QStringList &lstParams )
{

}

void QPlatformGlobal::ParsePlatformClientArgs( MyDataStructs::QMyStringList& lstTarget, const QStringList& lstParams )
{
    //
    // NetworkTcpServerIP=192.168.1.24@192.168.1.24@192.168.1.24@192.168.1.24
    // NetworkTcpServerPort=50000@50001@50000@50001
    // Exe 192.168.1.24@192.168.1.24@192.168.1.24@192.168.1.24 50000@50001@50000@50001
    // TCP                         UDP                         Broadcast     Mutlicast
    // t:IP@IP:Port@Port u:IP@IP:Port@Port b:Port@Port m:IP@IP:Port@Port

    lstTarget.clear( );

    QVariant varIPs;
    QVariant varPorts;

    int nCounter = lstParams.count( );

    if ( 3 == nCounter ) {
        varIPs = lstParams.at( 1 );
        varPorts = lstParams.at( 2 );
        ParseNetworkParams( varIPs, varPorts, lstTarget );
    } else if ( 2 == nCounter ) {
        varPorts = lstParams.at( 1 );
        ParseNetworkParams( varPorts, lstTarget );
    }
}

void QPlatformGlobal::ParsePlatformServerArgs( MyDataStructs::QMyStringList& lstTarget, const QStringList& lstParams )
{
    //
    // NetworkTcpServerPort=50000@50001
    // NetworkTcpMaxConnection=100@50
    // Exe 50000@50001 100@50
    // TCP                                    UDP              Broadcast    Mutlicast
    // t:Port@Port:Conn@Conn u:Port@Port b:Port@Port m:IP@IP:Port@Port

    lstTarget.clear( );

    QVariant varPorts;
    QVariant varMaxConenctions;

    int nCounter = lstParams.count( );

    if ( 3 == nCounter ) {
        varPorts = lstParams.at( 1 );
        varMaxConenctions = lstParams.at( 2 );
        ParseNetworkParams( varPorts, varMaxConenctions, lstTarget );
    } else if ( 2 == nCounter ) {
        varPorts = lstParams.at( 1 );
        ParseNetworkParams( varPorts, lstTarget );
    }
}

void QPlatformGlobal::ParsePlatformDataReceiverArgs( MyDataStructs::QMyStringList& lstTarget, const QStringList& lstParams )
{
    //
    // NetworkTcpServerPort=50000@50001
    // NetworkTcpMaxConnection=100@50
    // Exe 50000@50001 100@50
    //

    lstTarget.clear( );

    QVariant varPorts;
    QVariant varMaxConenctions;

    int nCounter = lstParams.count( );

    if ( 3 == nCounter ) {
        varPorts = lstParams.at( 1 );
        varMaxConenctions = lstParams.at( 2 );
        ParseNetworkParams( varPorts, varMaxConenctions, lstTarget );
    } else if ( 2 == nCounter ) {
        varPorts = lstParams.at( 1 );
        ParseNetworkParams( varPorts, lstTarget );
    }
}

void QPlatformGlobal::InitializeApplication( const MyEnums::ApplicationType type )
{
    commonFunction.SetDateTimeFormat( );
    commonFunction.InstallTextCodec( );

    switch ( type ) {
    case MyEnums::PlatformCentralClient :
        InitializePlatformClient( );
        break;

    case MyEnums::PlatformCentralServer :
        InitializePlatformServer( );
        break;

    case MyEnums::PlatformCentralDataReceiver :
        InitializePlatformDataReceiver( );
        break;
    }
}

void QPlatformGlobal::SetApplicationName( const QManipulateIniFile::LogFileNames type )
{
    QString strAppName;
    manipulateFile.LogFileDirName( type, strAppName );
    qApp->setApplicationName( strAppName );
}

void QPlatformGlobal::InitializePlatformClient( )
{
    SetApplicationName( QManipulateIniFile::PlatformCentralLogClient );
}

void QPlatformGlobal::InitializePlatformServer( )
{
    SetApplicationName( QManipulateIniFile::PlatformCentralLogServer );
}

void QPlatformGlobal::InitializePlatformDataReceiver( )
{
    SetApplicationName( QManipulateIniFile::PlatformCentralLogDataReceiver );
}

void QPlatformGlobal::BrowseLog( const QManipulateIniFile::LogFileNames type )
{
    widgetLibrary.BrowseLog( type );
}

void QPlatformGlobal::StartupLogWrite( QThread *pReceiver, const MyDataStructs::QEventMultiHash &hash )
{
    MyDataStructs::PQQueueEventParams pEventParams = new MyDataStructs::QQueueEventParams;
    pEventParams->enqueue( hash );
    pGenerator->PostEvent( MyEnums::ThreadLogger, MyEnums::LogWrite, pEventParams, pReceiver );
}

void QPlatformGlobal::StartupThreadExit( QThread* pReceiver, const MyEnums::ThreadType type )
{
    pGenerator->PostEvent( type, MyEnums::ThreadExit, NULL, pReceiver );
}

void QPlatformGlobal::TcpClientConnect( QThread* pReceiver, const QString& strIP, const QString& strPort  )
{
    MyDataStructs::PQQueueEventParams pEventParams = new MyDataStructs::QQueueEventParams;
    MyDataStructs::QEventMultiHash hash;
    hash.insertMulti( MyEnums::NetworkParamIP, strIP );
    hash.insertMulti( MyEnums::NetworkParamPort, strPort );

    pEventParams->enqueue( hash );
    pGenerator->PostEvent( MyEnums::ThreadTcpClient, MyEnums::TcpClientConnect, pEventParams, pReceiver );
}

void QPlatformGlobal::TcpClientDisconnect( QThread* pReceiver )
{
    pGenerator->PostEvent( MyEnums::ThreadTcpClient, MyEnums::TcpClientDisconnect, NULL, pReceiver );
}

void QPlatformGlobal::TcpClientSendData2AllThreads( const QByteArray& byteData )
{
    MyDataStructs::QMyStringList& lstIpPort = GetTcpClientIpPortList( );
    MyDataStructs::QStringThread& thread = GetTcpClientThreadHash( );

    MyDataStructs::QMyStringSet set = lstIpPort.toSet( );

    foreach ( const QString& strIpPort, set ) {
        foreach ( QThread* pReceiver, thread.values( strIpPort ) ) {
            QByteArray* pByteData = new QByteArray( byteData );
            TcpClientSendData( pReceiver, pByteData );
        }
    }
}

void QPlatformGlobal::TcpClientSendData( QThread* pReceiver, const QByteArray *pByteData )
{
    if ( NULL == pByteData ) {
        return;
    }

    MyDataStructs::PQQueueEventParams pEventParams = new MyDataStructs::QQueueEventParams;
    MyDataStructs::QEventMultiHash hash;
    quint32 nBytePointer = ( quint32 ) pByteData;
    hash.insertMulti( MyEnums::NetworkParamData, nBytePointer );
    pEventParams->enqueue( hash );
    pGenerator->PostEvent( MyEnums::ThreadTcpClient, MyEnums::TcpClientSendData, pEventParams , pReceiver );
}

void QPlatformGlobal::GenerateLogHash( MyDataStructs::QEventMultiHash &hash, const QStringList &lstText, const QManipulateIniFile::LogTypes type )
{
    QString strSeperator = "\n";
    QString strText = lstText.join( strSeperator );
    hash.insertMulti( type, strText );
}

void QPlatformGlobal::TcpClientAllConnectOrDisconnect( bool bConnect )
{
    QStringList lstIpPort;
    MyDataStructs::QMyStringSet set = listTcpClientIpPort.toSet( );

    foreach (const QString& strIpPort,  set ) {
        lstIpPort = strIpPort.split( strColonSeperator );

        foreach ( QThread* pReceiver, hashTcpClientThread.values( strIpPort ) ) {
            bConnect ? TcpClientConnect( pReceiver, lstIpPort.at( 0 ), lstIpPort.at( 1 ) ) :
                                TcpClientDisconnect( pReceiver );
        }
    }
}

void QPlatformGlobal::CreateUdpClientThread( const QManipulateIniFile::IniFileName iniFile, const bool bMultiThread )
{
    QUdpSenderThread* pThreadInstance = bMultiThread ? NULL : pGenerator->GenerateUdpClientThread( );
    if ( !bMultiThread ) {
        ConnectUdpClientSignalSlot( pThreadInstance );
    }

    CreateUdpClientThread( iniFile, listUdpClientIpPort, hashUdpClientThread, MyEnums::UdpUnicast, pThreadInstance );
    CreateUdpClientThread( iniFile, listUdpBroadcastClientPort, hashUdpBroadcastClientThread, MyEnums::UdpBroadcast, pThreadInstance );
    CreateUdpClientThread( iniFile, listUdpMulticastClientIpPort, hashUdpMulticastClientThread, MyEnums::UdpMulticast, pThreadInstance );
}

void QPlatformGlobal::CreateUdpClientThread( const QManipulateIniFile::IniFileName iniFile,
                                             MyDataStructs::QMyStringList &listParams,
                                             MyDataStructs::QStringThread &hashThread,
                                             const MyEnums::UdpDatagramType dgType,
                                             QUdpSenderThread* pThread )
{
    bool bMultiThread = ( NULL == pThread );

    if ( listParams.isEmpty( ) ) {
        QVariant varIPs;
        QVariant varPorts;

        if ( MyEnums::UdpBroadcast == dgType ) {
            GetNetworkParams( iniFile, QManipulateIniFile::NetworkUdpBroadcastPort, varPorts );
            ParseNetworkParams( varPorts, listParams );
        } else {
            QManipulateIniFile::IniFileSectionItems itemIP;
            QManipulateIniFile::IniFileSectionItems itemPort;

            if ( MyEnums::UdpMulticast == dgType ) {
                itemIP = QManipulateIniFile::NetworkMulticastIP;
                itemPort = QManipulateIniFile::NetworkMulticastPort;
            } else {
                itemIP = QManipulateIniFile::NetworkUdpServerIP;
                itemPort = QManipulateIniFile::NetworkUdpServerPort;
            }

            GetNetworkParams( iniFile, itemIP, varIPs );
            GetNetworkParams( iniFile, itemPort, varPorts );
            ParseNetworkParams( varIPs, varPorts, listParams );
        }
    }

    foreach( const QString& strParam, listParams ) {
        if ( bMultiThread ) {
            pThread = pGenerator->GenerateUdpClientThread( );
            ConnectUdpClientSignalSlot( pThread );
        }

        hashThread.insertMulti( strParam, pThread );
    }
}

void QPlatformGlobal::ConnectUdpClientSignalSlot( QThread *pReceiver )
{
    connect( pReceiver, SIGNAL( GetWholeUdpDatagram( void*, QString, quint16, MyEnums::UdpDatagramType ) ),
             this, SLOT( HandleGetWholeUdpDatagram( void*, QString, quint16, MyEnums::UdpDatagramType ) ) );
}

void QPlatformGlobal::GetUdpListHashParam( const MyEnums::UdpDatagramType dgType,
                                           MyDataStructs::QMyStringList *&pListParam,
                                           MyDataStructs::QStringThread *&pHashThread )
{
    switch ( dgType ) {
    case MyEnums::UdpUnicast :
        pListParam = &GetUdpClientIpPortList( );
        pHashThread = &GetUdpClientThreadHash( );
        break;

    case MyEnums::UdpBroadcast :
        pListParam = &GetUdpBroadcastClientPortList( );
        pHashThread = &GetUdpBroadcastClientThreadHash( );
        break;

    case MyEnums::UdpMulticast :
        pListParam = &GetUdpMulticastClientIpPortList( );
        pHashThread = &GetUdpMulticastClientThreadHash( );
        break;
    }
}

void QPlatformGlobal::UdpClientSendData( QThread* pReceiver, const QByteArray* pByteData, const QString& strIpPort, const MyEnums::UdpDatagramType dgType )
{
    if ( NULL == pByteData ) {
        return;
    }

    bool bBroadcast = ( MyEnums::UdpBroadcast == dgType );

    MyDataStructs::PQQueueEventParams pEventParams = new MyDataStructs::QQueueEventParams;
    MyDataStructs::QEventMultiHash hash;
    MyEnums::EventType evtType = MyEnums::UdpClientSendDatagram;

    if ( bBroadcast ) {
        evtType = MyEnums::UdpClientBroadcastDatagram;
        hash.insertMulti( MyEnums::NetworkParamPort, strIpPort );
    } else {
        QStringList lstParams = strIpPort.split( strColonSeperator );
        const QString& strIP = lstParams.at( 0 );
        const QString& strPort = lstParams.at( 1 );

        hash.insertMulti( MyEnums::NetworkParamIP, strIP );
        hash.insertMulti( MyEnums::NetworkParamPort, strPort );
    }

    quint32 nBytePointer = ( quint32 ) pByteData;
    hash.insertMulti( MyEnums::NetworkParamData, nBytePointer );
    pEventParams->enqueue( hash );
    pGenerator->PostEvent( MyEnums::ThreadUdpClient, evtType, pEventParams , pReceiver );
}

void QPlatformGlobal::UdpClientSendData2AllThreads( const QByteArray& byteData, const MyEnums::UdpDatagramType dgType )
{
    MyDataStructs::QMyStringList* pListParam = NULL;
    MyDataStructs::QStringThread* pHashThread = NULL;

    GetUdpListHashParam( dgType, pListParam, pHashThread );

    MyDataStructs::QMyStringSet set = pListParam->toSet( );

    foreach ( const QString& strIpPort, set ) {
        foreach ( QThread* pReceiver, pHashThread->values( strIpPort ) ) {
            QByteArray* pByteData = new QByteArray( byteData );
            UdpClientSendData( pReceiver, pByteData, strIpPort, dgType );
        }
    }
}

void QPlatformGlobal::HandleGetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort, MyEnums::UdpDatagramType dgType )
{
    QUdpReceiverSocketThread* pSenderThread = ( QUdpReceiverSocketThread* ) sender( );
    QByteArray* pByteData = ( QByteArray* ) pByteArray;
    OutputMsg( QString( *pByteData ) );

    OutputMsg( sender( )->objectName( ) );
    emit ParseUdpData( strSenderIP, nSenderPort, pSenderThread, pByteArray, dgType );
}

void QPlatformGlobal::HandleGetWholeTcpStreamDataFromServer( QTcpSocket* pPeerSocket, void *pByteArray )
{
    QTcpClientSocketThread* pSenderThread = ( QTcpClientSocketThread* ) sender( );
    MyDataStructs::QMyStringList lstKeys = hashTcpClientThread.keys( pSenderThread );
    OutputMsg( QStringList( lstKeys ).join( strAtSeperator ) );

    QByteArray* pByteData = ( QByteArray* ) pByteArray;
    OutputMsg( QString( *pByteData ) );

    MyDataStructs::QMyStringSet set = lstKeys.toSet( );

    OutputMsg( sender( )->objectName( ) );
    foreach ( const QString& strSerevr, set ) {
        emit ParseTcpData( strSerevr, pSenderThread, pPeerSocket, pByteArray );
    }
}

MyDataStructs::QMyStringList& QPlatformGlobal::GetTcpClientIpPortList( )
{
    // IP:Port
    return listTcpClientIpPort;
}

MyDataStructs::QStringThread& QPlatformGlobal::GetTcpClientThreadHash( )
{
    return hashTcpClientThread;
}

MyDataStructs::QMyStringList& QPlatformGlobal::GetUdpClientIpPortList( )
{
    return listUdpClientIpPort;
}

MyDataStructs::QStringThread& QPlatformGlobal::GetUdpClientThreadHash( )
{
    return hashUdpClientThread;
}

MyDataStructs::QMyStringList& QPlatformGlobal::GetUdpBroadcastClientPortList( )
{
    return listUdpBroadcastClientPort;
}

MyDataStructs::QStringThread& QPlatformGlobal::GetUdpBroadcastClientThreadHash( )
{
    return hashUdpBroadcastClientThread;
}

MyDataStructs::QMyStringList& QPlatformGlobal::GetUdpMulticastClientIpPortList( )
{
    return listUdpMulticastClientIpPort;
}

MyDataStructs::QStringThread& QPlatformGlobal::GetUdpMulticastClientThreadHash( )
{
    return hashUdpMulticastClientThread;
}

MyDataStructs::QMyStringList& QPlatformGlobal::GetTcpListenerPortMaxConnectionList( )
{
    return listTcpListenerPortMaxConnection;
}

MyDataStructs::QStringThread& QPlatformGlobal::GetTcpListenerThreadHash( )
{
    return hashTcpListenerThread;
}

MyDataStructs::QMyStringList& QPlatformGlobal::GetUdpListenerPortList( )
{
    return listUdpListenerPort;
}

MyDataStructs::QStringThread& QPlatformGlobal::GetUdpListenerThreadHash( )
{
    return hashUdpListenerThread;
}

MyDataStructs::QMyStringList& QPlatformGlobal::GetUdpBroadcastListenerPortList( )
{
    return listUdpBroadcastListenerPort;
}

MyDataStructs::QStringThread& QPlatformGlobal::GetUdpBroadcastListenerThreadHash( )
{
    return hashUdpBroadcastListenerThread;
}

MyDataStructs::QMyStringList& QPlatformGlobal::GetUdpMulticastListenerIpPortList( )
{
    return listUdpMulticastListenerIpPort;
}

MyDataStructs::QStringThread& QPlatformGlobal::GetUdpMulticastListenerThreadHash( )
{
    return hashUdpMulticastListenerThread;
}

void QPlatformGlobal::GetNetworkParams(  const QManipulateIniFile::IniFileName iniFile, const QManipulateIniFile::IniFileSectionItems item, QVariant& var )
{
    manipulateFile.IniFileValue( iniFile, QManipulateIniFile::IniNetwork, item, false, var );
}

void QPlatformGlobal::ControlTimer( const QManipulateIniFile::IniFileName iniFile, const bool bStart )
{
    int nPeerThreadInterval = 0;
    int nDatabaseThreadInterval = 0;

    if ( bStart ) {
        QVariant var;
        manipulateFile.IniFileValue( iniFile, QManipulateIniFile::IniThread, QManipulateIniFile::ThreadPeerReleaseInterval, false, var );
        nPeerThreadInterval = var.toInt( ) * 60 * 1000;

        manipulateFile.IniFileValue( iniFile, QManipulateIniFile::IniDatabase, QManipulateIniFile::DatabaseObjectReleaseInterval, false, var );
        nDatabaseThreadInterval = var.toInt( ) * 60 * 1000;
    }

    pGenerator->ControlTimer( bStart, nPeerThreadInterval, nDatabaseThreadInterval );
}

void QPlatformGlobal::CreateTcpClientThread( const QManipulateIniFile::IniFileName iniFile, const bool bConnect2Host )
{
    // NetworkTcpServerIP=192.168.1.20@192.168.1.24
    // NetworkTcpServerPort=50000@50001

    if ( listTcpClientIpPort.isEmpty( ) ) {
        QVariant varIPs;
        QVariant varPorts;

        GetNetworkParams( iniFile, QManipulateIniFile::NetworkTcpServerIP, varIPs );
        GetNetworkParams( iniFile, QManipulateIniFile::NetworkTcpServerPort, varPorts );
        ParseNetworkParams( varIPs, varPorts, listTcpClientIpPort );
    }

    foreach( const QString& strParam, listTcpClientIpPort ) {
        QStringList lstParam = strParam.split( strColonSeperator );

        const QString& strIP = lstParam.at( 0 );
        const QString& strPort = lstParam.at( 1 );

        QTcpClientSocketThread* pThreadInstance = pGenerator->GenerateTcpClientThread( );
        connect( pThreadInstance, SIGNAL( GetWholeTcpStreamData( QTcpSocket*, void* ) ),
                 this, SLOT( HandleGetWholeTcpStreamDataFromServer( QTcpSocket*, void* ) ) );
        hashTcpClientThread.insertMulti( strParam, pThreadInstance );

        if ( bConnect2Host ) {
            TcpClientConnect( pThreadInstance, strIP, strPort );
        }
    }
}

void QPlatformGlobal::TcpListenerStartup( QThread *pReceiver, const QString& strPort, const QString& strMaxConnection )
{
    MyDataStructs::PQQueueEventParams pEventParams = new MyDataStructs::QQueueEventParams;
    MyDataStructs::QEventMultiHash hash;

    hash.insertMulti( MyEnums::NetworkParamListenerPort, strPort );
    hash.insertMulti( MyEnums::NetworkParamListenerMaxConnections, strMaxConnection );

    pEventParams->enqueue( hash );
    pGenerator->PostEvent( MyEnums::ThreadTcpListener, MyEnums::TcpListenerStartup, pEventParams, pReceiver );
}

void QPlatformGlobal::TcpListenerAllStartup( )
{
    QStringList lstPortConnection;

    foreach (const QString& strPortConn,  listTcpListenerPortMaxConnection ) {
        lstPortConnection = strPortConn.split( strColonSeperator );

        foreach ( QThread* pReceiver, hashTcpListenerThread.values( strPortConn ) ) {
            TcpListenerStartup( pReceiver, lstPortConnection.at( 0 ), lstPortConnection.at( 1 ) );
        }
    }
}

void QPlatformGlobal::CreateUdpListenerThread( MyDataStructs::QMyStringList &listParams,
                                               MyDataStructs::QStringThread& hashThread,
                                               const QManipulateIniFile::IniFileName iniFile,
                                               const QManipulateIniFile::IniFileSectionItems item,
                                               const bool bServer, const bool bStartupListener,
                                               const MyEnums::UdpDatagramType dgType )
{
    bool bMulticast = MyEnums::UdpMulticast == dgType;

    if ( listParams.isEmpty( ) ) {
        QVariant varIPs;
        QVariant varPorts;    

        if ( bMulticast ) {
            GetNetworkParams( iniFile, QManipulateIniFile::NetworkMulticastIP, varIPs );
            GetNetworkParams( iniFile, item, varPorts );
            ParseNetworkParams( varIPs, varPorts, listParams );
        } else {
            GetNetworkParams( iniFile, item, varPorts );
            ParseNetworkParams( varPorts, listParams );
        }
    }

    foreach ( const QString& strParam, listParams ) {
        if ( hashThread.keys( ).contains( strParam ) ) {
            continue;
        }

        QStringList lstParam = strParam.split( strColonSeperator );
        const QString& strPort = lstParam.at( bMulticast ? 1 : 0 );

        QUdpReceiverSocketThread* pThreadInstance = pGenerator->GenerateUdpListenerThread( bServer, dgType );
        connect( pThreadInstance, SIGNAL( GetWholeUdpDatagram(void*,QString,quint16,MyEnums::UdpDatagramType)),
                 this, SLOT( HandleGetWholeUdpDatagram( void*, QString, quint16, MyEnums::UdpDatagramType ) ) );
        hashThread.insertMulti( strParam, pThreadInstance );

        if ( bStartupListener ) {
            UdpListenerStartup( pThreadInstance, strPort );
        }
    }
}

void QPlatformGlobal::CreateUdpListenerThread( const QManipulateIniFile::IniFileName iniFile, const bool bServer, const bool bStartupListener )
{
    // NetworkUdpServerPort=50000@50001
    CreateUdpListenerThread( listUdpListenerPort, hashUdpListenerThread, iniFile,
                             QManipulateIniFile::NetworkUdpServerPort, bServer,
                             bStartupListener, MyEnums::UdpUnicast );
}

void QPlatformGlobal::UdpListenerStartup( QThread* pReceiver, const QString& strPort )
{
    MyDataStructs::PQQueueEventParams pEventParams = new MyDataStructs::QQueueEventParams;
    MyDataStructs::QEventMultiHash hash;

    hash.insertMulti( MyEnums::NetworkParamListenerPort, strPort );

    pEventParams->enqueue( hash );
    pGenerator->PostEvent( MyEnums::ThreadUdpListener, MyEnums::UdpServerStartupListening, pEventParams, pReceiver );
}

void QPlatformGlobal::UdpListenerAllStartup( MyDataStructs::QMyStringList &listParams, MyDataStructs::QStringThread& hashThread )
{
    foreach (const QString& strPort,  listParams ) {
        foreach ( QThread* pReceiver, hashThread.values( strPort ) ) {
            UdpListenerStartup( pReceiver,strPort );
        }
    }
}

void QPlatformGlobal::UdpListenerAllStartup(  )
{
    UdpListenerAllStartup( listUdpListenerPort, hashUdpListenerThread );
}

void QPlatformGlobal::CreateUdpBroadcastListenerThread( const QManipulateIniFile::IniFileName iniFile, const bool bServer, const bool bStartupListener )
{
    CreateUdpListenerThread( listUdpBroadcastListenerPort, hashUdpBroadcastListenerThread, iniFile,
                             QManipulateIniFile::NetworkUdpBroadcastPort, bServer,
                             bStartupListener, MyEnums::UdpBroadcast );
}

void QPlatformGlobal::UdpBroadcastListenerStartup( QThread* pReceiver, const QString& strPort )
{
    UdpListenerStartup( pReceiver, strPort );
}

void QPlatformGlobal::UdpBroadcastListenerAllStartup(  )
{
    UdpListenerAllStartup( listUdpBroadcastListenerPort, hashUdpBroadcastListenerThread );
}

void QPlatformGlobal::CreateUdpMulticastListenerThread( const QManipulateIniFile::IniFileName iniFile, const bool bServer, const bool bStartupListener )
{
    CreateUdpListenerThread( listUdpMulticastListenerIpPort, hashUdpMulticastListenerThread, iniFile,
                             QManipulateIniFile::NetworkMulticastPort, bServer,
                             bStartupListener, MyEnums::UdpMulticast );
}

void QPlatformGlobal::UdpMulticastListenerStartup( QThread* pReceiver, const QString& strPort )
{
    UdpListenerStartup( pReceiver, strPort );
}

void QPlatformGlobal::UdpMulticastListenerAllStartup(  )
{
    UdpListenerAllStartup( listUdpMulticastListenerIpPort, hashUdpMulticastListenerThread );
}

void QPlatformGlobal::ParseNetworkParams( QVariant& varParam1, QVariant& varParam2, MyDataStructs::QMyStringList& lstParams  )
{
    // NetworkTcpServerPort=50000@50001
    // NetworkTcpMaxConnection=100@50

    QString strParam1;
    QString strParam2;

    strParam1 = varParam1.toString( );
    QStringList lstParam1 = strParam1.split( strAtSeperator );
    int nParam1 = lstParam1.count( );

    strParam2 = varParam2.toString( );
    QStringList lstParam2 = strParam2.split( strAtSeperator );
    int nParam2 = lstParam2.count( );

    if ( 0 == nParam1 * nParam2 || nParam1 != nParam2 ) {
        QStringList lstTexts;
        lstTexts << Q_FUNC_INFO;
        lstTexts << "Parammeter Error";
        lstTexts << strParam1 << strParam2;
        MyDataStructs::QEventMultiHash hash;
        GenerateLogHash( hash, lstTexts, QManipulateIniFile::LogCfgParam );
        StartupLogWrite( pGenerator->GenerateLogThread( ), hash );
        return;
    }

    QString strKey = "%1:%2";
    QString strTmpKey;

    for ( int nIndex = 0; nIndex < nParam1; nIndex++ ) {
        const QString& str1 = lstParam1.at( nIndex );
        const QString& str2 = lstParam2.at( nIndex );

        strTmpKey = strKey.arg( str1, str2 );
        lstParams.append( strTmpKey );
    }
}

void QPlatformGlobal::ParseNetworkParams( QVariant& varParam1, MyDataStructs::QMyStringList& lstParams  )
{
    // NetworkTcpServerPort=50000@50001
    // NetworkTcpMaxConnection=100@50

    QString strParam1;

    strParam1 = varParam1.toString( );
    QStringList lstParam1 = strParam1.split( strAtSeperator );
    int nParam1 = lstParam1.count( );


    if ( 0 == nParam1 ) {
        QStringList lstTexts;
        lstTexts << Q_FUNC_INFO;
        lstTexts << "Parammeter Error";
        MyDataStructs::QEventMultiHash hash;
        GenerateLogHash( hash, lstTexts, QManipulateIniFile::LogCfgParam );
        StartupLogWrite( pGenerator->GenerateLogThread( ), hash );
        return;
    }

    QString strKey = "%1";
    QString strTmpKey;

    for ( int nIndex = 0; nIndex < nParam1; nIndex++ ) {
        const QString& str1 = lstParam1.at( nIndex );

        strTmpKey = strKey.arg( str1 );
        lstParams.append( strTmpKey );
    }
}

void QPlatformGlobal::CreateTcpListenerThread( const QManipulateIniFile::IniFileName iniFile, const bool bStartupListener )
{
    // NetworkTcpServerPort=50000@50001
    // NetworkTcpMaxConnection=100@50

    if ( listTcpListenerPortMaxConnection.isEmpty( ) ) {
        QVariant varPorts;
        QVariant varMaxConnections;

        GetNetworkParams( iniFile, QManipulateIniFile::NetworkTcpServerPort, varPorts );
        GetNetworkParams( iniFile, QManipulateIniFile::NetworkTcpMaxConnection, varMaxConnections );
        ParseNetworkParams( varPorts, varMaxConnections, listTcpListenerPortMaxConnection );
    }

    foreach ( const QString& strParam, listTcpListenerPortMaxConnection ) {
        if ( hashTcpListenerThread.keys( ).contains( strParam ) ) {
            continue;
        }

        QStringList lstParam = strParam.split( strColonSeperator );
        const QString& strPort = lstParam.at( 0 );
        const QString& strMaxConn = lstParam.at( 1 );

        QListenerThread* pThreadInstance = pGenerator->GenerateTcpListenerThread( );
        hashTcpListenerThread.insertMulti( strParam, pThreadInstance );

        if ( bStartupListener ) {
            TcpListenerStartup( pThreadInstance, strPort, strMaxConn );
        }
    }
}

void QPlatformGlobal::UdpOperateMulticastGroup( const bool bJoin, const QString& strIpPort )
{
    MyDataStructs::QStringThread& hashThreads = GetUdpMulticastListenerThreadHash( );
    QStringList lstIpPort = strIpPort.split( strColonSeperator );

    if ( 0 == lstIpPort.count( ) ) {
        return;
    }

    const QString& strIP = lstIpPort.at( 0 );
    QThread* pThread = hashThreads.value( strIpPort );

    MyDataStructs::PQQueueEventParams pEventParams = new MyDataStructs::QQueueEventParams;
    MyDataStructs::QEventMultiHash hash;
    hash.insertMulti( MyEnums::NetworkParamIP, strIP );

    pEventParams->enqueue( hash );
    pGenerator->PostEvent( MyEnums::ThreadUdpListener,
                           bJoin ? MyEnums::UdpServerJoinMulticast : MyEnums::UdpServerLeaveMulticast,
                           pEventParams, pThread );
}

void QPlatformGlobal::UdpOperateAllMulticastGroups( const bool bJoin )
{
    MyDataStructs::QMyStringList& lstParams = GetUdpMulticastListenerIpPortList( );

    foreach ( const QString& strParam, lstParams ) {
        UdpOperateMulticastGroup( bJoin, strParam );
    }
}
