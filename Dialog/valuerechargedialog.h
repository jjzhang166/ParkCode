#ifndef VALUERECHARGEDIALOG_H
#define VALUERECHARGEDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QCloseEvent>
#include <QShowEvent>

namespace Ui {
    class CValueRechargeDialog;
}

class CValueRechargeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CValueRechargeDialog( QWidget *parent = 0);
    ~CValueRechargeDialog();

    void GetValue( QStringList& lstRows );
    void SetRemainder( QString strAmount );

private:
    Ui::CValueRechargeDialog *ui;

private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
};

#endif // VALUERECHARGEDIALOG_H
