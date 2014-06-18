#include "qftpthread.h"
#include <QApplication>
#include <QDebug>
#include <QFile>

QFtpThread* QFtpThread::pThreadInstance = NULL;

QFtpThread::QFtpThread(QObject *parent) :
    QThread(parent)
{
    bool bRet = connect( this, SIGNAL( terminated( ) ), this, SLOT( ThreadExit( ) ) );
    bRet = connect( &ftpClient, SIGNAL( commandStarted( int ) ), this, SLOT( FtpCommandStarted( int ) ) );
    bRet = connect( &ftpClient, SIGNAL( commandFinished( int, bool ) ), this, SLOT( FtpCmdFinished( int, bool ) ) );
    bRet = connect( &ftpClient, SIGNAL( stateChanged( int ) ), this, SLOT( StateChanged( int ) ) );
}

void QFtpThread::FtpCommandStarted(int nId)
{
    qDebug( ) << Q_FUNC_INFO << QString::number( nId ) << endl;
}

QFtpThread* QFtpThread::CreateInstance( QObject *pParent )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QFtpThread( pParent );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QFtpThread::SetFtpServer( QStringList &lstParams )
{
    lstFtpServer = lstParams;
}

void QFtpThread::PostUploadFileEvent( QString &strFileName, QByteArray &byImageData )
{
    QFtpThreadEvent* pEvent = QFtpThreadEvent::CreateEvent( QFtpThreadEvent::UploadFile );
    pEvent->SetFileName( strFileName );
    pEvent->SetImageData( byImageData );

    PostEvent( pEvent );
}

void QFtpThread::PostEvent( QFtpThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void QFtpThread::run( )
{
    exec( );
}

void QFtpThread::customEvent( QEvent* e )
{
    QFtpThreadEvent* pEvent = ( QFtpThreadEvent* ) e;
    QFtpThreadEvent::FtpEvent eEvent = ( QFtpThreadEvent::FtpEvent ) e->type( );

    switch ( eEvent ) {
    case QFtpThreadEvent::UploadFile :
        ProcessUploadFile( pEvent );
        break;
    }
}

void QFtpThread::ProcessUploadFile( QFtpThreadEvent *pEvent )
{
    QByteArray byFileName = pEvent->GetFileName( ).toLocal8Bit( );
    QString strFileName = QString::fromLatin1( byFileName.data( ), byFileName.count( ) );
    QByteArray byImageData = pEvent->GetImageData( );

    if ( QFtp::Unconnected == ftpClient.state( ) ) {
        StateChanged( QFtp::Unconnected );
    }
/*
    //QByteArray* pData = new QByteArray( byImageData );
    static QByteArray d;
    if ( d.size( ) == 0 ) {
        QFile file( "d:/MainBG.jpg" );
        file.open( QFile::ReadOnly );

        d = file.readAll( );
    }
    */
    int nPut = ftpClient.put( byImageData, strFileName );
    qDebug( ) << ftpClient.errorString( ) << endl;
    //dataHash.insert( nPut, pData );
}

void QFtpThread::StateChanged( int nState )
{
    if ( QFtp::Unconnected == nState ) {
        ftpClient.connectToHost( lstFtpServer[ 0 ], lstFtpServer[ 1 ].toUShort( ) );
        ftpClient.login( lstFtpServer[ 2 ], lstFtpServer[ 3 ] );
        qDebug( ) << Q_FUNC_INFO << ftpClient.errorString( ) << endl;
    }
}

void QFtpThread::FtpCmdFinished( int nId, bool bError )
{
#ifndef QT_NO_DEBUG
    QString str = ftpClient.errorString( );
    qDebug( ) << Q_FUNC_INFO << str << QString::number( nId ) << endl;
#endif

    QFtp::Command cmd = ftpClient.currentCommand( );
    if ( cmd == QFtp::Put ) {
        //QByteArray* pData = dataHash.value( nId );
        //dataHash.remove( nId );
        //delete pData;
    }
}

void QFtpThread::ThreadExit( )
{
    delete this;
}
