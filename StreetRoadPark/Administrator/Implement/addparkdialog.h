#ifndef ADDPARKDIALOG_H
#define ADDPARKDIALOG_H

#include <QDialog>

#include "Implement/iterfacetomysql.h"

namespace Ui {
class AddParkDialog;
}

class AddParkDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddParkDialog( QString strPid, QWidget *parent = 0 );
    ~AddParkDialog();

    QStringList &GetParkItemInfo();

private:
    bool Verify();
    
private slots:
    void on_ptnAdd_clicked();

    void on_ptnCancel_clicked();

private:
    Ui::AddParkDialog *ui;
    QStringList lstInfos;
    QString g_AdminID;
    QString parkId;
};

#endif // ADDPARKDIALOG_H
