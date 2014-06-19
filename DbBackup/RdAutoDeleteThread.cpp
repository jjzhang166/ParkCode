#include "RdAutoDeleteThread.h"
#include "Common/commonfunction.h"
#include <QDebug>

CRdAutoDeleteThread& CRdAutoDeleteThread::GetInstance( QObject *parent )
{
    CRdAutoDeleteThread* pThread = new CRdAutoDeleteThread( parent );

    return *pThread;
}

CRdAutoDeleteThread::CRdAutoDeleteThread(QObject *parent) :
    QThread(parent)
{
    bStartThread = false;
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgDbMaintain );
    QString strKey = "Options/%1";

    FeeRd = pSet->value( strKey.arg( "FeeRd" ), 0 ).toInt( ) * ( -1 );
    FeeRdAuto = pSet->value( strKey.arg( "FeeRdAuto" ), 0 ).toBool( );
    bStartThread |= FeeRdAuto;

    StopRd = pSet->value( strKey.arg( "StopRd" ), 0 ).toInt( ) * ( -1 );
    StopRdAuto = pSet->value( strKey.arg( "StopRdAuto" ), 0 ).toBool( );
    bStartThread |= StopRdAuto;

    SysLog = pSet->value( strKey.arg( "SysLog" ), 0 ).toInt( ) * ( -1 );
    SysLogAuto = pSet->value( strKey.arg( "SysLogAuto" ), 0 ).toBool( );
    bStartThread |= SysLogAuto;

    ImgRd = pSet->value( strKey.arg( "ImgRd" ), 0 ).toInt( ) * ( -1 );
    ImgRdAuto = pSet->value( strKey.arg( "ImgRdAuto" ), 0 ).toBool( );
    bStartThread |= ImgRdAuto;

    nAutoInterval = pSet->value( strKey.arg( "AutoInterval" ), 300 ).toUInt( );
    tAutoStart = pSet->value( strKey.arg( "AutoStart" ), "23:30:00" ).toTime( );

    connect( this, SIGNAL( finished( ) ), this, SLOT( ExitThread( ) ) );
}

void CRdAutoDeleteThread::run( )
{
    if ( !bStartThread ) {
        return;
    }

    while ( true ) {
        LetSleep( );
        DeleteData( );
        //LetSleep( );
        qDebug( ) << "Auto delete sucess." << endl;
    }
}

void CRdAutoDeleteThread::LetSleep( )
{
    QTime time = QTime::currentTime( );
    int nInterval = 1 * 60;
    int nTime = time.hour( ) * 60 * 60 + time.minute( ) * 60 + time.second( );
    int nStart = tAutoStart.hour( ) * 60 * 60 + tAutoStart.minute( ) * 60 + tAutoStart.second( );
    nTime = nStart - nTime;

    if ( nInterval > qAbs< int >( nTime ) ) {
        return;
    }

    nTime = ( 0 < nTime ) ? ( nTime - nInterval ) : ( 24 * 3600 + nTime - nInterval );
    sleep( nTime );
}

bool CRdAutoDeleteThread::CheckTimePoint( )
{
    bool bRet = false;
    QTime time = QTime::currentTime( );
    int nSecs = 300;

    if ( tAutoStart.addSecs( -1 * nSecs ) <= time && time <= tAutoStart.addSecs( nSecs ) ) {
        return true;
    }

    sleep( nAutoInterval );

    return bRet;
}

void CRdAutoDeleteThread::ExecuteSql( QDate tmpDate, int nIndex )
{
    QString strDate = "";
    CCommonFunction::Date2String( tmpDate, strDate );
    //CLogicInterface::GetInterface( )->DbDeleteRd( nIndex, strDate );
    dbInterf.DbDeleteRd( nIndex, strDate );
}

void CRdAutoDeleteThread::DeleteData( )
{
    QDate date = QDate::currentDate( );

    QStringList lstParams;
    CCommonFunction::ConnectMySql( lstParams );
    bool bRet = dbInterf.GetMysqlDb( ).DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );
    if ( false == bRet ) {
        return;
    }

    if ( FeeRdAuto ) {
        ExecuteSql( date.addDays( FeeRd ), 1 );
    }

    if ( StopRdAuto ) {
        ExecuteSql( date.addDays( StopRd ), 2 );
    }

    if ( SysLogAuto ) {
        ExecuteSql( date.addDays( SysLog ), 3 );
    }

    if ( ImgRdAuto ) {
        ExecuteSql( date.addDays( ImgRd ), 4 );
    }

    dbInterf.GetMysqlDb( ).DbDisconnect( );
}

void CRdAutoDeleteThread::ExitThread( )
{
    delete this;
}
