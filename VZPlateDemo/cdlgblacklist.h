#ifndef CDLGBLACKLIST_H
#define CDLGBLACKLIST_H

#include <QDialog>
#include "cconfigurator.h"

namespace Ui {
class CDlgBlacklist;
}

class CDlgBlacklist : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgBlacklist(QWidget *parent = 0);
    ~CDlgBlacklist();

private:
    void AddRow( const QString& strPlate );
    void ReadPlate( );
    void SavePlate( );
    inline void SelectRow( int nIndex );
    
private slots:
    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnSave_clicked();

private:
    Ui::CDlgBlacklist *ui;
};

#endif // CDLGBLACKLIST_H
