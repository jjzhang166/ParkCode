#ifndef MODRECEIVERDIALOG_H
#define MODRECEIVERDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "ItemInfos/iteminforeceiver.h"

namespace Ui {
class ModReceiverDialog;
}

class ModReceiverDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModReceiverDialog( QTreeWidgetItem * pItem, QWidget *parent = 0 );
    ~ModReceiverDialog();
    
private slots:
    void on_ptnMod_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::ModReceiverDialog *ui;
    QTreeWidgetItem * currentItem;
    ItemInfoReceiver newReceiverInfo;
    QString parkReceiverID;// PK
};

#endif // MODRECEIVERDIALOG_H
