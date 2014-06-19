#include "netprocessdata.h"
#include "../Database/mssqlserver.h"
#include "parkintranet.h"
#include "netclient.h"
#include <QApplication>
#ifdef PARKDATARECEIVER_APP
#include "../Heartbeat/heartbeatthread.h"
#else
#include "Heartbeat/heartbeatthread.h"
#endif

#include "ftp.h"
#include "../Database/dbheartbeat.h"

 QVector< QString > CNetProcessData::vecSql;
 QVector< QString > CNetProcessData::vecHBCmd;
 QSettings* CNetProcessData::pSettings = NULL;

 QFile* CNetProcessData::pFile = NULL;
 CMySqlDatabase* CNetProcessData::pMySQL = NULL;
 QHash< QString, QString > CNetProcessData::hashMgmtSql;
 QMultiHash< QString, QString > CNetProcessData::hashImgRequest;
 quint16 CNetProcessData::nUdpPort = 0;

#ifndef PARKDATARECEIVER_APP
 extern
#endif
 CHeartbeatThread* g_pHeartbeatThread;
#ifndef PARKDATARECEIVER_APP
 extern
#endif
 CFtp* g_pFtp;

CNetProcessData::CNetProcessData( const char* pData, quint64 nLen ) :
    pDatagram( pData ), nDataLen( nLen )
{
    setAutoDelete( true );
    GetSettings ( );
}

CNetProcessData* CNetProcessData::GetInstance( const char *pData, quint64 nLen )
{
    return new CNetProcessData( pData, nLen );
}

void CNetProcessData::GetSettings( )
{
    if ( NULL == pSettings ) {
        pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    }
}

void CNetProcessData::run( )
{
    if ( NULL == pDatagram ) {
        return;
    }

    ProcessData( pDatagram, nDataLen );

    delete[ ] pDatagram;
    pDatagram = NULL;
}

void CNetProcessData::ProcessData( const char* pData, quint64 nLen )
{
    // Data Header
    NetTransport::CommonHeader& commHeader = processMsg.GetCommonHeader( pData );
#ifndef QT_NO_DEBUG
    if ( nLen != commHeader.nDataLen ) {
        qDebug( ) << "Udp Data Lost" << endl;//Lost Data
    }
#endif

    QString strInfo;

    switch ( processMsg.GetPacketType( commHeader.dgType ) ) {
    case NetTransport::PacketTable :
        ProcessTableData( pData );
        strInfo = "ProcessTableData( pData )";
        break;

    case NetTransport::PacketImage :
        ProcessImageData( pData );
        strInfo = "ProcessImageData( pData )";
        break;

    case NetTransport::PacketHeartbeat :
        ProcessHeartbeatData( pData );
        strInfo = "ProcessHeartbeatData( pData )";
        break;

    case NetTransport::PacketSvrMsg :
        ProcessSvrMsgData( pData );
        strInfo = "ProcessSvrMsgData( pData )";
        break;

    case NetTransport::PacketCltMsg :
        ProcessCltMsgData( pData );
        strInfo = "ProcessCltMsgData( pData )";
        break;

   case NetTransport::PacketMgmtData :
        ProcessMgmtData( pData );
        strInfo = "ProcessMgmtData( pData )";
        break;
    }

    qDebug( ) << strInfo << endl;
}

bool CNetProcessData::WriteFile( const char *pData, const QString& strPath, quint32 nDataLen )
{
    bool bRet = false;

    if ( NULL == pFile ) {
        pFile = new QFile( );
    }

    pFile->setFileName( strPath );
    if ( !pFile->open( QIODevice::ReadWrite | QIODevice::Truncate ) ) {
        return bRet;
    }

    quint64 nRet = pFile->write( pData, nDataLen );
    pFile->close( );

    bRet = ( nRet == nDataLen );
    return bRet;
}

void CNetProcessData::GetAllMgmtSql( bool bRequest )
{
    QString strSeperator = "@";
    QStringList lstTables = pSettings->value( QString( "Mgmt/%1Tables" ).arg( bRequest ? "Request" : "" ), "" ).toString( ).split( strSeperator );
    QString strSql = "";

    foreach ( const QString strTable, lstTables ) {
        strSql = pSettings->value( QString( "Mgmt/%1Load" ).arg( strTable ), "" ).toString( );

        if ( !strSql.isEmpty( ) ) {
            strSql.replace( strSeperator, "," );
            hashMgmtSql.insert( strTable, strSql );
        }
    }
}

