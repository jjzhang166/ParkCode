#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "monitor.h"
#include "../Database/mysqldatabase.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //Q_PROPERTY(QCursor myCursor READ myCursor WRITE setMyCursor RESET unsetMyCursor)

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMdiArea* pMdiArea;
    CMonitor* pMonitor;
    CMySqlDatabase mysql;

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
