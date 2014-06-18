#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QPixmap>
#include <windows.h>
#include "qresponseevent.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nBytesAvailable = 0;
    nPakageSize = 0;
    pCodec = QTextCodec::codecForName( "GB2312" );
    QTextCodec::setCodecForLocale( pCodec );
    QTextCodec::setCodecForCStrings( pCodec );
    QTextCodec::setCodecForTr( pCodec );

    connect( &tcpSocket, SIGNAL( readyRead( ) ), this, SLOT( IncomingData( ) ) );

    if ( true ) {
        //Connect2Host( );
    } else {
        connect( &listener, SIGNAL( Accept( int ) ), this, SLOT( HandleAccept( int ) ) );
        listener.moveToThread( &listener );
        listener.start( );
    }

    pResposeThread = QProcessResponseThread::GetSingleton( );

    connect( pResposeThread, SIGNAL( PlateImg( QString ) ), this, SLOT( HandlePlateImg( QString ) ) );
    connect( pResposeThread, SIGNAL( Response( QString ) ), this, SLOT( HandleResponse( QString ) ) );
}

void MainWindow::HandlePlateImg( QString strFile )
{
    QPixmap pixmap( strFile );
    ui->lblPic->setPixmap( pixmap );
}

void MainWindow::HandleResponse( QString strMsg )
{
    ui->edtResponse->append( strMsg );
}

bool MainWindow::Connect2Host( )
{
    QAbstractSocket::SocketState state = tcpSocket.state( ) ;
    if ( QAbstractSocket::ConnectedState == state ) {
        return true;
    }

    QString strIP = ui->edtIP->text( );
    if ( strIP.isEmpty( ) ) {
        strIP = "127.0.0.1";
    }

    QString strPort = ui->edtPort->text( );
    if ( strPort.isEmpty( ) ) {
        strPort = "60000";
    }

    QHostAddress addr( strIP );//127.0.0.1
    quint16 nPort = strPort.toUShort( );
    tcpSocket.connectToHost( addr, nPort );

    return QAbstractSocket::ConnectedState == tcpSocket.state( );
}

MainWindow::~MainWindow()
{
    listener.terminate();
    delete ui;
}

void MainWindow::HandleAccept( int socketDescriptor )
{
    tcpSocket.setSocketDescriptor( socketDescriptor );
}

QString MainWindow::GetByteDataString( void *pData, quint8 nLength )
{
    QByteArray byTmp;
    byTmp.resize( nLength );

    memcpy( byTmp.data( ), pData, nLength );

    return QString( byData );
}

QByteArray MainWindow::GetToken( QByteArray& byStream )
{
    return byStream.mid( 0, Protocol::nTokenLength );
}

quint8 MainWindow::GetMessageType( QByteArray& byStream )
{
    return ( quint8 ) byStream.at( Protocol::nTokenLength );
}

QByteArray MainWindow::GetBody( QByteArray &byStream )
{
    return byStream.right( byStream.length( ) - Protocol::nHeadLength );
}

quint32 MainWindow::GetStreamLength( QByteArray& byStream )
{
    QByteArray byLen = byStream.mid( Protocol::nTokenLength + sizeof ( quint8 ), sizeof( quint32 ) );
    quint32* pLen = ( quint32* ) byLen.data( );

    return ntohl( *pLen );
}

void MainWindow::ParseResponseData( QByteArray &byData )
{
    ProcessResponse( byData );
}

void MainWindow::ProcessBallotSenseResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "A地感地址：%1\nA地感状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );

    AppendResponse( strMsg );
}

void MainWindow::ProcessActiveSendResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "地址：%1\n状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );

    AppendResponse( strMsg );
}

void MainWindow::ProcessGateSenseResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "B地感地址：%1\nB地感状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );

    AppendResponse( strMsg );
}

void MainWindow::AppendResponse( QString& strMsg )
{
    ui->edtResponse->append( strMsg + "\n" );
}

void MainWindow::ProcessInfraredResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "红外地址：%1\n红外状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );

    AppendResponse( strMsg );
}

