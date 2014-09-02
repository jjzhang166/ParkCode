#ifndef CZJDCTRLCMD_H
#define CZJDCTRLCMD_H
#include "CControllerCmd.h"

class CZjdCtrlCmd : public CControllerCmd
{
    Q_OBJECT
public:
    explicit CZjdCtrlCmd(QObject *parent = 0);

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
    
signals:
    
public slots:
    
};

#endif // CZJDCTRLCMD_H
