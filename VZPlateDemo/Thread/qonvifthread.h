#ifndef QONVIFTHREAD_H
#define QONVIFTHREAD_H

#include "QDigitalCameraThread.h"

class QOnvifThread : public QDigitalCameraThread
{
    Q_OBJECT
public:
    static QDigitalCameraThread* GetInstance( );

protected:
    void run( );
    void customEvent( QEvent *e );

private:
    explicit QOnvifThread(QObject *parent = 0);

private:
    static QDigitalCameraThread* pThreadInstance;

signals:

public slots:
    
};

#endif // QONVIFTHREAD_H
