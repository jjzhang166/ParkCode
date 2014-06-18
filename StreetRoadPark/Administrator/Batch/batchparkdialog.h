#ifndef BATCHPARKDIALOG_H
#define BATCHPARKDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class BatchParkDialog;
}

class BatchParkDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BatchParkDialog(QString strAdminId, QString strParkParentId, QString strPid, QTreeWidgetItem *pItem, QWidget *parent = 0);
    ~BatchParkDialog();
    
private slots:
    void on_parkTableWidget_cellClicked(int row, int column);
    void on_ptnAdd_clicked();
    void on_ptnModify_clicked();
    void on_ptnDelete_clicked();
    void on_ptnSave_clicked();
    void on_ptnClose_clicked();

private:
    Ui::BatchParkDialog *ui;
    QTreeWidgetItem * currentItem;
    QString g_AdminID;
    QString parkId;
    QString g_ParkParentId;
    QString g_Pid; // unitId
};

#endif // BATCHPARKDIALOG_H
