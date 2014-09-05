#ifndef CCMDFACTORY_H
#define CCMDFACTORY_H

#include <QObject>
#include "cvzctrlcmd.h"
#include "cxwctrlcmd.h"

class CCmdFactory : public QObject
{
    Q_OBJECT
public:

    static CControllerCmd* CreateCmd( CtrlType eType );

private:
    explicit CCmdFactory(QObject *parent = 0);

    static CControllerCmd* pXwCtrl;
    static CControllerCmd* pVzCtrl;
    
signals:
    
public slots:
    
};

#endif // CCMDFACTORY_H
