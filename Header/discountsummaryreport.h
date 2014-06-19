#ifndef DISCOUNTSUMMARYREPORT_H
#define DISCOUNTSUMMARYREPORT_H

#include <QFrame>
#include <QCloseEvent>
#include "mainwindow.h"

namespace Ui {
    class CDiscountSummaryReport;
}

class CDiscountSummaryReport : public QFrame
{
    Q_OBJECT

public:
    explicit CDiscountSummaryReport( QWidget* mainWnd, QWidget *parent = 0);
    ~CDiscountSummaryReport();

protected:
    void  closeEvent ( QCloseEvent * event );

private:
    Ui::CDiscountSummaryReport *ui;
    MainWindow* pParent;
};

#endif // DISCOUNTSUMMARYREPORT_H
