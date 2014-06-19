#include "logicinterface.h"
//#define GUI_MAIN_CONTROLER
#include <QDebug>
#include "commonfunction.h"

CLogicInterface* CLogicInterface::m_pInterface = 0;

CLogicInterface::CLogicInterface()
{
#ifdef GUI_MAIN_CONTROLER
    m_hMainCtrl = OpenInterface( );
#endif
}

CLogicInterface::~CLogicInterface( )
{
#ifdef GUI_MAIN_CONTROLER
    CloseInterface( m_hMainCtrl );
#endif
}

CMySqlDatabase& CLogicInterface::GetMysqlDb( bool bHistory )
{
    return bHistory ? mysqlHistoryDb : mysqlDb;
}

void CLogicInterface::OperateICCard( QStringList &lstData, bool bOpen )
{
#ifdef GUI_MAIN_CONTROLER
#endif

    if ( true == bOpen ) {

    } else {

    }
}

int CLogicInterface::DbDeleteRd( int nIndex, QString& strDate )
{
    QString strSql ="";
    QString strDelete = "";
    QString strDeleteGarage = "";
    QString strTmpDelete = "";
#ifndef QT_NO_DEBUG
   qDebug( ) << "Delete Start " << QTime::currentTime( ).toString( ) << endl;
#endif
#if false
    switch ( nIndex ) {
    case 1 :
        strSql = QString( "Delete From Feerd Where Date( FeeTime ) < '%1'" ).arg( strDate );
        break;

    case 2 :
        strSql = QString( "Delete From Stoprd
                          Where ( ( Date( InTime ) < '%1' )
                          and ( cardno like '%(%)%' Or outtime is not null ) )
                          OR ( cardno like '%(%)%' and ( Date( OutTime ) < '%2' ) ) " ).arg( strDate, strDate );
        break;

    case 3 :
        strSql = QString( "Delete From SysInfo Where Date( InfoTime ) < '%1'" ).arg( strDate );
        break;

    case 4 :
        strSql = QString( "Update Stoprd Set invideo1 = null, outvideo1 = null Where ( ( Date( InTime ) < '%1' )
                          and ( cardno like '%(%)%' Or outtime is not null ) )
                          OR ( cardno like '%(%)%' and ( Date( OutTime ) < '%2' ) ) " ).arg( strDate, strDate );
        break;
    }  
#endif

    switch ( nIndex ) {
        case 1 :
        strSql = QString( "Delete From Feerd Where Date( FeeTime ) < '%1'" ).arg( strDate );
        break;

        case 2 :
        strSql = QString( "Select stoprdid From stoprd Where ( ( Date( InTime ) < '%1' ) \
                          and ( outtime is not null or childrdindx = 1 ) ) \
                          OR ( Date( OutTime ) < '%2' ) " ).arg( strDate, strDate );
        strDelete = "Delete From stoprd where stoprdid in ( %1 )";
        strDeleteGarage = "Delete From GarageInGarage Where CardID IN ( Select Distinct Cardno From stoprd where stoprdid In( %1 ) ) and DateTime < '%2'";
        strTmpDelete = "Delete From tmpcardintime where type = 1 and stoprdid in( %1 ) and intime < '%2'";
        break;

        case 3 :
        strSql = QString( "Select infoindex From sysinfo Where Date( InfoTime ) < '%1'" ).arg( strDate );
        strDelete = "Delete From sysinfo where infoindex in ( %1 )";
        break;

        case 4 :
        strSql = QString( "Select stoprdid From stoprd Where ( ( Date( InTime ) < '%1' ) \
                          and ( outtime is not null or childrdindx = 1 ) ) \
                          OR ( Date( OutTime ) < '%2' ) " ).arg( strDate, strDate );
        strDelete = "Update stoprd as a  Set a.invideo1 = null, a.invideo2 = null, a.invideo3 = null, a.invideo4 = null, a.outvideo1 = null,\
                             a.outvideo2 = null, a.outvideo3 = null, a.outvideo4 = null where a.stoprdid in( %1 )";
        break;
    }

    if ( 1 == nIndex ) {
        return ExecuteSql( strSql );
    }


    //strSql = QString( "Call DeleteData( %1, '%2', @Res )" ).arg( QString::number( nIndex ), strDate );

    QStringList lstRows;
    QString strSeperator = ",";
    QString strWhere = "";
    ExecuteSql( strSql, lstRows ); // GetID
    int nCounts = lstRows.count( );
    int nCount = 0;

    if ( 0 == nCounts % 1000 ) {
        nCount = nCounts / 1000;
    } else {
        nCount = nCounts / 1000 + 1;
    }

    QStringList lstTmp;
    for ( int nItem = 0; nItem < nCount; nItem++ ) {
        lstTmp.clear( );
        for ( int nSection = 0; nSection < 1000; nSection++ ) {
            int nPos = nItem * 1000 + nSection;

            if ( nPos >= nCounts ) {
                break;
            }

            lstTmp << lstRows.at( nPos );
        }

        strWhere = lstTmp.join( strSeperator );

        if ( 0 < nCounts && 2 == nIndex ) {
            strSql = strDeleteGarage.arg( strWhere, strDate );
            ExecuteSql( strSql );

            strSql = strTmpDelete.arg( strWhere, strDate );
            ExecuteSql( strSql );
        }

        strSql = strDelete.arg( strWhere );
        ExecuteSql( strSql );
    }

#ifndef QT_NO_DEBUG
   qDebug( ) << "Delete End " << QTime::currentTime( ).toString( ) << endl;
#endif

    return 0;
}

int CLogicInterface::OperateRechargeInfo( QStringList &lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strError;
    int nRows = 0;
    int nCols = 0;

    QString strSql = "select a.feetime,a.feekind,a.feenumb,a.timelen, b.carcp, c.username, c.useradress, \
                     c.usercorp, a.feeoperator, d.cardselfno, d.cardno from feerd a \
                     inner join carinfo b on a.cardno = b.cardindex \
                     inner join userinfo c on a.cardno = c.cardindex \
                     inner join ( \
                     select distinct cardno, cardselfno from monthcard \
                     union select distinct cardno, cardselfno from savecard \
                     union select distinct cardno, cardselfno from tmpcard ) d \
                     on a.cardno = d.cardno and a.feekind not like '%收费'";

    nCols = 11;
    strSql += strWhere;
    if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
    GetMysqlDb( ).GetRowData( lstRows, strError );
    nRows = lstRows.count( ) / nCols;

    return nRows;
}

int CLogicInterface::OperateOutInInfo( QStringList &lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strError;
    int nRows = 0;
    int nCols = 0;

    QString strSql = "select a.cardno, a.cardkind, a.feenum, a.feefactnum, a.feezkyy, a.cardselfno, \
            a.inshebeiname, a.intime, a.outshebeiname, a.outtime, a.carkind, a.carcp, a.carcpout from stoprd a ";
    nCols = 13;
    strSql += strWhere;
    if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
    GetMysqlDb( ).GetRowData( lstRows, strError );
    nRows = lstRows.count( ) / nCols;

    return nRows;
}

int CLogicInterface::OperateBlacklistInfo( QStringList &lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        strSql = "SELECT plate, kind, color, id FROM blacklist";
        nCols = 4;
        strSql += strWhere;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        strSql = "Update blacklist set plate = '%1', kind = '%2', color = '%3' ";
        nCols = 3;
        strSql += strWhere;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;

    case CommonDataType::DeleteData :
        strSql = "Delete From blacklist ";
        strSql += strWhere;

        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        break;

    case CommonDataType::InsertData :
        strSql = "Insert Into blacklist ( plate, kind, color ) ";
        strSql += "Values( '%1', '%2', '%3' )";
        nCols = 3;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }

    return nRows;
}

