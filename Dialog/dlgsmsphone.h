#ifndef DLGSMSPHONE_H
#define DLGSMSPHONE_H

#include <QDialog>

namespace Ui {
class CDlgSmsPhone;
}

class CDlgSmsPhone : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgSmsPhone(QWidget *parent = 0);
    ~CDlgSmsPhone();

    void GetPhoneList( QStringList& lstData );

private:
    void Select( bool bAll );
    void FillData( );
    
private slots:
    void on_btnAllSelect_clicked();

    void on_btnAllUnselect_clicked();

    void on_btnOK_clicked();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::CDlgSmsPhone *ui;
};

#endif // DLGSMSPHONE_H
