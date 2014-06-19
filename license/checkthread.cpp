#include "checkthread.h"
#include "license.h"
#include "processcpuid.h"

CCheckThread* CCheckThread::pThread = NULL;

CCheckThread::CCheckThread( QObject *parent ) :
    QThread(parent)
{
    CLicense& license = CLicense::CreateSingleton( false );
    connect( this, SIGNAL( finished( ) ), this, SLOT( ExitThread( ) ) );
    connect( license.GetDongle( ), SIGNAL( DongleException( QString, bool, bool ) ), this, SLOT( DongleException( QString, bool, bool ) ) );
}

bool CCheckThread::GetBlob( QString& strParkID )
{
    CProcessCpuid process( NULL );

    return process.OperateBlob( byData, strParkID, true );
}

bool CCheckThread::Import2Database( )
{
    CProcessCpuid process( NULL );
    return process.Import2Database( );
}

void CCheckThread::DongleException( QString strMsg, bool bExit, bool bRetry )
{
    emit ExpirationSender( strMsg, bExit, bRetry );
}

CCheckThread& CCheckThread::GetInstance( QObject *parent )
{
    if ( NULL == pThread ) {
        pThread = new CCheckThread( parent );
    }

    return *pThread;
}

void CCheckThread::GetEndDate( QDate& dtDate )
{
    CLicense::CreateSingleton( false ).GetEndDate( dtDate );
}

void CCheckThread::run( )
{
    QString strMsg;
    CLicense& license = CLicense::CreateSingleton( true );
    bool bRet = license.GetPlainText( strMsg, byData );
    if ( !bRet ) {
        emit ExpirationSender( strMsg, !bRet, true );
    } else {
        //while ( true ) {
            if ( false == license.CheckExpiration( strMsg ) ) {
                emit ExpirationSender( strMsg, true, false );
                //break;
            }

        //    sleep( 5 * 60 );
        //}
    }
}

void CCheckThread::ExitThread( )
{
    //delete this;
}
