#ifndef COMMONDATA_H
#define COMMONDATA_H
#define CLIENT_INSTANCE ( int ) ( 2 )
#define SERVER_INSTANCE ( int ) ( 2 )
#define CLIENT_SERVER_TCP_PORT ( quint16 ) ( 60010 )
#define CLIENT_SERVER_UDP_PORT ( quint16 ) ( 60011 )
#define  UDP_DISPATCHER_PORT ( quint16 ) ( 60001 )
#define  TCP_DISPATCHER_PORT ( quint16 ) ( 60000 )
#define  HB_DISPATCHER_PORT ( quint16 ) ( 60001 )
#define  HTTP_DISPATCHER_PORT ( quint16 ) ( 80 )
#define  UDP_THREADPOOL_THREAD ( int ) ( 20 )
#define  TCP_THREADPOOL_THREAD ( int ) ( 20 )
#define  TCP_MAXPENDIG_CONN ( int ) ( 100 )
#define  ROW_SEPERATOR "\r"
#define  COL_SEPERATOR "\n"

#define TABLE_COUNT  ( int ) ( 0 )
#define HBCMD_COUNT ( int ) ( 0 )

#define HANDSHAKE "Success"

#include <Qt>
#include "netcommfunction.h"


///
// CommonHeader +
// OtherHeader +
// Body
namespace NetTransport {
    typedef enum __eTableType {
        TabInOutRecord,
        TabImgLog
    } eTableType;

    typedef struct __sTableType {
        quint16 TabInOutRecord : 1;
        quint16 TabImgLog : 1;
        quint16 TabParkInfo : 1;
        quint16 Tmp1 : 1;
        quint16 Tmp2 : 1;
        quint16 Tmp3 : 1;
        quint16 Tmp4 : 1;
        quint16 Tmp5 : 1;
        quint16 Tmp6 : 1;
        quint16 Tmp7 : 1;
        quint16 Tmp8 : 1;
        quint16 Tmp9 : 1;
        quint16 Tmp10 : 1;
        quint16 Tmp11 : 1;
        quint16 Tmp12 : 1;
        quint16 Tmp13 : 1;
    } sTableType;

    typedef enum __ePacketType {
        PacketTable,
        PacketImage,
        PacketHeartbeat,
        PacketSvrMsg, // From Center Server
        PacketCltMsg, // From Terminal Client
        PacketMgmtData
    } ePacketType;

    typedef struct __sPacketType {
        quint16 PacketTable : 1;
        quint16 PacketImage : 1;
        quint16 PacketHeartbeat : 1;
        quint16 PacketSvrMsg : 1;
        quint16 PacketCltMsg : 1;
        quint16 PacketMgmtData : 1;
        quint16 Tmp5 : 1;
        quint16 Tmp6 : 1;
        quint16 Tmp7 : 1;
        quint16 Tmp8 : 1;
        quint16 Tmp9 : 1;
        quint16 Tmp10 : 1;
        quint16 Tmp11 : 1;
        quint16 Tmp12 : 1;
        quint16 Tmp13 : 1;
        quint16 Tmp14 : 1;
    } sPacketType;

    typedef enum __eHeartbeat {
        HbClientIP,
        HbNetState,
        HbImgRequest
    } eHeartbeat;

    typedef enum __eMgmtData {
        MgmtTable,
        MgmtOtherData
    } eMgmtData;

    typedef struct __sHeartbeat {
        quint16 HbClientIP : 1;
        quint16 HbNetState : 1;
        quint16 Hb2 : 1;
        quint16 Hb3 : 1;
        quint16 Hb4 : 1;
        quint16 Hb5 : 1;
        quint16 Hb6 : 1;
        quint16 Hb7 : 1;
        quint16 Hb8 : 1;
        quint16 Hb9 : 1;
        quint16 Hb10 : 1;
        quint16 Hb11 : 1;
        quint16 Hb12 : 1;
        quint16 Hb13 : 1;
        quint16 Hb14 : 1;
        quint16 Hb15 : 1;
    } sHeartbeat;

    typedef enum __eCltMsg {
        CltTable,
        CltImg,
        CltHeartbeat
    } eCltMsg;

