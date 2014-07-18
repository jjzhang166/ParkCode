#ifndef READTHREAD_H
#define READTHREAD_H

#include <QThread>
#include "winserialport.h"
#include "portcmd.h"
#include <windows.h>

class CReadThread : public QThread
{
    Q_OBJECT
public:
    static CReadThread* CreateInstance( CWinSerialPort* pSerial );
    HANDLE GetEventObject( bool bEnter );

protected:
    void run( );
    void customEvent( QEvent* e );

private:
    explicit CReadThread(CWinSerialPort* pSerial, QObject *parent = 0);
    void InitializeThread( );
    void ParseData( QByteArray& byData );
    void ProcessCmd( QByteArray &byData, CPortCmd::PortUpCmd cmdType );
    void GateSense( bool bEnterGate, bool bLeavePark );

    static CReadThread* pThreadInstance;
    CWinSerialPort* pWinSerial;
    CPortCmd portCmd;

    HANDLE hInOutEvent[ 2 ];
    
signals:
    void SerialData( QByteArray byData );
    
private slots:
    void DataMayRead( );
    
};

#endif // READTHREAD_H
