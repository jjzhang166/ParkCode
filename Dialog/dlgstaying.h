#ifndef DLGSTAYING_H
#define DLGSTAYING_H

#include <QDialog>
#include <QTableWidget>
#include <QMenu>
#include "../Header/printyearlyreport.h"
#include "../Report/qreportthread.h"

namespace Ui {
class CDlgStaying;
}

class CDlgStaying : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgStaying(QWidget *parent = 0);
    ~CDlgStaying();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void on_tableWidgetMonth_cellClicked(int row, int column);

    void on_tableWidgetTime_cellClicked(int row, int column);

    void on_tabWidget_currentChanged(int index);

    void on_cbSort_currentIndexChanged(int index);

    void on_chk0_clicked(bool checked);

    void on_chk1_clicked(bool checked);

    void on_chk2_clicked(bool checked);

    void on_chk3_clicked(bool checked);

    void on_chk4_clicked(bool checked);

    void on_chk5_clicked(bool checked);

    void on_chk6_clicked(bool checked);

    void on_chk0_toggled(bool checked);

    void on_tableWidgetNoCard_cellClicked(int row, int column);
    void BulkMonthInRecordProcess( );
    void BulkTimeInRecordProcess( );
    void BulkNoCardInRecordProcess( );
    void ManualTimeFeeProcess( );
    void ManualNoCardFeeProcess( );
    void HandleRefreshData( int nType );

    void on_tableWidgetMonth_customContextMenuRequested(const QPoint &pos);

    void on_tableWidgetTime_customContextMenuRequested(const QPoint &pos);

    void on_tableWidgetNoCard_customContextMenuRequested(const QPoint &pos);

private:
    void BulkInRecordProcess( QTableWidget* pTabWidget, int nType );
    void ManualFeeProcess( QTableWidget* pTabWidget, int nType );

    void GetSpParams( QString& strCardNo, QString& strStoprdid, QTableWidget* pTabWidget );
    void CreateContextMenu( );
    void DisplayMenu( QTableWidget* pTabWidget, QMenu* pMenu, const QPoint& pos );
    void GetData( int nType /*0 all 1 2 3*/);
    void FillTable( QStringList& lstData, QTableWidget* pTable, int nRows );
    void DisplayPic( QTableWidget* pWidget, int nRow, int nCol );
    void SetFrameVisble( bool bVisible );

    void GetOrderByClause( QString& strOrder, int nChk, int nCb, int nCardType/*0 1 2*/ );
    void SortData( int nChk, int nCb, bool bCb = false );
    int GetChkIndex( );
    void GetMonthData( QString& strOrder );
    void GetTimeData( QString& strOrder );
    void GetNocardData( QString& strOrder );
    bool GetClicked( int nChk );
    void SetChkClikedArray( bool bInit );
    
private:
    Ui::CDlgStaying *ui;
    CPrintYearlyReport* pFrmDisplayPic;
    bool bHistory;
    bool bChkCliked[ 7 ];
    QSettings* pSystem;
    QMenu* pMenuMonth;
    QMenu* pMenuTime;
    QMenu* pMenuNoCard;
    QReportThread* pReportThread;
};

#endif // DLGSTAYING_H
