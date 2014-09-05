#include "ccmdfactory.h"

CControllerCmd* CCmdFactory::pXwCtrl = NULL;
CControllerCmd* CCmdFactory::pVzCtrl = NULL;

CCmdFactory::CCmdFactory(QObject *parent) :
    QObject(parent)
{
}

CControllerCmd* CCmdFactory::CreateCmd( CtrlType eType )
{
    CControllerCmd* pCmd = NULL;

    switch ( eType ) {
    case CtrlXw :
        if ( NULL == pXwCtrl ) {
            pXwCtrl = new CXwCtrlCmd( );
        }

        pCmd = pXwCtrl;
        break;

    case CtrlVz :
        if ( NULL == pVzCtrl ) {
            pVzCtrl = new CVzCtrlCmd( );
        }

        pCmd = pVzCtrl;
        break;
    }

    return pCmd;
}
