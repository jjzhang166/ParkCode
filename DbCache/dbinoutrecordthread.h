#ifndef DBINOUTRECORDTHREAD_H
#define DBINOUTRECORDTHREAD_H

#include <QObject>
#include <QThread>
class CDbInOutRecordThread : public QThread
{
    Q_OBJECT
public:
    explicit CDbInOutRecordThread(QObject *parent = 0);

protected:
    void run( );
    void customEvent ( QEvent * event );
    
signals:
    
public slots:
    
};

#endif // DBINOUTRECORDTHREAD_H
