#ifndef CDLGQUERYWHERE_H
#define CDLGQUERYWHERE_H

#include <QDialog>

namespace Ui {
class CDlgQueryWhere;
}

class CDlgQueryWhere : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgQueryWhere(QWidget *parent = 0);
    ~CDlgQueryWhere();
    void GetWhere( QStringList& lstWhere );
    
private slots:
    void on_rb2_clicked(bool checked);

    void on_rb3_clicked(bool checked);

    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::CDlgQueryWhere *ui;
};

#endif // CDLGQUERYWHERE_H
