#ifndef QCONTROLLERCOMMON_H
#define QCONTROLLERCOMMON_H

#include "ControllerCommon_global.h"
#include "CommonHead.h"
#include <QSettings>
#include <QWidget>
#include <QTextCodec>
#include <QMessageBox>

class CONTROLLERCOMMONSHARED_EXPORT QControllerCommon {
public:

    static void InitApp( );
    static QTextCodec* GetTextCodec( );
    static void PrintDebugInfo( QString strInfo );
    static void GetPath( QString& strPath, const LedControll::EPath eType );
    static void SaveSPConfig( const LedControll::SComConfig& sConfig );
    static void GetSPConfig( LedControll::SComConfig& sConfig );
    static void SaveModemConfig( const quint8 nDataFlowCtrl, const quint8 nAutoReply );
    static void GetModemConfig( quint8& nDataFlowCtrl, quint8& nAutoReply );
    static void SaveBufferConfig( const qint32 nInBuffer, const qint32 nOutBuffe );
    static void GetBufferConfig( qint32& nInBuffer, qint32& nOutBuffe );
    static void SaveSystemConfig( LedControll::SSysConfig& sConfig );
    static void SaveSystemConfig( LedControll::SSysConfig& sConfig, const QString& strFile );
    static void GetSystemConfig( LedControll::SSysConfig& sConfig );
    static void GetSystemConfig( LedControll::SSysConfig& sConfig, const QString& strFile );
    static void ControlSysMenu( QWidget &wg );
    static int MsgBox( QWidget* pParent, QString strTitle, QString strText, QMessageBox::Icon nType );
    static void GetPorts( QStringList& lstPorts );
    static int GetWaitTime( );

private:
    static QSettings& GetConfigSettings(  );

    static void SaveSystemConfig( LedControll::SSysConfig &sConfig, QSettings& settings );
    static void GetSystemConfig( LedControll::SSysConfig &sConfig, QSettings& settings );

    static void SaveLocation( QSettings& settings, wchar_t* pBuffer, const bool bNewDevice );
    static void GetLocation( QSettings& settings, wchar_t* pBuffer, const bool bNewDevice );

    static int nSleepTime;

protected:
    QControllerCommon();
};

#endif // QCONTROLLERCOMMON_H
