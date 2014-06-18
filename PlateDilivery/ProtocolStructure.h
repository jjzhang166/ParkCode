#ifndef PROTOCOLSTRUCTURE_H
#define PROTOCOLSTRUCTURE_H

#include <QtGlobal>
#include <QByteArray>

namespace Protocol {

enum RequestType {
    RequestReserved = 0,
    RequestQueryBallotSenseState,
    RequestQueryGateSenseState,
    RequestQueryInfraredState,
    RequestControlLED,
    RequestControlTrafficLights,
    RequestControlGate,
    RequestQueryPlateData,
    RequestVehicleUpDwonWeigh,
    RequestSavePlate,
    RequestActiveSend
};

enum ResponseType {
    ResponseReserved = 0,
    ResponseBallotSenseState,
    ResponseGateSenseState,
    ResponseInfraredState,
    ResponsePlateData,
    ResponseActiveSend
};

const quint8 nTokenLength = 8;
const quint8 nDateTimeLength = 14;
const quint8 nHeadLength = nTokenLength + sizeof ( quint8 ) + sizeof ( quint32 );
const QByteArray byToken( "ScFuture", nTokenLength );

typedef struct __ProtocolStructure {
    struct Head {
        qint8       nToken[ nTokenLength ];
        quint8      nMessageType;
        quint32     nTcpStreamLength;
    } Head;

    union Body {
        struct Request {
            union Part {
                struct QuerySenseState {
                    quint8 nAddress;
                } QuerySenseState;

                struct QueryInfraredState {
                    quint8 nAddress;
                } QueryInfraredState;

                struct ControlTrafficLights {
                    quint8 nAddress;
                    quint8 nOperation;
                } ControlTrafficLights;

                struct ControlGate {
                    quint8 nAddress;
                    quint8 nOperation;
                } ControlGate;

                struct ControlLED {
                    quint8 nAddress;
                    quint8 nData[ 1 ];// Content
                } ControlLED;

                struct QueryPlateData {
                    quint8 nAddress;
                } QueryPlateData;
            } Part;
        } Request;

        struct Response {
            union Part {
                struct SenseState {
                    quint8 nAddress;
                    quint8 nState;
                } SenseState;

                struct InfraredState {
                    quint8 nAddress;
                    quint8 nState;
                } InfraredState;

                struct PlateData {
                    quint8 nAddress;
                    quint8 nDateTime[ nDateTimeLength ];
                    quint8 nConfidence;
                    quint8 nPlateByteCount;
                    quint32 nPictureByteCount;
                    quint8 nData[ 1 ];
                    // Variable data
                    // PlateValue
                    // PictureValue
                } PlateData;
            } Part;
        } Response;
    } Body;
} ProtocolStructures, *PProtocolStructure;

}

#endif // PROTOCOLSTRUCTURE_H
