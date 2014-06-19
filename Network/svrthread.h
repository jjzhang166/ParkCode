#ifndef SVRTHREAD_H
#define SVRTHREAD_H

#include <QThread>
#include "udpdispatcher.h"
#include "tcpdispatcher.h"

class CSvrThread : public QThread
{
    Q_OBJECT
public:
    static CSvrThread* GetInstance( QObject *parent = 0 );
    bool StartupUdpServer( bool bServerEnd );
    bool StartupTcpServer( bool bServerEnd );

protected:
    void run( );

private:
    quint16 GetPort( bool bServerEnd, bool bTcp );
    quint16 GetThreadPoolCount( bool bServerEnd, bool bTcp );
    quint16 GetMaxPendingCount( bool bServerEnd );

private:
    CSvrThread( QObject *parent = 0 );
    CUdpDispatcher* udpServer[ SERVER_INSTANCE ];
    CTcpDispatcher* tcpServer[ SERVER_INSTANCE ];
    QSettings* pSettings;

signals:
    void Notify( QString strMsg );

private slots:
    void NotifyMessage( QString strMsg );
};

#endif // SVRTHREAD_H
