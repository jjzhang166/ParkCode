#ifndef REEWALRECORDS_H
#define REEWALRECORDS_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include "mainwindow.h"

namespace Ui {
    class
#if defined( NewUI )
    CONCAT_NEW_NAME( New, CRenewalRecords );
#else
    CONCAT_NEW_NAME( , CRenewalRecords );
#endif;
}

class CRenewalRecords : public QFrame
{
    Q_OBJECT

public:
    explicit CRenewalRecords( QWidget* mainWnd, QWidget *parent = 0);
    ~CRenewalRecords();

protected:
    void  closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void showEvent(QShowEvent *);
    void CalculatePos( );

private:
    void FillTable( );
    void ControlDataGrid( );

private:

#if defined( NewUI )
    Ui::CONCAT_NEW_NAME( New, CRenewalRecords )
#else
    Ui::CONCAT_NEW_NAME( , CRenewalRecords )
#endif
     *ui;

    MainWindow* pParent;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnMinimalize_clicked();
};

#endif // REEWALRECORDS_H
