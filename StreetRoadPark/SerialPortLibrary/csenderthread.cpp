#include "csenderthread.h"

CSenderThread::CSenderThread( Win_QextSerialPort* pPort, QObject *parent) :
    QThread(parent), pWinPort( pPort )
{
    setObjectName( QString( "[ Data Sender Thread ID = %1]" ).arg( qrand( ) ) );
}

CSenderThread* CSenderThread::CreateThread( Win_QextSerialPort* pPort, QObject* parent )
{
    qDebug( ) << Q_FUNC_INFO << endl;

    CSenderThread* pThread = new CSenderThread( pPort, parent );

    pThread->start( );
    pThread->moveToThread( pThread );
    return pThread;
}

void CSenderThread::Initialize( )
{

}

void CSenderThread::run( )
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );
    Initialize( );
    exec( );
}

void CSenderThread::PostEvent( CComThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void CSenderThread::PostCmd( QByteArray& byCmd )
{
    CComThreadEvent* pEvent = CComThreadEvent::CreateThreadEvent( CComThreadEvent::ThreadSender, CComThreadEvent::EventSendData );
    pEvent->SetByteArrayData( byCmd );

    PostEvent( pEvent );
}

void CSenderThread::customEvent( QEvent * pEvent )
{
    CComThreadEvent* pThreadEvent = ( CComThreadEvent* ) pEvent;
    CComThreadEvent::EventType evtType = ( CComThreadEvent::EventType ) pEvent->type( );

    QByteArray& byCmd = pThreadEvent->GetByteArrayData( );

    if ( CComThreadEvent::EventSendData == evtType ) {
        ProcessSendDataEvent( byCmd, pWinPort );
    }
}

void CSenderThread::ProcessSendDataEvent( QByteArray &byCmd, Win_QextSerialPort *pPort )
{
    if ( 0 == byCmd.length( ) ) {
        return;
    }

    static quint8 nFrequence = 100;

    do {
        if ( pPort->isWritable( ) ) {
            pPort->write( byCmd );
            pPort->flush( );

            QString strLog = "Send Cmd : " + QString( byCmd );
            SendLog( strLog, true );

            break;
        } else {
            Sleep( 10 );
            nFrequence--;
        }
    } while( 0 < nFrequence );

    nFrequence = 100;
}

void CSenderThread::SendLog( QString &strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}
