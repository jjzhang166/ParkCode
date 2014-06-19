#include "mgmtthread.h"
#include  "Network/netprocessdata.h"
#include "sendrequest.h"

//CManipulateMessage
//CMyTcpServer
//CTcpClient

CMgmtThread* CMgmtThread::pReceiverThread = NULL;
CMgmtThread* CMgmtThread::pSenderThread = NULL;

CMgmtThread::CMgmtThread( bool bSender, QObject *parent) :
    QThread(parent), bClient( bSender )
{
    pTcpClient = NULL;
    pTcpServer = NULL;
    pMySQL = NULL;
    pUdpClient = NULL;
    pUdpServer = NULL;

    nClientTimer = 0;
    nServerTimer = 0;

    pMySQL = new CMySqlDatabase( );
    pTxtCodec = CCommonFunction::GetTextCodec( );

    if ( bClient ) {
        pTcpClient = new CTcpClient( this );
        pUdpServer = new QUdpSocket( this );
        //connect( pTcpClient, SIGNAL( readyRead( ) ), this, SLOT( PeerData( ) ) );  git pull RemoteRepositoryAlias branchName
        connect( pUdpServer, SIGNAL( readyRead( ) ), this, SLOT( UdpPeerData( ) ) );
        connect( pTcpClient, SIGNAL( NotifyMessage( QString ) ), this, SLOT( NotifyMsg( QString ) ) );
        CCommonFunction::GetPath( strPath, CommonDataType::PathSnapshot );
        nInterval = config.GetInterval( false );
        if ( 0 < nInterval ) {
            nClientTimer = startTimer( nInterval * 60 * 1000 );
        }

        pUdpServer->bind( QHostAddress::Any, config.GetMgmtSvrPort( ), QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint );
    } else {
        pTcpServer = new CTcpDispatcher( this );
        //pUdpClient = new QUdpSocket( this );
        connect( pTcpServer, SIGNAL( NotifyMessage( QString ) ), this, SLOT( NotifyMsg( QString ) ) );
        nInterval = config.GetInterval( true );
        if ( 0 < nInterval ) {
            nServerTimer = startTimer( nInterval * 60 * 1000 );
        }
    }

    connect( this, SIGNAL( finished( ) ), this, SLOT( ThreadExit( ) ) );
}

void CMgmtThread::ThreadExit( )
{
    if ( 0 != nClientTimer ) {
        killTimer( nClientTimer );
    }

    if ( 0 != nServerTimer ) {
        killTimer( nServerTimer );
    }

    if ( NULL != pMySQL ) {
        delete pMySQL;
    }

    if ( NULL != pTcpClient ) {
        delete pTcpClient;
    }

    if ( NULL != pTcpServer ) {
        delete pTcpServer;
    }

    if ( NULL != pUdpClient ) {
        delete pUdpClient;
    }

    if ( NULL != pUdpServer ) {
        delete pUdpServer;
    }

    CNetProcessData::ReleaseResource( );

    delete this;
}

void CMgmtThread::customEvent( QEvent *event )
{

}

CMgmtThread* CMgmtThread::GetThread( bool bSender )
{
    if ( bSender && NULL == pSenderThread ) {
        pSenderThread = new CMgmtThread( bSender );
        pSenderThread->moveToThread( pSenderThread );
        pSenderThread->start( );
    } else if ( !bSender && NULL == pReceiverThread )  {
        pReceiverThread = new CMgmtThread( bSender  );
        pReceiverThread->moveToThread( pReceiverThread );
        pReceiverThread->start( );
    }

    return bSender ? pSenderThread : pReceiverThread;
}

void CMgmtThread::NotifyMsg( QString strMsg )
{
    qDebug( ) << strMsg << endl;
}

quint32 CMgmtThread::GetCommonHeaderSize( )
{
    return sizeof ( Mgmt::CommonHeader );
}

Mgmt::CommonHeader& CMgmtThread::GetCommonHeader( const char *pData )
{
    return *( Mgmt::PCommonHeader ) pData;
}

