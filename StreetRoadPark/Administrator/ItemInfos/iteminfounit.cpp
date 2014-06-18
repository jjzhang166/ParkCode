#include "iteminfounit.h"

ItemInfoUnit::ItemInfoUnit()
{
}

ItemInfoUnit::ItemInfoUnit(QString id, QString name, QString comments, QString pid, QString address)
{
    g_id.append( id );
    g_name.append( name );
    g_comments.append( comments );
    g_pid.append( pid );
    g_address.append( address );
}

const QString &ItemInfoUnit::getId() const
{
    return g_id;
}

const QString &ItemInfoUnit::getName() const
{
   return g_name;
}

const QString &ItemInfoUnit::getComments() const
{
    return g_comments;
}

const QString &ItemInfoUnit::getPid() const
{
    return g_pid;
}


const QString &ItemInfoUnit::getAddress() const
{
    return g_address;
}

void ItemInfoUnit::setId(QString id)
{
    g_id.append( id );
}

void ItemInfoUnit::setName(QString name)
{
      g_name.append( name );
}

void ItemInfoUnit::setComments(QString comments)
{
    g_comments.append( comments );
}

void ItemInfoUnit::setPid(QString pid)
{
     g_pid.append( pid );
}

void ItemInfoUnit::setAddress(QString address)
{
     g_address.append( address );
}

void ItemInfoUnit::PrintInfo() const
{
}
