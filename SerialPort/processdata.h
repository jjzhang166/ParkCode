#ifndef PROCESSDATA_H
#define PROCESSDATA_H

#include <QObject>
#include "SerialPort/winserialport.h"
#include "SerialPort/portcmd.h"
#include "mainwindow.h"
#include "Common/logicinterface.h"
#include "Common/commonfunction.h"
#include <Dialog/picturecontrastdlg.h>
#include <Dialog/dlginconformity.h>
#include <QQueue>
#include <QStack>
#include "dbwritethread.h"
#include "Network/ping.h"
#include "UploadData/quploaddatathread.h"

class CProcessData : public QObject
{
    Q_OBJECT
public:
    typedef enum __ParkCardType {
        CardMonthly,
        CardSave,
        CardTime,
        CardEmployee,
        CardNone
    } ParkCardType;

    typedef enum __QueryStateType {
        GateController
    } QueryStateType;

    int ParseData( QByteArray& byData );

    CWinSerialPort& GetWinSerialPort( );
    bool OpenPort( );
    void ClosePort( );
    bool IsOpen( );

    void ProcessUserRequest( CommonDataType::UserRequest request, char cCan, QStringList& lstData );
    void BroadcastLedInfo( QStringList& lstData );

    static CProcessData* GetProcessor( CWinSerialPort* pWinPort, MainWindow* pWindow );
    static CProcessData* GetProcessor( );
    static void ReleaseProcessor( );
    void ControlGate( bool bOpen, char cCan );
    void CheckCenterContronller( bool bEnter, QDateTime& dtDateTime );

    void TimeCardPass( int nAmount, int nHour, int nMin, QByteArray& byData );
    void RecognizePlate( QString strPlate, int nChannel, int nConfidence, bool bNocard, QByteArray bySerialData );
    void CheckBlacklist( QStringList& lstData );
    int MatchNum( QString &strPlate, const QString &strTest );
    bool RecognizeFuzzyPlate( CommonDataType::QPlateCardHash& hash, QString& strCarNo, QString& strPlate );

    void ParkspaceFull( bool bFull, QString& strInfo, char cCan );
    void CaptureManualGateImage( char cCan, QString& strWhere );

    void SendDbWriteMessage( CDbEvent::UserEvent event, QString &strSql, bool bHistory, bool bTimerCard, bool bSelect, int nInsert, QStringList& lstBroadcastData, QString& strCardNumber, bool bRefreshUI = false, QString strRdid = "" );
    void SendDbWriteMessage( CDbEvent::UserEvent event, QString &strSql, bool bHistory, bool bTimerCard, bool bSelect, bool bGarage, bool bRefreshUI = false, QString strRdid = "" );
    void SendDbWriteMessage( CDbEvent::UserEvent event, QString &strSql, bool bHistory, bool bTimerCard, bool bSelect, int nInsert, QStringList& lstBroadcastData, CommonDataType::BlobType blob, QByteArray &byData );
    void SendDbWriteMessage( CDbEvent::UserEvent event, QString &strSql, bool bHistory, bool bTimerCard, bool bSelect, CommonDataType::BlobType blob, QByteArray &byData );
    void SendDbWriteMessage( CDbEvent::UserEvent event, QString &strCardno, bool bEnter, int nType, bool bGarage, QByteArray &byData );

    bool WriteData( QByteArray& byData );
    void ManualFee( QStringList& lstParams, int nType, char cCan );

private:
    bool NetProbe( );
    void UploadData( QString& strPlate, QString& strCardID, bool bEnter, QString& strDateTime, QByteArray& byImageData );
    explicit CProcessData( CWinSerialPort* pWinPort, MainWindow* pWindow, QObject *parent = 0 );
    CProcessData( QObject *parent = 0 );
    ~CProcessData( );

    void ReadCanForRestart( bool bRead );
    void MakeCardCmd( QString& strCardNo, QByteArray& byData, char cCan );
    void PublishLedInfo( QString& strInfo, char cCan, bool bIndependent = false );

