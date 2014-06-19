#ifndef TIMECARD_H
#define TIMECARD_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include "mainwindow.h"
#include <QMenu>

namespace Ui {
    class
#if defined( NewUI )
    CONCAT_NEW_NAME( New, CTimeCard );
#else
    CONCAT_NEW_NAME( , CTimeCard );
#endif
}

class CTimeCard : public QFrame
{
    Q_OBJECT

public:
    explicit CTimeCard( QWidget* mainWnd, QWidget *parent = 0);
    ~CTimeCard();
    void WriteCardLog(QString strCotent);

protected:
    void  closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void CalculatePos( );

private:
    void CreateContextMenu( QTableWidget* parent );
    void OpenDialog( bool bNew );
    void GetDataFromDb( );
    void ControlDataGrid( );

signals:

private slots:
    void on_lblClose_linkActivated(QString);
    void on_tableAccess_cellClicked(int row, int column);
    void on_btnMinimalize_clicked();
    void on_tableTime_cellClicked(int row, int column);
    void on_tableTime_customContextMenuRequested( QPoint );
    void AddRecord( );
    void AddBulkRecord( );
    void ModifyRecord( );
    void DeleteRecord( );
    void Serach( );
    void Refresh( );
    void PrintCardInfo( );
    void Download2CC( );
    void CardLossProcess( );
    void PositionRow( QString strCardID );

    void on_pushButton_8_clicked();

private:
#if defined( NewUI )
    Ui::CONCAT_NEW_NAME( New, CTimeCard )
#else
    Ui::CONCAT_NEW_NAME( , CTimeCard )
#endif
     *ui;
    MainWindow* pParent;
    QMenu* pMenu;
};

#endif // TIMECARD_H
