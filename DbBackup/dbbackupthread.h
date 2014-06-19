#ifndef DBBACKUPTHREAD_H
#define DBBACKUPTHREAD_H

#include <QThread>
#include <QDateTime>
#include <QTime>
#include <QHash>
#include <QStringList>
#include "DbBackup/RdAutoDeleteThread.h"
#include "Common/logicinterface.h"

class CDbBackupThread : public QThread
{
    Q_OBJECT
public:
    explicit CDbBackupThread( bool bAuto, bool bRestore, QObject *parent = 0 );
    static CDbBackupThread& GetInstance( bool bAuto, bool bRestore, QObject *parent );

protected:
    void run( );

private:
    void BackupData( bool bImg, bool bAuto );
    void RestoreData( );
    void GetConfig( bool bOption );
    void LetSleep( bool bCurrentDay );
    bool CheckTimePoint( );
    inline int DayDiff( );

private:
    bool bAutoBackup;
    bool bAutoRestore;

    QTime tAutoBackupTime;
    bool bAutoBackupStartup;
    bool bAutoBackupImg;
    QDate dtNextAutoTime;
    QString strManualBackupPath;
    bool bManualBackupImg;
    QString strManualRestorePath;
    bool bManualOverwiteData;
    uint nAutoInterval;
    int nDayDiff;

    QStringList lstTables;
    QHash< QString, QString > sqlHash;

    //CRdAutoDeleteThread delThread;
    CLogicInterface dbInterf;

signals:

private slots:
    void ExitThread( );

};

#endif // DBBACKUPTHREAD_H
