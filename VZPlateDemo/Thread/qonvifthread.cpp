#include "qonvifthread.h"

QDigitalCameraThread* QOnvifThread::pThreadInstance = NULL;

QOnvifThread::QOnvifThread(QObject *parent) :
    QDigitalCameraThread(parent)
{
}

QDigitalCameraThread* QOnvifThread::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QOnvifThread( );
        pThreadInstance->moveToThread( pThreadInstance );
        pThreadInstance->start( );
    }

    return pThreadInstance;
}

void QOnvifThread::run( )
{
    exec( );
}

void QOnvifThread::customEvent( QEvent *e )
{
    QCameraEvent* pEvent = ( QCameraEvent* ) e;
    QCameraEvent::CameraEventType evtType = ( QCameraEvent::CameraEventType ) pEvent->type( );
}
