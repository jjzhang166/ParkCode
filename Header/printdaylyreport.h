#ifndef PRINTDAYLYREPORT_H
#define PRINTDAYLYREPORT_H

#include <QFrame>
#include <QCloseEvent>
#include "mainwindow.h"
#include "Report/reporter.h"

namespace Ui {
    class CPrintDaylyReport;
}

class CPrintDaylyReport : public QFrame
{
    Q_OBJECT

public:
    explicit CPrintDaylyReport( QWidget* mainWnd, QWidget *parent = 0);
    ~CPrintDaylyReport();

protected:
    void  closeEvent ( QCloseEvent * event );

private:
    inline void SetDateTimeFormat( QString& strFormat );
    inline void SetDateTime( QDateTime& dtStart, QDateTime& dtEnd );
    void GetParameter( );
    void SaveParameter( CommonDataType::ReportType nType );

private:
    Ui::CPrintDaylyReport *ui;
    MainWindow* pParent;
    CReporter reporter;
    int nReportType;
    bool bPersonTime;
    QTime tPersonStartTime;
    QTime tPersonEndTime;
    QTime tTimeCardStartTime;
    QTime tTimeCardEndTime;
    QStringList lstMonthQuery;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnClose_clicked();
    void on_btnPrint_clicked();
    void on_btnGenerate_clicked();
    void OnRdChkClicked( );
};

#endif // PRINTDAYLYREPORT_H
