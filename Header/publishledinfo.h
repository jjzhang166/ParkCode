#ifndef PUBLISHLEDINFO_H
#define PUBLISHLEDINFO_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include "mainwindow.h"

namespace Ui {
    class CPublishLEDInfo;
}

class CPublishLEDInfo : public QFrame
{
    Q_OBJECT

public:
    explicit CPublishLEDInfo( bool bLocalhost, QWidget* mainWnd, QWidget *parent = 0);
    ~CPublishLEDInfo();

protected:
    void  closeEvent ( QCloseEvent * event );
    void showEvent(QShowEvent *);
    void resizeEvent( QResizeEvent * );
    void CalculatePos( );

private:
    void FillTable( );
    void SelectAllCards( QTableWidget* pTable, bool bAll );

private:
    Ui::CPublishLEDInfo *ui;
    MainWindow* pParent;
    bool bLocal;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnDownloadTime_clicked();
    void on_btnUnselectAll_clicked();
    void on_btnSelectAll_clicked();
    void on_btnClose_clicked();
    void on_btnDownload_clicked( );
};

#endif // PUBLISHLEDINFO_H
