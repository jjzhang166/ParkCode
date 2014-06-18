#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTextCodec>
#include <QUdpSocket>

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
    QTextCodec* GetTextCodec( );
    void ReadFile( QString& strBase64 );
    bool ParseData( QByteArray& data );
    quint32 GetUInt32Value( const char *pData );

private:
    typedef QHash< qint32, QTcpSocket* > QIntSocketHash;

    QIntSocketHash hashSocket;
    QUdpSocket udpSocket;
    QTcpSocket tcpSocket;
    
private slots:
    void HandleConnected( );
    void HandleDisconnected( );
    void IncomingData( );
    void IncomingUdpData( );

    void on_btnConnect_clicked();

    void on_btnDisconnect_clicked();

    void on_btnSendData_clicked();

    void on_btnEnter_clicked();

    void on_btnLeave_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QByteArray byDatagram;
    QByteArray byTcpStream;
};

#endif // MAINWINDOW_H
