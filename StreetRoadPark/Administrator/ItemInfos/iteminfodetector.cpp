#include "iteminfodetector.h"

ItemInfoDetector::ItemInfoDetector()
{
}

ItemInfoDetector::ItemInfoDetector(QString pid, QString id, quint8 channelID, QString comments,
                                   quint16 threshold, quint16 delayTime, char detectorReset, QString receiverDetectorID)
{
    g_pid.append( pid );
    g_id.append( id );
    g_channelID = channelID;
    g_comments.append( comments );
    g_threshold = threshold;
    g_delayTime = delayTime;
    g_detectorReset = detectorReset;
    g_receiverDetectorID.append( receiverDetectorID );
}

const QString &ItemInfoDetector::getId() const
{
    return g_id;
}

const quint8 &ItemInfoDetector::getChannelID() const
{
    return g_channelID;
}

const QString &ItemInfoDetector::getComments() const
{
    return g_comments;
}

const quint16 &ItemInfoDetector::getThreshold() const
{
    return g_threshold;
}

const quint16 &ItemInfoDetector::getDelayTime() const
{
    return g_delayTime;
}

const char &ItemInfoDetector::getDetectorReset() const
{
    return g_detectorReset;
}

const QString &ItemInfoDetector::getReceiverDetectorID() const
{
    return g_receiverDetectorID;
}

const QString &ItemInfoDetector::getPid() const
{
    return g_pid;
}

void ItemInfoDetector::setId(QString id)
{
    g_id.append( id );
}

void ItemInfoDetector::setChannelID(quint8 channelID)
{
    g_channelID = channelID;
}

void ItemInfoDetector::setComments(QString comments)
{
    g_comments.append( comments );
}

void ItemInfoDetector::setThreshold(quint16 threshold)
{
    g_threshold = threshold;
}

void ItemInfoDetector::setDelayTime(quint16 delayTime)
{
    g_delayTime = delayTime;
}

void ItemInfoDetector::setDetectorReset(char detectorReset)
{
    g_detectorReset = detectorReset;
}

void ItemInfoDetector::setReceiverDetectorID(QString receiverDetectorID)
{
    g_receiverDetectorID.append( receiverDetectorID );
}

void ItemInfoDetector::setPid(QString pid)
{
    g_pid.append( pid );
}

void ItemInfoDetector::PrintInfo() const
{
}
