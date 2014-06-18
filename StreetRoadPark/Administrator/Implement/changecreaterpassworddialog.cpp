#include "changecreaterpassworddialog.h"
#include "ui_changecreaterpassworddialog.h"

#include <QMessageBox>

ChangeCreaterPasswordDialog::ChangeCreaterPasswordDialog(QString userid, QString userpass, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeCreaterPasswordDialog)
{
    ui->setupUi(this);
    userID.append( userid );
    password.append( userpass );
}

ChangeCreaterPasswordDialog::~ChangeCreaterPasswordDialog()
{
    delete ui;
}

QString &ChangeCreaterPasswordDialog::GetPassword()
{
    return password;
}

void ChangeCreaterPasswordDialog::on_pbtYes_clicked()
{
    QString oldPass = ui->edtOldPass->text();

    if( 0 != oldPass.compare( password ) )
    {
        QMessageBox::information( NULL, "提示", "密码不正确，请重新输入！", "确定" );
        return;
    }

    QString newPass = ui->edtNewPass->text();

    password = newPass;
    close();
    this->setResult( ChangeCreaterPasswordDialog::Accepted );
}

void ChangeCreaterPasswordDialog::on_pbtNo_clicked()
{
    close();
}
