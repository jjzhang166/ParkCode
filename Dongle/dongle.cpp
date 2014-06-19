#include "dongle.h"

const quint32 CDongle::dwCustomerID[ 2 ] = { 0x3660F464, 0x2C1CEE5E };
const quint8 CDongle::bATR[ 2 ][ 16 ] = { { 0x3B, 0x09, 0x45, 0x54, 0x31, 0x39, 0x39, 0x56, 0x31, 0x34, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00 },
                                          //{ 0x3B, 0x09, 0x45, 0x54, 0x31, 0x39, 0x39, 0x56, 0x32, 0x30, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00}
                                          { 0x5A, 0x63, 0x79, 0x26, 0x4C, 0x64, 0x5A, 0x63, 0x79, 0x26, 0x4C, 0x64, 0x43, 0x44, 0x53, 0x43 } };
const QString CDongle::strCustomerSeed[ 2 ] = { "四川前途高科电子技术有限公司", "赵长扬 廖东" };
// 无时间 ATR【Zcy&LdZcy&LdCDSC】
CDongle::CDongle( QObject* parent ) : QObject( parent )
{
    nTimerCheckID = 0;
    nTimerOpen = 0; //startTimer( 10000 );
}

CDongle::~CDongle( )
{
    if ( 0 != nTimerCheckID ) {
        killTimer( nTimerCheckID );
    }

    if ( 0 != nTimerOpen ) {
        killTimer( nTimerOpen );
    }
}

void CDongle::MyStartTimer( )
{
    nTimerCheckID = startTimer(  1 * 60 * 1000 );
}

void CDongle::timerEvent( QTimerEvent *event )
{
    if (  nTimerCheckID == event->timerId( ) ) {
        DongleDetection( bVerifyDate );
    } else if ( nTimerOpen == event->timerId( ) ) {
        DongleTimerOpen( );
    }
}

void CDongle::SetDate( QDate &start, QDate &end )
{
    dateStart = start;
    dateEnd = end;
}

void CDongle::SetVerifyDate( bool bVerifyDate )
{
    bVerifyDate = bVerifyDate;
}
