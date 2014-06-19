#ifndef QSQLSERVER_H
#define QSQLSERVER_H

#include "qmydatabase.h"

class QSqlServer : public QMyDatabase
{
    Q_OBJECT
public:
    virtual ~QSqlServer( );
    static QSqlServer* GetInstance( );

protected:
    explicit QSqlServer(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // QSQLSERVER_H
