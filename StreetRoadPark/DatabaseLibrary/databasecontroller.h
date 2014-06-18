#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include "DatabaseLibrary_global.h"
#include <QObject>
#include "qdatadispactherthread.h"

class DATABASELIBRARYSHARED_EXPORT DatabaseController : public QObject
{
    Q_OBJECT
public:
    static DatabaseController* GetController( QObject* parent = NULL );
    static void ReleaseController( );

    QDataDispactherThread* CreateDispactherThread( QObject* parent = NULL );
    void PostDispactherData( QDataDispactherThread* pDispatcher, QTcpSocket* pSocket, qint32 nPackageType, QByteArray& byData );
    void PostComPortData( qint32 nPackageType, QByteArray& byData, QString& strParkID );

    static int MySQLLibraryInit( int argc, char *argv[] );
    static void MySQLLibraryEnd( );
    static void CreateDbThreadPool( );
    static void PostConnectDbEvent( );

private:
    DatabaseController( QObject* parent = NULL );
    ~DatabaseController( );

    static DatabaseController* pController;
    QDatabaseProcessor* pComPortDataProcessor;

signals:
    void Log( QString strLog, bool bStatic );

public slots:

private slots:
    void HandleLog( QString strLog, bool bStatic );
};

#endif // DATABASECONTROLLER_H
