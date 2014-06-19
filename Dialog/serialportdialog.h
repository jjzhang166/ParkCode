#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>

namespace Ui {
    class CSerialPortDialog;
}

class CSerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSerialPortDialog(QWidget *parent = 0);
    ~CSerialPortDialog();
    void GetValue( QStringList& cfgStream, bool bInit );

private:
    Ui::CSerialPortDialog *ui;

private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
};

#endif // SERIALPORTDIALOG_H
