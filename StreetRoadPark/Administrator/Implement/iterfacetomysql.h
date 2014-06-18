#ifndef ITERFACETOMYSQL_H
#define ITERFACETOMYSQL_H

#include "Database/mysqldatabase.h"

class IterfaceToMySql
{
public:
    IterfaceToMySql();
    CMySqlDatabase &GetMySqlDb();
    static IterfaceToMySql *GetInterface();

private:
    CMySqlDatabase mySqlDb;
    static IterfaceToMySql * g_interface;
};

#endif // ITERFACETOMYSQL_H
