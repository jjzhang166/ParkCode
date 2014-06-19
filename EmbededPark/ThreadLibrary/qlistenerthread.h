#ifndef QLISTENERTHREAD_H
#define QLISTENERTHREAD_H

#include "qsocketdispatcherthread.h"
#include "../NetworkLibrary/qnetworklibrary.h"

class QListenerThread : public QMyThread
{
    Q_OBJECT
public:
    static QListenerThread* GetSingletonInstance( QObject* pParent = 0 );
    void PostStartListenEvent( );
    void PostStopListenEvent( );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    QListenerThread(QObject *parent = 0);

    void PostSocketDescriptorEvent( qintptr socketDescriptor );
private:
    static QListenerThread* pThreadInstance;
    QNetworkLibrary network;
    QSocketDispatcherThread* pSocketDispatcher;
    
signals:
    
protected slots:
    void HandleAccept( qintptr socketDescriptor );
    void HandleErrorInfo( qint32 logType, QString strText );
    
};

#endif // QLISTENERTHREAD_H
