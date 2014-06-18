#ifndef PMSLOG_H
#define PMSLOG_H

#include <QObject>
#include "Common/logicinterface.h"

class CPmsLog : public QObject
{
    Q_OBJECT
public:
    explicit CPmsLog(QObject *parent = 0);

public:
    static CPmsLog* GetInstance( );
    static void ReleaseInstance( );

    void WriteLog( QStringList& lstLogs );

private:
    CLogicInterface* pDataOperator;
    static CPmsLog* pLogger;
    
signals:
    
public slots:
    
};

#endif // PMSLOG_H