int CLogicInterface::OperateTollDiscountInfo( QStringList &lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        strSql = "SELECT zkname, zkflag, zknumb, zkdetail, zkindex FROM zkset";
        nCols = 5;
        strSql += strWhere;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        strSql = "Update zkset set zkname = '%1', zkflag = '%2', zknumb = %3, zkdetail = '%4' ";
        nCols = 4;
        strSql += strWhere;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;

    case CommonDataType::DeleteData :
        strSql = "Delete From zkset ";
        strSql += strWhere;

        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        break;

    case CommonDataType::InsertData :
        strSql = "Insert Into zkset ( zkname, zkflag, zknumb, zkdetail ) ";
        strSql += "Values( '%1', '%2', %3, '%4' )";
        nCols = 4;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }

    return nRows;
}

int CLogicInterface::OperateBatchCardInfo(QStringList &lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :

        break;

    case CommonDataType::UpdateData :

        break;

    case CommonDataType::DeleteData :
        strSql = "Delete From cardright ";
        strSql += strWhere;

        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        break;

    case CommonDataType::InsertData :
        strSql = "Insert Into cardright ( cardno, roadconind, starttime, endtime, shebeiname ) ";
        strSql += "Values( '%1', %2, '%3', '%4', '%5' )";
        nCols = 5;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }

    return nRows;
}

void CLogicInterface::OperateSysSettingInfo( QStringList &lstRows, CommonDataType::DatabaseOperation dbOperation )
{
#ifdef GUI_MAIN_CONTROLER
#endif
    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        break;

    case CommonDataType::UpdateData :
        break;

    case CommonDataType::DeleteData :
        break;

    case CommonDataType::InsertData :
        break;
    }
}

void CLogicInterface::OperateDeviceConfigInfo( QStringList &lstRows, CommonDataType::DatabaseOperation dbOperation )
{
#ifdef GUI_MAIN_CONTROLER
#endif
    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        break;

    case CommonDataType::UpdateData :
        break;

    case CommonDataType::DeleteData :
        break;

    case CommonDataType::InsertData :
        break;
    }
}

void CLogicInterface::ControlLedInfo( QStringList &lstChannel, QString &strInfo, QStringList &lstResult )
{
    lstResult.clear( );
    int nCount = lstChannel.count( );
    QString strName;

    //lstChannel << "Name";
    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        strName = lstChannel[ nIndex ];

#ifdef GUI_MAIN_CONTROLER
        nRet = SendLedInfo( m_hMainCtrl, strInfo );
#endif
#ifdef GUI_MAIN_CONTROLER
        if ( P_SUCCESS != nRet ) {
            strName += " LED发送信息失败！";
            lstResult << strName;
        }
#endif
    }
}

int CLogicInterface::OperateCarInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        strSql = "Select carcp, carmodel, carhaoma, carid FROM carinfo ";
                 // carpic cardindex
        nCols = 4;
        strSql += strWhere;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        strSql = "Update carinfo set carcp = '%1', carmodel = '%2', carhaoma = '%3', cardindex = '%4' ";
        nCols = 4;
        strSql += strWhere;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;

    case CommonDataType::DeleteData :
        strSql = "Delete From carinfo ";
        break;

    case CommonDataType::InsertData :
        strSql = "Insert Into carinfo ( carcp, carmodel, carhaoma, cardindex ) ";
        strSql += "Values( '%1', '%2', '%3', '%4' )";
        nCols = 4;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }

    return nRows;
}

int CLogicInterface::OperateOwnerInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        strSql = "SELECT username, usersex, useradress, ";
        strSql += "usercorp, userphone, userhaoma, "; //userpic
        strSql += "userid FROM userinfo "; //cardindex
        nCols = 7;
        strSql += strWhere;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        strSql = "Update IGNORE userinfo set username ='%1', usersex = '%2', useradress = '%3',";
        strSql += "usercorp = '%4', userphone = '%5', userhaoma = '%6', cardindex = '%7' ";
        nCols = 7;
        strSql += strWhere;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;

    case CommonDataType::DeleteData :
        strSql = "Delete IGNORE From userinfo ";
        strSql += strWhere;

        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        break;

    case CommonDataType::InsertData :
        strSql = "Insert IGNORE Into userinfo ( username, usersex, useradress, usercorp, userphone, userhaoma, cardindex ) ";
        strSql += "Values( '%1', '%2', '%3', '%4', '%5', '%6', '%7' )";
        nCols = 7;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }

    return nRows;
}

void CLogicInterface::UpdateSaveCardRemainder( bool bAdd, uint nAmount, QString strCardNo )
{
    QString strSql = QString( "Select cardfee From savecard Where cardno = '%1'" ).arg( strCardNo );
    QStringList lstRow;
    ExecuteSql( strSql, lstRow );
    if ( 0 >= lstRow.count( ) ) {
        return;
    }

    uint nFee = lstRow[ 0 ].toUInt( );
    if ( bAdd ) {
        nFee += nAmount;
    } else {
        nFee -= nAmount;
    }

    strSql = QString( "Update savecard Set cardfee = %1 Where cardno = '%2' " ).arg( QString::number( nFee ), strCardNo );
    ExecuteSql( strSql );
}

