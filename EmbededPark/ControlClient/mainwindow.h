#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../ThreadLibrary/qthreadlibrary.h"

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
    inline void AppendMessage( QString& strText );

private slots:
    void HandleDataIncoming( QTcpSocket* pSocket, QByteArray* pByteArray );
    void HandleDisplayLog( QString strText );
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QThreadLibrary libThread;
    QCommonLibrary::EventParam uParam;
};

#endif // MAINWINDOW_H