    inline quint32 GetCardNoByCom( QByteArray& byData );
    void EmployeeCard( QByteArray& byData );
    void DefaultClicked( QByteArray& byData );
    void ProcessCmd( QByteArray& byData, CPortCmd::PortUpCmd cmdType );
    void ConfirmSuccess( );
    bool ExitConfirm( QString& strCardno, QByteArray& byData );
    void ProcessCardInfo( QByteArray& byData, bool bPlate = false, QString strCurPlate = QString( ) );
    bool GetCCCardCanAddr( QString& strCardno, char& cCan, bool& bEnter );
    void LoadCapturedImg( QString& strPath, int nChannel );
    void GetCaptureFile( QString& strPath, QString& strCardNo, int nChannel, CommonDataType::CaptureImageType capType );
    void CaptureImage( QString& strCardNo, int nChannel, CommonDataType::CaptureImageType capType );
    void CaptureSenseImage( QByteArray& byData, CommonDataType::CaptureImageType capType );
    void ClearSenseImage( QByteArray& byData );
    void LoadEntranceImg( QString& strCardNo, CommonDataType::CaptureImageType capType );
    //inline bool WriteData( QByteArray& byData );
    inline void PlayAudioDisplayInfo( QByteArray& byData, QByteArray& vData,
                               CPortCmd::LedInfo led, CPortCmd::AudioAddress audio );
    inline void PlayAudioDisplayInfo( QByteArray& byData, QByteArray& vDataLed, QByteArray& vDataAudio,
                               CPortCmd::LedInfo led, CPortCmd::AudioAddress audio );

    inline void GetPlayDisplayList( QByteArray& byData, QByteArray& vDataLed, QByteArray& vDataAudio,
                                    CPortCmd::LedInfo led, CPortCmd::AudioAddress audio, int nChannel );
    void ProcessPlayDisplayList( int nChannel );
    void ComposePlayDisplayData( QList< QByteArray >& listData, int nHeader, int nTail, bool bAudio );

    inline void PlayAudio( QByteArray &byData, QByteArray &vData, CPortCmd::AudioAddress audio );
    inline void DisplayInfo( QByteArray &byData, QByteArray &vData, CPortCmd::LedInfo led );
    void GateSense( QByteArray& byData, QByteArray& vData, bool bEnterGate, bool bLeavePark );
    void GateControllerState( QByteArray& byData, QByteArray& vData );
    void QueryState( QueryStateType stateType );
    void BallotSense( QByteArray& byData, QByteArray& vData, bool bEnterBallot, bool bEnetrPark );
    void Dispenser( QByteArray& byData, QByteArray& vData );
    void BallotButton( QByteArray& byData, QByteArray& vData, bool bDown );
    void DisableSendCardHint( QByteArray& byData, QByteArray& vData );
    //void GetCardType1( QString& strCardNo, QStringList& lstRows, bool bEnter );
    //void GetCardType2( QString& strCardNo, QStringList& lstRows, bool bEnter );
    void GetCardType1( QString& strCardNo, QStringList& lstRows, ParkCardType& cardKind );
    void GetCardType2( QString& strCardNo, QStringList& lstRows, ParkCardType& cardKind );
    bool AssertCard( QByteArray& byData, QByteArray& vData, QStringList& lstRows, QString strPlate, ParkCardType& cardKind );
    bool ProcessMonthlyCard( QByteArray& byData, QByteArray& vData, QStringList& lstRows, QString strPlate, ParkCardType& cardKind );
    bool ProcessSaveCard( QByteArray& byData, QByteArray& vData, QStringList& lstRows, QString strPlate, ParkCardType& cardKind );
    bool ProcessTimeCard( QByteArray& byData, QByteArray& vData, QStringList& lstRows, QString strPlate, ParkCardType& cardKind );
    void ComposeDigitalAudio( QByteArray& vData, QString& strDigital );
    void WriteInOutRecord( bool bEnter, QString& strCardNumber, QString& strTable,
                           QString& strCardType, QString strPlate, char cCan, ParkCardType& cardKind, int nAmount = 0 );
    bool WriteInOutRecord( QByteArray& byData );
    void GetFreeCardSql( QStringList& lstParams, QString& strSql );
    void ManualNoCardWork( QStringList &lstParams, int nAmount, char cCan, QStringList& lstSqlParam );
    void ManualTimeCardWork( QStringList &lstParams, int nAmount, char cCan );
    bool GateNoCardWork( QByteArray& byData, QString& strPlate,
                         char cCan, QString& strCardno, QString& strType,
                         QString& strChannel, int& nFee, bool& bMonth, int& nDiscount );
    inline void GetChannelName( bool bEnter, char cCan, QString& strChannel );
    void GetHourMin( int nMins, int& nHour, int& nMin );
    void WriteFeeData( QString& strCardType, QString& strCardNo, int nAmount, QString& strDateTime );
    void GetCCDisplayInfo( QByteArray& byData, int nHour, int nMin, int nAmout );
    void CardRemainder( QByteArray& byData, QByteArray& vData, QString& strFee,
                        CPortCmd::LedInfo led, CPortCmd::AudioAddress audio, bool bEnter = true );
    void ControlGate( bool bEnter, QByteArray& byData, QByteArray& vData, ParkCardType& cardKind );
    void ShuaCard( QByteArray& byData, QByteArray& vData );
    void CCDisplayInfo( QByteArray& byData, QByteArray& vData, int nMin, int nHour, int nAmount, bool bEnter );
    void CardExitInfo( QByteArray& byData, QByteArray& vData, bool bSave, int nMin,
                       int nHour, int nAmount, int nRemainder = 0, bool bEnter = true );
    bool CarInsideOutside( bool bEnter, QString& strCardNumber, QString& strTable,
                           QByteArray& byData, QByteArray& vData, char cCan, ParkCardType& cardKind );
    void CarInsideOutside( bool bEnter, QString& strTable, QString& strCardNumber, char cCan );
    void ControlChargeInfo( QString &strCardNumber, QDateTime dtLeave, QString strAmount, QString strRetention );
    int CalculateFee( QDateTime& dtStart, QDateTime& dtEnd, QString& strCardNumber, char cCan );
    int CalculateFee( QDateTime& dtStart, QDateTime& dtEnd, QString& strType );
    QString GetFeeStd( QString& strCardNo );

