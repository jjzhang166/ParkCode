#ifndef HANDHELDICPROCESS_H
#define HANDHELDICPROCESS_H

#include <QFrame>
#include <QCloseEvent>
#include "mainwindow.h"

namespace Ui {
    class CHandheldICProcess;
}

class CHandheldICProcess : public QFrame
{
    Q_OBJECT

public:
    explicit CHandheldICProcess( QWidget* mainWnd, QWidget *parent = 0);
    ~CHandheldICProcess();

protected:
    void  closeEvent ( QCloseEvent * event );

private:
    Ui::CHandheldICProcess *ui;
    MainWindow* pParent;
};

#endif // HANDHELDICPROCESS_H
