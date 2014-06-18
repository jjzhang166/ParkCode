#ifndef BATCHDETECTORDIALOG_H
#define BATCHDETECTORDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class BatchDetectorDialog;
}

class BatchDetectorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BatchDetectorDialog(QTreeWidgetItem *pItem, QString parkReceiverId, QWidget *parent = 0);
    ~BatchDetectorDialog();
    
private slots:
    void on_detectorTableWidget_cellClicked(int row, int column);

    void on_ptnAdd_clicked();

    void on_ptnModify_clicked();

    void on_ptnDelete_clicked();

    void on_ptnSave_clicked();

    void on_ptnClose_clicked();

private:
    Ui::BatchDetectorDialog *ui;
    QTreeWidgetItem * currentItem;
    QString g_parkReceiverId;
    QString g_ReceiverDetectorId;
};

#endif // BATCHDETECTORDIALOG_H
