#ifndef MGMTTHREAD_H
#define MGMTTHREAD_H

#include <QThread>
#include "getconfig.h"
#include "DataType.h"

#include "Network/tcpclient.h"
#include "Network/tcpdispatcher.h"

class CMgmtThread : public QThread
{
    Q_OBJECT
public:
    explicit CMgmtThread( bool bSender, QObject *parent = 0 );
    static CMgmtThread* GetThread( bool bSender );

    void PeerRequest( QUdpSocket* pUdpSocket );

protected:
    void run( );
    void timerEvent ( QTimerEvent * event );
    void customEvent( QEvent * event );

private:
    void ClientRun( );
    void ServerRun( );
    bool SendTableData( QString& strFile, const QString& strTable );
    //void PeerRequest( );
    void SendPeerRequest( QStringList& lstRows, const QString& strTable );
    void UdpSendPeerRequest( QUdpSocket* pUdpSocket, QStringList& lstRows, const QString& strTable );
    void SendTableData( bool bRequest, QString& strWhere, QString& strTableName );
    inline quint32 GetCommonHeaderSize( );
    inline Mgmt::CommonHeader& GetCommonHeader( const char* pData );
    inline quint32 GetContentHeaderSize( );
    inline Mgmt::ContentHeader& GetContentHeader( const char* pData );
    inline const char* GetBody( const char* pData );
    void GetStopRdWhere( QString& strWhere );
    inline void GetFeeRdWhere( QString& strWhere );
    void UpdateStopRdTransferFlag( QString& strWhere );
    void UpdateFeeRdTransferFlag(  );

    CPeerSocket* GetPeerSocket( const QString& strKey );
    bool SendFilterData( CPeerSocket* pPeer, QString& strWhere, const QString& strTable );
    bool SendFilterData( QUdpSocket* pUdpSocket, QString& strWhere, const QString& strTable, const QString& strIP );

    void SetPacketType( Mgmt::CommonHeader& sHeader, Mgmt::ePacketType eType );
    Mgmt::ePacketType GetPacketType( Mgmt::CommonHeader& sHeader );
    bool ConnectMySQL( );

    void ProcessRequest( const char* pData );
    void ProcessTableRequest( const char* pData );
    void ProcessHandshakeRequest( const char* pData );

private:
    CGetConfig config;
    int nInterval;
    int nClientTimer;
    int nServerTimer;
    QString strPath;

    CMySqlDatabase* pMySQL;
    CTcpClient* pTcpClient;
    CTcpDispatcher* pTcpServer;
    QTextCodec* pTxtCodec;
    bool bClient;

    QUdpSocket* pUdpClient;
    QUdpSocket* pUdpServer;

    static CMgmtThread* pSenderThread;
    static CMgmtThread* pReceiverThread;
    
signals:
    
public slots:
    void ThreadExit( );
    void NotifyMsg( QString strMsg );
    void PeerData( );
    void UdpPeerData( );
};

#endif // MGMTTHREAD_H
