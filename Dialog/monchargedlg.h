#ifndef MONCHARGEDLG_H
#define MONCHARGEDLG_H

#include <QDialog>

namespace Ui {
    class CMonChargeDlg;
}

class CMonChargeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CMonChargeDlg(QWidget *parent = 0);
    ~CMonChargeDlg();

private:
    Ui::CMonChargeDlg *ui;

private slots:
    void on_btnCancel_clicked();
    void on_btnSave_clicked();
};

#endif // MONCHARGEDLG_H