    void QueryGateControllerState( char cAddr );
    QByteArray ControlVehicleImage( QString& strCardNo, bool bSave2Db, int nChannel, int nType,
                                    char cLevel = 1, bool bFreeCard = false, bool bMonth = false,
                                    QString strMonth = QString( ), bool bGarage = false );

    void CarInsideOutsideHash( QString& strInside, QString& strCardNo, bool bGet );

    void GetChannelInfo( QString& strCardNo );
    void GetPlate( QString& strCardNo, QString& strPlate );
    void DeleteCapturedFile( QString& strCardNo, int nChannel, bool bEnter, QDateTime& dtCurrent, QString strPlate );
    void DownloadTime( char cCan, QDate& date, QTime& time );
    void DownloadWelcome( char cCan );

    bool SingleChannel( QString& strPlate, bool bEnter, bool bSame, quint64 nCurrentTime );
    inline quint64 GetTimeSecond( QDateTime& time );
    inline bool GetTimeDiff( int nIntervalTime, quint64 nCurrentTime, QDateTime& tTarget );
    char GetCanLevel( char cCan );
    void TestCaptureImage( QString &strPlate, int nChannel );
    int GetChannelByCan( char cCan );
    inline bool MustCard( bool bEnter, QString& strCardID );
    bool PictureContrast( QStringList& lstRows, int& nAmount, QByteArray& byData, QString& strCardno );
    bool CheckCardRight( QString& strCardID, bool bEnter, QByteArray& byData, ParkCardType& cardKind );
    bool PlateCardComfirm( QString& strCardNumber, QByteArray& byData, QString strPlate, ParkCardType& cardKind );
    bool PlateCardComfirmDlg( QByteArray& byData, QString& strCardNumber, QString strPlate, ParkCardType& cardKind );

    void SendMultiCmd( QList< QByteArray* > lstCmd, char cCan );
    inline short GetCmdDataSize( QByteArray& byCmd );
    inline void SetCmdDataSize( short nSize, QByteArray& byCmd );
    inline void GetCardTypeData( QString& strType, QByteArray& vData );

    void GetNewCardInfo( QString& strCardNo );
    bool GetMonthDeadline( QDateTime& dtEndTime, QString& strCardNo );
    void SendIndependentLedInfo( QString& strInfo, char cCan );
    void SenseOpenGate( QByteArray& byRawData );
    inline bool IfSenseOpenGate( );
    inline bool NoCardWork( );

