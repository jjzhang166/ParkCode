#ifndef DBHISTORYTHREAD_H
#define DBHISTORYTHREAD_H

#include <QThread>
#include <QList>
#include "dbevent.h"
#include "../Common/logicinterface.h"

class CDbHistoryThread : public QThread
{
    Q_OBJECT
public:
    explicit CDbHistoryThread(QObject *parent = 0);

    bool AddParameters( CDbEvent::WriteParameter& parameter );

protected:
    void run( );

private:
    bool ConnectDb( );
    inline void DisconnectDb( );

private:
        CLogicInterface interfaceHistory;
        QList< CDbEvent::WriteParameter > lstParameters;
        QSettings* pSettings;
    
signals:
    
public slots:
        void ExitThread( );
};

#endif // DBHISTORYTHREAD_H
