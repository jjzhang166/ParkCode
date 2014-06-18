#ifndef WINSERIALPORT_H
#define WINSERIALPORT_H

#include <QObject>
#include "qextserialport/win_qextserialport.h"
#include <QSettings>

class CWinSerialPort : public QObject
{
    Q_OBJECT
public:
    explicit CWinSerialPort( const char* pCOMSection, QObject *parent = 0);
    virtual ~CWinSerialPort();

    void ConfigPort( );
    bool OpenPort( );
    void SetPortName( );
    void SetQueryMode( QextSerialBase::QueryMode mode );
    void ClosePort( );
    bool IsOpened( );
    void GetCfg( QStringList& cfgStream, bool bRead );
    qint64 WriteData( QByteArray& data );
    Win_QextSerialPort& GetRawSerialPort( );

private:
    BaudRateType GetBaud( int nIndex );
    DataBitsType GetDataBit( int nIndex );
    StopBitsType GetStopBit( int nIndex );
    ParityType GetParity( int nIndex );
    FlowType GetFlow( int nIndex );

signals:

public slots:

private:
     Win_QextSerialPort* pWinSerialPort;
     QObject *pParent;
     QSettings* pSettings;
     QString strCOMSection;

 private slots:

};

#endif // WINSERIALPORT_H
