#ifndef MONTHLYCARD_H
#define MONTHLYCARD_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include "mainwindow.h"
#include <QMenu>

namespace Ui {
    class
#if defined( NewUI )
    CONCAT_NEW_NAME( New, CMonthlyCard );
#else
    CONCAT_NEW_NAME( , CMonthlyCard );
#endif
}

class CMonthlyCard : public QFrame
{
    Q_OBJECT

public:
    explicit CMonthlyCard( QWidget* mainWnd, QWidget *parent = 0);
    ~CMonthlyCard();

    void WriteCardLog( QString strCotent );

protected:
    void  closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void CalculatePos( );

private:
    void CreateContextMenu( QTableWidget* parent );
    void OpenDialog( bool bNew );
    void GetDataFromDb( );
    void ControlDataGrid( );
    void FillPlateCtrl( );
    void ClearText( int nStart );
    void SaveCarInfo( );
    void MonthBulkProcess( bool bState );
    void GetFilePath( QString& strFile );
    void UpdateImage( QString& strFile, bool bUser );
    void SwitchItem(int row, int column);

private slots:
    void on_lblClose_linkActivated(QString);
    void on_tableAccess_cellClicked(int row, int column);
    void on_btnMinimalize_clicked();
    void on_tableMonthly_cellClicked(int row, int column);
    void AddRecord( );
    void AddBulkRecord( );
    void ModifyRecord( );
    void DeleteRecord( );
    void Recharge( );
    void BulkDate( );
    void BulkState( );
    void Serach( );
    void ChangeCard( );
    void Refresh( );
    void ModifyCardNo( );
    void PrintCardInfo( );
    void Download2CC( );
    void CardLossProcess( );
    void PositionRow( QString strCardID );
    void BroadcastMonthcardData( QStringList& lstWhere );
    void ColHeaderSectionClicked ( int logicalIndex );

private:
#if defined( NewUI )
    Ui::CONCAT_NEW_NAME( New, CMonthlyCard )
#else
    Ui::CONCAT_NEW_NAME( , CMonthlyCard )
#endif
     *ui;
    MainWindow* pParent;
    QMenu* pMenu;
    QStringList lstCarID;
    QLineEdit* edtPlates[ 10 ];

private slots:
    void on_tableMonthly_customContextMenuRequested( QPoint );
    void on_btnMonthRecharge_clicked( );
    void on_btnMonthSave_clicked( );
    void on_btnEntranceSave_clicked( );
    void textChanged ( QString text );

    void on_btnSaveRight_clicked();
    void on_btnLoadUserImg_clicked();
    void on_btnLoadCarImg_clicked();
    void on_tableMonthly_itemSelectionChanged();
};

#endif // MONTHLYCARD_H
