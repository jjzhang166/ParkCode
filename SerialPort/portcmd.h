#ifndef PORTCMD_H
#define PORTCMD_H

#include <QObject>
#include <QSettings>
#include <QTextCodec>

class CPortCmd : public QObject
{
    Q_OBJECT
public:
    explicit CPortCmd(QObject *parent = 0);
    typedef enum __PortDownCmd {
        DownSuccess,
        DownFailed,
        DownCCDisplay,
        DownOpenGate,
        DownCloseGate,
        DownDispenserReset,
        DownDispenserSend,
        DownDispenserReceive,
        DownDispenserQuery,
        DownPlayAudio,
        DownLED,
        DownQuerySense,
        DownQueryButton,
        DownQueryGate,
        DownQueryControler
    } PortDownCmd;

    typedef enum __PortUpCmd {
        UpNone,
        UpSuccess,
        UpFailed,
        UpCCExist,
        UpInGateExist,
        UpOutGateExist,
        UpCardInfo,
        UpDispenserReply,
        UpAudioEnd,
        UpInBallotSenseVehcleEnter,
        UpInBallotSenseVehcleLeave,
        UpOutBallotSenseVehcleEnter,
        UpOutBallotSenseVehcleLeave,
        UpButtonDownCar,
        UpButtonUpCar,
        UpButtonDownNoCar,
        UpButtonUpNoCar,
        UpInGateSenseVehcleEnter,
        UpInGateSenseVehcleLeave,
        UpOutGateSenseVehcleEnter,
        UpOutGateSenseVehcleLeave,
        UpQuerySenseCar,
        UpQuerySenseNoCar,
        UpQueryButtonOpen,
        UpQueryButtonClose,
        UpQueryGateCar,
        UpQueryGateNoCar,
        UpQueryControler,
    } PortUpCmd;

    typedef enum __LedInfo {
        LedShuaCard,
        LedGoodLuck,
        LedWelcome,
        LedFee,
        LedPass,
        LedCardMonth,
        LedCardSave,
        LedCardTime,
        LedCardInvalid,
        LedContactAdmin,
        LedMonthlyExceed,
        LedMonthlyRemainder,
        LedSaveRemainder,
        LedSaveRemainderInsufficient,
        LedTimeRemainder,
        LedCardLoss,
        LedRenewal,
        LedRecharge,
        LedCCDisplay,
        LedCarInside,
        LedCarOutside,
        LedStartup,
        LedTimeCardExit,
        LedSaveCardExit,
        LedTimeCardEnter,
        LedTimeCardPass,
        LedExitConfirm,
        LedCardNoRight,
        LedParksFull,
    } LedInfo;

    typedef enum __AudioAddress {
        AudioShuaCard,
        AudioGoodLuck,
        AudioWelcome,
        AudioFee,
        AudioPass,
        AudioCardInvalid,
        AudioContactAdmin,
        AudioMonthlyExceed,
        AudioMonthlyRemainder,
        AudioCardMonth,
        AudioCardSave,
        AudioCardTime,
        AudioSaveRemainder,
        AudioSaveRemainderInsufficient,
        AudioTimeRemainder,
        AudioCardLoss,
        AudioRenewal,
        AudioRecharge,
        AudioCCDisplay,
        AudioCarInside,
        AudioCarOutside,
        AudioStartup,
        AudioTimeCardExit,
        AudioSaveCardExit,
        AudioTimeCardEnter,
        AudioTimeCardPass,
        AudioExitConfirm,
        AudioCardNoRight,
        AudioParksFull
    } AudioAddress;

    void ParseDownCmd( QByteArray& byData, PortDownCmd cmdType, QByteArray& vData );
    PortUpCmd ParseUpCmd( QByteArray& byData, quint16& nDataLen, quint8& nCanAddr, quint8& nCheckSum, QByteArray& vData );
    quint8 CheckSum( QByteArray& byData );
    void GetLedInfo( LedInfo infoType, QByteArray& vData );
    void GetLedInfo2( LedInfo infoType, QByteArray& vData, QString* pStrParam, ... );
    void GetAudioAddr( AudioAddress audioType, QByteArray& vData );
    void GetAudioAddr2( AudioAddress audioType, QByteArray* pData, ... );
    void GetAudioDigital( QByteArray& vData, quint8 nDigital );
    void GetAudioChineseChar( QByteArray& vData, quint8 nIndex );
    void GetAudioLatinChar( QByteArray& vData, QString& strChar );
    void GetAudioAbbreviation( QByteArray& vData, QString& strAbbrev );


private:
    void SplitString( QString& strCmd, QByteArray& byData );
    void ConvertHex2MyString( QByteArray& vData, QString& strHex );

private:
       QSettings* pSettings;
       QTextCodec* pCodec;
       int nLedMsgCounter;

signals:

public slots:

};

#endif // PORTCMD_H
