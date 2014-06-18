#include "iteminfopark.h"

ItemInfoPark::ItemInfoPark()
{
}

ItemInfoPark::ItemInfoPark( QString id, QString name, quint16 space, quint16 usedSpace,
                           QString selfNumber, QString comments, QString parkParentID, QString pid )
{
    g_id = id;
    g_name.append( name );
    g_space = space;
    g_usedSpace = usedSpace;
    g_selfNumber.append( selfNumber );
    g_comments.append( comments );
    g_parkParentID.append( parkParentID );
    g_pid.append( pid );
}

const QString &ItemInfoPark::getId() const
{
    return g_id;
}

const QString &ItemInfoPark::getName() const
{
    return g_name;
}

const quint16 &ItemInfoPark::getSpace() const
{
    return g_space;
}

const quint16 &ItemInfoPark::getUsedSpace() const
{
    return g_usedSpace;
}

const QString &ItemInfoPark::getSelfNumber() const
{
    return g_selfNumber;
}

const QString &ItemInfoPark::getComments() const
{
    return g_comments;
}

const QString &ItemInfoPark::getParkParentID() const
{
    return g_parkParentID;
}

const QString &ItemInfoPark::getPid() const
{
    return g_pid;
}

void ItemInfoPark::setId(QString id)
{
    g_id = id;
}

void ItemInfoPark::setName(QString name)
{
    g_name.append( name );
}

void ItemInfoPark::setSpace(quint16 space)
{
    g_space = space;
}

void ItemInfoPark::setUsedSpace(quint16 userdSpace)
{
    g_usedSpace = userdSpace;
}

void ItemInfoPark::setSelfNumber(QString selfNumber)
{
    g_selfNumber.append( selfNumber );
}

void ItemInfoPark::setComments(QString comments)
{
    g_comments.append( comments );
}

void ItemInfoPark::setParkParentID(QString parkParentID)
{
    g_parkParentID.append( parkParentID );
}

void ItemInfoPark::setPid(QString pid)
{
    g_pid.append( pid );
}

void ItemInfoPark::PrintInfo() const
{
}
