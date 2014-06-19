#ifndef TARIFFSETTING_H
#define TARIFFSETTING_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include "mainwindow.h"
#include <QSettings>
#include <QTimeEdit>

namespace Ui {
    class CTariffSetting;
}

class CTariffSetting : public QFrame
{
    Q_OBJECT

public:
    explicit CTariffSetting( QWidget* mainWnd, QWidget *parent = 0);
    ~CTariffSetting();

protected:
    void  closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void CalculatePos( );

private:
    void GetValue( QStringList& lstValues );
    void GetAllParking( );
    void GetTariff(  );
    void ReadIniFile( );
    void WriteIniFile( );
    void ControlUI( bool bSection );

    void ControlRuleUI( bool bInner, int nIndex, bool bEnabled );
    void CompareTime( QTimeEdit& edtTime, QTime& time, bool bSequence );
    void ControlPerMinUI( bool bInner, bool bEnabled );
    void SaveData( );
    void GetWhere( QString& strWhere );

private:
    Ui::CTariffSetting *ui;
    MainWindow* pParent;
    QSettings* pSettings;
private slots:
    void on_lblClose_linkActivated(QString );
    void on_cbxName_currentIndexChanged(int index);
    void on_perMinOuter_valueChanged(int nValue );
    void on_perMinInner_valueChanged(int nValue );
    void on_tabWidget_currentChanged(int index);
    void on_tdtSection2_timeChanged(QTime date);
    void on_tdtSection1_timeChanged(QTime date);
    void on_rule7MinOuter_valueChanged( int nValue );
    void on_rule6MinOuter_valueChanged( int nValue );
    void on_rule5MinOuter_valueChanged( int nValue );
    void on_rule4MinOuter_valueChanged( int nValue );
    void on_rule3MinOuter_valueChanged( int nValue );
    void on_rule2MinOuter_valueChanged( int nValue );
    void on_rule1MinOuter_valueChanged( int nValue );
    void on_rule7MinInner_valueChanged( int nValue );
    void on_rule5MinInner_valueChanged( int nValue );
    void on_rule4MinInner_valueChanged( int nValue );
    void on_rule3MinInner_valueChanged( int nValue );
    void on_rule2MinInner_valueChanged( int nValue );
    void on_rule1MinInner_valueChanged( int nValue );
    void on_rule6MinInner_valueChanged( int nValue );
    void on_rbtnSection_clicked();
    void on_rbtnNoSection_clicked();
    void on_btnDownload_clicked( );
    void on_btnSave_clicked( );
    void on_btnSaveExit_clicked( );
    void on_btnCalculate_clicked( );
    void on_cbxType_currentIndexChanged ( int index );
};

#endif // TARIFFSETTING_H
