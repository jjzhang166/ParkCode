#include "Database/mysqldatabase.h"
#include <QDebug>
#include <QTextCodec>
#include <QFile>
#include "Common/commonfunction.h"
CMySqlDatabase::CMySqlDatabase(QObject *parent) :
    QObject(parent)
{
    //mysql_library_init( );
    mysql_init( &hConnect );
    my_bool bReconnect = 1;
    mysql_options( &hConnect, MYSQL_OPT_RECONNECT, &bReconnect );
    pCodec = CCommonFunction::GetTextCodec( );
    hStmt = NULL;
}

bool CMySqlDatabase::PingMysql( )
{
    return ( 0 ==  mysql_ping( &hConnect ) );
}

bool CMySqlDatabase::DbConnect( QString strHost, QString strUser, QString strPwd, QString strDB, quint32 nPort )
{
    MYSQL* hConn = mysql_real_connect( &hConnect, strHost.toStdString( ).c_str( ),
                                        strUser.toStdString( ).c_str( ),
                                        strPwd.toStdString( ).c_str( ),
                                        strDB.toStdString( ).c_str( ),
                                        nPort, NULL, CLIENT_MULTI_STATEMENTS );

    //
    // Set Client endpoit character set
    //
    if ( NULL != hConn ) {
        mysql_set_character_set( &hConnect, "GBK" );
    }
    //int nRet = mysql_query( &hConnect, "SET NAMES 'GBK'" );
    QString strError;
    GetErrorMsg( 0, strError, true, strError );

    return ( NULL != hConn );
}

void CMySqlDatabase::GetErrorMsg( int nErrorCode, QString &strError, bool bMysql, QString& strSql )
{
    switch ( nErrorCode ) {
    case CR_COMMANDS_OUT_OF_SYNC :
        strError = tr( "以不恰当的顺序执行了命令。" );
        break;

    case CR_SERVER_GONE_ERROR :
        strError = tr( "MySQL服务器不可用。" );
        break;

    case CR_OUT_OF_MEMORY :
        strError = tr( "内存溢出。" );
        break;

    case CR_SERVER_LOST :
        strError = tr( "在查询过程中，与服务器的连接丢失。" );
        break;

    case CR_UNKNOWN_ERROR :
        strError = tr( "出现未知错误。" );
        break;

    default :
            strError = bMysql ? mysql_error( &hConnect ) : mysql_stmt_error( hStmt );
        break;
    }

    qDebug( ) << strSql << endl;
    qDebug( ) << strError << endl;
}

bool CMySqlDatabase::DbCrud( QString& strSql, QString& strError )
{
    //
    // Unicode(UCS) =====> MBCS
    //

    QByteArray byteSql = pCodec->fromUnicode( strSql );

    int nSize = byteSql.count( );
    const char* pSql = byteSql.data( );

    int nRet = mysql_real_query( &hConnect, pSql, nSize );
    GetErrorMsg( nRet, strError, true, strSql );

    //mysql_num_rows();

    return ( 0 == nRet );
}

quint64 CMySqlDatabase::GetRowData( QStringList& lstRows, QString& strError  )
{
    lstRows.clear( );
    MYSQL_RES* pRowSet = mysql_store_result( &hConnect );

    if ( NULL == pRowSet ) {
        GetErrorMsg( 0, strError, true, strError );
        return 0;
    }

    my_ulonglong nRows = mysql_num_rows( pRowSet ); // Row
    unsigned int nFields = mysql_num_fields( pRowSet ); //Column
    // mysql_fetch_lengths( ) field length

    MYSQL_ROW row = NULL;
    while ( NULL != ( row = mysql_fetch_row( pRowSet) ) ) {
        for ( unsigned int nIndex = 0; nIndex < nFields; nIndex++ ){
            qDebug( ) << row[ nIndex ] << endl;
           lstRows << row[ nIndex ];
        }
    }

    mysql_free_result( pRowSet );

    return nRows;
}

void CMySqlDatabase::DbDisconnect( )
{
    mysql_close( &hConnect );
}

CMySqlDatabase::~CMySqlDatabase( )
{
    DbDisconnect( );
    //mysql_library_end( );
}