void CNetProcessData::GetTableSql( QString &strSql, QString& strPath, const char *pName )
{
    QString strKey( pName );
    strSql = hashMgmtSql.value(  strKey ).arg( strPath, strKey );
}

void CNetProcessData::WriteDb( QString &strPath, const char *pName )
{
    if ( NULL == pMySQL ) {
        pMySQL = new CMySqlDatabase( );
        GetAllMgmtSql( true );
        GetAllMgmtSql( false);
    }

    bool bRet = true;
    static bool bFirst = true;

    if ( bFirst || !pMySQL->PingMysql( ) ) {
        QStringList lstParams;
        CCommonFunction::ConnectMySql( lstParams );
        int nCounter = 0;

        while ( 6 > nCounter ) {
            nCounter++;
            bRet = pMySQL->DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );
            bFirst = false;

            if ( bRet ) {
                break;
            } else {
                Sleep(10000 );
                continue;
            }
        }
    }

    if ( !bRet ) {
        return;
    }

    QString strError;
    QString strSql;

    GetTableSql( strSql, strPath, pName );
    if ( !strSql.isEmpty( ) ) {
        pMySQL->DbCrud( strSql, strError );
        QFile::remove( strPath );
    }

#ifdef QT_NO_DBUS
    if ( !strError.isEmpty( ) ) {
        qDebug( ) << strError << endl;
    }
#endif
}

void CNetProcessData::WriteData2Db( const char* pData, const char* pName, quint32 nDataLen )
{
    QString strPath;
    CCommonFunction::GetPath( strPath, CommonDataType::PathSnapshot );
    strPath += pName;

    if ( !WriteFile( pData, strPath, nDataLen ) ) {
        return;
    }

    WriteDb( strPath, pName );
}

void CNetProcessData::ProcessMgmtData( const char *pData )
{
    NetTransport::MgmtHeader& mgmtHeader = processMsg.GetMgmtHeader( pData );
    const char* pBody = processMsg.GetMgmtBody( pData );
    NetTransport::eMgmtData mgmtType = processMsg.GetMgmtType( mgmtHeader.mgmtType );

    if ( 0 > mgmtHeader.nDataLen ) {
        mgmtHeader.nDataLen = 0;
    }

    switch ( mgmtType ) {
    case NetTransport::MgmtTable :
        WriteData2Db( pBody, mgmtHeader.cName, mgmtHeader.nDataLen );
        break;

    case NetTransport::MgmtOtherData :
        break;
    }
}

void CNetProcessData::SendImgRequestData( QByteArray &byData )
{
    NetTransport::DispatcherData data;
    memset( &data, 0, sizeof ( data ) );

    data.CommHeader.dgType.PacketSvrMsg = 1;
    quint16* pType = ( quint16* ) &data.auxHeader.svrHeader.svrMsgType;
    *pType = ( quint16 ) ( 1 << ( quint16 ) NetTransport::SvrGetInOutImg );

    int nCommHeader = sizeof ( data.CommHeader );
    int nAuxHeader = sizeof ( data.auxHeader.svrHeader );
    data.CommHeader.nDataLen = byData.count( ) + nCommHeader + nAuxHeader;

    byData.insert( 0, ( char* ) &data.auxHeader.imgHeader, nAuxHeader );
    byData.insert( 0, ( char* ) &data.CommHeader, nCommHeader );
}

void CNetProcessData::ProcessImgRequest( const char *pData )
{
    QString strBody( pData );
    QList< QString> lstRequest = hashImgRequest.values( strBody );
    if ( 0 == lstRequest.length( ) ) {
        return;
    }

    QHostAddress addr( strUdpIP );
    udpSocket = new QUdpSocket( );
    QByteArray byToken = QString( "FutureInternet" ).toAscii( );
    qint32 nMsgLen = sizeof ( quint32 );
    quint32 nTotal = 0;

    foreach ( const QString& str, lstRequest ) {
        hashImgRequest.remove( strBody, str );

        QByteArray byData = CCommonFunction::GetTextCodec( )->fromUnicode( str );
        SendImgRequestData( byData );

        nTotal = byToken.length( ) + nMsgLen + byData.length( );
        nTotal = htonl( nTotal );

        const char* pTotal = ( const char* ) &nTotal;
        byData.insert( 0, pTotal, nMsgLen );
        byData.insert( 0, byToken );

        //udpSocket->connectToHost( addr, nUdpPort );
        udpSocket->writeDatagram( byData, addr, nUdpPort );
    }

    delete udpSocket;
    udpSocket = NULL;
}