int CLogicInterface::OperateChargeRecord( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    //SELECT feeindex, feenumb, feetime, feekind, feeoperator, cardno, timelen FROM feerd
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        strSql ="Select feenumb, timelen, feetime, feekind, feeoperator From feerd ";
        nCols = 5;
        strSql += strWhere;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
            return 0;
        }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        strSql = "Update IGNORE feerd set feenumb = %1, timelen = %2, feetime = '%3', ";
        strSql += "feekind = '%4', feeoperator = '%5', cardno = '%6' ";
        break;

    case CommonDataType::DeleteData :
        strSql = "Delete IGNORE From feerd Where feeindex = %1";
        break;

    case CommonDataType::InsertData :
        strSql = "Insert IGNORE Into feerd ( feenumb, timelen, feetime, feekind, feeoperator, cardno ) ";
        strSql += "Values ( %1, %2, '%3', '%4', '%5', '%6' )";
        nCols = 6;

        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }

    return nRows;
}

void CLogicInterface::ConnectHistoryDb( bool bHistory )
{
    if ( !bHistory ) {
        return;
    }

    QStringList lstPrams;
    CCommonFunction::ConnectMySql( lstPrams, true );
    mysqlHistoryDb.DbConnect( lstPrams[ 0 ], lstPrams[ 1 ], lstPrams[ 2 ], lstPrams[ 3 ],
                                                        lstPrams[ 4 ].toUInt( ) );
}

void CLogicInterface::DisconnectHistoryDb( bool bHistory )
{
    if( !bHistory ) {
        return;
    }

    mysqlHistoryDb.DbDisconnect( );
}

int CLogicInterface::InnerExcuteSql( QString& strSql, bool bSelect, QStringList* pLstRows, bool bHistory )
{
    int nRet = 0;
    QString strError;
    ConnectHistoryDb( bHistory );
    if ( !GetMysqlDb( bHistory ).DbCrud( strSql, strError ) ) {
        return -1;
    }

    if ( bSelect && NULL != pLstRows ) {
        nRet = GetMysqlDb( bHistory ).GetRowData( *pLstRows, strError );
    }

    DisconnectHistoryDb( bHistory );

    return nRet;
}

int CLogicInterface::ExecuteSql(QString &strSql, bool bHistory )
{
    return InnerExcuteSql( strSql, false, NULL, bHistory );
}

int CLogicInterface::ExecuteSql( QString &strSql, QStringList &lstRow, bool bHistory )
{
    if( strSql.isEmpty( ) ) {
        return 0;
    }

    return InnerExcuteSql( strSql, true, &lstRow, bHistory );
}

int CLogicInterface::OperateInOutRecord( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    //SELECT stoprdid, cardno, inshebeiname, outshebeiname, invideo1, invideo2, invideo3, invideo4,
    //outvideo1, outvideo2, outvideo3, outvideo4, intime, outtime, childrdindx, feebeizhu,
    //feenum, feetime, feeoperator, feefactnum, carcp, username, cardselfno, carkind, feekind,
    //cardkind, parkid, feezkh, feezkyy FROM stoprd;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        strSql = "Select inshebeiname, intime, outshebeiname, outtime From stoprd ";
        strSql += strWhere;

        nCols = 4;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        break;

    case CommonDataType::DeleteData :
        break;

    case CommonDataType::InsertData :
        strSql = "Insert Into stoprd ( inshebeiname, intime, outshebeiname, outtime, cardno )";
        break;
    }

    return nRows;
}

int CLogicInterface::OperateInOutRight( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        strSql = "Select shebeiname, starttime, endtime, cardsetind From cardright ";
        strSql += strWhere;

        nCols = 4;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        strSql = "Update IGNORE cardright set starttime = '%1', endtime = '%2' where cardsetind = %3";
        nCols = 3;

        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;

    case CommonDataType::DeleteData :
        break;

    case CommonDataType::InsertData :
        break;
    }

    return nRows;
}

void CLogicInterface::ExistCardNumber( QString &strCardNo, QStringList& strList )
{
    strList.clear( );
    QStringList lstRows;
    QString strSQL = "select cardno from %1 where cardno = '%2'";
    QString strTmp = strSQL.arg( "monthcard", strCardNo );
    ExecuteSql( strTmp, lstRows );

    if ( 0 < lstRows.count( ) ) {
        strList << strCardNo + "卡号已在月租卡表。\n";
    }

    strSQL = "select cardno from %1 where cardno = '%2'";
    strTmp = strSQL.arg( "savecard", strCardNo );
    ExecuteSql( strTmp, lstRows );

    if ( 0 < lstRows.count( ) ) {
        strList << strCardNo + "卡号已在储值卡表。\n";
    }

    strSQL = "select cardno from %1 where cardno = '%2'";
    strTmp = strSQL.arg( "tmpcard", strCardNo );
    ExecuteSql( strTmp, lstRows );

    if ( 0 < lstRows.count( ) ) {
        strList << strCardNo + "卡号已在计时卡表。\n";
    }
}

int CLogicInterface::OperateCardInfo(QStringList &lstRows, CommonDataType::CardType carType, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        switch ( carType ) {
        case CommonDataType::MonthlyCard :
            strSql = "Select cardno, EnterMustCard, LeaveMustCard, MIMO, cardkind, starttime, endtime,cardstate, cardselfno, cardcomment, cardcreator From monthcard ";
            nCols = 11;
            break;

        case CommonDataType::ValueCard :
            strSql = "Select cardno, EnterMustCard, LeaveMustCard, cardkind, cardstate, cardfee, cardfeebz, cardselfno, cardcomment, cardcreator From savecard ";
            nCols = 10;
            break;

        case CommonDataType::TimeCard :
            strSql = "Select cardno, cardkind, cardfeebz, cardselfno, cardstate From tmpcard ";
            nCols = 5;
            break;
        }

        strSql += strWhere;

        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        switch ( carType ) {
        case CommonDataType::MonthlyCard :
            strSql = "Update IGNORE monthcard set cardno = '%1', cardkind = '%2', starttime = '%3', endtime = '%4',cardstate = '%5',";
            strSql += "cardselfno = '%6', cardcomment = '%7', cardcreator = '%8', EnterMustCard = %9, LeaveMustCard = %10, MIMO = %11  ";
            nCols = 11;
            break;

        case CommonDataType::ValueCard :
            strSql = "Update IGNORE savecard set cardno = '%1', cardkind = '%2', cardstate = '%3', cardfee = %4, cardfeebz = '%5',";
            strSql += "cardselfno = '%6', cardcomment = '%7', cardcreator = '%8', EnterMustCard = %9, LeaveMustCard = %10 ";
            nCols = 10;
            break;

        case CommonDataType::TimeCard :
            strSql = "Update IGNORE tmpcard set cardno = '%1', cardkind = '%2', cardfeebz = '%3', cardselfno = '%4', cardstate = '%5' ";
            nCols = 5;
            break;
        }

        strSql += strWhere;

        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;

    case CommonDataType::DeleteData :
        switch ( carType ) {
        case CommonDataType::MonthlyCard :
            strSql = "Delete From monthcard ";
            break;

        case CommonDataType::ValueCard :
            strSql = "Delete From savecard ";
            break;

        case CommonDataType::TimeCard :
            strSql = "Delete From tmpcard ";
            break;
        }

        strSql += strWhere;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        break;

    case CommonDataType::InsertData :
        switch ( carType ) {
        case CommonDataType::MonthlyCard :
            strSql = "Insert IGNORE Into monthcard ( cardno, cardkind, starttime, endtime,cardstate, cardselfno, cardcomment, cardcreator, EnterMustCard, LeaveMustCard, MIMO ) ";
            strSql += "Values ( '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', %9, %10, %11 )";
            nCols = 11;
            break;

        case CommonDataType::ValueCard :
            strSql = "Insert IGNORE Into savecard ( cardno, cardkind, cardstate, cardfee, cardfeebz, cardselfno, cardcomment, cardcreator, EnterMustCard, LeaveMustCard ) ";
            strSql += "Values ( '%1', '%2', '%3', %4, '%5', '%6', '%7', '%8', %9, %10 )";
            nCols = 10;
            break;

        case CommonDataType::TimeCard :
            strSql = "Insert IGNORE Into tmpcard ( cardno, cardkind, cardfeebz, cardselfno, cardstate ) ";
            strSql += "Values ( '%1', '%2', '%3', '%4', '%5' )";
            nCols = 5;
            break;
        }

        //strSql += strWhere;

        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }

    return nRows;
}

