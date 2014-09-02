#include "ccmdfactory.h"

CCmdFactory::CCmdFactory(QObject *parent) :
    QObject(parent)
{
}

CControllerCmd* CCmdFactory::CreateCmd( CtrlType eType )
{
    CControllerCmd* pCmd = NULL;

    switch ( eType ) {
    case CtrlXw :
        pCmd = new CXwCtrlCmd( );
        break;

    case CtrlVz :
        pCmd = new CVzCtrlCmd( );
        break;
    }

    return pCmd;
}
