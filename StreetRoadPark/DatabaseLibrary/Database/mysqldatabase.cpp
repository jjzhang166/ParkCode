
#include "mysqldatabase.h"
#include "../cdbconfigurator.h"
//
// 单(多)版本 单(多)实例 实例独占(共享)库
//
// Oracle MySQL(InnoDB) PostgreSQL
// MVCC Multiversion Concurrency Control( Snapshot )
//

CMySqlDatabase::CMySqlDatabase(QObject *parent) :
    QObject(parent)
{
    //mysql_library_init( );
    mysql_init( &hConnect );
    mysql_error( &hConnect );
    my_bool bReconnect = 1;
    mysql_options( &hConnect, MYSQL_OPT_RECONNECT, &bReconnect );
    pCodec = CDbConfigurator::GetConfigurator( )->GetTextCodec( );
    bReconnect = mysql_thread_safe( );
    hStmt = NULL;
    bFirstConnect = true;
}

void CMySqlDatabase::SetFirstConnect( bool bFirst )
{
    if ( !bFirstConnect ) {
        DbDisconnect( );
    }

    bFirstConnect = bFirst;
}

int CMySqlDatabase::MySQLLibraryInit( int argc, char *argv[] )
{
    char** groups = NULL;

    return mysql_library_init( argc, argv, groups );
}

void CMySqlDatabase::MySQLLibraryEnd( )
{
    mysql_library_end( );
}

bool CMySqlDatabase::GetFirstConnect( )
{
    return bFirstConnect;
}

ulong CMySqlDatabase::GetThreadID( )
{
    return mysql_thread_id( &hConnect );
}

bool CMySqlDatabase::PingMysql( )
{
    bool bRet = true;
    bRet = ( 0 ==  mysql_ping( &hConnect ) );

    return bRet;
}

bool CMySqlDatabase::DbConnect( const QString& strHost, const QString& strUser,
                                const QString& strPwd, const QString& strDB,
                                quint32 nPort )
{
    MYSQL* hConn = mysql_real_connect( &hConnect, strHost.toStdString( ).c_str( ),
                                        strUser.toStdString( ).c_str( ),
                                        strPwd.toStdString( ).c_str( ),
                                        strDB.toStdString( ).c_str( ),
                                        nPort, NULL, CLIENT_MULTI_STATEMENTS );

    bFirstConnect = false;

    //
    // Set Client endpoit character set
    //
    if ( NULL != hConn ) {
        mysql_set_character_set( &hConnect, "UTF8" );
    }
    //int nRet = mysql_query( &hConnect, "SET NAMES 'GBK'" );
    QString strError;
    GetErrorMsg( 0, strError, true, strError, "mysql_real_connect" );

    return ( NULL != hConn );
}

void CMySqlDatabase::GetErrorMsg( int nErrorCode,
                                  QString &strError,
                                  bool bMysql,
                                  QString& strSql,
                                  QString  strFunName )
{
    qint32 nCode = 0;

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
            nCode = bMysql ? mysql_errno( &hConnect ) : mysql_stmt_errno( hStmt );
        break;
    }

    //emit NotifyError( strSql, false );

    if ( !strError.isEmpty( ) ) {
        qDebug( ) << Q_FUNC_INFO << strError << endl;
        emit NotifyError( objectName( ) + ":" + strError + ":" + strFunName + " Error code:" + QString::number( nCode ), true );
    }
    //qDebug( ) << strSql << endl;
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
    GetErrorMsg( nRet, strError, true, strSql, "mysql_real_query" );

    //mysql_num_rows();

    bool bRet = ( 0 == nRet );

    return bRet;
}

quint64 CMySqlDatabase::GetRowData( QStringList& lstRows, QString& strError  )
{
    lstRows.clear( );
    my_ulonglong nRows = 0;
    MYSQL_RES* pRowSet = NULL;
    unsigned int nFields = 0;
    MYSQL_ROW row = NULL;

    do { // MultiStatement MultiResult
         pRowSet = mysql_store_result( &hConnect );

        if ( NULL == pRowSet ) {
            GetErrorMsg( 0, strError, true, strError, "mysql_store_result" );
           // return 0;
        } else {
            nRows += mysql_num_rows( pRowSet ); // Row
            nFields = mysql_num_fields( pRowSet ); //Column
            // mysql_fetch_lengths( ) field length

            while ( NULL != ( row = mysql_fetch_row( pRowSet ) ) ) { // One Resultset
                for ( unsigned int nIndex = 0; nIndex < nFields; nIndex++ ){
                    qDebug( ) << row[ nIndex ] << endl;
                   lstRows << row[ nIndex ];
                }
            }

            mysql_free_result( pRowSet );
        }
    } while ( mysql_next_result( &hConnect ) == 0 ) ;

    return nRows;
}

