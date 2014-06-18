#ifndef QDBTHREADEVENT_H
#define QDBTHREADEVENT_H

#include <QEvent>
#include <QGuiApplication>
#include <QDebug>
#include <QByteArray>
#include <QTcpSocket>
#include "cdbconfigurator.h"

class QDbThreadEvent : public QEvent
{
public:
    ~QDbThreadEvent( );
    typedef enum __ThreadType {
        ThreadDispatcher,
        ThreadDbProcessor
    } ThreadType;

    typedef enum __EventType {
        EventDispatchData = User, // ThreadDispatcher

        EventConnectDb,
        EventProcessComPortData,
        EventProcessDbData // ThreadDbProcessor
    } EventType;

    static QDbThreadEvent* CreateThreadEvent( ThreadType thrType, EventType evtType );

    void SetByteArray( QByteArray& byData );
    QByteArray& GetByteArray( );

    void SetDataPackageType( qint32 nType );
    qint32 GetDataPackageType( );

    void SetPeerSocket( QTcpSocket* pSocket );
    QTcpSocket* GetPeerSocket( );

    void SetComParkID( QString& strParkID );
    QString& GetComParkID( );

    void SetReconnect( bool bReconn );
    bool GetReconnect( );

private:
    QDbThreadEvent( ThreadType thrType, Type evtType );
    ThreadType typeThread;
    EventType typeEvent;

    QByteArray byByteArray;
    qint32 nDataPackageType;
    QString strComParkID;

    QTcpSocket* pPeerSocket;
    bool bReconnect;
};

#endif // QDBTHREADEVENT_H
