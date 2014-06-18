#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtEndian>
#include <QHostAddress>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 224.0.1.255
    //QHostAddress addr( "224.0.1.10" );
    //QHostAddress addr( "224.0.1.255" );
    udpSocket.bind(QHostAddress::AnyIPv4, 60000, QUdpSocket::ShareAddress);
    bool bRet = connect( &udpSocket, SIGNAL( readyRead( ) ),
                         this, SLOT( IncomingUdpData( ) ) );
    //bRet = udpSocket.joinMulticastGroup( addr );
    bRet = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandleConnected( )
{
    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );
    qDebug( ) << pSocket->objectName( ) << " connected." << endl;
}

void MainWindow::IncomingUdpData( )
{
    qDebug( ) << Q_FUNC_INFO <<endl;
    QByteArray byData;
    bool bRet = false;

    while ( udpSocket.hasPendingDatagrams( ) ) {
        byData.resize( udpSocket.pendingDatagramSize( ) );
        udpSocket.readDatagram( byData.data( ), byData.size( ) );
        byDatagram.append( byData );
        do {
            bRet = ParseData( byDatagram );
        } while ( bRet );
    }
}

quint32 MainWindow::GetUInt32Value( const char *pData )
{
    return qFromBigEndian< quint32 >( *( ( quint32* ) pData ) );
}

bool MainWindow::ParseData(QByteArray &data)
{
    bool bRet = false;
    QByteArray byToken = "StreetRoadPark";

    qint32 nIndex = data.indexOf( byToken );
    quint32 nTokenSize = byToken.length( );
    quint32 nCuurentStreamSize = data.length( ); // Current Stream Length

    if ( -1 == nIndex ) { // No Token
        qDebug( ) << "No Token" << endl;
        data.clear( );
        return bRet;
    } else if ( 0 < nIndex ) {
        ;//data.remove( 0, nIndex ); // Remove Token
    }

    quint32 nDataSize = sizeof ( qint32 );
    if ( nCuurentStreamSize <= ( nTokenSize + nDataSize * 3 ) ) {
        return bRet;
    }

    const char* pData = data.data( ) + nTokenSize;
    quint32 nPackageTotalSize = GetUInt32Value( pData ); // MessageSize = ProtocolHeadSize + BodySize
    quint32 nReserved = GetUInt32Value( pData + nDataSize );
    qint32 nPackageType = GetUInt32Value( pData + 2 * nDataSize );

    if ( nCuurentStreamSize < nPackageTotalSize ) { // Whole Package
        return bRet;
    }

    qint32 nExtraSize = nTokenSize + nDataSize * 3;
    qint32 nDataLen = nPackageTotalSize - nExtraSize;

    data.remove( 0, nExtraSize );
    QByteArray byBody = data.left( nDataLen );
    QString strBody = QString( byBody );
    ui->txtMulticast->appendPlainText( strBody );
    ui->txtMulticast->appendPlainText( "\n" );
    //qDebug( ) << "Received : " << strBody << endl;

    //DispatchData( pSocket, nPackageType, byBody );

    data.remove( 0, nDataLen );
    bRet = ( data.length( ) > nExtraSize );
}

void MainWindow::HandleDisconnected( )
{
    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );
    qDebug( ) << pSocket->objectName( ) << " disconnected." << endl;
}

void MainWindow::IncomingData( )
{
    if ( !ui->checkBox->isChecked( ) ) {
        return;
    }

    QTcpSocket* pSocket = ( QTcpSocket* ) sender( );

    QByteArray byData = pSocket->readAll( );
    byTcpStream.append( byData );
    bool bRet = false;

    do {
        bRet = ParseData( byTcpStream );
    } while ( bRet );

}

void MainWindow::on_btnConnect_clicked()
{
    QTcpSocket* pSocket = NULL;

    for ( qint32 nIndex = 0; nIndex < ui->sbConnCount->value( ); nIndex++ ) {
        pSocket = hashSocket.value( nIndex, NULL );

        if ( NULL == pSocket ) {
            pSocket = new QTcpSocket( );
            pSocket->setObjectName( QString( "Client【%1】" ).arg( nIndex ) );

            connect( pSocket, SIGNAL( readyRead( ) ),
                     this, SLOT( IncomingData( ) ) );

            connect( pSocket, SIGNAL( connected( ) ),
                     this, SLOT( HandleConnected( ) ) );

            connect( pSocket, SIGNAL( disconnected( ) ),
                     this, SLOT( HandleDisconnected( ) ) );
        }

        hashSocket.insert( nIndex, pSocket );

        if ( QTcpSocket::UnconnectedState == pSocket->state( ) ) {
            pSocket->connectToHost( ui->edtServerIP->text( ), ui->sbPort->value( ) );
        }
    }
}

