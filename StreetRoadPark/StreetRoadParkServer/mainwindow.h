#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cmainconfigurator.h"
#include "serialportcontroller.h"
#include "databasecontroller.h"
#include "networkcontroller.h"


#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QCloseEvent>

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
    void closeEvent( QCloseEvent * e );

private:
    void Initialize( );
    void InitializeCmd( QComboBox* pCB );
    void InitializeHash( );
    void InitializeSignalSlot( );

    inline qint32 GetItemData( QComboBox* pCB, qint32 nIndex );
    void HideCtrl( );
    void ShowCtrl( QComboBox* pCB, qint32 nIndex );

    void OpenPort( QStringList& lstCom );
    void ClosePort( QStringList& lstCom );

private slots:
    void DisplayPortLog( QString strLog, bool bStatic );
    void DisplayNetworkLog( QString strLog, bool bStatic );
    void DisplayDatabaseLog( QString strLog, bool bStatic );

    void on_btnPortCmd_clicked();

    void M77CmdIndexChanged(int index);

    void ComM77RIndexChanged(int index);

    void on_btnStartListen_clicked();

    void on_btnStopListen_clicked();

    void on_btnConnectDb_clicked();

private:
    typedef QHash< qint32, QString > QIntStringHash;
    typedef QHash< qint32, QLabel* > QIntLabelHash;
    typedef QHash< qint32, QSpinBox* > QIntSpinBoxHash;


    Ui::MainWindow *ui;

    CMainConfigurator* pConfig;
    QStringList lstCOMName;
    QIntStringHash hashLabelText;
    QIntLabelHash hashLabel;
    QIntSpinBoxHash hashSpinBox;

    SerialPortController* pPortController;
    NetworkController* pNetController;
    DatabaseController* pDbController;
};

#endif // MAINWINDOW_H
