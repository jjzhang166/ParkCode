#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include "netcommfunction.h"
#include <QTextCodec>
#include "ping.h"

class CTcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CTcpClient(QObject *parent = 0);
    ~CTcpClient( );

    bool Connect2Server( const QHostAddress& hostAddr, quint16 nPort );
    void SetTextCodec( QTextCodec* pCodec );

    quint64 SendData( const char * data, qint64 maxSize );
    quint64 SendData( const QByteArray & byteArray );

    quint64 ReceiveData( char* data, qint64 maxSize );
    QByteArray ReceiveData( qint64 maxSize );
    QByteArray ReceiveData(  );


    ////////////////////// Mgmt
    QByteArray* GetData( );
    void SetMaxDataSize( quint64 nSize  );
    quint64 GetMaxDataSize( );
    void Clear( );

    void SetCurrentDataSize( quint64 nSize  );
    quint64 GetCurrentDataSize( );

private:
    QByteArray* pData;
    quint64 nDataLen;
    quint64 nCurrentLen;
    CPing ping;
    ////////////////////// Mgmt

private:
    QHostAddress svrAddr;
    quint16 nSvrPort;
    QTextCodec* pTextCodec;

signals:
    void NotifyMessage( QString );

public slots:
    void HandleDisconnect( );
    void TcpError( QAbstractSocket::SocketError socketError );

};

#endif // TCPCLIENT_H