int CLogicInterface::OperateSysLogInfo( QStringList &lstRows, CommonDataType::SysLogType logType, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    QString strLogType;
    QString strSql = "";
    QString strError;
    int nRows = 0;
    int nCols = 0;

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        strSql = "Select infooperator, infotext, infotime From sysinfo ";
        strSql += strWhere; // infoindex
        strSql += " Order by infotime desc";

        nCols = 3;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        ;
        break;

    case CommonDataType::DeleteData :
        strSql = "Delete From sysinfo ";
        strSql += strWhere;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        break;

    case CommonDataType::InsertData :
        switch ( logType ) {
        case CommonDataType::ShiftLog :
            strLogType = "换班记录";
            break;

        case CommonDataType::DeleteDBLog :
            strLogType = "删除数据库";
            break;

        case CommonDataType::ManualGateLog :
            strLogType = "手动开关闸";
            break;

        case CommonDataType::HardwareInfoLog :
            strLogType = "硬件信息警告信息";
            break;

        case CommonDataType::CardMgmLog :
            strLogType = "卡片管理";
            break;

        case ( CommonDataType::SysLogType ) -1 :
            strLogType = "导入授权数据";
            break;
        }

        nCols = 4;
        nRows = lstRows.count( ) / nCols;
        strSql = "insert into sysinfo( infooperator,infokind,infotext, infotime ) values( ";
        strSql += "'%1', '%2', '%3', '%4' )";
        //strSql += strWhere;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }

    return nRows;
}

void CLogicInterface::GetAllTariff2File( )
{
    QStringList lstRows;
    QString strWhere = "";

    OperateTariffInfo( lstRows, CommonDataType::SelectData, strWhere );
    int nCount = lstRows.count( );
    int nCols = 40;
    int nRows = nCount / nCols;

    QSettings* pSettings = CCommonFunction::GetSettings( CommonDataType::CfgTariff );

    QString strSection;
    int nField = 0;
    int nTypes = pSettings->value( "CarType/Count").toInt( );

    QString strValues[ ] = { "大型车", "中型车", "小型车", "摩托车",
                             "免费车辆", "自定义1", "自定义2", "自定义3" };
    for ( int nIndex = 0; nIndex < 8; nIndex++ ) {
        pSettings->setValue( QString( "CarType/Count%1" ).arg( nIndex ),
                             strValues[ nIndex ] );
    }

    if ( 0 == nTypes ) {
        pSettings->setValue( "CarType/Count", 8 );
        nTypes = 8;
        //CCommonFunction::MsgBox( NULL, "提示", "费配置文件【TariffCfg.ini】内容丢失。", QMessageBox::Information );
        //return;
    }

    pSettings->sync( );

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        nField = nRow * nCols ;

        if ( 0 == nRow % nTypes) {
            strSection = lstRows[ nField++ ];
            pSettings->beginGroup( strSection );
        } else {
            nField++;
        }

        strSection = lstRows[ nField++ ];
        strSection += "/%1";

        pSettings->setValue( strSection.arg( "LimitTime" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "NoFullTime" ), lstRows[ nField++ ] );

        pSettings->setValue( strSection.arg( "Section1" ), lstRows[ nField++ ] );//QTime
        pSettings->setValue( strSection.arg( "Section2" ), lstRows[ nField++ ] );

        pSettings->setValue( strSection.arg( "rule1MinInner" ), lstRows[ nField++ ] );//int
        pSettings->setValue( strSection.arg( "rule1FootInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule2MinInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule2FootInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule3MinInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule3FootInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule4MinInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule4FootInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule5MinInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule5FootInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule6MinInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule6FootInner" ), lstRows[ nField++ ] );

        pSettings->setValue( strSection.arg( "rule1MinOuter" ), lstRows[ nField++ ] );//int
        pSettings->setValue( strSection.arg( "rule1FootOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule2MinOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule2FootOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule3MinOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule3FootOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule4MinOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule4FootOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule5MinOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule5FootOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule6MinOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "rule6FootOuter" ), lstRows[ nField++ ] );

        pSettings->setValue( strSection.arg( "perMinInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "perMinFootInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "perMinOuter" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "perMinFootOuter" ), lstRows[ nField++ ] );

        pSettings->setValue( strSection.arg( "LimitFootInner" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "LimitFootOuter" ), lstRows[ nField++ ] );

        pSettings->setValue( strSection.arg( "perMinNoSectionLimit" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "perMinFootNoSection" ), lstRows[ nField++ ] );

        pSettings->setValue( strSection.arg( "perMinNoSectionFirst" ), lstRows[ nField++ ] );
        pSettings->setValue( strSection.arg( "Section" ), lstRows[ nField++ ] );

        if ( 0 == ( nRow + 1 ) % nTypes ) {
            pSettings->endGroup(  );
        }
    }

    pSettings->sync( );
}

void CLogicInterface::OperateTariffInfo( QStringList &lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    int nRows = 0;
    int nCols = 0;
    QString strError;
    QString strSql = "";

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        strSql = QString( "SELECT rparkid,rfeemodel,kxiant,freet,fdtimestar,fdtimeend,\
                 gz1t,gz1f,gz2t,gz2f,gz3t,gz3f,gz4t,gz4f,gz5t,gz5f,gz6t,gz6f,\
                 gz7t,gz7f,gz8t,gz8f,gz9t,gz9f,gz10t,gz10f,gz11t,gz11f,gz12t,gz12f,\
                 dldwt,dldwf,dwdwt,dwdwf,dlxianfee,dwxianfee,\
                 xhdw,xhfh,firstjstime,section \
                 FROM feerate1 %1 \
                 order by rparkid, rfeemodel asc" ).arg( strWhere );

        nCols = 40;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        strSql = QString( "Update feerate1   Set kxiant = %1,freet = %2,fdtimestar = '%3',fdtimeend = '%4', \
                           gz1t = %5,gz1f = %6,gz2t = %7,gz2f = %8,gz3t = %9,gz3f = %10,gz4t = %11,\
                           gz4f = %12,gz5t = %13,gz5f = %14,gz6t = %15,gz6f = %16,gz7t = %17,\
                           gz7f = %18,gz8t = %19,gz8f = %20,gz9t = %21,gz9f = %22,gz10t = %23,\
                           gz10f = %24,gz11t = %25,gz11f = %26,gz12t = %27,gz12f = %28, dldwt = %29,\
                           dldwf = %30,dwdwt = %31,dwdwf = %32,dlxianfee = %33,dwxianfee = %34, \
                           xhdw = %35,xhfh = %36,firstjstime = %37, section = %38 " ) +  strWhere;

        nCols = 38;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;

    case CommonDataType::DeleteData :
        break;

    case CommonDataType::InsertData :
        strSql = QString( "Insert Into feerate1( kxiant,freet,fdtimestar,fdtimeend,\
                 gz1t,gz1f,gz2t,gz2f,gz3t,gz3f,gz4t,gz4f,gz5t,gz5f,gz6t,gz6f,\
                 gz7t,gz7f,gz8t,gz8f,gz9t,gz9f,gz10t,gz10f,gz11t,gz11f,gz12t,gz12f,\
                 dldwt,dldwf,dwdwt,dwdwf,dlxianfee,dwxianfee,\
                 xhdw,xhfh,firstjstime,rparkid,rfeemodel ) Values( %1,%2,'%3','%4',%5,\
                 %6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,\
                 %25,%26,%27,%28,%29,%30,%31,%32,%33,%34,%35,%36,%37,%38,%39, %40 )" );

        nCols = 40;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }
}

