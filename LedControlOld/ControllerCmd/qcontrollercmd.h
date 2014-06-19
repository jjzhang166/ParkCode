#ifndef QCONTROLLERCMD_H
#define QCONTROLLERCMD_H

#include "ControllerCmd_global.h"
#include "qcmdgenerator.h"
#include "qcmdparser.h"
#include "../ControllerCommon/CommonHead.h"

class CONTROLLERCMDSHARED_EXPORT QControllerCmd : public QObject {
    Q_OBJECT

public:
    static QControllerCmd* GetSingleton( );

    void ParseDataDomain( QByteArray& data, QString& strInfo, qint8& nIndex );
    void GetOldCmd( const LedControll::ECommand eCmd, QByteArray& oldData, qint32 nParam );
    void GetNewCmd( const LedControll::ECommand eCmd, QByteArray& newData, qint32 nParam, const bool bQuery, const bool bFlash );

protected:
    QControllerCmd( );
    virtual ~QControllerCmd( );

private:

private:
    QCmdGenerator* cmdGenrator;
    QCmdParser* cmdParser;
    static QControllerCmd* cmdController;
};

#endif // QCONTROLLERCMD_H
