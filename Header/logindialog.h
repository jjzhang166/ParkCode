#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QShowEvent>

namespace Ui {
    class CLoginDialog;
}

class CLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CLoginDialog(QWidget *parent = 0);
    ~CLoginDialog();

    void GetUsers( bool bStart );
    void GetUserPwd( QString& strUser, QString& strPWd, QString& strID );

    void HideCancelBtn( bool bVisble );
    QString GetOperatorID( );
    void EmployeeCard( QString& strCardno );
    QString GetCurrentUserID( );

    void SetIsLicense( bool bLicenseValue );
    bool GetIsLicense( );
    void HideLicenseButton( bool bServer );

    bool AutoLogin( );

protected:
    void closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * event );
    void keyPressEvent (QKeyEvent * event );
    void showEvent(QShowEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );

private:
    void ResponseButton( int nAccept );
    bool VerifyPwd( );
    void InitDlg( QStringList& strUsers );

private:
    Ui::CLoginDialog *ui;
    QString strImagePath;
    QString strCurrentID;
    bool bLicense;

private slots:
    void on_cbxUserName_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_btnConnectDb_clicked();
    void on_btnCancel_clicked();
    void on_btnImport_clicked();
    void on_btnLogin_clicked();

signals:
    void OnReconnect( );
    void ImportLicenseData( );

};

#endif // DIALOG_H
