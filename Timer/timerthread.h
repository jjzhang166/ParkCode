#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>

class CTimerThread : public QThread
{
    Q_OBJECT
public:
    explicit CTimerThread(QObject *parent = 0);

    static CTimerThread* GetInstance( );

protected:
    void run( );

private:
    inline void GetConfig( );
    quint32 CalculateFirstTime( );
    void StartTimerProc( );

private:
    bool bPeriodic;
    QString strTime;
    
signals:
    
public slots:
    void ExitThread( );
    
};

#endif // TIMERTHREAD_H
