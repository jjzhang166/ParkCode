#ifndef MODADMINDIALOG_H
#define MODADMINDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "ItemInfos/iteminfoadmin.h"

namespace Ui {
class ModAdminDialog;
}

class ModAdminDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModAdminDialog( QTreeWidgetItem *pItem, QWidget *parent = 0 );
    ~ModAdminDialog();

    
private slots:
    void on_ptnMod_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::ModAdminDialog *ui;
    QTreeWidgetItem * currentItem;
    ItemInfoAdmin newAdminInfo;
    QString oldAdminId;
};

#endif // MODADMINDIALOG_H
