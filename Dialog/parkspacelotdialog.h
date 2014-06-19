#ifndef PARKSPACELOTDIALOG_H
#define PARKSPACELOTDIALOG_H

#include <QDialog>

namespace Ui {
    class CParkSpaceLotDialog;
}

class CParkSpaceLotDialog : public QDialog
{
    Q_OBJECT //

public:
    explicit CParkSpaceLotDialog(QWidget *parent = 0);
    ~CParkSpaceLotDialog();

    void InitDlg( bool bChannel, QStringList& lstRows, bool bEneter, QStringList& lstCan );
    void GetParkName( QString& strName );
    void GetCanAddress( QVector< char >& vecCan );
    void GetCanAddress( QStringList& lstCan );

private:
    Ui::CParkSpaceLotDialog *ui;
    QString strParkName;

    // signals
    // emit
private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
    void RadioClick( );
};

#endif // PARKSPACELOTDIALOG_H
