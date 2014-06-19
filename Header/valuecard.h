#ifndef VALUECARD_H
#define VALUECARD_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include "mainwindow.h"
#include <QMenu>
#include <QLineEdit>
#include <QTableWidget>

namespace Ui {
    class
#if defined( NewUI )
    CONCAT_NEW_NAME( New, CValueCard );
#else
    CONCAT_NEW_NAME( , CValueCard );
#endif
}

class CValueCard : public QFrame
{
    Q_OBJECT

public:
    explicit CValueCard( QWidget* mainWnd, QWidget *parent = 0);
    ~CValueCard();
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
    void FillPlateCtrl( );
    void ClearText( int nStart );
    void SaveCarInfo( );

private slots:
    void on_lblClose_linkActivated(QString);
    void on_tableAccess_cellClicked(int row, int column);
    void on_btnMinimalize_clicked();
    void on_tableValue_cellClicked(int row, int column);
    void on_tableValue_customContextMenuRequested( QPoint );
    void AddRecord( );
    void AddBulkRecord( );
    void ModifyRecord( );
    void DeleteRecord( );
    void Recharge( );
    void Serach( );
    void ChangeCard( );
    void Refresh( );
    void PrintCardInfo( );
    void Download2CC( );
    void CardLossProcess( );

private:
#if defined( NewUI )
    Ui::CONCAT_NEW_NAME( New, CValueCard )
#else
    Ui::CONCAT_NEW_NAME( , CValueCard )
#endif
     *ui;
    MainWindow* pParent;
    QMenu* pMenu;
    QStringList lstCarID;
    QLineEdit* edtPlates[ 10 ];

signals:

private slots:
    void on_btnValueRecharge_clicked( );
    void on_btnValueSave_clicked( );
    void on_btnEntranceSave_clicked( );
    void textChanged( QString text );
    void PositionRow( QString strCardID );
    void on_btnSaveRight_clicked();
};

#endif // VALUECARD_H
