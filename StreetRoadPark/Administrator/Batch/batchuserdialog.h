#ifndef BATCHUSERDIALOG_H
#define BATCHUSERDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class BatchUserDialog;
}

class BatchUserDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BatchUserDialog(QString pid, QTreeWidgetItem *pItem, QWidget *parent = 0);
    ~BatchUserDialog();
    
private slots:
    void on_userTableWidget_cellClicked(int row, int column);
    void on_ptnAdd_clicked();
    void on_ptnModify_clicked();
    void on_ptnDelete_clicked();
    void on_ptnSave_clicked();
    void on_ptnClose_clicked();

private:
    Ui::BatchUserDialog *ui;
    QTreeWidgetItem * currentItem;
    QString g_pid;
};

#endif // BATCHUSERDIALOG_H
