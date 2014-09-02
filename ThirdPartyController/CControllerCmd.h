#ifndef CCONTROLLERCMD_H
#define CCONTROLLERCMD_H

#include <QtCore>
#include <QObject>
#include "EnumType.h"

class CControllerCmd : public QObject
{
    Q_OBJECT
public:
    explicit CControllerCmd(QObject *parent = 0);
    
    virtual void Initialize( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;
    virtual void ModifyTime( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;
    virtual void ReadTime( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;
    virtual void SelectWorkMode( QByteArray& byCmdData, quint16 nControllerAddr, bool bOffline ) = 0;

    // Output Cmd
    virtual void GetOpenGateCmd( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;
    virtual void GetCloseGateCmd( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;
    virtual void GetStopGateCmd( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;
    virtual void GetRejectOpenGateCmd( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;

    virtual void ReadRecordState( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;
    virtual void ReadCardID( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;

    virtual void BallotSenseEnter( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;
    virtual void BallotSenseLeave( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;

    virtual void GateSenseEnter( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;
    virtual void GateSenseLeave( QByteArray& byCmdData, quint16 nControllerAddr ) = 0;

    virtual void CarCreditCard( QByteArray& byCmdData, quint16 nControllerAddr,
                                QByteArray& byCardID ) = 0;
    virtual void CarFreeCard( QByteArray& byCmdData, quint16 nControllerAddr, QByteArray& byCardID ) = 0;
    virtual CmdType GetEnumType( QByteArray& byCmdData ) = 0;
    virtual void ConvertCmd( CtrlType eDstType, CmdType eSrcCmdType,
                             QByteArray& bySrcData, QByteArray& byDstData ) = 0;

protected:
    void GetDateTimeWeek( char& cHYear, char& cLYear, char& cMonth, char& cDay,
                          char&cHour, char& cMinute, char& cSecond, char& cWeek );

    virtual char GetAddress( QByteArray& byCmdData ) = 0;
    virtual void GetCardID( QByteArray& byCmdData, QByteArray& byCardID ) = 0;

private:
    inline void Convert2Hex( char& cData, int nData );

signals:
    
public slots:
    
};

#endif // CCONTROLLERCMD_H
