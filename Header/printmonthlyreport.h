#ifndef PRINTMONTHLYREPORT_H
#define PRINTMONTHLYREPORT_H

#include <QFrame>
#include <QCloseEvent>
#include "mainwindow.h"

namespace Ui {
    class CPrintMonthlyReport;
}

class CPrintMonthlyReport : public QFrame
{
    Q_OBJECT

public:
    explicit CPrintMonthlyReport( QWidget* mainWnd, QWidget *parent = 0);
    ~CPrintMonthlyReport();

    void SetChannelIndex( int& nChannel, int& nIndex );
    void InitResBtn( QString& strPlate );

protected:
    void  closeEvent ( QCloseEvent * event );
    void showEvent(QShowEvent *);

private:
    void DisableChinese( );
    void InitUI( );
    void ConnectResBtn( quint32 nCount, QString& strPlate );
    void ClearPlate( );

private:
    Ui::CPrintMonthlyReport *ui;
    MainWindow* pParent;
    QString strAbbreviation;
    int nPlateChannel;
    int nPlateIndex;
    int nChineseCount;
    QString strPlates;

signals:
    void SendValue( QString strValue, int nChannel, int nIndex );
    void ManualRecogonization( int nChannel );
    void ManualRecogonization( int nChannel, QString strPlate );
    void ClearMonitorPlate( int );

private slots:
    void on_btn96_clicked();
    void on_btn99_clicked();
    void OnBtnClicked( );
    void OnBtnResClicked( );
    void on_btnClear_clicked();
};

#endif // PRINTMONTHLYREPORT_H
