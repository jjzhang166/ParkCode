#include "timerproc.h"

CTimerProc::CTimerProc()
{
    setAutoDelete( true );
    pSystem = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
}

void CTimerProc::run( )
{
    UploadReport( );
}

void CTimerProc::ConnectMySql( QStringList& lstParams )
{
    QString strItem = "Mgmt/";
    lstParams.clear( );

    lstParams<< pSystem->value( strItem.arg( "Host" ), QVariant( "127.0.0.1" ) ).toString( );
    lstParams<< pSystem->value( strItem.arg( "User" ), QVariant( "test" ) ).toString( );
    lstParams<< pSystem->value( strItem.arg( "Pwd" ), QVariant( "test" ) ).toString( );
    lstParams<< pSystem->value( strItem.arg( "Schema" ), QVariant( "pms" ) ).toString( );
    lstParams<< pSystem->value( strItem.arg( "Port" ), QVariant( "3306" ) ).toString( );
}

void CTimerProc::GetSQL( QString &strSql, QString& strTable )
{
    QString strSection = QString( "Mgmt/%1" ).arg( strTable );
    QString strFile;
    QString strSeperator = "@";
    QString strTmpSql;

    CCommonFunction::GetPath( strFile, CommonDataType::PathSnapshot );
    strFile += strTable;

    strTmpSql = pSystem->value( strSection, "" ).toString( );
    if ( strTmpSql.isEmpty( ) ) {
        return;
    }

    strSql = strTmpSql.arg( strFile ).replace( strSeperator, "," );
}

void CTimerProc::ExecuteSQL( QString& strTable )
{
    QString strSql = "";
    QString strError;
    GetSQL( strSql, strTable );

    if ( strSql.isEmpty( ) ) {
        return;
    }

    mySql.DbCrud( strSql, strError );
    qDebug( ) << Q_FUNC_INFO << endl << strError << endl;
}

void CTimerProc::UploadReport( )
{
    QStringList lstParams;
    ConnectMySql( lstParams );
    bool bRet = mySql.DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );

    if ( !bRet ) {
        return;
    }

    QString strTables[ ] = { "Feerd", "Stoprd" };
    ExecuteSQL( strTables[ 0 ] );
    ExecuteSQL( strTables[ 1 ] );

    mySql.DbDisconnect( );
}

CTimerProc* CTimerProc::GetInstance( )
{
    return new CTimerProc( );
}
