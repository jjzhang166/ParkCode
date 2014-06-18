#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include <QThread>
#include "winserialport.h"
#include "serialevent.h"

class CWriteThread : public QThread
{
    Q_OBJECT
public:
    explicit CWriteThread(QObject *parent = 0);
    void SetSerialPort( CWinSerialPort* pPort, int nIndex = 0 );

protected:
    void run( );
    void customEvent( QEvent * e );

private:
    bool WriteData( CWinSerialPort* pWinPort, QByteArray &byData );

private:
    QHash< int, CWinSerialPort* > hashWinPort;
    
signals:
    
public slots:
    
};

#endif // WRITETHREAD_H
