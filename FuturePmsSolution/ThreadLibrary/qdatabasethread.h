#ifndef QDATABASETHREAD_H
#define QDATABASETHREAD_H

#include "qmybasethread.h"
#include "Event/qdatabasethreadevent.h"
#include <QThreadPool>
#include "qthreadpooltask.h"
#include "../MyDatabase/qdatabasegenerator.h"

class QDatabaseThread : public QMyBaseThread
{
    Q_OBJECT
public:
    static QDatabaseThread* GetSingleton( /*const bool bTcpThread*/ );
    void SetTaskType( bool bTcpTaskItem );
    ~QDatabaseThread( );

    static void ReleaseDatabaseObject( );
    bool SignalConnected( );

protected:
    explicit QDatabaseThread(QObject *parent = 0);

    void run( );
    void InitializeSubThread( );
    virtual void customEvent( QEvent* event );

private:
    void ProcessCrudEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void ProcessEnqueueEvent( MyDataStructs::PQQueueEventParams pEventParams );

    inline void GetDatabaseParam( const QManipulateIniFile::IniFileSectionItems item, QVariant& var );
    inline void GetConnectParamItem( const QManipulateIniFile::IniFileSectionItems item );

    inline void GetDatabaseTypeParam( );
    inline void GetDatabaseThreadpoolParam( );
    inline void GetDatabaseConnectParam( );
    inline void GetDatabaseObjLifeTime( );

    void QueueDatabaseObject( QMyDatabase*& pDababase, const bool bEnqueue );

private:

private:
    static QDatabaseThread* pThreadInstance;
    QThreadPool dbThreadPool;
    QDatabaseGenerator* pDatabaseGenerator;
    //bool bTcpTask;
    MyEnums::DatabaseType dbType;
    MyDataStructs::QParamMultiHash hashDatabaseParams;
    quint32 nDatabaseObjLifeTime;

    static MyDataStructs::QPointerQueue dbObjectQueue;
    static QMutex queueMutex;

signals:

public slots:

private slots:
    
};

#endif // QDATABASETHREAD_H
