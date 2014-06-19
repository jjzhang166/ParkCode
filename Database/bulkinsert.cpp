#include "bulkinsert.h"

CBulkInsert::CBulkInsert( )
{
    pDbServer = NULL;
    lstValues = NULL;
    setAutoDelete( true );
}

CBulkInsert* CBulkInsert::GetInstance( )
{
    return new CBulkInsert( );
}

CBulkInsert::~CBulkInsert( )
{
}

void CBulkInsert::SendSqlError( QSqlError error )
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
    qDebug( ) << "CBulkInsert:" << strError << endl;
#endif
}

QVariantList* CBulkInsert::GetVariantList( int nCols )
{
    nColCount = nCols;

    if ( NULL == lstValues ) {
        lstValues = new QVariantList[ nColCount ];
    }

    return lstValues;
}

void CBulkInsert::SetDbParams( QSqlDatabase *pDb, QString &strSql )
{
    pDbServer = pDb;
    strDbSql = strSql;
}

void CBulkInsert::run( )
{
    bool bRet = true;

    if ( !pDbServer->isOpen( ) ) {
        bRet = pDbServer->open( );
        if ( !bRet ) {
            SendSqlError( pDbServer->lastError( ).text( ) );
            return;
        }
    }

    QSqlQuery query = pDbServer->exec( );
    query.prepare( strDbSql );
    for ( int nIndex = 0; nIndex < nColCount; nIndex++ ) {
        query.addBindValue( lstValues[ nIndex ] );
    }

    pDbServer->transaction( );
    bRet = query.execBatch( );
    if ( bRet ) {
        pDbServer->commit( );
    } else {
        SendSqlError( query.lastError( ).text( ) );
        pDbServer->rollback( );
    }

    if ( NULL != lstValues ) {
        delete [ ] lstValues;
        lstValues = NULL;
    }

    if ( QSqlError::ConnectionError == query.lastError( ).type( ) ) {
        pDbServer->close( );
    }
}
