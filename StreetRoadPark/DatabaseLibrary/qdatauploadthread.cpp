#include "qdatauploadthread.h"

QDataUploadThread* QDataUploadThread::pThreadInstance = NULL;

QDataUploadThread::QDataUploadThread(QObject *parent) :
    QThread(parent)
{
    pUrl = NULL;
    setObjectName( "Data Upload Thread" );
    httpManager.setParent( this );
    pConfigurator = CDbConfigurator::GetConfigurator( );
    connect( &httpManager, SIGNAL( finished( QNetworkReply* ) ),
             this, SLOT( HttpMngrFinished( QNetworkReply* ) ) );
}

QDataUploadThread::~QDataUploadThread( )
{
    if ( NULL != pUrl ) {
        delete pUrl;
        pUrl = NULL;
    }
}

void QDataUploadThread::PostUploadEvent(const QByteArray &byData, QDataUploadEvent::UploadEvent evtType)
{
    QDataUploadEvent* pEvent = QDataUploadEvent::CreateThreadEvent( evtType );
    pEvent->SetEventData( byData );

    qApp->postEvent( this, pEvent );
}

QDataUploadThread* QDataUploadThread::CreateThread( QObject *parent )
{
    if ( NULL == pThreadInstance ) {
        qDebug( ) << Q_FUNC_INFO << endl;

        pThreadInstance = new QDataUploadThread( parent );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QDataUploadThread::HttpPost( const QByteArray& byData )
{
    QNetworkReply* reply = httpManager.post( httRequest, byData );
    ConnectReplyEvent( reply );
}

void QDataUploadThread::ConnectReplyEvent( QNetworkReply *reply )
{
    connect( reply, SIGNAL( finished( ) ), this, SLOT( ReplyFinished( ) ) );
    connect( reply, SIGNAL( readyRead( ) ), this, SLOT( GetReplyData( ) ) );
    connect( reply, SIGNAL( error( QNetworkReply::NetworkError ) ),
             this, SLOT( HttpError( QNetworkReply::NetworkError) ) );
}

void QDataUploadThread::ReplyFinished( )
{
    QNetworkReply* reply = ( QNetworkReply* ) sender( );
    //PrecessReponse( reply );
    reply->deleteLater( );
}

void QDataUploadThread::GetReplyData( )
{
    QNetworkReply* reply = ( QNetworkReply* ) sender( );
    reply->readAll( );
}

void QDataUploadThread::HttpError( QNetworkReply::NetworkError errCode )
{
    Q_UNUSED( errCode )
    QNetworkReply* reply = ( QNetworkReply* ) sender( );
    QString strTxt = reply->errorString( );
    SendLog( strTxt, false );
}

void QDataUploadThread::SendLog( QString &strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void QDataUploadThread::run( )
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );

    InitializeSubThread( );
    exec( );
}

void QDataUploadThread::customEvent( QEvent *event )
{
    QDataUploadEvent* pEvent = ( QDataUploadEvent* ) event;
    QDataUploadEvent::UploadEvent evtType = ( QDataUploadEvent::UploadEvent ) pEvent->type( );
    const QByteArray& byData = pEvent->GetEventData( );

    switch ( evtType ) {
    case QDataUploadEvent::UploadInOutRecordInsert :
        break;

    case QDataUploadEvent::UploadInoutRecordUpdate :
        break;

    case QDataUploadEvent::UploadFeeInfoInsert :
        break;

    case QDataUploadEvent::UploadFeeInfoUpdate :
        break;
    }

    HttpPost( byData );
}

void QDataUploadThread::InitializeSubThread( )
{
    QString strHost = pConfigurator->GetHttpHost( );
    int nPort = pConfigurator->GetHttpPort( );
    pUrl = new QUrl( QString( "http://%1:%2/" ).arg( strHost, QString::number( nPort ) ) );
    httRequest.setUrl( *pUrl );
}

void QDataUploadThread::HttpMngrFinished( QNetworkReply* reply )
{
    Q_UNUSED( reply )
}