void CLogicInterface::ReplaceSqlParam( int nRows, int nCols, QString& strSql, QStringList& lstRows )
{
    QString strError;
    QString strTmp;

    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        strTmp = strSql;
        for ( int nCol =0; nCol < nCols; nCol++ ) {
            strTmp = strTmp.arg( lstRows[ nIndex * nCols + nCol ] );
        }

        GetMysqlDb( ).DbCrud( strTmp, strError );
    }
}

int CLogicInterface::OperateRightInfo( QStringList &lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere )
{
    int nRows = 0;
    int nCols = 0;
    QString strError;
    QString strSql = "";
    //QString strKey = "[Guid(\"CF830377-C673-42AB-A8B6-0E1472075815\")]";
    // AES_ENCRYPT( )
    // AES_DECRYPT( )

    switch ( dbOperation ) {
    case CommonDataType::SelectData :
        //operatorpassword,surecardno
        strSql =  "Select operatorname,employeeid,operatorsex,operatorright,qxgl,feerate,\
                  datagl,sysinfo,StartVideo,StartPlate,ConnectDB,exitgl,MonthCard,\
                  ValueCard,TimeCard,LedInfo,DeviceConfig,SystemSet,CardRightSet,\
                  DiscountSet,Blacklist,SerialPortSet,PlateRecogSet,SyncTime,PassRecord,FeeRecord,\
                  DiscountReport,DailyReport,MonthlyReport,YearlyReport,\
                  operatoraddress,operatorphone,operatorid from operator "; //operatorid PK
        strSql += strWhere; //
        nCols = 33;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        GetMysqlDb( ).GetRowData( lstRows, strError );
        nRows = lstRows.count( ) / nCols;
        break;

    case CommonDataType::UpdateData :
        strSql = "Update operator set operatorname = '%1', employeeid = '%2', operatorsex = '%3', operatorright = '%4',";
        strSql += "qxgl = %5, feerate = %6, datagl = %7, sysinfo  = %8, StartVideo = %9,";
        strSql += "StartPlate = %10, ConnectDB = %11, exitgl = %12, MonthCard = %13, ValueCard = %14,";
        strSql += "TimeCard = %15, LedInfo = %16, DeviceConfig = %17, SystemSet = %18, CardRightSet = %19,";
        strSql += "DiscountSet = %20, Blacklist ='%21', SerialPortSet = %22, PlateRecogSet = %23, SyncTime = %24, PassRecord = %25, FeeRecord = %26,";
        strSql += "DiscountReport = %27, DailyReport = %28, MonthlyReport = %29, YearlyReport = %30,";
        strSql += "operatoraddress = '%31', operatorphone = '%32' ";
        strSql += strWhere; // operatorid = ?;
        nCols = 32;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;

    case CommonDataType::DeleteData :
        strSql = "Delete from operator ";
        strSql += strWhere;
        if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return 0;
    }
        break;

    case CommonDataType::InsertData :
        strSql =  "Insert Into operator( operatorname,employeeid, operatorsex,operatorright,";
        strSql += "qxgl,feerate,datagl,sysinfo,StartVideo,StartPlate,ConnectDB,exitgl,MonthCard,";
        strSql += "ValueCard,TimeCard,LedInfo,DeviceConfig,SystemSet,CardRightSet,";
        strSql += "DiscountSet,Blacklist,SerialPortSet,PlateRecogSet,SyncTime,PassRecord,FeeRecord,";
        strSql += "DiscountReport,DailyReport,MonthlyReport,YearlyReport,";
        strSql += "operatoraddress,operatorphone ) Values('%1', '%2', '%3', '%4',";
        strSql += " %5, %6, %7, %8, %9, %10, %11, %12, %13, %14, %15, %16,\
                  %17, %18, %19, %20, %21, %22, %23, %24, %25, %26, %27, %28, %29, %30, '%31', '%32' )";
        //strSql += strWhere;

        nCols = 32;
        nRows = lstRows.count( ) / nCols;
        ReplaceSqlParam( nRows, nCols, strSql, lstRows );
        break;
    }

    return nRows;
}

void CLogicInterface::GetStatusInfo( )
{
#ifdef GUI_MAIN_CONTROLER
#endif
    // Monitor
}

void CLogicInterface::GetRealTimeImg( )
{
#ifdef GUI_MAIN_CONTROLER
#endif
    // Monitor
}

