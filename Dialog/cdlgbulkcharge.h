#ifndef CDLGBULKCHARGE_H
#define CDLGBULKCHARGE_H

#include <QDialog>

namespace Ui {
class CDlgBulkCharge;
}

class CDlgBulkCharge : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgBulkCharge(QWidget *parent = 0);
    ~CDlgBulkCharge();

private:
    bool SaveData( );
    void GetUnit( );
    void InitUI( );
    
private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::CDlgBulkCharge *ui;
};

#endif // CDLGBULKCHARGE_H
