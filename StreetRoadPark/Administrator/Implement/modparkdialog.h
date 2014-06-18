#ifndef MODPARKDIALOG_H
#define MODPARKDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "ItemInfos/iteminfopark.h"

namespace Ui {
class ModParkDialog;
}

class ModParkDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModParkDialog( QTreeWidgetItem * pItem, QWidget *parent = 0 );
    ~ModParkDialog();
    
private slots:
    void on_ptnMod_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::ModParkDialog *ui;
    QTreeWidgetItem * currentItem;
    ItemInfoPark newParkInfo;
};

#endif // MODPARKDIALOG_H
