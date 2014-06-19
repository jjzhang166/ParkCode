#ifndef BULKINSERT_H
#define BULKINSERT_H

#include <QVariant>
#include <QRunnable>
#include <QtSql>
#include "../Common/commonfunction.h"
#include "../Network/localcltcommunication.h"

extern CLocalCltCommunication* g_pLocalCltComm;

class CBulkInsert : public QRunnable
{
public:
public:
    static CBulkInsert* GetInstance( );
    void run( );
    QVariantList* GetVariantList( int nCols );
    void SetDbParams( QSqlDatabase* pDb, QString& strSql );

    ~CBulkInsert( );

private:
    CBulkInsert( );
    void SendSqlError( QSqlError error );

    QSqlDatabase* pDbServer;
    QString strDbSql;
    QVariantList* lstValues;
    int nColCount;
};

#endif // BULKINSERT_H