void CNetProcessData::ProcessHeartbeatData( const char *pData )
{
    NetTransport::HeartbeatHeader& hbHeader = processMsg.GetHeartbeatHeader( pData );
    const char* pBody = processMsg.GetHeartbeatBody( pData );
    NetTransport::eHeartbeat hbType = processMsg.GetHeartbeatType( hbHeader.hbType );

    if ( NetTransport::HbImgRequest == hbType ) {
        ProcessImgRequest( pBody );
        return;
    }

    if ( vecHBCmd.count( ) <= hbType ) {
        return;
    }

    QString strBody( pBody );
    QStringList lstBody;
    QString& strHBCmd = vecHBCmd[ hbType ];
    //CMsSqlServer& dbServer = CMsSqlServer::CreateSingleton( );
    QString strTmp = "";

    lstBody = strBody.split( "," );

    switch ( hbType ) {
    case NetTransport::HbImgRequest:
        break;

    case NetTransport::HbClientIP :
         // ParkID,IP,Port
        if  ( 3 != lstBody.count( ) ) {
            break;
        }

        strTmp = strHBCmd.arg( lstBody[ 0 ], lstBody[ 1 ], lstBody[ 2 ] );
        //dbServer.ExecuteSql( strTmp );
        break;

    case NetTransport::HbNetState :
        // ParkID,IP,DateTime
        if  ( 3 != lstBody.count( ) ) {
            break;
        }

        QDateTime dt = QDateTime::fromMSecsSinceEpoch( lstBody[ 2 ].toULongLong( ) );
        QString strDt = "";
        CCommonFunction::DateTime2String( dt, strDt );
        strTmp = strHBCmd.arg( lstBody[0], lstBody[ 1 ],  strDt );
        //dbServer.ExecuteSql( strTmp );
        break;
    }

    if ( !strTmp.isEmpty( ) ) {
        CDbHeartbeat::GetInstance( )->PostSql( strTmp );
    }
}

void CNetProcessData::ProcessTableData( const char* pData )
{
    NetTransport::TableHeader& tabHeader = processMsg.GetTableHeader( pData );
    const char* pBody = processMsg.GetTableBody( pData );
    NetTransport::eTableType tabType = processMsg.GetTableType( tabHeader.tabType );

    if ( vecSql.count( ) <= tabType ) {
        return;
    }

    QString& strSql = vecSql[ tabType ];
    QStringList lstCols;
    int nRealCol = 0;

    QString strData( pBody );
    QStringList lstRows = strData.split( ROW_SEPERATOR );
    int nRealRow = lstRows.count( );

#ifndef QT_NO_DEBUG
    if ( nRealRow != tabHeader.nRows ) {
        qDebug( ) << "Udp Row Data Lost" << endl;//Lost Data
    }
#endif

    CMsSqlServer& dbServer = CMsSqlServer::CreateSingleton( );
    CBulkInsert& bulkInsert = dbServer.GetBulkInsert( ); // New Instance
    QVariantList* lstVariant = bulkInsert.GetVariantList( tabHeader.nCols );


    for ( int nRow = 0; nRow < nRealRow; nRow++ ) {
        QString strCols = lstRows.at( nRow );
        lstCols = strCols.split( COL_SEPERATOR );
        nRealCol = lstCols.count( );

#ifndef QT_NO_DEBUG
        if ( nRealCol!= tabHeader.nCols ) {
            qDebug( ) << "Udp Col Data Lost" << endl;//Lost Data
        }
#endif

        for ( int nCol = 0; nCol < nRealCol; nCol++ ) {
            lstVariant[ nCol ] << lstCols.at( nCol );
        }
    }

    dbServer.BulkInsert( strSql, bulkInsert );
}

