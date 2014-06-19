#ifndef MONTHLYCARDDIALOG_H
#define MONTHLYCARDDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QCloseEvent>
#include <QShowEvent>

namespace Ui {
    class CMonthlyCardDialog;
}

class CMonthlyCardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CMonthlyCardDialog( bool bNew, QString strUser, QTableWidget *pTable, QWidget *parent = 0);
    ~CMonthlyCardDialog();

    void InitDlg( );
    QLineEdit* GetCardNumCtrl( );

protected:
    void showEvent(QShowEvent * );

private:
    void SaveValue( );
    void FillTable( bool bNew );
    QString ClearZero( QLineEdit* pEdit );

protected:

    void closeEvent( QCloseEvent * event );

private:
    Ui::CMonthlyCardDialog *ui;
    QString strRecorder;
    QTableWidget *pMonTable;
    QStringList m_lstRows;
    bool m_bNew;

private:


private slots:
    void on_edtNumber_textChanged(QString strText );
    void on_btnSave_clicked( );
    void on_btnExit_clicked( );
};

#endif // MONTHLYCARDDIALOG_H
