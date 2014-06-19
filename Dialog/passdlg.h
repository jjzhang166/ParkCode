#ifndef PASSDLG_H
#define PASSDLG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
    class CPassDlg;
}

class CPassDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CPassDlg( bool bEnter, QWidget *parent = 0);
    ~CPassDlg();

    char GetCanAddress( );
    bool IsShow( );

protected:

    void closeEvent(QCloseEvent *e);

private:
    Ui::CPassDlg *ui;
    bool bDirection;

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
};

#endif // PASSDLG_H
