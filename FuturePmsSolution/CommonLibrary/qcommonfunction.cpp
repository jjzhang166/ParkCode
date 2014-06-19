#include "qcommonfunction.h"
#include <QMetaEnum>
#include <QApplication>
#include <QDir>
#include "CommonMacro.h"

QCommonFunction::QCommonFunction(QObject *parent) :
    QObject(parent)
{
    strDateFormat = "yyyy-MM-dd";
    strTimeFormat = "HH:mm:ss";
}

QCommonFunction::~QCommonFunction( )
{

}

void QCommonFunction::GetPathTypeName( PathTypes type, QString &strName )
{
    QMetaEnum metaEnum = metaObject( )->enumerator( 0 );
    strName = metaEnum.key( type );
}

void QCommonFunction::GetPath( QString &strPath, const PathTypes type )
{
    QString strSeperator = "/";
    QString strName;

    GetPathTypeName( type, strName );
    strPath = qApp->applicationDirPath( ) + strSeperator + strName + strSeperator;

    MakePath( strPath );
}

QTextCodec* QCommonFunction::GetTextCodec( ) const
{
    static QTextCodec* pCodec = NULL;

    if ( NULL != pCodec ) {
        return pCodec;
    }

    QList<QByteArray> lstCodec = pCodec->availableCodecs( );
    QString strMsg;
    bool bFound = false;

    for ( int nIndex = 0; nIndex < lstCodec.count( ); nIndex++ ) {
        QByteArray byData = lstCodec[ nIndex ];
        strMsg = QString( byData );
        OutputMsg( strMsg );

        if ( 0 == strMsg.toUpper().compare( "GB18030" ) ||
             0 == strMsg.toUpper().compare( "GBK" ) ||
             0 == strMsg.toUpper().compare( "GB2312" ) ) {
            bFound = true;
            break;
        }
    }

    if ( !bFound ) {
        strMsg = QString( "System" );
    }

    pCodec = QTextCodec::codecForName( strMsg.toAscii( ) );

    return pCodec;
}

void QCommonFunction::InstallTextCodec( ) const
{
    // MBCS(DBCS) UCS
    // ASCI ANSI ISO14060 GB2313 GBK GB18030 GB13000 BIG5 CJK
    //GBK、GB2312 GB18030－－Unicode－－UTF8
    //UTF8－－Unicode－－GBK、GB2312 GB18030
    QTextCodec *pCodec = GetTextCodec( );// QTextCodec::codecForName( "GB18030" );    //System//获取系统编码

    QTextCodec::setCodecForLocale( pCodec );
    QTextCodec::setCodecForCStrings( pCodec );
    QTextCodec::setCodecForTr( pCodec );
}

void QCommonFunction::MakePath( const QString& strPath ) const
{
    QDir dir;

    if ( dir.exists( strPath ) ) {
        return;
    }

    if ( !dir.mkpath( strPath ) ) {
        OutputMsg( QString( "dir.mkpath( %1 )" ).arg( strPath ) );
    }
}

void QCommonFunction::SetDateTimeFormat( )
{
    LCID localeID = ::GetSystemDefaultLCID( );

    BOOL bRet = ::SetLocaleInfo( localeID, LOCALE_SSHORTDATE, L"yyyy-M-d" );
    bRet = ::SetLocaleInfo( localeID, LOCALE_SDATE, L"-" );

    bRet = ::SetLocaleInfo( localeID, LOCALE_STIMEFORMAT, L"H:mm:ss" );
    bRet = ::SetLocaleInfo( localeID, LOCALE_STIME, L":" );

    QString strFormat = "yyyy'年'M'月'd'日' dddd";
    LPCWSTR lpLongFormat = ( LPCWSTR ) strFormat.utf16( );
    bRet = ::SetLocaleInfo( localeID, LOCALE_SLONGDATE, lpLongFormat );
}

QString QCommonFunction::GetDateString( const QDate& date )
{
    return date.toString( strDateFormat );
}

QString QCommonFunction::GetTimeString( const QTime& time )
{
    return time.toString( strTimeFormat );
}

QString QCommonFunction::GetDateTimeString( const QDateTime& dateTime )
{
    return dateTime.toString( strDateFormat + " " + strTimeFormat );
}

QDate QCommonFunction::GetStringDate( const QString& strDate )
{
    return QDate::fromString( strDate, strDateFormat );
}

QTime QCommonFunction::GetStringTime( const QString& strTime )
{
    return QTime::fromString( strTime, strTimeFormat );
}

QDateTime QCommonFunction::GetStringDateTime( const QString& strDateTime )
{
    return QDateTime::fromString( strDateTime, strDateFormat + " " + strTimeFormat );
}
