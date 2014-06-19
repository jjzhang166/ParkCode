#ifndef QCMDPARSER_H
#define QCMDPARSER_H

#include <QObject>

class QCmdParser : public QObject
{
    Q_OBJECT
public:
    explicit QCmdParser(QObject *parent = 0);
    virtual ~QCmdParser( );

    void ParseDataDomain( QByteArray& data, QString& strInfo, qint8& nIndex );

private:
    inline void GeLedtIlluminance( QByteArray& data, QString& strInfo );
    inline void GetLedTemperature( QByteArray& data, QString& strInfo );
    inline void GetLedWorkState( QByteArray& data, QString& strInfo );
    inline void GetLedFreqTriggerMode( QByteArray& data, QString& strInfo );
    inline void GetLedFreqTime( QByteArray& data, QString& strInfo );
    inline void GetLedFlashTime( QByteArray& data, QString& strInfo );
    inline void GetLedFreqBrightness( QByteArray& data, QString& strInfo );
    inline void GetLedFlashBrightness( QByteArray& data, QString& strInfo );
    inline void GetLedFlashRadiance( QByteArray& data, QString& strInfo );
    inline void GetLedFrenquencyRadiance( QByteArray& data, QString& strInfo );
    inline void GetLedFrequency( QByteArray& data, QString& strInfo );
    inline void GetLedWorkVoltage( QByteArray& data, QString& strInfo );
    inline void GetLedExternalTriggerSignalState( QByteArray& data, QString& strInfo );
    inline void GetLedFlashTriggerMode( QByteArray& data, QString& strInfo );

    inline void GetFloatValue( QByteArray& data, QString& strInfo );
    inline void GetIntegerValue( QByteArray& data, QString& strInfo );
    inline void GetTriggerMode( QByteArray& data, QString& strInfo );
    inline void GetThreshold( QByteArray& data, QString& strInfo );
    inline void GetFrameFreqControl( QByteArray& data, QString& strInfo );
    
signals:
    
public slots:
    
};

#endif // QCMDPARSER_H
