#ifndef QDATABASSEGENERATOR_H
#define QDATABASSEGENERATOR_H

#include <QObject>
#include "qsqlserver.h"
#include "qmysql.h"
#include "MyDatabase_global.h"

#include "../CommonLibrary/CommonEnum.h"

class MYDATABASESHARED_EXPORT QDatabaseGenerator : public QObject
{
    Q_OBJECT
public:
    static QDatabaseGenerator* GetSingleton( );

    QMyDatabase* GeneratorDatabaseInstance( const MyEnums::DatabaseType dbType );

protected:
    explicit QDatabaseGenerator(QObject *parent = 0);

private:
    static QDatabaseGenerator* pGenerator;
    
signals:
    
public slots:
    
};

#endif // QDATABASSEGENERATOR_H