quint32 CMgmtThread::GetContentHeaderSize( )
{
    return sizeof ( Mgmt::ContentHeader );
}

Mgmt::ContentHeader& CMgmtThread::GetContentHeader( const char *pData )
{
    return *( ( Mgmt::PContentHeader ) ( pData + GetCommonHeaderSize( ) ) );
}

const char* CMgmtThread::GetBody( const char *pData )
{
    return ( const char* ) ( pData + GetCommonHeaderSize( ) + GetContentHeaderSize( ) );
}

void CMgmtThread::SetPacketType( Mgmt::CommonHeader &sHeader, Mgmt::ePacketType eType )
{
    sHeader.dgType.nRequestType = ( 1 << eType );
}

Mgmt::ePacketType CMgmtThread::GetPacketType( Mgmt::CommonHeader &sHeader )
{
    int nType = 0;

    for ( quint32 nIndex = 0; nIndex < sizeof ( sHeader.dgType ); nIndex++ ) {
        if ( sHeader.dgType.nRequestType & ( 1 << nIndex ) ) {
            nType = nIndex;
            break;
        }
    }

    return ( Mgmt::ePacketType ) nType;
}

void CMgmtThread::UdpPeerData( ) // Get Request
{
    QUdpSocket* pUdpServer = qobject_cast< QUdpSocket* > ( sender( ) );
    QByteArray byData;
    quint64 nReadLen = 0;
    quint64 nDataLen = 0;
    int nPreSize = 0;

    while ( pUdpServer->hasPendingDatagrams( ) ) { // Sender Wait for a moment
        nDataLen = pUdpServer->pendingDatagramSize( );
        nPreSize = byData.count( );
        byData.resize( nPreSize + nDataLen );
        nReadLen += pUdpServer->readDatagram( byData.data( ), nDataLen );
    }

    if ( GetCommonHeaderSize( ) + GetContentHeaderSize( ) <  nReadLen ) {
        ProcessRequest( byData.data( ) );
    }
}

void CMgmtThread::PeerData( ) // Server --> Client
{
    CTcpClient* pSocket = qobject_cast< CTcpClient* >( sender( ) );
    quint64 nDataLen = pSocket->bytesAvailable( );

    QByteArray* pByteArray = pSocket->GetData( );
    quint64 nPreSize = pSocket->GetCurrentDataSize( );
    quint64 nCurDataSize = nPreSize + nDataLen;
    if ( 0 == pSocket->GetMaxDataSize( ) || GetCommonHeaderSize( ) > nCurDataSize ) {
        pByteArray->resize( nCurDataSize );
    }

    char* pSegData = ( char* ) ( ( quint64 ) pByteArray->data( ) + nPreSize );
    quint64 nDataRetLen = pSocket->read( pSegData, nDataLen );
    pSocket->SetCurrentDataSize( nDataRetLen );

    if ( strlen( HANDSHAKE )== nDataLen ) {
        qDebug( ) << HANDSHAKE << endl;
        pSocket->Clear( );
        return;
    }

    if ( 0 == pSocket->GetMaxDataSize( ) && GetCommonHeaderSize( ) <= nCurDataSize ) {
        Mgmt::CommonHeader& commHeader = GetCommonHeader( pSegData );
        pSocket->SetMaxDataSize( commHeader.nPacketSize );
        pByteArray->resize( commHeader.nPacketSize );
    }

#ifndef QT_NO_DEBUG
    if ( nDataRetLen != nDataLen ) {
        qDebug( ) << "Read Client : " << pSocket->peerAddress( ).toString( ) << " error" << endl;
    }
#endif

    if ( pSocket->GetCurrentDataSize( ) == pSocket->GetMaxDataSize( ) ) {
        const char* pData = pByteArray->data( );
        ProcessRequest( pData );
        pSocket->Clear( );

        //pSocket->write( HANDSHAKE );
    }
}

void CMgmtThread::ProcessTableRequest( const char *pData )
{
    QString strTableName( GetContentHeader( pData ).cName );
    pData = GetBody( pData );
    QString strWhere( pData );
    SendTableData( true, strWhere, strTableName );
}

