#include "commfunction.h"


CommFunction::CommFunction()
{
}

bool CommFunction::VerifyIsEmpty(QString strValue)
{
    if( strValue.isEmpty() )
    {
        QMessageBox::information( NULL, QString("提示"), QString("带*选项的值不能为空， 请重新确认！"), "确定" );
        return true;
    }
    return false;
}

bool CommFunction::VerifyLength(QString strValue, int nLen)
{
    if( strValue.length() > nLen )
    {
        QMessageBox::information( NULL, QString("提示"), QString("长度大于固定的%1位，请重新确认！").arg( nLen ), "确定" );
        return false;
    }
    else if( strValue.length() < nLen )
    {
        QMessageBox::information( NULL, QString("提示"), QString("长度小于固定的%1位，请重新确认！").arg( nLen ), "确定" );
        return false;
    }

    return true;
}

bool CommFunction::VerifyIsNumber(QString strValue)
{
    for( int i = 0; i < strValue.size(); ++i )
    {
        if( !strValue[i].isNumber() )
        {
            QMessageBox::information( NULL, QString("提示"), QString("请输入数字！"), "确定" );
            return false;
        }
    }
    return true;
}

bool CommFunction::VerifyMinMax(QString strValue, int min, int max)
{
    if( strValue.toInt() <= max && strValue.toInt() >= min )
    {
        return true;
    }
    else
    {
        QMessageBox::information( NULL, QString("提示"), QString("请输入%1到%2之间的数，包含%3和%4！").arg( min ).arg( max ).arg( min ).arg( max ), "确定" );
        return false;
    }
}

bool CommFunction::VerifyIsUnique( QString &strSql, QString &strError, QStringList &lstRows, QString strName )
{
    if( !IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql() )
    {
        return false;
    }

    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    if( !lstRows.isEmpty() )
    {
        QMessageBox::information( NULL, QString("提示"), QString("%1").arg( strName ), "确定" ); //QMessageBox::Ok
        return false;
    }

    return true;
}

bool CommFunction::OperateSql( QString &strSql, QString &strError, QStringList &lstRows )
{
    if( !IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql() )
    {
        strError = "连接数据库失败！";
        return false;
    }

    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    if( lstRows.isEmpty() )
    {
        return false;
    }

    return true;
}

void CommFunction::OperateModQuery( QString strSql )
{
    QString strError;
    QStringList lstRows;

    if( !IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql() )
    {
        return;
    }

    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
}

void CommFunction::OperateDb(QString &strSql, QString &strError, QStringList &lstRows)
{
    if( !IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql() )
    {
        strError = "连接数据库失败！";
        return;
    }

    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
}
