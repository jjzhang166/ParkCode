#include "ftp.h"
#include "../Common/logicinterface.h"

QStringList CFtp::lstFtpServer;

CFtp::CFtp( QObject *parent ) :
    QThread(parent)
{
    ftpClient.setParent( this );
    bool bRet = connect( this, SIGNAL( terminated( ) ), this, SLOT( ThreadExit( ) ) );
    bRet = connect( &ftpClient, SIGNAL( commandFinished( int, bool ) ), this, SLOT( FtpCmdFinished( int, bool ) ) );
    bRet = connect( &ftpClient, SIGNAL( stateChanged( int ) ), this, SLOT( StateChanged( int ) ) );
}

void CFtp::GetCommonParams( )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    lstFtpServer << pSet->value( "CenterServer/FtpIP" ).toString( )
                       << pSet->value( "CenterServer/FtpPort" ).toString( )
                       << pSet->value( "CenterServer/FtpUser" ).toString( )
                       << pSet->value( "CenterServer/FtpPwd" ).toString( );
}

void CFtp::GetImgData( QByteArray& byData, QStringList& lstParams )
{
    // PARKID / bool( 1 : plate 0 : cardid)  / Plate | CardID / IOFlag / DateTime
    //lstParams

    QString strTrue = "1";
    CLogicInterface* pInterface = CLogicInterface::GetInterface( );
    bool bPlate = ( strTrue == lstParams[ 1 ] );
    bool bEnter =  ( strTrue == lstParams[ 3 ] );
    QString strWhere = QString( "Where %1 = '%2' and %3time = '%4'" ).arg( bPlate ?
                                                                               QString ( "carcp%1" ).arg( bEnter ? "" : "out" ) : "cardno",
                                                lstParams[ 2 ], bEnter ? "in" : "out",  lstParams[ 4 ] );

    CommonDataType::BlobType blob = bEnter ? CommonDataType::BlobVehicleIn1: CommonDataType::BlobVehicleOut1;
    pInterface->OperateBlob( byData, false, blob, strWhere );
}

void CFtp::StateChanged( int nState )
{
    if ( QFtp::Unconnected == nState ) {
        ftpClient.connectToHost( lstFtpServer[ 0 ], lstFtpServer[ 1 ].toUShort( ) );
        ftpClient.login( lstFtpServer[ 2 ], lstFtpServer[ 3 ] );
        qDebug( ) << ftpClient.errorString( ) << endl;
    }
}

bool CFtp::SendFile( QStringList& lstParams )
{

    if ( 5 > lstParams.count( ) ) {
        return true;
    }

    if ( QFtp::Unconnected == ftpClient.state( ) ) {
        StateChanged( QFtp::Unconnected );
    }

    QByteArray* pData = new QByteArray( );
    GetImgData( *pData, lstParams );
    if ( 0 == pData->count( ) ) {
        delete pData;
        return true;
    }

    QString strDateTime = lstParams[ 4 ];
    static QString strFormat1 = "yyyy-M-d H:m:s";
    static QString strFormat2 = "yyyyMMddHHmmss";
    static QString strFormat3 = "%1_%2_%3_%4_%5.JPG";
    QDateTime dt = QDateTime::fromString( strDateTime, strFormat1 );
    strDateTime = dt.toString( strFormat2 );

    QString strSvrFile = strFormat3.arg( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], strDateTime );
    //ftpClient.mkdir( strDir );

    QString strEncodingFile = "";
    Encoding( strSvrFile, strEncodingFile );
    int nPut = ftpClient.put( *pData, strEncodingFile );
    qDebug( ) << ftpClient.errorString( ) << endl;
    dataHash.insert( nPut, pData );

    return true;
}

void CFtp::Encoding( QString &strRaw, QString &strResult )
{
    QByteArray byRaw;
#ifdef Q_OS_WIN
    byRaw = strRaw.toLocal8Bit( );
#else
    byRaw = CCommonFunction::GetTextCodec( )->fromUnicode( strRaw );
#endif

    strResult = QString::fromLatin1( byRaw.data( ), byRaw.count( ) );
}

void CFtp::Decoding( QString &strRaw, QString &strResult )
{
    QByteArray byRaw = strRaw.toLatin1( );

#ifdef Q_OS_WIN
    strResult = QString::fromLocal8Bit( byRaw.data( ), byRaw.count( ) );
#else
    strResult = CCommonFunction::GetTextCodec( )->toUnicode( byRaw );
#endif
}

void CFtp::run( )
{
    exec( );
}

void CFtp::customEvent( QEvent *e )
{
    CFtpEvent::FtpEvent event = ( CFtpEvent::FtpEvent ) e->type( );
    CFtpEvent* pEvent = ( CFtpEvent* ) e;
    switch ( event ) {
    case CFtpEvent::FtpPut :
        SendFile( pEvent->GetParams( ) );
        break;
    }
}

void CFtp::FtpCmdFinished( int nId, bool bError )
{
#ifndef QT_NO_DEBUG
    QString str = ftpClient.errorString( );
    qDebug( ) << str << endl;
#endif

    QFtp::Command cmd = ftpClient.currentCommand( );
    if ( cmd == QFtp::Put ) {
        QByteArray* pData = dataHash.value( nId );
        dataHash.remove( nId );
        delete pData;
        //ftpClient.close( );
    }
}

void CFtp::ThreadExit( )
{
    delete this;
}
