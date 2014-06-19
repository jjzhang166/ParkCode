#ifndef DLGMAKELICENSE_H
#define DLGMAKELICENSE_H

#include <QDialog>
#include "license/processcpuid.h"

namespace Ui {
class CDlgMakeLicense;
}

class CDlgMakeLicense : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgMakeLicense(QWidget *parent = 0);
    ~CDlgMakeLicense();

protected:
    void resizeEvent( QResizeEvent * event );

private:
    bool GetCode( QString& strCode );
    void FillParkID( );
    void ExpImpData( bool bImport );
    void ControlCBXEvent( bool bConnect );
    
private slots:
    void on_btnPSN_clicked();
    void on_btnSave_clicked();
    void on_btnClose_clicked();
    void on_btnData_clicked();

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnExport_clicked();

    void on_btnImport_clicked();
    void CbxIndexChanged( int nIndex );

    void on_btnBatch_clicked();

    void ParkIDChanged( QString& strParkID );

    void on_lblClose_linkActivated(const QString &link);

private:
    Ui::CDlgMakeLicense *ui;
    CProcessCpuid* pProcess;

signals:

};

#endif // DLGMAKELICENSE_H
