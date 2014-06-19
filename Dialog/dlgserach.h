#ifndef DLGSERACH_H
#define DLGSERACH_H

#include <QDialog>
#include <QResizeEvent>
#include "Common/CommonType.h"
#include <QLineEdit>

namespace Ui {
    class CDlgSerach;
}

class CDlgSerach : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgSerach( CommonDataType::CardType nType, QWidget *parent = 0);
    ~CDlgSerach();

    QLineEdit* GetEditCntrl( );

protected:
    void resizeEvent( QResizeEvent* event );

private:
    void GetWhere( QString& strWhere, QString& strCard );

private:
    Ui::CDlgSerach *ui;
    CommonDataType::CardType nCardType;
    QString strImagePath;
    QString strSql;
    bool bTimeCard;
    QString strCardSql;

signals:
    void PositionRow( QString strCardID );

private slots:
    void on_tabResult_cellDoubleClicked(int row, int );
    void on_lblClose_linkActivated(QString link);
    void on_btnClose_clicked();
};

#endif // DLGSERACH_H
