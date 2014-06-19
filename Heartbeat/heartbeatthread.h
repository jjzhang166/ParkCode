#ifndef HEARTBEATTHREAD_H
#define HEARTBEATTHREAD_H

#include <QThread>
#ifdef PARKDATARECEIVER_APP
#include "../Network/netclient.h"
#else
#include "Network/netclient.h"
#endif
#include "hbevent.h"

class CHeartbeatThread : public QThread
{
    Q_OBJECT
public:
    static CHeartbeatThread& GetInstance( QObject* parent = 0 );

private:
    CHeartbeatThread(QObject *parent = 0);
    ~CHeartbeatThread( );

protected:
    void run( );
    void customEvent( QEvent * e );
    void timerEvent( QTimerEvent * e );

private:
    void GetLiveNetworkInterfaceIP( );
    void SyncIP( QString& strIP );
    void SyncNetState( );
    void GetImgRequest( );

private:
    QSettings* pSettings;
    QString strParkID;
    QString strClientServerPort;
    QString strHostIP;
    QString strCenterIP;
    CNetClient* udpClient;
    CNetClient* tcpClient;
    int nIPTimerID;
    int nNetStateTimerID;
    int nImgRequestTimerID;
    QTextCodec* pTextCodec;

signals:

private slots:
    void ExitThread( );

};

#endif // HEARTBEATTHREAD_H
