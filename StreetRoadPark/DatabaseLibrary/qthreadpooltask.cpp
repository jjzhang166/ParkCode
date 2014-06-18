#include "qthreadpooltask.h"

QThreadPoolTask::QThreadPoolTask( )
{
    setAutoDelete( true );
}

QThreadPoolTask* QThreadPoolTask::CreateTask( )
{
    return new QThreadPoolTask( );
}

void QThreadPoolTask::run( )
{

}

void QThreadPoolTask::SetTaskData( QByteArray &byData )
{
    byTaskData.append( byData );
}

void QThreadPoolTask::SetPeerSocket( QTcpSocket *pSocket )
{
    pPeerSocket = pSocket;
}
