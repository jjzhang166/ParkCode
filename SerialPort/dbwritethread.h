#ifndef DBWRITETHREAD_H
#define DBWRITETHREAD_H

#include <QThread>
#include "dbevent.h"
#include "dbhistorythread.h"

class CDbWriteThread : public QThread
{
    Q_OBJECT
public:
    explicit CDbWriteThread(bool bImage = false, QObject *parent = 0);

protected:
    void run( );
    void customEvent( QEvent * e );

private:
    CDbWriteThread* GetWriteImageThread( );
    void PostWriteImage( QEvent* e );
    void WriteData( CDbEvent::WriteParameter& paramter, bool bSQL );
    bool ConnectDb( );
    inline void ExcuteSQL( CLogicInterface& intf, bool bSQL, CDbEvent::WriteParameter& paramter );

private:
    CLogicInterface interfaceNormal;
    CDbHistoryThread* pHistoryThread;
    bool bWriteImage;

    static CDbWriteThread* pWriteImage;

signals:

public slots:

};

#endif // DBWRITETHREAD_H
