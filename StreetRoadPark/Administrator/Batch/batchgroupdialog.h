#ifndef BATCHGROUPDIALOG_H
#define BATCHGROUPDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class BatchGroupDialog;
}

class BatchGroupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BatchGroupDialog( QString groupParentId, QString pid, QTreeWidgetItem *pItem, QWidget *parent = 0 );
    ~BatchGroupDialog();
    
private slots:
    void on_groupTableWidget_cellClicked(int row, int column);
    void on_ptnAdd_clicked();
    void on_ptnModify_clicked();
    void on_ptnDelete_clicked();
    void on_ptnSave_clicked();
    void on_ptnClose_clicked();

private:
    Ui::BatchGroupDialog *ui;
    QTreeWidgetItem * currentItem;
    QString g_groupParentId;
    QString g_pid;
};

#endif // BATCHGROUPDIALOG_H
