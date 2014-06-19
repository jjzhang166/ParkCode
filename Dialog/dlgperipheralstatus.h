#ifndef DLGPERIPHERALSTATUS_H
#define DLGPERIPHERALSTATUS_H

#include <QDialog>
#include <QResizeEvent>
#include "Common/commonfunction.h"

namespace Ui {
    class CDlgPeripheralStatus;
}

class CDlgPeripheralStatus : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgPeripheralStatus( bool bEnter, QWidget *parent = 0);
    ~CDlgPeripheralStatus();

protected:
    void resizeEvent ( QResizeEvent * event );

private:
    Ui::CDlgPeripheralStatus *ui;
    bool bPeripheralLocation;
    QSettings* pSettings;
    QString strKey;
    QLineEdit* lblInfos[ 5 ];

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnCancel_clicked();
    void on_btnSave_clicked();
    void OnBtnClicked( );
    void ResponseUserRequest( QByteArray& byData, int nMinor );
};

#endif // DLGPERIPHERALSTATUS_H
