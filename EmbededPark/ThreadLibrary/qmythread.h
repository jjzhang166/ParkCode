#ifndef QMYTHREAD_H
#define QMYTHREAD_H

#include "../CommonLibrary/qcommonlibrary.h"
#include <QThread>
#include "qthreadevent.h"

class QMyThread : public QThread
{
    Q_OBJECT
public:
    explicit QMyThread(QObject *parent = 0);
    void PostThreadExit( QMyThread* pThread );
    void InitializeThread( );

protected:
    void LaunchThreadExit( );
    void WriteLog( QCommonLibrary::LogType logType, QString& strText, bool bSingle );

    void PostThreadEvent( QThread* pThreadReceiver,
                          QCommonLibrary::ThreadType eThread,
                          QCommonLibrary::ThreadEventType eEvent,
                          QCommonLibrary::EventParam& uParam );

    void PostThreadEvent( QThread* pThreadReceiver,
                          QCommonLibrary::ThreadEventType eEvent );

    virtual void InitializeSubThread( ) = 0;

    void StartThread( QMyThread* pThread );

private:
    void ThreadStartExitLog( bool bStarted );
    
signals:
    
protected slots:
    void ThreadStarted( );
    void ThreadFinished( );
    
};

#endif // QMYTHREAD_H
