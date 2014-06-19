#ifndef LOGICINTERFACE_H
#define LOGICINTERFACE_H
#include <QStringList>
#include <QString>
#if PLATEDEMO_H
    #include "../Common/commonfunction.h"
    #include "../Database/mysqldatabase.h"
#elif VEHICLELICENSE_LIBRARY
    #include "../Common/commonfunction.h"
    #include "../Database/mysqldatabase.h"
#elif MULTIMEDIA_LIBRARY
    #include "../Common/commonfunction.h"
    #include "../Database/mysqldatabase.h"
#elif PARAM_CFG_H
    #include "../Common/commonfunction.h"
    #include "../Database/mysqldatabase.h"
#elif PARKDATARECEIVER_APP
    #include "../Common/commonfunction.h"
    #include "../Database/mysqldatabase.h"
#elif PARKDATACLIENT_APP
    #include "../Common/commonfunction.h"
    #include "../Database/mysqldatabase.h"
#else
    #include "Common/commonfunction.h"
    #include "Database/mysqldatabase.h"
#endif

class CLogicInterface
{
public:
    CLogicInterface( );
    ~CLogicInterface( );

public:
    static CLogicInterface* GetInterface( );
    static void ReleaseInterface( );

public:
    void ExistCardNumber( QString& strCardNo, QStringList& strList );
    int OperateOwnerInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int OperateCarInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int OperateChargeRecord( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int OperateInOutRecord( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int OperateInOutRight( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int DbDeleteRd( int nIndex, QString& strDate );

    void OperateICCard( QStringList& lstData, bool bOpen );
    int OperateRechargeInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int  OperateOutInInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int OperateBlacklistInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int OperateTollDiscountInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int OperateBatchCardInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    void OperateSysSettingInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation );
    void OperateDeviceConfigInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation );
    void ControlLedInfo( QStringList& lstChannel, QString& strInfo, QStringList& lstResult );
    int OperateCardInfo( QStringList& lstRows, CommonDataType::CardType carType, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int OperateSysLogInfo( QStringList& lstRows, CommonDataType::SysLogType logType, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    void OperateTariffInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    int OperateRightInfo( QStringList& lstRows, CommonDataType::DatabaseOperation dbOperation, QString& strWhere );
    void GetStatusInfo( );
    void GetRealTimeImg( );
    void GetEnteranceInfo( QString& strKey, QStringList& lstInfo );
    bool RecognizeBarcode( QString& strBarcode );
    void ControlCardDispenser( QStringList& lstChannel, bool bOpenGate, QString& strCmd, QStringList& lstResult );
    void GetAllChannels( QStringList& lstChannel, QString strEntrance );
    void GetAllParks( QStringList& lstPark );
    void GetCurrentPark( QStringList& lstPark );
    void ControlGate( QStringList& lstChannel, bool bOpenGate, QString& strCmd, QStringList& lstResult );
    void GetVehicleSpaceInfo( QString& strParking, QStringList& lstParkingInfo );
    void GetAllUsers( QStringList& lstUser );
    void AddAdminUser( );
    bool PingMysql( );
    CMySqlDatabase& GetMysqlDb( bool bHistory = false );
    int ExecuteSql( QString& strSql, bool bHistory = false );
    int ExecuteSql( QString& strSql, QStringList& lstRow, bool bHistory = false );
    void UpdateSaveCardRemainder( bool bAdd, uint nAmount, QString strCardNo );
    void OperateBlob( QString& strFile, bool bSave2Db, CommonDataType::BlobType type, QString& strWhere, bool bHistory = false );
    void OperateBlob( QByteArray& byData, bool bSave2Db, CommonDataType::BlobType type, QString& strWhere, bool bHistory = false );

    void GetEntityInfo( CommonDataType::QEntityHash& entInfo, QString& strWhere /* And Field = value*/, QString strTmpCard = QString( ) );
    void GetPlateCardInfo( CommonDataType::QPlateCardHash& plateCardHash, QString& strWhere );
    void GetCanAddress( );
    void GetAllTariff2File( );

private:
    void ReplaceSqlParam( int nRows, int nCols, QString& strSql, QStringList& lstRows );
    int InnerExcuteSql( QString& strSql, bool bSelect = false, QStringList* pLstRows = NULL, bool bHistory = false );
    void GetBlobSql( QString &strSql, bool bSave2Db, CommonDataType::BlobType type, QString& strWhere );

    void ConnectHistoryDb( bool bHistory );
    void DisconnectHistoryDb( bool bHistory );
private:

    static CLogicInterface* m_pInterface;
    CMySqlDatabase mysqlDb;
    CMySqlDatabase mysqlHistoryDb;
    //HANDLE m_hMainCtrl;
    quint32 m_hMainCtrl;
};

#endif // LOGICINTERFACE_H
