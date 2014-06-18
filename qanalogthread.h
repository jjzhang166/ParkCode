#ifndef QANALOGTHREAD_H
#define QANALOGTHREAD_H

#include <QThread>
#include <QEvent>
#include <QList>
#include <QByteArray>

class QAnalogThread : public QThread
{
    Q_OBJECT
public:

    static QAnalogThread* CreateInstance( );

    void AddCmd( QByteArray& byCmd );
    void ClearCmd( );

    void SetStopSend( bool bStop );
    void SetIntervalTime( int nTime );

    void PostEvent( );

protected:
    void run( );
    void customEvent( QEvent *e );

private:
    explicit QAnalogThread(QObject *parent = 0);

private:
    static QAnalogThread* pAnalogThread;
    QList< QByteArray > lstCmds;
    bool bStopSend;
    int nIntervalTime;
    
signals:
    void Command( QByteArray byCmd );
    
public slots:
    
};

#endif // QANALOGTHREAD_H
