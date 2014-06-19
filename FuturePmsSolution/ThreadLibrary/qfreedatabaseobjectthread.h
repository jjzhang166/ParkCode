#ifndef QFREEDATABASEOBJECTTHREAD_H
#define QFREEDATABASEOBJECTTHREAD_H

#include "QMyBaseThread.h"
#include "Event/qfreedatabaseobjectthreadevent.h"

class QFreeDatabaseObjectThread : public QMyBaseThread
{
    Q_OBJECT
public:
    static QFreeDatabaseObjectThread* GetSingleton( );
    ~QFreeDatabaseObjectThread( );

protected:
    explicit QFreeDatabaseObjectThread(QObject *parent = 0);

    void run( );
    void InitializeSubThread( );
    virtual void customEvent( QEvent* event );

private:
    void ProcessCheckDatabaseObjectEvent( MyDataStructs::PQQueueEventParams pEventParams );

private:

private:
    static QFreeDatabaseObjectThread* pThreadInstance;

signals:

public slots:

private slots:

};

#endif // QFREEDATABASEOBJECTTHREAD_H
