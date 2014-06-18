#ifndef QDBDATAPROCESS_H
#define QDBDATAPROCESS_H

#include <QObject>
#include "Database/mysqldatabase.h"
#include <QTcpSocket>
#include <QHostAddress>
#include "qjson2sqlparser.h"
#include "cdbconfigurator.h"

class QDbDataProcess : public QObject
{
    Q_OBJECT
public:
    explicit QDbDataProcess(QObject *parent = 0);
    void SetDatabase( CMySqlDatabase* pDb );
    void SetPeerSocket( QTcpSocket* pSocket );
    void SetNetController( QObject* pController );

    void ProcessSocketData( qint32 nPackageType, QByteArray& byJson );
    void ProcessComPortData( qint32 nPackageType, QByteArray& byData, QString& strParkID );

private:
    // Response Unicast Multicast Broadcast
    // MAC FF:FF:FF:FF:FF:FF 01:
    // Router IP / Switch Link / Hub Physical
    void PostData2PeerThread( QTcpSocket* pSocket, QByteArray& byData, int nPkType );
    inline void SendLog( QString& strLog, bool bStatic );
    inline QString GetDateTime( );
    void CallSP( QByteArray& byData, JsonStruct::JsonHead& sHead, int nPkType );
    void FeedbackData( JsonStruct::JsonHead& sHead, QString& strMessage, qint32 nPackageType, bool bSuccess );
    void PrintPackageType( qint32 nPackageType );
    inline void DetectorID2LocationID( QString& strDetectorID );
private:
    CMySqlDatabase* pDatabase;
    QTcpSocket* pPeerSocket;
    QJson2SqlParser parserJson2Sql;
    QObject* pNetController;
    CDbConfigurator* pConfig;
    
signals:
    void Log( QString strLog, bool bStatic );
    
public slots:
    
};

#endif // QDBDATAPROCESS_H