void CNetProcessData::ProcessImageData( const char* pData )
{
    NetTransport::ImageHeader& imgHeader = processMsg.GetImageHeader( pData );
    const char* pBody = processMsg.GetImageBody( pData );
    NetTransport::eImageType imgType = processMsg.GetImageType( imgHeader.imgType );

    QString strPath = "";
    QString strFile = "";
    QDir dir;
    QFile file;
    QString strDateTime = QDateTime::fromMSecsSinceEpoch( imgHeader.nMSecsSinceEpoch ).toString( "yyyyMMddHHmmss" );


    switch ( imgType ) {
    case NetTransport::ImgOut :
    case NetTransport::ImgIn :
        strPath = QString ( "Images/%1/%2/%3/%4/" ).arg( QString::number( imgHeader.nParkID ), QString::number( imgHeader.nCardID ),
                                                                                          imgHeader.cPlate, QString::number( imgType ) );
        strFile = QString( "%1.JPG" ).arg( strDateTime );
        break;

    case NetTransport::ImgCar :
        break;

    case NetTransport::ImgOwner :
        break;
    }

    if ( strPath.isEmpty( ) ) {
        return;
    }

    if ( !dir.exists( strPath ) ) {
        dir.mkpath( strPath );
    }

    if ( strFile.isEmpty( ) ) {
        return;
    }

    strFile  = strPath + strFile;
    file.setFileName( strFile );
    if ( file.exists( ) ) {
        file.remove( );
    }

    if ( !file.open( QIODevice::ReadWrite ) ) {
        return;
    }

    file.write( pBody, imgHeader.nImgSize );
    file.flush( );
    file.close( );
}

void CNetProcessData::GetInOutImage( QStringList &lstData )
{
    CFtpEvent* pFtpEvent = new CFtpEvent( CFtpEvent::FtpPut );
    pFtpEvent->SetParams( lstData );
    QApplication::postEvent( g_pFtp, pFtpEvent );

    QString& strDateTime = lstData[ 4 ];
    static QString strFormat1 = "yyyy-MM-dd HH:mm:ss";
    static QString strFormat2 = "yyyyMMddHHmmss";
    static QString strFormat3 = "%1_%2_%3_%4_%5.JPG";
    strDateTime = QDateTime::fromString( strDateTime, strFormat1 ).toString( strFormat2 );

    QString strSvrFile = strFormat3.arg( lstData[ 0 ], lstData[ 1 ], lstData[ 2 ], lstData[ 3 ], strDateTime );

    CHbEvent* pHbEvent = new CHbEvent( CHbEvent::HbImgLog );
    pHbEvent->SetImgLog( strSvrFile );
    QApplication::postEvent( g_pHeartbeatThread, pHbEvent );
}

void CNetProcessData::WebBrowserRequest( const QString &strParkID, const QString &strRequest )
{
    hashImgRequest.insertMulti( strParkID, strRequest );
}

void CNetProcessData::ProcessWebBrowserRequest( const char* pData )
{
    NetTransport::SvrMsgHeader& svrHeader = processMsg.GetSvrMsgHeader( pData );
    const char* pBody = processMsg.GetSvrMsgBody( pData );
    NetTransport::eSvrMsg svrType = processMsg.GetSvrMsgType( svrHeader.svrMsgType );

    QString strBody( pBody );
    QStringList lstData = strBody.split( "|" ); // Seperator

    switch ( svrType ) {
    case NetTransport::SvrAlert :
        if ( 6 > lstData.count( ) ) {
            break;
        }

        WebBrowserRequest( lstData.at( 0 ), strBody );
        break;

    case NetTransport::SvrGetInOutImg :
        WebBrowserRequest( lstData.at( 0 ), strBody );
        break;
    }
}

