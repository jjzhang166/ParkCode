#ifndef SPACEDIALOG_H
#define SPACEDIALOG_H

#include <QDialog>

namespace Ui {
    class CSpaceDialog;
}

class CSpaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSpaceDialog(QWidget *parent = 0);
    ~CSpaceDialog();
    void SpaceNumber( int& nSpace, bool bGet );
    void SpaceNocardNumber( int& nSpace, bool bGet );
    void ParkName( QString& strName, bool bGet );

private:
    Ui::CSpaceDialog *ui;

private slots:
    void on_pushButton_2_clicked();
    void on_btnOK_clicked();
};

#endif // SPACEDIALOG_H
