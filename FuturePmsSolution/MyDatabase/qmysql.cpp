#include "qmysql.h"

QMySQL::QMySQL(QObject *parent) :
    QMyDatabase(parent)
{
}

QMySQL::~QMySQL( )
{

}

QMySQL* QMySQL::GetInstance( )
{
    QMySQL* pInstance = new QMySQL( );

    return pInstance;
}
