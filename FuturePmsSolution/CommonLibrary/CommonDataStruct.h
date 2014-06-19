#ifndef COMMONDATASTRUCT_H
#define COMMONDATASTRUCT_H

#include <QQueue>
#include <QVariant>
#include <QTcpSocket>

namespace MyDataStructs {
    typedef QMultiHash< int, QVariant > QEventMultiHash, *PQEventMultiHash, QParamMultiHash;
    typedef QQueue< QEventMultiHash > QQueueEventParams, *PQQueueEventParams;
    typedef QList< QString > QMyStringList, *PQMyStringList;
    typedef QSet< QString > QMyStringSet, *PQMyStringSet;
    typedef QMultiHash< QString, QThread* > QStringThread, *PQStringThread;
    typedef QMultiHash< bool, QTcpSocket* > QSocketMultiHash; // true unused, false used
    typedef QQueue< void* > QPointerQueue, *PQPointerQueue;
    typedef QList< void* > QPointerList, *PQPointerList;

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

    typedef struct __sMgmtDataType {
        quint16 MgmtTable : 1;
        quint16 MgmtOtherData : 1;
        quint16 Mgmt1 : 1;
        quint16 Mgmt2 : 1;
        quint16 Mgmt3 : 1;
        quint16 Mgmt4 : 1;
        quint16 Mgmt5 : 1;
        quint16 Mgmt6 : 1;
        quint16 Mgmt7 : 1;
        quint16 Mgmt8 : 1;
        quint16 Mgmt9 : 1;
        quint16 Mgmt10 : 1;
        quint16 Mgmt11 : 1;
        quint16 Mgmt12 : 1;
        quint16 Mgmt13 : 1;
        quint16 Mgmt14 : 1;
    } sMgmtDataType;

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
        sMgmtDataType mgmtType; // 2
        quint32 nDataLen; // 4
        char cName[ 34 ]; // 10
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

#endif // COMMONDATASTRUCT_H
