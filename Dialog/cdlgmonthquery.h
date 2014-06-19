#ifndef CDLGMONTHQUERY_H
#define CDLGMONTHQUERY_H

#include <QDialog>

namespace Ui {
class CDlgMonthQuery;
}

class CDlgMonthQuery : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgMonthQuery(QWidget *parent = 0);
    ~CDlgMonthQuery();
    void GetParams( QStringList& lstParams );
    void SetParams( QStringList& lstParams );
    
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::CDlgMonthQuery *ui;
};

#endif // CDLGMONTHQUERY_H