void CMgmtThread::ProcessHandshakeRequest( const char *pData )
{

}

void CMgmtThread::ProcessRequest( const char *pData ) // Client Process Server Request
{
    Mgmt::CommonHeader& commHeader = GetCommonHeader( pData );

    switch ( GetPacketType( commHeader ) ) {
    case Mgmt::PacketTable :
        ProcessTableRequest( pData );
        break;

    case Mgmt::PacketOther :
        break;

    case Mgmt::PacketHandshake :
        ProcessHandshakeRequest( pData );
        break;
    }
}

void CMgmtThread::ClientRun( )
{
    QString strIP;

    config.GetMgmtSvrIP( strIP );
    QHostAddress hostAddr( strIP );
    pTcpClient->Connect2Server( hostAddr, config.GetMgmtSvrPort( ) );
    exec( ); // Message Loop / Event Loop
}

void CMgmtThread::ServerRun( )
{
    if ( pTcpServer->InitServer( config.GetMgmtSvrPort( ), 100, 1 ) ) {
        exec( );
    }
}

void CMgmtThread::run( )
{
    bClient ? ClientRun( ) : ServerRun( );
}

CPeerSocket* CMgmtThread::GetPeerSocket( const QString &strKey )
{
    CPeerSocket* pPeer = NULL;


    QHash< QString, CPeerSocket* >* pPeerSocketHash = NULL;
    pTcpServer->GetPeerSocketHash( pPeerSocketHash );

    if ( NULL == pPeerSocketHash || pPeerSocketHash->isEmpty( ) ) {
        return pPeer;
    }

    QList< QString > lstKeys = pPeerSocketHash->keys();

    for ( int nIndex = 0; nIndex < lstKeys.count( ); nIndex++ ) {
        const QString& strValue = lstKeys.at( nIndex );
        if ( !strValue.startsWith(  strKey ) ) {
            continue;
        }

        pPeer = pPeerSocketHash->value( strValue );
        break;
    }

    return pPeer;
}

bool CMgmtThread::SendFilterData( QUdpSocket *pUdpSocket, QString &strWhere, const QString &strTable, const QString& strIP )
{
    bool bRet = false;

    QByteArray byData = pTxtCodec->fromUnicode( strWhere );
    int nDataLen = byData.count( );

    Mgmt::DispatcherData data;
    memset( &data, 0, sizeof ( data ) );

    SetPacketType( data.CommHeader, Mgmt::PacketTable );
    strcpy( data.auxHeader.cntHeader.cName, strTable.toAscii( ).data( ) );
    data.auxHeader.cntHeader.nDataLen = nDataLen;

    int nCommHeader = GetCommonHeaderSize( );
    int nAuxHeader = GetContentHeaderSize( );
    data.CommHeader.nPacketSize = nDataLen + nCommHeader + nAuxHeader + 1;

    byData.insert( 0, ( char* ) &data.auxHeader.cntHeader, nAuxHeader );
    byData.insert( 0, ( char* ) &data.CommHeader, nCommHeader );
    byData.append( '\0' );

    QHostAddress hostAddr( strIP );
    quint16 nPort = config.GetMgmtSvrPort( );

    if ( QAbstractSocket::ConnectedState == pUdpSocket->state( ) ) {
        pUdpSocket->disconnectFromHost( );
    }
    pUdpSocket->connectToHost( hostAddr, nPort );
    bRet =( ( qint64 ) nDataLen == pUdpSocket->writeDatagram( byData, hostAddr, nPort ) );
    if ( !pUdpSocket->flush( ) ) {
        pUdpSocket->waitForBytesWritten( );
    }

    return bRet;
}

