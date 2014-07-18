#include "dongle.h"
// 0 ETDiamond 1 ET199
const quint32 CDongle::dwCustomerID[ 2 ] = { 0x58F14D84, 0x8F4E0C43 };
const quint8 CDongle::bATR[ 2 ][ 16 ] = { { 0x3B, 0x09, 0x45, 0x54, 0x31, 0x39, 0x39, 0x56, 0x31, 0x34, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00 },
                                          //{ 0x3B, 0x09, 0x45, 0x54, 0x31, 0x39, 0x39, 0x56, 0x32, 0x30, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00}
                                          { 0x5A, 0x68, 0x61, 0x6F, 0x43, 0x59, 0x26, 0x4C, 0x69, 0x61, 0x6F, 0x44, 0x00, 0x00, 0x00, 0x00 } };
const QString CDongle::strCustomerSeed[ 2 ] = { "", "赵长扬 廖东" };
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
