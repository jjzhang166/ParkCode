#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Network/netclient.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QTextCodec* pCodec, QWidget *parent = 0);
    ~MainWindow();

private:
    void SendTableData( QString& strBody, int nRows, int nCols,  NetTransport::eTableType tabType );
    void SendImageData( const char* pImg, quint32 nImgLen, NetTransport::eImageType imgType,
                        quint32 nParkID, QString& strPlate, QDateTime& datetime );

    void PostCustomEvent( CHttpServer* pReceiver, CHttpEvent::UserEvent nEvent, CHttpEvent::HttpGetResponse* pResponse = NULL );
    void Init( QTextCodec* pCodec );

private:
    Ui::MainWindow *ui;
    CNetClient* netClient;

private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_SendData_clicked();
    void on_StartupClient_clicked();
    void NotifyMessage( QString strMsg );
    void FtpCmdFinished( int nId, bool bError );
};

#endif // MAINWINDOW_H
