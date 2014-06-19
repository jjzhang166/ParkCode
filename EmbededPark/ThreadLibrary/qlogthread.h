#ifndef QLOGTHREAD_H
#define QLOGTHREAD_H

#include "qmythread.h"
#include "../IniConfigFile/qiniconfigfile.h"

class QLogThread : public QMyThread
{
    Q_OBJECT
public:
    static QLogThread* GetSingletonInstance( QObject* pParent = 0 );
    void PostLogWriteEvent( QCommonLibrary::LogType logType, QString& strText, bool bSingle );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    void ProcessWriteLogEvent( QCommonLibrary::EventParam& uParam );
    void WriteDatabase( QString* strSQL );
    void ConcatSQL( QString*& strSQL );
private:
    QLogThread(QObject *parent = 0);
    static QLogThread* pThreadInstance;
    QQueue< QString* > logQueue;
    
signals:
    void DisplayLog( QString strText );
    
public slots:
    
};

#endif // QLOGTHREAD_H
