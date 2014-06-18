#ifndef MODDETECTORDIALOG_H
#define MODDETECTORDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "ItemInfos/iteminfodetector.h"

namespace Ui {
class ModDetectorDialog;
}

class ModDetectorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModDetectorDialog( QTreeWidgetItem * pItem, QWidget *parent = 0 );
    ~ModDetectorDialog();
    
private slots:
    void on_ptnMod_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::ModDetectorDialog *ui;
    QTreeWidgetItem * currentItem;
    ItemInfoDetector newDetectorInfo;
    QString receiverDetectorID;
};

#endif // MODDETECTORDIALOG_H
