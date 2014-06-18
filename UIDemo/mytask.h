#ifndef MYTASK_H
#define MYTASK_H

#include <QObject>
#include <QRunnable>

class CMyTask : public QObject, QRunnable
{
    Q_OBJECT
public:
    explicit CMyTask(QObject *parent = 0);

    void run( );

signals:

public slots:

};

#endif // MYTASK_H
