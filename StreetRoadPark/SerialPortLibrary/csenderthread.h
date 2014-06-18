#ifndef CSENDERTHREAD_H
#define CSENDERTHREAD_H

#include <QThread>
#include "ccomthreadevent.h"
#include "qextserialport/win_qextserialport.h"

class CSenderThread : public QThread
{
    Q_OBJECT
public:
    static CSenderThread* CreateThread( Win_QextSerialPort* pPort, QObject* parent = 0 );
    void PostCmd( QByteArray& byCmd );

protected:
    void run( );
    void customEvent( QEvent * pEvent );

private:
    explicit CSenderThread( Win_QextSerialPort* pPort, QObject *parent = 0);
    void Initialize( );

    void ProcessSendDataEvent( QByteArray& byCmd, Win_QextSerialPort* pPort );

    inline void PostEvent( CComThreadEvent* pEvent );
    inline void SendLog( QString& strLog, bool bStatic );

    Win_QextSerialPort* pWinPort;

signals:
    void Log( QString strLog, bool bStatic );
    
signals:
    
public slots:
    
};

#endif // CSENDERTHREAD_H