bool CMgmtThread::SendFilterData( CPeerSocket *pPeer, QString &strWhere, const QString& strTable )
{
    bool bRet = false;

    QByteArray byData = pTxtCodec->fromUnicode( strWhere );
    int nDataLen = byData.count( );

    Mgmt::DispatcherData data;
    memset( &data, 0, sizeof ( data ) );

    SetPacketType( data.CommHeader, Mgmt::PacketTable );
    strcpy( data.auxHeader.cntHeader.cName, strTable.toAscii( ).data( ) );
    data.auxHeader.cntHeader.nDataLen = nDataLen;

    int nCommHeader = GetCommonHeaderSize( );
    int nAuxHeader = GetContentHeaderSize( );
    data.CommHeader.nPacketSize = nDataLen + nCommHeader + nAuxHeader + 1;

    byData.insert( 0, ( char* ) &data.auxHeader.cntHeader, nAuxHeader );
    byData.insert( 0, ( char* ) &data.CommHeader, nCommHeader );
    byData.append( '\0' );

    bRet =( ( qint64 ) nDataLen == pPeer->write( byData ) );
    if ( !pPeer->flush( ) ) {
        pPeer->waitForBytesWritten( );
    }

    return bRet;
}

void CMgmtThread::UdpSendPeerRequest( QUdpSocket* pUdpSocket, QStringList &lstRows, const QString &strTable )
{
    if ( 0 > lstRows.count( ) || strTable.isEmpty( ) ) {
        return;
    }

    QString strSeperator = "','";
    QString strWhere = "'" + lstRows.join( strSeperator ) + "'";
    QStringList& lstClientIP = config.GetClientIP( );

    foreach ( const QString strIP, lstClientIP ) {
        SendFilterData( pUdpSocket, strWhere, strTable, strIP );
        //Sleep( 10000 );
    }
}

void CMgmtThread::SendPeerRequest( QStringList &lstRows, const QString &strTable )
{
    if ( 0 > lstRows.count( ) || strTable.isEmpty( ) ) {
        return;
    }

    QString strSeperator = "','";
    QString strWhere = "'" + lstRows.join( strSeperator ) + "'";
    QStringList& lstClientIP = config.GetClientIP( );
    CPeerSocket* pPeer = NULL;

    foreach ( const QString strIP, lstClientIP ) {
        pPeer = GetPeerSocket( strIP );
        if ( NULL == pPeer ) {
            continue;
        }

        SendFilterData( pPeer, strWhere, strTable );
        //Sleep( 60000 );
    }
}

void CMgmtThread::PeerRequest( QUdpSocket* pUdpSocket ) // Server Request
{
    QStringList& lstTables = config.GetAllTables( true );
    QString strSql = "";
    QString strError = "";
    QStringList lstRows;
    bool bRet = false;

    foreach ( const QString strTable, lstTables ) {
        config.GetFilterSQL( strSql, strTable );

        if ( strSql.isEmpty( ) ) {
            continue;
        }

        bRet = ConnectMySQL( );

        if ( !bRet ) {
            continue;
        }

        if ( pMySQL->DbCrud( strSql, strError ) && 0 <= pMySQL->GetRowData( lstRows, strError ) ) {
            //SendPeerRequest( lstRows, strTable );
            UdpSendPeerRequest( pUdpSocket, lstRows, strTable );
            Sleep( 10000 );
        }

#ifdef QT_NO_DBUS
        if ( !strError.isEmpty( ) ) {
            qDebug( ) << strError << endl;
        }
#endif
    }
}

bool CMgmtThread::ConnectMySQL( )
{
     static bool bFirst = true;
     bool bRet = true;

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

     return bRet;
}

void CMgmtThread::SendTableData( bool bRequest, QString& strWhere, QString& strTableName )
{
    QStringList& lstTables = config.GetAllTables( bRequest );
    QString strSql = "";
    QString strError;
    bool bRet = false;
    QString strFile = "";
    QString strStopRd = "STOPRD";
    QString strFeeRd = "FEERD";

    foreach ( const QString strTable, lstTables ) {
        config.GetSQL( bRequest, strSql, strTable );

        if ( strSql.isEmpty( ) || ( bRequest && strTable != strTableName )) {
            continue;
        }

        strFile = strPath + strTable;
        if ( bRequest ) {
            strSql = strSql.arg( strTable, strWhere, strFile );
        } else {
            if ( strStopRd == strTable.toUpper( ) ) {
                strSql = strSql.arg( strTable, strWhere, strFile );
            } else {
                strSql = strSql.arg( strTable, strFile );
            }
        }

        bRet = ConnectMySQL( );

        if ( !bRet ) {
            continue;
        }

        if ( pMySQL->DbCrud( strSql, strError ) ) {
            if ( strStopRd == strTable.toUpper( ) ) {
                UpdateStopRdTransferFlag( strWhere );
            } else if ( strFeeRd == strTable.toUpper( ) ) {
                UpdateFeeRdTransferFlag( );
            }

            SendTableData( strFile, strTable );
            Sleep( 5000 );
            QFile::remove( strFile );
        }

#ifdef QT_NO_DBUS
        if ( !strError.isEmpty( ) ) {
            qDebug( ) << strError << endl;
        }
#endif
    }
}

