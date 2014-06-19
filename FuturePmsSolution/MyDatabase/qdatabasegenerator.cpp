#include "qdatabasegenerator.h"
QDatabaseGenerator* QDatabaseGenerator::pGenerator = NULL;

QDatabaseGenerator::QDatabaseGenerator(QObject *parent) :
    QObject(parent)
{
}

QDatabaseGenerator* QDatabaseGenerator::GetSingleton( )
{
    if ( NULL == pGenerator ) {
        pGenerator = new QDatabaseGenerator( );
    }

    return pGenerator;
}

QMyDatabase* QDatabaseGenerator::GeneratorDatabaseInstance( const MyEnums::DatabaseType dbType  )
{
    QMyDatabase* pDatabase = NULL;

    switch ( dbType ) {
    case MyEnums::DbMySQL :
        pDatabase = QMySQL::GetInstance( );
        break;

    case MyEnums::DbSQLServer :
        pDatabase = QSqlServer::GetInstance( );
        break;

    case MyEnums::DbSybase :
        break;

    case MyEnums::DbOracle :
        break;

    case MyEnums::DbDB2 :
        break;

    case MyEnums::DbSQLlite :
        break;

    case MyEnums::DbBDB :
        break;

    case MyEnums::DbAccess :
        break;

    case MyEnums::DbPostgreSQL :
        break;
    }

    return pDatabase;
}
