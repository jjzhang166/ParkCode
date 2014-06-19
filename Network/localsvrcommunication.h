#ifndef LOCALCOMMUNICATION_H
#define LOCALCOMMUNICATION_H

#include <QObject>
#include <QtNetwork>
#include <QHash>

#define LOCAL_COMM_NAME     "localcomm"
class CLocalSvrCommunication : public QObject
{
    Q_OBJECT
public:
    static CLocalSvrCommunication* GetInstance( QTextCodec* pCodec = 0, QObject *parent = 0 );
    static void ReleaseInstance( );

    void StartupServer(  );

private:
    CLocalSvrCommunication( QTextCodec* pCodec, QObject *parent = 0 );
    ~CLocalSvrCommunication( );

private:
    QLocalServer localServer;
    QTextCodec* pTextCodec;
    static CLocalSvrCommunication* pLocalComm;

signals:
    void NotifyMsg( QString strMsg );

private slots:
    void GetData( );
    void AcceptConnection( );
    void HandleServerDisconnect( );
    void SocketError( QLocalSocket::LocalSocketError );
};

#endif // LOCALCOMMUNICATION_H