void MainWindow::on_btnDisconnect_clicked()
{
    QTcpSocket* pSocket = NULL;

    for ( qint32 nIndex = 0; nIndex < hashSocket.count( ); nIndex++ ) {
        pSocket = hashSocket.value( nIndex, NULL );

        if ( NULL == pSocket ) {
            continue;
        }

        if ( QTcpSocket::ConnectedState == pSocket->state( ) ) {
            pSocket->disconnectFromHost( );
        }
    }
}

void MainWindow::on_btnSendData_clicked()
{
    QString strData = ui->txtData->toPlainText( );
    QByteArray byData = strData.toUtf8( );//GetTextCodec( )->fromUnicode( pConfig );
    quint32 nBodyDataLen = byData.length( );

    QTcpSocket* pSocket = NULL;
    QByteArray byTokenData = "StreetRoadPark";
    quint32 nDataSize = sizeof ( quint32 );
    quint32 nDataLen = 0;



    nDataLen = qToBigEndian< quint32 >( ui->edtPkType->text( ).toInt( ) );
    byData.insert( 0, ( const char* ) &nDataLen, nDataSize );


    nDataLen = qToBigEndian< quint32 >( 0 );
    byData.insert( 0, ( const char* ) &nDataLen, nDataSize );

    nDataLen = byTokenData.length( ) +
                nDataSize * 3 +
                nBodyDataLen;
    nDataLen = qToBigEndian< quint32 >( nDataLen );
    byData.insert( 0, ( const char* ) &nDataLen, nDataSize );

    byData.insert( 0, byTokenData );

    for ( qint32 nIndex = 0; nIndex < hashSocket.count( ); nIndex++ ) {
        pSocket = hashSocket.value( nIndex, NULL );

        if ( NULL == pSocket ) {
            continue;
        }

        if ( QTcpSocket::ConnectedState == pSocket->state( ) ) {
            nDataLen = pSocket->write( byData );
            pSocket->flush( );
            pSocket->waitForBytesWritten( 300000 );
            qDebug( ) << QString::number( nDataLen ) <<
                         " : " << pSocket->errorString( ) << endl;
        }
    }
}

QTextCodec* MainWindow::GetTextCodec( )
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

    pCodec = QTextCodec::codecForName( strText.toLatin1( ) );
    return pCodec;
}

void MainWindow::ReadFile( QString &strBase64 )
{
    QFile file( "MainBG.jpg" );
    file.open( QIODevice::ReadOnly );
    strBase64 = file.readAll( ).toBase64( );
}

void MainWindow::on_btnEnter_clicked()
{
    QString strJson = "{\"ClientID\":\"1234567890\",";
    strJson += "\"TypeCode\":\"TabletNormalData\",";
    strJson += "\"UserID\":\"002\",";
    strJson += "\"Data\":{";
    strJson += "\"LocationID\":\"5107010001001012\",";
    strJson += "\"Plate\":\"川A12345\",";
    strJson += "\"Payment\":\"35\",";
    strJson += "\"Operator\":\"张三\",";
    strJson += "\"PaymentTime\":\"2013-03-18 12:23:45\",";
    strJson += "\"State\":\"1\",";
    strJson += "\"FeeReceivable\":\"11\",";
    strJson += "\"RecordType\":\"2\",";
    strJson += "\"FreeType\":\"3\",";
    strJson += "\"Image\":\"%1\"}}";

    QString strBase64;
    ReadFile( strBase64 );
    strJson = strJson.arg( strBase64 );

    int nLen = GetTextCodec( )->fromUnicode( strJson ).count( );
    ui->edtLength->setText( QString::number( nLen ) );
    ui->txtData->appendPlainText( strJson );
}

