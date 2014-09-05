#ifndef CXWCTRLCMD_H
#define CXWCTRLCMD_H

#include "CControllerCmd.h"

class CXwCtrlCmd : public CControllerCmd
{
    Q_OBJECT
public:
    explicit CXwCtrlCmd(QObject *parent = 0);

    virtual void Initialize( QByteArray& byCmdData, quint16 nControllerAddr );
    virtual void ModifyTime( QByteArray& byCmdData, quint16 nControllerAddr );
    virtual void ReadTime( QByteArray& byCmdData, quint16 nControllerAddr );
    virtual void SelectWorkMode( QByteArray& byCmdData, quint16 nControllerAddr, bool bOffline );

    // Output Cmd
    virtual void GetOpenGateCmd( QByteArray& byCmdData, quint16 nControllerAddr );
    virtual void GetCloseGateCmd( QByteArray& byCmdData, quint16 nControllerAddr );
    virtual void GetStopGateCmd( QByteArray& byCmdData, quint16 nControllerAddr );
    virtual void GetRejectOpenGateCmd( QByteArray& byCmdData, quint16 nControllerAddr );

    virtual void ReadRecordState( QByteArray& byCmdData, quint16 nControllerAddr );
    virtual void ReadCardID( QByteArray& byCmdData, quint16 nControllerAddr );

    virtual void BallotSenseEnter( QByteArray& byCmdData, quint16 nControllerAddr );
    virtual void BallotSenseLeave( QByteArray& byCmdData, quint16 nControllerAddr );

    virtual void GateSenseEnter( QByteArray& byCmdData, quint16 nControllerAddr );
    virtual void GateSenseLeave( QByteArray& byCmdData, quint16 nControllerAddr );

    virtual void CarCreditCard( QByteArray& byCmdData, quint16 nControllerAddr, QByteArray& byCardID );
    virtual void CarFreeCard( QByteArray& byCmdData, quint16 nControllerAddr, QByteArray& byCardID );
    virtual CmdType GetEnumType( QByteArray& byCmdData );
    virtual void ConvertCmd( CtrlType eDstType, CmdType eSrcCmdType,
                             QByteArray& bySrcData, QByteArray& byDstData );

protected:
    virtual char GetAddress( QByteArray& byCmdData );
    virtual void GetCardID( QByteArray& byCmdData, QByteArray& byCardID );

private:
    void ConvertCmd2Vz( CmdType eSrcCmdType, QByteArray& byXwData, QByteArray& byVzData );
    
signals:
    
public slots:
    
};

#endif // CXWCTRLCMD_H
