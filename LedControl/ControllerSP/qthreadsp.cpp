#include "qthreadsp.h"
#include "QApplication"
#include "../ControllerCommon/qctrlevent.h"
#include <QDebug>

QThreadSP* QThreadSP::pSingleton = NULL;

QThreadSP::QThreadSP(QObject *parent) :
    QThread(parent)
{
    pDataReceiver = NULL;
    pController = NULL;
}

void QThreadSP::SetController( QControllerSP *pCtrl )
{
    static bool bEnter = false;

    if ( !bEnter ) {
        pController = pCtrl;
        connect( pController, SIGNAL( Data( QByteArray ) ), this, SLOT( HandleData( QByteArray ) ) );
        bEnter = true;
    }
}

void QThreadSP::SetDataReceiver( QThread *pThread )
{
    pDataReceiver = pThread;
}

QThreadSP& QThreadSP::GetSingleton( )
{
    if ( NULL == pSingleton )   {
        pSingleton = new QThreadSP( );
        pSingleton->start( );
        pSingleton->moveToThread( pSingleton ) ;
    }

    return *pSingleton;
}

void QThreadSP::HandleData( QByteArray data )
{
    SendData( data );

    //qDebug( ) << "Read Serial Port : " << data.toHex( ).toUpper( ) << endl;
}

void QThreadSP::SendData( QByteArray &data )
{
    if ( NULL == pDataReceiver ) {
        return;
    }

    QCtrlEvent* pEvent = new QCtrlEvent( ( QCtrlEvent::Type ) QCtrlEvent::SPParse );
    pEvent->SetData( data );
    qApp->postEvent( pDataReceiver, pEvent );
}

void QThreadSP::run( )
{
    exec( );
}

void QThreadSP::customEvent( QEvent *e )
{
    //QCtrlEvent* pEvent = (  QCtrlEvent* ) e;

    //if ( QCtrlEvent::SPWrite == ( QCtrlEvent::CtrlEvent ) pEvent->type( ) && NULL != pController ) {
    //    pController->WriteData( pEvent->GetData( ) );
    //}
}
