#ifndef ADDRECEIVERDIALOG_H
#define ADDRECEIVERDIALOG_H

#include <QDialog>

#include "Implement/iterfacetomysql.h"

namespace Ui {
class AddReceiverDialog;
}

class AddReceiverDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddReceiverDialog( QString parkId, QWidget *parent = 0);
    ~AddReceiverDialog();

    QStringList &GetReceiverItemInfo();

private:
    bool Verify();
    
private slots:
    void on_ptnAdd_clicked();
    void on_ptnCancel_clicked();

private:
    Ui::AddReceiverDialog *ui;
    QStringList lstInfos;
    QString g_parkID;
    QString parkReceiverId;
};

#endif // ADDRECEIVERDIALOG_H
