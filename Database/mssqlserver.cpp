#include "mssqlserver.h"
#include "bulkinsert.h"

#if false
// ODBC
// http://www.unixodbc.org/
QSqlDatabase db = QSqlDatabase::addDatabase( "QODBC" );
db.setDatabaseName( "DRIVER={SQL Server};SERVER=127.0.0.1;UID=hello;PWD=hello;DATABASE=hello;Trusted_Connection=Yes" );
#endif

CMsSqlServer* CMsSqlServer::pDbServer = NULL;

CMsSqlServer::CMsSqlServer(QObject *parent) :
    QObject(parent)
{
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    nPoolThread = pSettings->value( "Database/ConnPoolThread", DBS_THREADPOOL_THREAD ).toInt( );

    svrThreadPool = new QThreadPool( this );
    svrThreadPool->setMaxThreadCount( nPoolThread );
    svrThreadPool->setExpiryTimeout( -1 );

    //Trusted_Connection=Yes;
    strConnection = QString( "DRIVER={SQL Server};SERVER=%1;UID=%2;PWD=%3;DATABASE=%4;" ).arg(
            pSettings->value( "Database/MsServer", "127.0.0.1" ).toString( ),
            pSettings->value( "Database/MsUser", "" ).toString( ),
            pSettings->value( "Database/MsPwd", "" ).toString( ),
            pSettings->value( "Database/MsDatabase", "" ).toString( ) );

    CreateDbPool( nPoolThread );
}

CMsSqlServer::~CMsSqlServer( )
{
    if ( NULL != svrThreadPool ) {
        delete svrThreadPool;
    }

    for ( int nIndex = 0; nIndex < dbHash.count( ); nIndex++ ) {
        QSqlDatabase* pDb  = dbHash.value( nIndex );
        if ( NULL == pDb ) {
            continue;
        }

        if ( pDb->isOpen( ) ) {
            pDb->close( );
        }

        delete pDb;
    }
}

void CMsSqlServer::CreateDbPool( int nPoolThread )
{
    for ( int nIndex = 0; nIndex < nPoolThread + 1; nIndex++ ) {
        QString strConnName = "PMS Sql Server%1";
        QSqlDatabase db = QSqlDatabase::addDatabase( "QODBC",  strConnName.arg( nIndex ) );
        db.setDatabaseName( strConnection );

        QSqlDatabase* pDb = new QSqlDatabase( db );
        //SQL_CP_OFF 0/ SQL_CP_ONE_PER_DRIVER 1/ SQL_CP_ONE_PER_HENV 2/ SQL_CP_DRIVER_AWARE
        pDb->setConnectOptions( "SQL_ATTR_CONNECTION_POOLING=SQL_CP_ONE_PER_HENV;" );

        if ( nIndex != nPoolThread ) {
            dbHash.insert( nIndex, pDb );
        } else {
            pDbHeartbeat = pDb;
        }
    }
}

QSqlDatabase* CMsSqlServer::GetHeartbeatDb( )
{
    return pDbHeartbeat;
}

CMsSqlServer& CMsSqlServer::CreateSingleton( )
{
    if ( NULL == pDbServer ) {
        pDbServer = new CMsSqlServer( );
    }

    return *pDbServer;
}

void CMsSqlServer::DestroySingleton( )
{
    if ( NULL != pDbServer ) {
        delete pDbServer;
        pDbServer = NULL;
    }
}

CBulkInsert& CMsSqlServer::GetBulkInsert( )
{
    return *CBulkInsert::GetInstance( );
}

bool CMsSqlServer::Open( QSqlDatabase* pDbServer )
{
    bool bRet = true;

    if ( !pDbServer->isOpen( ) ) {
        bRet = pDbServer->open( );
        if ( !bRet ) {
            SendSqlError( pDbServer->lastError( ) );
            return bRet;
        }
    }

    return bRet;
}

void CMsSqlServer::SendSqlError( QSqlError error )
{
    if ( QSqlError::NoError == error.type( ) ) {
        return;
    }

    QString strDriverError = error.driverText( );
    QString strDbError = error.databaseText( );

    QString strSpace = " ";
    QString strError = "";

    if ( strSpace != strDriverError ) {
        strError = strDriverError;
    }

    if ( strSpace != strDbError ) {
        strError += strSpace + strDbError;
    }

    if ( !strError.isEmpty( ) && strSpace != strError ) {
        g_pLocalCltComm->SendData( strError );
    }

#ifndef QT_NO_DEBUG
    qDebug( ) << "CMsSqlServer:" << strError << endl;
#endif
}

bool CMsSqlServer::ExecuteSql( QString &strSql, QSqlDatabase *pDb )
{
    bool bRet = false;
    if ( NULL == pDb ) {
        return bRet;
    }

    if ( !Open( pDb ) ) {
        return false;
    }

    QSqlQuery query = pDb->exec( );
    bRet = query.exec( strSql );

    SendSqlError( query.lastError( ) );

    if ( QSqlError::ConnectionError == query.lastError( ).type( ) ) {
        pDb->close( );
    }

    return bRet;
}

bool CMsSqlServer::ExecuteSql( QString &strSql )
{
    bool bRet = false;
    QSqlDatabase* pDb = GetDb( );

    bRet = ExecuteSql( strSql, pDb );

    return bRet;
}

QSqlDatabase* CMsSqlServer::GetDb( )
{
    QSqlDatabase* pDb = NULL;
    static int nIndex = 0;

    if ( dbHash.count( ) <= nIndex ) {
        nIndex = 0;
    }

    pDb = dbHash.value( nIndex++ );

    return pDb;
}

bool CMsSqlServer::BulkInsert( QString &strSql, CBulkInsert& bulkInsert )
{
    bool bRet = false;
    QSqlDatabase* pDb = GetDb( );
    if ( NULL == pDb ) {
        return bRet;
    }

    bulkInsert.SetDbParams( pDb, strSql );
    svrThreadPool->start( &bulkInsert );

    return true;
}
