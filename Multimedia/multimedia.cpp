#include "multimedia.h"
#include <QDebug>
#include "HikSDK/hikvision.h"
#include "TmSDK/tm.h"
#include "JvsSDK/jvssdk.h"

CMultimedia::CMultimedia( QObject *parent ) : QObject( parent )
{
    qDebug( ) << "Hello" << endl;
    pCodec = CCommonFunction::GetTextCodec( );
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgPlate );
}

CMultimedia::~CMultimedia( )
{

}

int CMultimedia::TmEnablePicMessage( int nCards, BOOL bPicMessage, MyPrcPicMessage pPicMessage )
{
    return 0;
}

CMultimedia* CMultimedia::CreateInstance( AvSdk sdkType )
{
    CMultimedia* pSdk = NULL;

    switch ( sdkType ) {
    case HikSdk :
        pSdk = new CHikVision( );
        break;

    case TmSDK :
        pSdk = new CTm( );
        break;

    case JvsSDK :
        pSdk = new CJvsSDK( );
        break;
    }

    return pSdk;
}

void CMultimedia::DestroyInstance( CMultimedia* pInstance )
{
    if ( NULL != pInstance) {
        delete pInstance;
    }
}
