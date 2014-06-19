#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Controller/qcontroller.h"
#include <QRadioButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include "../ControllerCmd/qcontrollercmd.h"

#define QUERY_CMD_COUNT     ( qint8 ) 16

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void GetQueryCmd( QByteArray* pData );
    void SendCmd( const bool bNewDevice, const LedControll::ECommand eCmd, qint32 nParam );
    qint32 GetRbIndex( QObject* pSender );
    char GetSelectedRbIndex( QHash< char, QRadioButton* >& hash );
    void SwitchModeUI( const bool bFreqMode );
    void ChangMode( qint32 nMode, const bool bNeedChange );
    inline void SetOldMaxSize( );
    inline void SetNewMaxSize( );
    inline void SetSize( qint32 nWidth, qint32 nHeight );
    void SaveOldDevConfig( LedControll::SSysConfig& sConfig );
    void SaveNewDevConfig( LedControll::SNewSysConfig& sConfig );
    void SaveLocationConfig( QString& strLocation, wchar_t* pBuffer );
    void GetLocationDefault( QString& strLocation, const bool bNewDev );
    inline bool IsNewDevice( );
    inline void SetNewFlash( QObject* pBox);

    void UpdateUI( qint8 nIndex, QByteArray byData );
    void SetComboxValue( QComboBox* pCB, qint8 nValue );
    void ClearRadioboxValue( QHash< char, QRadioButton* >& hash, qint8 nKey );

protected:
    void timerEvent( QTimerEvent * e );

private slots:
    void on_btnSet_clicked();

    void on_btnSaveSet_clicked();

    void on_tbnReadSet_clicked();

    void on_btnTestFlash_clicked();

    void OnRbModeXClicked( );

    void OnRbSyncXClicked( );

    void OnSpXValueChanged( int nValue );

    void on_chkDevType_clicked(bool checked);

    void on_chkLightSensitive_clicked(bool checked);

    void on_chkBaseLight_clicked(bool checked);

    void on_cbMode_currentIndexChanged(int index);

    void on_btnQuery_clicked();

    void HandleCmd( QByteArray data, bool bSend );

    void HandleData( QByteArray data );

    void HandleQuery( QString strInfo, qint8 nIndex, QByteArray byData );

    void on_tabWidgetDevice_currentChanged(int index);

    void on_chkLightSensitiveFreq_clicked(bool checked);

    void on_chkLightSensitiveFlash_clicked(bool checked);

    void on_tabWidget_currentChanged(int index);

    void CbCurrentIndexChanged( int index );

private:
    void DlgConfig( );
    void InitializeSlot( );
    void InitializeUI( );
    void InitializeUI( const QString& strFile, const bool bNewDev );
    void InitializeUI( const LedControll::SSysConfig& sConfig, const bool bNewDev );
    void SetQueryTemplate( );
    inline void GetCheckBoxState( QHash< char, QRadioButton* >& hash,  char c );
    void SetSpinBoxValue( const LedControll::SSysConfig& sConfig, const bool bNewDev );
    void SetCheckBoxValue( const LedControll::SSysConfig& sConfig, const bool bNewDev );
    void SetComboBoxValue( const LedControll::SSysConfig& sConfig );
    void SetLocation( const LedControll::SSysConfig& sConfig, const bool bNewDev );
    inline void SetFlash( const bool bValue );
    inline bool GetFlash( );
    quint8 GetCbBCDValue( const QComboBox* pCB  );
    void InitializeCB( QComboBox* pCB );

private:
    QHash< char, QRadioButton* > hashMode;
    QHash< char, QRadioButton* > hashSync;
    QHash< char, QRadioButton* > hashFlashSync;
    QHash< char, QRadioButton* > hashFreqSync;
    QList< QObject* > lstFlashCtrl;
    
private:
    Ui::MainWindow *ui;
    QController controller;
    QControllerCmd* controllerCmd;
    bool bFlash;
    qint32 nModeIndex;
    QString strState;
    QString strStateValue[ QUERY_CMD_COUNT ];
    QByteArray byQueryCmds[ QUERY_CMD_COUNT ];
    qint32 nTimerID;
};

#endif // MAINWINDOW_H
