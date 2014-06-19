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

class CMySqlDatabase : public QObject
{
    Q_OBJECT
public:
    explicit CMySqlDatabase(QObject *parent = 0);
    ~CMySqlDatabase( );

    void SetExpiration( bool bExp );

    bool DbConnect( QString strHost, QString strUser, QString strPwd, QString strDB, quint32 nPort );
    void DbDisconnect( );
    bool DbCrud( QString& strSql, QString& strError );
    bool BlobReadDb( QString& strBlobFile, QString& strSql, QString& strError );
    bool BlobWriteDb( QString& strBlobFile, QString& strSql, QString& strError );

    bool BlobReadDb( QByteArray& byData, QString& strSql, QString& strError );
    bool BlobWriteDb( QByteArray& byData, QString& strSql, QString& strError );
    quint64 GetRowData( QStringList& lstRows, QString& strError );
    bool PingMysql( );

    static int MySQLLibraryInit( int argc, char** argv );
    static void MySQLLibrayEnd( );

private:
    void GetErrorMsg( int nErrorCode, QString& strError, bool bMysql, QString& strSql );

private:
    QTextCodec* pCodec;
    MYSQL hConnect;
    MYSQL_STMT* hStmt;

    static bool bExpiration;

signals:
    void NotifyError( QString strMsg );

public slots:

};

#endif // MYSQLDATABASE_H
