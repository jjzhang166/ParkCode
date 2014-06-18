#ifndef MODUNITDIALOG_H
#define MODUNITDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "ItemInfos/iteminfounit.h"

namespace Ui {
class ModUnitDialog;
}

class ModUnitDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModUnitDialog(QTreeWidgetItem *pItem, QWidget *parent = 0);
    ~ModUnitDialog();
    
private slots:
    void on_ptnMod_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::ModUnitDialog *ui;
    QTreeWidgetItem * currentItem;
    ItemInfoUnit newUnitInfo;
    QString oldUnitID;
};

#endif // MODUNITDIALOG_H
