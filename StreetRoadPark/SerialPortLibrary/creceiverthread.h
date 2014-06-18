#ifndef CRECEIVERTHREAD_H
#define CRECEIVERTHREAD_H

#include <QThread>
#include "ccomthreadevent.h"
#include "qextserialport/win_qextserialport.h"
#include "cparserthread.h"
#include "ccomconfigurator.h"

class CReceiverThread : public QThread
{
    Q_OBJECT
public:
    static CReceiverThread* CreateThread( Win_QextSerialPort* pPort, QObject* parent = 0 );
    void PostOpenPort( const QString& strCOMx );
    void PostClosePort( const QString& strCOMx );

protected:
    void run( );
    void customEvent( QEvent * pEvent );

private:
    explicit CReceiverThread( Win_QextSerialPort* pPort, QObject *parent = 0);
    void Initialize( );

    inline bool IsOpen( Win_QextSerialPort* pPort );

    void ProcessOpenPortEvent( QString& strCOMx, Win_QextSerialPort* pPort );
    void ProcessClosePortEvent( QString& strCOMx, Win_QextSerialPort* pPort );

    inline void PostEvent( CComThreadEvent* pEvent );

    inline void SendLog( QString& strLog, bool bStatic );

    Win_QextSerialPort* pWinPort;
    CParserThread* pParserThread;
    CComConfigurator* pConfig;
    
signals:
    void Log( QString strLog, bool bStatic );
    
public slots:

private slots:
    void ReceiveData( );
    void HandleLog( QString strLog, bool bStatic );
    
};

#endif // CRECEIVERTHREAD_H
