#include "qdatadownloadthread.h"

QDataDownloadThread* QDataDownloadThread::pThreadInstance = NULL;

QDataDownloadThread::QDataDownloadThread(QObject *parent) :
    QThread(parent)
{
    setObjectName( "Data Download Thread" );
}

QDataDownloadThread* QDataDownloadThread::CreateThread( QObject *parent )
{
    if ( NULL == pThreadInstance ) {
        qDebug( ) << Q_FUNC_INFO << endl;

        pThreadInstance = new QDataDownloadThread( parent );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QDataDownloadThread::run( )
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );

    InitializeSubThread( );
    exec( );
}

void QDataDownloadThread::SendLog( QString &strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void QDataDownloadThread::customEvent( QEvent *event )
{
}

void QDataDownloadThread::InitializeSubThread( )
{
}

void QDataDownloadThread::HttpVerbFinished( QNetworkReply* reply )
{
}