bool CMySqlDatabase::BlobReadDb( QString &strBlobFile, QString& strSql, QString& strError )
{
    //http://www.cplusplus.com
    QFile file( strBlobFile );
    bool bRet = file.open( QIODevice::WriteOnly );
    if ( !bRet ) {
        return bRet;
    }

    MYSQL_BIND bind[ 1 ];
    ulong       length = 0;
    QByteArray byteSql;
    int nSize = 0;
    const char* pSql = NULL;
    char* bufData = NULL;
    quint32 nData = 1024 * 1024 * 2;
    int nRet = 0;
    MYSQL_RES* res = NULL;
    my_bool bGetMaxLen = 1;

    hStmt = mysql_stmt_init( &hConnect );
    bRet = ( NULL != hStmt );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql );
        goto FileHandle;
    }

    byteSql = pCodec->fromUnicode( strSql );
    nSize = byteSql.count( );
    pSql = byteSql.data( );

    bRet = ( 0 == mysql_stmt_prepare( hStmt, pSql, nSize ) );
    if ( !bRet ){
        GetErrorMsg( 0, strError, false, strSql );
        goto StmtHandle;
    }

    bRet = ( 0 == mysql_stmt_execute( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql );
        goto StmtHandle;
    }

    // max_allowed_packet 16M
    // write_timeout 120
    // Net Buffer 16M
    bufData = ( char* ) malloc( nData );
    memset( bind, 0, sizeof ( bind ) );
    bind[ 0 ].buffer_type = MYSQL_TYPE_LONG_BLOB;
    bind[ 0 ].length = &length; // Return Real Data Length
    bind[ 0 ].is_null = 0; /* Bind the buffers */
    bind[ 0 ].buffer = bufData; // Bind data buffer
    bind[ 0 ].buffer_length = nData; // Buffer Length

    bRet = ( 0 == mysql_stmt_bind_result( hStmt, bind ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql );
        goto NewHandle;
    }

    bRet = ( 0 == mysql_stmt_attr_set( hStmt, STMT_ATTR_UPDATE_MAX_LENGTH, &bGetMaxLen ) );
    bRet = ( 0 == mysql_stmt_store_result( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql );
        goto NewHandle;
    }

    /////////////////////////////////// Get Meta Data
    res = mysql_stmt_result_metadata( hStmt );
    if ( NULL != res && 0 < res->field_count &&
        nData < res->fields[ 0 ].max_length ) {
        nData = res->fields[ 0 ].max_length; // Data Real Length
        mysql_free_result( res );

        bind[ 0 ].buffer_length = nData;
        bufData = ( char* ) realloc( bufData, nData );
        bind[ 0 ].buffer = bufData;
        bRet = ( 0 == mysql_stmt_bind_result( hStmt, bind ) );
        if ( !bRet ) {
            GetErrorMsg( 0, strError, false, strSql );
            goto NewHandle;
        }
    }
    ///////////////////////////////////

    nRet = mysql_stmt_fetch( hStmt );
    if ( MYSQL_DATA_TRUNCATED == nRet ) {
        ;
    } else {
        bRet = ( 0 == nRet );
        if ( !bRet ) {
            GetErrorMsg( 0, strError, false, strSql );
            goto NewHandle;
        }
    }

    file.write( ( const char* ) bufData, length );

    NewHandle:
    if ( NULL != bufData ) {
        free( bufData );
    }

    bRet = ( 0  == mysql_stmt_free_result( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql );
    }

    StmtHandle:
    bRet = ( 0 == mysql_stmt_close( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql );
    }

    FileHandle:
    file.close( );

    return bRet;
}

bool CMySqlDatabase::BlobWriteDb( QString &strBlobFile, QString& strSql, QString& strError )
{
    QFile file( strBlobFile );
    bool bRet = false;
    QByteArray byteSql;
    int nSize = 0;
    int nRet = 0;
    const char* pSql = NULL;

    if ( !file.exists( ) ) {
        return bRet;
    }

    bRet = file.open( QIODevice::ReadOnly );
    if ( !bRet ) {
        return bRet;
    }

    MYSQL_BIND bind[ 1 ];
    ulong       length = 0;

    hStmt = mysql_stmt_init( &hConnect );
    bRet = ( NULL != hStmt );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql );
        goto FileHandle;
    }

    byteSql = pCodec->fromUnicode( strSql );
    nSize = byteSql.count( );
    pSql = byteSql.data( );
    nRet = mysql_stmt_prepare( hStmt, pSql, nSize );
    bRet = ( 0 == nRet );
    if ( !bRet ){
        GetErrorMsg( nRet, strError, false, strSql );
        goto StmtHandle;
    }

    memset( bind, 0, sizeof ( bind ) );
    bind[ 0 ].buffer_type = MYSQL_TYPE_LONG_BLOB;
    bind[ 0 ].length = &length;
    bind[ 0 ].is_null = 0; /* Bind the buffers */
    //bind[ 0 ].buffer
    //bind[ 0 ].buffer_length

    bRet = ( 0 == mysql_stmt_bind_param( hStmt, bind ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql );
        goto StmtHandle;
    }

    byteSql = file.readAll( );
    nSize = byteSql.count( );
    pSql = byteSql.data( );
    if ( 0 < nSize ) {
        nRet = mysql_stmt_send_long_data( hStmt, 0, pSql, nSize );
        bRet = ( 0 == nRet );
        if ( !bRet ) {
            GetErrorMsg( nRet, strError, false, strSql );
            goto StmtHandle;
        }
    }

    nRet = mysql_stmt_execute( hStmt );
    bRet = ( 0 == nRet );
    if ( !bRet ) {
        GetErrorMsg( nRet, strError, false, strSql );
    }

    StmtHandle:
    bRet = ( 0 == mysql_stmt_close( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql );
    }

    FileHandle:
    file.close( );

    return bRet;
}