void CMySqlDatabase::DbDisconnect( )
{
    if ( NULL != hStmt ) {
        mysql_stmt_close( hStmt );
    }

    mysql_close( &hConnect );
    //mysql_thread_end( );
}

CMySqlDatabase::~CMySqlDatabase( )
{
    DbDisconnect( );
    mysql_thread_end( );
    //mysql_library_end( );
}

bool CMySqlDatabase::ExcutePreparedStmt( QByteArray& byBlob, char& nFlag, QString& strSpName )
{
    QString strError;
    QString strCall = QString( "Call %1( ?, ? )" ).arg( strSpName );
    QByteArray byCallData = pCodec->fromUnicode( strCall );

    qDebug( ) << strCall << endl;
    MYSQL_BIND bind[ 2 ];
    int nRet = 0;
    int nSize = 0;
    char* bufData = NULL;
    char* pSql = NULL;
    ulong nRealData = 0;
    int nFields = 0;

    if ( NULL == hStmt ) {
        hStmt = mysql_stmt_init( &hConnect );
    }

    bool bRet = ( NULL != hStmt );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strCall, "mysql_stmt_init" );
        goto FileHandle;
    }

    nSize = byCallData.count( ); // Call Statement
    pSql = byCallData.data( );
    nRet = 0;

    qDebug( ) << QString( byBlob ) << endl;
    if ( strPreSpName != strSpName ) {
        nRet = mysql_stmt_prepare( hStmt, pSql, nSize );
        strPreSpName = strSpName;
    }

    bRet = ( 0 == nRet );
    if ( !bRet ){
        GetErrorMsg( nRet, strError, false, strCall, "mysql_stmt_prepare" );
        goto StmtHandle;
    }

    nSize = byBlob.count( );
    pSql = byBlob.data( );

    memset( bind, 0, sizeof ( bind ) );
    bind[ 0 ].buffer_type = MYSQL_TYPE_LONG_BLOB; // txtSql
    bind[ 0 ].length = 0;
    bind[ 0 ].is_null = 0; /* Bind the buffers */
    bind[ 0 ].buffer = pSql;
    bind[ 0 ].buffer_length = nSize;

    bind[ 1 ].buffer_type = MYSQL_TYPE_TINY;
    bind[ 1 ].length = 0;
    bind[ 1 ].is_null = 0; /* Bind the buffers */
    bind[ 1 ].buffer = &nFlag;
    bind[ 1 ].buffer_length = sizeof ( nFlag );

    bRet = ( 0 == mysql_stmt_bind_param( hStmt, bind ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strCall, "mysql_stmt_bind_param" );
        goto StmtHandle;
    }

    if ( 0 < nSize ) {
        nRet = mysql_stmt_send_long_data( hStmt, 0, pSql, nSize );
        bRet = ( 0 == nRet );
        if ( !bRet ) {
            GetErrorMsg( nRet, strError, false, strCall, "mysql_stmt_send_long_data" );
            goto StmtHandle;
        }
    }

    nRet = mysql_stmt_execute( hStmt );
    bRet = ( 0 == nRet );
    if ( !bRet ) {
        GetErrorMsg( nRet, strError, false, strCall, "mysql_stmt_execute" );
        goto StmtHandle;
    }

    byBlob.clear( );

    do {
        nFields = mysql_stmt_field_count( hStmt );
        if ( 0 < nFields ) {
            if ( hConnect.server_status & SERVER_PS_OUT_PARAMS ) {
                // max_allowed_packet 16M
                // write_timeout 120
                // Net Buffer 16M
                //bufData = ( char* ) malloc( nData );
                memset( bind, 0, sizeof ( bind ) );
                bind[ 0 ].buffer_type = MYSQL_TYPE_LONG_BLOB;
                bind[ 0 ].length = &nRealData; // Return Real Data Length
                bind[ 0 ].is_null = 0; /* Bind the buffers */
                bind[ 0 ].buffer = 0; // Bind data buffer
                bind[ 0 ].buffer_length = 0; // Buffer Length

                bind[ 1 ].buffer_type = MYSQL_TYPE_TINY;
                bind[ 1 ].length = 0;
                bind[ 1 ].is_null = 0; /* Bind the buffers */
                bind[ 1 ].buffer = &nFlag;
                bind[ 1 ].buffer_length = sizeof ( nFlag );

                bRet = ( 0 == mysql_stmt_bind_result( hStmt, bind ) );
                if ( !bRet ) {
                    GetErrorMsg( 0, strError, false, strCall, "mysql_stmt_bind_result" );
                    goto StmtHandle;
                }

                //bRet = ( 0 == mysql_stmt_attr_set( hStmt, STMT_ATTR_UPDATE_MAX_LENGTH, &bGetMaxLen ) );
                //bRet = ( 0 == mysql_stmt_store_result( hStmt ) ); // 会引起失败
                //if ( !bRet ) {
                //    GetErrorMsg( 0, strError, false, strCall, "mysql_stmt_store_result" );
                //    goto NewHandle;
                //}

                while ( true ) {
                    nRet = mysql_stmt_fetch( hStmt );

                    if ( MYSQL_NO_DATA == nRet ) {
                        break;
                    } else if ( 1 == nRet ) {
                        bRet = ( 0 == nRet );
                        if ( !bRet ) {
                            GetErrorMsg( 0, strError, false, strCall, "mysql_stmt_fetch" );
                            break;
                        }
                    }

                    if ( 0 < nRealData ) {
                        bufData = ( char* ) malloc( nRealData );
                    } else {
                        qDebug( ) << Q_FUNC_INFO << nRealData << endl;
                        continue;
                    }

                    bind[ 0 ].buffer= bufData;
                    bind[ 0 ].buffer_length= nRealData;
                    mysql_stmt_fetch_column( hStmt, bind, 0, 0 );

                    byBlob.append( ( const char* ) bufData, nRealData );

                    if ( NULL != bufData ) {
                        free( bufData );
                    }
                }



                bRet = ( 0  == mysql_stmt_free_result( hStmt ) );
                if ( !bRet ) {
                    GetErrorMsg( 0, strError, false, strCall, "mysql_stmt_free_result" );
                }
            }
        }
    } while ( 0 == mysql_stmt_next_result( hStmt ) );

    StmtHandle:
    //bRet = ( 0 == mysql_stmt_close( hStmt ) );
    //if ( !bRet ) {
    //    GetErrorMsg( 0, strError, false, strCall, "mysql_stmt_close" );
    //}

    FileHandle:

    //hStmt = NULL;

    return bRet;
}

