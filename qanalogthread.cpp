#include "qanalogthread.h"
#include <windows.h>
#include <QApplication>

QAnalogThread* QAnalogThread::pAnalogThread = NULL;

QAnalogThread::QAnalogThread(QObject *parent) :
    QThread(parent)
{
    bStopSend = false;
    nIntervalTime = 2000;
}

QAnalogThread* QAnalogThread::CreateInstance( )
{
    if ( NULL == pAnalogThread ) {
        pAnalogThread = new QAnalogThread( );
        pAnalogThread->moveToThread( pAnalogThread );
        pAnalogThread->start( );
    }

    return pAnalogThread;
}

void QAnalogThread::run( )
{
    exec( );
}

void QAnalogThread::AddCmd( QByteArray& byCmd )
{
    lstCmds.append( byCmd );
}

void QAnalogThread::ClearCmd( )
{
    lstCmds.clear( );
}

void QAnalogThread::SetStopSend( bool bStop )
{
    bStopSend = bStop;
}

void QAnalogThread::SetIntervalTime( int nTime )
{
    nIntervalTime = nTime;
}

void QAnalogThread::PostEvent( )
{
    if ( 0 == lstCmds.count( ) ) {
        return;
    }

    QEvent* pEvent = new QEvent( QEvent::User );
    qApp->postEvent( this, pEvent );
}

void QAnalogThread::customEvent(QEvent *e)
{
    Q_UNUSED( e )

    while ( true ) {
        if ( bStopSend ) {
            break;
        }

        foreach ( QByteArray byCmd, lstCmds ) {
            emit Command( byCmd );
            Sleep( nIntervalTime );
        }
    }
}
