#ifndef QDATABASETHREAD_H
#define QDATABASETHREAD_H

#include "qmythread.h"

class QDatabaseThread : public QMyThread
{
    Q_OBJECT
public:
    static QDatabaseThread* GetSingletonInstance( QObject* pParent = 0 );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    QDatabaseThread(QObject *parent = 0);
    static QDatabaseThread* pThreadInstance;
    
signals:
    
public slots:
    
};

#endif // QDATABASETHREAD_H
