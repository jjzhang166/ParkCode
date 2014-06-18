#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class CMyThread : public QThread
{
    Q_OBJECT
public:
    explicit CMyThread(QObject *parent = 0);

public:
     void run( );

signals:

public slots:

};

#endif // MYTHREAD_H
