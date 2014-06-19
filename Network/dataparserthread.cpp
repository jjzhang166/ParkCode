#include "dataparserthread.h"
#include <windows.h>
#include "netprocessdata.h"
#include <QApplication>

CDataParserThread::CDataParserThread(qint32 nThreadPool, bool bTcp, QObject *parent) :
    QThread(parent)
{
    bTcpParser = bTcp;
    svrThreadPool = new QThreadPool( this );
    svrThreadPool->setMaxThreadCount( nThreadPool );
    svrThreadPool->setExpiryTimeout( -1 );
}

CDataParserThread::~CDataParserThread( )
{
    if ( NULL != svrThreadPool ) {
        delete svrThreadPool;
    }
}

CDataParserThread* CDataParserThread::GetInstance( qint32 nThreadPool, bool bTcp )
{
    CDataParserThread* pThreadInstance = new CDataParserThread( nThreadPool, bTcp );
    pThreadInstance->moveToThread( pThreadInstance );
    pThreadInstance->start( );

    return pThreadInstance;
}

void CDataParserThread::ReleaseInstance( )
{

}

void CDataParserThread::PostDataMessage( QByteArray& data, quint32 nSocket )
{
    CParserEvent* pEvent = new CParserEvent( data, nSocket, CParserEvent::ParserData );
    PostEvent( pEvent );
}

void CDataParserThread::PostDataMessage( QByteArray& data )
{
    CParserEvent* pEvent = new CParserEvent( data, CParserEvent::ParserData );
    PostEvent( pEvent );
}

void CDataParserThread::PostDataMessage( QByteArray& data, QString& strIP )
{
    CParserEvent* pEvent = new CParserEvent( data, strIP, CParserEvent::ParserData );
    PostEvent( pEvent );
}

void CDataParserThread::PostReleaseMessage( quint32 nSocket )
{
    CParserEvent* pEvent = new CParserEvent( nSocket, CParserEvent::ParserRelease );
    PostEvent( pEvent );
}

void CDataParserThread::PostEvent( CParserEvent* pEvent )
{
    qApp->postEvent( this, pEvent );
}

void CDataParserThread::run( )
{
    exec( ); // Event loop
}

void CDataParserThread::TcpParse( quint32 nSocket, QByteArray& byData, QString& strIP, CParserEvent::ParserEvent event  )
{
    QByteArray* pPreData = peerData.value( nSocket );
    bool bRet = true;

    switch ( event ) {
    case CParserEvent::ParserData :
        if ( NULL != pPreData ) {
            byData.insert( 0, *pPreData );
            pPreData->clear( ); // 前次余数据
        } else {
            pPreData = new QByteArray( );
            peerData.insert( nSocket, pPreData );
        }

        do {
            bRet = ParseData( byData, strIP );
        } while ( bRet );

        pPreData->append( byData );
        break;

    case CParserEvent::ParserRelease :
        if ( NULL != pPreData ) {
            peerData.remove( nSocket );
            delete pPreData;
        }
        break;
    }
}

void CDataParserThread::UdpParse( QByteArray& byData, QString& strIP, CParserEvent::ParserEvent event )
{
    bool bRet = true;

    switch ( event ) {
    case CParserEvent::ParserData :
        byData.insert( 0, byUdpData );
        byUdpData.clear( ); // 前次余数据

        do {
            bRet = ParseData( byData, strIP );
        } while ( bRet );

        byUdpData.append( byData );
        break;

    case CParserEvent::ParserRelease :
        break;
    }
}

bool CDataParserThread::ParseData( QByteArray &data, QString& strIP )
{
    bool bRet = false;

    QByteArray byToken = QString( "FutureInternet" ).toAscii( );
    qint32 nIndex = data.indexOf( byToken );
    qint32 nToken = byToken.length( );
    qint32 nLen = data.length( ); // Current Stream Length

    if ( -1 == nIndex ) {
        data.clear( );
        return bRet;
    } else if ( 0 < nIndex ) {
        data.remove( 0, nIndex ); // Not Token
    }

    qint32 nDataSize = sizeof ( quint32 );
    if ( nLen <= ( nToken + nDataSize ) ) {
        return bRet;
    }


    QByteArray byDataLen = data.mid( nToken, nDataSize );
    const char* pLen = byDataLen.data( );
    quint32 nTotalLen = *( ( quint32* ) pLen );
    qint32 nTotal = ntohl( nTotalLen ); // Message Size Token + DataSize + MessageSize

    if ( nLen < nTotal ) { // Whole Package
        return bRet;
    }

    qint32 nExtraSize = nToken + nDataSize;
    data.remove( 0, nExtraSize );

    qint32 nDataLen = nTotal - nExtraSize;
    char* pData = new char[ nDataLen + 1 ];
    memcpy( pData, data.data( ), nDataLen );
    pData[ nDataLen ] = '\0';

    CNetProcessData* processor  = CNetProcessData::GetInstance( pData, nDataLen );

    if ( !strIP.isEmpty( ) ) {
        processor->SetUdpIP( strIP );
    }
    svrThreadPool->start( processor );

    data.remove( 0, nDataLen );
    bRet = ( data.length( ) > nExtraSize );

    return bRet;
}

void CDataParserThread::customEvent( QEvent *e )
{
    CParserEvent::ParserEvent event = ( CParserEvent::ParserEvent ) e->type( );
    CParserEvent* eParser = ( CParserEvent* ) e;
    QByteArray& byData = eParser->GetData( );
    quint32 nSocket = eParser->GetSocket( );
    QString& strIP = eParser->GetUdpIP( );

    if ( bTcpParser ) {
        TcpParse( nSocket, byData, strIP, event );
    } else {
        UdpParse( byData, strIP, event );
    }
}
