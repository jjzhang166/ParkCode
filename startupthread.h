#ifndef STARTUPTHREAD_H
#define STARTUPTHREAD_H

#include <QThread>
#include <QEvent>

class CStartupThread : public QThread
{
    Q_OBJECT
public:
    explicit CStartupThread(QObject *parent = 0);

protected:
     void run( );
     void customEvent( QEvent * );

private:
     void StartDlg( );
     void DestroyDlg( );
     void UpdateInfo( QString strInfo );

signals:

public slots:

};

#endif // STARTUPTHREAD_H