bool CMySqlDatabase::BlobReadDb( QByteArray &byData, QString &strSql, QString &strError )
{
    //http://www.cplusplus.com
    bool bRet = false;
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
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_init" );
        goto FileHandle;
    }

    byteSql = pCodec->fromUnicode( strSql );
    nSize = byteSql.count( );
    pSql = byteSql.data( );

    bRet = ( 0 == mysql_stmt_prepare( hStmt, pSql, nSize ) );
    if ( !bRet ){
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_prepare" );
        goto StmtHandle;
    }

    bRet = ( 0 == mysql_stmt_execute( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_execute" );
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
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_bind_result" );
        goto NewHandle;
    }

    bRet = ( 0 == mysql_stmt_attr_set( hStmt, STMT_ATTR_UPDATE_MAX_LENGTH, &bGetMaxLen ) );
    bRet = ( 0 == mysql_stmt_store_result( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_store_result" );
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
            GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_bind_result" );
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
            GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_fetch" );
            goto NewHandle;
        } 
    }

    byData.clear( );
    byData.append( ( const char* ) bufData, length );

    NewHandle:
    if ( NULL != bufData ) {
        free( bufData );
    }

    bRet = ( 0  == mysql_stmt_free_result( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql,"mysql_stmt_free_result" );
    }

    StmtHandle:
    bRet = ( 0 == mysql_stmt_close( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_close" );
    }

    FileHandle:

    return bRet;
}

bool CMySqlDatabase::BlobReadDb( QString &strBlobFile, QString& strSql, QString& strError )
{
    //http://www.cplusplus.com
    QByteArray byData;
    bool bRet = BlobReadDb( byData, strSql, strError );
    if ( false == bRet ) {
        return bRet;
    }

    QFile file( strBlobFile );
    bRet = file.open( QIODevice::WriteOnly );
    if ( !bRet ) {
        return bRet;
    }

    file.write( byData );
    file.close( );

    return bRet;

#if false
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
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_init" );
        goto FileHandle;
    }

    byteSql = pCodec->fromUnicode( strSql );
    nSize = byteSql.count( );
    pSql = byteSql.data( );

    bRet = ( 0 == mysql_stmt_prepare( hStmt, pSql, nSize ) );
    if ( !bRet ){
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_prepare" );
        goto StmtHandle;
    }

    bRet = ( 0 == mysql_stmt_execute( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_execute" );
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
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_bind_result" );
        goto NewHandle;
    }

    bRet = ( 0 == mysql_stmt_attr_set( hStmt, STMT_ATTR_UPDATE_MAX_LENGTH, &bGetMaxLen ) );
    bRet = ( 0 == mysql_stmt_store_result( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_store_result" );
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
            GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_bind_result" );
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
            GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_fetch" );
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
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_free_result" );
    }

    StmtHandle:
    bRet = ( 0 == mysql_stmt_close( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_close" );
    }

    FileHandle:
    file.close( );

    return bRet;
#endif
}

bool CMySqlDatabase::BlobWriteDb( QByteArray &byData, QString &strSql, QString &strError )
{
    MYSQL_BIND bind[ 1 ];
    ulong       length = 0;
    QByteArray byteSql;
    int nRet = 0;
    int nSize = 0;
    const char* pSql = NULL;

    hStmt = mysql_stmt_init( &hConnect );
    bool bRet = ( NULL != hStmt );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_init" );
        goto FileHandle;
    }

    byteSql = pCodec->fromUnicode( strSql );
    nSize = byteSql.count( );
    pSql = byteSql.data( );
    nRet = mysql_stmt_prepare( hStmt, pSql, nSize );
    bRet = ( 0 == nRet );
    if ( !bRet ){
        GetErrorMsg( nRet, strError, false, strSql, "mysql_stmt_prepare" );
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
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_bind_param" );
        goto StmtHandle;
    }

    nSize = byData.count( );
    pSql = byData.data( );
    if ( 0 < nSize ) {
        nRet = mysql_stmt_send_long_data( hStmt, 0, pSql, nSize );
        bRet = ( 0 == nRet );
        if ( !bRet ) {
            GetErrorMsg( nRet, strError, false, strSql, "mysql_stmt_send_long_data" );
            goto StmtHandle;
        }
    }

    nRet = mysql_stmt_execute( hStmt );
    bRet = ( 0 == nRet );
    if ( !bRet ) {
        GetErrorMsg( nRet, strError, false, strSql, "mysql_stmt_execute" );
    }

    StmtHandle:
    bRet = ( 0 == mysql_stmt_close( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_close" );
    }

    FileHandle:

    return bRet;
}

bool CMySqlDatabase::BlobWriteDb( QString &strBlobFile, QString& strSql, QString& strError )
{
    QFile file( strBlobFile );
    bool bRet = false;

    if ( !file.exists( ) ) {
        return bRet;
    }

    bRet = file.open( QIODevice::ReadOnly );
    if ( !bRet ) {
        return bRet;
    }

    QByteArray byData = file.readAll( );
    file.close( );

    bRet = BlobWriteDb( byData, strSql, strError );

    return bRet;

#if false
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
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_bind_param" );
        goto StmtHandle;
    }

    byteSql = file.readAll( );
    nSize = byteSql.count( );
    pSql = byteSql.data( );
    if ( 0 < nSize ) {
        nRet = mysql_stmt_send_long_data( hStmt, 0, pSql, nSize );
        bRet = ( 0 == nRet );
        if ( !bRet ) {
            GetErrorMsg( nRet, strError, false, strSql, "mysql_stmt_send_long_data" );
            goto StmtHandle;
        }
    }

    nRet = mysql_stmt_execute( hStmt );
    bRet = ( 0 == nRet );
    if ( !bRet ) {
        GetErrorMsg( nRet, strError, false, strSql, "mysql_stmt_execute" );
    }

    StmtHandle:
    bRet = ( 0 == mysql_stmt_close( hStmt ) );
    if ( !bRet ) {
        GetErrorMsg( 0, strError, false, strSql, "mysql_stmt_close" );
    }

    FileHandle:
    file.close( );

    return bRet;
#endif
}
