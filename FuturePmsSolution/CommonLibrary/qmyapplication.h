#ifndef QMYAPPLICATION_H
#define QMYAPPLICATION_H

#include "QCommonFunction_global.h"
#include <QApplication>

class QCOMMONFUNCTIONSHARED_EXPORT QMyApplication : public QApplication
{
    Q_OBJECT
public:
    QMyApplication( int & argc, char ** argv );
    QMyApplication( int & argc, char ** argv, bool GUIenabled );
    QMyApplication( int & argc, char ** argv, Type type );
    virtual ~QMyApplication( );

     bool	winEventFilter ( MSG * msg, long * result );
    
signals:
    
public slots:
    
};

#endif // QMYAPPLICATION_H