void MainWindow::ProcessPlateResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    qint32 nIndex = 0;
    quint8 nAddress = byBody.at( nIndex );

    nIndex += sizeof ( quint8 );
    QByteArray byDateTime = byBody.mid( nIndex, Protocol::nDateTimeLength );
    QString strDateTime ( byDateTime );

    nIndex += Protocol::nDateTimeLength;
    quint8 nConfidence = byBody.at( nIndex );

    nIndex += sizeof ( quint8 );
    quint8 nPlateByteCount = byBody.at( nIndex );

    nIndex += sizeof ( quint8 );
    quint32 nPictureByteCount =*( quint32*  ) ( byBody.data( ) + nIndex );
    nPictureByteCount = ntohl( nPictureByteCount );

    nIndex += sizeof ( quint32 );
    QByteArray byPlate = byBody.mid( nIndex, nPlateByteCount );
    QString strPlate( byPlate );

    QString strMsg;
    strMsg = QString( "车牌地址：%1\n获取时间：%2\n可信度：%3\n车牌：%4" ).arg(
                        QString::number( nAddress ),
                        strDateTime,
                        QString::number( nConfidence ),
                        strPlate );

    AppendResponse( strMsg );

    nIndex += nPlateByteCount;
    QByteArray byPicture = byBody.mid( nIndex, nPictureByteCount );
    QFile file;
    QString strSingle = QString( "snapshot\\A%1D%2C%3P%4.jpg" ).arg( QString::number( nAddress ),
                                                                     strDateTime,
                                                                     QString::number( nConfidence ),
                                                                     strPlate );
    QString strFile = strSingle;//ui->chk->isChecked( ) ? strSingle : "tmp.jpg";

    file.setFileName( strFile );
    bool bRet = file.open( QIODevice::ReadWrite | QIODevice::Truncate );
    if ( !bRet ) {
        return;
    }

    file.write( byPicture );
    file.close( );

    QPixmap pixmap( strFile );
    ui->lblPic->setPixmap( pixmap );
}

void MainWindow::ProcessResponse( QByteArray &byStream )
{
    QByteArray byToken = GetToken( byStream );
    if ( byToken != Protocol::byToken ) {
        return;
    }

    Protocol::RequestType nMessageType = ( Protocol::RequestType ) GetMessageType( byStream );

    switch ( nMessageType ) {
    case Protocol::ResponseBallotSenseState :
        ProcessBallotSenseResponse( byStream );
        break;

    case Protocol::ResponseGateSenseState :
        ProcessGateSenseResponse( byStream );
        break;

    case Protocol::ResponseInfraredState :
        ProcessInfraredResponse( byStream );
        break;

    case Protocol::ResponsePlateData :
        ProcessPlateResponse( byStream );
        break;

    case Protocol::ResponseActiveSend :
        ProcessActiveSendResponse( byStream );
        break;
    }
}

void MainWindow::DisplayPic( quint8 *pData, quint32 nLength )
{
    if ( 0 == nLength ) {
        return;
    }

    qDebug( ) << " Picture size : " << nLength << endl ;

    QFile file( "plate.jpg" );
    if ( !file.open( QIODevice::ReadWrite | QIODevice::Truncate ) ) {
        return;
    }

    file.write( ( const char* ) pData, nLength );
    file.close( );

    QPixmap pixmap( "plate.jpg" );
    ui->lblPic->setPixmap( pixmap );
}

bool MainWindow::ParseMultipleResponseData( QByteArray &byResponse )
{
    bool bRet = false;
    qint32 nIndex = byResponse.indexOf( Protocol::byToken );

    if ( -1 == nIndex ) {
        byResponse.clear( );
        return bRet; // No Head
    }

    if ( 0 < nIndex) { // Remove
        byResponse.remove( 0, nIndex );
    }

    qint32 nLen = Protocol::nTokenLength;
    if ( nLen == byResponse.length( ) ) {
        return bRet;
    }

    nLen += sizeof ( quint8 ); // MessageType
    nLen += sizeof ( quint32 ); // TcpStreamLength

    if ( nLen >= byResponse.length( ) ) {
        return bRet;
    }

    quint32 nTotal = GetStreamLength( byResponse );
    if ( nTotal > byResponse.length( ) ) {
        return bRet;
    }

    switch ( GetMessageType( byResponse ) ) {
    case Protocol::ResponseBallotSenseState :
        //nLen += 2;
        break;

    case Protocol::ResponseGateSenseState :
        //nLen += 2;
        break;

    case Protocol::ResponseInfraredState :
        //nLen += 2;
        break;

    case Protocol::ResponsePlateData :
        //nLen += 2;
        break;

    case Protocol::ResponseActiveSend :
        //nLen += 2;
        break;
    }

    ParseResponseData( byResponse );

    byResponse.remove( 0, nTotal ); // Remove one Request

    bRet = ( 0 < byResponse.length( ) );
    return bRet;
}

void MainWindow::SendTcpStream( QByteArray &byData )
{
    QResponseEvent* pEvent = new QResponseEvent( QEvent::User );
    pEvent->SetReponseData( byData );

    QApplication::postEvent( pResposeThread, pEvent );
}

void MainWindow::IncomingData( )
{
    QByteArray byResponse = tcpSocket.readAll( );
    SendTcpStream( byResponse );
    return;

    bool bRet = false;
    byData.append( tcpSocket.readAll( ) );

    do {
        bRet = ParseMultipleResponseData( byData );
    } while ( bRet );

    return;

    /////////////////////////////
    qint64 nBytes = tcpSocket.bytesAvailable( );
    QByteArray byteData = tcpSocket.read( nBytes );

    if ( 0 == nBytesAvailable ) { // Start
        if ( nBytes < Protocol::nHeadLength ) {
            return;
        }

        nPakageSize = GetStreamLength( byteData );
    }


    byData.append( byteData );

    nBytesAvailable += nBytes;

    if ( nPakageSize == nBytesAvailable ) { // End
        ParseResponseData( byData );
    }

    if ( nPakageSize <= nBytesAvailable) {
        nBytesAvailable = 0;
        nPakageSize = 0;
        byData.clear( );
    }
}

