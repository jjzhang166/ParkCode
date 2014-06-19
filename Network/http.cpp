#include "http.h"
#include <QDebug>
#if false
HTTP Request/ Response mode
QNetworkAccessManager / QNetworkRequest / QNetworkReply  readyRead() signal
Communicate with Webserver
#endif
CHttp::CHttp(QObject *parent) :
    QObject(parent)
{
    pTextCodec = NULL;
    manager.setParent( this );
    connect( &manager, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( MngrFinished( QNetworkReply* ) ) );
}

void CHttp::SetTextCodec( QTextCodec *pCodec )
{
    pTextCodec = pCodec;
}

void CHttp::GetReplyData( )
{
    qDebug( ) << "GetReplyData" << endl;
    QNetworkReply *reply = qobject_cast< QNetworkReply* >( sender( ) );
    GetByteData( reply ).append( reply->readAll( ) );
}

void CHttp::ProcessResponse( QNetworkReply *reply )
{
    switch ( reply->operation( ) ) { // Operation Method
    case QNetworkAccessManager::HeadOperation :
        HandleHeadResponse( reply );
        break;
    case QNetworkAccessManager::GetOperation :
        HandleGetResponse( reply );
        break;
    case QNetworkAccessManager::PutOperation :
        HandlePutResponse( reply );
        break;
    case QNetworkAccessManager::PostOperation :
        HandlePostResponse( reply );
        break;
    case QNetworkAccessManager::DeleteOperation :
        HandleDeleteResponse( reply );
        break;
    case QNetworkAccessManager::CustomOperation :
        HandleCustomResponse( reply );
        break;
    case QNetworkAccessManager::UnknownOperation :
        HandleUnknownResponse( reply );
        break;
    }
}

QByteArray& CHttp::GetByteData( QNetworkReply *reply )
{
    return byResponse[ reply->operation( ) ];
}

void CHttp::HandleGetResponse( QNetworkReply* reply )
{
    QByteArray& byData = GetByteData( reply ); // Document
    //QString strMsg = pTextCodec->toUnicode( byData );
    // Get  charset=utf-8 by Http head
    QString strMsg = QString::fromUtf8( byData.data( ) );
    emit NotifyMessage( strMsg );
}

bool CHttp::Trysync( )
{
    return mutex.tryLock( );
}

void CHttp::HandlePutResponse( QNetworkReply* reply )
{
    QByteArray& byData = GetByteData( reply ); // Document
    QString strMsg( byData );
    emit NotifyMessage( strMsg );
}

void CHttp::HandlePostResponse( QNetworkReply* reply )
{
    QByteArray& byData = GetByteData( reply ); // Document
    QString strMsg( byData );
    emit NotifyMessage( strMsg );
}

void CHttp::HandleDeleteResponse( QNetworkReply* reply )
{
    QByteArray& byData = GetByteData( reply ); // Document
    QString strMsg( byData );
    emit NotifyMessage( strMsg );
}

void CHttp::HandleHeadResponse( QNetworkReply* reply )
{
    QByteArray& byData = GetByteData( reply ); // Document
    QString strMsg( byData );
    emit NotifyMessage( strMsg );
}

void CHttp::HandleCustomResponse( QNetworkReply* reply )
{
    QByteArray& byData = GetByteData( reply ); // Document
    QString strMsg( byData );
    emit NotifyMessage( strMsg );
}

void CHttp::HandleUnknownResponse( QNetworkReply* reply )
{
    QByteArray& byData = GetByteData( reply ); // Document
    QString strMsg( byData );
    emit NotifyMessage( strMsg );
}

void CHttp::HttpError( QNetworkReply::NetworkError code )
{
    QString strMsg = "";
    QNetworkReply *reply = qobject_cast< QNetworkReply* >( sender( )  );
    CNetCommFunction::GetErrorMsg( strMsg, code, reply );
    strMsg = "Http :\r\n" + strMsg;
    emit NotifyMessage( strMsg );
    qDebug( ) << "HttpError" << endl;

    GetByteData( reply ).clear( );
}

void CHttp::ConnectReplyEvent( QNetworkReply *reply )
{
    connect( reply, SIGNAL( finished( ) ), this, SLOT( ReplyFinished( ) ) );
    connect( reply, SIGNAL( readyRead( ) ), this, SLOT( GetReplyData( ) ) );
    connect( reply, SIGNAL( error( QNetworkReply::NetworkError ) ),
             this, SLOT( HttpError( QNetworkReply::NetworkError) ) );
    connect( reply, SIGNAL( downloadProgress( qint64, qint64 ) ), this, SLOT( DownloadProcess( qint64, qint64 ) ) );
    connect( reply, SIGNAL( uploadProgress( qint64, qint64 ) ), this, SLOT( UploadProcess( qint64, qint64 ) ) );
}

void CHttp::MngrFinished( QNetworkReply *reply )
{
    qDebug( ) << "MngrFinished" << endl;
}

void CHttp::Sync( bool bLock )
{
    bLock ? mutex.lock( ) : mutex.unlock( );
}

void CHttp::ReplyFinished( )
{
    qDebug( ) << "ReplyFinished" << endl;
    QNetworkReply *reply = qobject_cast< QNetworkReply* >( sender( )  );
    ProcessResponse( reply );
    reply->deleteLater( );
}

void CHttp::HttpGet( QString &strUrl )
{
    QNetworkReply *reply = manager.get( CreateRequest( strUrl ) );
    ConnectReplyEvent( reply );
}

void CHttp::HttpPut( QString& strUrl, QIODevice* pData )
{
    QNetworkReply *reply = manager.put( CreateRequest( strUrl ), pData );
    ConnectReplyEvent( reply );
}

void CHttp::HttpPut( QString& strUrl, const QByteArray& data )
{
    QNetworkReply *reply = manager.put( CreateRequest( strUrl ), data );
    ConnectReplyEvent( reply );
}

void CHttp::HttpPost( QString& strUrl, QIODevice* pData )
{
    QNetworkReply *reply = manager.post( CreateRequest( strUrl ), pData );
    ConnectReplyEvent( reply );
}

void CHttp::HttpPost( QString& strUrl, const QByteArray& data )
{
    QNetworkReply *reply = manager.post( CreateRequest( strUrl ), data );
    ConnectReplyEvent( reply );
}

void CHttp::HttpDelete( QString& strUrl )
{
    QNetworkReply *reply = manager.deleteResource( CreateRequest( strUrl ) );
    ConnectReplyEvent( reply );
}

void CHttp::HttpHead( QString& strUrl )
{
    QNetworkReply *reply = manager.head( CreateRequest( strUrl ) );
    ConnectReplyEvent( reply );
}

QNetworkRequest CHttp::CreateRequest( QString &strUrl )
{
    QUrl url( strUrl );
    return QNetworkRequest( url );
}

void CHttp::DownloadProcess( qint64 bytesReceived, qint64 bytesTotal )
{
    qDebug( ) << "DownloadProcess" << endl;
}

void CHttp::UploadProcess( qint64 bytesSent, qint64 bytesTotal )
{
    qDebug( ) << "UploadProcess" << endl;
}
