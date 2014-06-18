#ifndef MODUSERDIALOG_H
#define MODUSERDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class ModUserDialog;
}

class ModUserDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModUserDialog(QTreeWidgetItem *pItem, QWidget *parent = 0);
    ~ModUserDialog();
    
private slots:
    void on_ptnMod_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::ModUserDialog *ui;
    QTreeWidgetItem *currentItem;
    quint64 g_pid; // groupid
    QString strOldName;
};

#endif // MODUSERDIALOG_H
