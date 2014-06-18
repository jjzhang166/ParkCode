#ifndef QUPLOADDATATHREAD_H
#define QUPLOADDATATHREAD_H

#include <QThread>
#include <QtSql>
#include <QSettings>
#include "quploaddataevent.h"
#include "qftpthread.h"

class QUploadDataThread : public QThread
{
    Q_OBJECT
public:
    static QUploadDataThread* CreateInstance( QObject* pParent = NULL );
    ~QUploadDataThread( );

    void PostUploadDataEvent( QStringList& lstRecordParams, QByteArray& byImage );
    void CloseDB( );

protected:
    void run( );
    void customEvent( QEvent *e );

private:
    explicit QUploadDataThread(QObject *parent = 0);
    void InitializeThread( );
    inline void PrintMsg( QSqlError sqlError );
    inline void PostEvent( QUploadDataEvent* pEvent );

    void ProcessUploadDataEvent( QUploadDataEvent* pEvent );
    void UploadImage( QUploadDataEvent* pEvent );
    void GetFileName( QString& strName, QStringList& lstParams );

private:
    static QUploadDataThread* pThreadInstance;
    QString strConnectName;
    QSettings* pSettings;
    QString strParkID;
    QString strFileName;
    QFtpThread* pFtpThread;
    
signals:
    
private slots:
    void ThreadExit( );
    
};

#endif // QUPLOADDATATHREAD_H
