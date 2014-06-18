#ifndef QDATABASEPROCESSOR_H
#define QDATABASEPROCESSOR_H

#include <QThread>
#include "qdbthreadevent.h"
#include "Database/mysqldatabase.h"
#include <QSemaphore>
#include "qdbdataprocess.h"

class QDatabaseProcessor : public QThread
{
    Q_OBJECT
public:
    static QDatabaseProcessor* CreateThread( bool bPoolThread, QObject* parent = NULL );
    void SetDataDispatcher( QThread* pDispatcher );

    void AcquireProcessor( qint32 nResCount );
    bool TryAcquireProcessor( );
    bool TryAcquireProcessor( qint32 nTimeout );

    qint32 GetFreeOperationCount( );
    ~QDatabaseProcessor( );
    void PostDbDataProcessEvent( QTcpSocket* pSocket, qint32 nPackageType, QByteArray& byData );
    void PostComPortDataProcessEvent( qint32 nPackageType, QByteArray& byData, QString& strParkID );
    void PostDbConnectEvent( );

protected:
    void run( );
    void customEvent( QEvent *event );

    void InitializeSubThread( );

private:
    explicit QDatabaseProcessor( bool bPoolThread, QObject *parent = 0);

    inline void PostEvent( QDbThreadEvent* pEvent );
    inline void SendLog( QString& strLog, bool bStatic );

    void ProcessDatabaseDataEvent( QDbThreadEvent* pEvent );
    void ProcessComPortDataEvent( QDbThreadEvent* pEvent );
    void ProcessDatabaseConnectEvent( QDbThreadEvent* pEvent );

private:
    bool bThreadPoolProcessor;
    CMySqlDatabase* pDatabase;
    CDbConfigurator* pConfig;
    QStringList lstDbInfo;
    QSemaphore* pResSemaphore; // Processor Task Count
    qint32 nDbOperationCount;
    QDbDataProcess dataProcessor;
    QThread* pDataDispatcher;

signals:
    void Log( QString strLog, bool bStatic );

public slots:

private slots:
    void HandleLog( QString strLog, bool bStatic );
};

#endif // QDATABASEPROCESSOR_H