void CLogicInterface::GetEnteranceInfo( QString &strKey, QStringList &lstInfo )
{
#ifdef GUI_MAIN_CONTROLER
    GetInfo( );
#endif

    int nAll = 0;
    QString strIno;

    for ( int nIndex = 0; nIndex < nAll; nIndex++ ) {
        strIno = "";
        strIno += "1";
        strIno += "2";
        strIno += "3";
        strIno += "4...";

        lstInfo << strIno;
    }
}

bool CLogicInterface::RecognizeBarcode( QString &strBarcode )
{
    bool bRet = false;

#ifdef GUI_MAIN_CONTROLER
    Recognization( strBarcode );
#endif

    return bRet;
}

void CLogicInterface::ControlCardDispenser( QStringList &lstChannel, bool bOpenGate, QString &strCmd, QStringList& lstResult )
{
    int nCount = lstChannel.count( );
    strCmd = "";
    QString strName;
    QString strPort;
    unsigned int nPort = 0;

    //lstChannel << "Name" << "Port";
    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        strName = lstChannel[ nIndex++ ];
        strPort = lstChannel[ nIndex ]; ;
        nPort = strPort.toUInt( );

        if ( true == bOpenGate ) {
#ifdef GUI_MAIN_CONTROLER
            nRet = SendCmdCardDispenserOpen( m_hMainCtrl, nPort );
#endif
        } else {
#ifdef GUI_MAIN_CONTROLER
            nRet = SendCmdCardDispenserClose( m_hMainCtrl, nPort );
#endif
        }
#ifdef GUI_MAIN_CONTROLER
        if ( P_SUCCESS != nRet ) {
            strName += " 发卡机";
            strName += bOpenGate ? "打开" : "关闭";
            strName += "操作失败！";
            lstResult << strName;
        }
#endif
    }
}

void CLogicInterface::GetAllChannels( QStringList &lstChannel, QString strEntrance /*= Enter or <> Leave*/ )
{
    //select * from parkadmin.roadconerinfo where 0 <> shebeiadr % 2;
    QString strSql = QString( "Select distinct shebeiname, shebeiadr From \
                              roadconerinfo %1" ).arg( strEntrance );
    QString strError;
    if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return;
    }
    GetMysqlDb( ).GetRowData( lstChannel, strError );
}

void CLogicInterface::GetCurrentPark( QStringList &lstPark )
{
#if true
    QString strSql = QString( "select '0', parkindex, parknum, parkname from parkinfo \
                              where parkindex in ( select min( parkindex ) from parkinfo ) \
                              union all \
                              select b.shebeiadr,c.parkindex, c.parknum, c.parkname from treeview a, \
                              roadconerinfo b, parkinfo c where a.shebeiid = b.shebeiid and \
                              b.video1ip = '%1' and a.parentid = c.shebeiid" ).arg(
                              CCommonFunction::GetHostIP( ) );
#endif

   //QString strSql = QString( "select parkindex, parkname, parknum, '0'  from parkinfo" );

    QString strError;
    if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return;
    }
    GetMysqlDb( ).GetRowData( lstPark, strError );
}

void CLogicInterface::GetAllParks( QStringList &lstPark )
{
    QString strSql = "Select parkname,parkindex, parknum,shebeiid From parkinfo \
                     order by parkindex asc";
    QString strError;
    if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return;
    }
    GetMysqlDb( ).GetRowData( lstPark, strError );
}

void CLogicInterface::ControlGate( QStringList &lstChannel, bool bOpenGate, QString &strCmd, QStringList& lstResult )
{
    int nCount = lstChannel.count( );
    strCmd = "";
    QString strName;
    QString strPort;
    unsigned int nPort = 0;

    //lstChannel << "Name" << "Port";
    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        strName = lstChannel[ nIndex++ ];
        strPort = lstChannel[ nIndex ]; ;
        nPort = strPort.toUInt( );

        if ( true == bOpenGate ) {
#ifdef GUI_MAIN_CONTROLER
            nRet = SendCmdPoleUp() m_hMainCtrl, nPort );
#endif
        } else {
#ifdef GUI_MAIN_CONTROLER
            nRet = SendCmdPoleDown( m_hMainCtrl, nPort );
#endif
        }
#ifdef GUI_MAIN_CONTROLER
        if ( P_SUCCESS != nRet ) {
            strName += " 道闸";
            strName += bOpenGate ? "打开" : "关闭";
            strName += "操作失败！";
            lstResult << strName;
        }
#endif
    }
}

void CLogicInterface::GetVehicleSpaceInfo( QString &strParking, QStringList &lstParkingInfo )
{
    lstParkingInfo.clear( );

#ifdef GUI_MAIN_CONTROLER
    GetParkingInfo( strParking, );
#endif

    // lstParkingInfo << "总车位" << "剩余车位" << "月租卡" << "储值卡" << "临时卡" << "条码票";
    lstParkingInfo << "总车位" << "剩余车位" << "月租卡" << "储值卡" << "临时卡" << "条码票";
}

void CLogicInterface::GetAllUsers( QStringList &lstUser )
{
    QString strSql = "Select operatorname, operatorpassword, operatorid, EmployeeID From operator";
    QString strError;
    if ( !GetMysqlDb( ).DbCrud( strSql, strError ) ) {
        return;
    }
    GetMysqlDb( ).GetRowData( lstUser, strError );
}

bool CLogicInterface::PingMysql( )
{
    bool bRet = false;
    bRet = GetMysqlDb( ).PingMysql( );
    return bRet;
}

void CLogicInterface::GetPlateCardInfo( CommonDataType::QPlateCardHash &plateCardHash, QString& strWhere )
{
    QString strSql = "Select a.carcp, a.cardindex From carinfo a, monthCard b "
                     "where a.cardindex = b.cardno and b.cardstate = '启用' " + strWhere;
    QStringList lstRows;

    int nRows = ExecuteSql( strSql, lstRows );
    int nField = 0;
    //plateCardHash.clear( );
    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        nField = nRow * 2;
        QString& strKey = lstRows[ nField++ ];
        plateCardHash.insert( strKey, lstRows[ nField++ ] ); // Key Exist / Replace value
    }
}

void CLogicInterface::GetCanAddress( )
{
    QString strSql = QString ( "Select distinct shebeiadr From roadconerinfo \
                               where video1ip ='%1'" ).arg( CCommonFunction::GetHostIP( ) );
    QStringList lstRows;
    int nRows = ExecuteSql( strSql, lstRows );
    bool bEvent = false;
    char cCan = 0;

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        cCan = ( char ) lstRows[ nRow ].toShort( );
        bEvent = ( 0 != ( cCan % 2 ) ); // 1 2 3 4 5 6

        CCommonFunction::AddAddress( cCan, bEvent );
    }

    //CCommonFunction::AddAddress( char ( 0x3E ), true );
    //CCommonFunction::AddAddress( char ( 0x3F ), false );
}