void MainWindow::on_btnLeave_clicked()
{
    QString strJson = "{\"ClientID\":\"1234567890\",";
    strJson += "\"TypeCode\":\"TabletNormalData\",";
    strJson += "\"UserID\":\"002\",";
    strJson += "\"Data\":{";
    strJson += "\"LocationID\":\"5107010001001012\",";
    strJson += "\"Plate\":\"川A12345\",";
    strJson += "\"Payment\":\"30\",";
    strJson += "\"Operator\":\"张三\",";
    strJson += "\"PaymentTime\":\"2013-03-19 12:23:45\",";
    strJson += "\"State\":\"0\",";
    strJson += "\"FeeReceivable\":\"11\",";
    strJson += "\"RecordType\":\"2\",";
    strJson += "\"FreeType\":\"3\",";
    strJson += "\"Image\":\"%1\"}}";

    QString strBase64;
    ReadFile( strBase64 );
    strJson = strJson.arg( strBase64 );

    int nLen = GetTextCodec( )->fromUnicode( strJson ).count( );
    ui->edtLength->setText( QString::number( nLen ) );
    ui->txtData->appendPlainText( strJson );
}

void MainWindow::on_pushButton_clicked()
{
    QString strJson = "{\"ClientID\":\"1234567890\",";
    strJson += "\"TypeCode\":\"TabletManualData\",";
    strJson += "\"UserID\":\"002\",";
    strJson += "\"Data\":{";
    strJson += "\"LocationID\":\"5107010001001006\",";
    strJson += "\"Plate\":\"川A88888\",";
    strJson += "\"Payment\":\"30\",";
    strJson += "\"Operator\":\"张三\",";
    strJson += "\"PaymentTime\":\"2013-03-19 12:23:45\",";
    strJson += "\"State\":\"1\",";
    strJson += "\"FeeReceivable\":\"11\",";
    strJson += "\"RecordType\":\"2\",";
    strJson += "\"FreeType\":\"3\",";
    strJson += "\"Image\":\"%1\"}}";

    QString strBase64;
    ReadFile( strBase64 );
    strJson = strJson.arg( strBase64 );

    int nLen = GetTextCodec( )->fromUnicode( strJson ).count( );
    ui->edtLength->setText( QString::number( nLen ) );
    ui->txtData->appendPlainText( strJson );
}

void MainWindow::on_pushButton_2_clicked()
{
    QString strJson = "{\"ClientID\":\"1234567890\",";
    strJson += "\"TypeCode\":\"TabletManualData\",";
    strJson += "\"UserID\":\"002\",";
    strJson += "\"Data\":{";
    strJson += "\"LocationID\":\"5107010001001006\",";
    strJson += "\"Plate\":\"川A88888\",";
    strJson += "\"Payment\":\"30\",";
    strJson += "\"Operator\":\"张三\",";
    strJson += "\"PaymentTime\":\"2013-03-19 12:23:45\",";
    strJson += "\"State\":\"0\",";
    strJson += "\"FeeReceivable\":\"11\",";
    strJson += "\"RecordType\":\"2\",";
    strJson += "\"FreeType\":\"3\",";
    strJson += "\"Image\":\"%1\"}}";

    QString strBase64;
    ReadFile( strBase64 );
    strJson = strJson.arg( strBase64 );

    int nLen = GetTextCodec( )->fromUnicode( strJson ).count( );
    ui->edtLength->setText( QString::number( nLen ) );
    ui->txtData->appendPlainText( strJson );
}

void MainWindow::on_pushButton_3_clicked()
{
    QString strJson = "{\"ClientID\":\"1234567890\",";
    strJson += "\"TypeCode\":\"UnhandledSensorData\",";
    strJson += "\"UserID\":\"1\",";
    strJson += "\"Data\":{";
    strJson += "\"LocationID\":\"5101070001001006\"}}";

    QString strBase64;
    ReadFile( strBase64 );
    strJson = strJson.arg( strBase64 );

    int nLen = GetTextCodec( )->fromUnicode( strJson ).count( );
    ui->edtLength->setText( QString::number( nLen ) );
    ui->txtData->appendPlainText( strJson );
}

void MainWindow::on_pushButton_4_clicked()
{
    tcpSocket.connectToHost( ui->edtServerIP->text( ), 60000 );

    connect( &tcpSocket, SIGNAL( readyRead( ) ),
             this, SLOT( IncomingData( ) ) );
}