void CNetProcessData::ProcessSvrMsgData( const char *pData )
{
    QString strAppName = qApp->applicationName( );
    if ( strAppName.contains( "parkdatareceiver" ) ) {
        // GetImg
        ProcessWebBrowserRequest( pData );
        return;
    }

    NetTransport::SvrMsgHeader& svrHeader = processMsg.GetSvrMsgHeader( pData );
    const char* pBody = processMsg.GetSvrMsgBody( pData );
    NetTransport::eSvrMsg svrType = processMsg.GetSvrMsgType( svrHeader.svrMsgType );

    QString strBody( pBody );
    QStringList lstData = strBody.split( "|" ); // Seperator
    //// PARKID / bool( 1 : plate 0 : cardid)  / Plate | CardID / IOFlag / DateTime / Alert

    switch ( svrType ) {
    case NetTransport::SvrAlert :
        if ( 6 > lstData.count( ) ) {
            break;
        }

        // Broadcast alert message
        if ( "_" != lstData[ 5 ] ) { // 0 1 2 3
            CNetwork::Singleton( ).BroadcastDatagram( CommonDataType::DGSvrAlert, lstData );
        }
#ifndef QT_NO_DEBUG
        qDebug( ) << strBody << endl;
#endif

        // Get  an image
        GetInOutImage( lstData );
        break;

    case NetTransport::SvrGetInOutImg :
        GetInOutImage( lstData );
        break;
    }
}

void CNetProcessData::ProcessCltMsgData( const char *pData ) // Forward to center server
{
    NetTransport::CommonHeader& commHeader = processMsg.GetCommonHeader( pData );
    NetTransport::CltMsgHeader& cltHeader = processMsg.GetCltMsgHeader( pData );
    NetTransport::eCltMsg cltType = processMsg.GetCltMsgType( cltHeader.cltMsgType );

    QByteArray byBody( pData, commHeader.nDataLen ); // Deep copy of the string data
    int nCommSize = sizeof ( NetTransport::CommonHeader );
    int nCltSize = sizeof ( NetTransport::CltMsgHeader );

    byBody.remove( nCommSize, nCltSize );

    NetTransport::CommonHeader& forwardHeader = processMsg.GetCommonHeader( byBody.data( ) );
    forwardHeader.dgType.PacketCltMsg = 0;
    forwardHeader.nDataLen -= nCltSize;
    bool bTcp = true;

    switch ( cltType ) {
    case NetTransport::CltTable :
        forwardHeader.dgType.PacketTable = 1;
        break;

    case NetTransport::CltImg :
        forwardHeader.dgType.PacketImage = 1;
        break;

    case NetTransport::CltHeartbeat :
        forwardHeader.dgType.PacketHeartbeat = 1;
        bTcp = false;
        break;
    }

    // Forward data
    CHbEvent* pEvent = new CHbEvent( CHbEvent::HbForward );
    pEvent->SetByteArrayData( byBody, bTcp );
    QApplication::postEvent( g_pHeartbeatThread, pEvent );
    //CNetClient& netClient = CNetClient::GetInstance( bTcp, true );
    //netClient.SocketSendData( bTcp ? CNetClient::ClientTCPClient : CNetClient::ClientUDPClient, byBody );
}

void CNetProcessData::ReleaseResource( )
{
    CMsSqlServer::CreateSingleton( ).DestroySingleton( );

    if ( NULL != pFile ) {
        delete pFile;
    }

    if ( NULL != pMySQL ) {
        delete pMySQL;
    }
}

void CNetProcessData::SetUdpIP( QString &strIP )
{
    strUdpIP = strIP;
}

void CNetProcessData::GetCommonParams(  )
{
    CMsSqlServer::CreateSingleton( );
    GetSettings ( );
    vecSql.clear( );

    QString strParam;
    QString strKey = "SQL/Table%1";
    int nIndex = 0;

    QString strPort = pSettings->value( "Database/UdpPort", "6011" ).toString( );
     nUdpPort = strPort.toUInt( );

    int TableCount = pSettings->value( "SQL/TableCount", TABLE_COUNT ).toInt( );
    for ( nIndex = 0; nIndex < TableCount; nIndex++ ) {
        strParam = pSettings->value( strKey.arg( nIndex ), "" ).toString( );
        if ( !strParam.isEmpty( ) ) {
            strParam.replace( "@", "," );
            vecSql.append( strParam );
        }
    }

    int CmdCount = pSettings->value( "Heartbeat/CmdCount", HBCMD_COUNT ).toInt( );
    strKey = "Heartbeat/HBCmd%1";
    for ( nIndex = 0; nIndex < CmdCount; nIndex++ ) {
        strParam = pSettings->value( strKey.arg( nIndex ), "" ).toString( );
        if ( !strParam.isEmpty( ) ) {
            strParam.replace( "$", "," );
            vecHBCmd.append( strParam );
        }
    }
}
