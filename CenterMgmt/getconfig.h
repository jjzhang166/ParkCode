#ifndef GETCONFIG_H
#define GETCONFIG_H

#include <QObject>
#include "Common/commonfunction.h"

class CGetConfig : public QObject
{
    Q_OBJECT
public:
    explicit CGetConfig(QObject *parent = 0);

    bool GetStartupThreadFlag( bool bSender );
    void GetMgmtSvrIP( QString& strIP );
    quint16 GetMgmtSvrPort( );
    int GetInterval( bool bRequest );
    void GetSQL( bool bRequest, QString& strSql, const QString& strKey );
    QStringList& GetAllTables( bool bRequest );
    void GetFilterSQL( QString &strSql, const QString &strKey );
    QStringList& GetClientIP( );

private:
    void GetAllTableSql( bool bRequest );
    void GetTableFilterSQL( );
    void GetAllClientIP( );

private:
    QSettings* pSystemSet;
    QHash< QString, QString > hashSQL;
    QHash< QString, QString > hashRequestSQL;
    QHash< QString, QString > hashFilterWhereSQL;
    QStringList lstClientIP;
    QStringList lstTables;
    QStringList lstRequestTables;
    
signals:
    
public slots:
    
};

#endif // GETCONFIG_H
