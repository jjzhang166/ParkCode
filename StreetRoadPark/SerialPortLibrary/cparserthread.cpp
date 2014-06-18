#include "cparserthread.h"

#define CMD_LENGTH_DETECTOR_RECEIVER    ( qint32 ) 15
#define CMD_LENGTH_QUERY_RECEIVER       ( qint32 ) 28

CParserThread::CParserThread( QString& strParkID, QObject *parent ) :
    QThread(parent), strComParkID( strParkID )
{
    pDbController = DatabaseController::GetController( );
    pConfig = CComConfigurator::GetConfigurator( );
    byVerInfo = pConfig->GetReceiverVerInfo( );
    setObjectName( QString( "[Data Parser Thread ID = %1]" ).arg( qrand( ) ) );
    cStart = '$';
    char cEnd[ ] = { 0x0D, 0x0A, 0x00 };
    byEnd.append( cEnd, sizeof ( cEnd ) / sizeof ( char ) );
}

CParserThread* CParserThread::CreateThread( QString& strParkID, QObject* parent )
{
    qDebug( ) << Q_FUNC_INFO << endl;

    CParserThread* pThread = new CParserThread( strParkID, parent );

    pThread->start( );
    pThread->moveToThread( pThread );

    return pThread;
}

void CParserThread::run( )
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );
    Initialize( );
    exec( );
}

void CParserThread::PostData( QByteArray &byData )
{

    CComThreadEvent* pEvent = CComThreadEvent::CreateThreadEvent( CComThreadEvent::ThreadParser, CComThreadEvent::EventParseData );
    pEvent->SetByteArrayData( byData );
    //pEvent->SetComParkID( strParkID );
    PostEvent( pEvent );
}

void CParserThread::customEvent( QEvent * pEvent )
{
    CComThreadEvent* pThreadEvent = ( CComThreadEvent* ) pEvent;
    CComThreadEvent::EventType evtType = ( CComThreadEvent::EventType ) pEvent->type( );
    //QString& strComX = pThreadEvent->GetComParkID( );

    bool bRet = false;

    if ( CComThreadEvent::EventParseData == evtType ) {
        byPortData.append( pThreadEvent->GetByteArrayData( ) );

        do {
            bRet = ParseData( byPortData );
        } while ( bRet );
    }
}

void CParserThread::Initialize( )
{

}

void CParserThread::PostEvent( CComThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void CParserThread::SendLog( QByteArray& byCmd, bool bStatic )
{
    if ( !bStatic && !pConfig->GetDisplayDynamicLog( ) ) {
        return;
    }

    QString strLog( byCmd );
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void CParserThread::SendLog(QString &strLog, bool bStatic )
{
    if ( !bStatic && !pConfig->GetDisplayDynamicLog( ) ) {
        return;
    }

    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

bool CParserThread::GetVersionInfo( QByteArray &byData )
{
    bool bRet = true;
    qint32 nIndex = byData.indexOf( byVerInfo );

    if ( -1 == nIndex ) {
        return bRet;
    }

    SendLog( byVerInfo, false );
    byData.remove( nIndex, byVerInfo.length( ) );

    bRet = ( CMD_LENGTH_DETECTOR_RECEIVER <= byData.length( ) );

    return bRet;
}

bool CParserThread::ParseData( QByteArray &byData )
{
    bool bRet = false;
    qint32 nEndLen = byEnd.length( );
    qint32 nTotal = byData.length( );

    if ( nTotal < CMD_LENGTH_DETECTOR_RECEIVER ) {
        return bRet;
    }

    if ( !GetVersionInfo( byData ) ) {
        return bRet;
    }

    qint32 nStartIndex = byData.indexOf( cStart );
    if ( -1 == nStartIndex ) {
        byData.clear( );
        return bRet;
    } else if ( 0 < nStartIndex ) {
        byData.remove( 0, nStartIndex );
    }

    qint32 nEndIndex = byData.indexOf( byEnd );
    if ( -1 == nEndIndex ) {
        return bRet;
    }

    QByteArray byCmd = byData.left( nEndIndex + nEndLen );
    qint32 nCmdLen = byCmd.length( );
    byData.remove( 0, nCmdLen );

    qDebug( ) << QString( byCmd.toHex( ) ) << endl;
    byCmd.remove( nEndIndex, byEnd.length( ) );

    switch ( nCmdLen ) {
    case CMD_LENGTH_DETECTOR_RECEIVER :
        byCmd.remove( 0, 1 );
        pDbController->PostComPortData( 0, byCmd, strComParkID );
        byCmd.insert( 0, "Detector Info : " );
        break;

    case CMD_LENGTH_QUERY_RECEIVER :
        byCmd.insert( 0, "Query Info : " );
        break;
    }

    SendLog( byCmd, false );
    bRet = ( CMD_LENGTH_DETECTOR_RECEIVER <= byData.length( ) );

    return bRet;
}
