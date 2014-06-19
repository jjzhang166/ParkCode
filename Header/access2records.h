#ifndef ACCESS2RECORDS_H
#define ACCESS2RECORDS_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include "mainwindow.h"
#include <QGroupBox>

namespace Ui {
    class
#if defined( NewUI )
    CONCAT_NEW_NAME( New, CAccess2Records );
#else
    CONCAT_NEW_NAME( , CAccess2Records );
#endif
}

class CAccess2Records : public QFrame
{
    Q_OBJECT

public:
    explicit CAccess2Records( QWidget* mainWnd, QWidget *parent = 0);
    ~CAccess2Records();

protected:
    void  closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void showEvent(QShowEvent *);
    void hideEvent(  QHideEvent* );
    void CalculatePos( );
    void ControlDataGrid( );

private:
    void FillTable( QString& strWhere );
    void GetImage( CommonDataType::BlobType blob, int nRow, bool bEnter );
    void InitQuery( );
    void GetWhere( QString& strWhere );
    inline bool Search( QComboBox* pCB, int nRow, int nCol );

private:
#if defined( NewUI )
    Ui::CONCAT_NEW_NAME( New, CAccess2Records )
#else
    Ui::CONCAT_NEW_NAME( , CAccess2Records )
#endif
     *ui;
    MainWindow* pParent;
    QLabel* lblImage[ 8 ];
    QGroupBox* gbImage[  8 ];
    QLabel* lblScaleImage[ 8 ];
    QComboBox* cbxQuery[ 9 ];

private slots:
    void on_tableAccessRecord_cellDoubleClicked(int row, int column );
    void on_lblClose_linkActivated(QString);
    void on_tableAccessRecord_cellClicked(int row, int column);
    void on_btnMinimalize_clicked();
    void HideCtrl( bool bVisible );
    void on_btnQuery_clicked();
    void on_btnSerach_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
};

#endif // ACCESS2RECORDS_H
