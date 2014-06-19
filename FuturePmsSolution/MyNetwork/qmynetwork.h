#ifndef QMYNETWORK_H
#define QMYNETWORK_H

#include "QMyNetwork_global.h"

#include "qmytcpserver.h"
#include "qtcpclient.h"
#include "qtcppeerclient.h"
#include "qudpclient.h"
#include "qudpserver.h"

#include "../ManipulateIniFile/qmanipulateinifile.h"

class QMYNETWORKSHARED_EXPORT QMyNetwork :public QObject
{
    Q_OBJECT
public:
    explicit QMyNetwork( QObject* parent = 0 );
    virtual ~QMyNetwork( );

    //
    // TCP
    //

    void StartupTcpServer( quint16 nPort, int nMaxConnections );
    QTcpPeerClient* GenerateTcpPeerSocket( QTextCodec* pCodec );
    QTcpClient* GenerateTcpClientSocket( QTextCodec* pCodec );

    bool TcpConnect2Server( QTcpClient* pTcpClient, const QHostAddress &hostAddr, quint16 nPort );
    quint64 TcpSendData( QMyTcpSocket* pTcpSocket,  const char * data, qint64 maxSize );
    quint64 TcpSendData( QMyTcpSocket* pTcpSocket,  const QByteArray & byteArray );
    quint64 TcpReceiveData( QMyTcpSocket* pTcpSocket,  char* data, qint64 maxSize );
    QByteArray TcpReceiveData( QMyTcpSocket* pTcpSocket,  qint64 maxSize );
    QByteArray TcpReceiveData( QMyTcpSocket* pTcpSocket );

    //
    // UDP
    //

    QUdpClient* GenerateUdpClientSocket( QTextCodec* pCodec );
    QUdpServer* GenerateUdpServerSocket( QTextCodec* pCodec );

    quint64 UdpBroadcastDatagram( QMyUdpSocket* pUdpSocket, const QByteArray& byteData, const quint16 targetPort );
    bool StartupUdpListening( QMyUdpSocket* pUdpSocket, const quint16 nPort );
    bool UdpOperateMulticast( QMyUdpSocket* pUdpSocket, const QHostAddress& groupAddress, const bool bJoined );
    quint64 UdpSendDatagram( QMyUdpSocket* pUdpSocket, const QByteArray& byteData, const QHostAddress& targetAddress, const quint16 targetPort );

private:
    QMyTcpServer* pTcpServer;

signals:
    void NotifyMessage( void* pstrMsg, QManipulateIniFile::LogTypes type );
    void Accept( int socketDescriptor );
    void EnqueueThread( QTcpSocket* pPeerSocket );
    void GetWholeTcpStreamData( QTcpSocket* pPeerSocket, void* pByteArray );
    void GetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort );

public slots:

private slots:
    void HandleMessage( void* pstrMsg, QManipulateIniFile::LogTypes type );
    void HandleAccept( int socketDescriptor );
    void HandleThreadEnqueue( QTcpSocket* pPeerSocket );
    void HandleGetWholeTcpStreamData( QTcpSocket* pPeerSocket, void* pByteArray );
    void HandleGetWholeUdpDatagram( void* pByteArray, QString strSenderIP, quint16 nSenderPort );
};

#endif // QMYNETWORK_H
