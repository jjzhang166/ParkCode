#ifndef QTHREADSPWRITER_H
#define QTHREADSPWRITER_H

#include <QThread>
#include "qcontrollersp.h"

class CONTROLLERSPSHARED_EXPORT QThreadSPWriter : public QThread
{
    Q_OBJECT
public:
    void SetController( QControllerSP* pCtrlr );
    void SendData( QByteArray& data, int nWaitTime );
    static QThreadSPWriter& GetSingleton(  );

protected:
    explicit QThreadSPWriter(QObject *parent = 0);
    void run( );
    void customEvent( QEvent * e );

private:
    QControllerSP* pController;
    static QThreadSPWriter* pSingleton;
    
signals:
    
public slots:
    
};

#endif // QTHREADSPWRITER_H
