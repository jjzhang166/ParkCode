#ifndef DLGPASSDETAIL_H
#define DLGPASSDETAIL_H

#include <QDialog>
#include <QResizeEvent>

namespace Ui {
    class CDlgPassDetail;
}

class CDlgPassDetail : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgPassDetail(QWidget *parent = 0);
    ~CDlgPassDetail();

protected:
    void resizeEvent ( QResizeEvent * event );

private:
    Ui::CDlgPassDetail *ui;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnQuery_clicked();
};

#endif // DLGPASSDETAIL_H
