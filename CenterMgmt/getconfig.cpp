#include "getconfig.h"

CGetConfig::CGetConfig(QObject *parent) :
    QObject(parent)
{
    pSystemSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    GetAllTableSql( true );
    GetAllTableSql( false );
    GetTableFilterSQL( );
    GetAllClientIP( );
}

bool CGetConfig::GetStartupThreadFlag( bool bSender )
{
    bool bRet = false;
    QString strKey = QString( "Mgmt/Startup%1Thread" ).arg( bSender ? "Sender" : "Receiver" );
    bRet = pSystemSet->value( strKey, false ).toBool( );

    return bRet;
}

void CGetConfig::GetMgmtSvrIP( QString &strIP )
{
    QString strKey = QString( "Mgmt/MgmtSvrIP" );
    strIP = pSystemSet->value( strKey, "127.0.0.1" ).toString( );
}

quint16 CGetConfig::GetMgmtSvrPort( )
{
    QString strKey = QString( "Mgmt/MgmtSvrPort" );
    return pSystemSet->value( strKey, 8000 ).toUInt( );
}

int CGetConfig::GetInterval( bool bRequest  )
{
    int nInterval = pSystemSet->value( QString( "Mgmt/%1Interval" ).arg( bRequest ? "Receiver" : "Sender" ), 0 ).toInt( );

    return nInterval;
}

void CGetConfig::GetTableFilterSQL( )
{
    hashFilterWhereSQL.clear( );
    QString strSql = "";

    foreach ( const QString strTable, lstRequestTables ) {
        strSql = pSystemSet->value( QString( "Mgmt/%1Filter" ).arg( strTable ), "" ).toString( );

        if ( !strSql.isEmpty( ) ) {
           hashFilterWhereSQL.insert( strTable, strSql );
        }
    }
}

void CGetConfig::GetAllClientIP( )
{
    lstClientIP.clear( );
    QString strSeperator = "@";

    lstClientIP = pSystemSet->value( "Mgmt/MgmtClientIP", "" ).toString( ).split( strSeperator );
}

QStringList& CGetConfig::GetClientIP( )
{
    return lstClientIP;
}

void CGetConfig::GetFilterSQL( QString &strSql, const QString &strKey )
{
    strSql = hashFilterWhereSQL.value( strKey );
}

void CGetConfig::GetAllTableSql( bool bRequest )
{
    ( bRequest ? hashRequestSQL : hashSQL ).clear( );

    QString strSeperator = "@";
    QStringList lstTmpTables = pSystemSet->value(
                QString( "Mgmt/%1Tables" ).arg( bRequest ? "Request" : "" ), "" ).toString( ).split( strSeperator );
    QString strSql = "";

    if ( bRequest ) {
        lstRequestTables = lstTmpTables;
    } else {
        lstTables = lstTmpTables;
    }

    foreach ( const QString strTable, lstTmpTables ) {
        strSql = pSystemSet->value( QString( "Mgmt/%1Select" ).arg( strTable ), "" ).toString( );

        if ( !strSql.isEmpty( ) ) {
            strSql.replace( strSeperator, "," );
            ( bRequest ? hashRequestSQL : hashSQL ).insert( strTable, strSql );
        }
    }
}

QStringList& CGetConfig::GetAllTables( bool bRequest )
{
    return bRequest ? lstRequestTables : lstTables;
}

void CGetConfig::GetSQL( bool bRequest, QString &strSql, const QString &strKey )
{
    strSql = ( bRequest ? hashRequestSQL : hashSQL ).value( strKey );
}