void CLogicInterface::GetEntityInfo( CommonDataType::QEntityHash& entInfo, QString& strWhere, QString strTmpCard )
{
#if false
    int nInfos = entInfo.keys( ).count( );
    for ( int nInfo = 0; nInfo < nInfos; nInfo++ ) {
        QString strKey = entInfo.keys( )[ nInfo ];
        CommonDataType::PEntityInfo pInfo = entInfo[ strKey ];
        delete pInfo;
    }

    entInfo.clear( );

    Select a.cardno, a.cardstate, a.Inside, a.starttime, a.endtime, b.carmodel, b.carcp, c.shebeiname,
    c.starttime, c.endtime, d.shebeiadr, d.video1ip From Monthcard a, Carinfo b, Cardright c, roadconerinfo d
    Where a.cardno = b.cardindex And a.cardno = c.cardno And c.shebeiname = d.shebeiname // Month
    Select cardno, cardstate, Inside, cardfee, carcp, carmodel From Savecard, Carinfo Where cardno = cardindex // Vale
    Select cardno, cardstate, Inside, carcp, carmodel From Tmpcard, Carinfo Where cardno = cardindex // Time

    Select a.cardno, a.cardstate, a.Inside, a.starttime, a.endtime, b.carmodel, b.carcp
    From parkadmin.Monthcard a, parkadmin.Carinfo b
    Where a.cardno = b.cardindex

    Select c.cardno, c.shebeiname, c.starttime, c.endtime, d.shebeiadr, d.video1ip From  parkadmin.Cardright c, parkadmin.roadconerinfo d
    Where c.shebeiname = d.shebeiname And c.cardno = '10435830' Order by c.cardno;

    QString strSql = "Select a.cardno, a.cardstate, a.Inside, a.EnterMustCard, a.LeaveMustCard, %1 b.carcp, \
                      b.carmodel, c.shebeiname, c.starttime, c.endtime , \
                      d.shebeiadr, d.video1ip \
                      From %2 a, Carinfo b, Cardright c, roadconerinfo d \
                      Where a.cardno = b.cardindex And a.cardno = c.cardno And c.shebeiname = d.shebeiname %3 \
                      Order by a.cardno";
#endif
    QString strCardSql = "Select a.cardno, a.cardstate, a.Inside, a.EnterMustCard, a.LeaveMustCard, %1 From %2 a ";
    QString strChannelSql = "Select c.shebeiname, c.starttime, c.endtime, d.shebeiadr, d.video1ip \
                            From  Cardright c, roadconerinfo d \
                            Where c.shebeiname = d.shebeiname And c.cardno = '%1'";

    QStringList lstRows;
    QStringList lstChannelRows;

    QString tmpSql;
    QString strTableName;
    QString strParams[ 3 ] = { "a.starttime, a.endtime, a.MIMO, b.carcp, b.carmodel", "cardfee, cardfeebz, b.carcp, b.carmodel", "cardfeebz" };

    int nRows = 0;
    int nField = 0;
    int nCols = 6;
    QString strTrue = "1";
    bool bTmpCard = false;

    for ( int nIndex = CommonDataType::MonthlyCard; nIndex <= CommonDataType::TimeCard; nIndex++ ) {
        CCommonFunction::GetTableName( ( CommonDataType::CardType ) nIndex, strTableName );
        tmpSql = strCardSql.arg( strParams[ nIndex ] , strTableName );

        switch ( nIndex ) {
        case CommonDataType::MonthlyCard :
            tmpSql += ", Carinfo b Where a.cardno = b.cardindex ";
            tmpSql += strWhere;
            nCols = 10;
            break;

        case CommonDataType::ValueCard :
            tmpSql += ", Carinfo b Where a.cardno = b.cardindex ";
            tmpSql += strWhere;
            nCols = 9;
            break;

        case CommonDataType::TimeCard :
            bTmpCard = true;
            tmpSql += strTmpCard;  // " Where "
            nCols = 6;
            break;
        }


        lstRows.clear( );
        nRows = ExecuteSql( tmpSql, lstRows );
        qDebug( ) << tmpSql << endl;

        for ( int nRow = 0; nRow < nRows; nRow++ ) {
            nField = nRow * nCols;
            QString& strKey = lstRows[ nField++ ];

            CommonDataType::QEntityHash::iterator item = entInfo.find( strKey );
            bool bFound = ( entInfo.end( ) != item );
            CommonDataType::PEntityInfo pInfo = bFound ? item.value( ) : new CommonDataType::EntityInfo( );
            if ( false == bFound ) { // Skip duplication
                entInfo.insert( strKey, pInfo );
            }

            pInfo->bMIMO = false;
            pInfo->strCardNumber = strKey;
            pInfo->cardType = ( CommonDataType::CardType ) nIndex;
            pInfo->cardStatus = lstRows[ nField++ ];
            pInfo->nInside = lstRows[ nField++ ].toInt( );
            pInfo->MustCard.bEnterMustCard = ( strTrue == lstRows[ nField++ ] );
            pInfo->MustCard.bLeaveMustCard = ( strTrue == lstRows[ nField++ ] );

            switch ( nIndex ) {
            case CommonDataType::MonthlyCard :
                pInfo->MonthDateTime.dtStart = CCommonFunction::String2DateTime( lstRows[ nField++ ] );
                pInfo->MonthDateTime.dtEnd = CCommonFunction::String2DateTime( lstRows[ nField++ ] );
                pInfo->bMIMO =  ( strTrue == lstRows[ nField++ ] );
                break;

            case CommonDataType::ValueCard :
                pInfo->ValueFees.nSurplus = lstRows[ nField++ ].toInt( );
                pInfo->strFeeStd = CCommonFunction::GetFeeStd( lstRows[ nField++ ] );
                break;

            case CommonDataType::TimeCard :
                pInfo->strFeeStd = CCommonFunction::GetFeeStd( lstRows[ nField++ ] );
                break;
            }

            if ( !bTmpCard ) {
                QString& strPlate = lstRows[ nField++ ];
                QString& strModel = lstRows[ nField++ ];
                if ( false == pInfo->carInfo.contains( strPlate ) ) {
                    pInfo->carInfo.insert( strPlate, strModel ); // if key exists, replace value
                } else {
                    pInfo->carInfo[ strPlate ] = strModel; // Update
                }
            }

            tmpSql = strChannelSql.arg( strKey );
            lstChannelRows.clear( );
            int nChannelRows = ExecuteSql( tmpSql, lstChannelRows );

            pInfo->cardRight.clear( );
            for ( int nRowChannel = 0; nRowChannel < nChannelRows; nRowChannel++ ) {
                nField = nRowChannel * 5;

                QString& strName = lstChannelRows[ nField++ ];

                QStringList lstChannel;
                lstChannel << lstChannelRows[ nField++ ]; // StartTime
                lstChannel << lstChannelRows[ nField++ ]; // EndTime
                lstChannel << lstChannelRows[ nField++ ]; // CanAddr
                lstChannel << lstChannelRows[ nField++ ]; // PC IP

                pInfo->cardRight.insertMulti( strName, lstChannel );
            }
        }
    }
}

