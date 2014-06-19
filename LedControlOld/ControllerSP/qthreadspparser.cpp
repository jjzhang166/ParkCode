#include "qthreadspparser.h"
#include <QApplication>
#include "../ControllerCommon/qctrlevent.h"
#include <QDebug>

QThreadSPParser* QThreadSPParser::pSingleton = NULL;

QThreadSPParser::QThreadSPParser(QObject *parent) :
    QThread(parent)
{
    cmdController = QControllerCmd::GetSingleton( );
}

QThreadSPParser& QThreadSPParser::GetSingleton( )
{
    if ( NULL == pSingleton )   {
        pSingleton = new QThreadSPParser( );
        pSingleton->start( );
        pSingleton->moveToThread( pSingleton ) ;
    }

    return *pSingleton;
}

void QThreadSPParser::SendData( QByteArray &data )
{
    QCtrlEvent* pEvent = new QCtrlEvent( ( QCtrlEvent::Type ) QCtrlEvent::SPWrite );
    pEvent->SetData( data );
    qApp->postEvent( this, pEvent );
}

void QThreadSPParser::run( )
{
    exec( );
}

bool QThreadSPParser::ParseData( )
{
    bool bRet = false;
    //
    // GetFrame ( YiBin )
    //

    const char cAddrValue = ( char ) 0x00;//0xAA;
    const char cStartFrame = 0x68;
    const char cEndFrame = 0x16;

    char cHead[ ] = { cStartFrame, cAddrValue, cAddrValue,
                      cAddrValue, cAddrValue, cAddrValue, cAddrValue, cStartFrame };
    QByteArray byHead( cHead, sizeof ( cHead ) );

    int nHead = sizeof ( cHead );
    int nLen = nHead + 2;
    int nTotal = byData.length( );

    if ( nLen >= nTotal ) {
        return bRet;
    }

    qint32 nIndex = byData.indexOf( byHead );
    if ( -1 == nIndex ) {
        byData.clear( );
        return bRet;
    } else if ( 0 < nIndex ) {
        byData.remove( 0, nIndex );
    }

    nTotal = byData.length( );
    if ( nLen >= nTotal ) {
        return bRet;
    }

    quint8 cCtrlCode = byData.at( nHead );

    qint32 nDataLen = 0;
    QByteArray byDataDomain;

    switch ( cCtrlCode ) {
    case 0x91 : // Query 无后续数据帧
    case 0xB1 : // Query 有后续数据帧
        nDataLen = byData[ nLen - 1 ];
        nLen += nDataLen + 2;
        if ( nLen > nTotal ) {
            return bRet;
        }

        if ( cEndFrame == byData[ nLen - 1 ] ) {
            byDataDomain = byData.mid( nHead + 2, nDataLen );
            for ( int nIndex = 0; nIndex < byDataDomain.length( ); nIndex++ ) {
                byDataDomain[ nIndex ] = byDataDomain.at( nIndex ) - 0x33;
            }

            ProcessData( 0xB1 == cCtrlCode, byDataDomain );
        }
        break;

    case 0x94 : // Write 成功
        nLen += 2;
        if ( nLen > nTotal ) {
            return bRet;
        }

        if ( cEndFrame == byData[ nLen - 1 ] ) {
            ProcessSuccess( );
        }
        break;

    case 0xD1 : // Query 错误信息
    case 0xD4 : // Write
        nLen += 3;
        if ( nLen > nTotal ) {
            return bRet;
        }

        if ( cEndFrame == byData[ nLen - 1 ] ) {
            ProcessError( byData.at( nLen - 3 ), 0xD4 == cCtrlCode );
        }
        break;
    }

    if ( cEndFrame == byData[ nLen - 1 ] ) {
        emit Cmd( byData.mid( 0, nLen ), false ); // Cmd Frame
    }

    byData.remove( 0, nLen );
    nTotal = byData.length( );
    bRet = ( nLen <= nTotal );

    return bRet;
}

void QThreadSPParser::ProcessData( const bool bSubsequence, QByteArray& data )
{
    qDebug( ) << QString( data.toHex( ).toUpper( ) );

    if ( 4 > data.length( ) ) {
        return;
    }

    if ( bSubsequence ) {
        ;
    } else {
        QString strInfo;
        qint8 nIndex = 0;
        cmdController->ParseDataDomain( data, strInfo, nIndex );

        emit Query( strInfo, nIndex, data );
    }
}

void QThreadSPParser::ProcessSuccess( )
{
    qDebug( ) << "Success" << endl;
}

void QThreadSPParser::ProcessError( const char cErrorCode, const bool bWrite )
{
    char cError = cErrorCode - 0x33;
    qDebug( ) << ( bWrite ? "Write Error " : "Query Error " ) << QString::number( cError ) << endl;
}

void QThreadSPParser::customEvent( QEvent *e )
{
    QCtrlEvent* pEvent = (  QCtrlEvent* ) e;
    bool bRet = false;

    if ( QCtrlEvent::SPParse == ( QCtrlEvent::CtrlEvent ) pEvent->type( ) ) {
        //qDebug( ) << "QThreadSPParser: " << pEvent->GetData( ).toHex( ).toUpper( ) << endl;
        byData.append( pEvent->GetData( ) );

        do {
            bRet = ParseData( );
        } while ( bRet );
    }
}
