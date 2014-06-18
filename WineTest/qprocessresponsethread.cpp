#include "qprocessresponsethread.h"
#include "qresponseevent.h"
#include <windows.h>
#include <QFile>
#include <QApplication>
#include <QDateTime>

QProcessResponseThread* QProcessResponseThread::pThreadInstance = NULL;

QProcessResponseThread::QProcessResponseThread(QObject *parent) :
    QThread(parent)
{
}

QProcessResponseThread* QProcessResponseThread::GetSingleton( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QProcessResponseThread( );
        pThreadInstance->moveToThread( pThreadInstance );
        pThreadInstance->start( );
    }

    return pThreadInstance;
}

void QProcessResponseThread::run( )
{
    exec( );
}

void QProcessResponseThread::customEvent( QEvent *e )
{
    if ( NULL == e ) {
        return;
    }

    QResponseEvent* pEvent = ( QResponseEvent* ) e;

    if ( pEvent->type( )  == QEvent::User ) {
        byResponseData.append( pEvent->GetReponseData( ) );
        bool bRet = false;

        do {
            bRet = ParseMultipleResponseData( byResponseData );
        } while ( bRet );
    }
}

bool QProcessResponseThread::ParseMultipleResponseData( QByteArray &byResponse )
{
    bool bRet = false;
    qint32 nIndex = byResponse.indexOf( Protocol::byToken );

    if ( -1 == nIndex ) {
        byResponse.clear( );
        return bRet; // No Head
    }

    if ( 0 < nIndex) { // Remove
        byResponse.remove( 0, nIndex );
    }

    qint32 nLen = Protocol::nTokenLength;
    if ( nLen == byResponse.length( ) ) {
        return bRet;
    }

    nLen += sizeof ( quint8 ); // MessageType
    nLen += sizeof ( quint32 ); // TcpStreamLength

    if ( nLen >= byResponse.length( ) ) {
        return bRet;
    }

    quint32 nTotal = GetStreamLength( byResponse );
    if ( nTotal > byResponse.length( ) ) {
        return bRet;
    }

    switch ( GetMessageType( byResponse ) ) {
    case Protocol::ResponseBallotSenseState :
        //nLen += 2;
        break;

    case Protocol::ResponseGateSenseState :
        //nLen += 2;
        break;

    case Protocol::ResponseInfraredState :
        //nLen += 2;
        break;

    case Protocol::ResponsePlateData :
        //nLen += 2;
        break;

    case Protocol::ResponseActiveSend :
        //nLen += 2;
        break;
    }

    ParseResponseData( byResponse );

    byResponse.remove( 0, nTotal ); // Remove one Request

    bRet = ( 0 < byResponse.length( ) );
    return bRet;
}

void QProcessResponseThread::ParseResponseData( QByteArray &byData )
{
    ProcessResponse( byData );
}

void QProcessResponseThread::ProcessResponse( QByteArray &byStream )
{
    QByteArray byToken = GetToken( byStream );
    if ( byToken != Protocol::byToken ) {
        return;
    }

    Protocol::RequestType nMessageType = ( Protocol::RequestType ) GetMessageType( byStream );

    switch ( nMessageType ) {
    case Protocol::ResponseBallotSenseState :
        ProcessBallotSenseResponse( byStream );
        break;

    case Protocol::ResponseGateSenseState :
        ProcessGateSenseResponse( byStream );
        break;

    case Protocol::ResponseInfraredState :
        ProcessInfraredResponse( byStream );
        break;

    case Protocol::ResponsePlateData :
        ProcessPlateResponse( byStream );
        break;

    case Protocol::ResponseActiveSend :
        ProcessActiveSendResponse( byStream );
        break;
    }
}

void QProcessResponseThread::ProcessBallotSenseResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "A地感地址：%1\nA地感状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );

    AppendResponse( strMsg );
}

void QProcessResponseThread::ProcessActiveSendResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "地址：%1\n状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );

    AppendResponse( strMsg );
}

void QProcessResponseThread::ProcessGateSenseResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "B地感地址：%1\nB地感状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );

    AppendResponse( strMsg );
}

void QProcessResponseThread::ProcessInfraredResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "红外地址：%1\n红外状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );

    AppendResponse( strMsg );
}

void QProcessResponseThread::ProcessPlateResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    qint32 nIndex = 0;
    quint8 nAddress = byBody.at( nIndex );

    nIndex += sizeof ( quint8 );
    QByteArray byDateTime = byBody.mid( nIndex, Protocol::nDateTimeLength );
    QString strDateTime ( byDateTime );

    nIndex += Protocol::nDateTimeLength;
    quint8 nConfidence = byBody.at( nIndex );

    nIndex += sizeof ( quint8 );
    quint8 nPlateByteCount = byBody.at( nIndex );

    nIndex += sizeof ( quint8 );
    quint32 nPictureByteCount =*( quint32*  ) ( byBody.data( ) + nIndex );
    nPictureByteCount = ntohl( nPictureByteCount );

    nIndex += sizeof ( quint32 );
    QByteArray byPlate = byBody.mid( nIndex, nPlateByteCount );
    QString strPlate( byPlate );

    QString strMsg;
    strMsg = QString( "车牌地址：%1\n获取时间：%2\n可信度：%3\n车牌：%4" ).arg(
                        QString::number( nAddress ),
                        strDateTime,
                        QString::number( nConfidence ),
                        strPlate );

    AppendResponse( strMsg );

    nIndex += nPlateByteCount;
    QByteArray byPicture = byBody.mid( nIndex, nPictureByteCount );
    QFile file;
    QString strSingle = QApplication::applicationDirPath( ) + QString( "/snapshot/A%1D%2C%3P%4-%5.jpg" ).arg( QString::number( nAddress ),
                                                                     strDateTime,
                                                                     QString::number( nConfidence ),
                                                                     strPlate, QString::number( QDateTime::currentDateTime().toMSecsSinceEpoch( ) ) );
    QString strFile = strSingle;

    file.setFileName( strFile );
    bool bRet = file.open( QIODevice::ReadWrite | QIODevice::Truncate );
    if ( !bRet ) {
        return;
    }

    file.write( byPicture );
    file.close( );

    emit PlateImg( strFile );
    //QPixmap pixmap( strFile );
    //ui->lblPic->setPixmap( pixmap );
}

void QProcessResponseThread::AppendResponse( QString &strMsg )
{
    emit Response( strMsg );
}

QByteArray QProcessResponseThread::GetToken( QByteArray& byStream )
{
    return byStream.mid( 0, Protocol::nTokenLength );
}

quint8 QProcessResponseThread::GetMessageType( QByteArray& byStream )
{
    return ( quint8 ) byStream.at( Protocol::nTokenLength );
}

QByteArray QProcessResponseThread::GetBody( QByteArray &byStream )
{
    return byStream.right( byStream.length( ) - Protocol::nHeadLength );
}

quint32 QProcessResponseThread::GetStreamLength( QByteArray& byStream )
{
    QByteArray byLen = byStream.mid( Protocol::nTokenLength + sizeof ( quint8 ), sizeof( quint32 ) );
    quint32* pLen = ( quint32* ) byLen.data( );

    return ntohl( *pLen );
}
