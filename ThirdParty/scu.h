#ifndef SCU_H
#define SCU_H

#include <QObject>
#include "Network/udpclient.h"
#include "Common/commonfunction.h"
#include "../Network/http.h"

class CScu : public QObject
{
    Q_OBJECT
public:
    explicit CScu(QObject *parent = 0);

    void InteractWithScu( QStringList& lstData );

private:
    void ContructDatagram( QStringList& lstData );
    void SendDatagram( );
    void HttpSendData( QStringList& lstData );

private:
    CUdpClient udpClient;
    QByteArray bySendData;
    QBuffer byBuffer;
    QSettings* pSystemSet;
    QTextCodec* pTxtCodec;
    CHttp http;
    
signals:
    
public slots:
    
};

#endif // SCU_H