void CMgmtThread::GetFeeRdWhere( QString &strWhere )
{
    strWhere = " Where Transfered = 0 ";
}

void CMgmtThread::GetStopRdWhere( QString &strWhere )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSysSet );
    bool bMode = pSet->value( "CommonSet/MonthlyWorkMode", false ).toBool( );

    strWhere = " Where ( Transfered = 0 and MayDelete = 3 ) ";
    if ( bMode ) {
        strWhere += "  or ( cardkind = '���⿨'  and Transfered = 0  and MayDelete = 1 ) ";
    }
}

void CMgmtThread::UpdateStopRdTransferFlag( QString &strWhere )
{
    QString strSql = "Update Stoprd set Transfered  = 1 "  + strWhere;
    QString strError;
    pMySQL->DbCrud( strSql, strError );
    qDebug( ) << strError << endl;
}

void CMgmtThread::UpdateFeeRdTransferFlag(  )
{
    QString strSql = "Update Feerd set Transfered  = 1 where Transfered = 0";
    QString strError;
    pMySQL->DbCrud( strSql, strError );
    qDebug( ) << strError << endl;
}

void CMgmtThread::timerEvent( QTimerEvent *event )
{
    if ( nClientTimer == event->timerId( ) ) {
        QString strWhere = "";
        QString strTable = "";

        GetStopRdWhere( strWhere );
        SendTableData( false, strWhere, strTable );

        qDebug( ) << "Mgmt Client Timer" << endl;
    } else if ( nServerTimer == event->timerId( ) ) {
        //PeerRequest( );
        QThreadPool::globalInstance( )->start( CSendRequest::GetTask( this ) );
        qDebug( ) << "Mgmt Server Timer" << endl;
    }
}

bool CMgmtThread::SendTableData( QString& strFile, const QString& strTable  )
{
    bool bRet = false;
    static QFile* pFile = NULL;
    if ( NULL == pFile ) {
        pFile = new QFile( );
    }

    pFile->setFileName( strFile );
    if ( !pFile->open( QIODevice::ReadWrite ) ) {
        return bRet;
    }

    QByteArray byData = pFile->readAll( );
    int nDataLen = byData.count( );
    pFile->close( );

    if ( 0 == nDataLen ) {
        return bRet;
    }

    NetTransport::DispatcherData data;
    memset( &data, 0, sizeof ( data ) );

    data.CommHeader.dgType.PacketMgmtData = 1;
    strcpy( data.auxHeader.mgmtHeader.cName, strTable.toAscii( ).data( ) );
    data.auxHeader.mgmtHeader.nDataLen = nDataLen;

    quint16* pType = ( quint16* ) &data.auxHeader.mgmtHeader.mgmtType;
    *pType = ( quint16 ) ( 1 << ( quint16 ) NetTransport::MgmtTable );

    int nCommHeader = sizeof ( data.CommHeader );
    int nAuxHeader = sizeof ( data.auxHeader.mgmtHeader );
    data.CommHeader.nDataLen = nDataLen + nCommHeader + nAuxHeader;

    byData.insert( 0, ( char* ) &data.auxHeader.tabHeader, nAuxHeader );
    byData.insert( 0, ( char* ) &data.CommHeader, nCommHeader );

    bRet =( ( quint64 ) nDataLen == pTcpClient->SendData( byData ) );

    return bRet;
}
