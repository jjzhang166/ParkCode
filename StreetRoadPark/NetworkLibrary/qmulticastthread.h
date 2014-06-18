#ifndef QMULTICASTTHREAD_H
#define QMULTICASTTHREAD_H

#include "qthreadevent.h"
#include <QThread>
#include "qudpmulticast.h"

class QMulticastThread : public QThread
{
    Q_OBJECT
public:
    static QMulticastThread* CreateThread( QObject *pParent = NULL );

    void PostUDPMultiDataEvent( QByteArray& byUdpData, qint32 nPackageType );

    ~QMulticastThread( );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );
    void timerEvent( QTimerEvent *event );

private:
    inline void PostEvent( QThreadEvent* pEvent );
    void ProcessMultiDataEvent( QThreadEvent* pEvent );

    void PrintIntervalTime( );

private:
    QMulticastThread(QObject *parent = 0);

    inline void SendLog( QString& strLog, bool bStatic );

private:
    QUdpMulticast* pMulticast;
    CNetConfigurator* pConfig;
    qint32 nTimeSyncTimerID;
    qint32 nTimeSyncInterval;
    QString strTimeSyncJson;

signals:
    void Log( QString strLog, bool bStatic );

public slots:

private slots:
    
};

#endif // QMULTICASTTHREAD_H