    typedef struct __sCltMsg {
        quint16 CltTable : 1;
        quint16 CltImg : 1;
        quint16 CltHeartbeat : 1;
        quint16 Hb3 : 1;
        quint16 Hb4 : 1;
        quint16 Hb5 : 1;
        quint16 Hb6 : 1;
        quint16 Hb7 : 1;
        quint16 Hb8 : 1;
        quint16 Hb9 : 1;
        quint16 Hb10 : 1;
        quint16 Hb11 : 1;
        quint16 Hb12 : 1;
        quint16 Hb13 : 1;
        quint16 Hb14 : 1;
        quint16 Hb15 : 1;
    } sCltMsg;

    typedef enum __eSvrMsg {
        SvrAlert,
        SvrGetInOutImg
    } eSvrMsg;

    typedef struct __sSvrMsg {
        quint16 SvrAlert : 1;
        quint16 SvrGetInOutImg : 1;
        quint16 Hb2 : 1;
        quint16 Hb3 : 1;
        quint16 Hb4 : 1;
        quint16 Hb5 : 1;
        quint16 Hb6 : 1;
        quint16 Hb7 : 1;
        quint16 Hb8 : 1;
        quint16 Hb9 : 1;
        quint16 Hb10 : 1;
        quint16 Hb11 : 1;
        quint16 Hb12 : 1;
        quint16 Hb13 : 1;
        quint16 Hb14 : 1;
        quint16 Hb15 : 1;
    } sSvrMsg;

    typedef enum __eImageType {
        ImgOut,
        ImgIn,
        ImgCar,
        ImgOwner
    } eImageType;

    typedef struct __sImageType {
        quint16 ImgCar : 1;
        quint16 ImgOwner : 1;
        quint16 ImgIn : 1;
        quint16 ImgOut : 1;
        quint16 img1 : 1;
        quint16 img2 : 1;
        quint16 img3 : 1;
        quint16 img4 : 1;
        quint16 img5 : 1;
        quint16 img6 : 1;
        quint16 img7 : 1;
        quint16 img8 : 1;
        quint16 img9 : 1;
        quint16 img10 : 1;
        quint16 img11 : 1;
        quint16 img12 : 1;
    } sImageType;

    typedef struct __CommonHeader {
        sPacketType dgType; // Datagram type
        quint16 nReserved; // Aligment
        quint32 nDataLen; // Datagram len 4G
    } CommonHeader, *PCommonHeader;

    typedef struct __CltMsgHeader {
        sCltMsg cltMsgType;
        quint16 nReserved;
        //union {
        //    TableHeader tabHeader;
        //   ImageHeader imgHeader;
        //};
    } CltMsgHeader, *PCltMsgHeader;

    typedef struct __SvrMsgHeader {
        sSvrMsg svrMsgType;
        quint16 nReserved;
    } SvrMsgHeader, *PSvrMsgHeader;

    typedef struct __HeartbeatHeader {
        sHeartbeat hbType;
        quint16 nReserved;
    } HeartbeatHeader, *PHeartbeatHeader;

    typedef struct __TableHeader {
        sTableType tabType; // Table Data type
        quint16 nRows; // Data row count;
        quint16 nCols; // Data col count of each  row
    } TableHeader, *PTableHeader;

    typedef struct __ImageHeader {
        sImageType imgType; // 2
        quint32 nCardID; // 2
        quint32 nReserved; // 2
        char cPlate[ 10 ];
        quint32 nImgSize; // 4G
        quint64 nParkID;
        quint64 nMSecsSinceEpoch;
    } ImageHeader, *PImageHeader;

    typedef struct __MgmtHeader {
        eMgmtData mgmtType; // 4
        quint32 nDataLen; // 4
        char cName[ 32 ]; // 8
    } MgmtHeader , *PMgmtHeader ;

    typedef struct __DispatcherData { // BE LE
        CommonHeader CommHeader;

        union {
            TableHeader tabHeader;
            ImageHeader imgHeader;
            HeartbeatHeader hbHeader;
            SvrMsgHeader svrHeader;
            CltMsgHeader cltHeader;
            MgmtHeader mgmtHeader;
        } auxHeader;

        // Body
    } DispatcherData, *PDispatcherData;
}

#endif // COMMONDATA_H
