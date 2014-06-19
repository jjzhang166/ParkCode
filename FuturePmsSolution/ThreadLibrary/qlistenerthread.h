#ifndef QLISTENERTHREAD_H
#define QLISTENERTHREAD_H

#include "qmybasethread.h"
#include "Event/qlistenerthreadevent.h"

class QListenerThread : public QMyBaseThread
{
    Q_OBJECT
public:
    static QListenerThread* GetInstance( );
    ~QListenerThread( );

protected:
    explicit QListenerThread(QObject *parent = 0);

    void run( );
    void InitializeSubThread( );
    virtual void customEvent( QEvent* event );

private:
    void ProcessListenerStartupEvent( MyDataStructs::PQQueueEventParams pEventParams );

signals:
    void Accept( int socketDescriptor );

public slots:

private slots:
    void HandleAccept( int socketDescriptor );
    
};

#endif // QLISTENERTHREAD_H
