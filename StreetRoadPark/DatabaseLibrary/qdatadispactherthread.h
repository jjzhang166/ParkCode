#ifndef QDATADISPACTHERTHREAD_H
#define QDATADISPACTHERTHREAD_H

#include <QThread>
#include "qdbthreadevent.h"
#include <QThreadPool>
#include "qdatabaseprocessor.h"
#include <QMutex>
#include <QMutexLocker>

class QDataDispactherThread : public QThread
{
    Q_OBJECT
public:
    static QDataDispactherThread* CreateThread( QObject* parent = NULL );
    static void CreateDbThread( QObject* pReceiver );
    static void PostConnectDbEvent( );

    ~QDataDispactherThread( );
    void PostDispatchDataEvent( QTcpSocket* pSocket, qint32 nPackageType, QByteArray& byData );
    void PostComPortDataEvent( qint32 nPackageType, QByteArray& byData );

protected:
    void run( );
    void customEvent( QEvent *event );

    void InitializeSubThread( );

private:
    typedef QList< QDatabaseProcessor* > QProcessorList;
    typedef QMultiHash< qint32, QDatabaseProcessor* > QIntProcessorHash;
    explicit QDataDispactherThread(QObject *parent = 0);

    void FreeDbThread( );
    //void CreateDbThread( );
    QDatabaseProcessor* GetProcessor( );
    void ProcessDispatchDataEvent( QDbThreadEvent* pEvent );
    inline void PostEvent( QDbThreadEvent* pEvent );
    inline void SendLog( QString& strLog, bool bStatic );
    inline QDatabaseProcessor* CreateOneDbThread( );
    inline void ChangeProcessorHash( qint32 nIndex, QDatabaseProcessor* pThread );
    void ChangeProcessorHash( );

private:
    QThreadPool threadPool4Db;
    QThreadPool threadPool4Data;
    qint32 nDbThreadCount;
    qint32 nDbThreadOperationCount;
    qint32 nDbThreadInvalidWaitTime;
    CDbConfigurator* pConfig;
    static QIntProcessorHash hashProcessor;
    static QMutex mutexHashProcessor;

signals:
    void Log( QString strLog, bool bStatic );
    
public slots:

private slots:
    void HandleLog( QString strLog, bool bStatic );
    
};

#endif // QDATADISPACTHERTHREAD_H
