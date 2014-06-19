#ifndef DLGCARDLOSS_H
#define DLGCARDLOSS_H

#include <QDialog>
#include "Common/logicinterface.h"

namespace Ui {
class CDlgCardLoss;
}

class CDlgCardLoss : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgCardLoss( QString& strCardID, CommonDataType::CardType card, QWidget *parent = 0);
    ~CDlgCardLoss();

private slots:
    void on_btnCancel_clicked();

    void on_btnOK_clicked();

private:
    void SaveData( );
    void AddCbxValue( QComboBox *pCbx );
    
private:
    Ui::CDlgCardLoss *ui;

    QString strCardNo;
    CommonDataType::CardType cardType;
};

#endif // DLGCARDLOSS_H
