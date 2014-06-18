#include "qcommon.h"
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QDateTime>

QCommon::QCommon(QObject *parent) :
    QObject(parent)
{
}

QTextCodec* QCommon::GetTextCodec( )
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
        qDebug( ) << strText << endl;

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

    pCodec = QTextCodec::codecForName( strText.toAscii( ) );
    return pCodec;
}

void QCommon::GetPlatePicPath( QString &strPath )
{
    strPath = QApplication::applicationDirPath( ) + "/PlatePic/";
    QDir dir( strPath );

    if ( !dir.exists( ) ) {
        dir.mkpath( strPath );
    }
}

void QCommon::GetCurrentDateTime( QString &strDateTime )
{
    strDateTime = QDateTime::currentDateTime( ).toString( "yyyy-MM-dd hh:mm:ss" );
}

void QCommon::PlayMusic( QString& strName, bool bStop )
{
    static Phonon::MediaObject* pMediaObj = NULL;

    if ( bStop ) {
        if ( NULL != pMediaObj ) {
            pMediaObj->clear( );
            delete pMediaObj;
        }

        return;
    }

    if ( NULL == pMediaObj ) {
        pMediaObj = Phonon::createPlayer( Phonon::MusicCategory );
    }

    pMediaObj->clear( );

    QString strPath = qApp->applicationDirPath( ) + "/" + strName + ".wav";
    Phonon::MediaSource mediaSrc( strPath );
    //pMediaObj->setCurrentSource( mediaSrc );
    pMediaObj->enqueue( mediaSrc );
    pMediaObj->play( );
}
