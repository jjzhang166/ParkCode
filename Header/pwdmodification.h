#ifndef PWDMODIFICATION_H
#define PWDMODIFICATION_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include "mainwindow.h"

namespace Ui {
    class CPwdModification;
}

class CPwdModification : public QFrame
{
    Q_OBJECT

public:
    explicit CPwdModification( QWidget* mainWnd, QWidget *parent = 0);
    ~CPwdModification();

protected:
    void  closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void CalculatePos( );

private:
    Ui::CPwdModification *ui;
    MainWindow* pParent;
};

#endif // PWDMODIFICATION_H
