#include "iteminforeceiver.h"

ItemInfoReceiver::ItemInfoReceiver()
{
}

ItemInfoReceiver::ItemInfoReceiver(QString pid, QString name, QString id, quint8 channelID, QString comments, QString parkReceiverID)
{
    g_pid.append( pid );
    g_name.append( name );
    g_id.append( id );
    g_channelID = channelID;
    g_comments.append( comments );
    g_parkReceiverID.append( parkReceiverID );
}

const QString &ItemInfoReceiver::getId() const
{
    return g_id;
}

const QString &ItemInfoReceiver::getName() const
{
    return g_name;
}

const quint8 &ItemInfoReceiver::getChannelID() const
{
    return g_channelID;
}

const QString &ItemInfoReceiver::getComments() const
{
    return g_comments;
}

const QString &ItemInfoReceiver::getParkReceiverID() const
{
    return g_parkReceiverID;
}

const QString &ItemInfoReceiver::getPid() const
{
    return g_pid;
}

void ItemInfoReceiver::setId(QString id)
{
    g_id.append( id );
}

void ItemInfoReceiver::setName(QString name)
{
    g_name.append( name );
}

void ItemInfoReceiver::setChannelID( quint8 channelID )
{
    g_channelID = channelID;
}

void ItemInfoReceiver::setComments(QString comments)
{
    g_comments.append( comments );
}

void ItemInfoReceiver::setParkReceiverID(QString parkReceiverID)
{
    g_parkReceiverID.append( parkReceiverID );
}

void ItemInfoReceiver::setPid(QString pid)
{
    g_pid.append( pid );
}

void ItemInfoReceiver::PrintInfo() const
{
}
