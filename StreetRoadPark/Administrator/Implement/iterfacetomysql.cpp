#include "iterfacetomysql.h"

IterfaceToMySql * IterfaceToMySql::g_interface = 0;
IterfaceToMySql::IterfaceToMySql( )
{
}

CMySqlDatabase & IterfaceToMySql::GetMySqlDb()
{
    return mySqlDb;
}


IterfaceToMySql * IterfaceToMySql::GetInterface()
{
    if ( 0 == g_interface ) {
        g_interface = new IterfaceToMySql( );
    }

    return g_interface;
}
