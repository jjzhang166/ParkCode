#include "qsqlserver.h"

QSqlServer::QSqlServer(QObject *parent) :
    QMyDatabase(parent)
{
}

QSqlServer::~QSqlServer( )
{

}

QSqlServer* QSqlServer::GetInstance( )
{
    QSqlServer* pInstance = new QSqlServer( );

    return pInstance;
}
