#ifndef CCOMTHREADEVENT_H
#define CCOMTHREADEVENT_H

#include <QEvent>
#include <QDebug>
#include <QGuiApplication>
#include <QDateTime>
#include "ccomconfigurator.h"

class CComThreadEvent : public QEvent
{
public:

    typedef enum __ThreadType {
        ThreadSender,
        ThreadReceiver,
        ThreadParser
    } ThreadType;

    typedef enum __EventType {
        EventOpenPort = User,
        EventClosePort,
        EventSendData,
        EventParseData
    } EventType;

    static CComThreadEvent* CreateThreadEvent( ThreadType thrType, EventType evtType );

    void SetPortName( const QString& strCOMx );
    const QString& GetPortName( ) const;

    void SetByteArrayData( QByteArray& byData );
    QByteArray& GetByteArrayData( );

    void SetComParkID( QString& strParkID );
    QString& GetComParkID( );

private:
    CComThreadEvent( ThreadType thrType, Type evtType );
    ThreadType typeThread;
    EventType typeEvent;

    QString strCOM;
    QByteArray byByteArrayData;

    QString strComParkID;
};

#endif // CCOMTHREADEVENT_H
