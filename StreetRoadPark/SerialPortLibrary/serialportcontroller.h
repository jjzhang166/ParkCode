#ifndef SERIALPORTCONTROLLER_H
#define SERIALPORTCONTROLLER_H

#include "SerialPortLibrary_global.h"
#include <QObject>

#include "creceiverthread.h"
#include "csenderthread.h"

class SERIALPORTLIBRARYSHARED_EXPORT SerialPortController : public QObject
{
    Q_OBJECT
public:
    typedef enum __CmdPort {
        CmdDetectorThresholdModify = 0,
        CmdDetectorDelayTimeModify,
        CmdDetectorReadData$,
        CmdDetectorReadDataR,
        CmdDetectorReadDataA,
        CmdDetectorForceReset,
        CmdDetectorModifyID,
        CmdDetectorModifyChannel,
        CmdDetectorCommunicationTestOpen,
        CmdDetectorCommunicationTestClose,
        CmdReceiverModifyHostChannel,
        CmdReciverSetID,
        CmdReceiverHostSleep,
        CmdCount
    } CmdPort;

    static SerialPortController* GetController( QObject* parent = NULL );
    void ReleaseController( );

    void OpenSerialPort( const QString& strCOMx );
    void CloseSerialPort( const QString& strCOMx );

    void SendCmd( const QString &strCOMx, CmdPort eCmd, quint32 nP0, quint32 nP1 = 0,quint32 nP2 = 0 );

private:
    SerialPortController( QObject* parent = NULL );
    ~SerialPortController( );

    static SerialPortController* pController;
    typedef QHash< QString, QThread* > QComThreadHash;
    typedef QHash< QString, Win_QextSerialPort* > QComHash;

    CReceiverThread* ReceiverThread( const QString& strCOMx );
    CSenderThread* SenderThread( const QString& strCOMx );
    Win_QextSerialPort* ComObject( const QString& strCOMx );

    void FreeThread( QComThreadHash& hashThread );
    void FreeComObject( QComHash& hashCom );

    QComThreadHash hashReceiver;
    QComThreadHash hashSender;
    QComHash hashCom;

signals:
    void Log( QString strLog, bool bStatic );

public slots:

private slots:
    void HandleLog( QString strLog, bool bStatic );
};

#endif // SERIALPORTCONTROLLER_H
