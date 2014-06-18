#ifndef QFILECAMERATHREAD_H
#define QFILECAMERATHREAD_H

#include <QThread>
#include "qcameraevent.h"

class QFileCameraThread : public QThread
{
    Q_OBJECT
public:
    static QFileCameraThread* GetInstance( );

protected:
    void run( );
    void customEvent( QEvent *e );

private:
    explicit QFileCameraThread(QObject *parent = 0);

private:
    static QFileCameraThread* pThreadInstance;
    
signals:
    
public slots:
    
};

#endif // QFILECAMERATHREAD_H