    void SpaceChange( bool bEnter, char cCan );
    void GetCan2Channel( QString& strWhere );
    void BroadcastRecord( QString& strCardNumber, QDateTime& dtCurrent, int nCardTypeID,
                                        QString strPlate, QString& strCardType,
                          QString& strChannel, char cCan, QString& strStoprdid );

    bool ExcludeRemoteCardDuplication( quint32 nCardID, ParkCardType& cardKind );
    void ClearListContent( int nChannel );

    inline bool MonthCardWorkMode( QString& strCardNo );
    inline bool MonthNoCardWorkMode( );
    inline bool NoPlateOpenGate( );
    //void SendDbWriteMessage( CDbEvent::UserEvent event, QString &strSql, bool bHistory, bool bTimerCard );
    //void SendDbWriteMessage( CDbEvent::UserEvent event, QString &strSql, bool bHistory, bool bTimerCard, CommonDataType::BlobType blob, QByteArray &byData );
    inline bool GetDirectDb( );
    inline bool GetTimeCardBuffer( );
    void CreateBufferTable( );
    inline bool GetEntranceFlag( int nChannel );
    inline int GetChannelIndex( int nChannel );

    int GetMinFee( char cCan );

    void SendPlate( QString strPlate, int nChannel, int nConfidence );
    QString GetCardStatus( QString& strCardNo, ParkCardType cardType );

private:
    bool bUploadData;
    CPing ping;
    CWinSerialPort* pSerialPort;
    CPortCmd portCmd;
    MainWindow* pMainWindow;
    CPictureContrastDlg* pFeeDlg;
    CDlgInconformity* pConfirm[ 4 ];
    //ParkCardType cardType[ 2 ];
    //QString strCardNumber;
    bool bQueryGateControllerState;
    static CProcessData* pCmdProcessor;
    QStringList inChannelInfo;
    QStringList outChannelInfo;
    QString strCurrentPlate[ 4 ];
    QSettings* pSettings;
    bool bHavePlateRecog;
    char cPrecision;
    bool bPlateRecognize[ 4 ];
    QHash< QString, QVector< QDateTime > > singleChannelHash;
    int nSameInterval[ 4 ];
    char cCanVideo[ 4 ];
    bool bPlateClear[ 4 ][ 2 ]; // true : gate / false : Sense
    bool bCardCapture[ 4 ];
    bool bSendOnlyOnce;
    bool bNocardwork;
    bool bNocardworkUnknown;
    QString strVideoChannelName[ 4 ];
    //int nDiffInterval[ 2 ];
    bool bSingleChannel;
    bool bCardConfirm;
    bool bTest;
    bool bParkspaceFull;
    int nMonthWakeup;
    QHash< QString, QString > confirmHash;
    QHash< QString, char > cardCan;
    QQueue< QString > imgQueue[ 4 ];
    QQueue< QString > plateQueue[ 4 ];
    QStack< QString > imgStack[ 4 ];
    QHash< char, QString > hashCanChannel;
    QHash< quint32, quint64 > hashCardTime;
    QList< QByteArray > audioList[ 4 ];
    QList< QByteArray > ledList[ 4 ];
    bool bStartupPlateDilivery;
    bool bBlacklistCheck;
    static QUploadDataThread* pUploadDataThread;
    bool GateIfHaveVehicle[ 2 ];

signals:
    void RefreshUI( QString strRdid );
    void OnResponseUserRequest( QByteArray& byData, int nMinor );
    void PlateDelivery( int nChannel, QStringList lstData, QString strPlate );
    void VehicleGateInOut( bool bEnterGate, bool bLeavePark );

public slots:
    void HandleRefreshUI( QString strRdid );
    void HandleSendFileCount( quint32 nCount );
    void HandleReadThreadData( QByteArray byData );
    void HandleBroadData( QStringList lstData );

private slots:
    void PlateCardComfirmPass( QString strCardNo, char cCan, QString strPlate );
    void HandleWeighing( QStringList lstData );
    void HandleCapture( quint8 nChannel );

    //CardExitInfo( byData, vData, false, nMin, nHour, nAmount ); // 2011 12 18
    //CCDisplayInfo( byData, vData, nMin, nHour, nAmount, bEnter ); // 2011 12 18

    void SendTimeCardInfo( QByteArray& byData, QByteArray& vData, int nMin, int nHour, int nAmount, bool bEnter );
};

#endif // PROCESSDATA_H
