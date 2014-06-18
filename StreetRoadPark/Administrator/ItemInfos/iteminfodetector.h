#ifndef ITEMINFODETECTOR_H
#define ITEMINFODETECTOR_H
#include <QString>
#include <QMetaType>

//#include "ItemType.h"

class ItemInfoDetector
{
public:
    ItemInfoDetector();
    ItemInfoDetector( QString pid, QString id, quint8 channelID, QString comments,
                      quint16 threshold, quint16 delayTime, char detectorReset, QString receiverDetectorID );

    const QString &getId( ) const;
    const quint8 &getChannelID( ) const;
    const QString &getComments( ) const;
    const quint16 &getThreshold( ) const;
    const quint16 &getDelayTime( ) const;
    const char &getDetectorReset( ) const;
    const QString &getReceiverDetectorID( ) const;
    const QString &getPid( ) const;  

    void setId( QString id );
    void setChannelID( quint8 channelID );
    void setComments( QString comments );
    void setThreshold( quint16 threshold );
    void setDelayTime( quint16 delayTime );
    void setDetectorReset( char detectorReset );
    void setReceiverDetectorID( QString receiverDetectorID );
    void setPid( QString pid );
    void PrintInfo( )const;


private:
    QString g_pid; // ParkReceiverID
    QString g_id;
    quint8 g_channelID;
    QString g_comments;
    quint16 g_threshold;
    quint16 g_delayTime;
    char g_detectorReset; // 0  1重启
    QString g_receiverDetectorID;
};
Q_DECLARE_METATYPE( ItemInfoDetector )

#endif // ITEMINFODETECTOR_H
