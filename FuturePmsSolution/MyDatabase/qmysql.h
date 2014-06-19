#ifndef QMYSQL_H
#define QMYSQL_H

#include "QMyDatabase.h"

class QMySQL : public QMyDatabase
{
    Q_OBJECT
public:
    ~QMySQL( );
    static QMySQL* GetInstance( );

protected:
    explicit QMySQL(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // QMYSQL_H
