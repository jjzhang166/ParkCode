#include "qcommonlibrary.h"

const QString QCommonLibrary::strDateTimeFormat = "yyyy-MM-dd HH:mm:ss";
const QString QCommonLibrary::strDateFormat = "yyyy-MM-dd";
const QString QCommonLibrary::strTimeFormat = "HH:mm:ss";


QCommonLibrary::QCommonLibrary( QObject* parent ) : QObject( parent )
{
}

void QCommonLibrary::GetCurrentDateTime( QDateTime &dtDateTime )
{
    dtDateTime = QDateTime::currentDateTime( );
}

void QCommonLibrary::GetCurrentDateTime( QString &strDateTime )
{
    QDateTime dt = QDateTime::currentDateTime( );
    strDateTime = dt.toString( strDateTimeFormat );
}

void QCommonLibrary::DateTime2String( QDateTime &dtValue, QString& strText )
{
    strText = dtValue.toString( strDateTimeFormat );
}

void QCommonLibrary::Date2String( QDate &dValue, QString& strText )
{
    strText = dValue.toString( strDateFormat );
}

void QCommonLibrary::Time2String( QTime &tValue, QString& strText )
{
    strText = tValue.toString( strTimeFormat );
}

QDateTime QCommonLibrary::String2DateTime( QString& strDateTime )
{
    return QDateTime::fromString( strDateTime );
}

QTime QCommonLibrary::String2Time( QString& strTime )
{
    return QTime::fromString( strTime );
}

QDate QCommonLibrary::String2Date( QString& strDate )
{
    return QDate::fromString( strDate );
}

QString& QCommonLibrary::GetDataToken( )
{
    static QString strToken = "EmbededPark";
    return strToken;
}

QString& QCommonLibrary::GetConfigFileName( )
{
    static QString strFileName = "EmbededPark.ini";
    return strFileName;
}

void QCommonLibrary::PrintLog( QString &strText )
{
    if ( strText.isEmpty( ) ) {
        return;
    }

    qDebug( ) << strText << endl;
}

QString QCommonLibrary::GetKeySeperator( )
{
    return "+";
}

bool QCommonLibrary::GetDisplayLog( )
{
    bool bDisplay = true;

    return bDisplay;
}

void QCommonLibrary::AppInitialize( )
{
    QTextCodec *pCodec = GetTextCodec( );
    QTextCodec::setCodecForLocale( pCodec );

    qRegisterMetaType< qintptr >( "qintptr" );
}

QTextCodec* QCommonLibrary::GetTextCodec( )
{
    static QTextCodec* pCodec = NULL;

    if ( NULL != pCodec ) {
        return pCodec;
    }

    QList<QByteArray> lstCodec = pCodec->availableCodecs( );
    QString strText;
    bool bFound = false;

    for ( int nIndex = 0; nIndex < lstCodec.count( ); nIndex++ ) {
        QByteArray byData = lstCodec[ nIndex ];
        strText = QString( byData );

        if ( 0 == strText.toUpper().compare( "GB18030" ) ||
             0 == strText.toUpper().compare( "GBK" ) ||
             0 == strText.toUpper().compare( "GB2312" ) ) {
            bFound = true;
            break;
        }
    }

    if ( !bFound ) {
        strText = QString( "System" );
    }

    QByteArray byData = strText.toLatin1( );
    pCodec = QTextCodec::codecForName( byData );

    return pCodec;
}
