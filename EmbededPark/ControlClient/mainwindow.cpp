#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( &libThread, SIGNAL( DisplayLog( QString ) ),
             this, SLOT( HandleDisplayLog( QString ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AppendMessage( QString &strText )
{
    ui->edtLog->appendPlainText( strText );
    ui->edtLog->appendPlainText( "\r\n" );
}

void MainWindow::HandleDisplayLog( QString strText )
{
    AppendMessage( strText );
}

void MainWindow::HandleDataIncoming( QTcpSocket* pSocket, QByteArray* pByteArray )
{
    QString strText( *pByteArray );
    AppendMessage( strText );
    delete pByteArray;
}

void MainWindow::on_pushButton_clicked()
{
    qint32 nConn = 10;
    uParam.ParamValue.ClientSocketThread.Host.nIP = QHostAddress( "127.0.0.1" ).toIPv4Address( );
    uParam.ParamValue.ClientSocketThread.Host.nPort = 6000;
    uParam.ParamValue.ClientSocketThread.Host.bAll = true;

    while ( nConn-- ) {
        uParam.ParamValue.ClientSocketThread.Host.nSequence = nConn;
        libThread.PostClientSocketThreadEvent( QCommonLibrary::EventClientConnection, uParam, false, this );
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    libThread.PostClientSocketThreadEvent( QCommonLibrary::EventClientDisconnection, uParam, false );
}

void MainWindow::on_pushButton_3_clicked()
{
    libThread.PostClientSocketThreadEvent( QCommonLibrary::EventExit, uParam, false );
}

void MainWindow::on_pushButton_4_clicked()
{
    qint32 nConn = 10;

    while ( nConn-- ) {
        QByteArray* pByteArray = new QByteArray( );
        QString& strToken = QCommonLibrary::GetDataToken( );
        QByteArray byToken = QCommonLibrary::GetTextCodec( )->fromUnicode( strToken );
        pByteArray->append( byToken );
        QByteArray byBody = QString( "Test success %1." ).arg( nConn ).toLatin1( );
        qint32 nPackageLen = byToken.length( ) + sizeof ( quint32 ) * 3 + byBody.length( );
        nPackageLen = qToBigEndian< qint32 >( nPackageLen );
        pByteArray->append( ( char* ) &nPackageLen, sizeof ( quint32 ) );
        pByteArray->append( byBody );
        pByteArray->append( *pByteArray );


        //uParam.ParamValue.ClientSocketThread.Data.Host.bAll = false;
        uParam.ParamValue.ClientSocketThread.Data.Host.nSequence = nConn;
        uParam.ParamValue.ClientSocketThread.Data.pByteArray = pByteArray;
        libThread.PostClientSocketThreadEvent( QCommonLibrary::EventClientSendData, uParam, false );
    }
}
