#ifndef DLGREADCARDID_H
#define DLGREADCARDID_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class CDlgReadCardID;
}

class CDlgReadCardID : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgReadCardID(QWidget *parent = 0);
    ~CDlgReadCardID();

    QStringList& GetCardNoLst( );
    QLineEdit* GetEditCntrl( );
    
private slots:
    void on_btnDeleteAll_clicked();

    void on_btnDeleteSingle_clicked();

    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_edtCardID_textChanged(const QString &arg1);

private:
    Ui::CDlgReadCardID *ui;
    QStringList lstCardNo;
};

#endif // DLGREADCARDID_H
