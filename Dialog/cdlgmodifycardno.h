#ifndef CDLGMODIFYCARDNO_H
#define CDLGMODIFYCARDNO_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class CDlgModifyCardNo;
}

class CDlgModifyCardNo : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgModifyCardNo(QWidget *parent = 0);
    ~CDlgModifyCardNo();
    QString GetCardNo( );
    QLineEdit* GetCardNumCtrl( );
    void SetCardNo(  QString& strCardNo );
    
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::CDlgModifyCardNo *ui;
};

#endif // CDLGMODIFYCARDNO_H
