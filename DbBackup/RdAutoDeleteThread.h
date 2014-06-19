#ifndef RDAUTODELETETHREAD_H
#define RDAUTODELETETHREAD_H
#include <QThread>
#include <QDate>
#include <QTime>
#include "Common/logicinterface.h"

class CRdAutoDeleteThread : public QThread
{
    Q_OBJECT
public:
    explicit CRdAutoDeleteThread(QObject *parent = 0);
    static CRdAutoDeleteThread& GetInstance( QObject* parent );

protected:
    void run();

private:
    bool CheckTimePoint( );
    void DeleteData( );
    inline void ExecuteSql( QDate tmpDate, int nIndex );
    inline void LetSleep( );

private:
    int FeeRd;
    bool FeeRdAuto;

    int StopRd;
    bool StopRdAuto;

    int SysLog;
    bool SysLogAuto;

    int ImgRd;
    bool ImgRdAuto;

    quint32 nAutoInterval;
    QTime tAutoStart;

    bool bStartThread;

    CLogicInterface dbInterf;

signals:

private slots:
    void ExitThread( );

};
#endif // RDAUTODELETETHREAD_H
