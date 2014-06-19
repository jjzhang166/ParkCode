#ifndef DBMAINTENANCE_H
#define DBMAINTENANCE_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QFileDialog>
#include "mainwindow.h"
#include <QSettings>
#include <QShowEvent>

namespace Ui {
    class CDBMaintenance;
}

class CDBMaintenance : public QFrame
{
    Q_OBJECT

public:
    explicit CDBMaintenance( QWidget* mainWnd, QWidget *parent = 0);
    ~CDBMaintenance();

protected:
    void closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void CalculatePos( );
    void showEvent( QShowEvent * );

private:
    void OpenDialog( bool bBackup );

    void GetValue( bool bReadFile );
    void ReadIniFile( );
    void WriteIniFile( );
    void StartThread( bool bAutoBackup, bool bRestore );

private:
    Ui::CDBMaintenance *ui;
    MainWindow* pParent;
    QFileDialog fileDlg;
    QSettings* pSettings;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnClose_clicked();
    void on_btnBackup_clicked( );
    void on_btnRecovery_clicked( );
    void on_btnSave_clicked( );
    void on_btnBackupPath_clicked( );
    void on_btnRecoveyPath_clicked( );
    void ClearData( );
};

#endif // DBMAINTENANCE_H
