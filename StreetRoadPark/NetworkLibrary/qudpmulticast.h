#ifndef QUDPMULTICAST_H
#define QUDPMULTICAST_H

#include <QUdpSocket>
#include "cnetconfigurator.h"
#include <QHostAddress>
#include "qthreadevent.h"

class QUdpMulticast : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QUdpMulticast(QObject *parent = 0);

    void MulticastData( QString& strJson, qint32 nMulticastType );
    void MulticastData( QByteArray& byJson, qint32 nMulticastType  );

private:
    QString strMultiIP;
    quint16 nMulticastPort;
    CNetConfigurator* pConfig;
    QTextCodec* pCodec;
    QHostAddress multiIP;
    QByteArray byTokenData;
    
signals:
    
public slots:
    
};

#endif // QUDPMULTICAST_H
