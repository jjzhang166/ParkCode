#ifndef LOCALCLTCOMMUNICATION_H
#define LOCALCLTCOMMUNICATION_H

#include <QObject>
#include <QtNetwork>

#define LOCAL_COMM_NAME     "localcomm"

class CLocalCltCommunication : public QObject
{
    Q_OBJECT
public:
    explicit CLocalCltCommunication( QTextCodec* pCodec, QObject *parent = 0 );
    ~CLocalCltCommunication( );

    void Connect2Server( );
    void SendData( QString& strMsg );
    void Disconnect2Server( );

private:
    QLocalSocket clientSocket;
    QTextCodec* pTextCodec;

signals:
    void NotifyMsg( QString strMsg );

private slots:
    void HandleClientDisconnect( );
    void SocketError( QLocalSocket::LocalSocketError );

};

#endif // LOCALCLTCOMMUNICATION_H
