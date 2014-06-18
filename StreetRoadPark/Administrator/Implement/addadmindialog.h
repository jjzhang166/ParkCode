#ifndef ADDADMINDIALOG_H
#define ADDADMINDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "Implement/iterfacetomysql.h"
#include "ItemInfos/iteminfoadmin.h"
#include "ItemInfos/ItemType.h"

namespace Ui {
class AddAdminDialog;
}

class AddAdminDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddAdminDialog( QTreeWidgetItem *pItem, QWidget *parent = 0 );
    ~AddAdminDialog();

    void GetCmbItem(QString &strSql);

    QStringList & GetAdminItemInfo();// not use
private:
    bool Verify();// not use
    
private slots:
    void on_ptnAdd_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::AddAdminDialog *ui;
    QStringList lstInfos;
    QList< ItemInfoAdmin > AdminList;
    QTreeWidgetItem *currentItem;
};

#endif // ADDADMINDIALOG_H
