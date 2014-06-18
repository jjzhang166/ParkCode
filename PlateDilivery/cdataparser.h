#ifndef CDATAPARSER_H
#define CDATAPARSER_H

#include <QObject>
#include "ProtocolStructure.h"
#include "../SerialPort/winserialport.h"

class CDataParser : public QObject
{
    Q_OBJECT
public:
    explicit CDataParser(QObject *parent = 0);
    void Parse( QByteArray& byStream );

    QByteArray GetToken( QByteArray& byStream );
    quint8 GetMessageType( QByteArray& byStream );
    quint32 GetStreamLength( QByteArray& byStream );
    QByteArray GetBody( QByteArray& byStream );

    void TimerActiveSend( quint16 nAddress );

private:
    void ProcessBallotSenseRequest( QByteArray& byStream );
    void ProcessGateSenseRequest( QByteArray& byStream );
    void ProcessInfraredRequest( QByteArray& byStream );
    void ProcessLedRequest( QByteArray& byStream );
    void ProcessTrafficLightsRequest( QByteArray& byStream );
    void ProcessGateRequest( QByteArray& byStream );
    void ProcessPlateRequest( QByteArray& byStream );
    void ProcessVehicleUpDwonWeigh( QByteArray& byStream );
    void ProcessSavePlateRequest( QByteArray& byStream );
    void ProcessActiveSendRequest( QByteArray& byStream );

    void ProcessResponse( QByteArray& byStream );
    void ProcessBallotSenseResponse( QByteArray& byStream );
    void ProcessGateSenseResponse( QByteArray& byStream );
    void ProcessInfraredResponse( QByteArray& byStream );
    void ProcessPlateResponse( QByteArray& byStream );
    void ProcessActiveSendResponse( QByteArray& byStream );

    void CreateReponse( Protocol::ResponseType respType, quint8 nState, quint8 nAddress );
    void CreateBallotSenseReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress );
    void CreateGateSenseReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress );
    void CreateInfraredReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress );
    void CreatePlateReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress );
    void CreateActiveSendReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress );

    void ControlSerialPort( CWinSerialPort* pSerial, bool bOpen );
    int ParseUpCmd( QByteArray& byData,quint8 &nCanAddr );
    void ParseSerialData( QByteArray& byData );
    void WriteSerial( CWinSerialPort* pSerial, char cCmd[ ], int nCmdLen );

    void CaptureImage( quint8 nChannel );

private:
     CWinSerialPort* pSerialPort;
     CWinSerialPort* pWineSerialPort;
    
signals:
     void Response( QByteArray byResponse );
     void Capture( quint8 nChannel );
    
public slots:
     void DataMayRead( );
    
};

#endif // CDATAPARSER_H
