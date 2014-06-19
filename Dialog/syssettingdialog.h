#ifndef SYSSETTINGDIALOG_H
#define SYSSETTINGDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QResizeEvent>

namespace Ui {
    class CSysSettingDialog;
}

class CSysSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSysSettingDialog(QWidget *parent = 0);
    ~CSysSettingDialog();

protected:
    void resizeEvent(QResizeEvent * event );

private:
    void ReadFile( );
    void WriteFile( );
    void VideoMode( int& nMode, bool bGet );
    void Precision( int& nPrecision, bool bGet );

private:
    Ui::CSysSettingDialog *ui;
    QSettings* pSettings;
    QString strPath;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnSpecialSave_clicked();
    void on_btnVichle_clicked();
    void on_btnVideoModeSave_clicked();
    void on_btnOK_clicked();
    void on_btnCommonFormat_clicked();
    void on_btnCancel_clicked();
    void on_btnCommonSave_clicked();
};

#endif // SYSSETTINGDIALOG_H
