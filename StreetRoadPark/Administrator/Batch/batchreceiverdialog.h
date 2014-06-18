#ifndef BATCHRECEIVERDIALOG_H
#define BATCHRECEIVERDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class BatchReceiverDialog;
}

class BatchReceiverDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BatchReceiverDialog(QString parkId, QTreeWidgetItem *pItem, QWidget *parent = 0);
    ~BatchReceiverDialog();
    
private slots:
    void on_receiverTableWidget_cellClicked(int row, int column);
    void on_ptnAdd_clicked();
    void on_ptnModify_clicked();
    void on_ptnDelete_clicked();
    void on_ptnSave_clicked();
    void on_ptnClose_clicked();

private:
    Ui::BatchReceiverDialog *ui;
    QTreeWidgetItem * currentItem;
    QString g_parkID;
    QString parkReceiverId;
};

#endif // BATCHRECEIVERDIALOG_H
