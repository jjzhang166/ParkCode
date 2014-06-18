#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Network/svrthread.h"
#include "../Network/localsvrcommunication.h"
#include "../Network/localcltcommunication.h"
#include <QCloseEvent>
#include <QSystemTrayIcon>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent( QCloseEvent *  e );

private:
    void Singleton( );
    void NotifyIcon( );
    inline void AddMenuItem( QMenu* pMenu, QVariant& varData, QString& strText );

private:
    Ui::MainWindow *ui;
    QSettings* pSettings;
    QTextCodec* pTextCodec;
    CSvrThread* netServer;
    CLocalSvrCommunication* pLocalComm;
    QSystemTrayIcon* sysTrayIcon;

private slots:
    void on_btnSave_clicked();
    void on_btnClear_clicked();
    void DisplayMessage( QString strMsg );
    void SysTray( );
    void SysTrayActivate( QSystemTrayIcon::ActivationReason reason );
};

#endif // MAINWINDOW_H
