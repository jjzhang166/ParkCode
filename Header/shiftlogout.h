#ifndef SHIFTLOGOUT_H
#define SHIFTLOGOUT_H

#include <QFrame>
#include <QCloseEvent>
#include "mainwindow.h"

namespace Ui {
    class CShiftLogout;
}

class CShiftLogout : public QFrame
{
    Q_OBJECT

public:
    explicit CShiftLogout( QWidget* mainWnd, QWidget *parent = 0);
    ~CShiftLogout();

protected:
    void  closeEvent ( QCloseEvent * event );

private:
    Ui::CShiftLogout *ui;
    MainWindow* pParent;
};

#endif // SHIFTLOGOUT_H
