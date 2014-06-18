#ifndef TIMERPROC_H
#define TIMERPROC_H

#include <QRunnable>
#include <QStringList>
#include "Common/commonfunction.h"
#include "Database/mysqldatabase.h"

class CTimerProc : public QRunnable
{
public:
    CTimerProc();

    void run( );
    static CTimerProc* GetInstance( );

private:
    void UploadReport( );
    void ConnectMySql( QStringList& lstParams );
    void GetSQL( QString& strSql, QString& strTable );
    void ExecuteSQL( QString& strTable );

private:
    QSettings* pSystem;
    CMySqlDatabase mySql;
};

#endif // TIMERPROC_H
