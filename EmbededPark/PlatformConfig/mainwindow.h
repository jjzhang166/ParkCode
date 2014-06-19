#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include "../CommonLibrary/qcommonlibrary.h"

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
    void InitList( );
    void InitSettings( );
    void ReadConfig( );
    void WriteConfig( );
    
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::MainWindow *ui;
    QSettings* pSettings;
    QTextCodec* pCodec;

    QList< QSpinBox* > lstSpinBox;
    QList< QLineEdit* > lstLineEdit;
};

#endif // MAINWINDOW_H
