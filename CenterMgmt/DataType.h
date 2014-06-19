#ifndef DATATYPE_H
#define DATATYPE_H

#include <Qt>

namespace Mgmt {
    typedef struct __SvrRequestType {
        //quint32 DataTable : 1;
        //quint32 DataOther : 1;
        //quint32 DataHandshake : 1;
        quint32 nRequestType;
    } SvrRequestType;

    typedef enum __ePacketType {
        PacketTable,
        PacketOther,
        PacketHandshake
    } ePacketType;

    typedef struct __CommonHeader {
        SvrRequestType dgType; // 4
        quint32 nPacketSize;
    } CommonHeader, *PCommonHeader;

    typedef struct __ContentHeader {
        char cName[ 32 ]; // 4
        quint32 nDataLen;
    } ContentHeader, *PContentHeader;

    typedef struct __DispatcherData { // BE LE
        CommonHeader CommHeader;

        union {
            ContentHeader cntHeader;
        } auxHeader;

        // Body
    } DispatcherData, *PDispatcherData;
}

#endif // DATATYPE_H
