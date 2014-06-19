#ifndef DLGGARAGEINGARAGE_H
#define DLGGARAGEINGARAGE_H

#include <QDialog>
#include <QResizeEvent>
#include "../Header/printyearlyreport.h"

namespace Ui {
    class CDlgGarageInGarage;
}

class CDlgGarageInGarage : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgGarageInGarage(QWidget *parent = 0);
    ~CDlgGarageInGarage();

    bool FillTable( QString& strCardID );

protected:
    void resizeEvent(QResizeEvent *);

private:
    void SetFrameVisble( bool bVisible );
    void DisplayPic( QTableWidget* pWidget, int nRow, int nCol );

private:
    Ui::CDlgGarageInGarage *ui;
    CPrintYearlyReport* pFrmDisplayPic;

private slots:
    void on_lblClose_linkActivated(QString );
    void on_tabRecord_cellClicked(int row, int column);
};

#endif // DLGGARAGEINGARAGE_H
