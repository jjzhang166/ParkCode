#ifndef VALUECARDDIALOG_H
#define VALUECARDDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QCloseEvent>
#include <QShowEvent>

namespace Ui {
    class CValueCardDialog;
}

class CValueCardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CValueCardDialog(bool bNew, QString strUser, QTableWidget *pTable, QWidget *parent = 0);
    ~CValueCardDialog();
    void InitDlg( );
    QLineEdit* GetCardNumCtrl( );

private:
    void SaveValue( );
    void FillTable( bool bNew );
    QString ClearZero( QLineEdit* pEdit );

protected:
    void showEvent(QShowEvent *);
    void closeEvent( QCloseEvent * event );

private:
    Ui::CValueCardDialog *ui;
    QString strRecorder;
    QTableWidget *pMonTable;
    bool m_bNew;

private slots:
    void on_edtNumber_textChanged(QString strText);
    void on_btnExit_clicked();
    void on_btnSave_clicked();
};

#endif // VALUECARDDIALOG_H
