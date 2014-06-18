#include "qdataparserthread.h"

QDataParserThread::QDataParserThread(QObject *parent) :
    QThread(parent)
{
    byDataToken = DATA_TOKEN;
    setObjectName( QString( "[Data Parser Thread ID = %1]" ).arg( qrand( ) ) );
}

QDataParserThread::~QDataParserThread( )
{
    FreeSocketByteArray( tcpSocketByteArrayHash );
    FreeSocketByteArray( udpSocketByteArrayHash );
}

void QDataParserThread::FreeSocketByteArray( QSocketByteArrayHash &hash )
{
    foreach ( const QByteArray* pByteArray, hash.values( ) ) {
        delete pByteArray;
    }

    hash.clear( );
}

void QDataParserThread::PostEvent( QThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void QDataParserThread::SetDataDispatcher( QDataDispactherThread *pThread )
{
    //qDebug( ) << objectName( ) << ":" << pThread->objectName( ) << endl;
    pDataDispatcher = pThread;
}

void QDataParserThread::PostTCPDataEvent( QTcpSocket* pSocket, QByteArray &byTcpData )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadParser, QThreadEvent::EventTCPData );

    pEvent->SetByteArray( byTcpData );
    pEvent->SetPeerSocket( pSocket );

    PostEvent( pEvent );
}

void QDataParserThread::PostUDPDataEvent( QByteArray &byUdpData )
{
    Q_UNUSED( byUdpData )
}

void QDataParserThread::InitializeSubThread( )
{
    pDbController = DatabaseController::GetController( );
}

QDataParserThread* QDataParserThread::CreateThread( QObject *pParent )
{
    qDebug( ) << Q_FUNC_INFO << endl;

    QDataParserThread* pThread = new QDataParserThread( pParent );

    pThread->start( );
    pThread->moveToThread( pThread );

    return pThread;
}

void QDataParserThread::SendLog( QString& strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void QDataParserThread::run( )
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QDataParserThread::customEvent( QEvent *event )
{
    QThreadEvent* pEvent = ( QThreadEvent* ) event;
    QThreadEvent::EventType evtType = ( QThreadEvent::EventType ) pEvent->type( );

    if ( QThreadEvent::EventTCPData == evtType ) {
        TcpParse( pEvent );
    } else if ( QThreadEvent::EventUDPData == evtType ) {
        UdpParse( pEvent );
    }
}

void QDataParserThread::TcpParse( QThreadEvent* pEvent )
{
    QTcpSocket* pSocket = pEvent->GetPeerSocket( );
    QByteArray& pEventByteArray = pEvent->GetByteArray( );

    QByteArray* pData = tcpSocketByteArrayHash.value( pSocket );

    if ( 0 == pData ) {
        pData = new QByteArray( ); // Free in Destructor
        tcpSocketByteArrayHash.insert( pSocket, pData );
    }

    pData->append( pEventByteArray ); // Shared Memory

    bool bRet = false;
    do {
        bRet = ParseData( pSocket, *pData );
    } while ( bRet );
}

void QDataParserThread::UdpParse( QThreadEvent* pEvent )
{
    Q_UNUSED( pEvent )
}

quint32 QDataParserThread::GetUInt32Value( const char *pData )
{
    return qFromBigEndian< quint32 >( *( ( quint32* ) pData ) );
}

void QDataParserThread::DispatchData( QTcpSocket* pSocket, qint32 nPackageType, QByteArray &byDbData )
{
    //qDebug( ) << pSocket->thread( )->objectName( ) << ":"
    //          << objectName( ) << ":"
    //          << pDataDispatcher->objectName( ) << endl;
    pDbController->PostDispactherData( pDataDispatcher, pSocket, nPackageType, byDbData );
}

bool QDataParserThread::ParseData( QTcpSocket* pSocket, QByteArray &data )
{
    //  ASCII      +     quint32  +  quint32   +   enum ( qint32 ) +    QString
    // [DataToken] + [DataLength] + [Reserved] + [DataPackageType] + [HTTPMessage]
    // [DataToken] : Value[StreetRoad]
    // [DataLength] : Whole Message Length
    // [Reserved] : Extention use for future
    // [DataPackageType] : Data Package Type
    // [HTTPMessage] : ShiHongXing Define

    bool bRet = false;
    QByteArray& byToken = byDataToken;

    qint32 nIndex = data.indexOf( byToken );
    quint32 nTokenSize = byToken.length( );
    quint32 nCuurentStreamSize = data.length( ); // Current Stream Length

    if ( -1 == nIndex ) { // No Token
        qDebug( ) << "No Token" << endl;
        data.clear( );
        return bRet;
    } else if ( 0 < nIndex ) {
        ;//data.remove( 0, nIndex ); // Remove Token
    }

    quint32 nDataSize = sizeof ( qint32 );
    if ( nCuurentStreamSize <= ( nTokenSize + nDataSize * 3 ) ) {
        return bRet;
    }

    const char* pData = data.data( ) + nTokenSize;
    quint32 nPackageTotalSize = GetUInt32Value( pData ); // MessageSize = ProtocolHeadSize + BodySize
    quint32 nReserved = GetUInt32Value( pData + nDataSize );
    qint32 nPackageType = GetUInt32Value( pData + 2 * nDataSize );

    if ( nCuurentStreamSize < nPackageTotalSize ) { // Whole Package
        return bRet;
    }

    qint32 nExtraSize = nTokenSize + nDataSize * 3;
    qint32 nDataLen = nPackageTotalSize - nExtraSize;

    data.remove( 0, nExtraSize );
    QByteArray byBody = data.left( nDataLen );
    //QString strBody = QString( byBody );
    //qDebug( ) << "Received : " << strBody << endl;

    DispatchData( pSocket, nPackageType, byBody );

    data.remove( 0, nDataLen );
    bRet = ( data.length( ) > nExtraSize );

    return bRet;
}