void MainWindow::CreateBallotSenseRequest( QByteArray& byData )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 );
    nTcpStreamLength = htonl( nTcpStreamLength );
    byData.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    char nAddress = ( char ) ui->edtAddress->text( ).toShort( );
    byData.append( nAddress );
    SendData( byData );
}

void MainWindow::CreateActiveSendRequest( QByteArray& byData )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 );
    nTcpStreamLength = htonl( nTcpStreamLength );
    byData.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    char nAddress = ( char ) ui->edtAddress->text( ).toShort( );
    byData.append( nAddress );
    SendData( byData );
}

void MainWindow::CreateGateSenseRequest( QByteArray& byData )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 );
    nTcpStreamLength = htonl( nTcpStreamLength );
    byData.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    char nAddress = ( char ) ui->edtAddress->text( ).toShort( );
    byData.append( nAddress );
    SendData( byData );
}

void MainWindow::CreateInfraredRequest( QByteArray& byData )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 );
    nTcpStreamLength = htonl( nTcpStreamLength );
    byData.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    char nAddress = ( char ) ui->edtAddress->text( ).toShort( );
    byData.append( nAddress );
    SendData( byData );
}

void MainWindow::CreateLedRequest( QByteArray& byData )
{
    QString strContent = ui->edtLed->text( );
    if ( strContent.isEmpty( ) ) {
        return;
    }

    QByteArray byContent = pCodec->fromUnicode( strContent );
    quint32 nTcpStreamLength = Protocol::nHeadLength +
            sizeof ( quint8 ) + byContent.length( );
    nTcpStreamLength = htonl( nTcpStreamLength );
    byData.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    char nAddress = ( char ) ui->edtAddress->text( ).toShort( );
    byData.append( nAddress );
    byData.append( byContent );

    SendData( byData );
}

void MainWindow::CreateTrafficLightsRequest( QByteArray& byData )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 ) * 2;
    nTcpStreamLength = htonl( nTcpStreamLength );
    byData.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    char nAddress = ( char ) ui->edtAddress->text( ).toShort( );
    byData.append( nAddress );

    char nOperation = ( char ) ui->cbxTraffic->currentIndex( );
    byData.append( nOperation );

    SendData( byData );
}

void MainWindow::CreateGateRequest( QByteArray& byData )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 ) * 2;
    nTcpStreamLength = htonl( nTcpStreamLength );
    byData.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    char nAddress = ( char ) ui->edtAddress->text( ).toShort( );
    byData.append( nAddress );

    char nOperation = ( char ) ui->cbxGate->currentIndex( );
    byData.append( nOperation );

    SendData( byData );
}

void MainWindow::CreatePlateRequest( QByteArray& byData )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 );
    nTcpStreamLength = htonl( nTcpStreamLength );
    byData.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    char nAddress = ( char ) ui->edtAddress->text( ).toShort( );
    byData.append( nAddress );
    SendData( byData );
}

void MainWindow::on_btnRequest_clicked()
{
    if ( ui->edtAddress->text( ).isEmpty( ) ) {
        return;
    }

    QByteArray byData;
    byData.append( Protocol::byToken );

    char nMessageType = ui->cbxOp->currentIndex( ) + 1;
    byData.append( nMessageType );

    switch ( nMessageType ) {
    case Protocol::RequestQueryBallotSenseState :
        CreateBallotSenseRequest( byData );
        break;

    case Protocol::RequestQueryGateSenseState :
        CreateGateSenseRequest( byData );
        break;

    case Protocol::RequestQueryInfraredState :
        CreateInfraredRequest( byData );
        break;

    case Protocol::RequestControlLED :
        CreateLedRequest( byData );
        break;

    case Protocol::RequestControlTrafficLights :
        CreateTrafficLightsRequest( byData );
        break;

    case Protocol::RequestControlGate :
        CreateGateRequest( byData );
        break;

    case Protocol::RequestQueryPlateData :
        CreatePlateRequest( byData );
        break;

    case Protocol::RequestActiveSend :
        CreateActiveSendRequest( byData );
        break;
    }
}

void MainWindow::on_btnConnect_clicked()
{
    Connect2Host( );
}

void MainWindow::on_btnContinue_clicked()
{
    for ( char c = 0; c < 2; c++ ) {
        QByteArray byData;
        byData.append( Protocol::byToken );

        char nMessageType = 6;
        byData.append( nMessageType );

        quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 ) * 2;
        nTcpStreamLength = htonl( nTcpStreamLength );
        byData.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
        char nAddress = ( char ) c;
        byData.append( nAddress );

        char nOperation = ( char ) c;
        byData.append( nOperation );

        SendData( byData );
    }
}

void MainWindow::SendData( QByteArray &byData )
{
    tcpSocket.write( byData );
    tcpSocket.flush( );
    tcpSocket.waitForBytesWritten( );
}
