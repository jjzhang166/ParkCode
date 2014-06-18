#ifndef BATCHUNITDIALOG_H
#define BATCHUNITDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class BatchUnitDialog;
}

class BatchUnitDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BatchUnitDialog( QString strAdminId, QTreeWidgetItem *pItem, QWidget *parent = 0);
    ~BatchUnitDialog();
    
private slots:
    void on_unitTableWidget_cellClicked(int row, int column);
    void on_ptnAdd_clicked();
    void on_ptnModify_clicked();
    void on_ptnDelete_clicked();
    void on_ptnSave_clicked();
    void on_ptnClose_clicked();

private:
    Ui::BatchUnitDialog *ui;
    QTreeWidgetItem * currentItem;
    QString g_Pid; // AdminId
};

#endif // BATCHUNITDIALOG_H
