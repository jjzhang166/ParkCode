#ifndef PROCESSCPUID_H
#define PROCESSCPUID_H

#include <QObject>
#include "Common/logicinterface.h"
#include "Network/parkintranet.h"
#include "license/license.h"
#include <QTableWidget>

#define KEY_GUID "PMS123456789ËÄ´¨Ç°Í¾"

class CProcessCpuid : public QObject
{
    Q_OBJECT
public:
    explicit CProcessCpuid( QTableWidget* pWidget, QObject *parent = 0 );
    ~CProcessCpuid( );
    void SaveData( QString& strParkID );
    void GetData( QString& strParkID );
    bool ImportData( QString& strFile ) ;
    bool ExportData( QString& strFile, QString& strParkID );
    bool Import2Database( );

    void CpuidRequest( );

    bool OperateBlob( QByteArray& byData, QString& strParkID, bool bRead );
    void AddRow( QStringList& lstRow );
    void Batch( QString& strAdminParkID, QString& shrHid );
    void GetAllHIDs( QStringList& lstHids );

private:
    void CreateDropSP( bool bCreate );
    bool GetCipherData( QByteArray& byData, QString& strParkID  );
    bool GetPlainData( QByteArray& byData );
    inline bool OperateFileData( QByteArray& byData, QString& strFile, bool bWrite );
    bool RowExist( QStringList& lstRow );
    void GenerateRow( QStringList& lstRow, QString& strHID, QString& strIP, QString& strAdminParkID );
    void GetAllHIDs( QString& strParkID, QComboBox* pCbx );
    QComboBox* GetHidCbx( QString& strHid, QComboBox* pSender );
    void CallSP( QString& strParkID );

private:
    QTableWidget* pTableWidget;
    
signals:
    void ParkIDChanged( QString& strParkID ); 

public slots:
    void CpuidResponse( QStringList& lstData );
    void HIDChanged( QString strHID );
};

#endif // PROCESSCPUID_H
