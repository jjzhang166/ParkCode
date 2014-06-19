#ifndef QTCPPEERSOCKETTHREAD_H
#define QTCPPEERSOCKETTHREAD_H

#include "qmybasethread.h"
#include "Event/qtcppeerthreadevent.h"
#include "../MyNetwork/qtcppeerclient.h"

#include "qdatabasethread.h"
#include "Event/qdatabasethreadevent.h"

#include <QMutex>

class QTcpPeerSocketThread : public QMyBaseThread
{
    Q_OBJECT
public:
    static QTcpPeerSocketThread* GetInstance( bool& bSignalConnected );
    static void ReleaseThread( );
    bool MayRelease( );
    ~QTcpPeerSocketThread( );

    bool SignalConnected( );

protected:
    explicit QTcpPeerSocketThread(QObject *parent = 0);

    void run( );
    void InitializeSubThread( );
    virtual void customEvent( QEvent* event );

private:
    inline void GetThreadPeerSocketCount( );
    QTcpPeerClient* CreatePeerSocket( char nMaxSocket );
    void DestroyPeerSocket( MyDataStructs::QSocketMultiHash& hash );
    quint32 GetIniValue( const QManipulateIniFile::IniFileSectionItems item );
    void ManagePeerSocketHash( QTcpSocket*& pPeerSocket, bool bInserted );
    void ThreadEnqueue( );

    void ProcessDatabaseData( QTcpSocket* pPeerSocket, QByteArray* pByteArray );
    void ProcessOtherData( QTcpSocket* pPeerSocket, QByteArray* pByteArray );

    void ProcessCreateSocketEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void ProcessThreadPoolFeedbackEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void PostDatabaseEvent( MyEnums::EventType event, MyDataStructs::PQQueueEventParams pQueueEventParams, QThread* pReceiver );

private:
    QDatabaseThread* pDatabaseThread;
    QThreadPool peerThreadPool;
    MyDataStructs::QSocketMultiHash socketUsedHash;
    MyDataStructs::QSocketMultiHash socketUnusedHash;
    quint8 nThreadPeerSocketCount;
    static MyDataStructs::QPointerQueue peerThreadQueue;
    static QMutex queueMutex;

signals:
    void ReleaseMyself(QTcpPeerSocketThread* pThread );

public slots:

private slots:
    void HandleThreadEnqueue( QTcpSocket* pPeerSocket );
    void HandleGetWholeTcpStreamData( QTcpSocket* pPeerSocket, void* pByteArray );
    
};

#endif // QTCPPEERSOCKETTHREAD_H
