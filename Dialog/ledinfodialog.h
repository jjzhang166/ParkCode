#ifndef LEDINFODIALOG_H
#define LEDINFODIALOG_H

#include <QDialog>
#include <QResizeEvent>

namespace Ui {
    class CLedInfoDialog;
}

class CLedInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CLedInfoDialog(QWidget *parent = 0);
    ~CLedInfoDialog();

protected:
    void resizeEvent ( QResizeEvent * event );

private:
    void DownloadData( QString& strText );
    bool SelectTarget( );

private:
    Ui::CLedInfoDialog *ui;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnDownloadTime_clicked();
    void on_btnClose_clicked();
    void on_btnDownload_clicked();
};

#endif // LEDINFODIALOG_H
