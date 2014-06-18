#include "qftpthread.h"

// u:demo p:demo@demo
QFtpThread* QFtpThread::pThreadInstance = NULL;

QFtpThread::QFtpThread(QObject *parent) :
    QThread(parent )
{
    pNetworkAccessManager = NULL;
}

bool QFtpThread::ThreadInitialize( )
{
    bool bRet = true;//QBaseThread::ThreadInitialize( );
/*
    pConfigurator = QConfigurator::CreateConfigurator( );
    pConfigurator->GetFtpHost( strFtpHost );
    pConfigurator->GetFtpHostPort( nFtpHostPort );
    pConfigurator->GetFtpUser( strFtpUser );
    pConfigurator->GetFtpPwd( strFtpPwd );
    pConfigurator->GetFtpBasePath( strFtpBasePath );
*/
    strFtpHost = "115.29.149.133";
    nFtpHostPort = 21;
    strFtpUser = "Ftp";
    strFtpPwd = "[Guid(\"269C795D-337F-485A-954A-186CBDEB0C66\")]";
    strFtpBasePath = "/";

    pNetworkAccessManager = new QNetworkAccessManager( this );
    connect( pNetworkAccessManager, SIGNAL( finished( QNetworkReply* ) ),
             this, SLOT( HandleNamFinished( QNetworkReply* ) ) );

    return bRet;
}

void QFtpThread::ThreadUninitialize( )
{
    if ( NULL != pNetworkAccessManager ) {
        delete pNetworkAccessManager;
    }
}

QFtpThread* QFtpThread::CreateInstance( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QFtpThread( );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QFtpThread::PostUploadFileEvent( QString& strName, QByteArray& byFileData )
{
    QFtpEvent* pEvent = QFtpEvent::CreateFtpEvent( QFtpEvent::UploadFile );
    pEvent->SetFileName( strName );
    pEvent->SetFileData( byFileData );

    PostEvent( pEvent );
}

void QFtpThread::PostEvent( QFtpEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void QFtpThread::PostDownloadFileEvent( QString& strName )
{
    QFtpEvent* pEvent = QFtpEvent::CreateFtpEvent( QFtpEvent::DownloadFile );
    pEvent->SetFileName( strName );

    PostEvent( pEvent );
}

void QFtpThread::run( )
{
    ThreadInitialize( );
    exec( );
}

void QFtpThread::customEvent( QEvent* pEvent )
{
    QFtpEvent::FtpEvent eEvent = ( QFtpEvent::FtpEvent ) pEvent->type( );
    QFtpEvent* pFtpEvent = ( QFtpEvent* ) pEvent;

    switch ( eEvent ) {
    case QFtpEvent::UploadFile :
        ProcessUploadFileEvent( pFtpEvent );
        break;

    case QFtpEvent::DownloadFile :
        ProcessDownloadFileEvent( pFtpEvent );
        break;
    }
}

void QFtpThread::HandleNamFinished( QNetworkReply *reply )
{
    reply->deleteLater( );
}

void QFtpThread::HandleUploadReplyFinished( )
{
    QNetworkReply* pReply = ( QNetworkReply* ) sender( );
    QString strPath = pReply->url( ).path( );
    Decoding( strPath, strPath );

    QString strLog = "Upload " + strPath +" finished at";
    EmitLog( strLog );
}

void QFtpThread::EmitLog( QString &strLog )
{
    qDebug( ) << strLog << endl;
}

void QFtpThread::HandleUploadReplyError( QNetworkReply::NetworkError code )
{
    Q_UNUSED( code );
    QNetworkReply* pReply = ( QNetworkReply* ) sender( );
    QString strPath = pReply->url( ).path( );
    Decoding( strPath, strPath );

    QString strError = pReply->errorString( );
    Decoding( strError, strError );

    QString strLog = "Upload " + strPath +" " + strError;
    EmitLog( strLog );
}

void QFtpThread::Encoding( QString &strRaw, QString &strResult )
{
    QByteArray byRaw;
#ifdef Q_OS_WIN
    byRaw = strRaw.toLocal8Bit( );
#else
    byRaw = QCommonFunction::GetTextCodec( )->fromUnicode( strRaw );
#endif

    strResult = QString::fromLatin1( byRaw.data( ), byRaw.count( ) );
}

void QFtpThread::Decoding( QString &strRaw, QString &strResult )
{
    QByteArray byRaw = strRaw.toLatin1( );

#ifdef Q_OS_WIN
    strResult = QString::fromLocal8Bit( byRaw.data( ), byRaw.count( ) );
#else
    strResult = QCommonFunction::GetTextCodec( )->toUnicode( byRaw );
#endif
}

void QFtpThread::GetFtpUrl( QUrl &url, QString& strName )
{
    url.setScheme( "ftp" );
    url.setHost( strFtpHost );
    url.setUserName( strFtpUser );
    url.setPassword( strFtpPwd );
    url.setPort( nFtpHostPort );

    QString strPath = strFtpBasePath + strName;
    Encoding( strPath, strPath );
    url.setPath( strPath );
}

void QFtpThread::ProcessUploadFileEvent( QFtpEvent* pEvent )
{
    //ftp://User:Pwd@Server:Port/Path

    QUrl url;
    QString strName = pEvent->GetFileName( );
    QByteArray byFileData = pEvent->GetFileData( );

    GetFtpUrl( url, strName );
    QNetworkRequest request( url );

    QString strPath = url.path( );
    Decoding( strPath, strPath );

    QString strLog = "Upload " + strPath +" started at";
    EmitLog( strLog );

    QNetworkReply* pReply = pNetworkAccessManager->put( request, byFileData );
    //pReply->setProperty( "FtpData",  pFileData );

    connect( pReply, SIGNAL( finished( ) ),
             this, SLOT( HandleUploadReplyFinished( ) ) );
    connect( pReply, SIGNAL( error( QNetworkReply::NetworkError ) ),
             this, SLOT( HandleUploadReplyError( QNetworkReply::NetworkError ) ) );
}

void QFtpThread::ProcessDownloadFileEvent( QFtpEvent* pEvent )
{

}
