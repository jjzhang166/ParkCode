#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include <stddef.h>
#if (defined(_WIN32) || defined(_WIN64)) && !defined(__WIN__)
#include <winsock.h>
#endif

#include <QObject>
#include "mysql.h"
#include "errmsg.h"
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QTextCodec>
#include <QFile>

// vvEye ID:80372 Pwd:21cnLemontree
// 10061
// my.ini [mysqld] port=3306 bind-address=127.0.0.1

//
// Bulk Insert
// Insert Into Table( f1,f2 ) Values(),(),()
// Insert Into Table( f1, f2 ) Select f1, f2 from table
// Load data infile
// SP

class CMySqlDatabase : public QObject
{
    Q_OBJECT
public:
    explicit CMySqlDatabase(QObject *parent = 0);
    ~CMySqlDatabase( );

    bool DbConnect( const QString& strHost, const QString& strUser,
                    const QString& strPwd, const QString& strDB, quint32 nPort );
    void DbDisconnect( );
    bool DbCrud( QString& strSql, QString& strError );
    bool BlobReadDb( QString& strBlobFile, QString& strSql, QString& strError );
    bool BlobWriteDb( QString& strBlobFile, QString& strSql, QString& strError );

    bool BlobReadDb( QByteArray& byData, QString& strSql, QString& strError );
    bool BlobWriteDb( QByteArray& byData, QString& strSql, QString& strError );
    quint64 GetRowData( QStringList& lstRows, QString& strError );
    bool PingMysql( );
    bool GetFirstConnect( );
    void SetFirstConnect( bool bFirst );

    ulong GetThreadID( );

    static int MySQLLibraryInit( int argc, char *argv[] );
    static void MySQLLibraryEnd( );

    bool ExcutePreparedStmt( QByteArray& byBlob, char& nFlag, QString& strSpName );

private:
    void GetErrorMsg( int nErrorCode, QString& strError, bool bMysql, QString& strSql, QString  strFunName );

private:
    QTextCodec* pCodec;
    MYSQL hConnect;
    MYSQL_STMT* hStmt;
    bool bFirstConnect;
    QString strPreSpName;

signals:
    void NotifyError( QString strMsg, bool bStatic );

public slots:

};

#endif // MYSQLDATABASE_H
