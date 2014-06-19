#ifndef QCMDGENERATOR_H
#define QCMDGENERATOR_H

#include <QObject>
#include "../ControllerCommon/CommonHead.h"

class QCmdGenerator : public QObject
{
    Q_OBJECT
public:
    explicit QCmdGenerator(QObject *parent = 0);
    virtual ~QCmdGenerator( );

    void GetOldCmdBody( QByteArray& body, const LedControll::ECommand eCmd, qint32 nParam = 0 );
    void GetNewCmdBody( QByteArray &body, const LedControll::ECommand eCmd, qint32 nParam, const bool bQuery, const bool bFlash );

private:
    inline void GetFlashStateAlwaysRadianceChane( QByteArray& body );
    inline void GetFlashFrenquencyIntensityTune( const qint16 nTune, QByteArray& body );
    inline void GetFlashGearSet( const qint32 nGear, QByteArray& body );
    inline void GetFrenquencyGearSet( const qint32 nGear, QByteArray& body );
    inline void GetFlashFrenquencyGearClose( const qint32 nClose, QByteArray& body );
    inline void GetFlashGearAlwaysRadianceClose( const qint32 nClose, QByteArray& body );
    inline void GetFlashGearAlwaysRadianceOpen( const qint32 nOpen, QByteArray& body );
    inline void GetFlashFrenquencyGearWorkTimeSet( const qint32 nTime, QByteArray& body );
    inline void GetFlashFrenquencyLightSensitiveIfWork( const qint32 nWork, QByteArray& body );
    inline void GetSyncModeCmd( const qint32 nMode, QByteArray& body );
    inline void GetTestFlashCmd( const qint8 nTest, QByteArray& body );
    inline void GetFrameFrequencyCmd( const qint8 nFrameFreq, QByteArray& body );

    inline void GetNewCmdAddr( QByteArray& body );
    inline void GetCheckSum4NewCmd( QByteArray& body );
    inline void GetControlCode4NewCmd( QByteArray &body, const bool bQuery );
    inline void GetData4NewCmd( QByteArray &body, const LedControll::ECommand eCmd, qint32 nParam, const bool bQuery, const bool bFlash );

    
signals:
    
public slots:
    
};

#endif // QCMDGENERATOR_H
