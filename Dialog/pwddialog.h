#ifndef PWDDIALOG_H
#define PWDDIALOG_H

#include <QDialog>
#include <QResizeEvent>

namespace Ui {
    class CPwdDialog;
}

class CPwdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CPwdDialog(QWidget *parent = 0);
    ~CPwdDialog();

    void OperateUserPwd( QString& strUserName, QString& strUserPwd, bool bSet );

protected:
    void resizeEvent( QResizeEvent * event );

private:
    Ui::CPwdDialog *ui;
    QString strUser;
    QString strPwd;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnCancel_clicked();
    void on_btnSave_clicked();
};

#endif // PWDDIALOG_H
