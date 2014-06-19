#ifndef HANDICDIALOG_H
#define HANDICDIALOG_H

#include <QDialog>

namespace Ui {
    class CHandICDialog;
}

class CHandICDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CHandICDialog(QWidget *parent = 0);
    ~CHandICDialog();

private:
    Ui::CHandICDialog *ui;

private slots:
    void on_btnDiscount_clicked();
    void on_btnConnect_clicked();
};

#endif // HANDICDIALOG_H
