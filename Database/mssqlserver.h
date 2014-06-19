#ifndef MSSQLSERVER_H
#define MSSQLSERVER_H
#include <QObject>
#include <QtSql>
#include <QHash>
#include "bulkinsert.h"

#define  DBS_THREADPOOL_THREAD ( int )( 10 )

class CMsSqlServer : public QObject
{
    Q_OBJECT
public:
    ~CMsSqlServer( );
    static CMsSqlServer& CreateSingleton( );
    static void DestroySingleton( );

    QSqlDatabase* GetHeartbeatDb( );

public:
    bool BulkInsert( QString& strSql, CBulkInsert& bulkInsert );
    bool ExecuteSql( QString& strSql );
    bool ExecuteSql( QString& strSql,  QSqlDatabase* pDb );
    inline bool Open( QSqlDatabase* pDbServer );
    CBulkInsert& GetBulkInsert( );

private:
    CMsSqlServer(QObject *parent = 0);
    void CreateDbPool( int nPoolThread = 10 );
    QSqlDatabase* GetDb( );
    void SendSqlError( QSqlError error );

private:
    QThreadPool* svrThreadPool;
    static CMsSqlServer* pDbServer;
    QHash< int, QSqlDatabase* > dbHash;
    QSettings* pSettings;
    QString strConnection;
     int nPoolThread;

     QSqlDatabase* pDbHeartbeat;

signals:
     void ReportError( QString strMsg );

public slots:

};

#endif // MSSQLSERVER_H
