#ifndef COMMONTYPE_H
#define COMMONTYPE_H

#include <QString>
#include <QHash>
#include <QDateTime>

namespace CommonDataType {
    typedef enum __ReportType {
        ReportYearly,
        ReportMonthly,
        ReportDaily,
        ReportPerson,
        ReportTimeCardDetail,
        ReportChannel,
        ReportProvince,
        ReportInProvince,
        ReportMonth,
        ReportMonthInOut
    } ReportType;

    typedef enum __UserRequest {
        UserCenterControler,
        UserPheripheral,
        UserPublishLed,
        UserSMS
    } UserRequest;

    typedef enum __DatagramType {
        DGPassRecord,
        DGSyncTime,
        DGPublishLed,
        DGSvrAlert,
        DGCpuidRequest,
        DGCpuidResponse,
        DGGateCommand,
        DGTypeCount
    } DatagramType;

    typedef struct __Datagram {
        DatagramType dgType;
        void* pBody;
    } Datagram, *PDatagram;

    typedef enum __CardType {
        MonthlyCard,
        ValueCard,
        TimeCard
    } CardType, *PCardType;

    typedef struct __EntityInfo {
        // Generic Info
        QString strCardNumber;
        CardType cardType; // Monthly, Value, Time
        QString cardStatus;
        int nInside;
        bool bMIMO;

        struct __MustCard {
            bool bEnterMustCard;
            bool bLeaveMustCard;
        } MustCard;

        struct __MonthDateTime { // Month
            QDateTime dtStart;
            QDateTime dtEnd;
        } MonthDateTime;

        struct __ValueFees { // Value
            int nSurplus;

        } ValueFees;

        //struct __FeeStandard { // Common
        //   QString strFeeStd;
        //} FeeStandard;
        QString strFeeStd;

        //< Plate, Model > Multi plate
        QHash< QString, QString > carInfo;

        // < ChannelName, QStringList > Access right
        // < Name, StartTime/EndTime/CanAddr/PC IP >
        QMultiHash< QString, QStringList > cardRight;
    } EntityInfo, *PEntityInfo;

    // < CardNumber, PEntityInfo >
    typedef QHash< QString, PEntityInfo > QEntityHash;
    typedef QHash< QString, QString > QPlateCardHash;

    typedef enum __DataPath {
        PathSnapshot,
        PathCfgData,
        PathUIImage,
        PathPlate,
        PathExe
    } DataPath;

    typedef enum __CaptureImageType {
        CaptureBMP,
        CaptureJPG,
        CaptureJPEG,
        CapturePNG
    } CaptureImageType;

    typedef enum __BlobType {
        BlobVehicleIn1,
        BlobVehicleIn2,
        BlobVehicleIn3,
        BlobVehicleIn4,
        BlobVehicleOut1,
        BlobVehicleOut2,
        BlobVehicleOut3,
        BlobVehicleOut4,
        BlobOwner,
        BlobVehicle,
        BlobManualGate1,
        BlobManualGate2,
        BlobManualGate3,
        BlobManualGate4,
        BlobTimeInImg,
        BlobGarageImg
    } BlobType;

    typedef enum __AppInfoType {
        AppDirPath,
        AppFilePath,
        AppTariffFile,
        AppDBMaintaince
    } AppInfoType, *PAppInfoType;

    typedef enum __DatabaseOperation {
        SelectData,
        DeleteData,
        UpdateData,
        InsertData

    } DatabaseOperation, *PDatabaseOperation;

    typedef enum __SysLogType {
        ShiftLog,
        CardMgmLog,
        DeleteDBLog,
        ManualGateLog,
        HardwareInfoLog
    } SysLogType, *PSysLogType;

    typedef enum __ChildWndType {
        ShiftLogoutWnd,
        RightMgmWnd,
        TariffSettingWnd,
        DBMaintenanceWnd,
        SysLogWnd,
        PwdModificationWnd,
        MonthlyCardWnd,
        ValueCardWnd,
        TimeCardWnd,
        PublishLEDInfoWnd,
        DeviceConfigWnd,
        SysSettingWnd,
        BatchSetCardAccessWnd,
        TollDiscountTypeSetWnd,
        Access2RecordsWnd,
        RenewalRecordsWnd,
        DiscountSummaryReportWnd,
        PrintDaylyReportWnd,
        PrintMonthlyReportWnd,
        PrintYearlyReportWnd,
        HandheldICProcessWnd,
        MonitorWnd,
        BlacklistWnd,
        PictureContrast,
        RemoteMgmt
    } ChildWndType, *PChildWndType;

    typedef enum __CfgType {
        CfgSystem,
        CfgDbMaintain,
        CfgTariff,
        CfgDevice,
        CfgSysSet,
        CfgPlate
    } CfgType;

    //const char*
}

#endif // COMMONTYPE_H
