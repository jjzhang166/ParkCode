#ifndef QLOGGERTHREAD_H
#define QLOGGERTHREAD_H

#include "qmybasethread.h"
#include "Event/qloggerevent.h"

class QLoggerThread : public QMyBaseThread
{
    Q_OBJECT
public:
    static QLoggerThread* GetSingleton( );
    ~QLoggerThread( );

protected:
    explicit QLoggerThread(QObject *parent = 0);

    void run( );
    void InitializeSubThread( );
    virtual void customEvent( QEvent* event );

private:
    void ProcessWriteLogEvent( MyDataStructs::PQQueueEventParams pEventParams );
    void GetLogFileName( );

private:
    inline QString GetFileName( );
    void GetLogPath( );

private:
    static QLoggerThread* pThreadInstance;
    QString strLogPath;
    QManipulateIniFile::LogFileNames logFileName;
    
signals:
    
public slots:

private slots:
    
};

#endif // QLOGGERTHREAD_H
