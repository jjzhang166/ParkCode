#ifndef CHANGECREATERPASSWORDDIALOG_H
#define CHANGECREATERPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeCreaterPasswordDialog;
}

class ChangeCreaterPasswordDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChangeCreaterPasswordDialog( QString userid, QString userpass, QWidget *parent = 0);
    ~ChangeCreaterPasswordDialog();
    QString &GetPassword();
    
private slots:
    void on_pbtYes_clicked();

    void on_pbtNo_clicked();

private:
    Ui::ChangeCreaterPasswordDialog *ui;
    QString userID;
    QString password;
};

#endif // CHANGECREATERPASSWORDDIALOG_H
