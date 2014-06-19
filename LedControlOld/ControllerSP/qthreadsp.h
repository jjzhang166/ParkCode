#ifndef QTHREADSP_H
#define QTHREADSP_H

#include <QThread>
#include "qcontrollersp.h"

class CONTROLLERSPSHARED_EXPORT QThreadSP : public QThread
{
    Q_OBJECT
public:
    void SetController( QControllerSP* pCtrl );
    void SetDataReceiver( QThread* pThread );
    static QThreadSP& GetSingleton(  );

protected:
    explicit QThreadSP(QObject *parent = 0);
    void run( );
    void customEvent( QEvent * e );

private:
    void SendData( QByteArray& data );

private:
    QControllerSP* pController;
    QThread* pDataReceiver;
    static QThreadSP* pSingleton;
    
signals:
    
public slots:

private slots:
    void HandleData( QByteArray data );
    
};

#endif // QTHREADSP_H
