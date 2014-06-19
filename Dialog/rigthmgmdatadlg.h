#ifndef RIGTHMGMDATADLG_H
#define RIGTHMGMDATADLG_H

#include <QDialog>
#include <QTableWidget>
#include <QCloseEvent>
#include <QStringList>

namespace Ui {
    class CRigthMgmDataDlg;
}

class CRigthMgmDataDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CRigthMgmDataDlg(QTableWidget* pTableWG, QWidget *parent = 0);
    ~CRigthMgmDataDlg();

    void InitDlg( );
    void SetNewOrEdit( bool bNew );
    QStringList& GetData( );
    QString GetUser( );
    QLineEdit* GetCardIDCtrl( );

private:
    void NewOrEditDlg( bool bNew );
    bool SameUser( QString &strUser );
    bool ValidCardID( );

protected:
    void  closeEvent ( QCloseEvent * event );

private:
    Ui::CRigthMgmDataDlg *ui;
    QTableWidget* pTableWidget;
    bool bNewOrEdit;
    QStringList* pLstRow;

    void AllSelected( bool bSelected );

private slots:
    void on_btnAllCancel_clicked();
    void on_btnAllOk_clicked();
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
};

#endif // RIGTHMGMDATADLG_H
