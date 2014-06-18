#ifndef COMMFUNCTION_H
#define COMMFUNCTION_H

#include <QString>
#include <QMessageBox>
#include <QStringList>

#include "Implement/iterfacetomysql.h"

class CommFunction
{
public:
    CommFunction();

    static bool VerifyIsEmpty( QString strValue );
    static bool VerifyLength( QString strValue, int nLen );
    static bool VerifyIsNumber( QString strValue );
    static bool VerifyMinMax( QString strValue, int min, int max );
    static bool VerifyIsUnique(QString &strSql, QString &strError, QStringList &lstRows , QString strName);
    static bool OperateSql( QString &strSql, QString &strError, QStringList &lstRows );
    static void OperateModQuery( QString strSql );

    /////////////////////////////////////////////////
    static void OperateDb( QString &strSql, QString &strError, QStringList &lstRows );

};

#endif // COMMFUNCTION_H
