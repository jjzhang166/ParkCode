#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include "qhkipcthread.h"

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
    void closeEvent(QCloseEvent *event);

private slots:
    void HandleNotifyMessage( QString strMsg );
    void HandleCapturedJPGImage( quint32 nChannel, QString strFileName );
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QIPCThread* pVideoThread;
    QFrame* pFrame[ 4 ];
    LONG lUserID;
    LONG lRealPlayHandle;
};

#endif // MAINWINDOW_H
