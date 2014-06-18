#ifndef CDLGCONFIG_H
#define CDLGCONFIG_H

#include <QDialog>
#include "cconfigurator.h"
#include <QComboBox>

namespace Ui {
class CDlgConfig;
}

class CDlgConfig : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgConfig(QWidget *parent = 0);
    ~CDlgConfig();

private:
    void ReadConfig( );
    void Saveconfig( );
    int FillComboBox( QComboBox* pCbx, QString strInfo[ ][ 2 ], int nRow, const QString& strCurItem );
    void EnableAllControls( bool bEnable );
    void EnableIPCControl( bool bEnable );
    void EnbaleCaptureControl( bool bEnable );
    
private slots:
    void on_btnOk_clicked();

    void on_btnClose_clicked();

    void OnVideoType_currentIndexChanged( int index );

    void on_cbxVideoType_currentIndexChanged(int index);

private:
    Ui::CDlgConfig *ui;
};

#endif // CDLGCONFIG_H
