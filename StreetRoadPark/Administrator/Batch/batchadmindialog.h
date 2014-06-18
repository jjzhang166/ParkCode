#ifndef BATCHADMINDIALOG_H
#define BATCHADMINDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class BatchAdminDialog;
}

class BatchAdminDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BatchAdminDialog(QTreeWidgetItem *pItem, QWidget *parent = 0);
    ~BatchAdminDialog();

private:
    void InitAdminCmb();


private slots:
    void on_ptnAdd_clicked();
    void on_ptnModify_clicked();
    void on_ptnDelete_clicked();
    void on_ptnSave_clicked();
    void on_ptnClose_clicked();
    
    void on_adminTableWidget_cellClicked(int row, int column);

private:
    Ui::BatchAdminDialog *ui;
    QTreeWidgetItem * currentItem;
};

#endif // BATCHADMINDIALOG_H
