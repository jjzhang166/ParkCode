#ifndef RECHARGEDIALOG_H
#define RECHARGEDIALOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
    class CRechargeDialog;
}

class CRechargeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRechargeDialog( QDateTime& dtEnd, QWidget *parent = 0);
    ~CRechargeDialog();

    void GetValue( QStringList& lstRows );
    void GetCarModel( QString& strCardID );
    QDateTime GetEndDateTime( );

private:
    void CalculateDays( QDateTime dtStart, QDateTime dtEnd );

private:
    Ui::CRechargeDialog *ui;

private slots:
    void on_dtEnd_dateTimeChanged(QDateTime date);
    void on_dtStart_dateTimeChanged(QDateTime date);
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
};

#endif // RECHARGEDIALOG_H
