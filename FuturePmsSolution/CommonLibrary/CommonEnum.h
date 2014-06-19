#ifndef COMMONENUM_H
#define COMMONENUM_H
#include <QEvent>
namespace MyEnums {
    enum ApplicationType {
        PlatformCentralClient,
        PlatformCentralServer,
        PlatformCentralDataReceiver
    };

    enum DatabaseType {
        DbMySQL,
        DbSQLServer,
        DbSybase,
        DbOracle,
        DbDB2,
        DbSQLlite,
        DbBDB,
        DbAccess,
        DbPostgreSQL
    };

    enum ThreadType {
        ThreadLogger,
        ThreadTcpListener,
        ThreadUdpListener,
        ThreadTcpPeer,
        ThreadTcpClient,
        ThreadUdpClient,
        ThreadDatabase,
        ThreadFreeTcpPeerSocketThread,
        ThreadFreeDatabaseObjectThread
    };

    enum EventType {
        // Logger event
        LogEventBegin = QEvent::User,
        LogWrite,
        LogEventEnd,
        ////////////////////////////////////////
        TcpLinstenerEventBegin,
        TcpListenerStartup,
        TcpLinstenerEventEnd,
        ////////////////////////////////////////
        TcpPeerEventStart,
        TcpPeerCreateSocket,
        TcpPeerThreadPoolFeedback,
        TcpPeerEventEnd,
        /////////////////////////////////////////
        TcpClientEventStart,
        TcpClientConnect,
        TcpClientDisconnect,
        TcpClientSendData,
        TcpClientEventEnd,
        //////////////////////////////////////////
        UdpServerEventStart,
        UdpServerThreadPoolFeedback,
        UdpServerStartupListening,
        UdpServerJoinMulticast,
        UdpServerLeaveMulticast,
        UdpServerBroadcastDatagram,
        UdpServerSendDatagram,
        UdpServerEventEnd,
        //////////////////////////////////////////
        UdpClientEventStart,
        UdpClientBroadcastDatagram,
        UdpClientSendDatagram,
        UdpClientReceiveDatagram,
        UdpClientEventEnd,
        //////////////////////////////////////////
        FreeTcpPeerSocketThreadEventStart,
        TcpPeerSocketThreadFreeCheck,
        FreeTcpPeerSocketThreadEventEnd,
        //////////////////////////////////////////
        DatabaseConnectionPoolEventStart,
        DatabaseObjectFreeCheck,
        DatabaseConnectionPoolEventEnd,
        //////////////////////////////////////////
        DatabaseEventStart,
        DatabaseCrud, // CRUD Operation / SP
        DatabaseObjectEnqueue,
        DatabaseEventEnd,
        ThreadExit
    };

    enum LogType {
        Database,
        Network,
        Other,
        LogItems
    };

    enum UdpDatagramType {
        UdpUnicast,
        UdpBroadcast,
        UdpMulticast
    };

    enum EventParamType {
        ///////////// Network
        NetworkParamIP,
        NetworkParamPort, // TCP UDP Shared
        NetworkParamListenerPort,
        NetworkParamListenerMaxConnections,
        NetworkParamData,
        NetworkParamSocket,
        NetworkParamUdpSenderIP,
        NetworkParamUdpSenderPort,
        NetworkParamUdpDatagramType,
        NetworkParamSenderThread,
        NetworkParamDatabaseObject
    };

    ///////////////// Network data stream or datagram
    typedef enum __eTableType {
        TabInOutRecord,
        TabImgLog
    } eTableType;

    typedef enum __ePacketType {
        PacketTable,
        PacketImage,
        PacketHeartbeat,
        PacketSvrMsg, // From Center Server
        PacketCltMsg, // From Terminal Client
        PacketMgmtData
    } ePacketType;

    typedef enum __eHeartbeat {
        HbClientIP,
        HbNetState
    } eHeartbeat;

    typedef enum __eMgmtData {
        MgmtTable,
        MgmtOtherData
    } eMgmtData;

    typedef enum __eCltMsg {
        CltTable,
        CltImg,
        CltHeartbeat
    } eCltMsg;

    typedef enum __eSvrMsg {
        SvrAlert,
        SvrGetInOutImg
    } eSvrMsg;

    typedef enum __eImageType {
        ImgOut,
        ImgIn,
        ImgCar,
        ImgOwner
    } eImageType;
}

#endif // COMMONENUM_H
