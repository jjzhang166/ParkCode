#ifndef QDLGCONFIG_H
#define QDLGCONFIG_H

#include <QDialog>
#include "../ControllerCommon/qcontrollercommon.h"

namespace Ui {
class QDlgConfig;
}

class QDlgConfig : public QDialog
{
    Q_OBJECT
    
public:
    explicit QDlgConfig(QWidget *parent = 0);
    ~QDlgConfig();
    char GetComName( );

private:
    void ReadConfig( );
    void WriteConfig( );
    void GetPorts( );
    
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::QDlgConfig *ui;
    char cCom;
};

#endif // QDLGCONFIG_H
