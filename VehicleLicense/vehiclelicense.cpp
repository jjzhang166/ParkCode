#include "vehiclelicense.h"
#ifdef RAW_API
#include "WinTone/rawwintone.h"
#else
#include "WinTone/wintone.h"
#endif
#include <QtGui/QApplication>

// Load library Style Call 'C' Style Function
CVehicleLicense::CVehicleLicense( QObject* parent ) : QObject(parent)
{
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgPlate );
    bRegVideo = false;
    bStoping = false;

    pCodec = CCommonFunction::GetTextCodec( );
}

CVehicleLicense::~CVehicleLicense( )
{

}

void CVehicleLicense::SetStop(bool bStop)
{
    bStoping = bStop;
}

CVehicleLicense* CVehicleLicense::CreateInstance( LicenseSdk sdkType )
{
    CVehicleLicense* pSdk = NULL;

    switch ( sdkType ) {
    case WinToneSdk :
#ifdef RAW_API
        pSdk = new CRawWintone( );
#else
        pSdk = new CWinTone( );
#endif
        break;
    }

    return pSdk;
}

void CVehicleLicense::SetMsgBox( QString& strText, QString& strTitle,
                                 QMessageBox::StandardButton stdButton,
                                 QMessageBox::Icon ico )
{
    msgBox.setIcon( ico );
    msgBox.setWindowTitle( strTitle );
    msgBox.setText( strText );
    msgBox.setStandardButtons( stdButton );
}

void CVehicleLicense::DestroyInstance( CVehicleLicense* pInstance )
{
    if ( NULL != pInstance) {
        delete pInstance;
    }
}
