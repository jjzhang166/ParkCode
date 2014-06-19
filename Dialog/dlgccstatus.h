#ifndef DLGCCSTATUS_H
#define DLGCCSTATUS_H

#include <QDialog>
#include <QResizeEvent>
#include "Common/commonfunction.h"

namespace Ui {
    class CDlgCCStatus;
}

class CDlgCCStatus : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgCCStatus(QWidget *parent = 0);
    ~CDlgCCStatus();

protected:
    void resizeEvent ( QResizeEvent * event );

private:
    Ui::CDlgCCStatus *ui;
    QSettings* pSettings;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnCancel_clicked();
    void on_btnSave_clicked();
    void on_btnTest_clicked();
};

#endif // DLGCCSTATUS_H
