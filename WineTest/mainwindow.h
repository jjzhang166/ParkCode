#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qlistener.h"
#include <QTcpSocket>
#include "../PlateDilivery/ProtocolStructure.h"
#include <QTextCodec>
#include "qprocessresponsethread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QByteArray GetToken( QByteArray& byStream );
    quint8 GetMessageType( QByteArray& byStream );
    quint32 GetStreamLength( QByteArray& byStream );
    QByteArray GetBody( QByteArray& byStream );

    void ParseResponseData( QByteArray& byData );
    bool ParseMultipleResponseData( QByteArray &byResponse );
    QString GetByteDataString( void* pData, quint8 nLength );
    void DisplayPic( quint8* pData, quint32 nLength );

    void CreateBallotSenseRequest( QByteArray& byData );
    void CreateGateSenseRequest( QByteArray& byData );
    void CreateInfraredRequest( QByteArray& byData );
    void CreateLedRequest( QByteArray& byData );
    void CreateTrafficLightsRequest( QByteArray& byData );
    void CreateGateRequest( QByteArray& byData );
    void CreatePlateRequest( QByteArray& byData );
    void CreateActiveSendRequest( QByteArray& byData );

    void ProcessResponse( QByteArray& byStream );
    void ProcessBallotSenseResponse( QByteArray& byStream );
    void ProcessGateSenseResponse( QByteArray& byStream );
    void ProcessInfraredResponse( QByteArray& byStream );
    void ProcessPlateResponse( QByteArray& byStream );
    void ProcessActiveSendResponse( QByteArray& byStream );

    bool Connect2Host( );
    void AppendResponse( QString& strMsg );

    void SendData( QByteArray& byData );

    void SendTcpStream( QByteArray& byData );

private slots:
    void HandleAccept( int socketDescriptor );
    void IncomingData( );
    
    void on_btnRequest_clicked();

    void on_btnConnect_clicked();

    void on_btnContinue_clicked();

    void HandleResponse( QString strMsg );
    void HandlePlateImg( QString strFile );

private:
    Ui::MainWindow *ui;

    QListener listener;
    QTcpSocket tcpSocket;
    quint64 nBytesAvailable;
    QByteArray byData;
    quint32 nPakageSize;
    QTextCodec* pCodec;
    QProcessResponseThread* pResposeThread;
};

#endif // MAINWINDOW_H
