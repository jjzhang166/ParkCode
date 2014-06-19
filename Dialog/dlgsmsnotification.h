#ifndef DLGSMSNOTIFICATION_H
#define DLGSMSNOTIFICATION_H

#include <QDialog>
#include <QResizeEvent>
#include "Common/commonfunction.h"

namespace Ui {
    class CDlgSMSNotification;
}

class CDlgSMSNotification : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgSMSNotification(QWidget *parent = 0);
    ~CDlgSMSNotification();

protected:
    void resizeEvent ( QResizeEvent * event );

private:
    Ui::CDlgSMSNotification *ui;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnCancel_clicked();
    void on_btnSave_clicked();
};

#endif // DLGSMSNOTIFICATION_H
