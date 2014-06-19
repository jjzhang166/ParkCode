#ifndef TIMECARDDIALOG_H
#define TIMECARDDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QCloseEvent>
#include <QShowEvent>

namespace Ui {
    class CTimeCardDialog;
}

class CTimeCardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CTimeCardDialog(bool bNew, QString strUser, QTableWidget *pTable, QWidget *parent = 0);
    ~CTimeCardDialog();
    void InitDlg( );
    QLineEdit* GetCardNumCtrl( );

private:
    void SaveValue( );
    void FillTable( bool bNew );
    QString ClearZero( QLineEdit* pEdit );

protected:
    void closeEvent( QCloseEvent * event );
    void showEvent(QShowEvent *);

private:
    Ui::CTimeCardDialog *ui;
    QString strRecorder;
    QTableWidget *pMonTable;
    bool m_bNew;

private slots:
    void on_edtCardNumber_textChanged(QString strText);
    void on_btnExit_clicked();
    void on_btnSave_clicked();
};

#endif // TIMECARDDIALOG_H
