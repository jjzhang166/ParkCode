#ifndef NetProcessData_H
#define NetProcessData_H

#include <QtCore>
#include <QRunnable>
#include "CommonData.h"
#include "manipulatemessage.h"
#include "../common/commonfunction.h"
#include "../Database/mysqldatabase.h"

class CNetProcessData : public QRunnable

{
public:
    static CNetProcessData* GetInstance( const char* pData, quint64 nLen );
    static void GetCommonParams( );
    static void ReleaseResource( );
    void run( );

    void SetUdpIP( QString& strIP );

private:
    CNetProcessData( const char* pData, quint64 nLen );
    void ProcessData( const char* pData, quint64 nLen );
    void ProcessTableData( const char* pData );
    void ProcessImageData( const char* pData );
    void ProcessHeartbeatData( const char* pData );
    void ProcessSvrMsgData( const char* pData );
    void ProcessWebBrowserRequest( const char* pData );
    void ProcessCltMsgData( const char* pData );
    void ProcessMgmtData( const char* pData );
    static void GetSettings( );
    void GetInOutImage( QStringList& lstData );
    void WebBrowserRequest( const QString& strParkID, const QString& strRequest );
    void ProcessImgRequest( const char* pData );

    void WriteData2Db( const char* pData, const char* pName, quint32 nDataLen );
    bool WriteFile( const char* pData, const QString& strPath, quint32 nDataLen );
    void WriteDb( QString& strPath, const char* pName );
    void GetAllMgmtSql( bool bRequest );
    inline void GetTableSql( QString& strSql, QString& strPath, const char* pName );
    void SendImgRequestData( QByteArray& byData );

private:
    const char* pDatagram;
    quint64 nDataLen;
    CManipulateMessage processMsg;
    static QVector< QString > vecSql;
    static QVector< QString > vecHBCmd;
    static QSettings* pSettings;
    QString strUdpIP;
    QUdpSocket* udpSocket;

    //
    // Mgmt
    //
    static QFile* pFile;
    static CMySqlDatabase* pMySQL;
    static QHash< QString, QString > hashMgmtSql;
    static QMultiHash< QString, QString > hashImgRequest;
    static quint16 nUdpPort;
};

#endif // NetProcessData_H
