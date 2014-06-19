#ifndef DLGBLACKLISTLOCATION_H
#define DLGBLACKLISTLOCATION_H

#include <QDialog>

namespace Ui {
class CDlgBlacklistLocation;
}

class CDlgBlacklistLocation : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgBlacklistLocation(QWidget *parent = 0);
    ~CDlgBlacklistLocation();

signals:
    void Location( QString strPlate );
    
private slots:
    void on_btnOk_clicked();

    void on_btnClose_clicked();

private:
    Ui::CDlgBlacklistLocation *ui;
};

#endif // DLGBLACKLISTLOCATION_H
