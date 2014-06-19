#ifndef QNETWORKLIBRARY_H
#define QNETWORKLIBRARY_H

#include "../CommonLibrary/qcommonlibrary.h"
#include "NetworkLibrary_global.h"
#include <QtNetwork>
#include "qmytcpserver.h"
#include "qtcppeersocket.h"
#include "qtcpclientsocket.h"

class NETWORKLIBRARYSHARED_EXPORT QNetworkLibrary : public QObject
{
    Q_OBJECT
public:
    QNetworkLibrary( QObject* parent = 0 );
    ~QNetworkLibrary( );

    bool StartServerListen( QString& strInfo );
    void StoptServerListen( QString& strInfo );

    QTcpSocket* Connect2Host( quint32 nIP, quint16 nPort );
    void Disconnect2Hots( QTcpSocket* pSocket );
    quint64 SocketSendData( QTcpSocket* pSocket, QByteArray& byData );

    QTcpSocket* ProcessServerAttachSocketEvent( QCommonLibrary::EventParam& uParam );
    void PeerSocketDisconnectQueueChange( QTcpSocket* pSocket );

private:
    typedef QMultiHash< QString, QTcpSocket* > QHostSocketHash;
    typedef QQueue< QTcpSocket* > QSocketQueue;

    void Set2Null( );
    void ConnectLog( QTcpSocket* pSocket, bool bConnected, bool bPeer );
    void DisconnectHashChange( QTcpSocket* pSocket );

    void CreateHash( );
    void CreateQueue( );

    void DestroyHash( QNetworkLibrary::QHostSocketHash* pHash );
    void DestroyQueue( QNetworkLibrary::QSocketQueue* pQueue );

    void RemoveSocketFromQueue( QNetworkLibrary::QSocketQueue* pQueue, QTcpSocket* pSocket );

    void ConnectSocketEvent( QTcpSocket* pSocket );
    void Connect2Server( QTcpSocket* pSocket, bool bManual );
    inline void GetKey( quint32 nIP, quint16 nPort, QString& strKey );

private:
    QHostSocketHash* pConnectedSocketHash;
    QHostSocketHash* pDisconnectedSocketHash; // Client Host--Socket
    QSocketQueue* pAttachedSocketQueue;
    QSocketQueue* pDetachedSocketQueue; //  Server Peer Socket Queue

private:
    QMyTcpServer* pTcpServer;

signals:
    void Accept( qintptr socketDescriptor ); // Listener
    void DataIncoming( void* pSocket, void* pByteArray );
    void PeerDisconenct( QTcpSocket* pSocket ); // Server Socket
    void ErrorInfo( qint32, QString strText );
    void ErrorCode( QTcpSocket* pSocket );
    void ClientReconnect( QTcpSocket* pSocket );
    void ClientDisconnect( QTcpSocket* pSocket );

protected slots:
    void HandleAccept( qintptr socketDescriptor );
    void HandleDataIncoming( void* pSocket, void* pByteArray );
    void HandleConnectFinished( QTcpSocket* pSocket, bool bPeer );
    void HandleDisconnectFinished( QTcpSocket* pSocket, bool bPeer );
    void HandleErrorInfo( qint32 logType, QString strText );
    void HandleErrorCode( QTcpSocket* pSocket );
};

#endif // QNETWORKLIBRARY_H
