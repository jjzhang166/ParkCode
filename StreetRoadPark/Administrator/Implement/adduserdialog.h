#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "ItemInfos/iteminfouser.h"
#include "ItemInfos/ItemType.h"

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddUserDialog(QString pid, QTreeWidgetItem *pItem, QWidget *parent = 0);
    ~AddUserDialog();
    
private slots:
    void on_ptnAdd_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::AddUserDialog *ui;
    QString g_pid;
    QTreeWidgetItem *currentItem;
};

#endif // ADDUSERDIALOG_H
