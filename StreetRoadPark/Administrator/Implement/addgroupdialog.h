#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "ItemInfos/iteminfogroup.h"
#include "ItemInfos/ItemType.h"

namespace Ui {
class AddGroupDialog;
}

class AddGroupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddGroupDialog( QString groupParentId, QString pid, QTreeWidgetItem *pItem, QWidget *parent = 0);
    ~AddGroupDialog();
    
private slots:
    void on_ptnAdd_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::AddGroupDialog *ui;
    QString g_groupParentId;
    QString g_pid;
    QTreeWidgetItem *currentItem;
};

#endif // ADDGROUPDIALOG_H
