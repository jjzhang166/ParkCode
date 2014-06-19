#ifndef SYSSETTING_H
#define SYSSETTING_H

#include <QTabWidget>
#include <QCloseEvent>
#include <QResizeEvent>
#include "mainwindow.h"
#include <QSettings>

namespace Ui {
    class CSysSetting;
}

class CSysSetting : public QTabWidget
{
    Q_OBJECT

public:
    explicit CSysSetting( QWidget* mainWnd, QWidget *parent = 0);
    ~CSysSetting();

protected:
    void  closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void CalculatePos( );

private:
    void ReadFile( );
    void WriteFile( );

private:
    Ui::CSysSetting *ui;
    MainWindow* pParent;
    QSettings* pSettings;
};

#endif // SYSSETTING_H
