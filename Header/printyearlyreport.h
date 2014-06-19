#ifndef PRINTYEARLYREPORT_H
#define PRINTYEARLYREPORT_H

#include <QFrame>
#include <QCloseEvent>
#include "mainwindow.h"

namespace Ui {
    class CPrintYearlyReport;
}

class CPrintYearlyReport : public QFrame
{
    Q_OBJECT

public:
    explicit CPrintYearlyReport( QWidget* mainWnd, QWidget *parent = 0);
    ~CPrintYearlyReport();
    void DisplayPicture( QString& strFile );

protected:
    void  closeEvent ( QCloseEvent * event );

private:
    Ui::CPrintYearlyReport *ui;
    MainWindow* pParent;
};

#endif // PRINTYEARLYREPORT_H