void CLogicInterface::AddAdminUser( )
{
    QString strSql = "Insert Into operator( operatorname,employeeid, operatorsex,operatorright, ";
    strSql += "qxgl,feerate,datagl,sysinfo,StartVideo,StartPlate,ConnectDB,exitgl,MonthCard,";
    strSql += "ValueCard,TimeCard,LedInfo,DeviceConfig,SystemSet,CardRightSet,";
    strSql += "DiscountSet,Blacklist,SerialPortSet,PlateRecogSet,SyncTime,PassRecord,FeeRecord,";
    strSql += "DiscountReport,DailyReport,MonthlyReport,YearlyReport,";
    strSql += "operatoraddress,operatorphone ) ";

    strSql += "Select '系统管理员', '123456789', '女', '超级用户', '-1', '-1', '-1', '-1', '-1',";
    strSql += "'-1', '-1', '-1', '-1', '-1','-1', '-1', '-1', '-1','-1', '-1', '-1', '-1', '-1',";
    strSql += "'-1', '-1', '-1', '-1', '-1', '-1', '-1', '', '' ";
    strSql += "From DUAL Where Not Exists ( Select operatorright From operator Where operatorright = '超级用户' )";

    ExecuteSql( strSql );
}

CLogicInterface* CLogicInterface::GetInterface( )
{
    if ( 0 == m_pInterface ) {
        m_pInterface = new CLogicInterface( );
    }

    return m_pInterface;
}

void CLogicInterface::ReleaseInterface( )
{
    if ( 0 != m_pInterface ) {
        delete m_pInterface;
        m_pInterface = 0;
    }
}

void CLogicInterface::OperateBlob( QByteArray &byData, bool bSave2Db, CommonDataType::BlobType type, QString &strWhere, bool bHistory  )
{
    QString strError = "";
    QString strSql = "";
    GetBlobSql( strSql, bSave2Db, type, strWhere );
    ConnectHistoryDb( bHistory );

    if ( bSave2Db ) {
        GetMysqlDb( bHistory ).BlobWriteDb( byData, strSql, strError );
    } else {
        GetMysqlDb( bHistory ).BlobReadDb( byData, strSql, strError );
    }

    DisconnectHistoryDb( bHistory );
}

void CLogicInterface::GetBlobSql( QString &strSql, bool bSave2Db, CommonDataType::BlobType type, QString& strWhere )
{
    QString strVideoSql = bSave2Db ? QString( "Update IGNORE stoprd Set %1 = ? %2" ) :
                          QString( "Select %1 From stoprd %2" );
    QString strOwnerSql = bSave2Db ? QString( "Update IGNORE userinfo Set userpic = ? %1" ) :
                          QString( "Select userpic From userinfo %1" );
    QString strCarSql = bSave2Db ? QString( "Update IGNORE carinfo Set carpic = ? %1" ) :
                        QString( "Select carpic From carinfo %1" );
    QString strMGate = bSave2Db ? "Update IGNORE sysinfo Set %1 = ? %2" : "Select %1 From sysinfo %2";
    QString strGarageSql = bSave2Db ? QString( "Update IGNORE garageingarage Set Image = ? %1" ) :
                        QString( "Select Image From garageingarage %1" );

    QString strTimeInImg = "Select invideo1 from tmpcardIntime %1";

    switch ( type ) {
    case CommonDataType::BlobVehicleIn1 :
        strSql = strVideoSql.arg( "invideo1", strWhere );
        break;

    case CommonDataType::BlobVehicleIn2 :
        strSql = strVideoSql.arg( "invideo2", strWhere );
        break;

    case CommonDataType::BlobVehicleIn3 :
        strSql = strVideoSql.arg( "invideo3", strWhere );
        break;

    case CommonDataType::BlobVehicleIn4 :
        strSql = strVideoSql.arg( "invideo4", strWhere );
        break;

    case CommonDataType::BlobVehicleOut1 :
        strSql = strVideoSql.arg( "outvideo1", strWhere );
        break;

    case CommonDataType::BlobVehicleOut2 :
        strSql = strVideoSql.arg( "outvideo2", strWhere );
        break;

    case CommonDataType::BlobVehicleOut3 :
        strSql = strVideoSql.arg( "outvideo3", strWhere );
        break;

    case CommonDataType::BlobVehicleOut4 :
        strSql = strVideoSql.arg( "outvideo4", strWhere );
        break;

    case CommonDataType::BlobOwner :
        strSql = strOwnerSql.arg( strWhere );
        break;

    case CommonDataType::BlobVehicle :
        strSql = strCarSql.arg( strWhere );
        break;

    case CommonDataType::BlobManualGate1 :
        strSql = strMGate.arg( "infopic1", strWhere );
        break;

    case CommonDataType::BlobManualGate2 :
        strSql = strMGate.arg( "infopic2", strWhere );
        break;

    case CommonDataType::BlobManualGate3 :
        strSql = strMGate.arg( "infopic3", strWhere );
        break;

    case CommonDataType::BlobManualGate4 :
        strSql = strMGate.arg( "infopic4", strWhere );
        break;

   case CommonDataType::BlobTimeInImg :
        strSql = strTimeInImg.arg( strWhere );
        break;

    case CommonDataType::BlobGarageImg :
         strSql = strGarageSql.arg( strWhere );
         break;
    }

    strSql += " LIMIT 1";
}

void CLogicInterface::OperateBlob( QString& strFile, bool bSave2Db, CommonDataType::BlobType type, QString& strWhere, bool bHistory )
{
    QString strError = "";
    QString strSql = "";
    GetBlobSql( strSql, bSave2Db, type, strWhere );
    qDebug( ) << Q_FUNC_INFO << strSql << endl;

    ConnectHistoryDb( bHistory );
    if ( bSave2Db ) {
        GetMysqlDb( bHistory ).BlobWriteDb( strFile, strSql, strError );
    } else {
        GetMysqlDb( bHistory ).BlobReadDb( strFile, strSql, strError );
    }

    DisconnectHistoryDb( bHistory );
}
