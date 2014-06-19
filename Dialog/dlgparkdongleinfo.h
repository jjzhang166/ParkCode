#ifndef DLGPARKDONGLEINFO_H
#define DLGPARKDONGLEINFO_H

#include <QDialog>
#include "../license/processcpuid.h"

namespace Ui {
class CDlgParkDongleInfo;
}

class CDlgParkDongleInfo : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgParkDongleInfo( CProcessCpuid* pProcessor, QWidget *parent = 0);
    ~CDlgParkDongleInfo();

private:
    void AddRow( QString& strParkID, QString& strBrief, QString& strHids );
    inline void AddColumn( QString& strValue, int nRow, int nCol );
    void FillTableWidget( );
    
private slots:
    void on_btnAdd_clicked();

    void on_btnAddParkID_clicked();

    void on_btnDeleteParkID_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_btnDelete_clicked();

    void on_btnClose_clicked();

    void on_btnSave_clicked();

private:
    Ui::CDlgParkDongleInfo *ui;
    CProcessCpuid* pProcess;
};

#endif // DLGPARKDONGLEINFO_H
