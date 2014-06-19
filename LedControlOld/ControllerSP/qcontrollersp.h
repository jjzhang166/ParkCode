#ifndef QCONTROLLERSP_H
#define QCONTROLLERSP_H

#include <QObject>
#include "ControllerSP_global.h"
#include "qextserialport/win_qextserialport.h"
#include "../ControllerCommon/CommonHead.h"

class CONTROLLERSPSHARED_EXPORT QControllerSP : public QObject {
    Q_OBJECT

public:
    QControllerSP( QObject* parent = 0 );
    virtual ~QControllerSP( );

    bool IsOpened( );
    bool OpenPort( );
    void ClosePort( );
    qint64 WriteData( QByteArray& data, int nWaitTime = 0, const bool bThread = false );

private:
    BaudRateType GetBaud( quint8 nIndex );
    DataBitsType GetDataBit( quint8 nIndex );
    StopBitsType GetStopBit( quint8 nIndex );
    ParityType GetParity( quint8 nIndex );
    FlowType GetFlow( quint8 nIndex );
    void ConfigPortBeforeOpen( const LedControll::SComConfig& sConfig );
    void ConfigPortAfterOpen( const LedControll::SComConfig& sConfig );

private:
    Win_QextSerialPort* winPort;

signals:
    void Data( QByteArray data );
    void Cmd( QByteArray data, bool bSend );

public slots:

private slots:
    void ReceiveData( );
};

#endif // QCONTROLLERSP_H
