#include "avsdk.h"
#include "HikSDK/hikvision.h"

CAvSdk::CAvSdk()
{

}

CAvSdk::~CAvSdk( )
{

}

CAvSdk* CAvSdk::CreateInstance( AvSdk sdkType )
{
    CAvSdk* pSdk = NULL;

    switch ( sdkType ) {
    case HikSdk :
        pSdk = new CHikVision( );
        break;
    }

    return pSdk;
}

void CAvSdk::DestroyInstance( CAvSdk* pInstance )
{
    if ( NULL != pInstance) {
        delete pInstance;
    }
}
