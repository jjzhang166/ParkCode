#include "Timer\timerthread.h"
#include "Common/commonfunction.h"
#include <QThreadPool>
#include "timerproc.h"

CTimerThread::CTimerThread(QObject *parent) :
    QThread(parent)
{
    connect( this, SIGNAL( finished( ) ), this, SLOT( ExitThread( ) ) );
    GetConfig( );
}

void CTimerThread::ExitThread( )
{
    delete this;
}

CTimerThread* CTimerThread::GetInstance( )
{
    return new CTimerThread( );
}

void CTimerThread::GetConfig( )
{
    QSettings* pSystem = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    bPeriodic = pSystem->value( "Timer/Periodic", false ).toBool( );
    strTime = pSystem->value( "Timer/Time", "02:00:00" ).toString( );
}

quint32 CTimerThread::CalculateFirstTime( )
{
    QTime tCurrent = QTime::currentTime( );
    QTime tTime = QTime::fromString( strTime );
    quint32 nInterval = 0;
    quint32 nHour24 = 24 * 3600;

     qint32 nDiff = ( tCurrent.hour( ) - tTime.hour( ) ) * 3600 +
                            ( tCurrent.minute( ) - tTime.minute( ) ) * 60 +
                            tCurrent.second( ) - tTime.second( );

    if ( 0 < nDiff ) { // tCurrent > tTime
        nInterval = nHour24 - nDiff;
    } else if ( 0 > nDiff ) { // tCurrent < tTime
        nInterval = ( quint32 ) qAbs< int >( nDiff );
    } else { // tCurrent == tTime
        nInterval = 0;
    }

    return nInterval;
}

void CTimerThread::StartTimerProc( )
{
    QThreadPool* pPool = QThreadPool::globalInstance ( );
    pPool->start( CTimerProc::GetInstance( ) );
}

void CTimerThread::run( )
{
    quint32 nInterval = CalculateFirstTime( );
    quint32 nHour24 = 24 * 3600;

    do {
        sleep( nInterval);
        nInterval = nHour24;
        StartTimerProc( );
    } while ( bPeriodic );
}
