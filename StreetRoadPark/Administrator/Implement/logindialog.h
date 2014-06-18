#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QStringList>

#include "Implement/iterfacetomysql.h"

namespace Ui {
class CLoginDialog;
}

class CLoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CLoginDialog(QWidget *parent = 0);
    ~CLoginDialog();

    void InitLogin();
    void Clear();
    bool AutoLogin(QString &strUserName); // 勾选自动登录的
    QString GetUser();
    qint64 GetGroupID();

private:
    void InitCombo();
    void ReadUserFile(); // read lastest login user infor
    void WriteUserFile(); // save lastest login user infor
    void WriteAutoUser();   
    bool VerifyPass(QString &username, QString & password , QStringList &lstRows);

    
private slots:
    void on_btnLogin_clicked();
    void on_cbxUser_currentIndexChanged(int index);
    void on_ptnChangePassword_clicked();

private:
    Ui::CLoginDialog *ui;
    QString filePath;
    qint64 groupId;

};

#endif // LOGINDIALOG_H
