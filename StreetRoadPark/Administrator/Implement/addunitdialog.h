#ifndef ADDUNITDIALOG_H
#define ADDUNITDIALOG_H

#include <QDialog>

#include "Implement/iterfacetomysql.h"

namespace Ui {
class AddUnitDialog;
}

class AddUnitDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddUnitDialog(QWidget *parent = 0);
    ~AddUnitDialog();

    QStringList & GetUnitItemInfo();

private:
    bool Verify();
    
private slots:
    void on_ptnAdd_clicked();
    void on_ptnCancel_clicked();

private:
    Ui::AddUnitDialog *ui;
    QStringList lstInfos;
};

#endif // ADDUNITDIALOG_H
