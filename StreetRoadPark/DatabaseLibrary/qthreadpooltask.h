#ifndef QTHREADPOOLTASK_H
#define QTHREADPOOLTASK_H

#include <QRunnable>
#include <QTcpSocket>
#include <QByteArray>

class QThreadPoolTask : public QRunnable
{
public:
    static QThreadPoolTask* CreateTask( );

    void SetTaskData( QByteArray& byData );
    void SetPeerSocket( QTcpSocket* pSocket );
    //void SetDatabase( CMySqlDatabase* pDb );

    void run( );

private:
    QThreadPoolTask( );

private:
    QTcpSocket* pPeerSocket;
    //CMySqlDatabase* pDatabase;
    QByteArray byTaskData;
};

#endif // QTHREADPOOLTASK_H
