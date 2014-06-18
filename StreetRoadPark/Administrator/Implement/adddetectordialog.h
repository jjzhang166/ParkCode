#ifndef ADDDETECTORDIALOG_H
#define ADDDETECTORDIALOG_H

#include <QDialog>

#include "Implement/iterfacetomysql.h"

namespace Ui {
class AddDetectorDialog;
}

class AddDetectorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddDetectorDialog( QString parkReceiverId, QWidget *parent = 0);
    ~AddDetectorDialog();

    QStringList & GetDetectorItemInfo();
private:
    bool Verify();
    
private slots:
    void on_ptnAdd_clicked();
    void on_ptnCancel_clicked();

private:
    Ui::AddDetectorDialog *ui;
    QStringList lstInfos;
    QString g_parkReceiverId;
    QString g_ReceiverDetectorId;
};

#endif // ADDDETECTORDIALOG_H
