#include "ccontrollercmd.h"
#include <QDateTime>

CControllerCmd::CControllerCmd(QObject *parent) :
    QObject(parent)
{
}

void CControllerCmd::Convert2Hex( char& cData, int nData )
{
    // 28( Decimal )--->28( String )--->40( Hex )
    cData = QString::number( nData ).toUInt( 0, 16 );
}

void CControllerCmd::GetDateTimeWeek( char& cHYear, char& cLYear,
                                      char& cMonth, char& cDay,
                                      char&cHour, char& cMinute,
                                      char& cSecond, char& cWeek )
{
    QDateTime dtCurrent = QDateTime::currentDateTime( );
    QDate dDate = dtCurrent.date( );
    QTime tTime = dtCurrent.time( );

    int nYear = dDate.year( );
    Convert2Hex( cLYear, nYear % 100 );
    Convert2Hex( cHYear, ( nYear - nYear % 100 ) / 100 );

    int nMonth = dDate.month( );
    Convert2Hex( cMonth, nMonth );

    int nDay = dDate.day( );
    Convert2Hex( cDay, nDay );

    int nHour = tTime.hour( );
    Convert2Hex( cHour, nHour );

    int nMinute = tTime.minute( );
    Convert2Hex( cMinute, nMinute );

    int nSecond = tTime.second( );
    Convert2Hex( cSecond, nSecond );

    int nWeek = dDate.dayOfWeek( );
    Convert2Hex( cWeek, nWeek );
}
