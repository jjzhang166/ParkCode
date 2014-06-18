#ifndef MODGROUPDIALOG_H
#define MODGROUPDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class ModGroupDialog;
}

class ModGroupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModGroupDialog(QTreeWidgetItem *pItem, QWidget *parent = 0 );
    ~ModGroupDialog();
    
private slots:
    void on_ptnMod_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::ModGroupDialog *ui;
    QTreeWidgetItem *currentItem;
    quint64 g_groupParentId;
    QString g_pid;
    QString strOldGroupName;
};

#endif // MODGROUPDIALOG_H
