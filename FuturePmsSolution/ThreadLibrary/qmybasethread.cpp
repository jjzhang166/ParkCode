#include "qmybasethread.h"

QMyBaseThread::QMyBaseThread(QObject *parent) :
    QThread(parent)
{
    setObjectName( "QMyBaseThread" );
}

QMyBaseThread::~QMyBaseThread( )
{
    OutputMsg( currentThread( )->metaObject( )->className( ) );
}

void QMyBaseThread::ExitThread( )
{
    deleteLater( );
}

void QMyBaseThread::InitializeThread( )
{
    connect( this, SIGNAL( finished( ) ), this, SLOT( ExitThread( ) ) );
}

void QMyBaseThread::LaunchThreadExit( )
{
    moveToThread( qApp->thread( ) );
    exit( );
}

void QMyBaseThread::HandleMessage( void* pstrMsg, QManipulateIniFile::LogTypes type )
{
    OutputMsg( "Sender:" + sender( )->objectName( ) + QString( ":emit NotifyMessage( %1, LogTypes=%2 )" ).arg( *( QString* ) pstrMsg, QString::number( type ) ) );
    emit NotifyMessage( pstrMsg, type );
}
